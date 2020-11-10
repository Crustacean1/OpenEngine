#ifndef MESH
#define MESH

#include "../Buffer/Buffer.h"
#include "../VAO/VAO.h"
#include <math.h>

namespace OpenEngine
{
    class MeshRenderer;

    class Mesh
    {
    protected:
        unsigned int shape;

    public:
        virtual void bind() = 0;
        virtual unsigned int getMeshSize() = 0;
        unsigned int getShape() { return shape; }
    };
    template <typename V, typename I>
    class SimpleMesh : public Mesh //Resource
    {
        Buffer<V, GL_ARRAY_BUFFER> vertices;
        Buffer<I, GL_ELEMENT_ARRAY_BUFFER> indices;
        VAO vao;

    public:
        SimpleMesh();
        static std::shared_ptr<SimpleMesh<Vertex3pcn, V3Index>> generateCube(unsigned int resolution = 10, float size = 1);
        static std::shared_ptr<SimpleMesh<Vertex3pcn, V3Index>> generateTorus(unsigned int resolution = 10, float size1 = 1, float size2 = 0.5);
        static std::shared_ptr<SimpleMesh<Vertex3pc, V3Index>> generateSphere(unsigned int resolution = 10, float size = 1);
        static std::shared_ptr<SimpleMesh<Vertex3p, V3Index>> generatePlane(unsigned int resolution = 10, float size = 1);
        static std::shared_ptr<SimpleMesh<Vertex3p, V2Index>> generateGrid(unsigned int resolution = 10, float size = 10);

        unsigned int getMeshSize() override { return indices.getSize() * I::size; }
        void bind() override { vao.bind(); }
        friend MeshRenderer;
    };

    //Implementation

    template <typename V, typename I>
    std::shared_ptr<SimpleMesh<Vertex3p, V3Index>> SimpleMesh<V, I>::generatePlane(unsigned int resolution, float size)
    {
        std::shared_ptr<SimpleMesh<Vertex3p, V3Index>> mesh(new SimpleMesh<Vertex3p, V3Index>());
        mesh->vertices.setBuffer(resolution * resolution);
        mesh->indices.setBuffer((resolution - 1) * (resolution - 1) * 2);
        auto _ind = mesh->indices.getData().get();
        auto _vert = mesh->vertices.getData().get();

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
        mesh->shape = GL_TRIANGLES;
        mesh->vertices.flush();
        mesh->indices.flush();
        mesh->vao.swapBuffer(mesh->vertices);
        mesh->vao.swapBuffer(mesh->indices);
        return mesh;
    }

    template <typename V, typename I>
    SimpleMesh<V, I>::SimpleMesh() { shape = GL_TRIANGLES; }

    template <typename V, typename I>
    std::shared_ptr<SimpleMesh<Vertex3p, V2Index>> SimpleMesh<V, I>::generateGrid(unsigned int resolution, float size)
    {
        std::shared_ptr<SimpleMesh<Vertex3p, V2Index>> mesh(new SimpleMesh<Vertex3p, V2Index>());

        mesh->vertices.setBuffer(6 * resolution * resolution);
        mesh->indices.setBuffer(3 * resolution * resolution);

        auto _ind = mesh->indices.getData().get();
        auto _vert = mesh->vertices.getData().get();

        for (int i = 0, k = 0; i < resolution; i++)
        {
            for (int j = 0; j < resolution; j++)
            {
                _vert[k++].pos = glm::vec3(2 * size * (float)i / (resolution - 1) - size, 2 * size * (float)j / (resolution - 1) - size, -size);
                _vert[k++].pos = glm::vec3(2 * size * (float)i / (resolution - 1) - size, 2 * size * (float)j / (resolution - 1) - size, size);

                _vert[k++].pos = glm::vec3(2 * size * (float)i / (resolution - 1) - size, -size, 2 * size * (float)j / (resolution - 1) - size);
                _vert[k++].pos = glm::vec3(2 * size * (float)i / (resolution - 1) - size, size, 2 * size * (float)j / (resolution - 1) - size);

                _vert[k++].pos = glm::vec3(-size, 2 * size * (float)i / (resolution - 1) - size, 2 * size * (float)j / (resolution - 1) - size);
                _vert[k++].pos = glm::vec3(size, 2 * size * (float)i / (resolution - 1) - size, 2 * size * (float)j / (resolution - 1) - size);
            }
        }
        for (int i = 0, k = 0, l = 0; i < resolution * resolution * 3; i++)
        {
            _ind[k++].set(l++, l++);
        }

        mesh->shape = GL_LINES;

        mesh->vertices.flush();
        mesh->indices.flush();
        mesh->vao.swapBuffer(mesh->vertices);
        mesh->vao.swapBuffer(mesh->indices);
        return mesh;
    }

