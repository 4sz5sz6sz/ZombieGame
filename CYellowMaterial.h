#pragma once
#include "CEntity.h"
class CYellowMaterial: public CEntity
{
public:
	bool collected; // ������ ���� ���� ����
	CYellowMaterial(double startX, double startY) 
		: CEntity(startX, startY), collected(false) {}
	// �÷��̾� �浹 ���� �˻�
	bool CheckCollisionWithPlayer(double playerX, double playerY) {
		return CheckCollision(playerX, playerY, *this);
	}
};


