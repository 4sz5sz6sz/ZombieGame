// CMachineDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ZombieGame.h"
#include "afxdialogex.h"
#include "CMachineDlg.h"


// CMachineDlg 대화 상자
bool see_ending = false;
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
	DDX_Control(pDX, IDC_LIST_MACHINE_INVEN, m_listMachineInven);
	DDX_Control(pDX, IDC_LIST_VACCINE_MACHINE, m_listVaccineMachine);
	DDX_Control(pDX, IDC_PIC_End, m_picEnd);
}


BEGIN_MESSAGE_MAP(CMachineDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CMachineDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_MACHINE_MOVE, &CMachineDlg::OnBnClickedButtonMachineMove)
	ON_BN_CLICKED(IDC_BUTTON_MAKE, &CMachineDlg::OnBnClickedButtonMake)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, &CMachineDlg::OnClickedButtonReturn)
END_MESSAGE_MAP()


// CMachineDlg 메시지 처리기



void CMachineDlg::PrintPicture()
{
	// TODO: 여기에 구현 코드 추가.
		// TODO: 여기에 구현 코드 추가.
	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_picture_control_End.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc = m_picture_control_End.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	CImage image;//불러오고 싶은 이미지를 로드할 CImage 
	image.Load(_T("ending_bad.png"));//이미지 로드

	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
	ReleaseDC(dc);//DC 해제
}


void CMachineDlg::PrintPicture_Good()
{
	// TODO: 여기에 구현 코드 추가.
		// TODO: 여기에 구현 코드 추가.
	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_picture_control_End.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc = m_picture_control_End.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	CImage image;//불러오고 싶은 이미지를 로드할 CImage 
	image.Load(_T("ending_happy.png"));//이미지 로드

	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
	ReleaseDC(dc);//DC 해제
}




void CMachineDlg::EndCheck()
{
	// TODO: 여기에 구현 코드 추가.
	
	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_picEnd.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc = m_picEnd.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	CImage image;//불러오고 싶은 이미지를 로드할 CImage 

	int count1 = m_listVaccineMachine.GetCount();
	if (count1 == 4) {
		CString n1, n2, n3, n4;
		m_listVaccineMachine.GetText(0, n1);
		m_listVaccineMachine.GetText(1, n2);
		m_listVaccineMachine.GetText(2, n3);
		m_listVaccineMachine.GetText(3, n4);
		if (n1 == _T("주황 물약") && n2 == _T("빨강 물약") && n3 == _T("파랑 물약") && n4 == _T("노랑 물약")) {
			AfxMessageBox(_T("좀비 치료에 성공하였다."));
			//PrintPicture_Good();
			image.Load(_T("ending_happy.png"));//이미지 로드
			see_ending = true;
			image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
			ReleaseDC(dc);//DC 해제
		}
		else {
			AfxMessageBox(_T("좀비 세상이다.."));
			m_listVaccineMachine.ResetContent();
			//PrintPicture();
			image.Load(_T("ending_bad.png"));//이미지 로드
			see_ending = true;
			image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
			ReleaseDC(dc);//DC 해제
		}
	}
	else{
		AfxMessageBox(_T("좀비 세상이다.."));
		m_listVaccineMachine.ResetContent();
		//PrintPicture();
		image.Load(_T("ending_bad.png"));//이미지 로드
		see_ending = true;
		image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
		ReleaseDC(dc);//DC 해제
	}
}


void CMachineDlg::OnBnClickedCancel()
{
	if (m_listVaccineMachine.GetCount() && !see_ending) {
		MessageBox(_T("백신 제조 기계에 물약이 남아 있는거 같아."), _T("잠깐!"), MB_ICONWARNING);
	}
	else {
		int i;
		if (see_ending)
			m_strMachineInven[m_listMachineInven.GetCount()] = "엔딩";
		for (i = 0; i < m_listMachineInven.GetCount(); i++) {
			m_listMachineInven.GetText(i, m_strMachineInven[i]);
		}
		CDialogEx::OnCancel();
	}
}


BOOL CMachineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	for (int i = 0; i < 10; i++) {
		if (m_strMachineInven[i].GetLength() >= 1) {
			m_listMachineInven.InsertString(i, m_strMachineInven[i]);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMachineDlg::OnBnClickedButtonMachineMove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	int leftIndex = m_listMachineInven.GetCurSel();
	if (leftIndex != LB_ERR) {
		m_listMachineInven.GetText(leftIndex, str);
		m_listMachineInven.DeleteString(leftIndex);
		m_listVaccineMachine.AddString(str);
	}
}

void CMachineDlg::OnClickedButtonReturn()
{
	CString str;
	int leftIndex = m_listVaccineMachine.GetCurSel();
	if (leftIndex != LB_ERR) {
		m_listVaccineMachine.GetText(leftIndex, str);
		m_listVaccineMachine.DeleteString(leftIndex);
		m_listMachineInven.AddString(str);
	}
}

void CMachineDlg::OnBnClickedButtonMake()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndCheck();
}
