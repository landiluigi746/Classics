function get_imgui_dir()
    return "%{wks.location}/Vendor/imgui"
end

function link_imgui()
    links { "imgui" }

    imgui_dir = get_imgui_dir()

    includedirs { imgui_dir }
end

project "imgui"
    imgui_dir = get_imgui_dir()

    kind "StaticLib"

    location (imgui_dir)

    targetdir "%{wks.location}/Binaries/%{cfg.buildcfg}"
    objdir "%{wks.location}/Objects/%{cfg.buildcfg}"

    includedirs { imgui_dir }
    files { imgui_dir .. "/*.h", imgui_dir .. "/*.cpp" }
    vpaths
    {
        ["Header Files"] = { imgui_dir .. "*.h" },
		["Source Files"] = { imgui_dir .. "*.cpp" }
    }