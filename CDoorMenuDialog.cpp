// CDoorMenuDialog.cpp: 구현 파일
//

#include "pch.h"
#include "ZombieGame.h"
#include "afxdialogex.h"
#include "CDoorMenuDialog.h"


// CDoorMenuDialog 대화 상자

IMPLEMENT_DYNAMIC(CDoorMenuDialog, CDialogEx)

CDoorMenuDialog::CDoorMenuDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DOOR_MENU_DIALOG, pParent)
{

}

CDoorMenuDialog::~CDoorMenuDialog()
{
}

void CDoorMenuDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDoorMenuDialog, CDialogEx)
	ON_BN_CLICKED(IDC_STAGE_BUTTON1, &CDoorMenuDialog::OnBnClickedStageButton)
	ON_BN_CLICKED(IDC_STAGE_BUTTON2, &CDoorMenuDialog::OnBnClickedStageButton)
	ON_BN_CLICKED(IDC_STAGE_BUTTON3, &CDoorMenuDialog::OnBnClickedStageButton)
	ON_BN_CLICKED(IDC_STAGE_BUTTON4, &CDoorMenuDialog::OnBnClickedStageButton)
	ON_BN_CLICKED(IDC_STAGE_BUTTON5, &CDoorMenuDialog::OnBnClickedStageButton)
	ON_BN_CLICKED(IDC_STAGE_BUTTON6, &CDoorMenuDialog::OnBnClickedStageButton)
END_MESSAGE_MAP()


// CDoorMenuDialog 메시지 처리기


void CDoorMenuDialog::OnBnClickedStageButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CWnd* pWnd = GetFocus(); // 클릭된 컨트롤 가져오기
    int stageNumber = 0;
    if (pWnd) {
        UINT nID = pWnd->GetDlgCtrlID(); // 컨트롤 ID 가져오기
        switch (nID)
        {
        case IDC_STAGE_BUTTON1:
            stageNumber = 1;
            break;
        case IDC_STAGE_BUTTON2:
            stageNumber = 2;
            break;
        case IDC_STAGE_BUTTON3:
            stageNumber = 3;
            break;
        case IDC_STAGE_BUTTON4:
            stageNumber = 4;
            break;
        case IDC_STAGE_BUTTON5:
            stageNumber = 5;
            break;
        case IDC_STAGE_BUTTON6:
            stageNumber = 6;
            break;
        default:
            return; // 알 수 없는 버튼
        }
    
    }

    // 각 스테이지 대화 상자 실행
    CString msg;
    msg.Format(_T("Stage %d 시작!"), stageNumber);
    AfxMessageBox(msg);

    // 각 스테이지에 맞는 게임 시작
    CArrowKeyGameDialog arrowKeyGameDialog(stageNumber); // 생성자에 스테이지 전달
    arrowKeyGameDialog.DoModal();
}
