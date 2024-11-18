// ZombieMovement.h
//좀비 충돌, 좀비 이동을 나타내는 함수 2개 정의.
#pragma once
#include "Zombie.h"
#include <vector>

//bool IsPositionOccupied(double newX, double newY, const std::vector<Zombie>& zombies) {
//    for (const auto& zombie : zombies) {
//        if (abs(zombie.x - newY) < 0.3 && abs(zombie.y - newY < 0.3)) {
//            return true;
//        }
//    }
//    return false;
//}
//
//void MoveTowards(Zombie& zombie, double playerX, double playerY, const std::vector<Zombie>& zombies) {
//    double newX = zombie.x;
//    double newY = zombie.y;
//
//    if (zombie.x < playerX) newX += zombie.zombieSpeed;
//    else if (zombie.x > playerX) newX -= zombie.zombieSpeed;
//
//    if (zombie.y < playerY) newY += zombie.zombieSpeed;
//    else if (zombie.y > playerY) newY -= zombie.zombieSpeed;
//
//    if (!IsPositionOccupied(newX, newY, zombies)) {
//        zombie.x = newX;
//        zombie.y = newY;
//    }
//}

//void MoveZombie(Zombie& zombie, std::vector<Zombie>& zombies) {
//    int newX = zombie.x + zombie.directionX;
//    int newY = zombie.y + zombie.directionY;
//
//    if (!IsPositionOccupied(newX, newY, zombies)) {
//        zombie.SetPosition(newX, newY);
//    }
//    else {
//        zombie.directionX = -zombie.directionX;
//        zombie.directionY = -zombie.directionY;
//        zombie.Move();
//    }
//}
