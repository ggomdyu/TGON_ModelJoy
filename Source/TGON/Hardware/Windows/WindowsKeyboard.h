/**
 * @file    WindowsKeyboard.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <OIS.h>
#include <array>

#include "Platform/Config.h"
#include "Core/NonCopyable.h"

namespace tgon
{

enum class KeyCode
{
    Escape              = OIS::KeyCode::KC_ESCAPE,
    F1                  = OIS::KeyCode::KC_F1,
    F2                  = OIS::KeyCode::KC_F2,
    F3                  = OIS::KeyCode::KC_F3,
    F4                  = OIS::KeyCode::KC_F4,
    F5                  = OIS::KeyCode::KC_F5,
    F6                  = OIS::KeyCode::KC_F6,
    F7                  = OIS::KeyCode::KC_F7,
    F8                  = OIS::KeyCode::KC_F8,
    F9                  = OIS::KeyCode::KC_F9,
    F10                 = OIS::KeyCode::KC_F10,
    F11                 = OIS::KeyCode::KC_F11,
    F12                 = OIS::KeyCode::KC_F12,
    F13                 = OIS::KeyCode::KC_F13,
    F14                 = OIS::KeyCode::KC_F14,
    F15                 = OIS::KeyCode::KC_F15,
    ScrollLock          = OIS::KeyCode::KC_F15,
    Break               = OIS::KeyCode::KC_PAUSE,
    Space               = OIS::KeyCode::KC_SPACE,
    Apostrophe          = OIS::KeyCode::KC_APOSTROPHE,
    Comma               = OIS::KeyCode::KC_COMMA,
    Minus               = OIS::KeyCode::KC_MINUS,
    Period              = OIS::KeyCode::KC_PERIOD,
    Slash               = OIS::KeyCode::KC_SLASH,
    Alpha0              = OIS::KeyCode::KC_0,
    Alpha1              = OIS::KeyCode::KC_1,
    Alpha2              = OIS::KeyCode::KC_2,
    Alpha3              = OIS::KeyCode::KC_3,
    Alpha4              = OIS::KeyCode::KC_4,
    Alpha5              = OIS::KeyCode::KC_5,
    Alpha6              = OIS::KeyCode::KC_6,
    Alpha7              = OIS::KeyCode::KC_7,
    Alpha8              = OIS::KeyCode::KC_8,
    Alpha9              = OIS::KeyCode::KC_9,
    Semicolon           = OIS::KeyCode::KC_SEMICOLON,
    Less                = 0xF4,
    A                   = OIS::KeyCode::KC_A,
    B                   = OIS::KeyCode::KC_B,
    C                   = OIS::KeyCode::KC_C,
    D                   = OIS::KeyCode::KC_D,
    E                   = OIS::KeyCode::KC_E,
    F                   = OIS::KeyCode::KC_F,
    G                   = OIS::KeyCode::KC_G,
    H                   = OIS::KeyCode::KC_H,
    I                   = OIS::KeyCode::KC_I,
    J                   = OIS::KeyCode::KC_J,
    K                   = OIS::KeyCode::KC_K,
    L                   = OIS::KeyCode::KC_L,
    M                   = OIS::KeyCode::KC_M,
    N                   = OIS::KeyCode::KC_N,
    O                   = OIS::KeyCode::KC_O,
    P                   = OIS::KeyCode::KC_P,
    Q                   = OIS::KeyCode::KC_Q,
    R                   = OIS::KeyCode::KC_R,
    S                   = OIS::KeyCode::KC_S,
    T                   = OIS::KeyCode::KC_T,
    U                   = OIS::KeyCode::KC_U,
    V                   = OIS::KeyCode::KC_V,
    W                   = OIS::KeyCode::KC_W,
    X                   = OIS::KeyCode::KC_X,
    Y                   = OIS::KeyCode::KC_Y,
    Z                   = OIS::KeyCode::KC_Z,
    LeftBracket         = OIS::KeyCode::KC_LBRACKET,
    Backslash           = OIS::KeyCode::KC_BACKSLASH,
    RightBracket        = OIS::KeyCode::KC_RBRACKET,
    Grave               = OIS::KeyCode::KC_GRAVE,
    LeftArrow           = OIS::KeyCode::KC_LEFT,
    RightArrow          = OIS::KeyCode::KC_RIGHT,
    UpArrow             = OIS::KeyCode::KC_UP,
    DownArrow           = OIS::KeyCode::KC_DOWN,
    Insert              = OIS::KeyCode::KC_INSERT,
    Home                = OIS::KeyCode::KC_HOME,
    Delete              = OIS::KeyCode::KC_DELETE,
    End                 = OIS::KeyCode::KC_END,
    PageUp              = OIS::KeyCode::KC_PGUP,
    PageDown            = OIS::KeyCode::KC_PGDOWN,
    NumLock             = OIS::KeyCode::KC_NUMLOCK,
    KeypadEquals        = OIS::KeyCode::KC_NUMPADEQUALS,
    KeypadDivide        = OIS::KeyCode::KC_DIVIDE,
    KeypadMultiply      = OIS::KeyCode::KC_MULTIPLY,
    KeypadSubtract      = OIS::KeyCode::KC_SUBTRACT,
    KeypadAdd           = OIS::KeyCode::KC_ADD,
    KeypadEnter         = OIS::KeyCode::KC_NUMPADENTER,
    KeypadInsert        = OIS::KeyCode::KC_INSERT,
    KeypadEnd           = OIS::KeyCode::KC_END,
    //KeypadDown          = OIS::KeyCode::KC_NUMPAD2,
    //KeypadPageDown      = OIS::KeyCode::KC_F15,
    //KeypadLeft          = OIS::KeyCode::KC_NUMPAD4,
    //KeypadRight         = OIS::KeyCode::KC_NUMPAD6,
    KeypadHome          = OIS::KeyCode::KC_HOME,
    //KeypadUp            = OIS::KeyCode::KC_NUMPAD8,
    KeypadPageUp        = OIS::KeyCode::KC_PGUP,
    KeypadDelete        = OIS::KeyCode::KC_DELETE,
    BackSpace           = OIS::KeyCode::KC_BACK,
    Tab                 = OIS::KeyCode::KC_TAB,
    Return              = OIS::KeyCode::KC_RETURN,
    CapsLock            = OIS::KeyCode::KC_CAPITAL,
    LeftShift           = OIS::KeyCode::KC_LSHIFT,
    RightShift          = OIS::KeyCode::KC_RSHIFT,
    LeftControl         = OIS::KeyCode::KC_LCONTROL,
    RightControl        = OIS::KeyCode::KC_RCONTROL,
    LeftWindows         = OIS::KeyCode::KC_LWIN,
    RightWindows        = OIS::KeyCode::KC_RWIN,
    LeftAlt             = OIS::KeyCode::KC_LMENU,
    RightAlt            = OIS::KeyCode::KC_RMENU,
    //Back                = OIS::KeyCode::KC_F15,
    VolumeUp            = OIS::KeyCode::KC_VOLUMEUP,
    VolumeDown          = OIS::KeyCode::KC_VOLUMEDOWN,
    Power               = OIS::KeyCode::KC_POWER,
    Equals              = OIS::KeyCode::KC_EQUALS,
    At                  = OIS::KeyCode::KC_AT,
    Plus                = OIS::KeyCode::KC_ADD,
    MediaPlayPause      = OIS::KeyCode::KC_PLAYPAUSE,
    //MediaStop           = OIS::KeyCode::KC_STOP,
    MediaNext           = OIS::KeyCode::KC_NEXTTRACK,
    MediaPrevious       = OIS::KeyCode::KC_PREVTRACK,
    Mute                = OIS::KeyCode::KC_MUTE,
    //Fn                  = OIS::KeyCode::KC_F15,
    Colon               = OIS::KeyCode::KC_COLON,
    SysRq               = OIS::KeyCode::KC_SYSRQ,
};

class TGON_API WindowsKeyboard :
    private NonCopyable
{
/**@section Constructor */
protected:
    explicit WindowsKeyboard(OIS::Keyboard* nativeKeyboard) noexcept;

/**@section Method */
public:
    OIS::Keyboard* GetNativeKeyboard() noexcept;
    const OIS::Keyboard* GetNativeKeyboard() const noexcept;

/**@section Variable */
protected:
    OIS::Keyboard* m_nativeKeyboard;
    char m_currKeyStates[256];
};

using PlatformKeyboard = WindowsKeyboard;

} /* namespace tgon */
