#ifndef RESOURCEHOLDER_H
#define RESOURCEMANAGER_H

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <cassert>
#include <stdexcept>
//#include "NonCopyable.h"
template <typename Resource, typename Identifier>
class ResourceHolder//: NonCopyable
{
    public:
        void                load(Identifier id, const std::string& filename);

        template <typename Parameter>
        void                load (Identifier id, const std::string& filename, const Parameter& secondParam);

        Resource&           get(Identifier id);
        const Resource&     get(Identifier id) const;
        void unload();
        bool isLoaded(const Identifier id) const;

        void remove(const Identifier id);

    private:
        std::map<Identifier, std::unique_ptr<Resource>> resourceMap;
};

//Load resource
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

    auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}


//Load resource
template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename,
                                                const Parameter& secondParam)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, secondParam))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

    auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}


//check to see if a resource has already been loaded
template <typename Resource, typename Identifier>
bool ResourceHolder<Resource, Identifier>::isLoaded(const Identifier id) const
{
    if(resourceMap.find(id) == resourceMap.end())
        return false;

    return true;
}


//Get a reference to resource
template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto foundResource = resourceMap.find(id);
    assert(foundResource != resourceMap.end());

    return *foundResource->second;
}

//Get const reference to resource
template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto foundResource = resourceMap.find(id);
    assert(foundResource != resourceMap.end());

    return *foundResource->second;
}


//Remove resource
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::remove(const Identifier id)
{
    resourceMap.erase(resourceMap.find(id));
}


#endif // RESOURCEHOLDER_H
