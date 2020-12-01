#include "Model.h"
#include "../../Lib/Loaders/MeshLoader.h"
#include "../../Lib/Loaders/MaterialLoader.h"
#include "../../Lib/Render/MeshRenderer.h"
#include "../../Lib/Mesh/Mesh.h"
#include "../../Lib/Material/Material.h"

void Model::init()
{
    OpenEngine::MeshLoader meshLoader;
    OpenEngine::MaterialLoader materialLoader;
    auto meshes = meshLoader.loadMesh("Resources/Models/4/spaceship.obj");
    for(int i =0;i<meshes.size();i++)
    {
        meshes[i].first->shader = shader;
        auto renderer = object->addComponent<OpenEngine::MeshRenderer>();
        renderer->setMesh(meshes[i].second,meshes[i].first);
    }
}
void Model::update(double delta){}