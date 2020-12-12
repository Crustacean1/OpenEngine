#include "ResourceManager.h"
#include <iostream>

std::map<std::string, std::map<std::string, std::shared_ptr<void>>> OpenEngine::ResourceManager::resources;

void OpenEngine::ResourceManager::confess()
{
    for(auto type : resources)
    {
        for(auto res : type.second)
        {
            std::cout<<type.first<< "  "<<res.first<<std::endl;
        }
    }
}