
// ZombieGameDlg.h: 헤더 파일
//

#pragma once
#include "CZombieGameSaveDlg.h"
#include "CZombieGameChestDlg.h"


// CZombieGameDlg 대화 상자
class CZombieGameDlg : public CDialogEx
{
// 생성입니다.
public:
	CZombieGameDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	
	CZombieGameSaveDlg sdlg;
	CZombieGameChestDlg cdlg;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZOMBIEGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSafe();
	
	bool m_bUnitViewed; // 금고 버튼 bool 변수
	CZombieGameSaveDlg m_dlgZGSave; // 금고 관련된 무언가 뭐였지?
	afx_msg void OnClickedButtonSafe(); // 금고 버튼 클릭 함수

	bool m_bChestButton; // 나무 상자 버튼 bool 변수
	CZombieGameChestDlg m_dlgZGChest;
	afx_msg void OnClickedButtonChest();// 나무 상자 버튼 클릭 함수

	afx_msg void OnBnClickedButtonVaccineManfacturingMachine();
	afx_msg void OnBnClickedButtonDoor();
	CListBox m_listInven;
	CString m_strInven[10];
	afx_msg void OnBnClickedButtonDrawer();
	afx_msg void OnBnClickedButtonPhone();
	afx_msg void OnBnClickedButton1();
};
