project(
  'perl',
  'c',
  version: '5.43.5',
  meson_version: '>=1.5.0',
)

cc = meson.get_compiler('c')
fs = import('fs')

has_sigsetjmp = cc.has_function(
  'sigsetjmp',
  prefix: '#include <setjmp.h>',
)

inc = include_directories('.')
cdata = configuration_data()

cdata.set('HAS_SIGSETJMP', has_sigsetjmp)
if has_sigsetjmp
  cdata.set('Sigjmp_buf', 'sigjmp_buf')
  cdata.set('Sigsetjmp(buf,save_mask)', 'sigsetjmp((buf),(save_mask))')
  cdata.set('Siglongjmp(buf,retval)', 'siglongjmp((buf),(retval))')
else
  cdata.set('Sigjmp_buf', 'jmp_buf')
  cdata.set('Sigsetjmp(buf,save_mask)', 'setjmp((buf))')
  cdata.set('Siglongjmp(buf,retval)', 'longjmp((buf),(retval))')
endif

cdata.set('PeRl_CaTiFy(a, b)', 'a ## b')
cdata.set('PeRl_StGiFy(a)', '#a')
cdata.set('CAT2(a,b)', 'PeRl_CaTiFy(a,b)')
cdata.set('StGiFy(a)', 'PeRl_StGiFy(a)')
cdata.set('STRINGIFY(a)', 'PeRl_StGiFy(a)')
cdata.set('Gconvert(x,n,t,b)', 'sprintf((b),"%.*g",(n),(x))')

cdata.set_quoted('OSNAME', host_machine.system())
cdata.set_quoted('ARCHNAME', host_machine.cpu_family())

cdata.set('STDCHAR', 'char')

cdata.set('NVTYPE', 'double')
cdata.set('IVTYPE', 'intptr_t')
cdata.set('UVTYPE', 'uintptr_t')

cdata.set('I8TYPE', 'signed char')
cdata.set('U8TYPE', 'unsigned char')
cdata.set('I16TYPE', 'signed short')
cdata.set('U16TYPE', 'unsigned short')
cdata.set('I32TYPE', 'signed int')
cdata.set('U32TYPE', 'unsigned int')
cdata.set('I64TYPE', 'signed long long')
cdata.set('U64TYPE', 'unsigned long long')

cdata.set_quoted('IVdf', '%lld')
cdata.set_quoted('UVuf', '%llu')
cdata.set_quoted('UVof', '%llo')
cdata.set_quoted('UVxf', '%llx')
cdata.set_quoted('UVXf', '%llX')
cdata.set_quoted('NVef', '%e')
cdata.set_quoted('NVff', '%f')
cdata.set_quoted('NVgf', '%g')

cdata.set_quoted('I32df', '%d')
cdata.set_quoted('U32of', '%o')
cdata.set_quoted('U32uf', '%u')
cdata.set_quoted('U32xf', '%x')
cdata.set_quoted('U32Xf', '%X')

cdata.set_quoted('Gid_t_f', '%d')
cdata.set_quoted('Uid_t_f', '%d')

ivsize = cc.sizeof(
  'intptr_t',
  prefix: '#include <stdint.h>',
)
uvsize = cc.sizeof(
  'uintptr_t',
  prefix: '#include <stdint.h>',
)
nvsize = cc.sizeof('double')

cdata.set('IVSIZE', ivsize)
cdata.set('UVSIZE', uvsize)
cdata.set('NVSIZE', nvsize)
cdata.set('DOUBLESIZE', cc.sizeof('double'))

cdata.set('Size_t_size', cc.sizeof('size_t'))
cdata.set('Select_fd_set_t', 'fd_set *')

cdata.set('NV_PRESERVES_UV_BITS', cc.sizeof('double'))
cdata.set('NV_PRESERVES_UV', nvsize >= uvsize)
cdata.set('NV_OVERFLOWS_INTEGERS_AT', '1.0e+15')

