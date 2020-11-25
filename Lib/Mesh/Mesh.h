#ifndef MESH
#define MESH

#include "../Buffer/Buffer.h"
#include "../VAO/VAO.h"
#include <math.h>
#include <iostream>
namespace OpenEngine
{
    class MeshRenderer;
    class MeshLoader;

    class Mesh
    {
    protected:
        unsigned int shape;

    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual unsigned int getMeshSize() = 0;
        virtual unsigned int getShape() { return shape; }
    };
    template <typename V, typename I>
    class SimpleMesh : public Mesh //Resource
    {
        Buffer<V, GL_ARRAY_BUFFER> vertices;
        Buffer<I, GL_ELEMENT_ARRAY_BUFFER> indices;
        VAO vao;

        static void iterateSierpinski(SimpleMesh<Vertex3pc, V3Index> *mesh, unsigned int depth, float size, glm::vec3 pos, unsigned int &k = 0, unsigned int &l = 0);

    public:
        SimpleMesh();
        static SimpleMesh<Vertex3pcn, V3Index> *generateCube(unsigned int resolution = 10, float size = 1);
        static SimpleMesh<Vertex3pntxy, V3Index> *generateTorus(unsigned int resolution = 10, float size1 = 1, float size2 = 0.5);
        static SimpleMesh<Vertex3pntxy, V3Index> *generateSphere(unsigned int resolution = 10, float size = 1);
        static SimpleMesh<Vertex3pntxy, V3Index> *generatePlane(unsigned int resolution = 10, float size = 1);
        static SimpleMesh<Vertex3p, V2Index> *generateGrid(unsigned int resolution = 10, float size = 10);
        static SimpleMesh<Vertex3pc, V3Index> *generateSierpinski(unsigned int depth = 5, float size = 5);
        static SimpleMesh<Vertex3pntxy, V3Index> *generateCuboid(float x, float y, float z);

        void computeTangentSpace();

        unsigned int getMeshSize() override { return indices.getSize() * I::size; }
        void bind() override { vao.bind(); }
        void unbind() override { vao.unbind(); }
        Buffer<V, GL_ARRAY_BUFFER> &getVertexBuffer() { return vertices; }
        Buffer<I, GL_ELEMENT_ARRAY_BUFFER> &getIndexBuffer() { return indices; }
        void flush();
        friend MeshRenderer;
        friend MeshLoader;
    };

    //Implementation
    template <typename V, typename I>
    void SimpleMesh<V, I>::flush()
    {
        vertices.flush();
        indices.flush();
        vao.swapBuffer(vertices);
        vao.swapBuffer(indices);
    }

