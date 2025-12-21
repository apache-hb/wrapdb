dynaloader_makefile = custom_target(
  'DynaLoader.c',
  input: 'Makefile.PL',
  output: ['Makefile'],
  command: [
    miniperl,
    '@INPUT@',
  ],
  env: {
    'PERL5LIB': perlmods + [
      src_root / 'cpan/ExtUtils-MakeMaker/lib',
    ],
  },
  depends: [
    config_pm,
  ],
)

make = find_program('make')

dynaloader_build = custom_target(
  'DynaLoader_build',
  input: dynaloader_makefile,
  output: 'DynaLoader.o',
  command: [make, '-f', '@INPUT@', 'install', 'INSTALL_BASE=@OUTDIR@'],
)

libdynaloader = static_library(
  'DynaLoader',
  dynaloader_build,
  include_directories: inc,
)
