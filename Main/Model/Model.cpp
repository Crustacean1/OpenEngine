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
    auto * mesh = meshLoader.loadMesh("Resources/Models/Model4/nanosuit.obj");
    std::map<std::string,OpenEngine::Material3D*> materials = materialLoader.loadMaterial("Resources/Models/Model4/nanosuit.mtl");
    materials["Body"]->shader = shader;
    object.addComponent<OpenEngine::MeshRenderer>()->addMesh(mesh,materials["Body"]);
}
void Model::update(double delta){}