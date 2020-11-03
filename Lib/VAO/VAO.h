#ifndef D_VAO
#define D_VAO

#include "../Buffer/Buffer.h"

namespace OpenEngine
{
    class VAO
    {
        unsigned int ID = 0;
        void createVAO(){glGenVertexArrays(1,&ID);}

    public:
        VAO()
        {
            createVAO();
        }
        template <typename A, typename B>
        VAO(Buffer<A, GL_ARRAY_BUFFER> &vert, Buffer<B, GL_ELEMENT_ARRAY_BUFFER> &ind)
        {
            createVAO();
            bind();
            vert.bind();
            ind.bind();
            unbind();
        }
        template <typename A, int target>
        void swapBuffer(Buffer <A,target> &buff)
        {
            bind();
            buff.bind();
            unbind();
        }
        void bind(){glBindVertexArray(ID);}
        void unbind(){glBindVertexArray(0);}
    };
};     // namespace OpenEngine
#endif /*D_VAO*/