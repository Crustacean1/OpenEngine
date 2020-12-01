#include "MeshLoader.h"

#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include "../Mesh/Mesh.h"
#include "MaterialLoader.h"
#include "../Material/Material.h"

using namespace OpenEngine;


std::string getBasename(std::string a);

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
    while (**ptr < '-' && (*ptr) < end && **ptr != '\n')
    {
        (*ptr)++;
    }
    if (**ptr == '\\')
    {
        (*ptr)++;
        while (**ptr < '-' && (*ptr) < end)
        {
            (*ptr)++;
        }
    }
    return (!(**ptr > '9')) & ((*ptr) < end) & (**ptr != '\n');
}
bool compare(char **ptr, const char *str)
{
    while (*str != 0)
    {
        if (*str != **ptr)
        {
            return false;
        }
        (*ptr)++;
        str++;
    }
    return true;
}
void MeshLoader::countVertices(unsigned int &a, unsigned int &b, unsigned int &c, unsigned int &d, unsigned int &e)
{
    a = b = c = d = e = 0;
    char *ptr = data;
    unsigned int primitiveCount;
    std::string gName, mName;
    gName = mName = "default";

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
            while (*ptr != '\n' && ptr < end)
            {
                ptr += 2 * (*ptr == '\\');
                primitiveCount += (*ptr == '/');
                ptr++;
            }
            d += ((primitiveCount / 2) - 2) * 3;
            break;
        case 'o':
            e++;
            gName = "";
            ptr += 2;
            while (*ptr > ' ')
            {
                gName += *ptr;
                ptr++;
            }
            groups.push_back(std::pair<std::string, unsigned int>("", d));
            break;
        case 'u':
            if (!compare(&ptr, "usemtl"))
            {
                break;
            }
            while (*ptr > ' ')
            {
                ptr++;
            }
            mName = "";
            ptr++;
            while (*ptr > ' ')
            {
                mName += *ptr;
                ptr++;
            }
            groups.back().first = mName;
        case 'm':
            if (!compare(&ptr, "mtllib"))
            {
                break;
            }
            while (*ptr > ' ')
            {
                ptr++;
            }
            ptr++;
            while (*ptr > ' ')
            {
                matfile += *ptr;
                ptr++;
            }
            break;
        default:
            break;
        }
        while (*ptr != '\n' && ptr < end)
        {
            ptr++;
        }
        ptr++;
    }
    groups.push_back(std::pair<std::string, unsigned int>("", d));
}

