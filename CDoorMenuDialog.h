#pragma once
#include "afxdialogex.h"
#include "ArrowKeyGameDlg.h"


// CDoorMenuDialog 대화 상자

class CDoorMenuDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDoorMenuDialog)

public:
	CDoorMenuDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDoorMenuDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOOR_MENU_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStageButton();
};
