#include "PrecompiledHeader.pch"

#include "Game/Engine/GameApplication.h"

#include "Core/Random/Random.h"
#include "Core/Object/Object.h"
#include "Core/Platform/Window.h"
#include "Core/Platform/Generic/GenericWindowType.h"
#include "Core/Platform/Time.h"
#include "Core/Drawing/Bitmap.h"
#include "Core/Debug/Log.h"
#include "Core/Platform/Screen.h"
#include "Core/String/FixedString.h"
#include "Core/String/FixedStringUtility.h"
#include "Core/String/StringView.h"
#include "Core/Utility/InstantiateCounter.h"
#include "Core/Utility/Cast.h"
#include "Core/Math/Mathematics.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Color.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/Math/Extent.h"
#include "Core/Hash/UUID.h"
#include "Graphics/Abstract/Generic/GenericGraphicsType.h"
#include "Graphics/Abstract/Generic/GenericGraphics.h"
#include "Graphics/Abstract/OpenGL/OpenGLShader.h"
#include "Graphics/Abstract/OpenGL/OpenGLShaderCode.h"
#include "Graphics/Render/Renderer.h"
#include "Game/Module/GraphicsModule.h"
#include "Game/Module/TimeModule.h"
#include "Graphics/Abstract/VertexBuffer.h"

//#include <glm/glm/matrix.hpp>
//#include <glm/glm/common.hpp>
//#include <d3d9.h>
//#include <glm/glm/gtx/transform.hpp>
//#include <DirectXMath.h>

#define CONCAT(a, b) a##b
#define STRING_2(a) #a
#define STRING(a) STRING_2(a)

using namespace tgon;

template <typename T>
void PrintMat(const T& matA)
{
    core::Log("%f   %f  %f  %f\n%f   %f  %f  %f\n%f   %f  %f  %f\n%f   %f  %f  %f\n",
        matA[0][0], matA[0][1], matA[0][2], matA[0][3],
        matA[1][0], matA[1][1], matA[1][2], matA[1][3],
        matA[2][0], matA[2][1], matA[2][2], matA[2][3],
        matA[3][0], matA[3][1], matA[3][2], matA[3][3]);
}

class TGON_API ThousandParty :
    public game::GameApplication
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty)

    GLuint m_colorBuffer;
    GLuint m_indexBuffer;
    GLuint m_vertexArray = 0;

public:
    ThousandParty() :
        game::GameApplication([&]()
        {
            core::WindowStyle windowStyle;
            {
                windowStyle.width = 1200;
                windowStyle.height = 1200;
                windowStyle.showMiddle = true;
                windowStyle.title = u8"ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ";
                windowStyle.enableSystemButton = true;
                windowStyle.hasCaption = true;
                windowStyle.resizeable = false;
            }
            return windowStyle;
        }(),
        [&]()
        {
            graphics::VideoMode videoMode;
            {
                videoMode.graphicsSDK = graphics::GraphicsSDK::OpenGL4_0;
                videoMode.enableHardwareAccelerate = true;
                videoMode.enableMultiSampling = true;
            }
            return videoMode;
        }())
    {
        struct V3F_C4B
        {
            core::Vector3 position;
            core::Color4f color;
        };

        V3F_C4B v[] =
        {
            {core::Vector3(-1.0f, -1.0f, 0.0f), core::Color4f(1.0f, 0.0f, 0.0f, 1.0f)},
            {core::Vector3(-1.0f, 1.0f, 0.0f), core::Color4f(0.0f, 1.0f, 0.0f, 1.0f)},
            {core::Vector3(1.0f, 1.0f, 0.0f), core::Color4f(0.0f, 0.0f, 1.0f, 1.0f)},
            {core::Vector3(1.0f, -1.0f, 0.0f), core::Color4f(1.0f, 1.0f, 0.0f, 1.0f)},
        };

        unsigned int i[] =
        {
            0,1,2,0,2,3
        };

        std::initializer_list<graphics::VertexBufferDesc> viad =
        {
            graphics::VertexBufferDesc
            {
                graphics::VertexAttributeIndex::Position,
                3,
                graphics::VertexFormatType::Float,
                false,
                sizeof(V3F_C4B),
                offsetof(V3F_C4B, position),
            },
            graphics::VertexBufferDesc
            {
                graphics::VertexAttributeIndex::Color,
                4,
                graphics::VertexFormatType::Float,
                true,
                sizeof(V3F_C4B),
                offsetof(V3F_C4B, color),
            },
        };

        vb = new graphics::VertexBuffer(v, true, viad);
        if (vb->IsValid() == false)
        {
            return;
        }

        // Create INDEX BUFFER
        glGenBuffers(1, &m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i), i, GL_STATIC_DRAW);


        // Create VAO
        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);
        {
            vb->Use();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        }
        glBindVertexArray(0);

        shader = new graphics::OpenGLShader(g_positionColorVert, g_positionColorFrag);
        if (shader->IsValid() == false)
        {
            return;
        }
    }

    ~ThousandParty()
    {
        // Release VAO
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &m_vertexArray);

        delete vb;
    }

    graphics::VertexBuffer* vb;
    graphics::OpenGLShader* shader;
    core::Matrix4x4 MVP;

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

        static float x = 0.0f;
        auto M2 = core::Matrix4x4::Translate(x, 0.0f, 0.0f);
        auto V2 = core::Matrix4x4::LookAtRH({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        auto P2 = core::Matrix4x4::PerspectiveRH(3.14159268f / 8.0f, 500.0f / 500.0f, 0.1f, 1000.0f);
        x += 0.005f;
        
        MVP = M2 * V2 * P2;
        
        glClear(GL_COLOR_BUFFER_BIT);
        shader->Use();
        {
            shader->SetParameterMatrix4fv("g_uMVP", &MVP[0][0]);

            glBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }
        shader->Unuse();

        FindModule<game::GraphicsModule>()->GetGraphics()->SwapBuffer();
    }
};
TGON_DECLARE_APPLICATION(ThousandParty)
