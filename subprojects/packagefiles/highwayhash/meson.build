project(
  'highwayhash',
  ['c', 'cpp'],
  version: '0.0.0.20240305.5ad3bf8',
  meson_version: '>=0.59.0',
  default_options: ['cpp_std=c++11', 'warning_level=2'],
  license: 'Apache-2.0',
)

tests_opt = get_option('tests').disable_auto_if(meson.is_subproject())
cpp = meson.get_compiler('cpp')
threads = dependency('threads')
inc = include_directories('.')

common_sources = files(
  'highwayhash/arch_specific.cc',
  'highwayhash/c_bindings.cc',
  'highwayhash/hh_portable.cc',
  'highwayhash/instruction_sets.cc',
  'highwayhash/scalar_sip_tree_hash.cc',
  'highwayhash/sip_hash.cc',
  'highwayhash/sip_tree_hash.cc',
)
common_args = []
target_libs = []
test_highwayhash_libs = []
test_vector_libs = []

if host_machine.cpu_family() in ['x86', 'x86_64']
  common_args += '-DHH_TARGET_NAME=Portable'
  target_libs += static_library(
    'highwayhash_avx2',
    'highwayhash/hh_avx2.cc',
    cpp_args: '-mavx2',
    include_directories: inc,
    build_by_default: false,
  )
  target_libs += static_library(
    'highwayhash_sse41',
    'highwayhash/hh_sse41.cc',
    cpp_args: '-msse4.1',
    include_directories: inc,
    build_by_default: false,
  )
  test_highwayhash_libs += static_library(
    'highwayhash_test_avx2',
    'highwayhash/highwayhash_test_avx2.cc',
    cpp_args: '-mavx2',
    include_directories: inc,
    build_by_default: false,
  )
  test_highwayhash_libs += static_library(
    'highwayhash_test_sse41',
    'highwayhash/highwayhash_test_sse41.cc',
    cpp_args: '-msse4.1',
    include_directories: inc,
    build_by_default: false,
  )
  test_vector_libs += static_library(
    'vector_test_avx2',
    'highwayhash/vector_test_avx2.cc',
    cpp_args: '-mavx2',
    include_directories: inc,
    build_by_default: false,
  )
  test_vector_libs += static_library(
    'vector_test_sse41',
    'highwayhash/vector_test_sse41.cc',
    cpp_args: '-msse4.1',
    include_directories: inc,
    build_by_default: false,
  )
elif host_machine.cpu_family() in ['aarch64', 'arm']
  target_libs += static_library(
    'highwayhash_neon',
    'highwayhash/hh_neon.cc',
    include_directories: inc,
    build_by_default: false,
  )
  test_highwayhash_libs += static_library(
    'highwayhash_test_neon',
    'highwayhash/highwayhash_test_neon.cc',
    include_directories: inc,
    build_by_default: false,
  )
  test_vector_libs += static_library(
    'vector_test_neon',
    'highwayhash/vector_test_neon.cc',
    include_directories: inc,
    build_by_default: false,
  )
elif host_machine.cpu_family() in ['ppc', 'ppc64']
  target_libs += static_library(
    'highwayhash_vsx',
    'highwayhash/hh_vsx.cc',
    cpp_args: '-mvsx',
    include_directories: inc,
    build_by_default: false,
  )
  test_highwayhash_libs += static_library(
    'highwayhash_test_vsx',
    'highwayhash/highwayhash_test_vsx.cc',
    cpp_args: '-mvsx',
    include_directories: inc,
    build_by_default: false,
  )
else
  common_args += '-DHH_DISABLE_TARGET_SPECIFIC'
endif

highwayhash_lib = library(
  'highwayhash',
  common_sources,
  cpp_args: common_args,
  include_directories: inc,
  link_whole: target_libs,
  dependencies: threads,
  install: true,
)
highwayhash_dep = declare_dependency(
  include_directories: inc,
  link_with: highwayhash_lib,
  dependencies: threads,
)
meson.override_dependency('highwayhash', highwayhash_dep)

install_subdir(
  'highwayhash',
  install_dir: get_option('includedir'),
  exclude_files: [
    'arch_specific.cc',
    'benchmark.cc',
    'c_bindings.cc',
    'data_parallel_benchmark.cc',
    'data_parallel_test.cc',
    'example.cc',
    'hh_avx2.cc',
    'hh_neon.cc',
    'hh_portable.cc',
    'hh_sse41.cc',
    'hh_vsx.cc',
    'highwayhash_fuzzer.cc',
    'highwayhash_target.cc',
    'highwayhash_test.cc',
    'highwayhash_test_avx2.cc',
    'highwayhash_test_neon.cc',
    'highwayhash_test_portable.cc',
    'highwayhash_test_sse41.cc',
    'highwayhash_test_target.cc',
    'highwayhash_test_vsx.cc',
    'instruction_sets.cc',
    'nanobenchmark.cc',
    'nanobenchmark_example.cc',
    'os_mac.cc',
    'os_specific.cc',
    'profiler_example.cc',
    'scalar_sip_tree_hash.cc',
    'sip_hash.cc',
    'sip_hash_fuzzer.cc',
    'sip_hash_test.cc',
    'sip_tree_hash.cc',
    'vector_test.cc',
    'vector_test_avx2.cc',
    'vector_test_neon.cc',
    'vector_test_portable.cc',
    'vector_test_sse41.cc',
    'vector_test_target.cc',
  ],
)
install_headers(
  'c/highwayhash.h',
  subdir: 'highwayhash',
)

if tests_opt.allowed()
  nanobenchmark = static_library(
    'nanobenchmark',
    files('highwayhash/nanobenchmark.cc', 'highwayhash/os_specific.cc'),
    include_directories: inc,
    dependencies: threads,
    build_by_default: false,
  )

  highwayhash_test = executable(
    'highwayhash_test',
    [
      'highwayhash/highwayhash_test.cc',
      'highwayhash/highwayhash_test_portable.cc',
    ],
    include_directories: inc,
    link_with: nanobenchmark,
    link_whole: test_highwayhash_libs,
    dependencies: highwayhash_dep,
    build_by_default: false,
  )
  test(
    'highwayhash_test',
    highwayhash_test,
    suite: 'highwayhash',
  )

  vector_test = executable(
    'vector_test',
    ['highwayhash/vector_test.cc', 'highwayhash/vector_test_portable.cc'],
    include_directories: inc,
    link_with: nanobenchmark,
    link_whole: test_vector_libs,
    dependencies: highwayhash_dep,
    build_by_default: false,
  )
  test(
    'vector_test',
    vector_test,
    suite: 'highwayhash',
  )

  sip_hash_test = executable(
    'sip_hash_test',
    'highwayhash/sip_hash_test.cc',
    include_directories: inc,
    dependencies: highwayhash_dep,
    build_by_default: false,
  )
  test(
    'sip_hash_test',
    sip_hash_test,
    suite: 'highwayhash',
  )
endif
