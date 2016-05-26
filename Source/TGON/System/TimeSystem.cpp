#include "PrecompiledHeader.h"
#include "TimeSystem.h"

#include "../Platform/Console/TConsole.h"


tgon::TimeSystem::TimeSystem( ) :
	m_timeScale( 1.f ),
	m_oldTime( TTime::GetBootTime( ))
{
	TLog( L"[CREATED] tgon::TimeSystem" );
}

tgon::TimeSystem::~TimeSystem( )
{
	TLog( L"[DESTROYED] tgon::TimeSystem" );
}

void tgon::TimeSystem::Update( float tickTIme )
{
	auto currTime = TTime::GetBootTime( );
	m_tickTime = currTime - m_oldTime;

	m_oldTime = TTime::GetBootTime( );
}