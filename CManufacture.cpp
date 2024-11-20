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
	DDX_Control(pDX, IDC_LIST_MYPOKET, m_listCheckMedicine);
	DDX_Control(pDX, IDC_PIC_End, m_picture_control_End);
}


BEGIN_MESSAGE_MAP(CManufacture, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_MYPOKET, &CManufacture::OnLbnSelchangeListMypoket)
	ON_BN_CLICKED(IDC_BUTTON5, &CManufacture::OnBnClickedEndGame)
END_MESSAGE_MAP()


// CManufacture 메시지 처리기


void CManufacture::OnLbnSelchangeListMypoket()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CManufacture::OnBnClickedEndGame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//백신 제조를 눌렀을때 백신을 올게 만들었는지 아닌지 확인하는 코드
	EndCheck();
}


void CManufacture::EndCheck()
{
	// TODO: 여기에 구현 코드 추가.
	int count = m_listCheckMedicine.GetCount();
	if (count == 4) {
		CString n1, n2, n3, n4;
		m_listCheckMedicine.GetText(0, n1);
		m_listCheckMedicine.GetText(1, n2);
		m_listCheckMedicine.GetText(2, n3);
		m_listCheckMedicine.GetText(3, n4);
		if (n1 == _T("주황 물약") && n2 == _T("빨강 물약") && n3 == _T("파랑 물약") && n4 == _T("노랑 물약")) {
			AfxMessageBox(_T("좀비 치료에 성공하였다."));
		}
		else {
			AfxMessageBox(_T("좀비 세상이다.."));
			m_listCheckMedicine.ResetContent();
			PrintPicture();
		}
	}
	else if (count > 4) {
		AfxMessageBox(_T("좀비 세상이다.."));
		m_listCheckMedicine.ResetContent();
	}
	PrintPicture_Good();
}

void CManufacture::PrintPicture()
{
	// TODO: 여기에 구현 코드 추가.
	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_picture_control_End.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc = m_picture_control_End.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	CImage image;//불러오고 싶은 이미지를 로드할 CImage 
	image.Load(_T("베드 엔딩"));//이미지 로드

	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
	ReleaseDC(dc);//DC 해제
}


void CManufacture::PrintPicture_Good()
{
	// TODO: 여기에 구현 코드 추가.
	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_picture_control_End.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc = m_picture_control_End.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	CImage image;//불러오고 싶은 이미지를 로드할 CImage 
	image.Load(_T("해피 엔딩"));//이미지 로드

	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
	ReleaseDC(dc);//DC 해제
}
