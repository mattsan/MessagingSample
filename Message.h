#ifndef MESSAGE_H
#define MESSAGE_H

#include <iosfwd>

class Receiver;

class Message
{
public:
	virtual ~Message();
	virtual void dispatch(Receiver& receiver) = 0;
	virtual void read(std::istream& in) = 0;
	virtual void write(std::ostream& out) const = 0;
};

std::istream& operator >> (std::istream& in, Message& message);
std::ostream& operator << (std::ostream& out, const Message& message);

#endif//MESSAGE_H
