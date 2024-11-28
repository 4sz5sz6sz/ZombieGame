#pragma once
#include "afxdialogex.h"
#include "CYellowMaterial.h"
#include "CPlayer.h"
#include "Zombie.h"
#include "CSafeZone.h"
#include "CEntity.h"
#include <vector>
#include <afxcmn.h>  // 프로그레스 바와 관련된 헤더

//const int SCALE_FACTOR = 20;	//스케일링 상수. 전부 20배 한다는 뜻.


// ArrowKeyGameDlg 대화 상자



class CArrowKeyGameDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CArrowKeyGameDialog)

public:
	CArrowKeyGameDialog(int stageNumber, bool isGodModeEnabled=false, bool isSpeedBoostEnabled=false, bool isZombieFlipEnabled=false, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CArrowKeyGameDialog();
	//virtual BOOL PreTranslateMessage(MSG* pMsg) override;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARROW_KEY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	//double playerX;	//네모의 위치
	//double playerY;	//네모의 위치
	int squareSize;	//네모의 크기
	afx_msg void OnPaint();
	void DrawMessageLog(CPaintDC& dc);		//알림 메시지 출력
	void DrawCooldownOnSafeZone(CPaintDC& dc);	//최근에 생성된 안전지대 위에 쿨타임 출력
	void DrawPlayerHealthText(CPaintDC& dc) const;	//Player 옆, 체력바 업데이트
	void UpdateHealthBar(CPaintDC& dc) const;	//11시 방향, 체력바 업데이트
	void UpdateMovement();	// OnTimer(), 위치 업데이트
	void UpdateCooldown();	// 쿨타임 업데이트
	void UpdateSafeZones(); // 안전지대 업데이트
	void MovePlayer(double dx, double dy);

	//방향키 눌림 여부 저장
	bool moveUp;
	bool moveDown;
	bool moveLeft;
	bool moveRight;

	CPoint m_ptLocation;
	//CRect playerRect; // 네모의 위치
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg UINT OnGetDlgCode(); //방향키 입력을 받아들일 수 있도록 함.

	std::vector<CZombie> zombies; // 좀비들을 저장하는 벡터
	std::vector<CSafeZone> safeZones;	//안전지대 저장하는 벡터
	CPlayer player;                  //Player 객체
	double moveSpeed;				//Player의 스피드

	CPoint m_ptClientSize;
	CRect safeZone;
	//bool IsInSafeZone(double x, double y);	//안전지대 검사하는 함수
	

	std::chrono::steady_clock::time_point playerEnterTime; //플레이어가 안전지대에 들어간 시각
	bool playerInSafeZone; //플레이어가 안전지대에 있는지 저장
	const double K_SECONDS = 3.0; //안전지대에 머무는 시간 기준 (초 단위)
	int activeSafeZoneCount; //활성화된 안전지대의 수 (파괴되지 않은 안전지대 수)
	void CheckPlayerOnSafeZones(); //OnTimer() 내부 존재, 플레이어가 안전지대를 밟고 있는지 검사하는 함수

	bool isCooldownActive = false; // 쿨타임 활성화 여부
	

	CProgressCtrl cooldownProgressBar; // 쿨타임 프로그레스 바
	double remainingCooldownTime; // 남은 쿨타임 시간 (초 단위)

	std::vector<CYellowMaterial> yellowMaterials; // 
	//노랑 재료 벡터
	int collectedYellowMaterialCount; // 획득한 노랑 재료 갯수
	void GenerateYellowMaterials(int count); // 노란재료 생성
	void GenerateYellowMaterialAt(double x, double y); // 지정된 좌표에 노란재료 생성

	void CheckPlayerMaterialCollision();  // OnTimer(), 플레이어-재료 충돌 확인, 내부에서 material.CheckCollisionWithPlayer(x,y)가 n번 호출됨.
	void UpdatePlayerHP();// Player-Zombie 충돌에 따른 체력 업데이트
	bool isGameOver; // 게임오버 여부 저장. UpdatePlayerHP() 무한루프 방지.
	// 각 스테이지 별 환경 세팅 (ex. 좀비, 플레이어, 이동속도)
	void InitializeStage(int stageNumber);

	// 현재 스테이지의 목표 재료 수
	int requiredMaterialCount;
	// 재료 수 출력
	void DrawMaterialCount(CDC& dc) const;
	virtual BOOL OnInitDialog();
	
	int currentStage; // 현재 스테이지
	int stageWidth;		// 창 크기 너비
	int stageHeight;	// 창 크기 높이
	
	
	// 안전지대 생성 (4단계)
	std::vector<CSafeZone> GenerateSafeZones(int stageWidth, int stageHeight, int safeZoneHeight=10, int safeZoneSpacing=100, int safeZoneWidth=100, int columnSpacing=100, int columns=9);
	
	bool isGodModeEnabled; // 치트: 무적 모드
	bool isSpeedBoostEnabled; // 치트: 이동 속도 증가
	bool isZombieFlipEnabled; // 치트: 좀비 이동 방향 반전 상태
};
