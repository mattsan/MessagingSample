#include "ConcreteMessages.h"
#include "Processor.h"
#include "Factory.h"

#include <iostream>
#include <string>

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
