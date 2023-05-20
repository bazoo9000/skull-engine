workspace "Skull"
architecture "x64"

configurations
{
	"Debug", -- Pur si simplu debug
	"Release", -- Un fel de debug dar cu mai putine optiune si optimizat
	"Dist"  -- Un fel de release dar fara optiuni
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- pentru compatibilitate

IncludeDir = {}                                                 -- o sa avem mai multe dependecy-uri, asa ca o sa facem o lista pt toate
IncludeDir["GLFW"] = "Skull/vendor/GLFW/include"
include "Skull/vendor/GLFW"                                     -- acum includem toate librariile din GLFW

project "Skull"
location "Skull"
kind "SharedLib" -- Specifica ca este DLL
language "C++"

targetdir("bin/" .. outputdir .. "/%{prj.name}") -- target directory
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

pchheader "skpch.h"             -- echivalent cu: hey VS foloseste pch pls
pchsource "Skull/src/skpch.cpp" -- probabil ignorat in alte OS-uri si este echivalent cu: hey VS creeaza pch pls

files
{
	"%{prj.name}/src/**.h", -- ** = sa caute recursiv in folder fisiere cu .h
	"%{prj.name}/src/**.cpp" -- ** = sa caute recursiv in folder fisiere cu .cpp
}

includedirs
{
	"%{prj.name}/src",
	"%{prj.name}/vendor/spdlog/include",
	"%{IncludeDir.GLFW}"
}

links -- link the shit out of them
{
	"GLFW",
	"opengl32.lib"
}

filter "system:windows" -- macro-uri pentru OS anume
cppdialect "C++20"
staticruntime "On"      -- responsabil pentru link-urile statice
systemversion "latest"

defines
{
	"SK_PLATFORM_WINDOWS",
	"SK_BUILD_DLL"
}

postbuildcommands -- ca sa nu mai copiez dll in sandbox
{
	("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
}

filter "configurations:Debug"
defines "SK_DEBUG"
symbols "On"

filter "configurations:Release"
defines "SK_RELEASE"
optimize "On"

filter "configurations:Dist"
defines "SK_DIST"
optimize "On"

-- pentru viitor
--filters {"system:windows", "configurations:Release"}
--buildoptions "/MT"

project "Sandbox"
location "Sandbox"
kind "ConsoleApp" -- Specifica ca este EXE
language "C++"

targetdir("bin/" .. outputdir .. "/%{prj.name}") -- target directory
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files
{
	"%{prj.name}/src/**.h", -- ** = sa caute recursiv in folder fisiere cu .h
	"%{prj.name}/src/**.cpp" -- ** = sa caute recursiv in folder fisiere cu .cpp
}

includedirs
{
	"Skull/vendor/spdlog/include",
	"Skull/src"
}

links -- dll
{
	"Skull"
}

filter "system:windows" -- macro-uri pentru OS anume
cppdialect "C++20"
staticruntime "On"      -- responsabil pentru link-urile statice
systemversion "latest"

defines
{
	"SK_PLATFORM_WINDOWS"
}

filter "configurations:Debug"
defines "SK_DEBUG"
symbols "On"

filter "configurations:Release"
defines "SK_RELEASE"
optimize "On"

filter "configurations:Dist"
defines "SK_DIST"
optimize "On"
