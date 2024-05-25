include "dependencies.lua"

workspace "SOGEEngine"
    architecture "x64"
    startproject "SOGEGame"
    configurations {"Debug", "Release"}

    project "SOGEENgine"
        location "SOGEENgine"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        buildmessage("%{prj.name} workspace location: %{wks.location}")

        targetdir("bin/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")
        objdir("int/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")

        pchheader "sogepch.hpp"
        pchsource "%{wks.location}/%{prj.name}/source/sogepch.cpp"

        files
        {
            "%{wks.location}/%{prj.name}/include/**.hpp",
            "%{wks.location}/%{prj.name}/source/**.cpp",
            "%{wks.location}/%{prj.name}/source/**.inl"
        }

        includedirs
        {
            "%{wks.location}/%{prj.name}/include",
            "%{wks.location}/%{IncludeThirdpartyDirs.spdlog}",
            "%{wks.location}/%{IncludeThirdpartyDirs.DirectXTK}",
            "%{wks.location}/%{IncludeThirdpartyDirs.DirectXTKSrc}",
            "%{wks.location}/%{IncludeThirdpartyDirs.EntityX}",
            "%{wks.location}/%{IncludeThirdpartyDirs.entt}",
            "%{wks.location}/%{IncludeThirdpartyDirs.XoshiroCpp}"
        }

        defines
        {
            "_CRT_SECURE_NO_WARNINGS"
        }

        links
        {
            "d3d11.lib",
            "dxgi.lib",
            "d3dcompiler.lib",
            "dxguid.lib",
            "dxgidebug.dll"
        }

        filter "system:windows"
            systemversion "latest"

            defines
            {
                "SOGE_WINDOWS"
            }

        filter "configurations:Debug"
            symbols "on"

            defines
            {
                "SOGE_DEBUG",
                "SOGE_ENABLE_ASSERT"
            }

            links
            {
                "%{wks.location}/%{Libraries.DirectXTK_LIB_D}"
            }

        filter "configurations:Release"
            optimize "on"

            defines
            {
                "SOGE_RELEASE"
            }

            links
            {
                "%{wks.location}/%{Libraries.DirectXTK_LIB_R}"
            }

-----------------------
--- Engine editor
-----------------------

    project "SOGEGame"
        location "SOGEGame"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
        
        buildmessage("%{prj.name} workspace location: %{wks.location}")

        targetdir("%{wks.location}/%{prj.name}/")
        objdir("int/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")

        files
        {
            "%{wks.location}/%{prj.name}/include/**.hpp",
            "%{wks.location}/%{prj.name}/source/**.cpp"
        }

        includedirs
        {
            "%{wks.location}/%{prj.name}/include",
            "%{wks.location}/SOGEEngine/include",
            "%{wks.location}/SOGEEngine/3rdparty/spdlog/spdlog/include",
            "%{wks.location}/%{IncludeThirdpartyDirs.DirectXTK}",
            "%{wks.location}/%{IncludeThirdpartyDirs.entt}",
            "%{wks.location}/%{IncludeThirdpartyDirs.XoshiroCpp}"
        }

        links
        {
            "SOGEENgine"
        }

        filter "system:windows"
            systemversion "latest"

            defines
            {
                "SOGE_WINDOWS"
            }

        filter "configurations:Debug"
            symbols "on"

            defines
            {
                "SOGE_DEBUG"
            }

        filter "configurations:Release"
            optimize "on"

            defines
            {
                "SOGE_RELEASE"
            }
