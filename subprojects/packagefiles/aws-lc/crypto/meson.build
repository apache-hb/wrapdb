cc = meson.get_compiler('c')

src = files(
  'asn1/a_bitstr.c',
  'asn1/a_bool.c',
  'asn1/a_d2i_fp.c',
  'asn1/a_dup.c',
  'asn1/a_gentm.c',
  'asn1/a_i2d_fp.c',
  'asn1/a_int.c',
  'asn1/a_mbstr.c',
  'asn1/a_object.c',
  'asn1/a_octet.c',
  'asn1/a_strex.c',
  'asn1/a_strnid.c',
  'asn1/a_time.c',
  'asn1/a_type.c',
  'asn1/a_utctm.c',
  'asn1/a_utf8.c',
  'asn1/asn1_lib.c',
  'asn1/asn1_par.c',
  'asn1/asn_pack.c',
  'asn1/f_int.c',
  'asn1/f_string.c',
  'asn1/posix_time.c',
  'asn1/tasn_dec.c',
  'asn1/tasn_enc.c',
  'asn1/tasn_fre.c',
  'asn1/tasn_new.c',
  'asn1/tasn_typ.c',
  'asn1/tasn_utl.c',
  'base64/base64.c',
  'bio/bio.c',
  'bio/bio_addr.c',
  'bio/bio_mem.c',
  'bio/connect.c',
  'bio/dgram.c',
  'bio/errno.c',
  'bio/fd.c',
  'bio/file.c',
  'bio/hexdump.c',
  'bio/md.c',
  'bio/pair.c',
  'bio/printf.c',
  'bio/socket.c',
  'bio/socket_helper.c',
  'blake2/blake2.c',
  'bn_extra/bn_asn1.c',
  'bn_extra/convert.c',
  'buf/buf.c',
  'bytestring/asn1_compat.c',
  'bytestring/ber.c',
  'bytestring/cbb.c',
  'bytestring/cbs.c',
  'bytestring/unicode.c',
  'chacha/chacha.c',
  'cipher_extra/cipher_extra.c',
  'cipher_extra/derive_key.c',
  'cipher_extra/e_aes_cbc_hmac_sha1.c',
  'cipher_extra/e_aes_cbc_hmac_sha256.c',
  'cipher_extra/e_aesctrhmac.c',
  'cipher_extra/e_aesgcmsiv.c',
  'cipher_extra/e_chacha20poly1305.c',
  'cipher_extra/e_des.c',
  'cipher_extra/e_null.c',
  'cipher_extra/e_rc2.c',
  'cipher_extra/e_rc4.c',
  'cipher_extra/e_tls.c',
  'cipher_extra/tls_cbc.c',
  'conf/conf.c',
  'console/console.c',
  'crypto.c',
  'decrepit/bio/base64_bio.c',
  'decrepit/blowfish/blowfish.c',
  'decrepit/cast/cast.c',
  'decrepit/cast/cast_tables.c',
  'decrepit/cfb/cfb.c',
  'decrepit/dh/dh_decrepit.c',
  'decrepit/evp/evp_do_all.c',
  'decrepit/obj/obj_decrepit.c',
  'decrepit/ripemd/ripemd.c',
  'decrepit/rsa/rsa_decrepit.c',
  'decrepit/x509/x509_decrepit.c',
  'des/des.c',
  'dh_extra/dh_asn1.c',
  'dh_extra/params.c',
  'digest_extra/digest_extra.c',
  'dsa/dsa.c',
  'dsa/dsa_asn1.c',
  'ec_extra/ec_asn1.c',
  'ec_extra/ec_derive.c',
  'ec_extra/hash_to_curve.c',
  'ecdh_extra/ecdh_extra.c',
  'ecdsa_extra/ecdsa_asn1.c',
  'engine/engine.c',
  'err/err.c',
  'evp_extra/evp_asn1.c',
  'evp_extra/p_dh.c',
  'evp_extra/p_dh_asn1.c',
  'evp_extra/p_dsa.c',
  'evp_extra/p_dsa_asn1.c',
  'evp_extra/p_ec_asn1.c',
  'evp_extra/p_ed25519_asn1.c',
  'evp_extra/p_hmac_asn1.c',
  'evp_extra/p_kem_asn1.c',
  'evp_extra/p_methods.c',
  'evp_extra/p_pqdsa_asn1.c',
  'evp_extra/p_rsa_asn1.c',
  'evp_extra/p_x25519.c',
  'evp_extra/p_x25519_asn1.c',
  'evp_extra/print.c',
  'evp_extra/scrypt.c',
  'evp_extra/sign.c',
  'ex_data.c',
  'hpke/hpke.c',
  'hrss/hrss.c',
  'lhash/lhash.c',
  'mem.c',
  'obj/obj.c',
  'obj/obj_xref.c',
  'ocsp/ocsp_asn.c',
  'ocsp/ocsp_client.c',
  'ocsp/ocsp_extension.c',
  'ocsp/ocsp_http.c',
  'ocsp/ocsp_lib.c',
  'ocsp/ocsp_print.c',
  'ocsp/ocsp_server.c',
  'ocsp/ocsp_verify.c',
  'pem/pem_all.c',
  'pem/pem_info.c',
  'pem/pem_lib.c',
  'pem/pem_oth.c',
  'pem/pem_pk8.c',
  'pem/pem_pkey.c',
  'pem/pem_x509.c',
  'pem/pem_xaux.c',
  'pkcs7/bio/cipher.c',
  'pkcs7/pkcs7.c',
  'pkcs7/pkcs7_asn1.c',
  'pkcs7/pkcs7_x509.c',
  'pkcs8/p5_pbev2.c',
  'pkcs8/pkcs8.c',
  'pkcs8/pkcs8_x509.c',
  'poly1305/poly1305.c',
  'poly1305/poly1305_arm.c',
  'poly1305/poly1305_vec.c',
  'pool/pool.c',
  'rand_extra/ccrandomgeneratebytes.c',
  'rand_extra/deterministic.c',
  'rand_extra/getentropy.c',
  'rand_extra/rand_extra.c',
  'rand_extra/urandom.c',
  'rand_extra/vm_ube_fallback.c',
  'rand_extra/windows.c',
  'rc4/rc4.c',
  'refcount_c11.c',
  'refcount_lock.c',
  'refcount_win.c',
  'rsa_extra/rsa_asn1.c',
  'rsa_extra/rsa_crypt.c',
  'rsa_extra/rsa_print.c',
  'rsa_extra/rsassa_pss_asn1.c',
  'siphash/siphash.c',
  'spake25519/spake25519.c',
  'stack/stack.c',
  'thread.c',
  'thread_none.c',
  'thread_pthread.c',
  'thread_win.c',
  'trust_token/pmbtoken.c',
  'trust_token/trust_token.c',
  'trust_token/voprf.c',
  'ube/fork_ube_detect.c',
  'ube/ube.c',
  'ube/vm_ube_detect.c',
  'ui/ui.c',
  'x509/a_digest.c',
  'x509/a_sign.c',
  'x509/a_verify.c',
  'x509/algorithm.c',
  'x509/asn1_gen.c',
  'x509/by_dir.c',
  'x509/by_file.c',
  'x509/i2d_pr.c',
  'x509/name_print.c',
  'x509/policy.c',
  'x509/rsa_pss.c',
  'x509/t_crl.c',
  'x509/t_req.c',
  'x509/t_x509.c',
  'x509/t_x509a.c',
  'x509/v3_akey.c',
  'x509/v3_akeya.c',
  'x509/v3_alt.c',
  'x509/v3_bcons.c',
  'x509/v3_bitst.c',
  'x509/v3_conf.c',
  'x509/v3_cpols.c',
  'x509/v3_crld.c',
  'x509/v3_enum.c',
  'x509/v3_extku.c',
  'x509/v3_genn.c',
  'x509/v3_ia5.c',
  'x509/v3_info.c',
  'x509/v3_int.c',
  'x509/v3_lib.c',
  'x509/v3_ncons.c',
  'x509/v3_ocsp.c',
  'x509/v3_pcons.c',
  'x509/v3_pmaps.c',
  'x509/v3_prn.c',
  'x509/v3_purp.c',
  'x509/v3_skey.c',
  'x509/v3_utl.c',
  'x509/x509.c',
  'x509/x509_att.c',
  'x509/x509_cmp.c',
  'x509/x509_d2.c',
  'x509/x509_def.c',
  'x509/x509_ext.c',
  'x509/x509_lu.c',
  'x509/x509_obj.c',
  'x509/x509_req.c',
  'x509/x509_set.c',
  'x509/x509_trs.c',
  'x509/x509_txt.c',
  'x509/x509_v3.c',
  'x509/x509_vfy.c',
  'x509/x509_vpm.c',
  'x509/x509cset.c',
  'x509/x509name.c',
  'x509/x509rset.c',
  'x509/x509spki.c',
  'x509/x_algor.c',
  'x509/x_all.c',
  'x509/x_attrib.c',
  'x509/x_crl.c',
  'x509/x_exten.c',
  'x509/x_name.c',
  'x509/x_pubkey.c',
  'x509/x_req.c',
  'x509/x_sig.c',
  'x509/x_spki.c',
  'x509/x_val.c',
  'x509/x_x509.c',
  'x509/x_x509a.c',
)

