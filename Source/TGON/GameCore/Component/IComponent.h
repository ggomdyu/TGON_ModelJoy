/*
* Author : Cha Junho
* Date : 04/26/2015
* Latest author :
* Latest date :
*/

#pragma once
#include "../../Core/Object/TObject.h"
#include "../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API IComponent :
	public TObject
{
public:
	TGON_OBJECT( IComponent, std::nullptr_t )

public:
	/*
		Cons/Destructor
	*/
	explicit IComponent( class TGameObject* owner );
	
	virtual ~IComponent( ) = 0;
	
	//virtual void Clone( ) = 0;


public:
	/*
		Commands
	*/
	virtual void Update( float tickTime ) = 0;

public:
	/*
		Sets
	*/
	void SetOwner( class TGameObject* owner );
	
	/*
		Gets
	*/
	class TGameObject* GetOwner( ) const;


private:
	class TGameObject* m_owner;
};

inline void IComponent::SetOwner( TGameObject* owner )
{
	m_owner = owner;
}

inline TGameObject* IComponent::GetOwner( ) const
{
	return m_owner;
}


}