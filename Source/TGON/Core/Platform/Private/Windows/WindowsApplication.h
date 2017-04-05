/**
 * filename WindowsApplication.h
 * author   ggomdyu
 * since    03/20/2016
 */

#pragma once
#include "../Generic/GenericApplication.h"

#include "WindowsApplicationFwd.h"
#include <cstdint>

namespace tgon
{

class TGON_API WindowsApplication
{
/** 
 * @section Ctor/Dtor
 */
public:
	WindowsApplication() = delete;
	~WindowsApplication() = delete;

/**
 * @section Public command methods
 */
public:
	/**
	 * @brief                   Pull out the message from all queue.
     * @param [out] message     Message to pull out
	 * @return                  False if there is no message to pull out
	 */
    static bool PullMessage(MSG* message);
    /**
	 * @brief                   Pull out the message from specified window's message queue.
     * @param [in]  window      The window to pull out message from its queue
     * @param [out] message     Message to pull out
	 * @return                  False if there is no message to pull out
	 */
    static bool PullMessage(const class WindowsWindowFrame* window, MSG* message);
    /**
	 * @brief                   Pull out the message from all queue and dispatch it.
     * @param [out] message     Message to pull out
	 * @return                  False if there is no message to pull out
	 */
	static bool PumpMessage(MSG* message);
    /**
	 * @brief                   Show the Message box which has buttons: Yes, No
     * @param [in] message      Message box description
     * @param [in] caption      Message box title
     * @param [in] handler      Message box event handler when called button clicked
	 * @return                  False if there is no message to pull out
	 */ 
    static void ShowYesNoPopup(const char* message, const char* caption, OnPopupEventHandle handler);
    static void ShowYesNoPopup(const wchar_t* message, const wchar_t* caption, OnPopupEventHandle handler);
    static void ShowOkPopup(const char* message, const char* caption, OnPopupEventHandle handler);
    static void ShowOkPopup(const wchar_t* message, const wchar_t* caption, OnPopupEventHandle handler);
	
	/**
	 * @brief               Post quit message to message queue.
	 * @param   exitCode    Exit code
	 */
	static void Quit(int32_t exitCode);

	/**
	 * @brief               Terminate thread by force.
	 * @param	exitCode	Exit code
	 */
	static void ExitThread(int32_t exitCode);

	/**
	 * @brief               Enable show cursor mode: Hide or Show
	 * @param   enableShow	Pass true to show, false otherwise.
	 */
	static void ShowCursor(bool enableShow);

	/**
	 * @brief   Enable float calculate exception like: devide by zero, underflow, overflow, etc 
	 */
	static void EnableFloatingException(unsigned int newStat);

	/**/
	//static void DisableTaskSwitching();

/**
 * @section Event handlers
 */
public:
	static LRESULT CALLBACK OnMessageHandled(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam);

/**
 * @section Public variables
 */
public:
	static const HINSTANCE InstanceHandle;
	static const wchar_t* AppClassName;
};

using TApplication = GenericApplication<WindowsApplication>;

} /* namespace tgon */