if asm_opt.allowed()
  src += files('hrss/asm/poly_rq_mul.S')
endif

bcm_src = files('fipsmodule/bcm.c')

ldscript = cc.get_id() == 'gcc' ? 'fipsmodule/gcc_fips_shared.lds' : 'fipsmodule/fips_shared.lds'

bcm_asm_src = []

x86_bignum_root = s2n_bignum_root / 'x86_att'

bcm_asm_src += files(
  x86_bignum_root / 'p256/p256_montjscalarmul.S',
  x86_bignum_root / 'p256/p256_montjscalarmul_alt.S',
  x86_bignum_root / 'p256/bignum_montinv_p256.S',
  x86_bignum_root / 'p384/bignum_add_p384.S',
  x86_bignum_root / 'p384/bignum_sub_p384.S',
  x86_bignum_root / 'p384/bignum_neg_p384.S',
  x86_bignum_root / 'p384/bignum_tomont_p384.S',
  x86_bignum_root / 'p384/bignum_deamont_p384.S',
  x86_bignum_root / 'p384/bignum_montmul_p384.S',
  x86_bignum_root / 'p384/bignum_montmul_p384_alt.S',
  x86_bignum_root / 'p384/bignum_montsqr_p384.S',
  x86_bignum_root / 'p384/bignum_montsqr_p384_alt.S',
  x86_bignum_root / 'p384/bignum_nonzero_6.S',
  x86_bignum_root / 'p384/bignum_littleendian_6.S',
  x86_bignum_root / 'p384/p384_montjdouble.S',
  x86_bignum_root / 'p384/p384_montjdouble_alt.S',
  x86_bignum_root / 'p384/p384_montjscalarmul.S',
  x86_bignum_root / 'p384/p384_montjscalarmul_alt.S',
  x86_bignum_root / 'p384/bignum_montinv_p384.S',
  x86_bignum_root / 'p521/bignum_add_p521.S',
  x86_bignum_root / 'p521/bignum_sub_p521.S',
  x86_bignum_root / 'p521/bignum_neg_p521.S',
  x86_bignum_root / 'p521/bignum_mul_p521.S',
  x86_bignum_root / 'p521/bignum_mul_p521_alt.S',
  x86_bignum_root / 'p521/bignum_sqr_p521.S',
  x86_bignum_root / 'p521/bignum_sqr_p521_alt.S',
  x86_bignum_root / 'p521/bignum_tolebytes_p521.S',
  x86_bignum_root / 'p521/bignum_fromlebytes_p521.S',
  x86_bignum_root / 'p521/p521_jdouble.S',
  x86_bignum_root / 'p521/p521_jdouble_alt.S',
  x86_bignum_root / 'p521/p521_jscalarmul.S',
  x86_bignum_root / 'p521/p521_jscalarmul_alt.S',
  x86_bignum_root / 'p521/bignum_inv_p521.S',
  x86_bignum_root / 'curve25519/bignum_mod_n25519.S',
  x86_bignum_root / 'curve25519/bignum_neg_p25519.S',
  x86_bignum_root / 'curve25519/bignum_madd_n25519.S',
  x86_bignum_root / 'curve25519/bignum_madd_n25519_alt.S',
  x86_bignum_root / 'curve25519/edwards25519_decode.S',
  x86_bignum_root / 'curve25519/edwards25519_decode_alt.S',
  x86_bignum_root / 'curve25519/edwards25519_encode.S',
  x86_bignum_root / 'curve25519/edwards25519_scalarmulbase.S',
  x86_bignum_root / 'curve25519/edwards25519_scalarmulbase_alt.S',
  x86_bignum_root / 'curve25519/edwards25519_scalarmuldouble.S',
  x86_bignum_root / 'curve25519/edwards25519_scalarmuldouble_alt.S',
  x86_bignum_root / 'p384/bignum_tomont_p384_alt.S',
  x86_bignum_root / 'p384/bignum_deamont_p384_alt.S',
  x86_bignum_root / 'curve25519/curve25519_x25519.S',
  x86_bignum_root / 'curve25519/curve25519_x25519_alt.S',
  x86_bignum_root / 'curve25519/curve25519_x25519base.S',
  x86_bignum_root / 'curve25519/curve25519_x25519base_alt.S',
  x86_bignum_root / 'sha3/sha3_keccak_f1600.S',
)

