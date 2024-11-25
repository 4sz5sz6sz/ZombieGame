// ArrowKeyGameDlg.cpp: 구현 파일
//
//OutputDebugString(_T("테스트내용\n"));

#include "pch.h"
#include "ZombieGame.h"
#include "afxdialogex.h"
#include "ArrowKeyGameDlg.h"
#include "ZombieMovement.h"
#include "CYellowMaterial.h"
#include "CMessageManager.h"
#include <algorithm>	//max 함수
#include <chrono>	//시간 함수


// ArrowKeyGameDlg 대화 상자

IMPLEMENT_DYNAMIC(CArrowKeyGameDialog, CDialogEx)

CArrowKeyGameDialog::CArrowKeyGameDialog(int stageNumber, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARROW_KEY_DIALOG, pParent),
	player(6.5, 6.1),
	remainingCooldownTime(0),
	isCooldownActive(false),
	playerInSafeZone(false),
	collectedYellowMaterialCount(0),
	activeSafeZoneCount(0),
	currentStage(stageNumber)
{
	isGameOver = false;
	squareSize = 20;         // 네모의 크기
	m_ptLocation = (0, 0);
	moveUp = false;
	moveDown = false;
	moveLeft = false;
	moveRight = false;
	moveSpeed = 0.4;	//0.4 추천, 60fps이면 0.2
	
	//어차피 OnInitDialog()에서 변경 될 예정. 근데 warning 없애려고 초기화함.
	requiredMaterialCount = 0;
	stageHeight = 0;
	stageWidth = 0;
	//UINT_PTR m_nTimerID;

}

CArrowKeyGameDialog::~CArrowKeyGameDialog()
{
}

void CArrowKeyGameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CArrowKeyGameDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_BN_CLICKED(IDOK, &CArrowKeyGameDialog::OnBnClickedOk)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_GETDLGCODE()
END_MESSAGE_MAP()


// ArrowKeyGameDlg 메시지 처리기


void CArrowKeyGameDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	for (auto& material : yellowMaterials) {
		if (!material.collected) {
			dc.FillSolidRect(
				static_cast<int>(material.x * SCALE_FACTOR),
				static_cast<int>(material.y * SCALE_FACTOR),
				SCALE_FACTOR,
				SCALE_FACTOR,
				RGB(255, 255, 0)); //노란색 네모 그리기
		}
	}
	
	for (auto& zone : safeZones) {
		if (zone.isDestroyed) continue;
		int alpha = (int)(255 * zone.alpha / 255);
		alpha = max(20, alpha);	//하한 20
		CBrush safeZoneBrush(RGB(0, alpha, 0)); //연한 초록색.
		dc.FillRect(zone.rect, &safeZoneBrush);
		
	}

	//파란색 네모 그리기
	dc.FillSolidRect(
		static_cast<int>(player.x * SCALE_FACTOR),
		static_cast<int>(player.y * SCALE_FACTOR),
		SCALE_FACTOR, 
		SCALE_FACTOR, 
		RGB(0, 0, 255)
	); //파란색 네모

	for (auto& zombie : zombies) {
		dc.FillSolidRect(static_cast<int>(zombie.x * SCALE_FACTOR),
			static_cast<int>(zombie.y * SCALE_FACTOR),
			SCALE_FACTOR, 
			SCALE_FACTOR, 
			RGB(255, 0, 0)	//빨간색 네모
		);
	}


	UpdateHealthBar(dc);		//11시 방향, 체력바 업데이트
	DrawPlayerHealthText(dc);	//Player 옆, 체력 업데이트
	DrawMaterialCount(dc); 	// 재료 카운트 출력
	DrawCooldownOnSafeZone(dc);	//최근에 생성된 안전지대 위에 쿨타임 출력
	DrawMessageLog(dc);	//알림 메시지 출력

	//DrawHUD(dc);
}

