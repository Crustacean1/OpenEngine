#include "MeshRenderer.h"
#include "../Mesh/Mesh.h"
#include "../Object/Object.h"
#include "../Material/Material.h"
#include "Render.h"

OpenEngine::MeshRenderer::MeshRenderer(Object & object) : Renderer::Renderer(object,this){}


void OpenEngine::MeshRenderer::render(){}
void OpenEngine::MeshRenderer::prepare()
{}