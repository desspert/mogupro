#pragma once
#include <winsock2.h>

namespace Network
{
bool exportInt(int& value, char* const buffer, int& offset, int totalSize);
bool importInt(int& value, const char* const buffer, int& offset, int totalSize);

bool exportUInt(unsigned int& value, char* const buffer, int& offset, int totalSize);
bool importUInt(unsigned int& value, const char* const buffer, int& offset, int totalSize);

bool importChar(char& value, const char* const buffer, int& offset, int totalSize);
bool exportChar(char& value, char* const buffer, int& offset, int totalSize);

bool importShort(short& value, const char* const buffer, int& offset, int totalSize);
bool exportShort(short& value, char* const buffer, int& offset, int totalSize);

bool importStr(char& value, const char* const buffer, int& offset, int totalSize);
bool exportStr(char* value, char* const buffer, int& offset, int totalSize, size_t valueSize);
bool importStr(char* value, const char* const buffer, int& offset, int totalSize, size_t valueSize);

//!@ LookMe : Floatに対するhtonl,ntohlはできないのでどうするか
bool exportFloat(const float& value, char* const buffer, int& offset, int totalSize);
bool importFloat(float& value, const char* const buffer, int& offset, int totalSize);
}