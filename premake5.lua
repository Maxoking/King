workspace "King"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "King/vendor/GLFW/include"
IncludeDir["Glad"] = "King/vendor/Glad/include"
IncludeDir["ImGUI"] = "King/vendor/ImGUI/"
IncludeDir["Assimp"] = "King/vendor/Assimp/include"
IncludeDir["stb_image"] = "King/vendor/stb_image"

include "King/vendor/GLFW"
include "King/vendor/Glad"
include "King/vendor/ImGUI"

project "King"
	location "King"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "kngpch.h"
	pchsource "King/src/kngpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.vert",
		"%{prj.name}/src/**.frag"
	}


	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/glm",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.Assimp}",
		"%{IncludeDir.stb_image}"
	}
	
	libdirs
	{
		"King/vendor/Assimp/lib"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGUI",
		"assimpd.lib",
		"opengl32.lib"
	}


	systemversion "latest"

	defines
	{
		"KING_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}


	filter "configurations:Debug"
		defines "KING_DEBUG"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		defines "KING_RELEASE"
		runtime "Release"
		optimize "on"


	filter "configurations:Dist"
		defines "KING_DIST"
		runtime "Release"
		optimize "on"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.Assimp}",
		"King/vendor/spdlog/include",
		"King/vendor/glm",
		"King/src"
	}

	links
	{
		"King"
	}
	
	systemversion "latest"

	defines
	{
		"GLFW_INCLUDE_NONE"
	}



	filter "configurations:Debug"
		defines "KING_DEBUG"
		runtime "Debug"
		symbols "on"		

	filter "configurations:Release"
		defines "KING_RELEASE"
		runtime "Release"
		symbols "on"

	filter "configurations:Dist"
		defines "KING_DIST"
		runtime "Release"
		symbols "on"