#pragma once
#include "afxdialogex.h"


// CZombieGameSaveDlg 대화 상자

class CZombieGameSaveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZombieGameSaveDlg)

public:
	CZombieGameSaveDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CZombieGameSaveDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SAFE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPicCalender();
	afx_msg void OnStnClickedPicCalender();
	CStatic m_PicCalender;
	afx_msg void OnClickedButtonCalender();
	CComboBox m_cbCombo1;
	CComboBox m_cbCombo2;
	CComboBox m_cbCombo3;
	CComboBox m_cbCombo4;
	afx_msg void OnClickedButtonOpen();
//	CListBox m_listSafeInside;
	CListBox m_listSaveInside;
};
