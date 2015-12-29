#pragma once


// file operations compression
bool FileCompressor(const char * fileName, const char * dstFileName, float fErrorThreshold = 1.0f, bool extendedInfo = true);
// chunk file compressor. could be used for in-memory operations
bool ChunkFileCompressor(Engine2::CChunkFile& srcFile, Engine2::CChunkFile& dstFile, float fErrorThreshold = 1.0f, bool extendedInfo = true);
