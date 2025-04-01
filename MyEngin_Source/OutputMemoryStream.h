#pragma once
#include "CommonInclude.h"
#include <cstdlib>
#include <cstdint>
#include "LinkingContext.h"
#include "pGameObject.h"
#include "ByteSwap.h"
#include "MemoryStream.h"

class OutputMemoryStream : public MemoryStream
{
public:
	OutputMemoryStream();

	~OutputMemoryStream();

	//get a pointer to the data in the stream
	const 	char*		GetBufferPtr()	const { return mBuffer; }
	uint32_t	GetLength()		const { return mHead; }

	void Write(const void* inData,	size_t inByteCount);
	template< typename T > void Write(T inData);
	void Write(const std::vector< int >& inIntVector);
	template< typename T >
	void Write(const std::vector< T >& inVector);
	void Write(const std::string& inString);
	void Write(const GameObject* inGameObject);

	virtual void Serialize(void* ioData, uint32_t inByteCount) {
		Write(ioData, inByteCount);
	}
	virtual bool IsInput() const { return true; }

private:
	void		ReallocBuffer(uint32_t inNewLength);

	char*		mBuffer;
	uint32_t	mHead;
	uint32_t	mCapacity;

	LinkingContext* mLinkingContext;
};
