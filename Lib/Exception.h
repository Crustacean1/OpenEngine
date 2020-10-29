#ifndef EXCEPTION
#define EXCEPTION

#include <exception>
#include <string>

namespace OpenEngine
{
    class DevException : protected std::exception
    {
        std::string msg;
        public:
        DevException(std::string _str) : msg(_str){}
        virtual const char * what() const throw()
        {
            return msg.c_str();
        }
    };
}; // namespace OpenEngine

#endif /*EXCEPTION*/