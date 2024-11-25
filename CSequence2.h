#pragma once
#include "afxdialogex.h"


// CSequence2 대화 상자

class CSequence2 : public CDialogEx
{
	DECLARE_DYNAMIC(CSequence2)

public:
	CSequence2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSequence2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEQUENCE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnRadioBlue();
	afx_msg void OnRadioOrange();
	afx_msg void OnRadioRed();
	afx_msg void OnRadioYellow();
	void CHECK();
	CListBox m_listBox22;
	CButton m_picture_control22;
	CComboBox m_cbListItem22;
	void UpdateComboBox22();
	afx_msg void OnBnClickedButton1();
};

