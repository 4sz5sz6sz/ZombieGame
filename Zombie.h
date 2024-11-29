//방향키 게임에서 쓰이는 Zombie 객체들에 대한 정의. 클래스.
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

        //ALT키 상태 확인
        bool isCKeyPressed = (GetAsyncKeyState('C') & 0x8000) != 0;

        if (rand() % 3 == 0) {
            // 33% 확률로 랜덤 이동
            int randomDirection = rand() % 4;  // 0: 상, 1: 하, 2: 좌, 3: 우
            switch (randomDirection) {
            case 0: dy = -zombieSpeed; break;  // 상
            case 1: dy = zombieSpeed; break;  // 하
            case 2: dx = -zombieSpeed; break;  // 좌
            case 3: dx = zombieSpeed; break;  // 우
            }
        }
        else {
            //
            bool reverseDirection = isZombieFlipEnabled && isCKeyPressed;

            // 플레이어 방향으로 이동
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
                return true;  // 안전지대 내에 있음
            }
        }
        return false;
    }
};
