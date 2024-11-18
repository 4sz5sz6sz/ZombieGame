#pragma once
#include "afxdialogex.h"


// CManufacture 대화 상자

class CManufacture : public CDialogEx
{
	DECLARE_DYNAMIC(CManufacture)

public:
	CManufacture(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CManufacture();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
