#include "BaseComponent.h"
#include "../Object/Object.h"

OpenEngine::BaseComponent::BaseComponent(OpenEngine::Object & _obj) : object(_obj){}

void OpenEngine::BaseComponent::setObject(OpenEngine::Object & _obj)
{
    object = _obj;
    onAttach();
}