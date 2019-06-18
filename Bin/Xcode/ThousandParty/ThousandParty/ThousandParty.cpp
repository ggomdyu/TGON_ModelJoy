#include "PrecompiledHeader.h"

#include "TGON.h"
#include "ThousandParty.h"
#include "Drawing/FontFactory.h"
#include "String/Encoding.h"
#include "String/UnicodeScalar.h"
#include "LogoScene.h"
#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#include <unicode/utypes.h>

#include "Drawing/TextureAtlasTree.h"

TGON_DECLARE_ENGINE(ThousandParty);

using namespace tgon;

TextureAtlasTree tat;

void ThousandParty::OnLaunch()
{
    SuperType::OnLaunch();

    this->Initialize();
}

void ThousandParty::OnTerminate()
{
    SuperType::OnTerminate();
}

void ThousandParty::Update()
{
    SuperType::Update();
}

void ThousandParty::Initialize()
{
    this->InitializeModule();
}

void Draw(TextureAltasNode* node)
{
    if (node->left)
    {
        Draw(node->left.get());
    }
    if (node->right)
    {
        Draw(node->right.get());
    }

    auto r = RandRange(0, 255);
    auto g = RandRange(0, 255);
    auto b = RandRange(0, 255);
    if (node->id != 0)
    for (int y = node->rect.y; y < node->rect.y + node->rect.height-4; ++y)
        for (int x = node->rect.x; x < node->rect.x + node->rect.width-4; ++x)
        {
            HWND wndHandle = reinterpret_cast<HWND>(Application::GetInstance()->GetRootWindow()->GetNativeWindow());
            HDC dcHandle = ::GetDC(wndHandle);
            {
                SetPixel(dcHandle, static_cast<int>(x), static_cast<int>(y), RGB(r, g, b));
            }
            ::ReleaseDC(wndHandle, dcHandle);
        }
}

void ThousandParty::InitializeModule()
{
    using namespace tgon;
    
    FontFactory ff;
    std::shared_ptr<Font> font = ff.GetFont("E:/Users/ggomdyu/Desktop/maplestory.ttf");
    
    for (int i = 0; i < 300; ++i)
    {
        bool a = tat.Insert({0,0,RandRange(50, 70), RandRange(50, 70) }, i);
        if (a == false)
        {
            int n = 34;
        }
    }
    Draw(&tat.m_rootNode);

    
    int n = 3;
//    char str[] = u8"가";
//    char32_t ch = u'가';
//    constexpr UnicodeScalar us(u8"가");
//    //char32_t c = (str[0] << 0);
//    auto& glyphData = font->GetGlyphData(44032, 50);
//
//    for (int y = 0; y < glyphData.size.height; ++y)
//        for (int x = 0; x < glyphData.size.width; ++x)
//        {
//            HWND wndHandle = reinterpret_cast<HWND>(Application::GetInstance()->GetRootWindow()->GetNativeWindow());
//            HDC dcHandle = ::GetDC(wndHandle);
//            {
//                auto color = 255 - glyphData.bitmap[y * glyphData.size.width + x];
//                if (color != 255)
//                {
//                    SetPixel(dcHandle, static_cast<int>(x), static_cast<int>(y), RGB(color, color, color));
//                }
//            }
//            ::ReleaseDC(wndHandle, dcHandle);
//        }


    // Input Module
    const auto& rootWindow = Application::GetInstance()->GetRootWindow();
    InputMode inputMode;
    {
        inputMode.isUseMouse = false;
        inputMode.isUseKeyboard = true;
        inputMode.isUseGamepad = false;
    }
    this->RegisterModule<InputModule>(*rootWindow, inputMode);

    //// Graphics Module
    //VideoMode videoMode;
    //{
    //    videoMode.clearColor = Color4f(0.0f, 0.44313f, 0.75686f, 1.0f);
    //    videoMode.enableHardwareAccelerate = true;
    //    videoMode.enableTripleBuffer = false;
    //    videoMode.enableVerticalSync = false;
    //    videoMode.enableMultiSampling = false;
    //};
    //this->RegisterModule<GraphicsModule>(*rootWindow, videoMode);
    
    // Etc
    this->RegisterModule<TimeModule>();
    this->RegisterModule<TaskModule>();
    //this->RegisterModule<SceneModule>()->ChangeScene(new LogoScene);
}
