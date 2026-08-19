project(
  'riegeli',
  'cpp',
  version: '0.0.0.20250822.9f2744d',
  meson_version: '>=0.59.0',
  default_options: ['cpp_std=c++17', 'warning_level=2'],
  license: 'Apache-2.0',
)

if host_machine.system() == 'windows'
  error('This Riegeli port does not support Windows')
endif

tests_opt = get_option('tests').disable_auto_if(meson.is_subproject())
cpp = meson.get_compiler('cpp')
protoc = find_program('protoc')

absl_deps = [
  dependency('absl_base'),
  dependency('absl_container'),
  dependency('absl_hash'),
  dependency('absl_log'),
  dependency('absl_numeric'),
  dependency('absl_status'),
  dependency('absl_strings'),
  dependency('absl_synchronization'),
  dependency('absl_time'),
  dependency('absl_types'),
]
brotli_deps = [
  dependency('libbrotlicommon'),
  dependency('libbrotlidec'),
  dependency('libbrotlienc'),
]
protobuf = dependency('protobuf')
riegeli_deps = absl_deps + brotli_deps + [
  dependency('highwayhash'),
  dependency('snappy'),
  dependency('libzstd'),
  protobuf,
  dependency('threads'),
]

riegeli_inc = include_directories('.')
subdir('riegeli/records')

riegeli_sources = files(
  'riegeli/base/assert.cc',
  'riegeli/base/background_cleaning.cc',
  'riegeli/base/buffer.cc',
  'riegeli/base/byte_fill.cc',
  'riegeli/base/chain.cc',
  'riegeli/base/compact_string.cc',
  'riegeli/base/cord_utils.cc',
  'riegeli/base/debug.cc',
  'riegeli/base/errno_mapping.cc',
  'riegeli/base/external_data.cc',
  'riegeli/base/memory_estimator.cc',
  'riegeli/base/object.cc',
  'riegeli/base/options_parser.cc',
  'riegeli/base/parallelism.cc',
  'riegeli/base/shared_buffer.cc',
  'riegeli/base/sized_shared_buffer.cc',
  'riegeli/base/status.cc',
  'riegeli/base/stream_utils.cc',
  'riegeli/base/string_utils.cc',
  'riegeli/base/unicode.cc',
  'riegeli/brotli/brotli_allocator.cc',
  'riegeli/brotli/brotli_dictionary.cc',
  'riegeli/brotli/brotli_reader.cc',
  'riegeli/brotli/brotli_writer.cc',
  'riegeli/bytes/array_backward_writer.cc',
  'riegeli/bytes/array_writer.cc',
  'riegeli/bytes/backward_writer.cc',
  'riegeli/bytes/buffer_options.cc',
  'riegeli/bytes/buffered_reader.cc',
  'riegeli/bytes/buffered_writer.cc',
  'riegeli/bytes/chain_backward_writer.cc',
  'riegeli/bytes/chain_reader.cc',
  'riegeli/bytes/chain_writer.cc',
  'riegeli/bytes/cord_backward_writer.cc',
  'riegeli/bytes/cord_reader.cc',
  'riegeli/bytes/cord_writer.cc',
  'riegeli/bytes/fd_handle.cc',
  'riegeli/bytes/fd_internal.cc',
  'riegeli/bytes/fd_reader.cc',
  'riegeli/bytes/fd_writer.cc',
  'riegeli/bytes/file_mode_string.cc',
  'riegeli/bytes/limiting_backward_writer.cc',
  'riegeli/bytes/limiting_reader.cc',
  'riegeli/bytes/limiting_writer.cc',
  'riegeli/bytes/null_backward_writer.cc',
  'riegeli/bytes/null_writer.cc',
  'riegeli/bytes/prefix_limiting_backward_writer.cc',
  'riegeli/bytes/prefix_limiting_reader.cc',
  'riegeli/bytes/prefix_limiting_writer.cc',
  'riegeli/bytes/pullable_reader.cc',
  'riegeli/bytes/pushable_backward_writer.cc',
  'riegeli/bytes/pushable_writer.cc',
  'riegeli/bytes/reader.cc',
  'riegeli/bytes/resizable_writer.cc',
  'riegeli/bytes/restricted_chain_writer.cc',
  'riegeli/bytes/string_reader.cc',
  'riegeli/bytes/string_writer.cc',
  'riegeli/bytes/wrapping_backward_writer.cc',
  'riegeli/bytes/wrapping_reader.cc',
  'riegeli/bytes/wrapping_writer.cc',
  'riegeli/bytes/write_int_internal.cc',
  'riegeli/bytes/writer.cc',
  'riegeli/chunk_encoding/brotli_encoder_selection.cc',
  'riegeli/chunk_encoding/chunk.cc',
  'riegeli/chunk_encoding/chunk_decoder.cc',
  'riegeli/chunk_encoding/chunk_encoder.cc',
  'riegeli/chunk_encoding/compressor.cc',
  'riegeli/chunk_encoding/compressor_options.cc',
  'riegeli/chunk_encoding/decompressor.cc',
  'riegeli/chunk_encoding/deferred_encoder.cc',
  'riegeli/chunk_encoding/hash.cc',
  'riegeli/chunk_encoding/simple_decoder.cc',
  'riegeli/chunk_encoding/simple_encoder.cc',
  'riegeli/chunk_encoding/transpose_decoder.cc',
  'riegeli/chunk_encoding/transpose_encoder.cc',
  'riegeli/messages/parse_message.cc',
  'riegeli/messages/serialize_message.cc',
  'riegeli/messages/serialized_message_backward_writer.cc',
  'riegeli/messages/serialized_message_reader.cc',
  'riegeli/messages/serialized_message_rewriter.cc',
  'riegeli/messages/serialized_message_writer.cc',
  'riegeli/ordered_varint/ordered_varint_reading.cc',
  'riegeli/ordered_varint/ordered_varint_writing.cc',
  'riegeli/records/chunk_reader.cc',
  'riegeli/records/chunk_writer.cc',
  'riegeli/records/record_position.cc',
  'riegeli/records/record_reader.cc',
  'riegeli/records/record_writer.cc',
  'riegeli/records/skipped_region.cc',
  'riegeli/snappy/snappy_reader.cc',
  'riegeli/snappy/snappy_streams.cc',
  'riegeli/snappy/snappy_writer.cc',
  'riegeli/varint/varint_reading.cc',
  'riegeli/zstd/zstd_dictionary.cc',
  'riegeli/zstd/zstd_reader.cc',
  'riegeli/zstd/zstd_writer.cc',
)

