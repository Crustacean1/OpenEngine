#ifndef MESHRENDERER
#define MESHRENDERER

#include "Renderer.h"
#include "../Mesh/Mesh.h"

namespace OpenEngine
{
    class MeshRenderer :public Renderer
    {
        std::shared_ptr<Mesh> myMesh;
        std::shared_ptr<Shader> myShader;
        public:

        void render();
        void prepareRender();
        
        std::shared_ptr<Shader> getShader();
        std::shared_ptr<Mesh> getmesh();

        void setMesh(std::shared_ptr<Mesh> _mesh);
        void setShader(std::shared_ptr<Shader> _shader);
    };
};

#endif /*MESHRENDERER*/