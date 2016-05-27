#include "PrecompiledHeader.h"
#include "WindowsApplication.h"

#include "../../Window/WindowEvent.h"
#include "../../Slate/PlatformWindow.h"


TGON_API const HINSTANCE tgon::WindowsApplication::InstanceHandle( ::GetModuleHandleW( NULL ));
TGON_API MSG tgon::WindowsApplication::m_msg;


tgon::WindowsApplication::WindowsApplication(
	const WindowStyle& rootWndStyle ) :

	AbstractApplication( rootWndStyle )
{
}

tgon::WindowsApplication::~WindowsApplication( )
{
}

int32_t tgon::WindowsApplication::Run( )
{
	while ( m_msg.message != WM_QUIT )
	{
		bool doesMsgExist = MessageLoop( );
		if ( !doesMsgExist )
		{
			this->OnIdle( );
		}
	}

	return 0;
}

const tgon::SpTWindow& tgon::WindowsApplication::GetWindow( ) const
{
	return m_window;
}

void tgon::WindowsApplication::Run(
	WindowsWindow& window )
{
	assert( false && "You just called DEPRECATED!!" );

	/*while ( m_msg.message != WM_QUIT )
	{
		bool doesMsgExist = MessageLoop( );
		if ( !doesMsgExist )
		{
			windOnIdle( );
		}
	}*/
}

bool tgon::WindowsApplication::MessageLoop( )
{
	if ( PeekMessageW( &m_msg, nullptr, 0, 0, PM_REMOVE ) == TRUE )
	{
		::TranslateMessage( &m_msg ); // Process WM_CHAR
		::DispatchMessageW( &m_msg );
		return true;
	}
	else
	{
		return false;
	}
}

tgon::TSystemBatteryInfo tgon::WindowsApplication::GetPowerInfo( )
{
	SYSTEM_POWER_STATUS sps;
	::GetSystemPowerStatus( &sps );

	TSystemBatteryInfo adapter;
	adapter.batteryFlag = static_cast<TSystemBatteryInfo::BateryFlag>( sps.BatteryFlag );
	adapter.batteryFlag = static_cast<TSystemBatteryInfo::BateryFlag>( sps.BatteryLifePercent );

	return adapter;
}