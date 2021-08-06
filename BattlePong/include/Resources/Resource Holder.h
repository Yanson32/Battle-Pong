#ifndef RESOURCEHOLDER_H
#define RESOURCEMANAGER_H
/**********************************************************//**
*   @brief  This class is designed to hold game resources.
*           game resources should only be loaded into memory
*           once and used repeatedly. The RessourceHolder
*           class is designed to facilitate this. The
*           ResourceHolder class was not written by me
*           and has been modified from the original code.
**************************************************************/

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <cassert>
#include <stdexcept>


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


/************************************************************//**
*   @brief  Load a resource into the ResourceHolder
*   @param  id identifier used to retrive the resource with
*           get method.
*   @param  filename path to the resource to be loaded
****************************************************************/
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

    auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}


/************************************************************//**
*   @brief  Load a resource into the ResourceHolder
*   @param  id identifier used to retrive the resource with
*           get method.
*   @param  filename path to the resource to be loaded
*   @param  secondParam
****************************************************************/
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


/************************************************************//**
*   @brief  Determine if a resource has already been loaded
*   @return true is returned if the resource is loaded and
*           false is returned otherwise.
****************************************************************/
template <typename Resource, typename Identifier>
bool ResourceHolder<Resource, Identifier>::isLoaded(const Identifier id) const
{
    if(resourceMap.find(id) == resourceMap.end())
        return false;

    return true;
}


/************************************************************//**
*   @brief  Get the specified resource. The resource should
*           already be loaded. In debug mode, if the resource
*           hasen't been loaded, an error will result.
*   @param  id the identifier if the resource to be retrieved.
*   @return The resource identifed by id.
****************************************************************/
template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto foundResource = resourceMap.find(id);
    assert(foundResource != resourceMap.end());

    return *foundResource->second;
}


/************************************************************//**
*   @brief  Get the specified resource. The resource should
*           already be loaded. In debug mode, if the resource
*           hasen't been loaded, an error will result.
*   @param  id the identifier if the resource to be retrieved.
*   @return The resource identifed by id.
****************************************************************/
template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto foundResource = resourceMap.find(id);
    assert(foundResource != resourceMap.end());

    return *foundResource->second;
}


/************************************************************//**
*   @brief  Remove a resource from the ResourceHolder.
*   @param  id the identifier if the resource to be retrieved.
****************************************************************/
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::remove(const Identifier id)
{
    resourceMap.erase(resourceMap.find(id));
}


#endif // RESOURCEHOLDER_H
