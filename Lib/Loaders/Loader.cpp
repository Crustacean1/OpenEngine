#include "Loader.h"
#include <filesystem>

std::string OpenEngine::expandResourcePath(std::string filename)
{
    return std::filesystem::absolute(std::filesystem::path(filename));
}