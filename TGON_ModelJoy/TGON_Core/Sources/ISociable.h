/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <string>
#include "SociableMessage.h"

namespace tgon {
	enum SociableEnum
	{
		Social_Unknown,
		Social_System,
		Social_Object,
		Social_Component,
	};

	class ISociable
	{
	public:
		ISociable( uint32_t key, const SociableEnum sociableType );
		virtual ~ISociable( );

	public:
		virtual void				RecvMessage( _In_ const SociableMessage& msg ) = 0;

		uint32_t					GetKey( ) const					{ return m_key; }

	protected:
		void						SetKey( uint32_t key )		{ m_key = key; }

	private:
		const SociableEnum	m_sociableType;
		uint32_t					m_key;
	};
}