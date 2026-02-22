project(
   'SilentPatchGTA',
   'cpp',
   version: '7.27',
   license: 'MIT',
   license_files: 'LICENSE',
   default_options: [
      'buildtype=debugoptimized',
      'b_ndebug=if-release',
      'cpp_std=c++17'
   ]
)

cpp = meson.get_compiler('cpp')
fs = import('fs')
windows = import('windows')

if host_machine.cpu_family() != 'x86' or host_machine.system() != 'windows'
   error('This mod only supports 32-bit x86 Windows!')
endif

rwsdkpath = get_option('rwsdkpath')
if rwsdkpath != '' and fs.is_dir(rwsdkpath)
   rwsdk_found = true
else
   warning('RenderWare SDK was not found (non-ddraw compilation will fail)')
   rwsdk_found = false
endif

# Set Windows version to XP
add_project_arguments('-DWINVER=0x0501', '-D_WIN32_WINNT=0x0501', language: 'cpp')

# PATTERNS_USE_HINTS=1: Expose pattern functions required by SilentPatch
# _USE_MATH_DEFINES: Make sure that M_PI gets defined
add_project_arguments('-DPATTERNS_USE_HINTS=1', '-D_USE_MATH_DEFINES', language: 'cpp')

if cpp.get_id() == 'msvc'
   # /Zc:threadSafeInit-: Avoid UCRT requirement for WinXP support
   # /LARGEADDRESSAWARE: Allow the library to use higher memory addreses
   add_project_arguments('/Zc:threadSafeInit-', language: 'cpp')
   add_project_link_arguments('/LARGEADDRESSAWARE', language: 'cpp')
else
   gcc_args = [
      '-masm=intel', # Inline ASM blocks use Intel syntax
      '-mincoming-stack-boundary=2' # Make sure stack is aligned to the x86 ABI
   ]
   gcc_link_args = [
      '-Wl,--large-address-aware', # Same explanation as MSVC
      '-static', # Remove external GCC library requirement for the mod
      '-static-libgcc',
      '-static-libstdc++'
   ]

   foreach gcc_arg : gcc_args
      if cpp.has_argument(gcc_arg)
         add_project_arguments(gcc_arg, language: 'cpp')
      endif
   endforeach

   foreach gcc_link_arg : gcc_link_args
      if cpp.has_link_argument(gcc_link_arg)
         add_project_link_arguments(gcc_link_arg, language: 'cpp')
      endif
   endforeach
endif

# Library used by all of SilentPatch
shlwapi_dep = cpp.find_library('shlwapi')

common_include = include_directories('SilentPatch')

# Source files used by all SilentPatch parts
common_files = files(
   'SilentPatch/Desktop.cpp',
   'SilentPatch/Utils/Patterns.cpp'
)
common_res = files('SilentPatch/SilentPatch.rc')

# Reference to the .asi suffix
asi_suffix = 'asi'

subdir('DDraw')

## SilentPatchIII/VC ##

iiivc_include = [
   common_include
]

if rwsdk_found
   iiivc_include += include_directories(rwsdkpath / 'include/d3d8')
endif

iiivc_files = files(
   'SilentPatch/Common.cpp',
   'SilentPatch/Common_ddraw.cpp',
   'SilentPatch/ParseUtils.cpp',
   'SilentPatch/RWGTA.cpp',
   'SilentPatch/StoredCar.cpp',
   'SilentPatch/SVF.cpp',
   'SilentPatch/TheFLAUtils.cpp',
   'SilentPatch/Timer.cpp'
)

iiivc_sources = [
   common_files,
   iiivc_files
]

subdir('SilentPatchIII')
subdir('SilentPatchVC')

# TODO: Add SilentPatchSA
