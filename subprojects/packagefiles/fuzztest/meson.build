project(
  'fuzztest',
  'cpp',
  version: '20260629',
  meson_version: '>=0.64.0',
  default_options: ['cpp_std=c++17', 'warning_level=2'],
  license: 'Apache-2.0 AND BSD-3-Clause',
)

if host_machine.system() == 'windows'
  error('FuzzTest does not support Windows')
endif

tests_opt = get_option('tests').disable_auto_if(meson.is_subproject())
cpp = meson.get_compiler('cpp')

absl_deps = [
  dependency('absl_base'),
  dependency('absl_container'),
  dependency('absl_debugging'),
  dependency('absl_flags'),
  dependency('absl_hash'),
  dependency('absl_log'),
  dependency('absl_numeric'),
  dependency('absl_random'),
  dependency('absl_status'),
  dependency('absl_strings'),
  dependency('absl_synchronization'),
  dependency('absl_time'),
  dependency('absl_types'),
]
gtest = dependency('gtest')
re2 = dependency('re2_internal')
riegeli = dependency('riegeli')
protobuf = dependency('protobuf')
protoc = find_program('protoc')
threads = dependency('threads')
dl = cpp.find_library(
  'dl',
  required: false,
)

fuzztest_inc = include_directories('.')
fuzztest_cpp_args = []

fuzztest_sources = files(
  'common/bazel.cc',
  'common/blob_file.cc',
  'common/crashing_input_filename.cc',
  'common/hash.cc',
  'common/remote_file.cc',
  'common/remote_file_oss.cc',
  'common/sha1.cc',
  'common/temp_dir.cc',
  'fuzztest/fuzzing_bit_gen.cc',
  'fuzztest/fuzztest_macros.cc',
  'fuzztest/init_fuzztest.cc',
  'fuzztest/internal/compatibility_mode.cc',
  'fuzztest/internal/configuration.cc',
  'fuzztest/internal/corpus_database.cc',
  'fuzztest/internal/coverage.cc',
  'fuzztest/internal/domains/in_grammar_impl.cc',
  'fuzztest/internal/domains/in_regexp_impl.cc',
  'fuzztest/internal/domains/regexp_dfa.cc',
  'fuzztest/internal/domains/rune.cc',
  'fuzztest/internal/domains/utf.cc',
  'fuzztest/internal/escaping.cc',
  'fuzztest/internal/fixture_driver.cc',
  'fuzztest/internal/googletest_adaptor.cc',
  'fuzztest/internal/io.cc',
  'fuzztest/internal/logging.cc',
  'fuzztest/internal/register_absl_fuzzing_mocks.cc',
  'fuzztest/internal/registry.cc',
  'fuzztest/internal/runtime.cc',
  'fuzztest/internal/sanitizer_interface.cc',
  'fuzztest/internal/seed_seq.cc',
  'fuzztest/internal/serialization.cc',
  'fuzztest/internal/status.cc',
  'fuzztest/internal/subprocess.cc',
  'fuzztest/internal/type_support.cc',
)

fuzztest_lib = static_library(
  'fuzztest',
  fuzztest_sources,
  cpp_args: fuzztest_cpp_args,
  include_directories: fuzztest_inc,
  dependencies: absl_deps + [gtest, protobuf, re2, riegeli, threads, dl],
  install: true,
)

fuzztest_dep = declare_dependency(
  compile_args: fuzztest_cpp_args,
  include_directories: fuzztest_inc,
  link_with: fuzztest_lib,
  dependencies: absl_deps + [gtest, protobuf, re2, riegeli, threads, dl],
)

fuzztest_gtest_main_lib = static_library(
  'fuzztest_gtest_main',
  'fuzztest/fuzztest_gtest_main.cc',
  include_directories: fuzztest_inc,
  dependencies: [fuzztest_dep, gtest],
  install: true,
)
fuzztest_gtest_main_dep = declare_dependency(
  link_with: fuzztest_gtest_main_lib,
  dependencies: fuzztest_dep,
)

fuzztest_llvm_fuzzer_main_lib = static_library(
  'fuzztest_llvm_fuzzer_main',
  'fuzztest/llvm_fuzzer_main.cc',
  include_directories: fuzztest_inc,
  dependencies: [fuzztest_dep, gtest],
  install: true,
)
fuzztest_llvm_fuzzer_main_dep = declare_dependency(
  link_with: fuzztest_llvm_fuzzer_main_lib,
  dependencies: fuzztest_dep,
)

