#ifndef MESHLOADER
#define MESHLAODER

#include <glm/glm.hpp>
#include <string>
#include <map>
#include <vector>
#include <list>

namespace OpenEngine
{
    template<typename V,typename I>
    class SimpleMesh;

    class Vertex3pntxy;
    class V3Index;

    class Material3D;

    class MeshLoader
    {
        char * data;
        char * end;
        unsigned int dataLength;
        std::string matfile;
        std::vector<std::pair<std::string,unsigned int>> groups;

        bool toNextNum(char ** ptr);

        void loadData(const char * filename);
        void countVertices(unsigned int &a,unsigned int &b,unsigned int &c,unsigned int &d,unsigned int &e);

        void loadVerticesData(char ** ptr,float ** target,char size);

        glm::uvec3 loadIndice(char ** ptr);
        void loadIndicesData(char ** ptr,glm::uvec3 ** ind);

        unsigned int createMap(std::map<unsigned int,std::map<unsigned int,unsigned int>> * map,glm::uvec3 * indices,unsigned int size);
        void createVertices(glm::vec3 *pos,glm::vec2 *tex,glm::vec3 *norm,std::map<unsigned int,std::map<unsigned int,unsigned int>> * map,unsigned int size,unsigned int vCount);
        void createIndices(glm::uvec3 * indices,unsigned int indCount,std::map<unsigned int,std::map<unsigned int,unsigned int>> * map);

        void loadMeshData(float * pos,float * tex,float * norm,glm::uvec3 * ind);

        std::vector<std::pair<Material3D*,SimpleMesh<Vertex3pntxy,V3Index>*>> meshes;

        public:
        std::vector<std::pair<Material3D*,SimpleMesh<Vertex3pntxy,V3Index> *>> loadMesh(const char * filename);
    };
};

#endif /*MESHLOADER*/