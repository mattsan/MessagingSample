#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iosfwd>

#include "Receiver.h"

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

#endif//PROCESSOR_H
