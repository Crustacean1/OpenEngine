#include "Object.h"

std::string OpenEngine::Object::mainIndex = "\0";

std::string OpenEngine::Object::incrementIndex(std::string & index)
{
    unsigned int sum = 1;
    for(unsigned int i = 0;i<index.size()&&sum!=0;i++)
    {
        sum+=index[i];
        index[i] = sum&255;
        sum = sum>>8;
    }
    if(sum)
    {
        index+=(char)0;
    }
    return index;
}

OpenEngine::Object::Object(std::shared_ptr<Object> _parent) : parent(_parent)
{

}
std::string OpenEngine::Object::getId() const
{
    return index;
}
