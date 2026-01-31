project(
  'aws-lc',
  'c',
  version: '1.67.0',
  license: 'OpenSSL AND ISC AND SSLeay-standalone AND MIT AND BSD-3-Clause AND Apache-2.0',
  default_options: [
    'warning_level=3',
    'cpp_std=c++17',
    'c_std=c11',
  ],
  meson_version: '>=1.4.0',
)

tests_opt = get_option('tests').disable_auto_if(meson.is_subproject())
libssl_opt = get_option('libssl')
fips_opt = get_option('fips')
asm_opt = get_option('asm').enable_auto_if(fips_opt.allowed())
openssl_override_opt = get_option('openssl-override')

go = find_program(
  'go',
  required: fips_opt,
  native: true,
)
perl = find_program(
  'perl',
  required: fips_opt,
  native: true,
)
jitterentropy = dependency(
  'jitterentropy',
  required: fips_opt,
)

fips_opt = fips_opt.require(
  asm_opt.allowed(),
  error_message: 'Assembly must be enabled to build aws-lc in FIPS mode.',
)
fips_opt = fips_opt.require(
  go.found(),
  error_message: 'Go toolchain is required to build aws-lc in FIPS mode.',
)
fips_opt = fips_opt.require(
  perl.found(),
  error_message: 'Perl is required to build aws-lc in FIPS mode.',
)
fips_opt = fips_opt.require(
  jitterentropy.found(),
  error_message: 'Jitterentropy library is required to build aws-lc in FIPS mode.',
)

inject_hash_src = files('util/fipstools/inject_hash/inject_hash.go')
capture_hash_src = files('util/fipstools/capture_hash/capture_hash.go')

custom_target_sh = find_program(
  'inject_hash_wrapper.sh',
  required: fips_opt,
  native: true,
)

if tests_opt.allowed() or libssl_opt.allowed()
  add_languages(
    'cpp',
    native: false,
  )
endif

gtest_dep = dependency(
  'gtest',
  required: tests_opt,
)
inc = include_directories('include')

# For now use the bundled s2n-bignum until they create a versioned release so it
# can be imported into wrapdb.
# see https://github.com/mesonbuild/wrapdb/pull/2486 and https://github.com/awslabs/s2n-bignum/issues/313
s2n_bignum_root = meson.current_source_dir() / 'third_party/s2n-bignum/s2n-bignum-imported'
s2n_bignum_inc = include_directories(
  'third_party/s2n-bignum/s2n-bignum-imported/include',
)

generated = files('generated-src/err_data.c')

if host_machine.system() == 'windows'
  osname = 'win'
elif host_machine.system() == 'darwin'
  osname = 'macos'
else
  osname = 'linux'
endif

if host_machine.cpu_family() == 'x86_64'
  archname = 'x86_64'
elif host_machine.cpu_family() == 'aarch64'
  archname = 'aarch64'
else
  archname = host_machine.cpu_family()
endif

asm_src = []

if host_machine.system() == 'linux' and host_machine.cpu_family() == 'x86_64'
  generated_src = 'generated-src/linux-x86_64'
  asm_src += files(
    'generated-src/linux-x86_64/crypto/chacha/chacha-x86_64.S',
    'generated-src/linux-x86_64/crypto/cipher_extra/aes128gcmsiv-x86_64.S',
    'generated-src/linux-x86_64/crypto/cipher_extra/aesni-sha1-x86_64.S',
    'generated-src/linux-x86_64/crypto/cipher_extra/aesni-sha256-x86_64.S',
    'generated-src/linux-x86_64/crypto/cipher_extra/chacha20_poly1305_x86_64.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/aesni-gcm-avx512.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/aesni-gcm-x86_64.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/aesni-x86_64.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/aesni-xts-avx512.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/ghash-ssse3-x86_64.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/ghash-x86_64.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/md5-x86_64.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/p256-x86_64-asm.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/p256_beeu-x86_64-asm.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/rdrand-x86_64.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/rsaz-2k-avx512.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/rsaz-3k-avx512.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/rsaz-4k-avx512.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/rsaz-avx2.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/sha1-x86_64.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/sha256-x86_64.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/sha512-x86_64.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/vpaes-x86_64.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/x86_64-mont.S',
    'generated-src/linux-x86_64/crypto/fipsmodule/x86_64-mont5.S',
  )
