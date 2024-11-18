// CManufacture.cpp: 구현 파일
//

#include "pch.h"
#include "ZombieGame.h"
#include "afxdialogex.h"
#include "CManufacture.h"


// CManufacture 대화 상자

IMPLEMENT_DYNAMIC(CManufacture, CDialogEx)

CManufacture::CManufacture(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CManufacture::~CManufacture()
{
}

void CManufacture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManufacture, CDialogEx)
END_MESSAGE_MAP()


// CManufacture 메시지 처리기
