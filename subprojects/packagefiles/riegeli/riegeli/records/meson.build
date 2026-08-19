records_metadata_proto = custom_target(
  'records_metadata_proto',
  input: 'records_metadata.proto',
  output: ['records_metadata.pb.cc', 'records_metadata.pb.h'],
  command: [
    protoc,
    '--cpp_out=@OUTDIR@',
    '-I',
    meson.current_source_dir(),
    meson.current_source_dir() / 'records_metadata.proto',
  ],
)
