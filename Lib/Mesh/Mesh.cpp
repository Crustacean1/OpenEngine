#include "Mesh.h"

void OpenEngine::Mesh::generatePlane(unsigned int resolution,float size)
{
    vertices.setBuffer(resolution*resolution);
    indices.setBuffer((resolution-1)*(resolution-1)*2);
    auto _ind = indices.getData().get();
    auto _vert = vertices.getData().get();
    for(unsigned int i = 0,k =0;i+1<resolution;i++)
    {
        for(unsigned int j = 0;j+1<resolution;j++)
        {
            _ind[k++].set(i*resolution+j,i*resolution+j+1,(i+1)*resolution+j);
            _ind[k++].set((i+1)*(resolution)+j+1,i*resolution+j+1,(i+1)*resolution+j);
        }
    }
    for(int i = 0,k = 0;i<resolution;i++)
    {
        for(int j = 0;j<resolution;j++)
        {
            _vert[k++].pos = glm::vec3(-size+(float)2*size*i/(resolution-1),-size+(float)2*size*j/(resolution-1),-1);
        }
    }
    vertices.flush();
    indices.flush();
    vao.swapBuffer(vertices);
    vao.swapBuffer(indices);
}
OpenEngine::Mesh::Mesh(){}