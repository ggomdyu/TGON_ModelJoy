// stdafx.h : Defines the entry point for the console application.

#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-28
* 최종 수정 :
* 최종 수정일 :
*/

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.

#define NSBEGIN( name ) namespace name {
#define NSEND( ) }

#include <iostream>
#include <sstream>
#include <memory>
#include <cassert>
#include <map>
#include <unordered_set>

#include <Windows.h>
#include <dwmapi.h>

#include "msgstream.h"
#include "Uncopyable.h"
#include "WindowsWindowUtil.h"
#include "WindowStyle.h"
#include "WindowEvent.h"