elif host_machine.system() == 'linux' and host_machine.cpu_family() == 'aarch64'
  asm_src += files(
    'generated-src/linux-aarch64/crypto/chacha/chacha-armv8.S',
    'generated-src/linux-aarch64/crypto/cipher_extra/chacha20_poly1305_armv8.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/aesv8-armx.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/aesv8-gcm-armv8-unroll8.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/aesv8-gcm-armv8.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/armv8-mont.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/bn-armv8.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/ghash-neon-armv8.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/ghashv8-armx.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/keccak1600-armv8.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/md5-armv8.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/p256-armv8-asm.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/p256_beeu-armv8-asm.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/rndr-armv8.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/sha1-armv8.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/sha256-armv8.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/sha512-armv8.S',
    'generated-src/linux-aarch64/crypto/fipsmodule/vpaes-armv8.S',
  )
elif host_machine.system() == 'linux' and host_machine.cpu_family() == 'ppc64le'
  asm_src += files(
    'generated-src/linux-ppc64le/crypto/fipsmodule/aesp8-ppc.S',
    'generated-src/linux-ppc64le/crypto/fipsmodule/ghashp8-ppc.S',
  )
elif host_machine.system() == 'windows' and host_machine.cpu_family() == 'x86_64'
  asm_src += files(
    'generated-src/win-x86_64/crypto/chacha/chacha-x86_64.asm',
    'generated-src/win-x86_64/crypto/cipher_extra/aes128gcmsiv-x86_64.asm',
    'generated-src/win-x86_64/crypto/cipher_extra/aesni-sha1-x86_64.asm',
    'generated-src/win-x86_64/crypto/cipher_extra/aesni-sha256-x86_64.asm',
    'generated-src/win-x86_64/crypto/cipher_extra/chacha20_poly1305_x86_64.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/aesni-gcm-avx512.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/aesni-gcm-x86_64.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/aesni-x86_64.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/aesni-xts-avx512.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/ghash-ssse3-x86_64.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/ghash-x86_64.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/md5-x86_64.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/p256-x86_64-asm.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/p256_beeu-x86_64-asm.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/rdrand-x86_64.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/rsaz-2k-avx512.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/rsaz-3k-avx512.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/rsaz-4k-avx512.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/rsaz-avx2.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/sha1-x86_64.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/sha256-x86_64.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/sha512-x86_64.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/vpaes-x86_64.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/x86_64-mont.asm',
    'generated-src/win-x86_64/crypto/fipsmodule/x86_64-mont5.asm',
  )
elif host_machine.system() == 'windows' and host_machine.cpu_family() == 'aarch64'
  asm_src += files(
    'generated-src/win-aarch64/crypto/chacha/chacha-armv8.S',
    'generated-src/win-aarch64/crypto/cipher_extra/chacha20_poly1305_armv8.S',
    'generated-src/win-aarch64/crypto/fipsmodule/aesv8-armx.S',
    'generated-src/win-aarch64/crypto/fipsmodule/aesv8-gcm-armv8-unroll8.S',
    'generated-src/win-aarch64/crypto/fipsmodule/aesv8-gcm-armv8.S',
    'generated-src/win-aarch64/crypto/fipsmodule/armv8-mont.S',
    'generated-src/win-aarch64/crypto/fipsmodule/bn-armv8.S',
    'generated-src/win-aarch64/crypto/fipsmodule/ghash-neon-armv8.S',
    'generated-src/win-aarch64/crypto/fipsmodule/ghashv8-armx.S',
    'generated-src/win-aarch64/crypto/fipsmodule/keccak1600-armv8.S',
    'generated-src/win-aarch64/crypto/fipsmodule/md5-armv8.S',
    'generated-src/win-aarch64/crypto/fipsmodule/p256-armv8-asm.S',
    'generated-src/win-aarch64/crypto/fipsmodule/p256_beeu-armv8-asm.S',
    'generated-src/win-aarch64/crypto/fipsmodule/rndr-armv8.S',
    'generated-src/win-aarch64/crypto/fipsmodule/sha1-armv8.S',
    'generated-src/win-aarch64/crypto/fipsmodule/sha256-armv8.S',
    'generated-src/win-aarch64/crypto/fipsmodule/sha512-armv8.S',
    'generated-src/win-aarch64/crypto/fipsmodule/vpaes-armv8.S',
  )
endif

subdir('include/openssl')
subdir('crypto')

private_c_args += cc.get_supported_arguments('-Wno-deprecated-declarations')