cdata.set('U8SIZE', cc.sizeof('unsigned char'))
cdata.set('U16SIZE', cc.sizeof('unsigned short'))
cdata.set('U32SIZE', cc.sizeof('unsigned int'))
cdata.set('U64SIZE', cc.sizeof('unsigned long long'))

cdata.set('I8SIZE', cc.sizeof('signed char'))
cdata.set('I16SIZE', cc.sizeof('signed short'))
cdata.set('I32SIZE', cc.sizeof('signed int'))
cdata.set('I64SIZE', cc.sizeof('signed long long'))

cdata.set('PTRSIZE', cc.sizeof('void *'))

cdata.set_quoted('SH_PATH', '/bin/sh')

cdata.set('Size_t', 'size_t')
cdata.set('SSize_t', 'ssize_t')
cdata.set('Off_t', 'off_t')
cdata.set('Mode_t', 'mode_t')
cdata.set('Gid_t', 'gid_t')
cdata.set('Uid_t', 'uid_t')
cdata.set('Pid_t', 'pid_t')
cdata.set('Sigjmp_buf', 'sigjmp_buf')
cdata.set('Stat_t', 'struct stat')
cdata.set('Signal_t', 'void')
cdata.set('Time_t', 'time_t')
cdata.set('Malloc_t', 'void *')
cdata.set('Free_t', 'void')
cdata.set('Direntry_t', 'struct dirent')

cdata.set('Gid_t_sign', '-1')

cdata.set('Quad_t', 'int64_t')
cdata.set('Uquad_t', 'uint64_t')
cdata.set('QUADKIND', '4')  # QUAD_IS_INT64_T == 4

cdata.set('Drand01()', '((double)rand()/RAND_MAX)')
cdata.set('Rand_seed_t', 'unsigned int')
cdata.set('seedDrand01(x)', 'srand((unsigned int)(x))')
cdata.set('RANDBITS', 15)

cdata.set('I_STDINT', cc.has_header('stdint.h'))
cdata.set('I_UNISTD', cc.has_header('unistd.h'))
cdata.set('I_WCHAR', cc.has_header('wchar.h'))
cdata.set('I_LOCALE', cc.has_header('locale.h'))
cdata.set('I_DIRENT', cc.has_header('dirent.h'))

cdata.set('HAS_SELECT', 1)
cdata.set('HAS_PIPE', 1)
cdata.set('HAS_FORK', 1)
cdata.set(
  'HAS_LDBL_DIG',
  cc.has_define(
    'LDBL_DIG',
    prefix: '#include <float.h>',
  ),
)

cdata.set('I_SYS_TYPES', cc.has_header('sys/types.h'))
cdata.set('I_SYS_PARAM', cc.has_header('sys/param.h'))
cdata.set('I_SYS_RESOURCE', cc.has_header('sys/resource.h'))
cdata.set('I_SYS_SELECT', cc.has_header('sys/select.h'))
cdata.set('I_SYS_STAT', cc.has_header('sys/stat.h'))
cdata.set('I_SYS_TIME', cc.has_header('sys/time.h'))
cdata.set('I_SYS_TIMES', cc.has_header('sys/times.h'))
cdata.set('I_SYS_WAIT', cc.has_header('sys/wait.h'))
cdata.set('I_SYS_IOCTL', cc.has_header('sys/ioctl.h'))
cdata.set('I_PTHREAD', cc.has_header('pthread.h'))
cdata.set('I_INTTYPES', cc.has_header('inttypes.h'))
cdata.set('I_FCNTL', cc.has_header('fcntl.h'))
cdata.set('I_UTIME', cc.has_header('utime.h'))
cdata.set('I_PWD', cc.has_header('pwd.h'))
cdata.set('I_GRP', cc.has_header('grp.h'))
cdata.set('I_SIGNAL', cc.has_header('signal.h'))
cdata.set('I_SETJMP', cc.has_header('setjmp.h'))
cdata.set('I_LANGINFO', cc.has_header('langinfo.h'))
cdata.set('I_PTHREAD', cc.has_header('pthread.h'))

