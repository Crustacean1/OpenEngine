#include "Cellular.h"
#include <ctime>
#include <stdlib.h>
#include "../../Lib/Mesh/Mesh.h"
#include "../../Lib/Material/Material.h"
#include "../../Lib/Render/MeshRenderer.h"
#include "../../Lib/Render/Render.h"
#include "../../Lib/Object/Object.h"
#include <iostream>

void Labirynth::fill()
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < depth; j++)
        {
            grid1[depth * i + j] = ((rand() % 1000) > ((1 - probability) * 1000));
        }
    }
}
void Labirynth::iterate(int degree)
{
    char *g1, *g2;
    g1 = (degree % 2) ? grid2 : grid1;
    g2 = (!(degree % 2)) ? grid2 : grid1;
    int count;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < depth; j++)
        {
            count = 0;
            for (int a = std::max(0, i - 1); a < std::min(i + 2, (int)width); a++)
            {
                for (int b = std::max(0, j - 1); b < std::min(j + 2, (int)depth); b++)
                {
                    if(a==i&&b==j){continue;}
                    count += (g1[a*depth+b]==1);
                }
            }
            g2[i*depth+j] = (g1[i*depth+j]&((count<6)&(count>1))|(!g1[i*depth+j]&((count>5))));
        }
    }
}
void Labirynth::instantiate(int degree)
{
    char * ptr = (degree%2) ? grid2 : grid1;
    auto renderer = object.getComponent<OpenEngine::MeshRenderer>(0);
    auto mesh  = OpenEngine::SimpleMesh<OpenEngine::Vertex3pntxy,OpenEngine::V3Index>::generateCuboid(0.5,1,0.5);
    for(int i = 0;i<width;i++)
    {
        for(int j = 0;j<depth;j++)
        {
            if(!ptr[i*depth+j]){continue;}
            auto child = new OpenEngine::Object(object);
            child->addComponent<OpenEngine::MeshRenderer>()->setMesh(mesh,mat);
            child->transform.localPosition = glm::dquat(0,scale*i,1,scale*j);
        }
    }
    object.transform.flushTransform();
}
void Labirynth::init()
{
    grid1 = new char[width * depth];
    grid2 = new char[width * depth];
    fill();
    //debug(grid1);
    std::cout<<std::endl;
    for(int i = 0;i<iterations;i++)
    {
        iterate(i);
        //debug(grid1);
        //std::cout<<std::endl;
    }
    instantiate(iterations);
    //debug(grid2);
}
void Labirynth::debug(char * ptr)
{
    for(int i = 0;i<width;i++)
    {
        for(int j = 0;j<depth;j++)
        {
            std::cout<<(int)ptr[i*depth+j]<<" ";
        }
        std::cout<<std::endl;
    }
}