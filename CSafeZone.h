#pragma once
#include <afxwin.h>
#include <chrono>
class CSafeZone
{
public:
    CRect rect;  // ���������� ��ġ�� ũ��
    bool isDestroyed;  // �ı� ����
    double timeOnZone;  // �÷��̾ �������뿡 �ӹ� �ð� (�� ����)
    int alpha;

    CSafeZone(const CRect& zone)
        : rect(zone), isDestroyed(false), timeOnZone(0.0), alpha(255) {}

};

