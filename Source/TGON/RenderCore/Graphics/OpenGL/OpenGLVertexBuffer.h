/*
* Author : Cha Junho
* Date : 07/28/2016
* Latest author :
* Latest date : 
*/


#pragma once
#include "../Core/Platform/OSAL/PlatformInclude.h"
#include <cstdint>


namespace tgon
{


class OpenGLVertexBuffer;
using VertexBufferImpl = OpenGLVertexBuffer;

class TGON_API OpenGLVertexBuffer
{
public:
	/*
		Ctor/Dtor
	*/
	OpenGLVertexBuffer( const OpenGLVertexBuffer& rhs ) = delete;


	/*
		Operators
	*/
	OpenGLVertexBuffer& operator=( const OpenGLVertexBuffer& rhs ) = delete;


public:
	/*
		Commands
	*/
	// If failed, return nullptr
	void* Lock( int32_t lockOffset, int32_t lockSize, bool isDiscard );

	bool Unlock( );


	/*
		Sets
	*/


	/*
		Gets
	*/
	

private:



};


}