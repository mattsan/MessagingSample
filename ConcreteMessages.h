#ifndef CONCRETE_MESSAGES_H
#define CONCRETE_MESSAGES_H

#include "Message.h"
#include "Receiver.h"

template<typename T>
class DispatchableMessage : public Message
{
public:
	static Message* create()
	{
		return new T;
	}

	void dispatch(Receiver& receiver)
	{
		receiver.received(static_cast<T&>(*this));
	}
};

class Foo : public DispatchableMessage<Foo>
{
public:
	explicit Foo(int x = 0, int y = 0);
	void read(std::istream& in);
	void write(std::ostream& out) const;

	int x() const;
	int y() const;

private:
	int x_;
	int y_;
};

class Bar : public DispatchableMessage<Bar>
{
public:
	explicit Bar(int x = 0, int y = 0, int z = 0);
	void read(std::istream& in);
	void write(std::ostream& out) const;

	int x() const;
	int y() const;
	int z() const;

private:
	int x_;
	int y_;
	int z_;
};

class Baz : public DispatchableMessage<Baz>
{
public:
	explicit Baz(double distance = 0, double angle = 0);
	void read(std::istream& in);
	void write(std::ostream& out) const;

	double distance() const;
	double angle() const;

private:
	double distance_;
	double angle_;
};

#endif//CONCRETE_MESSAGES_H
