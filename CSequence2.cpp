// CSequence2.cpp: 구현 파일

#include "pch.h"
#include "ZombieGame.h"
#include "afxdialogex.h"
#include "CSequence2.h"

// CSequence2 대화 상자
IMPLEMENT_DYNAMIC(CSequence2, CDialogEx)

CSequence2::CSequence2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEQUENCE, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSequence2::~CSequence2()
{
}

void CSequence2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_OUTPUT, m_listBox22);
	DDX_Control(pDX, IDC_COMBO_AUTO, m_cbListItem22);
	DDX_Control(pDX, IDC_PIC1, m_picture_control22);
}

BEGIN_MESSAGE_MAP(CSequence2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CSequence2::OnBnClickedButtonDelete)
	ON_COMMAND(IDC_RADIO_BLUE, &CSequence2::OnRadioBlue)
	ON_COMMAND(IDC_RADIO_ORANGE, &CSequence2::OnRadioOrange)
	ON_COMMAND(IDC_RADIO_RED, &CSequence2::OnRadioRed)
	ON_COMMAND(IDC_RADIO_YELLOW, &CSequence2::OnRadioYellow)
	ON_BN_CLICKED(IDC_BUTTON1, &CSequence2::OnBnClickedButton1)
END_MESSAGE_MAP()

// CSequence2 메시지 처리기

void CSequence2::OnBnClickedButtonDelete()
{
	// ComboBox에서 선택된 항목을 삭제합니다.
	int index = m_cbListItem22.GetCurSel();
	if (index != CB_ERR) {
		m_listBox22.DeleteString(index);
		UpdateComboBox22();
	}
	else {
		AfxMessageBox(_T("삭제할 물약을 고르세요"));
	}
}

void CSequence2::OnRadioBlue()
{
	// 파랑 물약을 리스트에 추가하고, ComboBox를 갱신합니다.
	m_listBox22.AddString(_T("파랑 물약"));
	UpdateComboBox22();
	CHECK();
}

void CSequence2::OnRadioOrange()
{
	// 주황 물약을 리스트에 추가하고, ComboBox를 갱신합니다.
	m_listBox22.AddString(_T("주황 물약"));
	UpdateComboBox22();
	CHECK();
}

void CSequence2::OnRadioRed()
{
	// 빨강 물약을 리스트에 추가하고, ComboBox를 갱신합니다.
	m_listBox22.AddString(_T("빨강 물약"));
	UpdateComboBox22();
	CHECK();
}

void CSequence2::OnRadioYellow()
{
	// 노랑 물약을 리스트에 추가하고, ComboBox를 갱신합니다.
	m_listBox22.AddString(_T("노랑 물약"));
	UpdateComboBox22();
	CHECK();
}

void CSequence2::CHECK()
{
	// 리스트가 4개 아이템을 가질 때 정답을 확인합니다.
	int count = m_listBox22.GetCount();
	if (count == 4) {
		CString n1, n2, n3, n4;
		m_listBox22.GetText(0, n1);
		m_listBox22.GetText(1, n2);
		m_listBox22.GetText(2, n3);
		m_listBox22.GetText(3, n4);
		if (n1 == _T("주황 물약") && n2 == _T("빨강 물약") && n3 == _T("파랑 물약") && n4 == _T("노랑 물약")) {
			AfxMessageBox(_T("정답입니다."));
		}
		else {
			AfxMessageBox(_T("틀렸습니다."));
			m_listBox22.ResetContent();
		}
	}
	else if (count > 4) {
		AfxMessageBox(_T("틀렸습니다."));
		m_listBox22.ResetContent();
	}
}

void CSequence2::UpdateComboBox22()
{
	// 리스트 박스의 항목을 ComboBox에 업데이트합니다.
	int nCnt = m_listBox22.GetCount();
	m_cbListItem22.ResetContent();

	for (int i = 0; i < nCnt; i++) {
		CString strItem;
		strItem.Format(_T("리스트 항목: %d"), i + 1);
		m_cbListItem22.AddString(strItem);
	}
}

void CSequence2::OnBnClickedButton1()
{
	// 이미지 표시 버튼 클릭 시 픽처 컨트롤에 이미지를 표시합니다.
	CRect rect2; // 픽처 컨트롤의 크기를 저장할 CRect 객체
	m_picture_control22.GetWindowRect(rect2); // GetWindowRect를 사용해서 픽처 컨트롤의 크기를 받는다.
	CDC* dc = m_picture_control22.GetDC(); // 픽처 컨트롤의 DC를 얻는다.
	CImage image; // 불러오고 싶은 이미지를 로드할 CImage 
	image.Load(_T("zombi_get_hint.png")); // 원하는 이미지 경로로 변경
	image.StretchBlt(dc->m_hDC, 0, 0, rect2.Width(), rect2.Height(), SRCCOPY); // 이미지를 픽처 컨트롤 크기로 조정
	ReleaseDC(dc); // DC 해제
}

BOOL CSequence2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr) {
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.
	SetIcon(m_hIcon, TRUE);  // 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE); // 작은 아이콘을 설정합니다.

	return TRUE;
}
