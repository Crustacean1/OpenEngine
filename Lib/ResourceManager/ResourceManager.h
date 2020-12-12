#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include <string>
#include <memory>
#include <map>
#include <filesystem>
#include <iostream>

namespace OpenEngine
{
    class ResourceManager
    {
        ResourceManager &operator=(const ResourceManager &b);
        ResourceManager(const ResourceManager &b);

    protected:
        ResourceManager() {}
        static std::map<std::string, std::map<std::string, std::shared_ptr<void>>> resources;

    public:
        template <typename T>
        static std::shared_ptr<T> load(std::string filename);
        //UID * operator[](const std::string & index);
        static void confess();
    };

    template <typename T>
    std::shared_ptr<T> ResourceManager::load(std::string filename)
    {
        try
        {
            std::string fullPath = std::filesystem::absolute(std::filesystem::path(filename));
            if (resources.find(typeid(T).name()) != resources.end())
            {
                if (resources[typeid(T).name()].find(fullPath) != resources[typeid(T).name()].end())
                {
                    return std::static_pointer_cast<T>(resources[typeid(T).name()][fullPath]);
                }
            }
            resources[typeid(T).name()][fullPath] = T::defLoader->load(filename.c_str());
            return std::static_pointer_cast<T>(resources[typeid(T).name()][fullPath]);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << '\n';
        }
    }
}; // namespace OpenEngine

#endif /*RESOURCEMANAGER*/