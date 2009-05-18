#include <iostream>

#include "Message.h"

Message::~Message()
{
}

std::istream& operator >> (std::istream& in, Message& message)
{
	message.read(in);
	return in;
}

std::ostream& operator << (std::ostream& out, const Message& message)
{
	message.write(out);
	return out;
}
