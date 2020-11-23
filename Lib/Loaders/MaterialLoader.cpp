#include "MaterialLoader.h"
#include "../Material/Material.h"
#include <iostream>
#include <fstream>


std::map<std::string,OpenEngine::Material*> OpenEngine::MaterialLoader::loadMaterial(const char * filename)
{
    std::ifstream file(filename);
    Material * currentMaterial;
    std::map<std::string,Material *> materials;
    std::string buff;

    float r,g,b;
    while(file>>buff)
    {
        if(buff=="newmtl")
        {
            file>>buff;
            materials[buff] = currentMaterial = new Material();
        }
        else if(buff=="Ns")
        {
            file>>currentMaterial->shininess;
        }
        else if(buff=="Ka")
        {
            file>>r>>g>>b;
            currentMaterial->amb.createFromColor(r*255,g*255,b*255);
        }
        else if(buff=="Kd")
        {
            file>>r>>g>>b;
            currentMaterial->diff.createFromColor(r*255,g*255,b*255);
        }
        else if(buff=="Ks")
        {
            file>>r>>g>>b;
            currentMaterial->spec.createFromColor(r*255,g*255,b*255);
        }
        else if(buff=="map_Ka")
        {
            file>>buff;
            currentMaterial->amb.loadFromFile(buff);   
        }
        else if(buff=="map_Kd")
        {
            file>>buff;
            currentMaterial->diff.loadFromFile(buff);
        }
        else if(buff=="map_Bump")
        {
            file>>buff;
            currentMaterial->norm.loadFromFile(buff);
        }
        else if(buff=="map_Ks")
        {
            file>>buff;
            currentMaterial->spec.loadFromFile(buff);
        }
        else
        {
        }
    }
    return materials;
}