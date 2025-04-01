#pragma once
#include <cstdint>
#include "CommonInclude.h"
#include <cstdlib>
#include "ByteSwap.h"
#define STREAM_ENDIANNESS 0
#define PLATFORM_ENDIANNESS 0

class MemoryStream
{
	virtual void Serialize(void* ioData, uint32_t inByteCount)=0;
	virtual bool IsInput() const = 0;
	template<typename T> 
	void Serialize(T& ioData);
};


