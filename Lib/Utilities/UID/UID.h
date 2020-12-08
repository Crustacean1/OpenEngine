#ifndef UID_H
#define UID_H

#include <stdint.h>

namespace OpenEngine
{
    template<typename T>
    class UID
    {
        static uint64_t mainIndex;
        uint64_t index;

        UID& operator=(const UID & a){}  //
        UID(const UID& a){} // prevents copies

        public:
        UID() : index(mainIndex++){}
        uint64_t getId(){return index;}
        operator uint64_t() const {return index;}
    };
};
template<typename T>
uint64_t OpenEngine::UID<T>::mainIndex = 0;

#endif /*UID_H*/