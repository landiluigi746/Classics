project "Common"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    location "./"
    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir "%{wks.location}/bin-int/%{cfg.buildcfg}"

    vpaths
    {
        ["Header Files/*"] = { "Source/**.hpp" },
        ["Source Files/*"] = { "Source/**.cpp" },
    }
    files { "Source/**.hpp", "Source/**.cpp" }

    includedirs { "Source" }

    link_raylib()
    include_raylib_cpp()