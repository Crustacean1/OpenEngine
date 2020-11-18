#include "Uniform.h"

template<typename T>
std::string OpenEngine::Uniform<T>::__basename = T::basename;

template<typename T>
unsigned int OpenEngine::Uniform<T>::__maxUniformsCount = T::maxUniformsCount;

template<typename T>
T * OpenEngine::Uniform<T>::__uniforms[5];

template<typename T>
unsigned int OpenEngine::Uniform<T>::__uniformsCount = 0;