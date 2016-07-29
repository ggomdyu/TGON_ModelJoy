/*
* Author : Cha Junho
* Date : 07/28/2016
* Latest author :
* Latest date : 
*/


#pragma once
#include "../../../Platform/Config/Build.h"

#include "../../../Platform/Utility/Windows/unique_comptr.h"
#include <d3d9.h>
#include <d3dx9.h>


namespace tgon
{


using VertexBufferImpl = class D3D9VertexBuffer;

class TGON_API D3D9VertexBuffer
{
public:
	/*
		Cons/Destructor
	*/
	// The vertex buffer size will be vertexSize * vertexCount.
	// If isDynamic is true, then the device move vertex data to write efficient memory( AGP ).
	D3D9VertexBuffer( int32_t vertexSize, int32_t vertexCount, bool isDynamic );

	virtual ~D3D9VertexBuffer( );

	D3D9VertexBuffer( const D3D9VertexBuffer& rhs ) = delete;


	/*
		Operators
	*/
	D3D9VertexBuffer& operator=( const D3D9VertexBuffer& rhs ) = delete;


public:
	/*
		Commands
	*/
	// If failed, return nullptr
	void* Lock( int32_t lockOffset, int32_t lockSize, bool isDiscard );

	bool Unlock( );

	IDirect3DVertexBuffer9* GetVertexBuffer( );


	/*
		Gets
	*/
	D3DVERTEXBUFFER_DESC GetDesc( );


private:
	unique_comptr<IDirect3DVertexBuffer9> m_vertexBuffer;

	DWORD m_usage;

	DWORD m_pool;

	DWORD m_lockFlag;
};


inline IDirect3DVertexBuffer9* tgon::D3D9VertexBuffer::GetVertexBuffer( )
{
	return m_vertexBuffer;
}

inline D3DVERTEXBUFFER_DESC D3D9VertexBuffer::GetDesc( )
{
	D3DVERTEXBUFFER_DESC desc;
	m_vertexBuffer->GetDesc( &desc );

	return desc;
}


}