    template <typename V, typename I>
    SimpleMesh<Vertex3pntxy, V3Index> *SimpleMesh<V, I>::generatePlane(unsigned int resolution, float size)
    {
        auto mesh(new SimpleMesh<Vertex3pntxy, V3Index>());
        mesh->vertices.setBuffer(resolution * resolution);
        mesh->indices.setBuffer((resolution - 1) * (resolution - 1) * 2);
        auto _ind = mesh->indices.getData();
        auto _vert = mesh->vertices.getData();

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
                _vert[k].tex = glm::vec2((float)i / (resolution - 1), (float)j / (resolution - 1));
                _vert[k].norm = glm::vec3(0, 0, 1);
                _vert[k++].pos = glm::vec3(-size + (float)2 * size * i / (resolution - 1), -size + (float)2 * size * j / (resolution - 1), 0);
            }
        }
        mesh->shape = GL_TRIANGLES;
        mesh->flush();
        return mesh;
    }

    template <typename V, typename I>
    SimpleMesh<V, I>::SimpleMesh() { shape = GL_TRIANGLES; }

    template <typename V, typename I>
    SimpleMesh<Vertex3p, V2Index> *SimpleMesh<V, I>::generateGrid(unsigned int resolution, float size)
    {
        auto mesh(new SimpleMesh<Vertex3p, V2Index>());

        mesh->vertices.setBuffer(6 * resolution * resolution);
        mesh->indices.setBuffer(3 * resolution * resolution);

        auto _ind = mesh->indices.getData();
        auto _vert = mesh->vertices.getData();

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

        mesh->flush();
        return mesh;
    }

    template <typename V, typename I>
    SimpleMesh<Vertex3pntxy, V3Index> *SimpleMesh<V, I>::generateSphere(unsigned int resolution, float size)
    {
        auto mesh(new SimpleMesh<Vertex3pntxy, V3Index>());

        mesh->vertices.setBuffer(resolution * resolution);
        mesh->indices.setBuffer((resolution - 1) * (resolution - 1) * 2);

        auto _ind = mesh->indices.getData();
        auto _vert = mesh->vertices.getData();

        double xangle = 0;
        double yangle = -90;

        for (unsigned int i = 0, k = 0; i < resolution; i++) // Computing position, normals and textures, setting tangents and bitangents to zero
        {
            xangle = 0;
            for (unsigned int j = 0; j < resolution; j++)
            {
                //_vert[k++].pos = glm::vec3((float)size*i/resolution,0,(float)size*j/resolution);
                _vert[k++].pos = size * glm::vec3(cos(glm::radians(yangle)) * cos(glm::radians(xangle)), sin(glm::radians(yangle)), cos(glm::radians(yangle)) * sin(glm ::radians(xangle)));
                _vert[k - 1].norm = _vert[k - 1].pos / size;
                _vert[k - 1].tex = glm::vec2((float)j / (resolution - 1), (float)i / (resolution - 1));
                _vert[k - 1].tan = glm::vec3(0, 0, 0);
                _vert[k - 1].bitan = glm::vec3(0, 0, 0);
                xangle -= (360.f) / (resolution - 1);
            }
            yangle += (180.f) / (resolution - 1);
        }

        for (unsigned int i = 0, k = 0; i < resolution - 1; i++) // Indices addressing
        {
            for (unsigned int j = 0; j < resolution - 1; j++)
            {

                _ind[k++].set(i * resolution + j, i * resolution + (j + 1), (i + 1) * resolution + j);
                _ind[k++].set((i + 1) * resolution + (j + 1), i * resolution + (j + 1), (i + 1) * resolution + j);
            }
        }
        glm::vec3 buff;

        mesh->shape = GL_TRIANGLES;
        mesh->flush();
        return mesh;
    }
    template <typename V, typename I>
    SimpleMesh<Vertex3pntxy, V3Index> *SimpleMesh<V, I>::generateTorus(unsigned int resolution, float size1, float size2)
    {
        auto mesh(new SimpleMesh<Vertex3pntxy, V3Index>());

        mesh->vertices.setBuffer(resolution * resolution);
        mesh->indices.setBuffer((resolution - 1) * (resolution - 1) * 2);

        auto _ind = mesh->indices.getData();
        auto _vert = mesh->vertices.getData();

        double xangle = 0;
        double yangle = 0;

        for (unsigned int i = 0, k = 0; i < resolution; i++)
        {
            xangle = 0;
            for (unsigned int j = 0; j < resolution; j++)
            {
                //_vert[k].col = glm::vec3(1 * ((float)i / (resolution - 1)), 0.25, 1 * ((float)j / (resolution - 1)));
                _vert[k].tex = glm::vec2((float)i / (resolution - 1), (float)j / (resolution - 1));
                _vert[k].norm = glm::vec3(cos(glm::radians(xangle)) * cos(glm::radians(yangle)), sin(glm::radians(xangle)), sin(glm::radians(yangle)) * cos(glm::radians(xangle)));
                _vert[k++].pos = (float)(size1 + (1) * size2 * cos(glm::radians(xangle))) * glm::vec3(cos(glm::radians(yangle)), 0, sin(glm::radians(yangle))) + (float)((1) * size2 * sin(glm::radians(xangle))) * glm::vec3(0, 1, 0);
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
        mesh->flush();
        return mesh;
    }
    template <typename V, typename I>
    SimpleMesh<Vertex3pc, V3Index> *SimpleMesh<V, I>::generateSierpinski(unsigned int depth, float size)
    {
        auto mesh(new SimpleMesh<Vertex3pc, V3Index>());

        mesh->vertices.setBuffer(pow(4, depth + 1));
        mesh->indices.setBuffer(pow(4, depth + 1));

        auto vert = mesh->vertices.getData();
        auto ind = mesh->indices.getData();

        unsigned int k, l;
        k = l = 0;

        iterateSierpinski(mesh, depth, size, glm::vec3(0, 0, 0), k, l);
        mesh->shape = GL_TRIANGLES;
        mesh->flush();
        return mesh;
    }
    template <typename V, typename I>
    void SimpleMesh<V, I>::iterateSierpinski(SimpleMesh<Vertex3pc, V3Index> *mesh, unsigned int depth, float size, glm::vec3 pos, unsigned int &k, unsigned int &l)
    {
        if (depth < 1)
        {
            auto vert = mesh->vertices.getData();
            auto ind = mesh->indices.getData();

            vert[k++] = {glm::vec3(pos), glm::vec3(0.5, 0.6, 0.7)};
            vert[k++] = {glm::vec3(pos) + 2 * size * glm::vec3(0.5, 0, sqrt(3) / 2.0), glm::vec3(0.6, 0.5, 0.7)};
            vert[k++] = {glm::vec3(pos) + 2 * size * glm::vec3(1, 0, 0), glm::vec3(0.5, 0.6, 0.7)};
            vert[k++] = {glm::vec3(pos) + 2 * size * glm::vec3(0.5, sqrt(2.0 / 3.0), 0.5 / sqrt(3)), glm::vec3(0.7, 0.6, 0.5)};

            ind[l++] = {k - 4, k - 3, k - 2};
            ind[l++] = {k - 4, k - 3, k - 1};
            ind[l++] = {k - 1, k - 3, k - 2};
            ind[l++] = {k - 4, k - 1, k - 2};

            return;
        }
        iterateSierpinski(mesh, depth - 1, size / 2, pos, k, l);
        iterateSierpinski(mesh, depth - 1, size / 2, pos + size * glm::vec3(1, 0, 0), k, l);
        iterateSierpinski(mesh, depth - 1, size / 2, pos + size * glm::vec3(0.5, 0, sqrt(3) / 2), k, l);
        iterateSierpinski(mesh, depth - 1, size / 2, pos + size * glm::vec3(0.5, sqrt(2.0 / 3.0), 0.5 / sqrt(3)), k, l);
    }
    template <typename V, typename I>
    void SimpleMesh<V, I>::computeTangentSpace()
    {
        if constexpr (!std::is_base_of<VTan, V>())
        {
            return;
        }

        auto _vert = vertices.getData();
        auto _ind = indices.getData();

        for (int i = 0; i < vertices.getSize(); i++)
        {
            _vert[i].bitan = _vert[i].tan = glm::vec3(0, 0, 0);
        }

        for (unsigned int i = 0; i < indices.getSize(); i++) // Computing sum of bitangents for each vertex
        {
            for (int j = 0; j < 3; j++)
            {
                //if((tab[_ind[i].indices[j]]++)!=YuIlhan){continue;}
                glm::vec3 d1 = (_vert[_ind[i].indices[(j + 1) % 3]].pos - _vert[_ind[i].indices[j]].pos);
                glm::vec3 d2 = (_vert[_ind[i].indices[(j + 2) % 3]].pos - _vert[_ind[i].indices[j]].pos);

                glm::vec2 u1 = (_vert[_ind[i].indices[(j + 1) % 3]].tex - _vert[_ind[i].indices[j]].tex);
                glm::vec2 u2 = (_vert[_ind[i].indices[(j + 2) % 3]].tex - _vert[_ind[i].indices[j]].tex);

                _vert[_ind[i].indices[j]].tan += ((d1 * u2.y - d2 * u1.y) / (u2.y * u1.x - u1.y * u2.x));
                _vert[_ind[i].indices[j]].bitan += ((d1 * u2.x - d2 * u1.x) / (u2.x * u1.y - u1.x * u2.y));
            }
        }
        for (unsigned int i = 0; i < vertices.getSize(); i++) //Normalizing tangents and bitangents
        {
            _vert[i].tan = glm::normalize(_vert[i].tan);
            _vert[i].bitan = glm::normalize(_vert[i].bitan);
        }
        flush();
    }
    template <typename V, typename I>
    SimpleMesh<Vertex3pntxy, V3Index> *SimpleMesh<V, I>::generateCuboid(float x, float y, float z)
    {
        auto mesh = new SimpleMesh<Vertex3pntxy, V3Index>();
        mesh->vertices.setBuffer(24);
        mesh->indices.setBuffer(12);
        auto vertices = mesh->vertices.getData();
        auto indices = mesh->indices.getData();
        glm::vec3 dir[] = {glm::vec3(x, 0, 0), glm::vec3(0, y, 0), glm::vec3(0, 0, z)};
        float dims[] = {x,y,z};
        for (int i = 0, k = 0, d = 0; i < 3; i++)
        {
            indices[d++].set(k, k + 1, k + 2);
            indices[d++].set(k + 2, k + 3, k + 1);
            indices[d++].set(k + 4, k + 5, k + 6);
            indices[d++].set(k + 6, k + 7, k + 5);
            for (int a = 0; a < 2; a++)
            {
                for (int b = 0; b < 2; b++)
                {
                    for (int c = 0; c < 2; c++)
                    {
                        vertices[k].pos = dir[i] * (float)(1-2*a) + dir[(i+1)%3]*(float)(1-2*b) + dir[(i+2)%3] *(float)(1-2*c);
                        vertices[k].tex = glm::vec2(dims[(i+1)%3]*(1-2*b),dims[(i+2)%3]*(1-2*c));
                        vertices[k].norm = dir[i] * (float)(1-2*a);
                        k++;
                    }
                }
            }
        }
        mesh->shape = GL_TRIANGLES;
        mesh->computeTangentSpace();
        mesh->flush();
        return mesh;
    }
};     // namespace OpenEngine
#endif /*MESH*/