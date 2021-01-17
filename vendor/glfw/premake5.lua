workspace "opengl-renderer"
	architecture "x64"
	
	configurations {
		"Debug",
		"Release"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
	}
	
	links {
		"GLFW",
		"GLAD",
		"opengl32.lib",
		"assimp-vc142-mt.lib"
	}
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"