/*
* Author : Cha Junho
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once
#include "../Abstract/APlatformWindow.h"

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>
#include <atomic> // std::atomic can not copied so be careful on place member


namespace tgon
{


class TGON_API WindowsPlatformWindow : 
	public APlatformWindow,
	public IDropTarget
{
	friend class WindowsPlatformApplication;

	// 
	// Ctor/Dtor
	// 
public:
	/* param	wndStyle	Window style property that you want to make */
	explicit WindowsPlatformWindow( /*In*/ const WindowStyle& wndStyle );
	virtual ~WindowsPlatformWindow( );

	// 
	// Commands
	// 
public:
	virtual bool PumpEvent( ) override;
	virtual void Show( ) override;
	virtual void Hide( ) override;
	virtual void Quit( ) override;
	virtual void Maximize( ) override;
	virtual void Minimize( ) override;
	virtual void BringToFront( ) override;
	virtual void Flash( ) override;
	
	//
	// COM Interfaces
	//
	STDMETHODIMP QueryInterface( REFIID riid, void** ppvObject ) override;
	STDMETHODIMP_( ULONG ) AddRef( ) override;
	STDMETHODIMP_( ULONG ) Release( ) override;
	STDMETHODIMP DragEnter( LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect ) override;
	STDMETHODIMP DragOver( DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect ) override;
	STDMETHODIMP DragLeave( ) override;
	STDMETHODIMP Drop( LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect ) override;

	// 
	// Sets
	// 
	virtual void EnableGlobalMouseFocus( bool isEnable ) override;
	virtual void SetPosition( int32_t x, int32_t y ) override;
	virtual void SetScale( int32_t width, int32_t height ) override;
	virtual void SetCaption( /*In*/ const wchar_t* caption ) override;

	// 
	// Gets
	// 
	/* @return	Return position that contains non-client area */
	virtual void GetPosition( /*Out*/ int32_t* x, /*Out*/ int32_t* y ) const override;
	/* @return	Return window size that contains non-client area */
	virtual void GetSize( /*Out*/ int32_t* width, /*Out*/ int32_t* height ) const override;
	/* @param	caption	Destination of caption text */
	virtual void GetCaptionText( /*Out*/ wchar_t* caption ) const override;
	/* @return	Return window's handle */
	HWND GetWindowHandle( ) const;

	// 
	// Internal works
	// 
private:
	void AdditionalInit( /*In*/ const WindowStyle& );
	virtual LRESULT ProcessMessage( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam );

	// 
	// Private variables
	// 
private:
	HWND m_wndHandle;
	uint32_t m_refCount;
};

using TPlatformWindow = WindowsPlatformWindow;


} /*namespace tgon*/