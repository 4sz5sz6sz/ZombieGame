#include "pch.h"
#include "CEntity.h"

// 두 CEntity 객체 간의 충돌 판정, 충돌이면 distance=1.0
bool CEntity::CheckCollision(double newX, double newY, const CEntity& other, double distance) const {
    // 두 CEntity 객체 간의 충돌 판정, 충돌이면 distance=1.0
    //충돌 판정 아니라, 거리 재는 용도면 distance 값을 조정 가능.
    //ex. 노랑 재료가 플레이어로부터 가까이 있는가?
    double dx = abs(newX - other.x);
    double dy = abs(newY - other.y);
    return (dx <= distance && dy <= distance);
}

// CEntity-CRect 충돌 판정, 테두리 닿으면 충돌로 판정.
bool CEntity::CheckCollision(double newX, double newY, const CRect& zone) const {
    // CRect는 고정된 네모. ex. 안전지대

    double scaledX = newX * SCALE_FACTOR;
    double scaledY = newY * SCALE_FACTOR;

    bool withinLeftRight = (scaledX >= zone.left - GENERAL_MARGIN && scaledX <= zone.right + BOTTOM_RIGHT_MARGIN);
    bool withinTopBottom = (scaledY >= zone.top - GENERAL_MARGIN && scaledY <= zone.bottom + BOTTOM_RIGHT_MARGIN);

    return withinLeftRight && withinTopBottom;
}
