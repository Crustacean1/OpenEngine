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

        unsigned int shape = GL_TRIANGLES;

    public:
        SimpleMesh();
        static SimpleMesh<Vertex3pcn,V3Index> generateCube(unsigned int resolution = 10, float size = 1);
        static SimpleMesh<Vertex3pcn,V3Index> generateTorus(unsigned int resolution = 10, float size = 1);
        static SimpleMesh<Vertex3pcn,V3Index> generateSphere(unsigned int resolution = 10, float size = 1);
        static SimpleMesh<Vertex3p,V3Index> generatePlane(unsigned int resolution = 10, float size = 1);
        static SimpleMesh<Vertex3p,V2Index> generateGrid(unsigned int resolution = 10, float size = 10);

        unsigned int getMeshSize() override { return indices.getSize()*3; }
        void bind() override { vao.bind(); }
        friend MeshRenderer;
    };

//Implementation

template<typename V,typename I>
SimpleMesh<Vertex3p,V3Index> SimpleMesh<V,I>::generatePlane(unsigned int resolution, float size)
{
    SimpleMesh<Vertex3p,V3Index> mesh;
    mesh.vertices.setBuffer(resolution * resolution);
    mesh.indices.setBuffer((resolution - 1) * (resolution - 1) * 2);
    auto _ind = mesh.indices.getData().get();
    auto _vert = mesh.vertices.getData().get();

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

    mesh.vertices.flush();
    mesh.indices.flush();
    mesh.vao.swapBuffer(vertices);
    mesh.vao.swapBuffer(indices);
    return mesh;

}

template<typename V,typename I>
SimpleMesh<V,I>::SimpleMesh() {}

template<typename V,typename I>
SimpleMesh<Vertex3p,V2Index> SimpleMesh<V,I>::generateGrid(unsigned int resolution, float size)
{
    SimpleMesh<Vertex3p,V2Index> mesh;

    mesh.vertices.setBuffer(6 * resolution * resolution);
    mesh.indices.setBuffer(3 * resolution * resolution);

    auto _ind = mesh.indices.getData().get();
    auto _vert = mesh.vertices.getData().get();

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
    for (int i = 0, k = 0,l = 0; i < resolution*resolution*3; i++)
    {
        _ind[k++].set(l++,l++);
    }

    mesh.vertices.flush();
    mesh.indices.flush();
    mesh.vao.swapBuffer(mesh.vertices);
    mesh.vao.swapBuffer(mesh.indices);
    return mesh;
}


}; // namespace OpenEngine
#endif /*MESH*/