riegeli_lib = library(
  'riegeli',
  riegeli_sources,
  records_metadata_proto,
  include_directories: riegeli_inc,
  dependencies: riegeli_deps,
  install: true,
)
riegeli_dep = declare_dependency(
  include_directories: riegeli_inc,
  link_with: riegeli_lib,
  sources: records_metadata_proto[1],
  dependencies: riegeli_deps,
)
meson.override_dependency('riegeli', riegeli_dep)

find = find_program('find')
riegeli_non_headers = run_command(
  find,
  'riegeli',
  '-type',
  'f',
  '!',
  '-name',
  '*.h',
  check: true,
).stdout().strip().split('\n')
riegeli_install_excludes = []
foreach path : riegeli_non_headers
  riegeli_install_excludes += path.replace('riegeli/', '')
endforeach

install_subdir(
  'riegeli',
  install_dir: get_option('includedir'),
  exclude_directories: ['records/tools'],
  exclude_files: riegeli_install_excludes,
)
custom_target(
  'install_records_metadata_header',
  input: records_metadata_proto[1],
  output: 'records_metadata.pb.h',
  command: [find_program('cp'), '@INPUT@', '@OUTPUT@'],
  install: true,
  install_dir: get_option('includedir') / 'riegeli/records',
)

if tests_opt.allowed()
  riegeli_records_test = executable(
    'riegeli_records_test',
    'riegeli/records/records_test.cc',
    include_directories: riegeli_inc,
    dependencies: riegeli_dep,
    build_by_default: false,
  )
  test(
    'records_round_trip',
    riegeli_records_test,
    suite: 'riegeli',
  )
endif