//알림 메시지 출력
void CArrowKeyGameDialog::DrawMessageLog(CPaintDC& dc)
{
	// 메시지 출력 위치
	int startX = 10;
	int startY = 480; // 화면 아래쪽
	int lineHeight = 20;

	auto messages = CMessageManager::GetInstance().GetMessages();
	for (size_t i = 0; i < messages.size(); ++i) {
		CString message = messages[i];
		CRect messageRect(startX, startY + i * lineHeight, startX + 300, startY + (i + 1) * lineHeight);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(0, 0, 0)); // 흰색 텍스트
		dc.DrawText(message, &messageRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}
}

//최근에 생성된 안전지대 위에 쿨타임 출력
void CArrowKeyGameDialog::DrawCooldownOnSafeZone(CPaintDC& dc)
{
	if (!safeZones.empty()) {
		CSafeZone latestZone = safeZones.back();  //가장 최근에 생성된 안전지대

		//남은 쿨타임 계산
		remainingCooldownTime = player.GetRemainingCooldownTime();
		if (remainingCooldownTime > 0) {
			CString timeText;
			dc.SetTextColor(RGB(0, 0, 0)); //검은색 텍스트
			timeText.Format(_T("%.1f 초"), remainingCooldownTime);

			CRect textRect = latestZone.rect;
			textRect.top -= 20;  //텍스트 위치를 안전지대 위로 조정
			dc.SetBkMode(TRANSPARENT);
			dc.DrawText(timeText, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}

void CArrowKeyGameDialog::DrawPlayerHealthText(CPaintDC& dc) const
{
	CString hpText;	//체력 문자열 정의
	hpText.Format(_T("HP: %.0f%%"), player.HP);
	CRect hpRect(
		static_cast<int>(player.x * SCALE_FACTOR + SCALE_FACTOR + 10), // 플레이어 오른쪽에 약간 띄워 표시
		static_cast<int>(player.y * SCALE_FACTOR),
		static_cast<int>(player.x * SCALE_FACTOR + SCALE_FACTOR + 80),
		static_cast<int>(player.y * SCALE_FACTOR + 20)
	);
	dc.SetBkMode(TRANSPARENT);	//투명 배경
	//dc.SetTextColor(RGB(255, 0, 0)); //빨간색 텍스트
	dc.SetTextColor(RGB(255, 165, 0)); //주황색 텍스트
	dc.DrawText(hpText, &hpRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

void CArrowKeyGameDialog::UpdateHealthBar(CPaintDC& dc) const
{
	//체력바 그리기
	int healthBarWidth = 200; // 체력바의 총 길이
	int healthBarHeight = 20; // 체력바의 높이
	int healthBarX = 10;      // 체력바의 X 좌표 (화면의 왼쪽)
	int healthBarY = 40;      // 체력바의 Y 좌표 (화면의 위쪽)

	//체력에 비례한 체력바 길이 계산
	int currentHealthWidth = (int)(player.HP / 100.0 * healthBarWidth);

	//체력바 배경 (회색)
	CBrush bgBrush(RGB(200, 200, 200)); // 배경 색
	dc.FillRect(CRect(healthBarX, healthBarY, healthBarX + healthBarWidth, healthBarY + healthBarHeight), &bgBrush);

	//체력바 (빨간색)
	CBrush healthBrush(RGB(255, 0, 0)); // 체력 색
	dc.FillRect(CRect(healthBarX, healthBarY, healthBarX + currentHealthWidth, healthBarY + healthBarHeight), &healthBrush);

	//체력 값 텍스트 추가
	CString hpText;	//체력 문자열 정의
	hpText.Format(_T("HP: %.0f%%"), player.HP);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 0, 0)); // 텍스트 색상: 검정색
	dc.DrawText(hpText, CRect(healthBarX, healthBarY, healthBarX + healthBarWidth, healthBarY + healthBarHeight), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}


void CArrowKeyGameDialog::UpdateMovement()
{
	// TODO: 여기에 구현 코드 추가.
	double dx = 0, dy = 0;
	if (moveUp) {
		dy -= moveSpeed;
		
	}
	if (moveDown) {
		dy += moveSpeed;
		//CString debugMsg;
		//debugMsg.Format(L"dy: %d", dy);  // 키 값 확인용 메시지
		//AfxMessageBox(debugMsg);
	}
	if (moveLeft) {
		dx -= moveSpeed;
	}
	if (moveRight) {
		dx += moveSpeed;
	}
	
	//대각선 이동할 때 속도가 루트2(배) 만큼 빨라지는 현상 보정.
	if (dx && dy) {	//대각선 이동일 때 속도 보정. 각 성분이 2로 보정됨. 체감 속도는 2루트2,
		//double length = sqrt(dx * dx + dy * dy);
		//double scalingFactor = (double)moveSpeed / length;
		//double scalingFactor = 1/sqrt(2);
		dx = dx / sqrt(2);
		dy = dy / sqrt(2);
	}

	//// dx, dy 값을 출력
	/*CString debugMsg;
	debugMsg.Format(_T("dx: %f, dy: %f\n"), dx, dy);
	OutputDebugString(debugMsg);*/

	if (dx || dy) MovePlayer(dx, dy);

	Invalidate();	//화면 업데이트, 네모 표시
}



void CArrowKeyGameDialog::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)					// 가상키 코드 값에 대해 
	{
	case VK_LEFT:					// 왼쪽 화살표 키를 누를 때
		moveLeft = false;
		break;
	case VK_RIGHT:				// 오른쪽 화살표 키를 누를 때
		moveRight = false;
		break;
	case VK_UP:					// 위쪽 화살표 키를 누를 때
		moveUp = false;
		break;
	case VK_DOWN:				// 아래쪽 화살표 키를 누를 때
		moveDown = false;
		break;
	case VK_PRIOR:					// Pg up 키를 누를 때
		//m_ptLocation.y -= 50;			// 위쪽으로 50픽셀 이동
		//moveLeft = false;
		break;
	case VK_NEXT:					// Pg dn 키를 누를 때
		//m_ptLocation.y += 50;			// 아래쪽으로 50픽셀 이동
		break;
	case VK_HOME:					// Home 키를 누를 때
		//m_ptLocation = CPoint(0, 0);		// 처음 위치로 이동
		break;
	}
	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CArrowKeyGameDialog::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CString debugMsg;
	//debugMsg.Format(L"Key Pressed: %d", nChar);  // 키 값 확인용 메시지
	//AfxMessageBox(debugMsg);


	switch (nChar)					// 가상키 코드 값에 대해 
	{
	case VK_LEFT:					// 왼쪽 화살표 키를 누를 때
		moveLeft = true;
		break;
	case VK_RIGHT:				// 오른쪽 화살표 키를 누를 때
		moveRight = true;
		break;
	case VK_UP:					// 위쪽 화살표 키를 누를 때
		moveUp = true;
		break;
	case VK_DOWN:				// 아래쪽 화살표 키를 누를 때
		moveDown = true;
		break;
	case VK_PRIOR:					// Pg up 키를 누를 때
		//m_ptLocation.y -= 50;			// 위쪽으로 50픽셀 이동
		//moveLeft = true;
		break;
	case VK_NEXT:					// Pg dn 키를 누를 때
		//m_ptLocation.y += 50;			// 아래쪽으로 50픽셀 이동
		break;
	case VK_HOME:					// Home 키를 누를 때
		//m_ptLocation = CPoint(0, 0);		// 처음 위치로 이동
		break;
	}
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000) { // Ctrl 키를 누를 때
		/*OutputDebugString(_T("Ctrl 키가 눌렸습니다. 안전지대를 설치합니다.\n"));*/
		player.TryToPlaceSafeZone(this, zombies, safeZones);	//안전지대 설치
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CArrowKeyGameDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CDialogEx::OnOK();
}


int CArrowKeyGameDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	


	CRect progressRect(10, 10, 200, 30);  // 프로그레스 바의 위치와 크기 설정
	cooldownProgressBar.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTH, progressRect, this, 1);  // WS_TABSTOP 제거
	cooldownProgressBar.EnableWindow(FALSE);  // 비활성화
	cooldownProgressBar.SetRange(0, 100);  // 범위 설정: 0 ~ 100%
	cooldownProgressBar.SetPos(0);  // 초기값 설정
	//cooldownProgressBar.SendMessage(PBM_SETBARCOLOR, 0, RGB(255, 0, 0)); // 빨간색 설정했는데... 안 먹힘..

	
	SetTimer(1, 30, NULL);	//30ms에 한번 업데이트.//16으로 설정하면 60fps

	return 0;
}


