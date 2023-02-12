#ifndef SEW_H
#define SEW_H
#pragma once

/**
 * @brief File contains C interface for SEW functionality
 * @author Salih MSA
 */


/**
 * @brief SEW_ENCRYPTION_ALGORITHM (enum) - enum specifies to functionality which underlying encryption algorithm is to be used
 * This allows functions to be abstract, such that `encrypt` just encrypts the data
 * It also is encoded to be equivalent to the key size / IV needed
 */
enum SEW_ENCRYPTION_ALGORITHM {
	AES_256 = 32,
};


/**
 * @brief SEW_DIFFIE_HELLMAN_ALGORITHM (enum) - enum specifies which Diffie-Hellman key exchange algorithm is to be used
 */
enum SEW_DIFFIE_HELLMAN_ALGORITHM {
	DIFFIE_HELLMAN = 0,
};


/**
 * @brief sew_key_generation - generates key using cryptographically secure number generator
 *
 * @param[in] const enum SEW_ENCRYPTION_ALGORITHM enc_alg - encryption algorithm key will be used for
 *
 * @param[out] unsigned char const *key - pointer to array of bytes
 * This should be declared to have an adaquete size based on the protocol to be used
 * Use the appropriate enum SEW_ENCRYPTION_ALGORITHM which specifies the byte length for (e.g. unsigned char key[AES_256], unsigned char *key = malloc(AES_256))
 *
 * @return int - 0 upon success, 1 if key generation failed
 */
int sew_key_generation(unsigned char const* key, const enum SEW_ENCRYPTION_ALGORITHM enc_alg);


/**
 * @brief sew_key_exchange - runs key generation & exchange protocol
 * This makes use of the Diffie-Hellman key exchange operation
 * This will make use of both openssl functionality and syscalls read, write to transfer bytes to the given socket
 *
 * @param[in] const int socket - Linux file handle to netdev device to exchange messages with
 *
 * @param[in] const enum SEW_ENCRYPTION_ALGORITHM enc_alg - encryption algorithm key will be used for
 *
 * @param[in] const enum SEW_DIFFIE_HELLMAN_ALGORITHM exch_alg - Diffie-Hellman algorithm to exchange keys
 *
 * @param[out] unsigned char const *key - pointer to array of bytes
 * This should be declared to have an adaquete size based on the protocol to be used
 * Use the appropriate enum SEW_ENCRYPTION_ALGORITHM which specifies the byte length for (e.g. unsigned char key[AES_256], unsigned char *key = malloc(AES_256))
 *
 * @return int - 0 upon success, 1 if fd is invalid (not netdev or invalid fd generally), 2 if initial key generation failed, 3 if the exchange failed
 */
int sew_key_exchange(const int socket, const enum SEW_ENCRYPTION_ALGORITHM enc_alg, const enum SEW_DIFFIE_HELLMAN_ALGORITHM exch_alg, unsigned char const *key);


/**
 * @brief sew_encrypt - functionality encrypts string of plain text unsigned characters
 *
 * @param[in] const unsigned char const *plain_txt - immutable plain text unsigned characters
 *
 * @param[in] const size_t plain_txt_len - length of plain text buffer contents to encrypt
 *
 * @param[out] unsigned char const *cipher_txt - buffer to dump cipher text
 *
 * @param[in] const size_t cipher_txt_len - maximum length of cipher text buffer
 *
 * @param[in] const unsigned char const *key - encryption key
 * Note: this should match in size to the value behind enc_alg
 *
 * @param[in] const unsigned char const *iv - initialisation vector
 * Note: this should match in size to the value behind enc_alg
 *
 * @param[in] const enum SEW_ENCRYPTION_ALGORITHM enc_alg - encryption algorithm to be used to use key & iv properly
 *
 * @return ssize_t - -1 if encryption key is invalid, -2 if there was an issue with read or write buffer, positive number indicates bytes written to buffer `cipher_txt`
 */
ssize_t sew_encrypt(const unsigned char const *plain_txt, const size_t plain_txt_len, unsigned char const *cipher_txt, const size_t cipher_txt_len, const unsigned char const *key, const unsigned char const *iv, const enum SEW_ENCRYPTION_ALGORITHM enc_alg);


/**
 * @brief sew_decrypt - functionality decrypts string of cipher text unsigned characters
 *
 * @param[in] const unsigned char const *cipher_txt - immutable plain text unsigned characters
 *
 * @param[in] const size_t cipher_txt_len - length of plain text buffer contents to encrypt
 *
 * @param[out] unsigned char const *plain_txt - buffer to dump cipher text
 *
 * @param[in] const size_t plain_txt_len - maximum length of cipher text buffer
 *
 * @param[in] const unsigned char const *key - encryption key
 * Note: this should match in size to the value behind enc_alg
 *
 * @param[in] const unsigned char const *iv - initialisation vector
 * Note: this should match in size to the value behind enc_alg
 *
 * @param[in] const enum SEW_ENCRYPTION_ALGORITHM enc_alg - encryption algorithm to be used to use key & iv properly
 *
 * @return ssize_t - -1 if key is invalid, -2 if there was an issue with read or write buffer, positive number indicates bytes written to buffer `cipher_txt`
 */
ssize_t sew_decrypt(const unsigned char const *cipher_txt, const size_t cipher_txt_len, unsigned char const *plain_txt, const size_t plain_txt_len, const unsigned char const *key, const unsigned char const *iv, const enum SEW_ENCRYPTION_ALGORITHM enc_alg);


#endif /* SEW_H */
