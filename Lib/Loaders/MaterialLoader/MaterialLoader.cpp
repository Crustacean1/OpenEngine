#include "../../Material/Material.h"
#include "MaterialLoader.h"
#include "../TextureLoader/TextureLoader.h"
#include <iostream>
#include <fstream>

std::string getBasename(std::string a)
{
    if(-a.find_last_of("/")==std::string::npos){return a;}
    return a.substr(0,a.find_last_of("/")+1);
}

std::map<std::string,OpenEngine::Material3D*> OpenEngine::MaterialLoader::load(std::string filename)
{
    std::ifstream file(filename);
    Material3D * currentMaterial;
    std::map<std::string,Material3D *> materials;
    std::string dirname = getBasename(filename);
    std::string buff;

    float r,g,b;
    while(file>>buff)
    {
        if(buff=="newmtl")
        {
            file>>buff;
            materials[buff] = currentMaterial = new Material3D();
        }
        else if(buff=="Ns")
        {
            file>>currentMaterial->shininess;
        }
        else if(buff=="Ka")
        {
            file>>r>>g>>b;
            currentMaterial->amb->createFromColor(r*255,g*255,b*255);
        }
        else if(buff=="Kd")
        {
            file>>r>>g>>b;
            currentMaterial->diff->createFromColor(r*255,g*255,b*255);
        }
        else if(buff=="Ks")
        {
            file>>r>>g>>b;
            currentMaterial->spec->createFromColor(r*255,g*255,b*255);
        }
        else if(buff=="map_Ka")
        {
            file>>buff;
            currentMaterial->amb = TextureLoader::getInstance()->load(dirname+buff);
        }
        else if(buff=="map_Kd")
        {
            file>>buff;
            currentMaterial->diff = TextureLoader::getInstance()->load(dirname+buff);
        }
        else if(buff=="map_Bump")
        {
            file>>buff;
            currentMaterial->norm = TextureLoader::getInstance()->load(dirname+buff);
        }
        else if(buff=="map_Ks")
        {
            file>>buff;
            currentMaterial->spec = TextureLoader::getInstance()->load(dirname+buff);
        }
        else
        {
        }
    }
    return materials;
}