void CArrowKeyGameDialog::MovePlayer(double dx, double dy)
{
	// TODO: 여기에 구현 코드 추가.
	//playerRect.OffsetRect(dx, dy);	//네모위치이동
	player.x += dx; // playerX 좌표 갱신
	player.y += dy; // playerY 좌표 갱신
	Invalidate();	//OnPaint() 호출
}



void CArrowKeyGameDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1)  // 타이머 ID가 1인 경우, UpdateMovement() 호출
	{
		for (auto& zombie : zombies) {
			zombie.MoveTowards(player.x, player.y,zombies,safeZones);
		}
		UpdateMovement();	//위치 갱신
		UpdatePlayerHP(); // 체력 갱신
		UpdateCooldown();	//???? 쿨타임 갱신.
		CheckPlayerMaterialCollision(); // 플레이어와 재료 충돌 확인
		CheckPlayerOnSafeZones(); // 플레이어가 안전지대를 밟고 있는지 확인
		Invalidate();  //화면 갱신
	}
	CDialogEx::OnTimer(nIDEvent);
}


UINT CArrowKeyGameDialog::OnGetDlgCode()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CDialogEx::OnGetDlgCode();
	//방향키 입력을 받아들일 수 있도록 함.
	//이거 없으면 방향키 입력 못 받음.
	return DLGC_WANTARROWS;	
}


