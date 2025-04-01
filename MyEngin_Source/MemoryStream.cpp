#include "MemoryStream.h"
template<typename T>
void MemoryStream::Serialize(T & ioData)
{
	static_assert(
		std::is_arithmetic<T>::value || std::is_enum<T>::value,
		"Generic Serialize only supports primitive data types");

	if (STREAM_ENDIANNESS == PLATFORM_ENDIANNESS)
		Serialize(&ioData, sizeof(ioData));
	else {
		if (IsInput()) {
			T data;
			Serialize(&data, sizeof(T));
			ioData = ByteSwap(data);
		}
		else {
			T swappedData = ByteSwap(ioData);
			Serialize(&swappedData, sizeof(swappedData));
		}
	}
}