bcm_asm_src += files(
  'fipsmodule/ml_kem/mlkem/native/x86_64/src/intt.S',
  'fipsmodule/ml_kem/mlkem/native/x86_64/src/mulcache_compute.S',
  'fipsmodule/ml_kem/mlkem/native/x86_64/src/ntt.S',
  'fipsmodule/ml_kem/mlkem/native/x86_64/src/nttfrombytes.S',
  'fipsmodule/ml_kem/mlkem/native/x86_64/src/ntttobytes.S',
  'fipsmodule/ml_kem/mlkem/native/x86_64/src/nttunpack.S',
  'fipsmodule/ml_kem/mlkem/native/x86_64/src/polyvec_basemul_acc_montgomery_cached_asm_k2.S',
  'fipsmodule/ml_kem/mlkem/native/x86_64/src/polyvec_basemul_acc_montgomery_cached_asm_k3.S',
  'fipsmodule/ml_kem/mlkem/native/x86_64/src/polyvec_basemul_acc_montgomery_cached_asm_k4.S',
  'fipsmodule/ml_kem/mlkem/native/x86_64/src/reduce.S',
  'fipsmodule/ml_kem/mlkem/native/x86_64/src/rej_uniform_asm.S',
  'fipsmodule/ml_kem/mlkem/native/x86_64/src/tomont.S',
)

