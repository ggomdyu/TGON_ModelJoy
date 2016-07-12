/*
* Author : Cha Junho
* Date : 05/15/2016
* Latest author :
* Latest date :
* Description : Abstract-API Sets for Windows
*/


#pragma once
#include "../Abstract/AbstractTime.h"
#include "../../Config/Build.h"

#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	undef WIN32_LEAN_AND_MEAN
#endif


namespace tgon
{


using TimeImpl = class WindowsTime;

class TGON_API WindowsTime :
	public AbstractTime
{
public:
	/*
		Commands
	*/
	// Getting OS's execution time as millisecond
	static uint32_t GetBootTime( );
	
	static uint64_t GetBootTime64( );

	// Getting current system time
	static TSystemTime GetLocalTime( );
	

private:
	/*
		Cons/Destructor
	*/
	WindowsTime( ) = delete;

	virtual ~WindowsTime( ) = delete;
};


inline uint32_t WindowsTime::GetBootTime( )
{
	return GetTickCount( );
}

inline uint64_t WindowsTime::GetBootTime64( )
{
	return GetTickCount64( );
}


}