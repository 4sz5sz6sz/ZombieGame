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
    ON_BN_CLICKED(IDC_CHEAT_CHECK_BUTTON, &CStageMenuDialog::OnBnClickedCheatCheckButton)
    ON_WM_PAINT()
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
            isDarknessEnabled = false;
            break;
        case IDC_NEW_STAGE_BUTTON2:
            selectedStage = 2;
            isDarknessEnabled = false;
            break;
        case IDC_NEW_STAGE_BUTTON3:
            selectedStage = 3;
            isDarknessEnabled = false;
            break;
        case IDC_NEW_STAGE_BUTTON4:
            selectedStage = 4;
            isDarknessEnabled = false;
            break;
        case IDC_NEW_STAGE_BUTTON5:
            selectedStage = 5;
            isDarknessEnabled = false;
            break;
        case IDC_NEW_STAGE_BUTTON6:
            selectedStage = 6;
            isDarknessEnabled = true;   //어둠 추가
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
        CArrowKeyGameDialog arrowKeyGameDialog(selectedStage,isGodModeEnabled, isSpeedBoostEnabled, isZombieFlipEnabled, isDarknessEnabled); //생성자에 스테이지 전달
        arrowKeyGameDialog.DoModal();
        /*EndDialog(IDOK);*/
    }
}

void CStageMenuDialog::UpdateButtonStates()
{
    // TODO: 여기에 구현 코드 추가.
    CButton* pStartButton = (CButton*)GetDlgItem(IDC_NEW_START_BUTTON);
    pStartButton->EnableWindow(selectedStage >= 1 && stageCleared[selectedStage]);
}

// 치트키 확인 버튼 이벤트
void CStageMenuDialog::OnBnClickedCheatCheckButton() 
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    // Edit Control에서 입력된 텍스트 가져오기
    CEdit* cheatEdit = (CEdit*)GetDlgItem(IDC_CHEAT_EDIT);

    CString cheatText;
    cheatEdit->GetWindowText(cheatText); // 사용자가 입력한 치트 텍스트

    if (cheatText.IsEmpty()) {
        AfxMessageBox(_T("치트키를 입력해주세요!"));
        return;
    }

    // 치트키 검사
    if (cheatText.CompareNoCase(_T("GODMODE")) == 0) {
        isGodModeEnabled = true; // 무적 모드 활성화
        AfxMessageBox(_T("치트: 무적 모드 활성화!"));
    }
    else if (cheatText.CompareNoCase(_T("SPEEDBOOST")) == 0) {
        isSpeedBoostEnabled = true; // 이동 속도 증가
        AfxMessageBox(_T("치트: 이동 속도 증가!"));
    }
    else if (cheatText.CompareNoCase(_T("ZOMBIEFLIP")) == 0) {
        isZombieFlipEnabled = !isZombieFlipEnabled; // 좀비 이동 방향 반전 토글
        if (isZombieFlipEnabled) {
            AfxMessageBox(_T("치트: 좀비 이동 방향 반전!"));
        }
        else {
            AfxMessageBox(_T("치트: 좀비 이동 방향 정상화!"));
        }
    }
    else {
        AfxMessageBox(_T("유효하지 않은 치트키입니다."));
    }

    // 입력 초기화
    cheatEdit->SetWindowText(_T(""));
    Invalidate();
}



void CStageMenuDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
    // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
    if (isGodModeEnabled) {
        CString cheatStatus = _T("무적 모드 활성화");
        CRect rect(10, 50, 200, 70); // 위치 조정
        dc.SetBkMode(TRANSPARENT);
        dc.SetTextColor(RGB(255, 0, 0));
        dc.DrawText(cheatStatus, &rect, DT_LEFT | DT_SINGLELINE);
    }

    if (isSpeedBoostEnabled) {
        CString cheatStatus = _T("이동 속도 증가");
        CRect rect(10, 70, 200, 90); // 위치 조정
        dc.SetBkMode(TRANSPARENT);
        dc.SetTextColor(RGB(0, 0, 255));
        dc.DrawText(cheatStatus, &rect, DT_LEFT | DT_SINGLELINE);
    }

    if (isZombieFlipEnabled) {
        CString cheatStatus = _T("좀비 이동 방향 반전 활성화");
        CRect rect(10, 90, 300, 110);
        dc.SetBkMode(TRANSPARENT);
        dc.SetTextColor(RGB(128, 0, 128)); // 보라색
        dc.DrawText(cheatStatus, &rect, DT_LEFT | DT_SINGLELINE);
    }
}