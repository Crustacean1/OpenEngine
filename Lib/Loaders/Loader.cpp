#include "Loader.h"
#include <filesystem>

std::string OpenEngine::getFullResourcePath(std::string filename)
{
    return std::filesystem::absolute(std::filesystem::path(filename));
}