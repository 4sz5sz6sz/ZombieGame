
// ZombieGameDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ZombieGame.h"
#include "ZombieGameDlg.h"
#include "afxdialogex.h"
#include "CSequenceDlg.h"
#include "CManufacture.h"
#include "ArrowKeyGameDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CZombieGameDlg 대화 상자



CZombieGameDlg::CZombieGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZOMBIEGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bUnitViewed = false; // 금고 버튼 초기화
	m_bChestButton = false; // 나무상자 버튼 초기화
}

void CZombieGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CZombieGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SAFE, &CZombieGameDlg::OnClickedButtonSafe)
	ON_BN_CLICKED(IDC_BUTTON_CHEST, &CZombieGameDlg::OnClickedButtonChest)
	ON_BN_CLICKED(IDC_BUTTON_VACCINE_MANFACTURING_MACHINE, &CZombieGameDlg::OnBnClickedButtonVaccineManfacturingMachine)
	ON_BN_CLICKED(IDC_BUTTON_DOOR, &CZombieGameDlg::OnBnClickedButtonDoor)
END_MESSAGE_MAP()


// CZombieGameDlg 메시지 처리기

BOOL CZombieGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CZombieGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CZombieGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CZombieGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CZombieGameDlg::OnClickedButtonSafe()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	sdlg.DoModal(); // 모달모달모발모발자라나라모발모발
	if (!m_bUnitViewed)
	{
		m_dlgZGSave.Create(IDD_DIALOG_SAFE, this);

		CRect rectMain, rectUnitTable;
		GetWindowRect(&rectMain);

		//m_dlgZGSave.GetWindowRect(&rectUnitTable); 이거 제거하면 왜 되는거임?
		m_dlgZGSave.MoveWindow(rectMain.right, rectMain.top, rectUnitTable.Width(),
			rectUnitTable.Height());

		m_dlgZGSave.ShowWindow(SW_SHOW);
		m_bUnitViewed = TRUE;
	}
	else
	{
		m_dlgZGSave.ShowWindow(SW_HIDE);
		m_dlgZGSave.DestroyWindow();
		m_bUnitViewed = FALSE;
	}
}


void CZombieGameDlg::OnClickedButtonChest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cdlg.DoModal();
	if (!m_bChestButton)
	{
		m_dlgZGChest.Create(IDD_DIALOG_CHEST, this);

		CRect rectMain, rectUnitTable;
		GetWindowRect(&rectMain);

		//m_dlgZGChest.GetWindowRect(&rectUnitTable);
		m_dlgZGChest.MoveWindow(rectMain.right, rectMain.top, rectUnitTable.Width(),
			rectUnitTable.Height());

		m_dlgZGChest.ShowWindow(SW_SHOW);
		m_bChestButton = TRUE;
	}
	else
	{
		m_dlgZGChest.ShowWindow(SW_HIDE);
		m_dlgZGChest.DestroyWindow();
		m_bChestButton = FALSE;
	}
}


void CZombieGameDlg::OnBnClickedButtonVaccineManfacturingMachine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CSequenceDlg sequenceDlg;
	//sequenceDlg.DoModal();
	CManufacture Manufacture;
	Manufacture.DoModal();


}


void CZombieGameDlg::OnBnClickedButtonDoor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CArrowKeyGameDialog arrowKeyDialog;
	arrowKeyDialog.DoModal(); // 모달 창으로 표시
}
