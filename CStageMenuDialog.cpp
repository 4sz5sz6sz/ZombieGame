// CStageMenuDialog.cpp: 구현 파일
//

#include "pch.h"
#include "ZombieGame.h"
#include "afxdialogex.h"
#include "CStageMenuDialog.h"


// CStageMenuDialog 대화 상자

IMPLEMENT_DYNAMIC(CStageMenuDialog, CDialogEx)

CStageMenuDialog::CStageMenuDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STAGE_MENU_DIALOG, pParent)
{
    selectedStage = 0;
}

CStageMenuDialog::~CStageMenuDialog()
{
}

void CStageMenuDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStageMenuDialog, CDialogEx)
    ON_BN_CLICKED(IDC_NEW_STAGE_BUTTON1, &CStageMenuDialog::OnBnClickedStageButton)
    ON_BN_CLICKED(IDC_NEW_STAGE_BUTTON2, &CStageMenuDialog::OnBnClickedStageButton)
    ON_BN_CLICKED(IDC_NEW_STAGE_BUTTON3, &CStageMenuDialog::OnBnClickedStageButton)
    ON_BN_CLICKED(IDC_NEW_STAGE_BUTTON4, &CStageMenuDialog::OnBnClickedStageButton)
    ON_BN_CLICKED(IDC_NEW_STAGE_BUTTON5, &CStageMenuDialog::OnBnClickedStageButton)
    ON_BN_CLICKED(IDC_NEW_STAGE_BUTTON6, &CStageMenuDialog::OnBnClickedStageButton)
    ON_BN_CLICKED(IDC_NEW_START_BUTTON, &CStageMenuDialog::OnBnClickedStartButton)
END_MESSAGE_MAP()


// CStageMenuDialog 메시지 처리기

void CStageMenuDialog::OnBnClickedStageButton() {
    // 스테이지 선택 로직
    CWnd* pWnd = GetFocus(); // 클릭된 컨트롤 가져오기
    if (pWnd) {
        UINT nID = pWnd->GetDlgCtrlID(); // 컨트롤 ID 가져오기
        switch (nID)
        {
        case IDC_NEW_STAGE_BUTTON1:
            selectedStage = 1;
            break;
        case IDC_NEW_STAGE_BUTTON2:
            selectedStage = 2;
            break;
        case IDC_NEW_STAGE_BUTTON3:
            selectedStage = 3;
            break;
        case IDC_NEW_STAGE_BUTTON4:
            selectedStage = 4;
            break;
        case IDC_NEW_STAGE_BUTTON5:
            selectedStage = 5;
            break;
        case IDC_NEW_STAGE_BUTTON6:
            selectedStage = 6;
            break;
        default:
            return; // 알 수 없는 버튼
        }

    }
    /*CString msg;
    msg.Format(_T("Stage %d 시작!"), selectedStage);
    AfxMessageBox(msg);*/
    UpdatePreview(); // 선택된 스테이지에 맞는 미리보기 표시
    UpdateButtonStates(); //시작 버튼 상태 갱신
    // 시작 버튼 활성화
    /*CButton* startButton = (CButton*)GetDlgItem(IDC_NEW_START_BUTTON);
    startButton->EnableWindow(TRUE);*/
}

void CStageMenuDialog::UpdatePreview() {
    // 선택된 스테이지에 따른 미리보기 내용 변경
    CStatic* preview = (CStatic*)GetDlgItem(IDC_NEW_STAGE_PREVIEW);
    CString previewText;    
    previewText.Format(_T("스테이지 %d 미리보기"), selectedStage);
    //OutputDebugString(_T("미리보기 텍스트 설정 성공\n"));
    preview->SetWindowText(previewText);
}

void CStageMenuDialog::OnBnClickedStartButton() {
    if (selectedStage > 0) {
        CString msg;
        msg.Format(_T("스테이지 %d 시작!"), selectedStage);
        AfxMessageBox(msg);
        // 스테이지 시작 코드 작성
        CArrowKeyGameDialog arrowKeyGameDialog(selectedStage); //생성자에 스테이지 전달
        arrowKeyGameDialog.DoModal();
        /*EndDialog(IDOK);*/
    }
}

void CStageMenuDialog::UpdateButtonStates()
{
    // TODO: 여기에 구현 코드 추가.
    CButton* pStartButton = (CButton*)GetDlgItem(IDC_NEW_START_BUTTON);
    pStartButton->EnableWindow(selectedStage >= 1 && stageCleared[selectedStage]);
    // 밑에 3줄??
    //
    //
    //


}
