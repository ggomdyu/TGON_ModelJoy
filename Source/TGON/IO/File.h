/**
 * @file    File.h
 * @author  ggomdyu
 * @since   07/14/2019
 */

#pragma once
#include <string_view>
#include <optional>

#include "Platform/Config.h"
#include "String/Encoding.h"
#include "Time/DateTime.h"

#include "FileStream.h"

namespace tgon
{
 
enum class FileAttributes
{
    Archive = 0x20,
    Compressed = 0x800,
    Device = 0x40,
    Directory = 0x10,
    Encrypted = 0x4000,
    Hidden = 0x2,
    IntegrityStream = 0x8000,
    Normal = 0x80,
    NoScrubData = 0x20000,
    NotContentIndexed = 0x2000,
    Offline = 0x1000,
    ReadOnly = 0x1,
    ReparsePoint = 0x400,
    SparseFile = 0x200,
    System = 0x4,
    Temporary = 0x100
};

class TGON_API File
{
/**@section Constructor */
public:
    File() = delete;

/**@section Method */
public:
    static bool Copy(const std::string_view& srcPath, const std::string_view& destPath);
    static bool Copy(const std::string_view& srcPath, const std::string_view& destPath, bool overwrite);
    static bool Delete(const std::string_view& path);
    static bool Exists(const std::string_view& path);
    static bool Move(const std::string_view& srcPath, const std::string_view& destPath);
    static bool SetCreationTime(const std::string_view& path, const DateTime& creationTime);
    static bool SetCreationTimeUtc(const std::string_view& path, const DateTime& creationTimeUtc);
    static bool SetLastAccessTime(const std::string_view& path, const DateTime& lastAccessTime);
    static bool SetLastAccessTimeUtc(const std::string_view& path, const DateTime& lastAccessTimeUtc);
    static bool SetLastWriteTime(const std::string_view& path, const DateTime& lastWriteTime);
    static bool SetLastWriteTimeUtc(const std::string_view& path, const DateTime& lastWriteTimeUtc);
    static std::optional<DateTime> GetCreationTime(const std::string_view& path);
    static std::optional<DateTime> GetCreationTimeUtc(const std::string_view& path);
    static std::optional<DateTime> GetLastAccessTime(const std::string_view& path);
    static std::optional<DateTime> GetLastAccessTimeUtc(const std::string_view& path);
    static std::optional<DateTime> GetLastWriteTime(const std::string_view& path);
    static std::optional<DateTime> GetLastWriteTimeUtc(const std::string_view& path);
    static std::optional<FileAttributes> GetAttributes(const std::string_view& path);
    static bool Decrypt(const std::string_view& path);
    static bool Encrypt(const std::string_view& path);
    static std::string ReadAllText(const std::string_view& path);
    static std::string ReadAllText(const std::string_view& path, const Encoding& encoding);
    static std::optional<std::vector<std::byte>> ReadAllBytes(const std::string_view& path);
    static FileStream Create(const std::string_view& path);
    static FileStream Create(const std::string_view& path, int32_t bufferSize);
    static FileStream Create(const std::string_view& path, int32_t bufferSize, FileOptions options);
    static FileStream Open(const std::string_view& path, FileMode mode);
    static FileStream Open(const std::string_view& path, FileMode mode, FileAccess access);
    static FileStream Open(const std::string_view& path, FileMode mode, FileAccess access, FileShare share);

    //static void SetAttributes(const std::string_view& path, FileAttributes fileAttributes);
    //static void AppendAllLines(const std::string_view& path, IEnumerable<string> contents);
    //static void AppendAllLines(const std::string_view& path, IEnumerable<string> contents, Encoding encoding);
    //static Task AppendAllLinesAsync(const std::string_view& path, IEnumerable<string> contents, CancellationToken cancellationToken = default(CancellationToken));
    //static Task AppendAllLinesAsync(const std::string_view& path, IEnumerable<string> contents, Encoding encoding, CancellationToken cancellationToken = default(CancellationToken));
    //static void AppendAllText(const std::string_view& path, string contents);
    //static void AppendAllText(const std::string_view& path, string contents, Encoding encoding);
    //static Task AppendAllTextAsync(const std::string_view& path, string contents, CancellationToken cancellationToken = default(CancellationToken));
    //static Task AppendAllTextAsync(const std::string_view& path, string contents, Encoding encoding, CancellationToken cancellationToken = default(CancellationToken));
    //static StreamWriter AppendText(const std::string_view& path);
    
    //static StreamWriter CreateText(const std::string_view& path);
    //static FileStream OpenRead(const std::string_view& path);
    //static StreamReader OpenText(const std::string_view& path);
    //static FileStream OpenWrite(const std::string_view& path);
    //static string[] ReadAllLines(const std::string_view& path);
    //static string[] ReadAllLines(const std::string_view& path, Encoding encoding);
    
    //static IEnumerable<string> ReadLines(const std::string_view& path);
    //static IEnumerable<string> ReadLines(const std::string_view& path, Encoding encoding);
    //static void Replace(const std::string_view& sourcePath, string destinationPath, string destinationBackupPath);
    //static void Replace(const std::string_view& sourcePath, string destinationPath, string destinationBackupPath, bool ignoreMetadataErrors);
    //static void WriteAllBytes(const std::string_view& path, byte[] bytes);
    //static void WriteAllLines(const std::string_view& path, string[] contents);
    //static void WriteAllLines(const std::string_view& path, IEnumerable<string> contents);
    //static void WriteAllLines(const std::string_view& path, string[] contents, Encoding encoding);
    //static void WriteAllLines(const std::string_view& path, IEnumerable<string> contents, Encoding encoding);
    //static void WriteAllText(const std::string_view& path, string contents);
    //static void WriteAllText(const std::string_view& path, string contents, Encoding encoding);
};

} /* namespace tgon */
