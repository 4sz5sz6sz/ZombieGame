//����Ű ���ӿ��� ���̴� Zombie ��ü�鿡 ���� ����. Ŭ����.
#pragma once
#include "CEntity.h"
#include "CSafeZone.h"


class CZombie : public CEntity {
public:
    double zombieSpeed;
    int index;

    CZombie(double startX, double startY, int idx, double speed=0.8)
        : CEntity(startX, startY), index(idx), zombieSpeed(speed) {}

    bool IsPositionOccupied(double newX, double newY, const std::vector<CZombie>& zombies) const {
        for (const auto& zombie : zombies) {
            if (index == zombie.index) continue;
            if (abs(zombie.x - newX) <= 0.5 && abs(zombie.y - newY) <= 0.5) {
                return true;
            }
            
        }
        return false;
    }

    void MoveTowards(double playerX, double playerY, const std::vector<CZombie>& zombies, const std::vector<CSafeZone>& safeZones, bool isZombieFlipEnabled) {
        double dx = 0.0, dy = 0.0;

        //ALTŰ ���� Ȯ��
        bool isCKeyPressed = (GetAsyncKeyState('C') & 0x8000) != 0;

        if (rand() % 3 == 0) {
            // 33% Ȯ���� ���� �̵�
            int randomDirection = rand() % 4;  // 0: ��, 1: ��, 2: ��, 3: ��
            switch (randomDirection) {
            case 0: dy = -zombieSpeed; break;  // ��
            case 1: dy = zombieSpeed; break;  // ��
            case 2: dx = -zombieSpeed; break;  // ��
            case 3: dx = zombieSpeed; break;  // ��
            }
        }
        else {
            //
            bool reverseDirection = isZombieFlipEnabled && isCKeyPressed;

            // �÷��̾� �������� �̵�
            if ((x < playerX)^ reverseDirection) dx = zombieSpeed;
            else if ((x > playerX)^ reverseDirection) dx = -zombieSpeed;

            if ((y < playerY)^ reverseDirection) dy = zombieSpeed;
            else if ((y > playerY)^ reverseDirection) dy = -zombieSpeed;
        }

        if (dx && dy) {
            dx /= sqrt(2);
            dy /= sqrt(2);
        }

        double newX = x + dx;
        double newY = y + dy;

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
