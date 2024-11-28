#pragma once
#include "afxdialogex.h"
#include "ArrowKeyGameDlg.h"

// CStageMenuDialog 대화 상자

class CStageMenuDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CStageMenuDialog)

public:
	CStageMenuDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CStageMenuDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STAGE_MENU_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStageButton();
	afx_msg void OnBnClickedStartButton();
	void UpdatePreview();
	
	int selectedStage; // 선택한 스테이지 번호
	void UpdateButtonStates();

	bool isGodModeEnabled = false; // 치트: 무적 모드
	bool isSpeedBoostEnabled = false; // 치트: 이동 속도 증가
	afx_msg void OnBnClickedCheatCheckButton();// 치트키 확인 버튼 이벤트
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton2();
};
