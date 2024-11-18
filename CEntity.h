#pragma once
#include <afxwin.h>
#include <vector>

const int SCALE_FACTOR = 20;    //���� ���. 20��� �����ϸ� �ȴٴ� ��. �׸� �浹 ������ �ʿ���.
const int GENERAL_MARGIN = 15;  //�浹����, �׸���� 9�� 12�� ������ ������.
const int BOTTOM_RIGHT_MARGIN = -2; //�浹����, �׸���� 6�� 3�� ������ ������.
//15, -2�� �����̾���.
//20,2�� ����.

class CEntity {
public:
    double x, y;  // ���� ��ġ ���� (double Ÿ�� ��ǥ)

    CEntity(double startX, double startY) : x(startX), y(startY) {}

    // �� CEntity ��ü ���� �浹 ����, �浹�̸� distance=1.0
    bool CheckCollision(double newX, double newY, const CEntity& other, double distance=1.0) const {
        //�浹 ���� �ƴ϶�, �Ÿ� ��� �뵵�� distance ���� ���� ����.
        //ex. ��� ��ᰡ �÷��̾�κ��� ������ �ִ°�?
        double dx = abs(newX - other.x);
        double dy = abs(newY - other.y);
        return (dx <= distance && dy <= distance);
    }

    // CEntity-CRect �浹 ����  , �׵θ� ������ �浹�� ����.
    // CRect�� ������ �׸�.
    // //CRect�� ����: ��������.
    bool CheckCollision(double newX, double newY, const CRect& zone) const {
        double scaledX = newX * SCALE_FACTOR;
        double scaledY = newY * SCALE_FACTOR;

        bool withinLeftRight = (scaledX >= zone.left - GENERAL_MARGIN && scaledX <= zone.right + BOTTOM_RIGHT_MARGIN);
        bool withinTopBottom = (scaledY >= zone.top - GENERAL_MARGIN && scaledY <= zone.bottom + BOTTOM_RIGHT_MARGIN);

        return withinLeftRight && withinTopBottom;
    }
};
