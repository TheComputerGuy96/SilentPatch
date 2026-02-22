vc_name = 'SilentPatchVC'

# TODO: Simplify the resource handling code
vc_meta = [
   '-DSILENTPATCH_EXT=".' + asi_suffix + '"',
   '-DSILENTPATCH_NAME="' + iii_name + '"',
   '-DSILENTPATCH_FULL_NAME="SilentPatch for Vice City"',
   '-DSILENTPATCH_REVISION_ID=11',
   '-DSILENTPATCH_BUILD_ID=1',
   '-DSILENTPATCH_COPYRIGHT=2013-2024'
]

vc_conf = configure_file(
   input: common_res,
   output: 'SilentPatch_' + vc_name + '.rc',
   copy: true
)
vc_res = windows.compile_resources(
   vc_conf,
   args: vc_meta,
   include_directories: common_include
)

vc_sources = [
   iiivc_sources,
   vc_res,
   'ModelInfoVC.cpp',
   'SilentPatchVC.cpp',
   'StdAfxVC.cpp',
   'VehicleVC.cpp'
]

shared_library(
   'SilentPatchVC',
   vc_sources,
   name_prefix: '',
   name_suffix: asi_suffix,
   cpp_args: ['-D_GTA_VC', vc_meta],
   include_directories: iiivc_include,
   dependencies: shlwapi_dep
)