    template <typename V, typename I>
    std::shared_ptr<SimpleMesh<Vertex3pc, V3Index>> SimpleMesh<V, I>::generateSphere(unsigned int resolution, float size)
    {
        std::shared_ptr<SimpleMesh<Vertex3pc, V3Index>> mesh(new SimpleMesh<Vertex3pc, V3Index>());

        mesh->vertices.setBuffer(resolution * resolution);
        mesh->indices.setBuffer((resolution - 1) * (resolution - 1) * 2);

        auto _ind = mesh->indices.getData().get();
        auto _vert = mesh->vertices.getData().get();

        double xangle = 0;
        double yangle = -90;

        for (unsigned int i = 0, k = 0; i < resolution; i++)
        {
            xangle = 0;
            for (unsigned int j = 0; j < resolution; j++)
            {
                _vert[k].col = glm::vec3(1 * ((float)i / (resolution - 1)), 0.25, 1 * ((float)j / (resolution - 1)));
                _vert[k++].pos = size * glm::vec3(cos(glm::radians(yangle)) * cos(glm::radians(xangle)), sin(glm::radians(yangle)), cos(glm::radians(yangle)) * sin(glm ::radians(xangle)));
                xangle += (360.f) / (resolution - 1);
            }
            yangle += (180.f) / (resolution - 1);
        }

        for (unsigned int i = 0, k = 0; i < resolution - 1; i++)
        {
            for (unsigned int j = 0; j < resolution - 1; j++)
            {
                _ind[k++].set(i * resolution + j, i * resolution + j + 1, (i + 1) * resolution + j);
                _ind[k++].set((i + 1) * resolution + (j + 1), i * resolution + j + 1, (i + 1) * resolution + j);
            }
        }

        mesh->shape = GL_TRIANGLES;
        mesh->indices.flush();
        mesh->vertices.flush();
        mesh->vao.swapBuffer(mesh->indices);
        mesh->vao.swapBuffer(mesh->vertices);
        return mesh;
    }
    template <typename V, typename I>
    std::shared_ptr<SimpleMesh<Vertex3pcn, V3Index>> SimpleMesh<V, I>::generateTorus(unsigned int resolution, float size1, float size2)
    {
        std::shared_ptr<SimpleMesh<Vertex3pcn, V3Index>> mesh(new SimpleMesh<Vertex3pcn, V3Index>());

        mesh->vertices.setBuffer(resolution * resolution);
        mesh->indices.setBuffer((resolution - 1) * (resolution - 1) * 2);

        auto _ind = mesh->indices.getData().get();
        auto _vert = mesh->vertices.getData().get();

        double xangle = 0;
        double yangle = 0;

        for (unsigned int i = 0, k = 0; i < resolution; i++)
        {
            xangle = 0;
            for (unsigned int j = 0; j < resolution; j++)
            {
                _vert[k].col = glm::vec3(1 * ((float)i / (resolution - 1)), 0.25, 1 * ((float)j / (resolution - 1)));
                _vert[k++].pos = (float)(size1 + (0.75+0.25*sin(glm::radians(yangle * 5))) * size2 * cos(glm::radians(xangle))) * glm::vec3(cos(glm::radians(yangle)), 0, sin(glm::radians(yangle))) + (float)((0.75+0.25*sin(glm::radians(yangle * 5))) * size2 * sin(glm::radians(xangle))) * glm::vec3(0, 1, 0);
                xangle += (360.f) / (resolution - 1);
            }
            yangle += (360.f) / (resolution - 1);
        }

        for (unsigned int i = 0, k = 0; i < resolution - 1; i++)
        {
            for (unsigned int j = 0; j < resolution - 1; j++)
            {
                _ind[k++].set(i * resolution + j, i * resolution + j + 1, (i + 1) * resolution + j);
                _ind[k++].set((i + 1) * resolution + (j + 1), i * resolution + j + 1, (i + 1) * resolution + j);
            }
        }

        mesh->shape = GL_TRIANGLES;
        mesh->indices.flush();
        mesh->vertices.flush();
        mesh->vao.swapBuffer(mesh->indices);
        mesh->vao.swapBuffer(mesh->vertices);
        return mesh;
    }
};     // namespace OpenEngine
#endif /*MESH*/