//-----------------------------------------------------------------------
//  Message.h

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

//-----------------------------------------------------------------------
//  Receiver.h

class Foo;
class Bar;
class Baz;

class Receiver
{
public:
	virtual void received(const Foo& foo) = 0;
	virtual void received(const Bar& bar) = 0;
	virtual void received(const Baz& baz) = 0;
};

//-----------------------------------------------------------------------
//  DispatchableMessage.h

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

//-----------------------------------------------------------------------
//  ConcreteMessages.h

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

//-----------------------------------------------------------------------
//  Processor.h

class Processor : public Receiver
{
public:
	explicit Processor(std::ostream& out);

	void received(const Foo& foo);
	void received(const Bar& bar);
	void received(const Baz& baz);

private:
	std::ostream& out_;
};

//-----------------------------------------------------------------------
//  Message.cpp

#include <iostream>

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

//-----------------------------------------------------------------------
//  ConcreteMessages.cpp

Foo::Foo(int x, int y) : x_(x), y_(y)
{
}

void Foo::read(std::istream& in)
{
	in >> x_ >> y_;
}

void Foo::write(std::ostream& out) const
{
	out << "Foo" << ' ' << x_ << ' ' << y_ << ' ';
}

int Foo::x() const
{
	return x_;
}

int Foo::y() const
{
	return y_;
}

Bar::Bar(int x, int y, int z) : x_(x), y_(y), z_(z)
{
}

void Bar::read(std::istream& in)
{
	in >> x_ >> y_ >> z_;
}

void Bar::write(std::ostream& out) const
{
	out << "Bar" << ' ' << x_ << ' ' << y_ << ' ' << z_ << ' ';
}

int Bar::x() const
{
	return x_;
}

int Bar::y() const
{
	return y_;
}

int Bar::z() const
{
	return z_;
}

Baz::Baz(double distance, double angle) : distance_(distance), angle_(angle)
{
}

void Baz::read(std::istream& in)
{
	in >> distance_ >> angle_;
}

void Baz::write(std::ostream& out) const
{
	out << "Baz" << ' ' << distance_ << ' ' << angle_ << ' ';
}

Processor::Processor(std::ostream& out) : out_(out)
{
}

void Processor::received(const Foo& foo)
{
	out_ << foo << '\n';
}

void Processor::received(const Bar& bar)
{
	out_ << bar << '\n';
}

void Processor::received(const Baz& baz)
{
	out_ << baz << '\n';
}

//-----------------------------------------------------------------------
//  Factory.h

#include <map>
#include <string>

typedef Message* (*creator_func_type)();
typedef std::map<std::string, creator_func_type> Creators;

//-----------------------------------------------------------------------
//  Main.cpp

int main(int, char*[])
{
	Processor processor(std::cout);

	Creators creators;
	creators.insert(Creators::value_type("Foo", Foo::create));
	creators.insert(Creators::value_type("Bar", Bar::create));
	creators.insert(Creators::value_type("Baz", Baz::create));

	std::string id;

	while(std::cin >> id)
	{
		Creators::const_iterator i = creators.find(id);
		if(i != creators.end())
		{
			Message* message = i->second();
			std::cin >> *message;
			message->dispatch(processor);
			delete message;
		}
		else
		{
			std::cout << "UNKNOWN ID : " << id << "\n";
		}
	}

	return 0;
}
