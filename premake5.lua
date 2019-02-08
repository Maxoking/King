workspace "King"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

project "King"
	location "King"
	kind "SharedLib"
	language "C++"

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
		"%{prj.name}/vendor/spdlog/include"
	}

	cppdialect "C++17"
	staticruntime "On"
	systemversion "10.0.17763.0"

	defines
	{
		"KING_BUILD_DLL"
	}




	filter "configurations:Debug"
		defines "KING_DEBUG"
		symbols "On"


	filter "configurations:Release"
		defines "KING_RELEASE"
		symbols "On"


	filter "configurations:Dist"
	defines "KING_DIST"
	symbols "On"

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
		"King/vendor/spdlog/include",
		"King/src"
	}

	links
	{
		"King"
	}

	cppdialect "C++17"
	staticruntime "On"
	systemversion "10.0.17763.0"

	filter "configurations:Debug"
		defines "KING_DEBUG"
		symbols "On"


	filter "configurations:Release"
		defines "KING_RELEASE"
		symbols "On"


	filter "configurations:Dist"
	defines "KING_DIST"
	symbols "On"