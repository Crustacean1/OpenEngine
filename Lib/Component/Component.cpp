#include "Component.h"
#include "ComponentFactory.h"
#include "../Object/Object.h"

OpenEngine::Component::~Component()
{
    factory.drop(this);
}
OpenEngine::Component::Component(Object & _obj,ComponentFactory<Component> & _fact) : object(_obj),factory(_fact)
{

}