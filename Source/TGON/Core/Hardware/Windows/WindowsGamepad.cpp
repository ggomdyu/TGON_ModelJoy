#include "PrecompiledHeader.h"

#include "../Gamepad.h"

#include <string>

namespace tgon
{

WindowsGamepad::WindowsGamepad(OIS::JoyStick* gamepadDevice) noexcept :
    m_gamepadDevice(gamepadDevice)
{
    assert(gamepadDevice != nullptr && "gamepadDevice can't be nullptr.");
}

void WindowsGamepad::Update()
{
    m_prevGamepadState = m_gamepadDevice->getJoyStickState();
    m_gamepadDevice->capture();
}

void WindowsGamepad::Vibrate(float leftMotor, float rightMotor)
{
    //auto a = m_gamepadDevice->getNumberOfComponents(OIS::OIS_Axis);
    //auto b = m_gamepadDevice->getNumberOfComponents(OIS::OIS_Slider);
    //auto c = m_gamepadDevice->getNumberOfComponents(OIS::OIS_POV);
    //auto d = m_gamepadDevice->getNumberOfComponents(OIS::OIS_Button);
    //auto e = m_gamepadDevice->getNumberOfComponents(OIS::OIS_Vector3);
    //auto gamepadState = m_gamepadDevice->getJoyStickState();
    //int i = 0;
    ///*for (bool axes : gamepadState.mButtons)
    //{
    //    if (axes == false)
    //    {
    //    ++i;
    //        continue;
    //    }

    //    auto str = std::wstring(L"Axis") + std::to_wstring(i++) + L" " + std::to_wstring(axes) + L"\n";
    //    OutputDebugStringW(str.c_str());
    //}*/

    //for (auto pov : gamepadState.mPOV)
    //{
    //    auto str = std::wstring(L"Pov Direction") + std::to_wstring(i++) + L" " + std::to_wstring(pov.direction) + L"\n";
    //    OutputDebugStringW(str.c_str());
    //}

    //int n = 3;
}

bool WindowsGamepad::IsButtonDown(int32_t buttonNumber) const
{
    decltype(auto) currGamepadState = m_gamepadDevice->getJoyStickState();
    if (currGamepadState.mButtons.size() <= buttonNumber)
    {
        return false;
    }

    if (m_prevGamepadState.mButtons[buttonNumber] == false && 
        currGamepadState.mButtons[buttonNumber])
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool WindowsGamepad::IsButtonHold(int32_t buttonNumber) const
{
    decltype(auto) currGamepadState = m_gamepadDevice->getJoyStickState();
    if (currGamepadState.mButtons.size() <= buttonNumber)
    {
        return false;
    }

    if (m_prevGamepadState.mButtons[buttonNumber] &&
        currGamepadState.mButtons[buttonNumber])
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool WindowsGamepad::IsButtonUp(int32_t buttonNumber) const
{
    decltype(auto) currGamepadState = m_gamepadDevice->getJoyStickState();
    if (currGamepadState.mButtons.size() <= buttonNumber)
    {
        return false;
    }

    if (m_prevGamepadState.mButtons[buttonNumber] &&
        currGamepadState.mButtons[buttonNumber] == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

} /* namespace tgon */
