/**
 * @file    BaseAudioImporter.h
 * @author  ggomdyu
 * @since   05/02/2018
 */

#pragma once
#include <cstdint>
#include <memory>

#include "Core/NonCopyable.h"

namespace tgon
{

template <typename _DerivedType>
class BaseAudioImporter :
    private NonCopyable
{
/**@section Constructor */
public:
    BaseAudioImporter() noexcept = default;
    BaseAudioImporter(const std::byte* fileData, std::size_t fileDataBytes);

/**@section Method */
public:
    static bool IsExactFormat(const std::byte* fileData, std::size_t fileDataBytes);
    bool Import(const std::byte* fileData, std::size_t fileDataBytes);
    bool IsValid() const noexcept;
    std::unique_ptr<std::byte[]>& GetAudioData() noexcept;
    const std::unique_ptr<std::byte[]>& GetAudioData() const noexcept;
    size_t GetAudioDataBytes() const noexcept;
    int32_t GetBitsPerSample() const noexcept;
    int32_t GetChannels() const noexcept;
    int32_t GetSamplingRate() const noexcept;

/**@section Variable */
protected:
    std::unique_ptr<std::byte[]> m_audioData;
    size_t m_audioDataBytes = 0;
    int32_t m_bitsPerSample = 0;
    int32_t m_channels = 0;
    int32_t m_samplingRate = 0;
};

template <typename _DerivedType>
inline BaseAudioImporter<_DerivedType>::BaseAudioImporter(const std::byte* fileData, std::size_t fileDataBytes) :
    BaseAudioImporter()
{
    this->Import(fileData, fileDataBytes);
}

template <typename _DerivedType>
inline bool BaseAudioImporter<_DerivedType>::Import(const std::byte* fileData, std::size_t fileDataBytes)
{
    return static_cast<_DerivedType*>(this)->Import(fileData, fileDataBytes);
}

template <typename _DerivedType>
inline bool BaseAudioImporter<_DerivedType>::IsValid() const noexcept
{
    return m_audioData != nullptr;
}

template <typename _DerivedType>
inline bool BaseAudioImporter<_DerivedType>::IsExactFormat(const std::byte* fileData, std::size_t fileDataBytes)
{
    return _DerivedType::IsExactFormat(fileData, fileDataBytes);
}

template <typename _DerivedType>
inline std::unique_ptr<std::byte[]>& BaseAudioImporter<_DerivedType>::GetAudioData() noexcept
{
    return m_audioData;
}

template <typename _DerivedType>
inline const std::unique_ptr<std::byte[]>& BaseAudioImporter<_DerivedType>::GetAudioData() const noexcept
{
    return m_audioData;
}

template <typename _DerivedType>
inline size_t BaseAudioImporter<_DerivedType>::GetAudioDataBytes() const noexcept
{
    return m_audioDataBytes;
}

template <typename _DerivedType>
inline int32_t BaseAudioImporter<_DerivedType>::GetBitsPerSample() const noexcept
{
    return m_bitsPerSample;
}

template <typename _DerivedType>
inline int32_t BaseAudioImporter<_DerivedType>::GetChannels() const noexcept
{
    return m_channels;
}

template <typename _DerivedType>
inline int32_t BaseAudioImporter<_DerivedType>::GetSamplingRate() const noexcept
{
    return m_samplingRate;
}

} /* namespace tgon */
