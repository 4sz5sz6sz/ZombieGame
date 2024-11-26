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
	DDX_Control(pDX, IDC_PIC_GETRED, m_picGetRed);
}


BEGIN_MESSAGE_MAP(CSurabDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CSurabDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SURAB_MOVE, &CSurabDlg::OnBnClickedButtonSurabMove)
	ON_WM_PAINT()
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


void CSurabDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (int i = 0; i < m_listSurabInven.GetCount(); i++) {
		m_listSurabInven.GetText(i, m_strSurabInven[i]);
	}
	CDialogEx::OnCancel();
}


void CSurabDlg::OnBnClickedButtonSurabMove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	int leftIndex = m_listSurab.GetCurSel();
	if (leftIndex != LB_ERR) {
		m_listSurab.GetText(leftIndex, str);
		m_listSurab.DeleteString(leftIndex);
		m_listSurabInven.AddString(str);
	}
}


void CSurabDlg::OnPaint()
{
	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_picGetRed.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* tt; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	tt = m_picGetRed.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	CImage image;//불러오고 싶은 이미지를 로드할 CImage 
	image.Load(_T("drawer.png"));//이미지 로드
	image.StretchBlt(tt->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
	ReleaseDC(tt);

	CPaintDC dc(this);
}
