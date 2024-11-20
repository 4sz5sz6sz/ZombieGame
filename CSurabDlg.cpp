// CSurabDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ZombieGame.h"
#include "afxdialogex.h"
#include "CSurabDlg.h"


// CSurabDlg 대화 상자

IMPLEMENT_DYNAMIC(CSurabDlg, CDialogEx)

CSurabDlg::CSurabDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SURAB, pParent)
{

}

CSurabDlg::~CSurabDlg()
{
}

void CSurabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SURABINVEN, m_listSurabInven);
	DDX_Control(pDX, IDC_LIST_SURAB, m_listSurab);
}


BEGIN_MESSAGE_MAP(CSurabDlg, CDialogEx)
END_MESSAGE_MAP()


// CSurabDlg 메시지 처리기
