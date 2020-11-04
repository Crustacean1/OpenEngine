#ifndef MESHRENDERER
#define MESHRENDERER

#include "Renderer.h"
#include "../Buffer/Buffer.h"

namespace OpenEngine
{
    class MeshRenderer :public Renderer
    {
        Buffer<unsigned int,GL_ELEMENT_ARRAY_BUFFER> indices;
        Buffer<Vertex3p,GL_ARRAY_BUFFER> vertices;
        public:
        void render();
        void prepareRender();
    };
};

#endif /*MESHRENDERER*/