-- premake5.lua
workspace "Termimage"
   configurations { "Debug", "Release" }
   
   project "Termimage"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   architecture "x64"
   targetdir "bin/%{cfg.buildcfg}"

   includedirs {
        "./src",
        "./src/vendor/fmt/include",
        "./src/vendor/njson/include",
        "./src/vendor/stb/include"
    }

   files { "**.h", "**.hpp", "**.cpp", "**.cc", "**.cx", "**.c" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
