#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <string>

typedef Message* (*creator_func_type)();
typedef std::map<std::string, creator_func_type> Creators;

#endif//FACTORY_H
