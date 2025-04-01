#include "InputMemoryStream.h"


InputMemoryStream::InputMemoryStream(char* inBuffer, uint32_t inByteCount) :
	mBuffer(inBuffer), 
	mCapacity(inByteCount), 
	mHead(0),
	mLinkingContext(nullptr) 
	{}

InputMemoryStream::~InputMemoryStream() { 
	std::free(mBuffer); 
}

uint32_t InputMemoryStream::GetRemainingDataSize() const
{
	return mCapacity - mHead;
}


template< typename T > 
void InputMemoryStream::Read(T& outData)
{
	static_assert(std::is_arithmetic< T >::value ||
		std::is_enum< T >::value,
		"Generic Read only supports primitive data types");
	Read(&outData, sizeof(outData));
}

template< typename T >
void InputMemoryStream::Read(std::vector< T >& outVector)
{
	size_t elementCount;
	Read(elementCount);
	outVector.resize(elementCount);
	for (const T& element : outVector)
	{
		Read(element);
	}
}

void InputMemoryStream::Read(GameObject*& outGameObject)
{
	uint32_t networkId;
	Read(networkId);
	outGameObject = mLinkingContext->GetGameObject(networkId);
}

void InputMemoryStream::Read(void* outData, uint32_t inByteCount)
{
	uint32_t resultHead = mHead + inByteCount;
	if (resultHead > mCapacity)
	{
		//handle error, no data to read!
		//...
	}

	std::memcpy(outData, mBuffer + mHead, inByteCount);

	mHead = resultHead;
}