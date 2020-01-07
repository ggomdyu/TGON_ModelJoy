/**
 * @file    FileStream.h
 * @author  ggomdyu
 * @since   08/04/2019
 * @see     https://referencesource.microsoft.com/#mscorlib/system/io/filestream.cs
 */

#pragma once
#include <vector>
#include <string>

#include "Stream.h"

namespace tgon
{

enum class FileMode
{
    CreateNew = 1,
    Create = 2,
    Open = 3,
    OpenOrCreate = 4,
    Truncate = 5,
    Append = 6,
};

enum class FileAccess
{
    Read = 1,
    Write = 2,
    ReadWrite = 3
};

enum class FileShare
{
    None = 0,
    Read = 1,
    Write = 2,
    ReadWrite = 3,
    Delete = 4,
    Inheritable = 16
};

enum class FileOptions
{
    WriteThrough = std::numeric_limits<int>::min(),
    None = 0,
    Encrypted = 16384,
    DeleteOnClose = 67108864,
    SequentialScan = 134217728,
    RandomAccess = 268435456,
    Asynchronous = 1073741824
};

class FileStream :
    public Stream
{
/**@section Constructor */
public:
    FileStream(const char* path, FileMode mode);
    FileStream(const char* path, FileMode mode, FileAccess access);
    FileStream(const char* path, FileMode mode, FileAccess access, FileShare share);
    FileStream(const char* path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize);
    FileStream(const char* path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize, FileOptions options);
    FileStream(FileStream&& rhs) noexcept;

/**@section Destructor */
public:
    ~FileStream() override;
    
/**@section Operator */
public:
    FileStream& operator=(FileStream&& rhs) noexcept;
    bool operator==(const FileStream& rhs) const noexcept;
    bool operator!=(const FileStream& rhs) const noexcept;

/**@section Method */
public:
    bool CanRead() const override;
    bool CanSeek() const override;
    bool CanWrite() const override;
    bool SetLength(int64_t value) override;
    int64_t Length() const override;
    int64_t Position() const override;
    int32_t Read(std::byte* buffer, int32_t count) override;
    int32_t ReadByte() override;
    bool Write(const std::byte* buffer, int32_t count) override;
    bool WriteByte(std::byte value) override;
    int64_t Seek(int64_t offset, SeekOrigin origin) override;
    void Close() override;
    const std::string& Name() const noexcept;
    void Flush() override;
    void Flush(bool flushToDisk);
    bool IsClosed() const noexcept;
    
protected:
    std::vector<std::byte>& GetBuffer() noexcept;
    void FlushWriteBuffer();
    void FlushReadBuffer();
    int32_t InternalRead(std::byte* buffer, int32_t count);
    int32_t InternalWrite(const std::byte* buffer, int32_t count);
    int64_t InternalSeek(int64_t offset, SeekOrigin origin);
    void InternalFlush();
    bool InternalSetLength(int64_t value);

/**@section Variable */
protected:
    static constexpr FileShare DefaultShare = FileShare::Read;
    static constexpr FileOptions DefaultFileOption = FileOptions::None;
    static constexpr int DefaultBufferSize = 4096;

    void* m_nativeHandle;
    std::vector<std::byte> m_buffer;
    int32_t m_bufferSize;
    int32_t m_readPos;
    int32_t m_readLen;
    int32_t m_writePos;
    int64_t m_filePos;
    FileAccess m_access;
    std::string m_fileName;    
};

} /* namespace tgon */