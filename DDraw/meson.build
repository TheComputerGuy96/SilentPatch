ddraw_name = 'ddraw'

# TODO: Simplify the resource handling code
ddraw_meta = [
   '-DSILENTPATCH_EXT=".dll"',
   '-DSILENTPATCH_NAME="' + ddraw_name + '"',
   '-DSILENTPATCH_FULL_NAME="SilentPatch DDraw Component"',
   '-DSILENTPATCH_REVISION_ID=6',
   '-DSILENTPATCH_BUILD_ID=1',
   '-DSILENTPATCH_COPYRIGHT=2014-2024'
]

ddraw_conf = configure_file(
   input: common_res,
   output: 'SilentPatch_' + ddraw_name + '.rc',
   copy: true
)
ddraw_res = windows.compile_resources(
   ddraw_conf,
   args: ddraw_meta,
   include_directories: common_include
)

ddraw_sources = [
   common_files,
   ddraw_res,
   '../SilentPatch/Common_ddraw.cpp',
   'dllmain.cpp'
]

shared_library(
   ddraw_name,
   ddraw_sources,
   name_prefix: '',
   cpp_args: ddraw_meta,
   include_directories: common_include,
   dependencies: shlwapi_dep,
   vs_module_defs: 'DDraw.def'
)
