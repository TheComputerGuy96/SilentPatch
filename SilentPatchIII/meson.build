iii_name = 'SilentPatchIII'

# TODO: Simplify the resource handling code
iii_meta = [
   '-DSILENTPATCH_EXT=".' + asi_suffix + '"',
   '-DSILENTPATCH_NAME="' + iii_name + '"',
   '-DSILENTPATCH_FULL_NAME="SilentPatch for GTA III"',
   '-DSILENTPATCH_REVISION_ID=9',
   '-DSILENTPATCH_BUILD_ID=2',
   '-DSILENTPATCH_COPYRIGHT=2013-2024'
]

iii_conf = configure_file(
   input: common_res,
   output: 'SilentPatch_' + iii_name + '.rc',
   copy: true
)
iii_res = windows.compile_resources(
   iii_conf,
   args: iii_meta,
   include_directories: common_include
)

iii_sources = [
   iiivc_sources,
   iii_res,
   'ModelInfoIII.cpp',
   'SilentPatchIII.cpp',
   'StdAfxIII.cpp'
]

shared_library(
   iii_name,
   iii_sources,
   name_prefix: '',
   name_suffix: asi_suffix,
   cpp_args: ['-D_GTA_III', iii_meta],
   include_directories: iiivc_include,
   dependencies: shlwapi_dep
)