fuzztest_llvm_fuzzer_wrapper_lib = static_library(
  'fuzztest_llvm_fuzzer_wrapper',
  'fuzztest/llvm_fuzzer_wrapper.cc',
  cpp_args: fuzztest_cpp_args,
  include_directories: fuzztest_inc,
  dependencies: fuzztest_dep,
  install: true,
)
fuzztest_llvm_fuzzer_wrapper_dep = declare_dependency(
  link_with: fuzztest_llvm_fuzzer_wrapper_lib,
  dependencies: fuzztest_dep,
)

meson.override_dependency('fuzztest', fuzztest_dep)
meson.override_dependency('fuzztest_gtest_main', fuzztest_gtest_main_dep)
meson.override_dependency(
  'fuzztest_llvm_fuzzer_main',
  fuzztest_llvm_fuzzer_main_dep,
)
meson.override_dependency(
  'fuzztest_llvm_fuzzer_wrapper',
  fuzztest_llvm_fuzzer_wrapper_dep,
)

antlr4_runtime = dependency('antlr4-runtime')
generated_antlr_parser = static_library(
  'fuzztest_generated_antlr_parser',
  files(
    'grammar_codegen/generated_antlr_parser/ANTLRv4Lexer.cpp',
    'grammar_codegen/generated_antlr_parser/ANTLRv4Parser.cpp',
    'grammar_codegen/generated_antlr_parser/ANTLRv4ParserBaseListener.cpp',
    'grammar_codegen/generated_antlr_parser/ANTLRv4ParserListener.cpp',
  ),
  include_directories: fuzztest_inc,
  dependencies: antlr4_runtime,
)

grammar_codegen_lib = static_library(
  'fuzztest_grammar_codegen',
  files(
    'grammar_codegen/antlr_frontend.cc',
    'grammar_codegen/backend.cc',
    'grammar_codegen/code_generation.cc',
  ),
  include_directories: fuzztest_inc,
  link_with: generated_antlr_parser,
  dependencies: absl_deps + [antlr4_runtime, fuzztest_dep],
)

grammar_domain_code_generator = executable(
  'grammar_domain_code_generator',
  'tools/grammar_domain_code_generator.cc',
  include_directories: fuzztest_inc,
  link_with: grammar_codegen_lib,
  dependencies: absl_deps + [antlr4_runtime, fuzztest_dep],
  install: true,
)
meson.override_find_program(
  'grammar_domain_code_generator',
  grammar_domain_code_generator,
)

subdir('centipede')

atomic = cpp.find_library(
  'atomic',
  required: false,
)
rt = cpp.find_library(
  'rt',
  required: false,
)
centipede_deps = absl_deps + [
  fuzztest_dep,
  protobuf,
  riegeli,
  threads,
  dl,
  atomic,
  rt,
]
centipede_cpp_args = []
if host_machine.system() == 'linux'
  centipede_cpp_args += '-D_GNU_SOURCE'
  if not cpp.has_function(
    'memfd_create',
    prefix: '#define _GNU_SOURCE\n#include <sys/mman.h>',
  )
    centipede_cpp_args += [
      '-include',
      meson.current_source_dir() / 'centipede/meson_memfd_compat.h',
    ]
  endif
endif

centipede_sources = files(
  'centipede/analyze_corpora.cc',
  'centipede/binary_info.cc',
  'centipede/byte_array_mutator.cc',
  'centipede/call_graph.cc',
  'centipede/centipede.cc',
  'centipede/centipede_callbacks.cc',
  'centipede/centipede_default_callbacks.cc',
  'centipede/centipede_interface.cc',
  'centipede/command.cc',
  'centipede/config_file.cc',
  'centipede/config_init.cc',
  'centipede/config_util.cc',
  'centipede/control_flow.cc',
  'centipede/corpus.cc',
  'centipede/corpus_io.cc',
  'centipede/coverage.cc',
  'centipede/crash_deduplication.cc',
  'centipede/crash_summary.cc',
  'centipede/distill.cc',
  'centipede/environment.cc',
  'centipede/environment_flags.cc',
  'centipede/execution_metadata.cc',
  'centipede/feature.cc',
  'centipede/feature_set.cc',
  'centipede/fuzztest_mutator.cc',
  'centipede/knobs.cc',
  'centipede/minimize_crash.cc',
  'centipede/pc_info.cc',
  'centipede/periodic_action.cc',
  'centipede/resource_pool.cc',
  'centipede/runner_flags.cc',
  'centipede/runner_request.cc',
  'centipede/runner_result.cc',
  'centipede/rusage_profiler.cc',
  'centipede/rusage_stats.cc',
  'centipede/seed_corpus_maker_lib.cc',
  'centipede/seed_corpus_maker_proto_lib.cc',
  'centipede/shared_memory_blob_sequence.cc',
  'centipede/stop.cc',
  'centipede/symbol_table.cc',
  'centipede/util.cc',
  'centipede/workdir.cc',
)
centipede_sources += centipede_stats_compat_source

