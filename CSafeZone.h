#pragma once
#include <afxwin.h>
#include <chrono>
class CSafeZone
{
public:
    CRect rect;  // 안전지대의 위치와 크기
    bool isDestroyed;  // 파괴 여부
    double timeOnZone;  // 플레이어가 안전지대에 머문 시간 (초 단위)
    int alpha;

    CSafeZone(const CRect& zone)
        : rect(zone), isDestroyed(false), timeOnZone(0.0), alpha(255) {}

};

