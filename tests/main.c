#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <sklein.h>

#include "test-vectors.h"

void print_buffer(const char *name, const uint8_t *buffer, size_t buf_len);

bool buffers_equals(const uint8_t *buffer1, const uint8_t *buffer2, size_t len);

int main(int argc, char *argv[])
{
    int tests_passed = 0;
    int tests_failed = 0;
    int tests_count = klein_test_count;
    uint8_t temp_buffer[8]; // buffer for encrypted/decrypted KLEIN block

    for (int i = 0; i < tests_count; ++i)
    {
        printf("\nTest %d for %s\n", i + 1, klein_mode_to_string(klein_test_data[i]->mode));
        sklein_t crypter = sklein_create(klein_test_data[i]->mode);
        if (crypter == NULL)
        {
            tests_failed++;
            printf("Failed to create crypting context for selected mode\n");
            continue;
        }
        int result = sklein_set_key(crypter, klein_test_data[i]->key, klein_test_data[i]->key_len);
        if (result != KLEIN_RESULT_OK)
        {
            tests_failed++;
            printf("Failed to set key with length %ld\n", klein_test_data[i]->key_len);
            continue;
        }
        print_buffer("message", klein_test_data[i]->data, klein_test_data[i]->data_len);
        print_buffer("key", klein_test_data[i]->key, klein_test_data[i]->key_len);
        memcpy(temp_buffer, klein_test_data[i]->data, klein_test_data[i]->data_len);
        result = sklein_encrypt_block(crypter, temp_buffer);
        if (result != KLEIN_RESULT_OK)
        {
            tests_failed++;
            printf("Encryption process failed\n");
            continue;
        }
        print_buffer("cipher", temp_buffer, klein_test_data[i]->data_len);
        print_buffer("expected", klein_test_data[i]->result, klein_test_data[i]->data_len);
        if (!buffers_equals(klein_test_data[i]->result, temp_buffer, klein_test_data[i]->data_len))
        {
            tests_failed++;
            printf("Incorrect encryption result\n");
            continue;
        }

        result = sklein_decrypt_block(crypter, temp_buffer);
        if (result != KLEIN_RESULT_OK)
        {
            tests_failed++;
            printf("Decryption process failed\n");
            continue;
        }
        print_buffer("decrypted", temp_buffer, klein_test_data[i]->data_len);
        print_buffer("expected", klein_test_data[i]->data, klein_test_data[i]->data_len);
        if (!buffers_equals(klein_test_data[i]->data, temp_buffer, klein_test_data[i]->data_len))
        {
            tests_failed++;
            printf("Incorrect decryption result\n");
            continue;
        }
        // no error till now
        printf("- TEST PASSED -\n");
        tests_passed++;
    }

    printf("\nTest summary:\nPassed: %d\nFailed: %d\nAll:%d\n",
           tests_passed, tests_failed, tests_count);

    if (tests_passed != tests_count)
    {
        return 1;
    }
    return 0;
}

void print_buffer(const char *name, const uint8_t *buffer, size_t buf_len)
{
    if (!buffer || buf_len < 1)
    {
        printf("(invalid buffer data)");
        return;
    }
    printf("[%s] :", (name != NULL) ? name : "(unnamed)");
    for (size_t i = 0; i < buf_len; ++i)
    {
        printf("%02X", buffer[i]);
    }
    printf("\n");
}

bool buffers_equals(const uint8_t *buffer1, const uint8_t *buffer2, size_t len)
{
    if (!buffer1 || !buffer2 || len < 1)
    {
        return false;
    }
    if (buffer1 == buffer2)
    {
        // same buffer so for sure is exactly te same ;-)
        return true;
    }
    for (size_t i = 0; i < len; ++i)
    {
        if (buffer1[i] != buffer2[i])
        {
            return false;
        }
    }
    return true;
}
