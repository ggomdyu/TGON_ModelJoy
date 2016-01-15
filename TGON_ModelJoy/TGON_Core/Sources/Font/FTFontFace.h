/*
* 작성자 : 차준호
* 작성일 : 2016-01-14
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "FTFontManager.h"


namespace tgon {


enum AlignTable
{
	FT_LEFT			= 0,
	FT_CENTER		= 0x1,
	FT_RIGHT		= 0x2,
	FT_TOP			= 0x4,
	FT_VCENTER	= 0x8,
};

enum ThicknessTable
{
	FT_NORMAL,
	FT_BOLD
};


class FTFontFace
{
public:
	FTFontFace( const char* fontPath, int size );
	~FTFontFace( );

	operator	FT_Face( ) const		{ return m_face; }

public:
	int			GetHeight( ) const		{ return m_size; }
	FT_Face	GetFace( ) const		{ return m_face; }

private:
	FT_Face m_face;

	bool m_isKerning;
	int m_size;
};


}