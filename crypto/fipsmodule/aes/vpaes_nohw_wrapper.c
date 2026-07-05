// Copyright 2024 Brian Smith / XP Compatibility wrapper.
//
// This wrapper provides the vpaes_* symbols that ring's Rust code expects on
// x86 targets, but backed by the generic C-only AES implementation so that
// targets without SSE2 (e.g. Windows XP on pre-SSE2 CPUs) can still link.
//
// This file is only compiled for Windows x86 in this fork.

#include <ring-core/aes.h>

// aes_nohw_* are declared in aes.h when building the ring C library; they are
// part of the ring C library's public ABI for this fork.
extern int aes_nohw_set_encrypt_key(const uint8_t *key, unsigned bits,
                                    AES_KEY *out);
extern void aes_nohw_encrypt(const uint8_t *in, uint8_t *out,
                             const AES_KEY *key);

int vpaes_set_encrypt_key(const uint8_t *user_key, unsigned bits,
                          AES_KEY *key) {
    return aes_nohw_set_encrypt_key(user_key, bits, key);
}

void vpaes_encrypt(const uint8_t *in, uint8_t *out, const AES_KEY *key) {
    aes_nohw_encrypt(in, out, key);
}
