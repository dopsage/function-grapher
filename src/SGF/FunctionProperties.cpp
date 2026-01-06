
#include "SGF/FunctionProperties.hpp"

using namespace sgf;

FunctionProperties::FunctionProperties() :
                    FunctionProperties(L"")
{
    
}

FunctionProperties::FunctionProperties(std::wstring definition)
{
    this->definition = definition;
}

FunctionProperties::FunctionProperties(const FunctionProperties& other) :
                    FunctionProperties(other.definition)
{
    
}
