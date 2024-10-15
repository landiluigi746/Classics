project "Launcher"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    location "./"
    targetdir "%{wks.location}/Binaries/%{cfg.buildcfg}"
    objdir "%{wks.location}/Objects/%{cfg.buildcfg}"

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
        ["Header Files/*"] = { "src/**.hpp" },
        ["Source Files/*"] = { "src/**.cpp" },
        ["Resource Files/*"] = { "**.rc" }
    }
    files { "src/**.hpp", "src/**.cpp", "**.rc", "**.h" }

    includedirs { "src" }
    
    link_raylib()
    link_imgui()
    link_rlImGui()
    link_Common()
    link_Games()