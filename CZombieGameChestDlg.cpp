// CZombieGameChestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ZombieGame.h"
#include "afxdialogex.h"
#include "CZombieGameChestDlg.h"
int flag = 0;
int clockpicture = 0;
// CZombieGameChestDlg 대화 상자

IMPLEMENT_DYNAMIC(CZombieGameChestDlg, CDialogEx)

CZombieGameChestDlg::CZombieGameChestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHEST, pParent)
{
	
}

CZombieGameChestDlg::~CZombieGameChestDlg()
{
}

void CZombieGameChestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ANSWER, m_listAnswer);
	DDX_Control(pDX, IDC_PIC_CLOCK, m_picClock);

	DDX_Control(pDX, IDC_LIST_CHEST_INSIDE, m_listChestInside);
}


BEGIN_MESSAGE_MAP(CZombieGameChestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLOCK_REVERSE, &CZombieGameChestDlg::OnClickedButtonClockReverse)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CZombieGameChestDlg::OnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CZombieGameChestDlg::OnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CZombieGameChestDlg::OnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CZombieGameChestDlg::OnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CZombieGameChestDlg::OnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CZombieGameChestDlg::OnClickedButtonClear)
END_MESSAGE_MAP()


// CZombieGameChestDlg 메시지 처리기

void CZombieGameChestDlg::OnClickedButtonClockReverse()
{
	if (clockpicture == 0) {
		clockpicture++;
		CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
		m_picClock.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
		CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
		dc = m_picClock.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
		CImage image;//불러오고 싶은 이미지를 로드할 CImage 
		image.Load(_T("Clock.png"));//이미지 로드
		image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
		ReleaseDC(dc);
	}
	else {
		MessageBox(_T("이미 시계가 보이는데 굳이 뒤집을 필요는 없잖아요..."), _T("이런!"), MB_ICONWARNING);
	}
}


void CZombieGameChestDlg::OnClickedButtonCheck()
{
	CString str;
	int nCount = m_listAnswer.GetCount();
	int ch = 0;
		for (int i = 0; i < nCount; i++)
		{
			m_listAnswer.GetText(i, str);
			if (i >= 0 && i <= 4) {
				if (str == "→")
					ch++;
			}
			if (i >= 5 && i <= 8) {
				if (str == "←")
					ch++;
			}
			if (i >= 9 && i <= 11) {
				if (str == "↓")
					ch++;
			}
			if (i >= 12 && i <= 16) {
				if (str == "↑")
					ch++;
			}
		}
	if (ch == nCount && nCount != 0) {
		if (flag == 0) {
			flag++;
			MessageBox(_T("금고 문이 열렸다!"), _T("덜컥!"), MB_ICONINFORMATION);
			m_listChestInside.AddString(_T("물약"));
		}
		else {
			MessageBox(_T("이미 금고 문은 열려있어..."), _T("저런!"), MB_ICONWARNING);
		}
	}
	else {
		MessageBox(_T("비밀번호가 틀린거 같다...\n다시 해보자"), _T("이런!"), MB_ICONWARNING);
	}
}

void CZombieGameChestDlg::OnClickedButtonUp() // 위 버튼 입력
{
	m_listAnswer.AddString(_T("↑"));
}


void CZombieGameChestDlg::OnClickedButtonDown() // 아래 버튼 입력
{
	m_listAnswer.AddString(_T("↓"));
}


void CZombieGameChestDlg::OnClickedButtonRight() // 오른쪽 버튼 입력
{
	m_listAnswer.AddString(_T("→"));
}


void CZombieGameChestDlg::OnClickedButtonLeft() // 왼쪽 버튼 입력
{
	m_listAnswer.AddString(_T("←"));
}


void CZombieGameChestDlg::OnClickedButtonClear()
{
	int nCount = m_listAnswer.GetCount();
	for (int i = 0; i < nCount; i++) {
		m_listAnswer.DeleteString(0);
	}

}
