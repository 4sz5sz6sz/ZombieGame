#pragma once
#include "afxdialogex.h"


// CMachineDlg 대화 상자

class CMachineDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMachineDlg)

public:
	CMachineDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMachineDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MACHINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void PrintPicture();
	void PrintPicture_Good();
	CStatic m_picture_control_End;
	CListBox m_listMachineInven;
	CListBox m_listVaccineMachine;
	void EndCheck();
	afx_msg void OnBnClickedCancel();
	CString m_strMachineInven[10];
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonMachineMove();
	afx_msg void OnBnClickedButtonMake();
};
