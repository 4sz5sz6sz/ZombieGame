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

    // �� CEntity-CEntity ��ü ���� �浹 ����, �浹�̸� distance=1.0
    bool CheckCollision(double newX, double newY, const CEntity& other, double distance=1.0) const;

    // CEntity-CRect �浹 ����, �׵θ� ������ �浹�� ����.
    bool CheckCollision(double newX, double newY, const CRect& zone) const;
};
