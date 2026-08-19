seed_corpus_config_proto = custom_target(
  'seed_corpus_config_proto',
  input: 'seed_corpus_config.proto',
  output: ['seed_corpus_config.pb.cc', 'seed_corpus_config.pb.h'],
  command: [
    protoc,
    '--cpp_out=@OUTDIR@',
    '-I',
    meson.current_source_dir(),
    meson.current_source_dir() / 'seed_corpus_config.proto',
  ],
)

python = import('python').find_installation()
stats_compat_script = meson.current_source_dir() / 'meson_stats_compat.py'
centipede_stats_compat_header = configure_file(
  input: 'stats.h',
  output: 'stats.h',
  command: [python, stats_compat_script, '@INPUT@', '@OUTPUT@'],
)
centipede_stats_compat_source = configure_file(
  input: 'stats.cc',
  output: 'stats.cc',
  command: [python, stats_compat_script, '@INPUT@', '@OUTPUT@'],
)
