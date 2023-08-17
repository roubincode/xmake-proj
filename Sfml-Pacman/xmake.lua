add_cxxflags("-std=c++17")

-- sfml
add_includedirs("/usr/local/SFML/include",
                "/usr/local/SFML/include/SFML")
add_linkdirs("/usr/local/SFML/lib")
add_links("sfml-graphics","sfml-system","sfml-window")

-- mingw
set_config("plat", "mingw")
set_config("sdk", "/usr/x86_64-w64-mingw32")
set_config("kind", "static")

-- build
target("pacman")
    set_kind("binary") 
    add_files("Src/**.cpp")
    add_includedirs("Src/include")
    set_toolchains("mingw")
    -- set output dir
    set_targetdir("build")
    -- remove console
    add_ldflags("-mwindows")
    -- copy resources
    after_build(function (target) 
        os.cp("Resources", "$(buildir)")
        os.cp("SFML/lib/*", "$(buildir)/")
    end)