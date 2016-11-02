// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C의 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <list>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <functional>
#include <ctime>
#include <crtdbg.h>
#include <gdiplus.h>
#include "BitBmp.h"
#include <algorithm>


using namespace std;
using namespace Gdiplus;


#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "gdiplus")