void CArrowKeyGameDialog::UpdateCooldown()
{
	if (isCooldownActive)
	{
		/*auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed = now - lastSafeZoneTime;
		remainingCooldownTime = max(3.0 - elapsed.count(), 0.0);*/
		//std::max 쓰면 에러발생.
		remainingCooldownTime = player.GetRemainingCooldownTime();

		// 프로그레스 바 업데이트, 0~100사이의 값을 가짐.
		int progress = (int)((remainingCooldownTime) / 3.0 * 100.0);
		//int progress = (int)((3.0-remainingCooldownTime) / 3.0 * 100.0);



		cooldownProgressBar.SetPos(progress);

		if (remainingCooldownTime <= 0.0)
		{
			isCooldownActive = false;
			remainingCooldownTime = 0.0;
			cooldownProgressBar.SetPos(0);  // 쿨타임이 끝나면 프로그레스 바 초기화
		}

		cooldownProgressBar.RedrawWindow();
	}
}

// 안전지대 업데이트
void CArrowKeyGameDialog::UpdateSafeZones()
{
	// TODO: 여기에 구현 코드 추가.
	//아직 미정..
}


// 플레이어가 안전지대에 있는지 검사하는 함수, 
void CArrowKeyGameDialog::CheckPlayerOnSafeZones()
{
	// TODO: 여기에 구현 코드 추가.
	bool onAnySafeZone = false;

	for (auto& zone : safeZones) {
		if (!zone.isDestroyed && player.CheckCollision(player.x,player.y,zone.rect)){	//만약 안전지대를 밟고 있다면
			if (!playerInSafeZone) { 
				//플레이어가 안전지대에 처음 들어감
				playerInSafeZone = true;
				playerEnterTime = std::chrono::steady_clock::now();
			}
			else {
				//플레이어가 계속 안전지대에 있음
				auto now = std::chrono::steady_clock::now();
				std::chrono::duration<double> elapsed = now - playerEnterTime;

				//투명도 업데이트
				zone.alpha = (int)((1.0 - elapsed.count() / K_SECONDS) * 255);
				zone.alpha = max(zone.alpha, 20); //하한 20

				//k초 이상 머물렀으면 안전지대 파괴
				if (elapsed.count() >= K_SECONDS) {
					OutputDebugString(_T("안전지대가 파괴되었습니다.\n"));
					CMessageManager::GetInstance().AddMessage(_T("안전지대가 파괴되었습니다."));
					zone.isDestroyed = true;
					zone.rect = CRect(-1000, -1000, -900, -900); // 안전지대를 화면 밖으로 보냄.
					activeSafeZoneCount--;
					playerInSafeZone = false; // 플레이어가 안전지대를 벗어난 것으로 처리
				}
			}
			onAnySafeZone = true;
			break;
		}
	}

	if (!onAnySafeZone) {
		playerInSafeZone = false; //플레이어가 안전지대를 벗어났음
		//모든 안전지대의 투명도 복구
		for (auto& zone : safeZones) {
			if (zone.isDestroyed) continue;
			zone.alpha = 255;
		}
	}
}