libcrypto_testcases = {
  'abi_self_test': {
    'sources': files('crypto/abi_self_test.cc'),
  },
  'asn1_test': {
    'sources': files('crypto/asn1/asn1_test.cc'),
  },
  'base64_test': {
    'sources': files('crypto/base64/base64_test.cc'),
  },
  'bio_md_test': {
    'sources': files('crypto/bio/bio_md_test.cc'),
  },
  'bio_socket_test': {
    'sources': files('crypto/bio/bio_socket_test.cc'),
  },
  'bio_test': {
    'sources': files('crypto/bio/bio_test.cc'),
  },
  'blake2_test': {
    'sources': files('crypto/blake2/blake2_test.cc'),
  },
  'buf_test': {
    'sources': files('crypto/buf/buf_test.cc'),
  },
  'bytestring_test': {
    'sources': files('crypto/bytestring/bytestring_test.cc'),
  },
  'chacha_test': {
    'sources': files('crypto/chacha/chacha_test.cc'),
  },
  'aead_test': {
    'sources': files('crypto/cipher_extra/aead_test.cc'),
  },
  'cipher_test': {
    'sources': files('crypto/cipher_extra/cipher_test.cc'),
  },
  'compiler_test': {
    'sources': files('crypto/compiler_test.cc'),
  },
  'conf_test': {
    'sources': files('crypto/conf/conf_test.cc'),
  },
  'console_test': {
    'sources': files('crypto/console/console_test.cc'),
  },
  'constant_time_test': {
    'sources': files('crypto/constant_time_test.cc'),
  },
  'crypto_test': {
    'sources': files('crypto/crypto_test.cc'),
  },
  'blowfish_test': {
    'sources': files('crypto/decrepit/blowfish/blowfish_test.cc'),
  },
  'cast_test': {
    'sources': files('crypto/decrepit/cast/cast_test.cc'),
  },
  'cfb_test': {
    'sources': files('crypto/decrepit/cfb/cfb_test.cc'),
  },
  'decrepit_evp_test': {
    'sources': files('crypto/decrepit/evp/evp_test.cc'),
  },
  'ripemd_test': {
    'sources': files('crypto/decrepit/ripemd/ripemd_test.cc'),
  },
  'des_test': {
    'sources': files('crypto/des/des_test.cc'),
  },
  'dh_extra_test': {
    'sources': files('crypto/dh_extra/dh_test.cc'),
  },
  'digest_extra_test': {
    'sources': files('crypto/digest_extra/digest_test.cc'),
  },
  'dsa_test': {
    'sources': files('crypto/dsa/dsa_test.cc'),
  },
  'ecdh_extra_test': {
    'sources': files('crypto/ecdh_extra/ecdh_test.cc'),
  },
  'endian_test': {
    'sources': files('crypto/endian_test.cc'),
  },
  'err_test': {
    'sources': files('crypto/err/err_test.cc'),
  },
  'evp_extra_test': {
    'sources': files('crypto/evp_extra/evp_extra_test.cc'),
  },
  'evp_test': {
    'sources': files('crypto/evp_extra/evp_test.cc'),
  },
  'mldsa_test': {
    'sources': files('crypto/evp_extra/mldsa_test.cc'),
  },
  'p_kem_test': {
    'sources': files('crypto/evp_extra/p_kem_test.cc'),
  },
  'p_pqdsa_test': {
    'sources': files('crypto/evp_extra/p_pqdsa_test.cc'),
  },
  'scrypt_test': {
    'sources': files('crypto/evp_extra/scrypt_test.cc'),
  },
  'fips_callback_test': {
    'sources': files('crypto/fips_callback_test.cc'),
  },
  'aes_test': {
    'sources': files('crypto/fipsmodule/aes/aes_test.cc'),
  },
  'bn_assert_test': {
    'sources': files('crypto/fipsmodule/bn/bn_assert_test.cc'),
  },
  'bn_test': {
    'sources': files('crypto/fipsmodule/bn/bn_test.cc'),
  },
  'cmac_test': {
    'sources': files('crypto/fipsmodule/cmac/cmac_test.cc'),
  },
  'cpu_aarch64_dit_test': {
    'sources': files('crypto/fipsmodule/cpucap/cpu_aarch64_dit_test.cc'),
  },
  'cpu_arm_linux_test': {
    'sources': files('crypto/fipsmodule/cpucap/cpu_arm_linux_test.cc'),
  },
  'ed25519_test': {
    'sources': files('crypto/fipsmodule/curve25519/ed25519_test.cc'),
  },
  'x25519_test': {
    'sources': files('crypto/fipsmodule/curve25519/x25519_test.cc'),
  },
  'ec_test': {
    'sources': files('crypto/fipsmodule/ec/ec_test.cc'),
  },
  'p256_nistz_test': {
    'sources': files('crypto/fipsmodule/ec/p256-nistz_test.cc'),
  },
  'ecdsa_test': {
    'sources': files('crypto/fipsmodule/ecdsa/ecdsa_test.cc'),
  },
  'evp_ctx_test': {
    'sources': files('crypto/fipsmodule/evp/evp_ctx_test.cc'),
  },
  'hkdf_test': {
    'sources': files('crypto/fipsmodule/hkdf/hkdf_test.cc'),
  },
  'kdf_test': {
    'sources': files('crypto/fipsmodule/kdf/kdf_test.cc'),
  },
  'md5_test': {
    'sources': files('crypto/fipsmodule/md5/md5_test.cc'),
  },
  'ml_kem_test': {
    'sources': files('crypto/fipsmodule/ml_kem/ml_kem_test.cc'),
  },
  'gcm_test': {
    'sources': files('crypto/fipsmodule/modes/gcm_test.cc'),
  },
  'xts_test': {
    'sources': files('crypto/fipsmodule/modes/xts_test.cc'),
  },
  'pbkdf_test': {
    'sources': files('crypto/fipsmodule/pbkdf/pbkdf_test.cc'),
  },
  'cpu_jitter_test': {
    'sources': files('crypto/fipsmodule/rand/cpu_jitter_test.cc'),
    'dependencies': [jitterentropy],
  },
  'ctrdrbg_test': {
    'sources': files('crypto/fipsmodule/rand/ctrdrbg_test.cc'),
  },
  'entropy_source_test': {
    'sources': files('crypto/fipsmodule/rand/entropy/entropy_source_test.cc'),
  },
  'tree_drbg_jitter_entropy_isolated_test': {
    'sources': files(
      'crypto/fipsmodule/rand/entropy/tree_drbg_jitter_entropy_isolated_test.cc',
    ),
  },
  'rand_isolated_test': {
    'sources': files('crypto/fipsmodule/rand/rand_isolated_test.cc'),
  },
  'rand_test': {
    'sources': files('crypto/fipsmodule/rand/rand_test.cc'),
  },
  'service_indicator_test': {
    'sources': files(
      'crypto/fipsmodule/service_indicator/service_indicator_test.cc',
    ),
    'timeout': 3000,  # slooooooow
  },
  'sha3_test': {
    'sources': files('crypto/fipsmodule/sha/sha3_test.cc'),
  },
  'sha_test': {
    'sources': files('crypto/fipsmodule/sha/sha_test.cc'),
  },
  'sshkdf_test': {
    'sources': files('crypto/fipsmodule/sshkdf/sshkdf_test.cc'),
  },
  'hpke_test': {
    'sources': files('crypto/hpke/hpke_test.cc'),
  },
  'hrss_test': {
    'sources': files('crypto/hrss/hrss_test.cc'),
  },
  'impl_dispatch_test': {
    'sources': files('crypto/impl_dispatch_test.cc'),
  },
  'lhash_test': {
    'sources': files('crypto/lhash/lhash_test.cc'),
  },
  'mem_set_test': {
    'sources': files('crypto/mem_set_test.cc'),
  },
  'mem_test': {
    'sources': files('crypto/mem_test.cc'),
  },
  'obj_test': {
    'sources': files('crypto/obj/obj_test.cc'),
  },
  'ocsp_test': {
    'sources': files('crypto/ocsp/ocsp_test.cc'),
  },
  'pem_test': {
    'sources': files('crypto/pem/pem_test.cc'),
  },
  'bio_cipher_test': {
    'sources': files('crypto/pkcs7/bio/bio_cipher_test.cc'),
  },
  'pkcs7_test': {
    'sources': files('crypto/pkcs7/pkcs7_test.cc'),
  },
  'pkcs12_test': {
    'sources': files('crypto/pkcs8/pkcs12_test.cc'),
  },
  'pkcs8_test': {
    'sources': files('crypto/pkcs8/pkcs8_test.cc'),
  },
  'poly1305_test': {
    'sources': files('crypto/poly1305/poly1305_test.cc'),
  },
  'pool_test': {
    'sources': files('crypto/pool/pool_test.cc'),
  },
  'ccrandomgeneratebytes_test': {
    'sources': files('crypto/rand_extra/ccrandomgeneratebytes_test.cc'),
  },
  'getentropy_test': {
    'sources': files('crypto/rand_extra/getentropy_test.cc'),
  },
  'urandom_test': {
    'sources': files('crypto/rand_extra/urandom_test.cc'),
  },
  'vm_ube_fallback_test': {
    'sources': files('crypto/rand_extra/vm_ube_fallback_test.cc'),
  },
  'refcount_test': {
    'sources': files('crypto/refcount_test.cc'),
  },
  'rsa_test': {
    'sources': files('crypto/rsa_extra/rsa_test.cc'),
  },
  'rsassa_pss_asn1_test': {
    'sources': files('crypto/rsa_extra/rsassa_pss_asn1_test.cc'),
  },
  'rwlock_static_init_test': {
    'sources': files('crypto/rwlock_static_init.cc'),
  },
  'self_test': {
    'sources': files('crypto/self_test.cc'),
  },
  'siphash_test': {
    'sources': files('crypto/siphash/siphash_test.cc'),
  },
  'spake25519_test': {
    'sources': files('crypto/spake25519/spake25519_test.cc'),
  },
  'stack_test': {
    'sources': files('crypto/stack/stack_test.cc'),
  },
  'file_test_gtest': {
    'sources': files('crypto/test/file_test_gtest.cc'),
  },
  'malloc_test': {
    'sources': files('crypto/test/malloc.cc'),
  },
  'thread_test': {
    'sources': files('crypto/thread_test.cc'),
  },
  'trust_token_test': {
    'sources': files('crypto/trust_token/trust_token_test.cc'),
  },
  'fork_ube_detect_test': {
    'sources': files('crypto/ube/fork_ube_detect_test.cc'),
  },
  'ube_test': {
    'sources': files('crypto/ube/ube_test.cc'),
  },
  'vm_ube_detect_test': {
    'sources': files('crypto/ube/vm_ube_detect_test.cc'),
  },
  'x509_tab_test': {
    'sources': files('crypto/x509/tab_test.cc'),
  },
  'x509_compat_test': {
    'sources': files('crypto/x509/x509_compat_test.cc'),
  },
  'x509_test': {
    'sources': files('crypto/x509/x509_test.cc'),
  },
  'x509_time_test': {
    'sources': files('crypto/x509/x509_time_test.cc'),
  },
}

