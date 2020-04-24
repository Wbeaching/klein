#include <stdio.h>

#include <simple-klein.h>

static void print_hex_block(uint8_t *data, uint32_t length);

int main(int argc, char *argv[])
{
    printf("KLEIN cipher demo application\n");

    sklein_t crypter = sklein_create(KLEIN_MODE_64);
    if (crypter == NULL)
    {
        printf("ERROR: Failed to create KLEIN-64\n");
        return 1;
    }
    printf("Testing KLEIN-64 (PLAIN / KEY / CIPHER / DECRYPT)\n");

    uint8_t data64[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uint8_t key64[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};
    print_hex_block(data64, 8);
    print_hex_block(key64, sizeof(key64));
    int result = 0;

    result = sklein_set_key(crypter, key64, sizeof(key64));
    if (result != KLEIN_RESULT_OK)
    {
        printf("ERROR: Failed to set key: %d\n", result);
        return 1;
    }

    result = sklein_crypt_block(crypter, data64);
    if (result != KLEIN_RESULT_OK)
    {
        printf("ERROR: Failed to crypt\n");
        return 1;
    }
    print_hex_block(data64, 8);
    printf("(59 23 56 C4 99 71 76 C8)\n");

    result = sklein_decrypt_block(crypter, data64);
    if (result != KLEIN_RESULT_OK)
    {
        printf("ERROR: Failed to decrypt\n");
        return 1;
    }
    print_hex_block(data64, 8);
    printf("(FF FF FF FF FF FF FF FF)\n");
    sklein_destroy(crypter);
    crypter = NULL;
    return 0;
}

static void print_hex_block(uint8_t *data, uint32_t length)
{
    if (!data || length == 0)
    {
        return;
    }
    for (uint32_t i = 0; i < length; ++i)
    {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
