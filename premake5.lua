workspace "Voxitol"
	architecture "x64"
	startproject  "Voxitol"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

IncludeDir = {}
IncludeDir["GLFW"] = "Voxitol/Vendor/GLFW/include"
IncludeDir["GLAD"] = "Voxitol/Vendor/glad/include"
IncludeDir["GLM"] = "Voxitol/Vendor/glm"
IncludeDir["ImGUI"] = "Voxitol/Vendor/imgui"
IncludeDir["STB"] = "Voxitol/Vendor/stb_image"
IncludeDir["YamlCPP"] = "Voxitol/Vendor/yaml-cpp/include"

include "Voxitol/Vendor/GLFW"
include "Voxitol/Vendor/ImGui"
include "Voxitol/Vendor/yaml-cpp"
	
project "Voxitol"
	location "Voxitol/source"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "vxpch.h"
	pchsource "Voxitol/Source/vxpch.cpp"

	files
	{
		"Voxitol/Source/**.h",
		"Voxitol/Source/**.cpp",
		"Voxitol/Vendor/stb_image/**.h",
		"Voxitol/Vendor/stb_image/**.cpp",
		"Voxitol/Vendor/glad/**.c"
	}

	includedirs
	{
		"Voxitol/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.YamlCPP}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}
	
	filter "files:Voxitol/Vendor/**.c"
		flags { "NoPCH" }
	filter "files:Voxitol/Vendor/**.cpp"
		flags { "NoPCH" }

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"VX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "VX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VX_RELEASE"
		optimize "On"