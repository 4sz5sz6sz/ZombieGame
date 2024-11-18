#pragma once
#include <vector>
#include <afxwin.h> // CRect 포함
#include "Zombie.h"
#include "CEntity.h"
#include <chrono>  // 쿨타임 계산, ms 단위로 측정 가능.
#include <algorithm>

class CArrowKeyGameDialog; //전방 선언

class CPlayer : public CEntity {
public:
    //double x, y;             // 플레이어의 위치
    double HP; // 체력
    int safeZoneSize;        // 설치되는 안전지대의 크기
    std::chrono::steady_clock::time_point lastSafeZoneTime; // 마지막 안전지대 설치 시간


    CPlayer(double startX, double startY) : CEntity(startX, startY), safeZoneSize(50), lastSafeZoneTime(std::chrono::steady_clock::now()), HP(100.0) {}

    // 안전지대 설치 함수
    void TryToPlaceSafeZone(CArrowKeyGameDialog* pGameDialog, std::vector<CZombie>& zombies, std::vector<CSafeZone>& safeZones);

    // 남은 쿨타임 시간 계산 (초 단위로 반환)
    double GetRemainingCooldownTime() const {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - lastSafeZoneTime;
        return max(3.0 - elapsed.count(), 0.0);  // 3초에서 경과 시간을 뺀 값
    }
    
    void TakeDamage(double amount=5.0); // 데미지 입는 경우 호출
    void Heal(double amount=0.1); // 회복하는 경우 호출
    bool IsAlive() const; // 살아있는지 검사. HP가 0 이상인지 여부.
};

