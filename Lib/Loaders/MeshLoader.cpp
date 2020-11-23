#include "MeshLoader.h"

#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include "../Mesh/Mesh.h"

using namespace OpenEngine;

float tempfloat1, tempfloat2; //global veriable for performance, used as buffer
bool tempsign1;
inline float toFloat(char **ptr)
{
    tempfloat1 = 0;
    tempsign1 = (**ptr == '-');
    (*ptr) += tempsign1;
    while (**ptr > '/')
    {
        tempfloat1 *= 10;
        tempfloat1 += **ptr - '0';
        (*ptr)++;
    }
    if (**ptr != '.')
    {
        return tempfloat1;
    }
    tempfloat2 = 0.1f;
    (*ptr)++;
    while (**ptr > '/' && **ptr < ':')
    {
        tempfloat1 += tempfloat2 * (**ptr - '0');
        tempfloat2 /= 10;
        (*ptr)++;
    }
    tempfloat1 *= (1 - (**ptr == 'e'));
    while (**ptr > ' ')
    {
        (*ptr)++;
    }
    return tempfloat1 * (1 - 2 * tempsign1);
}
unsigned int tempunsigned1;
inline unsigned int toUnsigned(char **ptr)
{
    while (**ptr < '-')
    {
        (*ptr)++;
    }
    tempunsigned1 = 0;
    while (**ptr > '/')
    {
        tempunsigned1 *= 10;
        tempunsigned1 += **ptr - '0';
        (*ptr)++;
    }
    return tempunsigned1;
}

bool MeshLoader::toNextNum(char **ptr)
{
    while (**ptr < '-'&&(*ptr)<end&&**ptr!='\n')
    {
        (*ptr)++;
    }
    if (**ptr == '\\')
    {
        (*ptr)++;
        while (**ptr < '-'&&(*ptr)<end)
        {
            (*ptr)++;
        }
    }
    return (!(**ptr > '9'))&((*ptr)<end)&(**ptr!='\n');
}
void MeshLoader::countVertices(unsigned int &a, unsigned int &b, unsigned int &c, unsigned int &d, unsigned int &e)
{
    a = b = c = d = e = 0;
    char *ptr = data;
    unsigned int primitiveCount;
    while (ptr < end)
    {
        switch (*ptr)
        {
        case '#':
            break;
        case 'v':
            switch (*(ptr + 1))
            {
            case ' ':
                a++;
                break;
            case 't':
                b++;
                break;
            case 'n':
                c++;
                break;
            }
            break;
        case 'f':
            primitiveCount = 0;
            while (*ptr!='\n'&&ptr<end)
            {
                ptr += 2*(*ptr=='\\');
                primitiveCount += (*ptr == '/');
                ptr++;
            }
            d += ((primitiveCount / 2) - 2) * 3;
            break;
        case 'g':
            e++;
            break;
        default:
            break;
        }
        while (*ptr!='\n'&&ptr<end){ptr++;}
        ptr++;
    }
}

void MeshLoader::loadVerticesData(char **ptr, float **target,char size)
{
    if (!toNextNum(ptr))
    {
        return;
    }
    while (toNextNum(ptr))
    {
        **target = toFloat(ptr);
        (*target)+=(size-->0);
    }
}
glm::uvec3 MeshLoader::loadIndice(char **ptr)
{
    glm::uvec3 ind;
    ind[0] = toUnsigned(ptr);
    (*ptr)++;
    ind[1] = toUnsigned(ptr);
    (*ptr)++;
    ind[2] = toUnsigned(ptr);
    while(*ptr<end&&**ptr>' '){(*ptr)++;}
    return ind;
}
int cnt = 0;
void MeshLoader::loadIndicesData(char **ptr, glm::uvec3 **ind)
{
    if (!toNextNum(ptr))
    {
        return;
    }
    glm::uvec3 base = loadIndice(ptr);
    if (!toNextNum(ptr))
    {
        return;
    }
    glm::uvec3 prev = loadIndice(ptr);
    while (toNextNum(ptr))
    {
        cnt+=3;
        *((*ind)++) = base;
        *((*ind)++) = prev;
        prev = *((*ind)++) = loadIndice(ptr);
    }
}
void MeshLoader::loadMeshData(float *pos, float *tex, float *norm, glm::uvec3 *ind)
{
    char *ptr = data;
    char * end = data+dataLength;
    int over = 0;
    while (ptr <end)
    {
        switch (*(ptr++))
        {
        case 'v':
            switch (*(ptr++))
            {
            case ' ':
                loadVerticesData(&ptr, &pos,3);
                break;
            case 't':
                ptr++;
                loadVerticesData(&ptr, &tex,2);
                break;
            case 'n':
                ptr++;
                loadVerticesData(&ptr, &norm,3);
                break;
            }
            break;
        case 'f':
            loadIndicesData(&ptr, &ind);
            break;
        }
        while (*ptr !='\n' && ptr<end)
        {
            ++ptr;
        };
        ++ptr;
    }
    std::cout<<over<<std::endl;
    std::cout<<"ended on: "<<(int)(ptr-data)<<" "<<dataLength<<std::endl;
}

