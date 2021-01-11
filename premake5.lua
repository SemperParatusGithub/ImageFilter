workspace "ImageFilter"
	architecture "x64"
	configurations { "Debug", "Release" }

project "ImageFilter"
	location "ImageFilter"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
	objdir ("obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

	files { 
 		"ImageFilter/src/**.h",
		"ImageFilter/src/**.cpp",
		"ImageFilter/3rdParty/stb_image/**.h",
		"ImageFilter/3rdParty/stb_image/**.cpp",
	}
	includedirs { 
		"ImageFilter/3rdParty/stb_image"
	}

	filter "system:windows"
		systemversion "latest"
		defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "system:linux"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		symbols "Off"
		optimize "Full"
		runtime "Release"