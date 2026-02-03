if _ACTION then
   rwsdk = os.getenv("RW37SDK")
   if not rwsdk or not os.isdir(rwsdk) then
      print("Failed to find RenderWare (3.7) SDK folder!")
      print("Make sure RW37SDK variable is set for non-DDraw compilation to work")
   end
end

workspace "SilentPatchGTA"
   platforms { "WinXP", "Win7" }
   configurations { "Debug", "Release", "Shipping" }
   location "build-premake"

project "*"
   kind "SharedLib"
   targetextension ".asi"
   language "C++"

   cppdialect "C++17"
   staticruntime "On"

   system "windows"
   links "shlwapi" -- Library used by most (if not all) of SilentPatch

   -- Expose pattern functions required by SilentPatch
   defines { "PATTERNS_USE_HINTS=1" }

	-- Auto-generated defines for resources
	defines { "SILENTPATCH_EXT=\"%{prj.targetextension}\"",
         "SILENTPATCH_NAME=\"%{prj.name}\"" }

   includedirs { "SilentPatch" }

   -- Source files used by all SilentPatch parts
   files { "SilentPatch/Desktop.cpp", "SilentPatch/Utils/Patterns.cpp", "SilentPatch/SilentPatch.rc" }

   -- Environment/configuration-specific settings
   filter "configurations:not Debug"
      optimize "Speed"
      functionlevellinking "On"
      linktimeoptimization "On"

   filter "configurations:Debug"
      defines { "DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Shipping"
      defines { "NDEBUG" }

   filter { "configurations:Shipping", "toolset:msc*" }
      linkoptions { "/pdbaltpath:%_PDB%" }

   filter "platforms:WinXP"
      defines { "WINVER=0x0501", "_WIN32_WINNT=0x0501" } -- Target WinXP

   filter { "platforms:WinXP", "toolset:msc*" }
      buildoptions { "/Zc:threadSafeInit-" }

   filter "platforms:Win7"
      defines { "WINVER=0x0601", "_WIN32_WINNT=0x0601" } -- Target Win7
      conformancemode "on"

   filter "toolset:msc*"
      buildoptions { "/sdl" }
      architecture "x86"

   filter "toolset:not msc*"
      buildoptions  { "-masm=intel" } -- Inline ASM blocks use Intel syntax
      defines { "_USE_MATH_DEFINES" } -- Make sure that M_PI gets defined
      architecture "ARM" -- Hack to prevent messing up LDFLAGS on MinGW GCC

project "DDraw"
   include "DDraw/VersionInfo.lua"

   targetname "ddraw"
   targetextension ".dll"

   defines { "SILENTPATCH_NAME=SilentPatchDDraw" }

   files { "SilentPatch/Common_ddraw.cpp", "DDraw/dllmain.cpp", "DDraw/DDraw.def" }

project "SilentPatchIII"
   include "SilentPatchIII/VersionInfo.lua"

   defines { "_GTA_III" }

   if _ACTION and os.getenv("RW37SDK") then
      includedirs({ os.getenv("RW37SDK") .. "/include/d3d8" })
   end

   files {
      "SilentPatch/Common.cpp",
      "SilentPatch/Common_ddraw.cpp",
      "SilentPatch/ParseUtils.cpp",
      "SilentPatch/RWGTA.cpp",
      "SilentPatch/StoredCar.cpp",
      "SilentPatch/SVF.cpp",
      "SilentPatch/TheFLAUtils.cpp",
      "SilentPatch/Timer.cpp",
      "SilentPatchIII/*.cpp"
   }

project "SilentPatchVC"
   include "SilentPatchVC/VersionInfo.lua"

   defines { "_GTA_VC" }

   if _ACTION and os.getenv("RW37SDK") then
      includedirs({ os.getenv("RW37SDK") .. "/include/d3d8" })
   end

   files {
      "SilentPatch/Common.cpp",
      "SilentPatch/Common_ddraw.cpp",
      "SilentPatch/ParseUtils.cpp",
      "SilentPatch/RWGTA.cpp",
      "SilentPatch/StoredCar.cpp",
      "SilentPatch/SVF.cpp",
      "SilentPatch/TheFLAUtils.cpp",
      "SilentPatch/Timer.cpp",
      "SilentPatchVC/*.cpp"
   }

project "SilentPatchSA"
   include "SilentPatchSA/VersionInfo.lua"

   -- TODO: Add FLAC support
   defines { "_GTA_SA", "NO_FLAC_SUPPORT" }

   if _ACTION and os.getenv("RW37SDK") then
      includedirs({ os.getenv("RW37SDK") .. "/include/d3d9" })
   end

   includedirs { "SilentPatchSA" }

   files {
      "SilentPatch/FriendlyMonitorNames.cpp",
      "SilentPatch/ParseUtils.cpp",
      "SilentPatch/SVF.cpp",
      "SilentPatch/TheFLAUtils.cpp",
      "SilentPatchSA/*.cpp",
      "SilentPatchSA/SilentPatchSA.rc"
   }