void MeshLoader::loadData(const char *filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        return;
    }
    file.seekg(0, file.end);
    dataLength = file.tellg();
    file.seekg(0, file.beg);
    data = new char[dataLength + 1];
    file.read(data, dataLength);
    data[dataLength] = 0;
    end = data+dataLength+1;
}
unsigned int MeshLoader::createMap(std::map<unsigned int, std::map<unsigned int, unsigned int>> *map, glm::uvec3 *ind, unsigned int size)
{
    unsigned int count = 1;
    for (int i = 0; i < size; i++)
    {
        if (map[ind[i][0] - 1][ind[i][1] - 1][ind[i][2] - 1] == 0)
        {
            map[ind[i][0] - 1][ind[i][1] - 1][ind[i][2] - 1] = count++;
        }
    }
    return count;
}
void MeshLoader::createVertices(Vertex3pntxy *vertices, glm::vec3 *pos, glm::vec2 *tex, glm::vec3 *norm, std::map<unsigned int, std::map<unsigned int, unsigned int>> *map, unsigned int size)
{
    for (int i = 0; i < size; i++)
    {
        for (auto &j : map[i])
        {
            for (auto &k : j.second)
            {
                vertices[k.second].pos = pos[i + 1];
                vertices[k.second].tex = tex[j.first + 1];
                vertices[k.second].norm = norm[k.first + 1];
            }
        }
    }
}
void MeshLoader::createIndices(glm::uvec3 *indices, unsigned int indCount, std::map<unsigned int, std::map<unsigned int, unsigned int>> *map, V3Index *v3ind)
{
    unsigned int *ptr = (unsigned int *)v3ind;
    for (int i = 0; i < indCount; i++)
    {
        *(ptr++) = map[indices[i][0] - 1][indices[i][1] - 1][indices[i][2] - 1];
    }
}

SimpleMesh<Vertex3pntxy, V3Index> *MeshLoader::loadMesh(const char *filename)
{
    loadData(filename);
    if (data == nullptr)
    {
        return nullptr;
    }
    unsigned int posCount, texCount, normCount, indCount, groupCount;
    countVertices(posCount, texCount, normCount, indCount, groupCount);
    std::cout << "mesh data: " << posCount << " " << texCount << " " << normCount << " " << indCount << " " << groupCount << std::endl;
    SimpleMesh<Vertex3pntxy, V3Index> *mesh = new SimpleMesh<Vertex3pntxy, V3Index>();

    glm::vec3 *positions = new glm::vec3[posCount + 1];
    glm::vec2 *textures = new glm::vec2[texCount + 1];
    glm::vec3 *normals = new glm::vec3[normCount + 1];
    glm::uvec3 *indices = new glm::uvec3[indCount];

    positions[0] = normals[0] = glm::vec3(0, 0, 0);
    textures[0] = glm::vec2(0, 0);

    loadMeshData((float *)(positions + 1), (float *)(textures + 1), (float *)(normals + 1), indices);

    auto *indicesMap = new std::map<unsigned int, std::map<unsigned int, unsigned int>>[posCount];
    unsigned int verticesCount = createMap(indicesMap, indices, indCount);
    std::cout << "indices mapped" << std::endl;

    auto &vbuff = mesh->getVertexBuffer();
    auto &ibuff = mesh->getIndexBuffer();
    vbuff.setBuffer(verticesCount);
    ibuff.setBuffer(indCount / 3);

    createVertices(vbuff.getData(), positions, textures, normals, indicesMap, posCount);
    std::cout << "vertices created" << std::endl;
    createIndices(indices, indCount, indicesMap, ibuff.getData());
    std::cout << "indices remapped" << std::endl;
    mesh->computeTangentSpace();
    mesh->flush();

    delete[] positions;
    delete[] textures;
    delete[] normals;
    delete[] indicesMap;
    return mesh;
}