src_fipsmodule = files(
  'fipsmodule/cpucap/cpucap.c',
  'fipsmodule/fips_shared_support.c',
)

fipsmodule_c_args = [
  '-DS2N_BN_HIDE_SYMBOLS',
]

private_c_args = ['-DBORINGSSL_IMPLEMENTATION']
public_c_args = []

private_c_args += cc.get_supported_arguments(
  '-fno-common',
  '-Wno-unused-parameter',
  '-Wno-overlength-strings',
  '-Wno-extra-semi',
  '-Wno-pedantic',
)

if host_machine.system() == 'linux'
  private_c_args += ['-D_XOPEN_SOURCE=700']
endif

if get_option('default_library') == 'shared'
  public_c_args += ['-DBORINGSSL_SHARED_LIBRARY']
endif

if fips_opt.allowed()
  private_c_args += ['-DBORINGSSL_FIPS']
endif

if asm_opt.disabled()
  private_c_args += ['-DOPENSSL_NO_ASM']
endif

if asm_opt.allowed()
  src += asm_src
  bcm_src += bcm_asm_src
endif

if not jitterentropy.found()
  private_c_args += ['-DDISABLE_CPU_JITTER_ENTROPY']
endif

if fips_opt.allowed()
  marker_src = files('fipsmodule/fips_shared_library_marker.c')

  libcrypto_body = static_library(
    'libcrypto-awslc-body',
    src,
    generated,
    c_args: [private_c_args, public_c_args],
    include_directories: inc,
    install: false,
    pic: true,
    gnu_symbol_visibility: 'hidden',
    override_options: ['debug=false'],
  )

  fipsmodule = static_library(
    'fipsmodule',
    src_fipsmodule,
    c_args: [private_c_args, public_c_args, fipsmodule_c_args],
    include_directories: inc,
    install: false,
    # Code must be PIC, any relocations can cause the executable to mutate
    # when loaded, invalidating the FIPS hash.
    pic: true,
    gnu_symbol_visibility: 'hidden',
    # Very load bearing, if debug info is included into the final binary
    # it will become unusable if ever stripped.
    override_options: ['debug=false'],
  )

  bcm_library = static_library(
    'bcm_library',
    bcm_src,
    c_args: [private_c_args, public_c_args, fipsmodule_c_args],
    link_args: ['-T', meson.current_source_dir() / ldscript],
    include_directories: [inc, s2n_bignum_inc],
    install: false,
    pic: true,
    gnu_symbol_visibility: 'hidden',
    override_options: ['debug=false'],
  )

  ld = find_program(cc.get_linker_id())

  fips_bcm_module = custom_target(
    'fips_bcm_module',
    output: 'fips_bcm_module.o',
    command: [
      ld,
      '-r',
      '-T',
      meson.current_source_dir() / ldscript,
      '-o',
      '@OUTPUT@',
      '--whole-archive',
      bcm_library.full_path(),
    ],
    depends: [bcm_library],
  )

  libcrypto_awslc_prelink = shared_library(
    'crypto-awslc-prelink',
    c_args: private_c_args,
    link_whole: [
      libcrypto_body,
      fipsmodule,
    ],
    objects: [fips_bcm_module],
    dependencies: [jitterentropy],
    include_directories: inc,
    gnu_symbol_visibility: 'hidden',
    override_options: ['debug=false'],
    # Due to FIPS hash injection we need to mutate this library. If we
    # don't provide an soname with the final name then the linker will
    # link to the pre-hash injected version of library, which will cause
    # the FIPS POST checks to fail.
    link_args: ['-Wl,-soname,libcrypto-awslc.so'],
  )

  libcrypto_awslc = custom_target(
    'libcrypto-awslc',
    output: 'libcrypto-awslc.so',
    command: [
      custom_target_sh,
      # WORKDIR
      meson.project_source_root(),
      # INPUT
      libcrypto_awslc_prelink.full_path(),
      # OUTPUT
      meson.current_build_dir() / 'libcrypto-awslc.so',
      # CMD
      inject_hash_src[0].full_path(),
    ],
    depends: libcrypto_awslc_prelink,
    install: true,
    install_dir: get_option('libdir'),
  )
else
  # In non-FIPS mode aws-lc still links against the bcm and fipsmodule
  # libraries for functionality.
  fipsmodule = static_library(
    'fipsmodule',
    src_fipsmodule,
    c_args: [private_c_args, public_c_args, fipsmodule_c_args],
    include_directories: inc,
    install: false,
    gnu_symbol_visibility: 'hidden',
  )

  libbcm = static_library(
    'bcm',
    bcm_src,
    c_args: [private_c_args, public_c_args, fipsmodule_c_args],
    include_directories: [inc, s2n_bignum_inc],
    install: false,
    gnu_symbol_visibility: 'hidden',
  )

  libcrypto_awslc = library(
    'libcrypto-awslc',
    src,
    generated,
    c_args: [private_c_args, public_c_args],
    link_whole: [fipsmodule, libbcm],
    dependencies: [jitterentropy],
    include_directories: inc,
    install: true,
    gnu_symbol_visibility: 'hidden',
  )
endif

libcrypto_dep = declare_dependency(
  link_with: libcrypto_awslc,
  include_directories: inc,
  compile_args: public_c_args,
)

meson.override_dependency('libcrypto-awslc', libcrypto_dep)