testcases = libcrypto_testcases

if gtest_dep.found()
  tar = find_program(
    'tar',
    native: true,
  )
  crypto_test_data = custom_target(
    'crypto_test_data',
    output: 'crypto_test_data.cc',
    input: 'generated-src/crypto_test_data.cc.tar.bz2',
    command: [tar, 'jxf', '@INPUT@', '-O'],
    capture: true,
  )

  libtest_util = static_library(
    'aws_lc_test_util',
    'crypto/test/test_util.cc',
    'crypto/test/file_util.cc',
    'crypto/test/file_test.cc',
    'crypto/test/file_test_gtest.cc',
    'crypto/test/wycheproof_util.cc',
    'crypto/test/x509_util.cc',
    'crypto/test/abi_test.cc',
    'crypto/test/gtest_main.cc',
    crypto_test_data,
    include_directories: [inc, s2n_bignum_inc],
    dependencies: [gtest_dep, libcrypto_dep],
    cpp_args: [private_c_args],
  )

  foreach testname, kwargs : testcases
    kwargs += {
      'dependencies': kwargs.get('dependencies', []) + [
        gtest_dep,
        libcrypto_dep,
      ],
    }

    exe = executable(
      testname,
      sources: kwargs['sources'],
      cpp_args: [private_c_args],
      dependencies: kwargs.get('dependencies', []),
      link_with: [libtest_util],
    )

    test(
      testname,
      exe,
      protocol: 'gtest',
      timeout: kwargs.get('timeout', 30),
    )
  endforeach
endif

if libssl_opt.allowed()
  subdir('ssl')
endif

if openssl_override_opt
  meson.override_dependency('libcrypto', libcrypto_dep)
  meson.override_dependency('libssl', libssl_dep)
endif

summary(
  {
    'Tests': tests_opt,
    'libssl': libssl_opt,
    'FIPS mode': fips_opt,
    'Assembly': asm_opt,
    'OpenSSL override': openssl_override_opt,
  },
)
