#ifndef RECEIVER_H
#define RECEIVER_H

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

#endif//RECEIVER_H
