#include <iostream>

#include "ConcreteMessages.h"

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
