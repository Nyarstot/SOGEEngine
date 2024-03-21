project "EntityX"
    kind "StaticLib"
    language "C++"
    staticruntime "On"

    targetdir("bin/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")
    objdir("int/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")

    files
    {
        "EntityX/entityx/3rdparty/catch.h",
        "EntityX/entityx/3rdparty/simplesignal.h",
        
        "EntityX/entityx/deps/Dependencies.h",

        "EntityX/entityx/help/NonCopyable.h",
        "EntityX/entityx/help/Pool.cc",
        "EntityX/entityx/help/Pool.h",
        "EntityX/entityx/help/Timer.cc",
        "EntityX/entityx/help/Timer.h",

        "EntityX/entityx/tags/TagsComponent.h",

        "EntityX/entityx/Entity.cc",
        "EntityX/entityx/Entity.h",
        "EntityX/entityx/Entityx.h",
        "EntityX/entityx/Event.cc",
        "EntityX/entityx/Event.h",
        "EntityX/entityx/quick.h",
        "EntityX/entityx/System.cc",
        "EntityX/entityx/Entity.h",

        "include/entityx/config.h"
    }

    includedirs
    {
        "./EntityX/",
        "./include/"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"