centipede_lib = static_library(
  'centipede_lib',
  centipede_sources,
  seed_corpus_config_proto,
  cpp_args: centipede_cpp_args,
  include_directories: fuzztest_inc,
  dependencies: centipede_deps,
  install: true,
)
centipede_dep = declare_dependency(
  include_directories: fuzztest_inc,
  link_with: centipede_lib,
  dependencies: centipede_deps,
)
meson.override_dependency('centipede', centipede_dep)

centipede_exe = executable(
  'centipede-bin',
  'centipede/centipede_main.cc',
  include_directories: fuzztest_inc,
  dependencies: centipede_dep,
  install: true,
)
install_symlink(
  'centipede',
  pointing_to: 'centipede-bin',
  install_dir: get_option('bindir'),
)
meson.override_find_program('centipede', centipede_exe)

seed_corpus_maker_flag_args = [
  '-DFLAGS_config=FLAGS_seed_corpus_config',
  '-DFLAGS_noconfig=FLAGS_seed_corpus_noconfig',
]
seed_corpus_maker_flags_lib = static_library(
  'seed_corpus_maker_flags',
  'centipede/seed_corpus_maker_flags.cc',
  cpp_args: seed_corpus_maker_flag_args,
  include_directories: fuzztest_inc,
  dependencies: absl_deps,
)

seed_corpus_maker = executable(
  'seed_corpus_maker',
  'centipede/seed_corpus_maker.cc',
  cpp_args: seed_corpus_maker_flag_args,
  include_directories: fuzztest_inc,
  link_with: seed_corpus_maker_flags_lib,
  dependencies: centipede_dep,
  install: true,
)
meson.override_find_program('seed_corpus_maker', seed_corpus_maker)

blob_file_converter = executable(
  'blob_file_converter',
  'centipede/blob_file_converter.cc',
  include_directories: fuzztest_inc,
  dependencies: centipede_dep,
  install: true,
)
meson.override_find_program('blob_file_converter', blob_file_converter)

runner_cpp_args = cpp.get_supported_arguments(
  '-fsanitize-coverage=0',
  '-fno-sanitize=address,hwaddress,thread,undefined',
)
runner_cpp_args += centipede_cpp_args
centipede_runner_sources = files(
  'centipede/byte_array_mutator.cc',
  'centipede/execution_metadata.cc',
  'centipede/feature.cc',
  'centipede/knobs.cc',
  'centipede/runner.cc',
  'centipede/runner_dl_info.cc',
  'centipede/runner_fork_server.cc',
  'centipede/runner_request.cc',
  'centipede/runner_result.cc',
  'centipede/runner_utils.cc',
  'centipede/sancov_callbacks.cc',
  'centipede/sancov_interceptors.cc',
  'centipede/sancov_object_array.cc',
  'centipede/sancov_state.cc',
  'centipede/shared_memory_blob_sequence.cc',
)
centipede_runner_no_main_lib = static_library(
  'centipede_runner_no_main',
  centipede_runner_sources,
  cpp_args: runner_cpp_args,
  include_directories: fuzztest_inc,
  dependencies: absl_deps + [threads, dl, rt],
  install: true,
)
centipede_runner_no_main_dep = declare_dependency(
  include_directories: fuzztest_inc,
  link_whole: centipede_runner_no_main_lib,
  dependencies: absl_deps + [threads, dl, rt],
)
meson.override_dependency(
  'centipede_runner_no_main',
  centipede_runner_no_main_dep,
)

centipede_runner_lib = static_library(
  'centipede_runner',
  'centipede/runner_main.cc',
  cpp_args: runner_cpp_args,
  include_directories: fuzztest_inc,
  link_whole: centipede_runner_no_main_lib,
  dependencies: absl_deps + [threads, dl, rt],
  install: true,
)
centipede_runner_dep = declare_dependency(
  include_directories: fuzztest_inc,
  link_whole: centipede_runner_lib,
  dependencies: absl_deps + [threads, dl, rt],
)
meson.override_dependency('centipede_runner', centipede_runner_dep)

