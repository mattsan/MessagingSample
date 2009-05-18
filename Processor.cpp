#include "Processor.h"
#include "ConcreteMessages.h"

#include <iostream>

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
