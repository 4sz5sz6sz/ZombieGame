// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.
bool stageCleared[8] = { false, true, false, false, false, false, false, false }; // 초기화: 1단계만 해금
//bool stageCleared[8] = { false, true, true, true, true, true, true, false}; // 디버깅용@@@@@ 올 클리어