public_headers = [
  'common/bazel.h',
  'common/blob_file.h',
  'common/crashing_input_filename.h',
  'common/defs.h',
  'common/hash.h',
  'common/logging.h',
  'common/remote_file.h',
  'common/sha1.h',
  'common/status_macros.h',
  'common/temp_dir.h',
  'fuzztest/domain.h',
  'fuzztest/domain_core.h',
  'fuzztest/fuzzing_bit_gen.h',
  'fuzztest/fuzztest.h',
  'fuzztest/fuzztest_core.h',
  'fuzztest/fuzztest_macros.h',
  'fuzztest/googletest_fixture_adapter.h',
  'fuzztest/init_fuzztest.h',
  'fuzztest/internal/any.h',
  'fuzztest/internal/centipede_adaptor.h',
  'fuzztest/internal/compatibility_mode.h',
  'fuzztest/internal/configuration.h',
  'fuzztest/internal/corpus_database.h',
  'fuzztest/internal/coverage.h',
  'fuzztest/internal/domains/absl_helpers.h',
  'fuzztest/internal/domains/aggregate_of_impl.h',
  'fuzztest/internal/domains/arbitrary_impl.h',
  'fuzztest/internal/domains/bit_flag_combination_of_impl.h',
  'fuzztest/internal/domains/bit_gen_ref.h',
  'fuzztest/internal/domains/container_mutation_helpers.h',
  'fuzztest/internal/domains/container_of_impl.h',
  'fuzztest/internal/domains/domain.h',
  'fuzztest/internal/domains/domain_base.h',
  'fuzztest/internal/domains/domain_type_erasure.h',
  'fuzztest/internal/domains/element_of_impl.h',
  'fuzztest/internal/domains/filter_impl.h',
  'fuzztest/internal/domains/flat_map_impl.h',
  'fuzztest/internal/domains/in_grammar_impl.h',
  'fuzztest/internal/domains/in_range_impl.h',
  'fuzztest/internal/domains/in_regexp_impl.h',
  'fuzztest/internal/domains/lazy.h',
  'fuzztest/internal/domains/map_impl.h',
  'fuzztest/internal/domains/mutation_metadata.h',
  'fuzztest/internal/domains/one_of_impl.h',
  'fuzztest/internal/domains/optional_of_impl.h',
  'fuzztest/internal/domains/overlap_of_impl.h',
  'fuzztest/internal/domains/protobuf_domain_impl.h',
  'fuzztest/internal/domains/regexp_dfa.h',
  'fuzztest/internal/domains/rune.h',
  'fuzztest/internal/domains/serialization_helpers.h',
  'fuzztest/internal/domains/smart_pointer_of_impl.h',
  'fuzztest/internal/domains/special_values.h',
  'fuzztest/internal/domains/unique_elements_container_of_impl.h',
  'fuzztest/internal/domains/utf.h',
  'fuzztest/internal/domains/value_mutation_helpers.h',
  'fuzztest/internal/domains/variant_of_impl.h',
  'fuzztest/internal/enum_reflection.h',
  'fuzztest/internal/escaping.h',
  'fuzztest/internal/fixture_driver.h',
  'fuzztest/internal/flag_name.h',
  'fuzztest/internal/fuzzing_mock_stream.h',
  'fuzztest/internal/googletest_adaptor.h',
  'fuzztest/internal/io.h',
  'fuzztest/internal/logging.h',
  'fuzztest/internal/meta.h',
  'fuzztest/internal/printer.h',
  'fuzztest/internal/register_absl_fuzzing_mocks.h',
  'fuzztest/internal/registration.h',
  'fuzztest/internal/registry.h',
  'fuzztest/internal/runtime.h',
  'fuzztest/internal/sanitizer_interface.h',
  'fuzztest/internal/seed_seq.h',
  'fuzztest/internal/serialization.h',
  'fuzztest/internal/status.h',
  'fuzztest/internal/subprocess.h',
  'fuzztest/internal/table_of_recent_compares.h',
  'fuzztest/internal/type_support.h',
]

fs = import('fs')
foreach header : public_headers
  install_headers(
    header,
    subdir: fs.parent(header),
  )
endforeach

