function get_raylib_cpp_dir()
    return "%{wks.location}/Vendor/raylib-cpp"
end

function include_raylib_cpp()
    raylib_cpp_dir = get_raylib_cpp_dir()

    includedirs { raylib_cpp_dir .. "/include" }
end

project "raylib-cpp"
    kind "None"
    raylib_dir = get_raylib_dir()
    raylib_cpp_dir = get_raylib_cpp_dir()

    language "C++"
    cppdialect "C++17"

    location (raylib_cpp_dir)
    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"

    vpaths
    {
        ["Header Files"] = { raylib_cpp_dir .. "/include/**.hpp"}
    }

    files { raylib_cpp_dir .. "/include/**.hpp" }

    link_raylib()