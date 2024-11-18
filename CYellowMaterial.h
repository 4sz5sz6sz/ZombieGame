#pragma once
#include "CEntity.h"
class CYellowMaterial: public CEntity
{
public:
	bool collected; // 노란재료 수집 여부 저장
	CYellowMaterial(double startX, double startY) 
		: CEntity(startX, startY), collected(false) {}
	// 플레이어 충돌 여부 검사
	bool CheckCollisionWithPlayer(double playerX, double playerY) {
		return CheckCollision(playerX, playerY, *this);
	}
};


