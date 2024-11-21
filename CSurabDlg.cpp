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


BOOL CSurabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	for (int i = 0; i < 10; i++) {
		if (m_strSurabInven[i].GetLength() >= 1) {
			m_listSurabInven.InsertString(i, m_strSurabInven[i]);
		}
	}
	m_listSurab.AddString(_T("빨간 물약"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