void MeshLoader::loadVerticesData(char **ptr, float **target, char size)
{
    if (!toNextNum(ptr))
    {
        return;
    }
    while (toNextNum(ptr))
    {
        **target = toFloat(ptr);
        (*target) += (size-- > 0);
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
    while (*ptr<end &&* * ptr> ' ')
    {
        (*ptr)++;
    }
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
        cnt += 3;
        *((*ind)++) = base;
        *((*ind)++) = prev;
        prev = *((*ind)++) = loadIndice(ptr);
    }
}
void MeshLoader::loadMeshData(float *pos, float *tex, float *norm, glm::uvec3 *ind)
{
    char *ptr = data;
    char *end = data + dataLength;
    int over = 0;
    while (ptr < end)
    {
        switch (*(ptr++))
        {
        case 'v':
            switch (*(ptr++))
            {
            case ' ':
                loadVerticesData(&ptr, &pos, 3);
                break;
            case 't':
                ptr++;
                loadVerticesData(&ptr, &tex, 2);
                break;
            case 'n':
                ptr++;
                loadVerticesData(&ptr, &norm, 3);
                break;
            }
            break;
        case 'f':
            loadIndicesData(&ptr, &ind);
            break;
        }
        while (*ptr != '\n' && ptr < end)
        {
            ++ptr;
        };
        ++ptr;
    }
    std::cout << over << std::endl;
    std::cout << "ended on: " << (int)(ptr - data) << " " << dataLength << std::endl;
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
    end = data + dataLength + 1;
}
unsigned int MeshLoader::createMap(std::map<unsigned int, std::map<unsigned int, unsigned int>> *map, glm::uvec3 *ind, unsigned int size)
{
    for(int i = 1;i<groups.size();i++)
    {
        meshes.push_back(std::pair<Material3D*,SimpleMesh<Vertex3pntxy,V3Index>*>(nullptr,new SimpleMesh<Vertex3pntxy,V3Index>()));
    }
    unsigned int count = 1;

    unsigned int *ptr;
    for (int i = 0; i < size; i++)
    {
        if (map[ind[i][0] - 1][ind[i][1] - 1][ind[i][2] - 1] == 0)
        {
            map[ind[i][0] - 1][ind[i][1] - 1][ind[i][2] - 1] = count++;
        }
    }
    return count;
}
void MeshLoader::createVertices(glm::vec3 *pos, glm::vec2 *tex, glm::vec3 *norm, std::map<unsigned int, std::map<unsigned int, unsigned int>> *map, unsigned int size, unsigned int vCount)
{
    for (auto &mesh : meshes)
    {
        mesh.second->getVertexBuffer().setBuffer(vCount);
    }

    unsigned int offset = 0;
    for (int i = 0; i < size; i++)
    {
        for (auto &j : map[i])
        {
            for (auto &k : j.second)
            {
                for (auto &mesh : meshes)
                {
                    mesh.second->getVertexBuffer().getData()[k.second].pos = pos[i + 1];
                    mesh.second->getVertexBuffer().getData()[k.second].tex = tex[j.first + 1];
                    mesh.second->getVertexBuffer().getData()[k.second].norm = norm[k.first + 1];
                }
            }
        }
    }
}
void MeshLoader::createIndices(glm::uvec3 *indices, unsigned int indCount, std::map<unsigned int, std::map<unsigned int, unsigned int>> *map)
{
    for (int i = 0; i < meshes.size(); i++)
    {
        meshes[i].second->getIndexBuffer().setBuffer((groups[i + 1].second - groups[i].second)/3);
    }
    auto it = ++groups.begin();
    auto mesh = meshes.begin();
    unsigned int * ptr = (unsigned int*)meshes[0].second->getIndexBuffer().getData();
    for (int i = 0; i < indCount; i++)
    {
        if(i>=(*it).second)
        {
            (*mesh).second->computeTangentSpace();
            ptr = (unsigned int*)(*(++mesh)).second->getIndexBuffer().getData();
            it++;
        }
        *(ptr++) = map[indices[i][0] - 1][indices[i][1] - 1][indices[i][2] - 1];
    }
    (*mesh).second->computeTangentSpace();
    //(*mesh).second->flush();
}

std::vector<std::pair<Material3D *, SimpleMesh<Vertex3pntxy, V3Index> *>> MeshLoader::loadMesh(const char *filename)
{
    loadData(filename);
    if (data == nullptr)
    {
        return std::vector<std::pair<Material3D *, SimpleMesh<Vertex3pntxy, V3Index> *>>();
    }
    unsigned int posCount, texCount, normCount, indCount, groupCount;
    countVertices(posCount, texCount, normCount, indCount, groupCount);
    std::cout << "mesh data: " << posCount << " " << texCount << " " << normCount << " " << indCount << " " << groupCount << std::endl;

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

    createVertices(positions, textures, normals, indicesMap, posCount, verticesCount);
    createIndices(indices, indCount, indicesMap);

    MaterialLoader materialLoader;
    std::map<std::string,Material3D*> materials = materialLoader.loadMaterial((getBasename(filename)+matfile).c_str());
    materials["default"] = new Material3D();
    for(int i = 0;i<meshes.size();i++)
    {
        if(materials.find(groups[i].first)==materials.end())
        {
            meshes[i].first = materials["default"];
            continue;
        }
        meshes[i].first = materials[groups[i].first];
    }

    delete[] positions;
    delete[] textures;
    delete[] normals;
    delete[] indicesMap;
    return meshes;
}