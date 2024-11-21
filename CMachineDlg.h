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
};
