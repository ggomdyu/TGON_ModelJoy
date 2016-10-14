/*
 * Author : Cha Junho
 * Date : 03/20/2016
 * Latest author :
 * Latest date :
*/


#pragma once
#include "../Generic/GenericSystem.h"


namespace tgon
{


class TGON_API WindowsSystem :
	public GenericSystem<WindowsSystem>
{
	/* 
	 * Ctor/Dtor
	*/ 
public:
	WindowsSystem( ) = delete;
	~WindowsSystem( ) = delete;

	/*
	 * Commands
	*/
public:
	static BatteryProperty GetPowerInfo( );	
};


using System = WindowsSystem;


} /*namespace tgon*/