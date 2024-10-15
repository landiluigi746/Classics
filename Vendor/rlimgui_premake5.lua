--Adapted from Jeffery Myers' https://github.com/raylib-extras/rlImGui

function get_rlImGui_dir()
    return "%{wks.location}/Vendor/rlImGui"
end

function link_rlImGui()
    links { "rlImGui" }
    
    rlImGui_dir = get_rlImGui_dir()

    includedirs { rlImGui_dir }
end

project "rlImGui"
    rlImGui_dir = get_rlImGui_dir()
	
    kind "StaticLib"

    location (rlImGui_dir)
	targetdir "%{wks.location}/Binaries/%{cfg.buildcfg}"
    objdir "%{wks.location}/Objects/%{cfg.buildcfg}"
	
    language "C++"
	cdialect "C99"
	cppdialect "C++17"
    
    includedirs { rlImGui_dir }
	vpaths 
	{
        ["Header Files"] = { rlImGui_dir .. "*.h" },
		["Source Files"] = { rlImGui_dir .. "*.cpp" }
	}
	files { rlImGui_dir .. "/*.h", rlImGui_dir .. "/*.cpp", rlImGui_dir .. "/extras/**.h" }
    
    include_raylib()
    link_imgui()

	defines {"IMGUI_DISABLE_OBSOLETE_FUNCTIONS","IMGUI_DISABLE_OBSOLETE_KEYIO"}