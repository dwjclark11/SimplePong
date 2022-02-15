-- Currently Builds for Windows using Visual Studio 2019 Community!

workspace "SimplePong"
	system "Windows"
	architecture "x86"

	configurations
	{
		"Debug",	-- All debug information
		"Release",	-- Still has logging
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "SimplePong"
	location "SimplePong"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}" )

	-- Declare the header file
	pchheader "stdafx.h"
	pchsource "SimplePong/src/stdafx.cpp" -- Only needed for visual studio will be ignored by others


	-- Included files and folders
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.inl",
	}

	-- C/C++: General - Additional Include Directories
	includedirs
	{
		"%{prj.name}/libs/SFML/include",
	}
	-- Linker: General - Additional Library Dependencies
	libdirs
	{
		"%{prj.name}/libs/SFML/lib",
	}	

	-- Filters for different platforms
	filter "system:windows"
		systemversion "latest" 

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"WIN32",
		}

	filter "configurations:Debug"
		buildoptions "/MTd"
		runtime "Debug"
		symbols "on"
	-- Input: Addidtional Dependencies
		links
		{
			"sfml-window-d",
			"sfml-graphics-d",
			"sfml-system-d",
			"sfml-audio-d",
			"sfml-network-d",
		}

	filter "configurations:Release"
		buildoptions "/MT"
		runtime "Release"
		optimize "full"
		links
		{
			"sfml-window",
			"sfml-graphics",
			"sfml-system",
			"sfml-audio",
			"sfml-network",
		}

