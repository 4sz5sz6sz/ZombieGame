//방향키 게임에서 쓰이는 Zombie 객체들에 대한 정의. 클래스.
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
            // 랜덤 이동
            int randomDirection = rand() % 4;  // 0: 상, 1: 하, 2: 좌, 3: 우
            switch (randomDirection) {
            case 0: newY -= zombieSpeed; break;  // 상
            case 1: newY += zombieSpeed; break;  // 하
            case 2: newX -= zombieSpeed; break;  // 좌
            case 3: newX += zombieSpeed; break;  // 우
            }
        }
        else {
            // 플레이어 방향으로 이동
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
                return true;  // 안전지대 내에 있음
            }
        }
        return false;
    }
};
