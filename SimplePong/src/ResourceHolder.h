#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

/* Here we are creating a Resource Holder Template. This will have two template parameters: Resource --> The Type of Resource 
that you would need to load a file from or your own resource class which conforms to the desired interface.
Identifer --> The ID type for the resource to access, for example, Textures::ID. */

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier ID, const std::string& filename);
	
	template <typename Parameter>
	void load(Identifier ID, const std::string& filename, const Parameter& secondParameter);

	Resource& get(Identifier ID);
	const Resource& get(Identifier ID) const;

private:
	void insertResource(Identifier ID, std::unique_ptr<Resource> resource);

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;

};

#include "ResourceHolder.inl"

