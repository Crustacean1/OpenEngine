#ifndef MESH
#define MESH

#include "../Buffer/Buffer.h"
#include "../VAO/VAO.h"

namespace OpenEngine
{
    class MeshRenderer;

    class Mesh
    {
    public:
        virtual void bind() = 0;
        virtual unsigned int getMeshSize() = 0;
    };
    template <typename V, typename I>
    class SimpleMesh :public Mesh //Resource
    {
        Buffer<I, GL_ELEMENT_ARRAY_BUFFER> indices;
        Buffer<V, GL_ARRAY_BUFFER> vertices;
        VAO vao;

    public:
        SimpleMesh();
        void generateCube(unsigned int resolution = 10, float size = 1);
        void generateTorus(unsigned int resolution = 10, float size = 1);
        void generateSphere(unsigned int resolution = 10, float size = 1);
        void generatePlane(unsigned int resolution = 10, float size = 1);
        void generateGrid(unsigned int resolution = 10, float size = 10);

        unsigned int getMeshSize() override { return indices.getSize()*3; }
        void bind() override { vao.bind(); }
        friend MeshRenderer;
    };
}; // namespace OpenEngine

//Implementation

template<typename V,typename I>
void OpenEngine::SimpleMesh<V,I>::generatePlane(unsigned int resolution, float size)
{
    vertices.setBuffer(resolution * resolution);
    indices.setBuffer((resolution - 1) * (resolution - 1) * 2);
    auto _ind = indices.getData().get();
    auto _vert = vertices.getData().get();

    for (unsigned int i = 0, k = 0; i + 1 < resolution; i++)
    {
        for (unsigned int j = 0; j + 1 < resolution; j++)
        {
            _ind[k++].set(i * resolution + j, i * resolution + j + 1, (i + 1) * resolution + j);
            _ind[k++].set((i + 1) * (resolution) + j + 1, i * resolution + j + 1, (i + 1) * resolution + j);
        }
    }

    for (int i = 0, k = 0; i < resolution; i++)
    {
        for (int j = 0; j < resolution; j++)
        {
            _vert[k++].pos = glm::vec3(-size + (float)2 * size * i / (resolution - 1), -size + (float)2 * size * j / (resolution - 1), 0);
        }
    }

    vertices.flush();
    indices.flush();
    vao.swapBuffer(vertices);
    vao.swapBuffer(indices);
}

template<typename V,typename I>
OpenEngine::SimpleMesh<V,I>::SimpleMesh() {}

template<typename V,typename I>
void OpenEngine::SimpleMesh<V,I>::generateGrid(unsigned int resolution, float size)
{
    vertices.setBuffer(6 * resolution * resolution);
    indices.setBuffer(3 * resolution * resolution);

    auto _ind = indices.getData().get();
    auto _vert = vertices.getData().get();

    for (int i = 0, k = 0; i < resolution; i++)
    {
        for (int j = 0; j < resolution; j++)
        {
            _vert[k++].pos = glm::vec3(0, 0, -size);
            _vert[k++].pos = glm::vec3(0, 0, size);

            _vert[k++].pos = glm::vec3(0, -size, 0);
            _vert[k++].pos = glm::vec3(0, size, 0);

            _vert[k++].pos = glm::vec3(-size, 0, 0);
            _vert[k++].pos = glm::vec3(size, 0, 0);
        }
    }
    for (int i = 0, k = 0; i < resolution; i++)
    {
        for(int j = 0;j<resolution;j++)
        {
            _ind[k].set()
        }
    }
}


#endif /*MESH*/