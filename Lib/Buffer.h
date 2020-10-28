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

    struct Vertex3pc
    {
        glm::vec3 pos;
        glm::vec3 col;
        static void setAttribs()
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(sizeof(float) * 3));
            glEnableVertexAttribArray(1);
        }
    };
    struct Vertex3pcn
    {
        glm::vec3 pos;
        glm::vec3 col;
        glm::vec3 norm;
        static void setAttribs()
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(sizeof(float) * 3));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(sizeof(float) * 6));
            glEnableVertexAttribArray(2);
        }
    };

    template <typename T, int target>
    class Buffer
    {
        std::shared_ptr<T> data;
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
        Buffer() {initBuffer();}
        template <typename... Types>
        Buffer(Types... types)
        {
            data = std::shared_ptr<T>(new T[sizeof...(types)]{types...});
            size = sizeof...(types);
            initBuffer();
            flush();
        }
        Buffer(unsigned int _size)
        {
            data = new T[_size];
            size = _size;
            initBuffer();
            flush();
        }
        void setBuffer(std::shared_ptr<T> _data, unsigned int _size)
        {
            data = _data;
            size = _size;
        }
        void flush()
        {
            glBufferData(target, size * sizeof(T), data.get(), GL_STATIC_DRAW);
        }
        T &operator[](unsigned int index) // No index checking, performance is crucial, ev. modulo?
        {
            return data.get()[index];
        }
        void bind()
        {
            glBindBuffer(target, ID);
            if constexpr (target == GL_ARRAY_BUFFER)
            {
                T::setAttribs();
            }
        }
        Buffer<T,target>& operator=(Buffer<T,target> buff)
        {
            ID = buff.ID;
            active = buff.active;
            size = buff.size;
            memcpy(data,buff.data,sizeof(T)*size);
            return *this;
        }
        ~Buffer()
        {
            deleteBuffer();
        }
    };

}; // namespace OpenEngine

#endif /*BUFFER*/