find = find_program('find')
centipede_headers = run_command(
  find,
  'centipede',
  '-maxdepth',
  '1',
  '-type',
  'f',
  '-name',
  '*.h',
  check: true,
).stdout().strip().split('\n')
foreach header : centipede_headers
  if header not in [
    'centipede/meson_memfd_compat.h',
    'centipede/stats.h',
    'centipede/test_coverage_util.h',
  ]
    install_headers(
      header,
      subdir: 'centipede',
    )
  endif
endforeach
install_headers(
  centipede_stats_compat_header,
  subdir: 'centipede',
)
install_data(
  'centipede/centipede_flags.inc',
  install_dir: get_option('includedir') / 'centipede',
)

if tests_opt.allowed()
  gmock_main = dependency(
    'gmock_main',
    required: tests_opt,
  )
  nlohmann_json = dependency(
    'nlohmann_json',
    required: tests_opt,
  )

  if gmock_main.found() and protobuf.found() and protoc.found() and nlohmann_json.found()
    subdir('fuzztest/internal')
    subdir('fuzztest/grammars')

    test_support = static_library(
      'fuzztest_test_support',
      'common/test_util.cc',
      test_proto,
      cpp_args: fuzztest_cpp_args,
      include_directories: fuzztest_inc,
      dependencies: [fuzztest_dep, gtest, protobuf],
      build_by_default: false,
    )

    tests = [
      'common/blob_file_test.cc',
      'common/crashing_input_filename_test.cc',
      'common/hash_test.cc',
      'common/remote_file_test.cc',
      'domain_tests/aggregate_combinators_test.cc',
      'domain_tests/arbitrary_domains_protobuf_test.cc',
      'domain_tests/arbitrary_domains_test.cc',
      'domain_tests/bitgen_ref_domain_test.cc',
      'domain_tests/container_combinators_test.cc',
      'domain_tests/container_test.cc',
      'domain_tests/in_regexp_domain_test.cc',
      'domain_tests/map_filter_combinator_test.cc',
      'domain_tests/misc_domains_test.cc',
      'domain_tests/numeric_domains_test.cc',
      'domain_tests/pointer_domains_test.cc',
      'domain_tests/recursive_domains_test.cc',
      'domain_tests/specific_value_domains_test.cc',
      'domain_tests/string_domains_test.cc',
      'fuzztest/fuzzing_bit_gen_test.cc',
      'fuzztest/fuzztest_macros_test.cc',
      'fuzztest/internal/any_test.cc',
      'fuzztest/internal/configuration_test.cc',
      'fuzztest/internal/enum_reflection_test.cc',
      'fuzztest/internal/fixture_driver_test.cc',
      'fuzztest/internal/io_test.cc',
      'fuzztest/internal/register_absl_fuzzing_mocks_test.cc',
      'fuzztest/internal/runtime_test.cc',
      'fuzztest/internal/sanitizer_interface_test.cc',
      'fuzztest/internal/seed_seq_test.cc',
      'fuzztest/internal/serialization_test.cc',
      'fuzztest/internal/subprocess_test.cc',
      'fuzztest/internal/table_of_recent_compares_test.cc',
      'fuzztest/internal/type_support_test.cc',
    ]

    foreach path : tests
      name = fs.stem(path)
      test_cpp_args = fuzztest_cpp_args
      test_args = []
      if path == 'domain_tests/arbitrary_domains_protobuf_test.cc'
        test_cpp_args += '-DGTEST_HAS_ABSL'
      endif
      if path == 'common/remote_file_test.cc'
        # Filesystem timestamp granularity and clock skew make this ordering
        # assertion flaky even though the touch operation succeeds.
        test_args += '--gtest_filter=-RemotePathTouchExistingFile.UpdatesTheLastModifiedTime'
      endif
      if path == 'fuzztest/internal/type_support_test.cc'
        excluded_tests = ['ProtobufTest.Printer']
        if cpp.get_id() == 'gcc' and cpp.version().version_compare('>=15')
          # GCC 15 prints same-namespace types without their namespace in
          # __PRETTY_FUNCTION__, contrary to this test's fixed expectations.
          excluded_tests += 'ProtobufEnumTest.Printer'
        endif
        # This multiline proto matcher assumes GoogleTest's optional RE2
        # backend; its unescaped braces are invalid with the POSIX backend.
        test_args += '--gtest_filter=-' + ':'.join(excluded_tests)
      endif
      exe = executable(
        name,
        path,
        test_proto[1],
        cpp_args: test_cpp_args,
        include_directories: fuzztest_inc,
        link_with: test_support,
        dependencies: absl_deps + [fuzztest_dep, gmock_main, protobuf, re2],
        build_by_default: false,
      )
      test(
        name,
        exe,
        args: test_args,
        suite: 'fuzztest',
        timeout: 120,
      )
    endforeach

    in_grammar_domain_test = executable(
      'in_grammar_domain_test',
      'domain_tests/in_grammar_domain_test.cc',
      test_proto[1],
      json_grammar,
      cpp_args: fuzztest_cpp_args,
      include_directories: fuzztest_inc,
      link_with: test_support,
      dependencies: absl_deps + [
        fuzztest_dep,
        gmock_main,
        nlohmann_json,
        protobuf,
      ],
      build_by_default: false,
    )
    test(
      'in_grammar_domain_test',
      in_grammar_domain_test,
      suite: 'fuzztest',
      timeout: 120,
    )

    centipede_runner_smoke_test = executable(
      'centipede_runner_smoke_test',
      'centipede/testing/empty_fuzz_target.cc',
      dependencies: centipede_runner_dep,
      build_by_default: false,
    )
    test(
      'runner_smoke_test',
      centipede_runner_smoke_test,
      suite: 'centipede',
    )

    centipede_tests = [
      'binary_info_test.cc',
      'byte_array_mutator_test.cc',
      'call_graph_test.cc',
      'callstack_test.cc',
      'centipede_callbacks_test.cc',
      'concurrent_bitset_test.cc',
      'concurrent_byteset_test.cc',
      'config_file_test.cc',
      'config_util_test.cc',
      'corpus_io_test.cc',
      'corpus_test.cc',
      'crash_deduplication_test.cc',
      'crash_summary_test.cc',
      'distill_test.cc',
      'environment_test.cc',
      'execution_metadata_test.cc',
      'feature_set_test.cc',
      'feature_test.cc',
      'foreach_nonzero_test.cc',
      'fuzztest_mutator_test.cc',
      'hashed_ring_buffer_test.cc',
      'int_utils_test.cc',
      'knobs_test.cc',
      'minimize_crash_test.cc',
      'mutation_data_test.cc',
      'pc_info_test.cc',
      'periodic_action_test.cc',
      'resource_pool_test.cc',
      'reverse_pc_table_test.cc',
      'rolling_hash_test.cc',
      'runner_cmp_trace_test.cc',
      'runner_flags_test.cc',
      'runner_result_test.cc',
      'rusage_profiler_test.cc',
      'rusage_stats_test.cc',
      'seed_corpus_maker_lib_test.cc',
      'seed_corpus_maker_proto_lib_test.cc',
      'shared_memory_blob_sequence_test.cc',
      'stats_test.cc',
      'symbol_table_test.cc',
      'util_test.cc',
      'workdir_test.cc',
    ]
    centipede_test_wrapper = (meson.current_source_dir() / 'centipede/meson_test_wrapper.py'
)

    foreach filename : centipede_tests
      name = fs.stem(filename)
      test_sources = ['centipede' / filename]
      test_cpp_args = centipede_cpp_args
      test_args = []
      if filename == 'seed_corpus_maker_proto_lib_test.cc'
        test_sources += seed_corpus_config_proto[1]
      endif
      if filename == 'util_test.cc'
        test_cpp_args += '-fno-signed-char'
      endif
      if filename == 'rusage_stats_test.cc'
        test_args += '--gtest_filter=-RUsageMemoryTest.Accuracy'
      endif
      if filename == 'rusage_profiler_test.cc'
        test_args += '--gtest_filter=-*ValidateTimelapseSnapshots*'
      endif
      if filename == 'config_util_test.cc'
        # Bazel rewrites __FILE__ to workspace-relative paths. Meson preserves
        # the subproject prefix, so the exact path-key assertions do not apply.
        test_args += '--gtest_filter=-FlagUtilTest.GetFlagsPerSource'
      endif
      exe = executable(
        'centipede_' + name,
        test_sources,
        cpp_args: test_cpp_args,
        include_directories: fuzztest_inc,
        link_with: test_support,
        dependencies: centipede_deps + [centipede_dep, gmock_main],
        build_by_default: false,
      )
      test(
        name,
        python,
        args: [centipede_test_wrapper, exe] + test_args,
        suite: 'centipede',
        timeout: 180,
      )
    endforeach
  endif
endif
