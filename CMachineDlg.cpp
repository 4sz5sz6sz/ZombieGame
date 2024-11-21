// CMachineDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ZombieGame.h"
#include "afxdialogex.h"
#include "CMachineDlg.h"


// CMachineDlg 대화 상자

IMPLEMENT_DYNAMIC(CMachineDlg, CDialogEx)

CMachineDlg::CMachineDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MACHINE, pParent)
{

}

CMachineDlg::~CMachineDlg()
{
}

void CMachineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMachineDlg, CDialogEx)
END_MESSAGE_MAP()


// CMachineDlg 메시지 처리기
