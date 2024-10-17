function gameProject(game)
    project (game)
        dir = ("./" .. game .. "/")
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        location (dir)
        targetdir "%{wks.location}/Binaries/%{cfg.buildcfg}"
        objdir "%{wks.location}/Objects/%{cfg.buildcfg}"

        filter "action:vs*"
            debugdir "$(SolutionDir)"

        vpaths
        {
            ["Header Files/*"] = { dir .. "src/**.hpp" },
            ["Source Files/*"] = { dir .. "src/**.cpp" }
        }
        files { dir .. "src/**.hpp", dir .. "src/**.cpp" }
        
        defines { string.upper(game) .. "_ASSETS_PATH=\"" .. "Games/" .. game .. "/" .. "assets/\"" }

        includedirs { dir .. "src" }
        
        link_raylib()
        link_imgui()
        link_rlImGui()
        link_Common()
end

local dirs = io.popen("dir /b /ad"):lines()

function linkgame(game)
    games_dir = "%{wks.location}/Games"
    print(game)
    links { game }
    includedirs { games_dir .. "/" .. game .. "/src" }
end

function link_Games()
    games_dir = "%{wks.location}/Games"
    for dir in dirs do
        linkgame(dir)
    end
end

for dir in io.popen("dir /b /ad"):lines() do
    gameProject(dir)
end