#include "Model.h"
#include "../../Lib/Loaders/MeshLoader/MeshLoader.h"
#include "../../Lib/Loaders/MaterialLoader/MaterialLoader.h"
#include "../../Lib/Render/MeshRenderer.h"
#include "../../Lib/Render/Render.h"
#include "../../Lib/Mesh/Mesh.h"
#include "../../Lib/Object/Object.h"
#include "../../Lib/Material/Material.h"

void Model::init()
{
    OpenEngine::MeshLoader meshLoader;
    OpenEngine::MaterialLoader materialLoader;
    auto meshes = meshLoader.loadMesh("Resources/Models/4/spaceship.obj");
    for(int i =0;i<meshes.size();i++)
    {
        meshes[i].first->shader = shader;
        auto renderer = object.addComponent<OpenEngine::MeshRenderer>();
        renderer->setMesh(meshes[i].second,meshes[i].first);
    }
}
void Model::update(double delta){}