workspace "opengl-renderer"
	architecture "x64"
	
	configurations {
		"Debug",
		"Release"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "vendor/glfw/include"

-- Includes GLFW premake5.lua --
include "vendor/glfw"

project "opengl-renderer"
	location "opengl-renderer"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"%{prj.name}/**.hpp"
	}
	
	includedirs {
		"%{prj.name}",
		"%{IncludeDir.GLFW}"
	}
	
	links {
		"GLFW"
	}
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"