#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/


class IModelBase
{
public:
	IModelBase( );
	~IModelBase( );

	virtual void Render( ) = 0;

public:
	virtual void LoadMesh( const char* const szFilePath ) = 0;
};