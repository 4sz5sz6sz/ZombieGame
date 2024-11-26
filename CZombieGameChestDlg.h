#pragma once
#include "afxdialogex.h"


// CZombieGameChestDlg 대화 상자

class CZombieGameChestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZombieGameChestDlg)

public:
	CZombieGameChestDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CZombieGameChestDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHEST };
#endif
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonClockReverse();
	afx_msg void OnClickedButtonCheck();
	afx_msg void OnClickedButtonUp();
	afx_msg void OnClickedButtonDown();
	afx_msg void OnClickedButtonRight();
	afx_msg void OnClickedButtonLeft();
	CListBox m_listAnswer;
	afx_msg void OnClickedButtonClear();
	CStatic m_picClock;
	CListBox m_listChestInside;

	virtual BOOL OnInitDialog();
	CString m_strInven[10];
	CListBox m_listSaveInven;
	afx_msg void OnClickedButtonItmeMove2();
	afx_msg void OnBnClickedCancel();
	CStatic m_picGetOrange;
};
