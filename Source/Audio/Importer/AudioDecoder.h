/**
 * @file    AudioDecoder.h
 * @author  ggomdyu
 * @since   05/02/2018
 */

#pragma once
#include "Core/Object.h"

namespace tgon
{

class AudioDecoder :
    public Object
{
public:
    TGON_DECLARE_RTTI(AudioDecoder)
    
/**@section Constructor */
public:
    template <typename _SmartPointerType>
    AudioDecoder(_SmartPointerType&& audioData, int32_t audioDataBytes, int32_t bitsPerSample, int32_t channels, int32_t samplingRate) noexcept;
    
/**@section Method */
public:
    std::shared_ptr<std::byte[]> GetAudioData() noexcept;
    std::shared_ptr<const std::byte[]> GetAudioData() const noexcept;
    int32_t GetAudioDataBytes() const noexcept;
    int32_t GetBitsPerSample() const noexcept;
    int32_t GetChannels() const noexcept;
    int32_t GetSamplingRate() const noexcept;

/**@section Variable */
protected:
    std::shared_ptr<std::byte[]> m_audioData;
    int32_t m_audioDataBytes = 0;
    int32_t m_bitsPerSample = 0;
    int32_t m_channels = 0;
    int32_t m_samplingRate = 0;
};

template <typename _SmartPointerType>
inline AudioDecoder::AudioDecoder(_SmartPointerType&& audioData, int32_t audioDataBytes, int32_t bitsPerSample, int32_t channels, int32_t samplingRate) noexcept :
    m_audioData(std::forward<_SmartPointerType>(audioData)),
    m_audioDataBytes(audioDataBytes),
    m_bitsPerSample(bitsPerSample),
    m_channels(channels),
    m_samplingRate(samplingRate)
{
}

inline std::shared_ptr<std::byte[]> AudioDecoder::GetAudioData() noexcept
{
    return m_audioData;
}

inline std::shared_ptr<const std::byte[]> AudioDecoder::GetAudioData() const noexcept
{
    return m_audioData;
}

inline int32_t AudioDecoder::GetBitsPerSample() const noexcept
{
    return m_bitsPerSample;
}

inline int32_t AudioDecoder::GetChannels() const noexcept
{
    return m_channels;
}

inline int32_t AudioDecoder::GetSamplingRate() const noexcept
{
    return m_samplingRate;
}

} /* namespace tgon */
