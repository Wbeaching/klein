#ifndef __SIMPLE_KLEIN_H__
#define __SIMPLE_KLEIN_H__

#include <stdint.h>

#define sklein_crypt_block(x,y) sklein_encrypt_block(x,y); \
    _Pragma("message \"sklein_crypt_block() function is deprecated and will be removed - use sklein_encrypt_block()\"")

typedef struct simple_klein *sklein_t;

/** Enum type with supported KLEIN modes
 *
 * As defined in KLEIN specification all modes uses same block length
 * but different encryption (master) key length
 */
enum klein_mode
{
    KLEIN_MODE_64 = 0, ///< KLEIN-64 with 64-bit master key and 12 rounds
    KLEIN_MODE_80,     ///< KLEIN-80 with 80-bit master key and 16 rounds
    KLEIN_MODE_96,     ///< KLEIN-96 with 96-bit master key and 20 rounds
};

/** klein_result is an enum type defining possible SKLEIN API errors
 */
enum klein_result
{
    KLEIN_RESULT_OK = 0,         ///< No error, function finished with success
    KLEIN_RESULT_FAIL,           ///< General failure
    KLEIN_RESULT_INVALID_PARAM,  ///< Function failure due to invalid param value
    KLEIN_RESULT_INVALID_LENGTH, ///< Function failre due to invali param (ex. key) length
};

/** sklein_create() creates instance of KLEIN encryptor/decryptor
 *
 * @param km KLEIN mode as defined in #klein_mode enum
 *
 * @return NULL or ready to use klein object
 */
sklein_t sklein_create(int km);

/** sklein_set_key() set master key to KLEIN crypting object
 *
 * @param crypter KLEIN crypting object created by #sklein_create()
 * @param mkey pointer to array with master key
 * @param k_length length of provided key, has to match key length for selected KLEIN mode
 *
 * @return #KLEIN_RESULT_OK on success
 * @return #KLEIN_RESULT_INVALID_PARAM or #KLEIN_RESULT_INVALID_LENGTH on error
 */
int sklein_set_key(sklein_t crypter, const uint8_t *mkey, uint8_t k_length);

/** sklein_encrypt_block() implements KLEIN encryption
 *
 * @param crypter KLEIN crypting object created by #sklein_create()
 * @param block pointer to 8 bytes of data to be encrypted, encryption result will be stored in the same buffer
 *
 * @return #KLEIN_RESULT_OK on success
 * @return #KLEIN_RESULT_INVALID_PARAM if invalid parameter given
 */
int sklein_encrypt_block(sklein_t crypter, uint8_t *block);

/** sklein_decrypt_block() implements KLEIN decryption
 *
 * @param crypter KLEIN crypting object created by #sklein_create()
 * @param block pointer to 8 bytes of data to be decrypted, decryption result will be stored in the same buffer
 *
 * @return #KLEIN_RESULT_OK on success
 * @return #KLEIN_RESULT_INVALID_PARAM if invalid parameter given
 */
int sklein_decrypt_block(sklein_t crypter, uint8_t *block);

/** sklein_destroy() releases resources allocated by #sklein_create()
 *
 * @param crypter KLEIN crypting object created by #sklein_create()
 */
void sklein_destroy(sklein_t crypter);

/** klein_mode_to_string() converts #klein_mode enum to strin representation
 *
 * @param mode KLEIN mode enum value
 *
 * @return string representing provided enum value
 */
const char *klein_mode_to_string(int mode);

#endif
