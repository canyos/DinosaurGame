#pragma once
#include "CommonInclude.h"
#include <cstdlib>
#include <cstdint>
#include "LinkingContext.h"
#include "pGameObject.h"
#include "ByteSwap.h"
#include "MemoryStream.h"



class InputMemoryStream : public MemoryStream
{
public:
	InputMemoryStream(char* inBuffer, uint32_t inByteCount);

	~InputMemoryStream();

	uint32_t GetRemainingDataSize() const;

	void Read(void* outData, uint32_t inByteCount);
	template< typename T > 
	void Read(T& outData);
	template< typename T >
	void Read(std::vector< T >& outVector);
	void Read(GameObject*& outGameObject);

	virtual void Serialize(void* ioData, uint32_t inByteCount) {
		Read(ioData, inByteCount);
	}
	virtual bool IsInput() const { return true; }

private:
	char*		mBuffer;
	uint32_t	mHead;
	uint32_t	mCapacity;

	LinkingContext* mLinkingContext;
};