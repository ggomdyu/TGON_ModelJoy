/**
 * @file    OpenGLShaderCode.h
 * @author  ggomdyu
 * @since   12/19/2017
 */

#pragma once

constexpr const char g_positionColorVert[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
layout(location = 0) in vec3 vertPosition;                                          \n\
                                                                                    \n\
uniform mat4 matWVP;                                                                \n\
uniform vec4 uColor;                                                                \n\
out vec4 fragColor;                                                                 \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    gl_Position = matWVP * vec4(vertPosition, 1.0);                                 \n\
    fragColor = uColor;                                                             \n\
}                                                                                   \n\
";

constexpr const char g_positionColorFrag[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
in vec4 fragColor;                                                                  \n\
out vec4 outColor;                                                                  \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    outColor = fragColor;                                                           \n\
}                                                                                   \n\
";

constexpr const char g_positionNormalUVVert[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
layout(location = 0) in vec3 vertPosition;                                          \n\
layout(location = 1) in vec3 vertNormal;                                            \n\
layout(location = 2) in vec2 vertUV;                                                \n\
out vec2 fragUV;                                                                    \n\
uniform mat4 matWVP;                                                                \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    gl_Position = matWVP * vec4(vertPosition, 1.0);                                 \n\
    fragUV = vertUV;                                                                \n\
}                                                                                   \n\
";

constexpr const char g_positionNormalUVFrag[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
in vec2 fragUV;                                                                     \n\
out vec4 outColor;                                                                  \n\
                                                                                    \n\
uniform sampler2D textureSampler;                                                   \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    outColor = texture(textureSampler, fragUV);                                     \n\
}                                                                                   \n\
";

constexpr const char g_positionUVVert[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
layout(location = 0) in vec3 vertPosition;                                          \n\
layout(location = 1) in vec2 vertUV;                                                \n\
uniform mat4 matWVP;                                                                \n\
out vec2 fragUV;                                                                    \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    gl_Position = matWVP * vec4(vertPosition, 1.0);                                 \n\
    fragUV = vertUV;                                                                \n\
}                                                                                   \n\
";

constexpr const char g_positionUVFrag[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
in vec2 fragUV;                                                                     \n\
out vec4 outColor;                                                                  \n\
                                                                                    \n\
uniform sampler2D textureSampler;                                                   \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    outColor = texture(textureSampler, fragUV);                                     \n\
}                                                                                   \n\
";

constexpr const char g_grayScaleFrag[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
in vec2 fragUV;                                                                     \n\
out vec4 outColor;                                                                  \n\
uniform sampler2D textureSampler;                                                   \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    vec4 color = texture(textureSampler, fragUV);                                   \n\
    float grayScale = (color.r + color.g + color.b) / 3;                            \n\
    outColor = vec4(grayScale, grayScale, grayScale, color.a);                      \n\
}                                                                                   \n\
";

constexpr const char g_weightedGrayScaleFrag[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
    in vec2 fragUV;                                                                 \n\
    out vec4 outColor;                                                              \n\
    uniform sampler2D textureSampler;                                               \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    vec4 color = texture(textureSampler, fragUV);                                   \n\
    float grayScale = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;       \n\
    outColor = vec4(grayScale, grayScale, grayScale, color.a);                      \n\
}                                                                                   \n\
";

constexpr const char g_inverseFrag[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
in vec2 fragUV;                                                                     \n\
out vec4 outColor;                                                                  \n\
uniform sampler2D textureSampler;                                                   \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    vec4 color = texture(textureSampler, fragUV);                                   \n\
    outColor = vec4(1.0 - color.r, 1.0 - color.g, 1.0 - color.b, color.a);          \n\
}                                                                                   \n\
";

constexpr const char g_sharpenFrag[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
in vec2 fragUV;                                                                     \n\
out vec4 outColor;                                                                  \n\
uniform sampler2D textureSampler;                                                   \n\
uniform float centerKernel = 9;                                                   \n\
uniform float aroundKernel = -1;                                                    \n\
uniform float aroundUVOffset = 1.0 / 300.0;                                         \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    vec2 kernelOffset[] = vec2[](                                                   \n\
        vec2(-aroundUVOffset, aroundUVOffset), vec2(0.0, aroundUVOffset), vec2(aroundUVOffset, aroundUVOffset),             \n\
        vec2(-aroundUVOffset, 0.0), vec2(0.0, 0.0), vec2(aroundUVOffset, 0.0),                                              \n\
        vec2(-aroundUVOffset, -aroundUVOffset), vec2(0.0, -aroundUVOffset), vec2(aroundUVOffset, -aroundUVOffset)           \n\
    );                                                                              \n\
    float kernel[] = float[](                                                       \n\
        aroundKernel, aroundKernel, aroundKernel,                                   \n\
        aroundKernel, centerKernel, aroundKernel,                                   \n\
        aroundKernel, aroundKernel, aroundKernel                                    \n\
    );                                                                              \n\
                                                                                    \n\
    vec3 finalColor;                                                                \n\
    for (int i = 0; i < 9; ++i)                                                     \n\
    {                                                                               \n\
        vec3 offsetTexColor = vec3(texture(textureSampler, fragUV + kernelOffset[i]));  \n\
        finalColor += offsetTexColor * kernel[i];                                   \n\
    }                                                                               \n\
                                                                                    \n\
    outColor = vec4(finalColor, 1.0);                                               \n\
}                                                                                   \n\
";

constexpr const char g_blurFrag[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
\n\
in vec2 fragUV;                                                                     \n\
out vec4 outColor;                                                                  \n\
uniform sampler2D textureSampler;                                                   \n\
uniform float centerKernel = 4;                                                     \n\
uniform float aroundKernel = -1;                                                    \n\
uniform float aroundUVOffset = 1.0 / 300.0;                                         \n\
\n\
void main()                                                                         \n\
{                                                                                   \n\
    vec2 kernelOffset[] = vec2[](                                                   \n\
        vec2(-aroundUVOffset, aroundUVOffset), vec2(0.0, aroundUVOffset), vec2(aroundUVOffset, aroundUVOffset),             \n\
        vec2(-aroundUVOffset, 0.0), vec2(0.0, 0.0), vec2(aroundUVOffset, 0.0),                                              \n\
        vec2(-aroundUVOffset, -aroundUVOffset), vec2(0.0, -aroundUVOffset), vec2(aroundUVOffset, -aroundUVOffset)           \n\
    );                                                                              \n\
    float kernel[] = float[](                                                       \n\
        1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0,                                         \n\
        2.0 / 16.0, centerKernel / 16.0, 2.0 / 16.0,                                       \n\
        1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0                                          \n\
    );                                                                              \n\
                                                                                    \n\
    vec3 finalColor;                                                                \n\
    for (int i = 0; i < 9; ++i)                                                     \n\
    {                                                                               \n\
        vec3 offsetTexColor = vec3(texture(textureSampler, fragUV + kernelOffset[i]));  \n\
        finalColor += offsetTexColor * kernel[i];                                   \n\
    }                                                                               \n\
                                                                                    \n\
    outColor = vec4(finalColor, 1.0);                                               \n\
}                                                                                   \n\
";