#include "ResourceHolder.h"

/* One thing we have to note when using templates is that the complete implementation needs to be in the header file. We cannot use .cpp!!!
for this method definitions anymore, but we would still like to separate interface and implementations. That is why we use a file ResourceHolder.hpp
for the class definition, and a file ResourceHolder.inl for the method definitions. At the end of the .hpp, we include the .inl file containing the
implementation. .inl is a common file extension for inline template implementations. */

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier ID, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());

	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - failed to load " + filename);


	insertResource(ID, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier ID, const std::string& filename, const Parameter& secondParam)
{
	std::unique_ptr<Resource> resource(new Resource());

	if (!resource->loadFromFile(filename, secondParam))
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load" + filename);


		/*	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
			assert(inserted.second);*/
	}
	insertResource(ID, std::move(resource));
}


template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier ID)
{
	auto found = mResourceMap.find(ID);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier ID) const
{
	auto found = mResourceMap.find(ID);
	assert(found != mResourceMap.end());

	return *found->second; //Be careful when using pointers!!!!
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier ID, std::unique_ptr<Resource> resource)
{
	//Insert and check success
	auto inserted = mResourceMap.insert(std::make_pair(ID, std::move(resource)));
	assert(inserted.second);
}
