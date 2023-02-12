#ifndef SEW_HH
#define SEW_HH
#pragma once

#include "sew.h"

/**
 * @brief File contains C++ interface for SEW functionality
 * @author Salih MSA
 */


namespace sew {

	class KeyExchange {
		private:
			SEWEncryptionInformation enc_info ;

		public:
			KeyExchange(const enum SEW_ENCRYPTION_ALGORITHM enc_alg) noexcept ;

			// the key exchange can happen a bunch of times. calling run will just create new keys, etc.
			void run(const int socket) noexcept ;

			~KeyExchange() noexcept ;
	} ;

	// encrypt, decrypt functionality
	// should support both STL (string, vec, array) & native C string

}


#endif // SEW_HH
