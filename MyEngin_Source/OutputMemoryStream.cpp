#include "OutputMemoryStream.h"
OutputMemoryStream::OutputMemoryStream() :
	mLinkingContext(nullptr)
{
	ReallocBuffer(32);
}
OutputMemoryStream::~OutputMemoryStream() {
	std::free(mBuffer);
}

template< typename T > 
void OutputMemoryStream::Write(T inData)
{
	static_assert(std::is_arithmetic< T >::value ||
		std::is_enum< T >::value,
		"Generic Write only supports primitive data types");

	if (STREAM_ENDIANNESS == PLATFORM_ENDIANNESS)
	{
		Write(&inData, sizeof(inData));
	}
	else
	{
		T swappedData = ByteSwap(inData);
		Write(&swappedData, sizeof(swappedData));
	}

}

void OutputMemoryStream::Write(const void* inData,	size_t inByteCount)
{
	//make sure we have space...
	uint32_t resultHead = mHead + static_cast<uint32_t>(inByteCount);
	if (resultHead > mCapacity)
	{
		ReallocBuffer(max(mCapacity * 2, resultHead));
	}

	//copy into buffer at head
	std::memcpy(mBuffer + mHead, inData, inByteCount);

	//increment head for next write
	mHead = resultHead;
}

void OutputMemoryStream::Write(const std::vector< int >& inIntVector)
{
	size_t elementCount = inIntVector.size();
	Write(elementCount);
	Write(inIntVector.data(), elementCount * sizeof(int));
}

template< typename T >
void OutputMemoryStream::Write(const std::vector< T >& inVector)
{
	uint32_t elementCount = inVector.size();
	Write(elementCount);
	for (const T& element : inVector)
	{
		Write(element);
	}
}

void OutputMemoryStream::Write(const std::string& inString)
{
	size_t elementCount = inString.size();
	Write(elementCount);
	Write(inString.data(), elementCount * sizeof(char));
}

void OutputMemoryStream::Write(const GameObject* inGameObject)
{
	uint32_t networkId = mLinkingContext->GetNetworkId(const_cast<GameObject*>(inGameObject), false);
	Write(networkId);
}

void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
	mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
	//handle realloc failure
	//...
	mCapacity = inNewLength;
}