#include "sew.h"

/**
 * @brief File contains implementation of C SEW functionality with relation to generating keys
 * @author Salih MSA
 */


extern unsigned int OPENSSL_ia32cap_P[] ;
extern void OPENSSL_cpuid_setup() ;


int sew_key_generation(unsigned char const *key, const enum SEW_ENCRYPTION_ALGORITHM enc_alg)
{
	OPENSSL_add_all_algorithms_noconf(); /* This is called by OPENSSL_load_builtin_engines() */

	int status = OPENSSL_ia32cap_P[1] & (1 << (62 - 32));
	if (!status) {
		return 1;
	}

	ENGINE_load_rdrand(); /* Load the engine of interest */
	ENGINE *eng1 = ENGINE_by_id("rdrand"); /* used for ENGINE_finish */
	if (!eng1) {
		return 1;
	}

	ENGINE *eng2 = eng1; /* Make the assignment for proper cleanup (ENGINE_by_id needs one cleanup, ENGINE_init needs a second distinct cleanup) */ /* used for ENGINE_free */
	status = ENGINE_init(eng2);
	if (!status) {
		return 1;
	}

	status = ENGINE_set_default(eng2, ENGINE_METHOD_RAND); /* Set the default RAND_method */
	if (!status) {
		return 1;
	}

	status = RAND_bytes(key, (int)enc_alg);
	if (!status) {
		return 1;
	}

	if (eng1) {
		ENGINE_free(eng1);
	}
	if (eng2) {
		ENGINE_finish(eng2);
	}
	ENGINE_cleanup();

	return 0;
}
