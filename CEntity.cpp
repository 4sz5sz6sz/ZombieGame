#include "pch.h"
#include "CEntity.h"

// �� CEntity ��ü ���� �浹 ����, �浹�̸� distance=1.0
bool CEntity::CheckCollision(double newX, double newY, const CEntity& other, double distance) const {
    // �� CEntity ��ü ���� �浹 ����, �浹�̸� distance=1.0
    //�浹 ���� �ƴ϶�, �Ÿ� ��� �뵵�� distance ���� ���� ����.
    //ex. ��� ��ᰡ �÷��̾�κ��� ������ �ִ°�?
    double dx = abs(newX - other.x);
    double dy = abs(newY - other.y);
    return (dx <= distance && dy <= distance);
}

// CEntity-CRect �浹 ����, �׵θ� ������ �浹�� ����.
bool CEntity::CheckCollision(double newX, double newY, const CRect& zone) const {
    // CRect�� ������ �׸�. ex. ��������

    double scaledX = newX * SCALE_FACTOR;
    double scaledY = newY * SCALE_FACTOR;

    bool withinLeftRight = (scaledX >= zone.left - GENERAL_MARGIN && scaledX <= zone.right + BOTTOM_RIGHT_MARGIN);
    bool withinTopBottom = (scaledY >= zone.top - GENERAL_MARGIN && scaledY <= zone.bottom + BOTTOM_RIGHT_MARGIN);

    return withinLeftRight && withinTopBottom;
}
