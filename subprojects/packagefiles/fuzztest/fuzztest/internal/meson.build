test_proto = custom_target(
  'fuzztest_test_protobuf',
  input: 'test_protobuf.proto',
  output: ['test_protobuf.pb.cc', 'test_protobuf.pb.h'],
  command: [
    protoc,
    '--cpp_out=@OUTDIR@',
    '-I',
    meson.current_source_dir(),
    meson.current_source_dir() / 'test_protobuf.proto',
  ],
)
