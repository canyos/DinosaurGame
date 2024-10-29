#pragma once
#include <Windows.h>
#include <assert.h>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <functional>

// filesystem 관련 설정 추가
#if _MSC_VER >= 1920     // Visual Studio 2019 이상
	#include <filesystem>
	namespace fs = std::filesystem;
#else
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#endif

#include <math.h>
#include <bitset>
#include <stack>
#include <queue>
#include "pMath.h"
#include "pEnum.h"


#include <mmsystem.h>
#include <wingdi.h>
#include <dinput.h>
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

