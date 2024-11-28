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
	// 각 스테이지 클리어 여부, 6단계까지만 저장.
	//bool stageCleared[8];	
	void UpdateButtonStates();
	afx_msg void OnBnClickedButton2();
};
