#ifndef MESH
#define MESH

#include "../Buffer/Buffer.h"
#include "../VAO/VAO.h"

namespace OpenEngine
{
    class Mesh //Resource
    {
        Buffer<VIndex, GL_ELEMENT_ARRAY_BUFFER> indices;
        Buffer<Vertex3p, GL_ARRAY_BUFFER> vertices;
        VAO vao;
    public:
        Mesh();
        void generateCube(unsigned int resolution = 10,unsigned int size =1);
        void generateTorus(unsigned int resolution = 10,unsigned int size =1);
        void generateSphere(unsigned int resolution = 10,unsigned int size =1);
        void generatePlane(unsigned int resolution = 10, unsigned int size = 1);
    };
}; // namespace OpenEngine

#endif /*MESH*/