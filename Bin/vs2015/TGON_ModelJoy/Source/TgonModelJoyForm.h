#pragma once
#include <Core/Platform/PlatformApplication.h>
#include <Core/Platform/PlatformTime.h>
#include <Core/Platform/PlatformConsole.h>
#include <Engine/GameApplication.h>
#include <Engine/CoreEvents.h>
#include <Core/Template/Cast.h>


using namespace tgon;

class MyCustomWindow :
	public TPlatformWindow
{
public:
	// 
	// Event handlers
	// 
	virtual bool OnDestroy( )
	{
		return MessageBox( NULL, L"Are you sure you want to quit?", L"WARNING!", MB_YESNO ) == IDYES;
	}

	virtual bool OnGetFocus( ) override
	{
		return false;
	}

	virtual bool OnLoseFocus( ) override
	{
		return false;
	}

};


class TGONSample :
	public GameApplication
{
	// 
	// Generator
	// 
public:
	TGON_GENERATE_OBJECT_INTERFACE( TGONSample, GameApplication )

	// 
	// Ctor/Dtor
	// 
public:
	TGONSample( ) :
		GameApplication( 
			new MyCustomWindow( WindowStyle::LoadFromXML( "WindowStyle.xml" ))
		)
	{
	}

	virtual ~TGONSample( )
	{

	}

	virtual void Update( )
	{
	}

};