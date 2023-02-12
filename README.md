# SEW
## README

SEW (Salih's Encryption Wrapper) is a wrapper around [openssl](https://www.openssl.org/)'s encryption functionality, allowing for simpler encryption for basic communications

This includes:
* Key generation for named encryption algorithms
* Symmetric key exchange using different versions of the Diffie Hellman algorithm (over Linux raw `netdev` socket or equivalent)
* Wrappers to encrypt / decrypt using said encryption algorithms

---

There are three files which can be included, which are in the `include/` directory:
* sew.h - C functionality
* sew.hh - C++ functionality
* sew.rs - Rust functionality

All three will need compile-time linkage - the object files can be found after compilation in the `lib/` directory

---

See LICENSE.md for terms of usage.
