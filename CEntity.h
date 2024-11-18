#pragma once
#include <afxwin.h>
#include <vector>

const int SCALE_FACTOR = 20;    //전역 상수. 20배로 스케일링 된다는 뜻. 네모 충돌 판정에 필요함.
const int GENERAL_MARGIN = 15;  //충돌판정, 네모기준 9시 12시 방향의 보정값.
const int BOTTOM_RIGHT_MARGIN = -2; //충돌판정, 네모기준 6시 3시 방향의 보정값.
//15, -2가 최적이었음.
//20,2로 변경.

class CEntity {
public:
    double x, y;  // 공통 위치 정보 (double 타입 좌표)

    CEntity(double startX, double startY) : x(startX), y(startY) {}

    // 두 CEntity 객체 간의 충돌 판정, 충돌이면 distance=1.0
    bool CheckCollision(double newX, double newY, const CEntity& other, double distance=1.0) const {
        //충돌 판정 아니라, 거리 재는 용도면 distance 값을 조정 가능.
        //ex. 노란 재료가 플레이어로부터 가까이 있는가?
        double dx = abs(newX - other.x);
        double dy = abs(newY - other.y);
        return (dx <= distance && dy <= distance);
    }

    // CEntity-CRect 충돌 판정  , 테두리 닿으면 충돌로 판정.
    // CRect는 고정된 네모.
    // //CRect의 예시: 안전지대.
    bool CheckCollision(double newX, double newY, const CRect& zone) const {
        double scaledX = newX * SCALE_FACTOR;
        double scaledY = newY * SCALE_FACTOR;

        bool withinLeftRight = (scaledX >= zone.left - GENERAL_MARGIN && scaledX <= zone.right + BOTTOM_RIGHT_MARGIN);
        bool withinTopBottom = (scaledY >= zone.top - GENERAL_MARGIN && scaledY <= zone.bottom + BOTTOM_RIGHT_MARGIN);

        return withinLeftRight && withinTopBottom;
    }
};
