workspace "Skull"
architecture "x64"
startproject "Sandbox"

configurations
{
	"Debug", -- Pur si simplu debug
	"Release", -- Un fel de debug dar cu mai putine optiune si optimizat
	"Dist"  -- Un fel de release dar fara optiuni
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- pentru compatibilitate

IncludeDir = {}                                                 -- o sa avem mai multe dependecy-uri, asa ca o sa facem o lista pt toate
IncludeDir["GLFW"] = "Skull/vendor/GLFW/include"
IncludeDir["Glad"] = "Skull/vendor/Glad/include"
IncludeDir["ImGui"] = "Skull/vendor/imgui"
IncludeDir["glm"] = "Skull/vendor/glm"

group "Dependencies"
include "Skull/vendor/GLFW" -- acum includem toate librariile din GLFW
include "Skull/vendor/Glad"
include "Skull/vendor/imgui"
group ""

project "Skull"
location "Skull"
kind "SharedLib" -- Specifica ca este DLL
language "C++"
staticruntime "off"

targetdir("bin/" .. outputdir .. "/%{prj.name}") -- target directory
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

pchheader "skpch.h"             -- echivalent cu: hey VS foloseste pch pls
pchsource "Skull/src/skpch.cpp" -- probabil ignorat in alte OS-uri si este echivalent cu: hey VS creeaza pch pls

files
{
	"%{prj.name}/src/**.h", -- ** = sa caute recursiv in folder fisiere cu .h
	"%{prj.name}/src/**.cpp", -- ** = sa caute recursiv in folder fisiere cu .cpp
	"%{prj.name}/vendor/glm/glm/**.hpp",
	"%{prj.name}/vendor/glm/glm/**.inl"
}

includedirs
{
	"%{prj.name}/src",
	"%{prj.name}/vendor/spdlog/include",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.Glad}",
	"%{IncludeDir.ImGui}",
	"%{IncludeDir.glm}"
}

links -- link the shit out of them
{
	"GLFW",
	"Glad",
	"ImGui",
	"opengl32.lib"
}

filter "system:windows" -- macro-uri pentru OS anume
cppdialect "C++20"
systemversion "latest"

defines
{
	"SK_PLATFORM_WINDOWS",
	"SK_BUILD_DLL",
	"GLFW_INCLUDE_NONE"
}

postbuildcommands -- ca sa nu mai copiez dll in sandbox
{
	("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
}

-- buildoptions nu era acolo si facea spdlog sa elibereze memorie aiurea, rezultand la crashuri
-- NOTE: in viitor, daca vreau sa fac dll-uri, ar trebui sa fac buildoptions sa fie cum ii in visual studio la proprietati
filter "configurations:Debug"
defines "SK_DEBUG"
runtime "Debug"
symbols "On"

filter "configurations:Release"
defines "SK_RELEASE"
runtime "Release"
optimize "On"

filter "configurations:Dist"
defines "SK_DIST"
runtime "Release"
optimize "On"

-- pentru viitor
-- filters {"system:windows", "configurations:Release"}
-- buildoptions "/MT"

project "Sandbox"
location "Sandbox"
kind "ConsoleApp" -- Specifica ca este EXE
language "C++"
staticruntime "off"

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
	"Skull/src",
	"%{IncludeDir.glm}"
}

links -- dll
{
	"Skull"
}

filter "system:windows" -- macro-uri pentru OS anume
cppdialect "C++20"
systemversion "latest"

defines
{
	"SK_PLATFORM_WINDOWS"
}

filter "configurations:Debug"
defines "SK_DEBUG"
runtime "Debug"
symbols "On"

filter "configurations:Release"
defines "SK_RELEASE"
runtime "Release"
optimize "On"

filter "configurations:Dist"
defines "SK_DIST"
runtime "Release"
optimize "On"
