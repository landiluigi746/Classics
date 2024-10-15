function link_Common()
    links { "Common" }

    includedirs { "%{wks.location}/Common/src" }
end

project "Common"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    location "./"
    targetdir "%{wks.location}/Binaries/%{cfg.buildcfg}"
    objdir "%{wks.location}/Objects/%{cfg.buildcfg}"

    filter "action:vs*"
        debugdir "$(SolutionDir)"

    vpaths
    {
        ["Header Files/*"] = { "src/**.hpp" },
        ["Source Files/*"] = { "src/**.cpp" }
    }
    files { "src/**.hpp", "src/**.cpp" }

    includedirs { "src" }
    
    link_raylib()
    link_imgui()
    link_rlImGui()