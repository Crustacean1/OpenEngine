#ifndef BUFFER
#define BUFFER

#include <iostream>

#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace OpenEngine //tuple or inheritance
{
    struct VPos
    {
        glm::vec3 pos;
        //VPos(glm::vec3 _p = glm::vec3(0, 0, 0)) : pos(_p) {}
    };
    struct VNorm
    {
        glm::vec3 norm;
        //VNorm(glm::vec3 _n = glm::vec3(0, 0, 0)) : norm(_n) {}
    };
    struct VTex
    {
        glm::vec2 tex;
        //VTex(glm::vec2 _t = glm::vec2(0, 0)) : tex(_t) {}
    };
    struct VCol
    {
        glm::vec3 col;
        //VCol(glm::vec3 _c = glm::vec3(0,0,0)) : col(_c){}
    };
    struct VTan
    {
        glm::vec3 tan;
        glm::vec3 bitan;
        //VTan(glm::vec3 _t = glm::vec3(0, 0, 0), glm::vec3 _b = glm::vec3(0, 0, 0)) : tan(_t), bitan(_b) {}
    };
    struct Vertex3p
    {
        glm::vec3 pos;
        static void setAttribs()
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
        }
        Vertex3p() {}
        Vertex3p(glm::vec3 _pos) : pos(_pos) {}
    };

    struct Vertex3pc : public VPos, public VCol
    {
        static void setAttribs()
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(sizeof(float) * 3));
            glEnableVertexAttribArray(1);
        }
    };
    struct Vertex3pcn : public VPos, public VCol, public VNorm
    {
        static void setAttribs()
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(sizeof(float) * 3));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(sizeof(float) * 6));
            glEnableVertexAttribArray(2);
        }
    };
    struct Vertex3pntxy : public VPos, public VNorm, public VTex, public VTan
    {
        static void setAttribs()
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *)(sizeof(float) * 3));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *)(sizeof(float) * 6));
            glEnableVertexAttribArray(2);

            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *)(sizeof(float) * 8));
            glEnableVertexAttribArray(3);

            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *)(sizeof(float) * 11));
            glEnableVertexAttribArray(4);
        }
    };

    struct V3Index
    {
        static const int size = 3;
        unsigned int indices[size];
        V3Index() {}
        V3Index(unsigned int a, unsigned int b, unsigned int c)
        {
            indices[0] = a;
            indices[1] = b;
            indices[2] = c;
        }
        void set(unsigned int a, unsigned int b, unsigned int c)
        {
            indices[0] = a;
            indices[1] = b;
            indices[2] = c;
        }
    };
    struct V2Index
    {
        static const int size = 2;
        unsigned int indices[size];
        V2Index() {}
        V2Index(unsigned int a, unsigned int b)
        {
            indices[0] = a;
            indices[1] = b;
        }
        void set(unsigned int a, unsigned int b)
        {
            indices[0] = a;
            indices[1] = b;
        }
    };

    template <typename T, int target>
    class Buffer
    {
        T* data;
        unsigned int size;
        unsigned int ID;
        bool active = false;

        void initBuffer()
        {
            if (active)
            {
                return;
            }
            active = true;

            glGenBuffers(1, &ID);
            bind();
        }
        void deleteBuffer()
        {
            if (!active)
            {
                return;
            }
            active = false;
            glDeleteBuffers(1, &ID);
            size = 0;
            data = nullptr;
        }

    public:
        Buffer() { initBuffer(); }
        template <typename... Types>
        Buffer(Types... types)
        {
            data = new T[sizeof...(types)]{types...};
            size = sizeof...(types);
            initBuffer();
            flush();
        }
        Buffer(unsigned int _size)
        {
            setBuffer(_size);
            initBuffer();
            flush();
        }
        void setBuffer(T* _data, unsigned int _size)
        {
            data = _data;
            size = _size;
        }
        void setBuffer(unsigned int _size)
        {
            data = new T[_size];
            size = _size;
        }
        void flush()
        {
            glBufferData(target, size * sizeof(T), data, GL_STATIC_DRAW);
        }
        T &operator[](unsigned int index) // No index checking, performance is crucial, ev. modulo?
        {
            return data[index];
        }
        void bind()
        {
            glBindBuffer(target, ID);
            if constexpr (target == GL_ARRAY_BUFFER)
            {
                T::setAttribs();
            }
        }
        Buffer<T, target> &operator=(Buffer<T, target> buff)
        {
            ID = buff.ID;
            active = buff.active;
            size = buff.size;
            buff.data = new T[size];
            memcpy(data, buff.data, sizeof(T) * size);
            return *this;
        }
        ~Buffer()
        {
            deleteBuffer();
        }
        unsigned int getSize() { return size; }
        T* getData() { return data; }
    };

}; // namespace OpenEngine

#endif /*BUFFER*/