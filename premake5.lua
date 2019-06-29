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

include "King/vendor/GLFW"
include "King/vendor/Glad"
include "King/vendor/ImGUI"

project "King"
	location "King"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "kngpch.h"
	pchsource "King/src/kngpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	postbuildcommands
	{
		"{COPY}  %{cfg.targetdir}/King.dll  %{cfg.targetdir}/../Sandbox"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/glm",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGUI}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGUI",
		"opengl32.lib"
	}

	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

	defines
	{
		"KING_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}




	filter "configurations:Debug"
		defines "KING_DEBUG"
		symbols "On"
		buildoptions "/MDd"


	filter "configurations:Release"
		defines "KING_RELEASE"
		symbols "On"
		buildoptions "/MD"


	filter "configurations:Dist"
		defines "KING_DIST"
		symbols "On"
		buildoptions "/MD"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"King/vendor/spdlog/include",
		"King/vendor/glm",
		"King/src"
	}

	links
	{
		"King",
		"Glad"
	}

	defines
	{
		"GLFW_INCLUDE_NONE"
	}

	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"
	staticruntime "off"

	filter "configurations:Debug"
		defines "KING_DEBUG"
		symbols "On"		
		buildoptions "/MDd"


	filter "configurations:Release"
		defines "KING_RELEASE"
		symbols "On"
		buildoptions "/MD"


	filter "configurations:Dist"
		defines "KING_DIST"
		symbols "On"
		buildoptions "/MD"