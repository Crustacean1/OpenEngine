#include "ComponentManager.h"

template <typename T,typename M>
std::map<unsigned int, OpenEngine::ComponentManager<T,M> *> OpenEngine::ComponentManager<T,M>::managers;

template<typename T,typename M>
unsigned int OpenEngine::ComponentManager<T,M>::mainIndex = 0;