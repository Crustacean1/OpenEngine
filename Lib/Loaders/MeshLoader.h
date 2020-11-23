#ifndef MESHLOADER
#define MESHLAODER

#include <glm/glm.hpp>
#include <map>

namespace OpenEngine
{
    template<typename V,typename I>
    class SimpleMesh;

    class Vertex3pntxy;
    class V3Index;

    class MeshLoader
    {
        char * data;
        char * end;
        unsigned int dataLength;

        bool toNextNum(char ** ptr);

        void loadData(const char * filename);
        void countVertices(unsigned int &a,unsigned int &b,unsigned int &c,unsigned int &d,unsigned int &e);

        void loadVerticesData(char ** ptr,float ** target,char size);

        glm::uvec3 loadIndice(char ** ptr);
        void loadIndicesData(char ** ptr,glm::uvec3 ** ind);

        unsigned int createMap(std::map<unsigned int,std::map<unsigned int,unsigned int>> * map,glm::uvec3 * indices,unsigned int size);
        void createVertices(Vertex3pntxy * vertices,glm::vec3 *pos,glm::vec2 *tex,glm::vec3 *norm,std::map<unsigned int,std::map<unsigned int,unsigned int>> * map,unsigned int size);
        void createIndices(glm::uvec3 * indices,unsigned int indCount,std::map<unsigned int,std::map<unsigned int,unsigned int>> * map,V3Index * v3ind);

        void loadMeshData(float * pos,float * tex,float * norm,glm::uvec3 * ind);

        public:
        SimpleMesh<Vertex3pntxy,V3Index> * loadMesh(const char * filename);
    };
};

#endif /*MESHLOADER*/