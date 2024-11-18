#pragma once
#include <vector>
#include <afxwin.h> // CRect ����
#include "Zombie.h"
#include "CEntity.h"
#include <chrono>  // ��Ÿ�� ���, ms ������ ���� ����.
#include <algorithm>

class CArrowKeyGameDialog; //���� ����

class CPlayer : public CEntity {
public:
    //double x, y;             // �÷��̾��� ��ġ
    double HP; // ü��
    int safeZoneSize;        // ��ġ�Ǵ� ���������� ũ��
    std::chrono::steady_clock::time_point lastSafeZoneTime; // ������ �������� ��ġ �ð�


    CPlayer(double startX, double startY) : CEntity(startX, startY), safeZoneSize(50), lastSafeZoneTime(std::chrono::steady_clock::now()), HP(100.0) {}

    // �������� ��ġ �Լ�
    void TryToPlaceSafeZone(CArrowKeyGameDialog* pGameDialog, std::vector<CZombie>& zombies, std::vector<CSafeZone>& safeZones);

    // ���� ��Ÿ�� �ð� ��� (�� ������ ��ȯ)
    double GetRemainingCooldownTime() const {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - lastSafeZoneTime;
        return max(3.0 - elapsed.count(), 0.0);  // 3�ʿ��� ��� �ð��� �� ��
    }
    
    void TakeDamage(double amount=5.0); // ������ �Դ� ��� ȣ��
    void Heal(double amount=0.1); // ȸ���ϴ� ��� ȣ��
    bool IsAlive() const; // ����ִ��� �˻�. HP�� 0 �̻����� ����.
};

