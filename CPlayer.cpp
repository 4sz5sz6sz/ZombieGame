#include "pch.h"
#include "CPlayer.h"
#include "ArrowKeyGameDlg.h"
#include "CMessageManager.h"


void CPlayer::TryToPlaceSafeZone(CArrowKeyGameDialog* pGameDialog, std::vector<CZombie>& zombies, std::vector<CSafeZone>& safeZones) {
    //현재 시간, 지난 시간 확인.
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - lastSafeZoneTime;
    
    // 3초가 지나지 않았으면 설치 불가
    if (elapsed.count() < 3.0) {
        CMessageManager::GetInstance().AddMessage(_T("안전지대 설치 쿨타임 중입니다..."));
        OutputDebugString(_T("안전지대 설치 쿨타임 중입니다...\n"));
        return;
    }

    // 새로운 안전지대 설정 (플레이어 주변에 배치)
    CRect newSafeZone(
        static_cast<int>(x * SCALE_FACTOR) - safeZoneSize / 2,
        static_cast<int>(y * SCALE_FACTOR) - safeZoneSize / 2,
        static_cast<int>(x * SCALE_FACTOR) + safeZoneSize / 2,
        static_cast<int>(y * SCALE_FACTOR) + safeZoneSize / 2
    );

    // 새로운 안전지대 안에 좀비가 있는지 확인
    for (const auto& zombie : zombies) {
        if (CheckCollision(zombie.x, zombie.y,newSafeZone)) {
            CMessageManager::GetInstance().AddMessage(_T("안전지대 설치 실패: 충돌 발생"));
            OutputDebugString(_T("안전지대 설치가 취소되었습니다. 엔티티가 안전지대 내에 있습니다.\n"));
            return;
        }
    }

    // 좀비가 없다면 안전지대 추가
    safeZones.push_back(newSafeZone);

    // 마지막 설치 시간 업데이트
    pGameDialog->isCooldownActive = true;
    lastSafeZoneTime = now;
}

// 데미지 입는 경우 호출
void CPlayer::TakeDamage(double amount) //디폴트 값 5.0
{
    // TODO: 여기에 구현 코드 추가.
    HP = max(HP - amount, 0.0); // 하한이 0
}


// 회복하는 경우 호출
void CPlayer::Heal(double amount)   //디폴트 값 0.1
{
    // TODO: 여기에 구현 코드 추가.
    HP = min(HP + amount, 100.0); // 상한이 100.0
}


// 살아있는지 검사. HP가 0 이상인지 여부.
bool CPlayer::IsAlive() const
{
    // TODO: 여기에 구현 코드 추가.
    return HP>0;
}
