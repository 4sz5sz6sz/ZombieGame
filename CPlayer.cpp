#include "pch.h"
#include "CPlayer.h"
#include "ArrowKeyGameDlg.h"
#include "CMessageManager.h"


void CPlayer::TryToPlaceSafeZone(CArrowKeyGameDialog* pGameDialog, std::vector<CZombie>& zombies, std::vector<CSafeZone>& safeZones) {
    //���� �ð�, ���� �ð� Ȯ��.
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - lastSafeZoneTime;
    
    // 3�ʰ� ������ �ʾ����� ��ġ �Ұ�
    if (elapsed.count() < 3.0) {
        CMessageManager::GetInstance().AddMessage(_T("�������� ��ġ ��Ÿ�� ���Դϴ�..."));
        OutputDebugString(_T("�������� ��ġ ��Ÿ�� ���Դϴ�...\n"));
        return;
    }

    // ���ο� �������� ���� (�÷��̾� �ֺ��� ��ġ)
    CRect newSafeZone(
        static_cast<int>(x * SCALE_FACTOR) - safeZoneSize / 2,
        static_cast<int>(y * SCALE_FACTOR) - safeZoneSize / 2,
        static_cast<int>(x * SCALE_FACTOR) + safeZoneSize / 2,
        static_cast<int>(y * SCALE_FACTOR) + safeZoneSize / 2
    );

    // ���ο� �������� �ȿ� ���� �ִ��� Ȯ��
    for (const auto& zombie : zombies) {
        if (CheckCollision(zombie.x, zombie.y,newSafeZone)) {
            CMessageManager::GetInstance().AddMessage(_T("�������� ��ġ ����: �浹 �߻�"));
            OutputDebugString(_T("�������� ��ġ�� ��ҵǾ����ϴ�. ��ƼƼ�� �������� ���� �ֽ��ϴ�.\n"));
            return;
        }
    }

    // ���� ���ٸ� �������� �߰�
    safeZones.push_back(newSafeZone);

    // ������ ��ġ �ð� ������Ʈ
    pGameDialog->isCooldownActive = true;
    lastSafeZoneTime = now;
}

// ������ �Դ� ��� ȣ��
void CPlayer::TakeDamage(double amount) //����Ʈ �� 5.0
{
    // TODO: ���⿡ ���� �ڵ� �߰�.
    HP = max(HP - amount, 0.0); // ������ 0
}


// ȸ���ϴ� ��� ȣ��
void CPlayer::Heal(double amount)   //����Ʈ �� 0.1
{
    // TODO: ���⿡ ���� �ڵ� �߰�.
    HP = min(HP + amount, 100.0); // ������ 100.0
}


// ����ִ��� �˻�. HP�� 0 �̻����� ����.
bool CPlayer::IsAlive() const
{
    // TODO: ���⿡ ���� �ڵ� �߰�.
    return HP>0;
}
