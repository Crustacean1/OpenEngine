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
    auto meshes = meshLoader.loadMesh("Resources/Models/Model4/nanosuit.obj");
    auto renderer = object.addComponent<OpenEngine::MeshRenderer>();
    for(int i =0;i<meshes.size();i++)
    {
        meshes[i].first->shader = shader;
        renderer->addMesh(meshes[i].second,meshes[i].first);
    }
}
void Model::update(double delta){}