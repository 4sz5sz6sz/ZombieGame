//����Ű ���ӿ��� ���̴� Zombie ��ü�鿡 ���� ����. Ŭ����.
#pragma once
#include "CEntity.h"
#include "CSafeZone.h"


class CZombie : public CEntity {
public:
    double zombieSpeed;
    int index;

    CZombie(double startX, double startY, int idx)
        : CEntity(startX, startY), index(idx), zombieSpeed(0.5) {}

    bool IsPositionOccupied(double newX, double newY, const std::vector<CZombie>& zombies) const {
        for (const auto& zombie : zombies) {
            if (index == zombie.index) continue;
            if (abs(zombie.x - newX) <= 0.5 && abs(zombie.y - newY) <= 0.5) {
                return true;
            }
            
        }
        return false;
    }

    void MoveTowards(double playerX, double playerY, const std::vector<CZombie>& zombies, const std::vector<CSafeZone>& safeZones) {
        double newX = x;
        double newY = y;
        
        if (rand() % 3 == 0) {
            // ���� �̵�
            int randomDirection = rand() % 4;  // 0: ��, 1: ��, 2: ��, 3: ��
            switch (randomDirection) {
            case 0: newY -= zombieSpeed; break;  // ��
            case 1: newY += zombieSpeed; break;  // ��
            case 2: newX -= zombieSpeed; break;  // ��
            case 3: newX += zombieSpeed; break;  // ��
            }
        }
        else {
            // �÷��̾� �������� �̵�
            if (x < playerX) newX += zombieSpeed;
            else if (x > playerX) newX -= zombieSpeed;

            if (y < playerY) newY += zombieSpeed;
            else if (y > playerY) newY -= zombieSpeed;
        }

        if (!IsInSafeZones(newX, newY, safeZones) && !IsPositionOccupied(newX, newY, zombies)) {
            x = newX;
            y = newY;
        }
    }

    
    bool IsInSafeZones(double newX, double newY, const std::vector<CSafeZone>& safeZones) {
        for (const auto& zone : safeZones) {
            if (CheckCollision(newX, newY, zone.rect)) {
                return true;  // �������� ���� ����
            }
        }
        return false;
    }
};
