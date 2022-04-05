#ifndef LOADER
#define LOADER

#include <string>
#include <memory>
#include <map>

namespace OpenEngine
{
    std::string expandResourcePath(std::string filename);
    template <typename T>
    class Loader
    {
        std::map<std::string, std::shared_ptr<T>> resources;

    protected:
        std::shared_ptr<T> getResource(std::string path);
        std::shared_ptr<T> addResource(std::string path, const std::shared_ptr<T> &res);
    };
    template <typename T>
    std::shared_ptr<T> Loader<T>::getResource(std::string path)
    {
        std::string fullpath = expandResourcePath(path);
        if (resources.find(fullpath) != resources.end())
        {
            return resources[fullpath];
        }
        return nullptr;
    }
    template <typename T>
    std::shared_ptr<T> Loader<T>::addResource(std::string path, const std::shared_ptr<T> &res)
    {
        if (res != nullptr)
        {
            std::string fullpath = expandResourcePath(path);
            resources[fullpath] = res;
        }
        return res;
    }
}; // namespace OpenEngine

#endif /*LOADER*/