cdata.set(
  'HAS_MBTOWC',
  cc.has_function(
    'mbtowc',
    prefix: '#include <stdlib.h>',
  ),
)
cdata.set(
  'HAS_MBRTOWC',
  cc.has_function(
    'mbrtowc',
    prefix: '#include <stdlib.h>',
  ),
)

cdata.set('LOCALTIME_MIN', 0)
cdata.set('LOCALTIME_MAX', 0)

cdata.set('MULTIPLICITY', 1)
cdata.set('PERL_CORE', 1)

project_version = meson.project_version().split('.')
cdata.set('PERL_REVISION', project_version[0].to_int())
cdata.set('PERL_VERSION', project_version[1].to_int())
cdata.set('PERL_SUBVERSION', project_version[2].to_int())

cdata.set('NEED_VA_COPY', 1)
cdata.set('USE_PERLIO', 1)
cdata.set('USE_LOCALE', 1)
cdata.set('USE_ITHREADS', 1)
# cdata.set('USE_QUADMATH', 1)
cdata.set('CHARBITS', 8)
cdata.set('HAS_NL_LANGINFO', cc.has_header('langinfo.h'))
cdata.set(
  'HAS_NL_LANGINFO_L',
  cc.has_function(
    'nl_langinfo_l',
    prefix: '#include <langinfo.h>',
  ),
)
cdata.set('HAS_QUAD', 1)

nsig = cc.get_define(
  'NSIG',
  prefix: '#include <signal.h>',
)

signames = cc.run(
  '#include "meson_signames.c"',
  include_directories: inc,
  required: true,
)
signums = cc.run(
  '#include "meson_signums.c"',
  include_directories: inc,
  required: true,
)

cdata.set('SIG_NAME', signames.stdout().strip())
cdata.set('SIG_NUM', signums.stdout().strip())
cdata.set('SIG_SIZE', nsig)

config = configure_file(
  output: 'config.h',
  configuration: cdata,
  install: true,
  install_dir: get_option('includedir') / 'perl5',
)

git_cdata = configuration_data()
git_cdata.set('PERL_GIT_UNPUSHED_COMMITS', '')

git_version = configure_file(
  output: 'git_version.h',
  configuration: git_cdata,
  install: true,
  install_dir: get_option('includedir') / 'perl5',
)

gen_uudmap = executable('generate_uudmap', 'generate_uudmap.c')

uudmap_out = custom_target(
  'uudmap',
  output: ['uudmap.h', 'bitcount.h', 'mg_data.h'],
  command: [gen_uudmap, '@OUTPUT0@', '@OUTPUT1@', '@OUTPUT2@'],
)

regexec_file = files('regexec.c')

subdir('ext/re')

src = files(
  'av.c',
  'builtin.c',
  'caretx.c',
  'class.c',
  'deb.c',
  'doio.c',
  'doop.c',
  'dquote.c',
  'dump.c',
  'globals.c',
  'gv.c',
  'hv.c',
  'keywords.c',
  'locale.c',
  'mathoms.c',
  'mg.c',
  'miniperlmain.c',
  'mro_core.c',
  'numeric.c',
  'op.c',
  'pad.c',
  'peep.c',
  'perl.c',
  'perlio.c',
  'perly.c',
  'pp.c',
  'pp_ctl.c',
  'pp_hot.c',
  'pp_pack.c',
  'pp_sort.c',
  'pp_sys.c',
  'pp_sys.c',
  'reentr.c',
  'regcomp.c',
  'regcomp_invlist.c',
  'regcomp_study.c',
  'regcomp_trie.c',
  'regexec.c',
  'run.c',
  'scope.c',
  'sv.c',
  'taint.c',
  'time64.c',
  'toke.c',
  'universal.c',
  'utf8.c',
  'util.c',
)

m = cc.find_library(
  'm',
  required: false,
)

perl = executable(
  'perl',
  src,
  uudmap_out,
  config,
  link_with: libregexec,
  dependencies: [m],
  install: true,
)

meson.override_find_program('perl', perl)
