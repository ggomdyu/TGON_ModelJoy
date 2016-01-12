/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "ISociable.h"

namespace tgon {
	class ISystem : public ISociable
	{
	public:
		ISystem( unsigned int key );
		virtual ~ISystem( );

		virtual void Initialize( )	{};
		virtual void FrameMove( float elapsedTime ) = 0;

	private:
		void operator delete( void* arg )	{ std::free( arg ); }
	};
}