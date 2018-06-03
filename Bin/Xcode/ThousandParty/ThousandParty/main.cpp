#include "PrecompiledHeader.h"

#include "TGON.h"

using namespace tgon;

class TGON_API ThousandParty final :
    public Application
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty)

public:
    ThousandParty() :
        Application(WindowStyle())
    {
        this->AddModule<TimeModule>();
        this->AddModule<EventModule>();
        this->AddModule<GraphicsModule>(VideoMode(), this->GetRootWindow());
        this->AddModule<InputModule>([]()
        {
            InputMode inputMode;
            inputMode.isUseKeyboard = true;
            inputMode.isUseMouse = true;
            inputMode.isUseGamepad = false;
            return inputMode;
        } (), this->GetRootWindow());
    }

/* @section Public destructor */
public:
    virtual ~ThousandParty()
    {
    }

/* @section Public event handler */
public:
    virtual void OnWillLaunch() override
    {
        SuperType::OnWillLaunch();
    }

    virtual void OnDidLaunch() override
    {
        SuperType::OnDidLaunch();
    }

    virtual void OnUpdate() override
    {
        SuperType::OnUpdate();
        
        decltype(auto) inputModule = GetModule<InputModule>();
        
        decltype(auto) keyboard = inputModule->GetKeyboard();
        if (keyboard->IsKeyDown(Keyboard::KeyCode::Space))
        {
            Log(LogLevel::Debug, "1");
        }
        else if (keyboard->IsKeyHold(Keyboard::KeyCode::Space))
        {
            Log(LogLevel::Debug, "2");
        }
        else if (keyboard->IsKeyUp(Keyboard::KeyCode::Space))
        {
            Log(LogLevel::Debug, "3");
        }
        
        decltype(auto) mouse = inputModule->GetMouse();
        if (mouse->IsMouseDown(Mouse::MouseCode::Left))
        {
            Log(LogLevel::Debug, "1");
        }
        else if (mouse->IsMouseHold(Mouse::MouseCode::Left))
        {
            Log(LogLevel::Debug, "2");
        }
        else if (mouse->IsMouseUp(Mouse::MouseCode::Left))
        {
            Log(LogLevel::Debug, "3");
        }

        /*decltype(auto) gamepad = inputModule->GetGamepad();
        gamepad->Vibrate(0.0f, 0.0f);*/
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)
