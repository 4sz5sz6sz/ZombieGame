#pragma once
#include "afxdialogex.h"


// CSurabDlg 대화 상자

class CSurabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSurabDlg)

public:
	CSurabDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSurabDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SURAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listSurabInven;
	CListBox m_listSurab;
	CString m_strSurabInven[10];
	virtual BOOL OnInitDialog();
};
