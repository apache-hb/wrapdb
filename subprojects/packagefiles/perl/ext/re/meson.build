regexec = fs.copyfile(regexec_file, 'regexec.c')

libregexec = static_library(
  'regexec',
  regexec,
  c_args: ['-DPERL_EXT_RE_BUILD', '-DPERL_EXT_RE_DEBUG', '-DPERL_EXT'],
  include_directories: inc,
)
