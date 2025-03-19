#pragma once
#include "SocketInclude.h"
#include "SocketAddress.h"

class SocketAddressFactory
{
public:

	static SocketAddressPtr CreateIPv4FromString(const std::string& inString);
};