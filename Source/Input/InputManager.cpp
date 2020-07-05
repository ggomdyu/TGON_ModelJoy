#include "PrecompiledHeader.h"

#include "Platform/Application.h"

#include "InputManager.h"

namespace tg
{

InputManager::InputManager()
{
    auto inputManager = std::make_unique<gainput::InputManager>();

#if TGON_PLATFORM_WINDOWS
    WindowsApplication::SetCustomMessageCallback([](const MSG& msg)
    {
        m_inputManager->HandleMessage(msg);
    });
#endif
}

InputManager::~InputManager()
{
    m_inputManager.release();
}

std::unique_ptr<Keyboard> InputManager::CreateKeyboard() const
{
    return std::make_unique<Keyboard>(m_inputManager->CreateAndGetDevice<gainput::InputDeviceKeyboard>());
}

std::unique_ptr<Mouse> InputManager::CreateMouse() const
{
    return std::make_unique<Mouse>(m_inputManager->CreateAndGetDevice<gainput::InputDeviceMouse>());
}

std::unique_ptr<Gamepad> InputManager::CreateGamePad() const
{
    return std::make_unique<Gamepad>(m_inputManager->CreateAndGetDevice<gainput::InputDevicePad>());
}

void InputManager::Update()
{
    m_inputManager->Update();
}

}
