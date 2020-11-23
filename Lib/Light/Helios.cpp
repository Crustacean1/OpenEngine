#include "Helios.h"
#include "../Light/Light.h"
#include "../Camera/Camera.h"
//#include <iostream>
void OpenEngine::Helios::illuminate(Camera * cam)
{
    //std::cout<<"illuminating"<<components[0]-><<"\n";
    glm::vec4 lPos;
    for(auto & component : components)
    {
        component->illuminate(cam->getViewMatrix(component->object.getGlobalPosition(),
                                  component->object.getGlobalRotation(),
                                  component->object.getGlobalScale()));
    }
}