// 노란재료 생성
void CArrowKeyGameDialog::GenerateYellowMaterials(int count)
{
	// TODO: 여기에 구현 코드 추가.
	srand((unsigned)time(NULL)); // 랜덤 시드 설정

	//CRect clientRect;
	//GetClientRect(&clientRect); // 현재 창의 크기를 얻음
	/*int maxX = clientRect.Width() / 7.6;
	int maxY = clientRect.Height() / 7.6;*/
	int maxX = stageWidth / 23;
	int maxY = stageHeight / 23;

	CString debugMsg;
	debugMsg.Format(_T("maxX: %d, maxY: %d\n"), maxX, maxY);
	OutputDebugString(debugMsg);

	for (int i = 0; i < count; ++i) {
		//double x = (rand() % 40 + 5) * 0.5;
		//double y = (rand() % 30 + 5) * 0.5;
		double x, y;
		//double x = 37;
		//double y = 26;
		//double x = maxX;
		//double y = maxY;
		int cnt = 0;
		while (++cnt) {
			x = (rand() % (maxX * 20)) * 0.05;
			y = (rand() % (maxY * 20)) * 0.05;
			//100번 넘게 재실행 된다면, 그냥 인정하고 생성시키기
			if (cnt>100) break;

			//스폰 지점이 거리 10 이내에 가까이 있다면,리롤
			if (player.CheckCollision(x, y, player, 10)) continue;
			
			//스폰 지점이 안전지대 내부에 있다면, 리롤.
			bool inSafeZone = false;
			for (auto& zone : safeZones) {
				//정적 메소드 처럼 그냥 player의 멤버함수를 호출함. 
				//실제로는 노란재료-안전지대 간의 위치관계 검사. 
				//player의 위치정보와는 무관함.
				if (player.CheckCollision(x, y, zone.rect)) {
					inSafeZone = true;
					break;
				}
			}
			if (inSafeZone) continue;

			//여기까지 continue 안되고 무사히 진행됐으면 x y 값 확정짓고 마무리.
			break;
		}
		yellowMaterials.emplace_back(x, y);
	}
}


void CArrowKeyGameDialog::CheckPlayerMaterialCollision()
{
	// TODO: 여기에 구현 코드 추가.
	for (auto& material : yellowMaterials) {
		if (!material.collected && material.CheckCollisionWithPlayer(player.x, player.y)) {
			material.collected = true; // 수집 처리
			++collectedYellowMaterialCount;

			CString debugMsg;

			debugMsg.Format(_T("재료를 획득했습니다! 현재 획득한 재료 수: %d\n"), collectedYellowMaterialCount);
			//CMessageManager::GetInstance().AddMessage(debugMsg);
			OutputDebugString(debugMsg);

			// 게임 목표 달성 확인
			if (collectedYellowMaterialCount >= requiredMaterialCount) {
				OutputDebugString(_T("목표 달성! 모든 재료를 획득했습니다!\n"));
				AfxMessageBox(_T("목표 달성! 모든 재료를 획득했습니다!"));
				isGameOver = true;
				// 추가 처리 (게임 종료, 다음 스테이지 등)
				EndDialog(IDCANCEL); //디버깅 할때는 주석처리 해도 됨. 게임 이어가기 가능.
			}
		}
	}
}


