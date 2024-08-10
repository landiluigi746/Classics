project "Launcher"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    location "./"
    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir "%{wks.location}/bin-int/%{cfg.buildcfg}"

    filter "configurations:Release"
        kind "WindowedApp"
        entrypoint "mainCRTStartup"

    filter "action:vs*"
        debugdir "$(SolutionDir)"

    filter {"action:vs*", "configurations:Release"}
        kind "WindowedApp"
        entrypoint "mainCRTStartup"
    filter {}

    vpaths
    {
        ["Header Files/*"] = { "Source/**.hpp" },
        ["Source Files/*"] = { "Source/**.cpp" },
    }
    files { "Source/**.hpp", "Source/**.cpp" }

    includedirs { "Source" }

    link_raylib()
    include_raylib_cpp()