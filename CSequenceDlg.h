#pragma once
#include "afxdialogex.h"


// CSequenceDlg 대화 상자

class CSequenceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSequenceDlg)

public:
	CSequenceDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSequenceDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listBox;
	CComboBox m_cbListItem;
	void UpdateComboBox();
	afx_msg void OnRadioRed();
	afx_msg void OnRadioYellow();
	afx_msg void OnRadioBlue();
	afx_msg void OnRadioOrange();
	void Check();
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnBnClickedView1();
	CButton m_picture_control1;
};
