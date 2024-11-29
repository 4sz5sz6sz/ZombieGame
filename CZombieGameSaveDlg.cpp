// CZombieGameSaveDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ZombieGame.h"
#include "afxdialogex.h"
#include "CZombieGameSaveDlg.h"
#include "ZombieGameDlg.h"

int check = 0;
bool ifok = true;

// CZombieGameSaveDlg 대화 상자

IMPLEMENT_DYNAMIC(CZombieGameSaveDlg, CDialogEx)

CZombieGameSaveDlg::CZombieGameSaveDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG_SAFE, pParent)
{

}

CZombieGameSaveDlg::~CZombieGameSaveDlg()
{

}

void CZombieGameSaveDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PIC_CALENDER, m_PicCalender);

    DDX_Control(pDX, IDC_COMBO1, m_cbCombo1);
    DDX_Control(pDX, IDC_COMBO2, m_cbCombo2);
    DDX_Control(pDX, IDC_COMBO3, m_cbCombo3);
    DDX_Control(pDX, IDC_COMBO4, m_cbCombo4);
    DDX_Control(pDX, IDC_LIST_CHEST_INSIDE, m_listSaveInside);
    DDX_Control(pDX, IDC_LIST_CHEST_INVEN, m_listChestInven);
    DDX_Control(pDX, IDC_PIC_GETBLUE, m_picGetBlue);
}


BEGIN_MESSAGE_MAP(CZombieGameSaveDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_CALENDER, &CZombieGameSaveDlg::OnClickedButtonCalender)
    ON_BN_CLICKED(IDC_BUTTON_OPEN, &CZombieGameSaveDlg::OnClickedButtonOpen)
    ON_BN_CLICKED(IDC_BUTTON_ITEM_MOVE1, &CZombieGameSaveDlg::OnClickedButtonItemMove1)
    ON_BN_CLICKED(IDCANCEL, &CZombieGameSaveDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CZombieGameSaveDlg 메시지 처리기


void CZombieGameSaveDlg::OnClickedButtonCalender() // 달력펼치기 버튼을 누르면 달력 사진이 보이는 코드
{
    CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
    m_PicCalender.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
    CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
    dc = m_PicCalender.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
    CImage image;//불러오고 싶은 이미지를 로드할 CImage 
    image.Load(_T("Calender.png"));//이미지 로드
    image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
    ReleaseDC(dc);
}

void CZombieGameSaveDlg::OnClickedButtonOpen() // 다이얼 값이 맞는지 판단문
{
    int n[4] = { 0, 0, 0, 0 };
    n[0] = m_cbCombo1.GetCurSel();
    n[1] = m_cbCombo2.GetCurSel();
    n[2] = m_cbCombo3.GetCurSel();
    n[3] = m_cbCombo4.GetCurSel();
    if (n[0] == 2 && n[1] == 7 && n[2] == 9 && n[3] == 6) { // 다이얼 값이 맞는지 판별해주는 조건문
        if (check == 0) {
            check++;
            MessageBox(_T("자물쇠가 풀렸다!"), _T("덜컥!"), MB_ICONINFORMATION);
            m_listSaveInside.AddString(_T("파랑 물약"));
            ifok = false;
            CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
            m_picGetBlue.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
            CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
            dc = m_picGetBlue.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
            CImage image;//불러오고 싶은 이미지를 로드할 CImage 
            image.Load(_T("blue.png"));//이미지 로드
            image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
            ReleaseDC(dc);
        }
        else {
            MessageBox(_T("이미 상자는 열려있어..."), _T("저런!"), MB_ICONWARNING);
        }
    }
    else {
        MessageBox(_T("비밀번호가 틀린거 같다...\n다시 해보자"), _T("이런!"), MB_ICONWARNING);
    }
}


void CZombieGameSaveDlg::OnClickedButtonItemMove1()
{
    CString str;
    int leftIndex = m_listSaveInside.GetCurSel();
    if (leftIndex != LB_ERR) {
        m_listSaveInside.GetText(leftIndex, str);
        m_listSaveInside.DeleteString(leftIndex);
        m_listChestInven.AddString(str);
        if (str == "파랑 물약")
            ifok = true;
    }
}

void CZombieGameSaveDlg::OnBnClickedCancel()
{
    if (!ifok) {
        MessageBox(_T("나무 상자 안에 무언가 있는거 같아!"), _T("잠깐!"), MB_ICONWARNING);
    }
    else {
        for (int i = 0; i < m_listChestInven.GetCount(); i++) {
            m_listChestInven.GetText(i, m_strInven[i]);
        }
        CDialogEx::OnCancel();
    }
}


BOOL CZombieGameSaveDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    for (int i = 0; i < 10; i++) {
        if (m_strInven[i].GetLength() >= 1) {
            m_listChestInven.InsertString(i, m_strInven[i]);
        }
    }

    return TRUE;  // return TRUE unless you set the focus to a control
    // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
