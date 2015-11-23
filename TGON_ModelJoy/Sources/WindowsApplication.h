/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 
* 최종 수정일 : 
*/
#pragma once
#include "GenericApplication.h"

NSBEGIN( tgon );
class WindowsApplication;
typedef WindowsApplication Application;

class WindowsApplication final : public GenericApplication
{
public:
	static bool ResponseMessage( );

public:
	static HINSTANCE GetInstanceHandle( ) { return m_hInstance; }

private:
	WindowsApplication( ) {}
	virtual ~WindowsApplication( ) {}

private:
	static HINSTANCE m_hInstance;
};
NSEND( );