// Player-Zombie 충돌에 따른 체력 업데이트
void CArrowKeyGameDialog::UpdatePlayerHP()
{
	// TODO: 여기에 구현 코드 추가.
	if (isGameOver) return;
	bool isCollision = false;

	//충돌 여부 검사
	for (auto& zombie : zombies) {
		if (player.CheckCollision(player.x, player.y, zombie)) {
			isCollision = true;
			break;
		}
	}

	//충돌 여부에 따라 체력 조정
	if (isCollision) {
		player.TakeDamage(); //충돌 시 체력 5 감소
	}
	else {
		player.Heal(); //충돌하지 않을 때 체력 0.5 회복
	}

	//게임 오버
	if (!isGameOver && !player.IsAlive()) {
		isGameOver = true;
		AfxMessageBox(_T("게임 오버! 체력이 0이 되었습니다."));
		//추가적인 게임 오버 처리

		EndDialog(IDCANCEL); //디버깅 할때는 주석처리 해도 됨. 게임 이어가기 가능.
	}
}


// 각 스테이지 별 환경 세팅 (ex. 좀비, 플레이어, 이동속도)
void CArrowKeyGameDialog::InitializeStage(int stageNumber)
{
	// TODO: 여기에 구현 코드 추가.

	// 기존 데이터 초기화
	safeZones.clear();         // 기존 안전지대 초기화
	zombies.clear();           // 기존 좀비 초기화
	yellowMaterials.clear();   // 기존 노란재료 초기화
	collectedYellowMaterialCount = 0; // 현재까지 수집한 재료 수 초기화

	isCooldownActive = false;  // 쿨타임 비활성화
	remainingCooldownTime = 0.0; // 쿨타임 초기화
	
	//창 크기 디폴트 값
	stageWidth = 800;
	stageHeight = 600;

	switch (stageNumber)
	{
	case 1:
		// Stage 1 설정
		stageWidth = 800;
		stageHeight = 600;
		safeZones.push_back(CRect(100, 100, 200, 200)); //activeSafeZoneCount++;
		safeZones.push_back(CRect(300, 300, 400, 400)); //activeSafeZoneCount++;
		activeSafeZoneCount = (int)safeZones.size();
		zombies.push_back(CZombie(12, 10, 1,0.3));
		zombies.push_back(CZombie(15, 10, 2, 0.3));
		zombies.push_back(CZombie(10, 15, 3, 0.3));
		GenerateYellowMaterials(10);           // 노란재료 10개 생성
		requiredMaterialCount = 10;				// 목표 재료 수
		break;
	case 2:
		// Stage 2 설정
		stageWidth = 1000;
		stageHeight = 700;
		// 안전지대
		safeZones.push_back(CRect(100, 100, 200, 200));
		safeZones.push_back(CRect(400, 400, 500, 500));
		activeSafeZoneCount = (int)safeZones.size();

		// 좀비
		zombies.push_back(CZombie(12, 10, 1));
		zombies.push_back(CZombie(15, 10, 2));
		zombies.push_back(CZombie(10, 15, 3));
		zombies.push_back(CZombie(20, 25, 4)); // 추가 좀비

		// 노란재료
		GenerateYellowMaterials(15);
		requiredMaterialCount = 15;				// 목표 재료 수
		break;
	case 3:
		// Stage 3 설정
		stageWidth = 1200;
		stageHeight = 800;
		safeZones.push_back(CRect(100, 100, 200, 200)); 
		safeZones.push_back(CRect(300, 300, 400, 400)); 
		activeSafeZoneCount = (int)safeZones.size();
		zombies.push_back(CZombie(12, 10, 1));
		zombies.push_back(CZombie(15, 10, 2));
		zombies.push_back(CZombie(10, 15, 3));
		GenerateYellowMaterials(10);           // 노란재료 10개 생성
		requiredMaterialCount = 10;				// 목표 재료 수
		break;
	case 4:
		// Stage 4 설정
		stageWidth = 1600;
		stageHeight = 1000;
		safeZones.push_back(CRect(100, 100, 200, 200)); 
		safeZones.push_back(CRect(300, 300, 400, 400)); 
		activeSafeZoneCount = (int)safeZones.size();

		zombies.push_back(CZombie(12, 10, 1,0.3));
		zombies.push_back(CZombie(15, 10, 2, 0.1));
		zombies.push_back(CZombie(10, 15, 3, 0.2));
		zombies.push_back(CZombie(22, 20, 4, 0.3));
		zombies.push_back(CZombie(25, 20, 5, 0.4));
		zombies.push_back(CZombie(20, 25, 6, 0.5));
		zombies.push_back(CZombie(30, 32, 7, 0.3));
		zombies.push_back(CZombie(40, 31, 8, 0.3));
		zombies.push_back(CZombie(50, 37, 9, 0.3));
		zombies.push_back(CZombie(-10, 39, 10, 0.5));
		zombies.push_back(CZombie(-10, -10, 11,0.5));
		zombies.push_back(CZombie(80, 45, 12,0.5));
		zombies.push_back(CZombie(90, 65, 13, 0.4));
		zombies.push_back(CZombie(100, 75, 14, 0.5));
		zombies.push_back(CZombie(110, 55, 15, 0.5));
		zombies.push_back(CZombie(-1, -1, 16, 0.5));
		zombies.push_back(CZombie(-3, -2, 17, 0.5));
		zombies.push_back(CZombie(-1, -3, 18, 0.5));
		GenerateYellowMaterials(10);           // 노란재료 10개 생성
		requiredMaterialCount = 10;				// 목표 재료 수
		break;
	case 5:
		// Stage 5 설정
		stageWidth = 1600;
		stageHeight = 1000;
		safeZones.push_back(CRect(100, 100, 200, 200));
		safeZones.push_back(CRect(300, 300, 400, 400));
		activeSafeZoneCount = (int)safeZones.size();
		zombies.push_back(CZombie(12, 10, 1));
		zombies.push_back(CZombie(15, 10, 2));
		zombies.push_back(CZombie(10, 15, 3));
		GenerateYellowMaterials(10);           // 노란재료 10개 생성
		requiredMaterialCount = 10;				// 목표 재료 수
		break;
	case 6:
		// Stage 6 설정
		stageWidth = 1600;
		stageHeight = 1000;
		safeZones.push_back(CRect(100, 100, 200, 200));
		safeZones.push_back(CRect(300, 300, 400, 400));
		activeSafeZoneCount = (int)safeZones.size();
		zombies.push_back(CZombie(12, 10, 1));
		zombies.push_back(CZombie(15, 10, 2));
		zombies.push_back(CZombie(10, 15, 3));
		GenerateYellowMaterials(10);           // 노란재료 10개 생성
		requiredMaterialCount = 10;				// 목표 재료 수
		break;
	}
}


// 재료 수 출력
void CArrowKeyGameDialog::DrawMaterialCount(CDC& dc) const
{
	// TODO: 여기에 구현 코드 추가.
	CString materialCountText;
	materialCountText.Format(_T("재료: %d / %d"), collectedYellowMaterialCount, requiredMaterialCount);

	// 11시 방향 위치 설정
	int textX = 210;  // 화면 왼쪽 여백
	int textY = 10;  // 화면 상단 여백
	CRect textRect(textX, textY, textX + 200, textY + 30); // 텍스트 위치와 크기 설정

	dc.SetBkMode(TRANSPARENT);  // 투명 배경
	dc.SetTextColor(RGB(0, 0, 0));  // 검은색 텍스트
	dc.DrawText(materialCountText, &textRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}


BOOL CArrowKeyGameDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	InitializeStage(currentStage);	//각 스테이지 별 환경 설정. //GetClientRect(&clientRect); 때문에 위치변.
	MoveWindow(0, 0, stageWidth, stageHeight);	


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
