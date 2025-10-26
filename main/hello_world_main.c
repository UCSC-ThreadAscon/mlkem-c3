/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#include "kem.h"
#include "randombytes.h"

#define NTESTS 1

void hello_world(void)
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
    return;
}

const uint8_t canary[8] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF
};

/* allocate a bit more for all keys and messages and
 * make sure it is not touched by the implementations.
 */
static void write_canary(uint8_t *d) {
    for (size_t i = 0; i < 8; i++) {
        d[i] = canary[i];
    }
}

static int check_canary(const uint8_t *d) {
    for (size_t i = 0; i < 8; i++) {
        if (d[i] != canary[i]) {
            return -1;
        }
    }
    return 0;
}

static int test_keys(void) {
    unsigned char key_a[CRYPTO_BYTES + 16], key_b[CRYPTO_BYTES + 16];
    unsigned char pk[CRYPTO_PUBLICKEYBYTES + 16];
    unsigned char sendb[CRYPTO_CIPHERTEXTBYTES + 16];
    unsigned char sk_a[CRYPTO_SECRETKEYBYTES + 16];

    write_canary(key_a);
    write_canary(key_a + sizeof(key_a) - 8);
    write_canary(key_b);
    write_canary(key_b + sizeof(key_b) - 8);
    write_canary(pk);
    write_canary(pk + sizeof(pk) - 8);
    write_canary(sendb);
    write_canary(sendb + sizeof(sendb) - 8);
    write_canary(sk_a);
    write_canary(sk_a + sizeof(sk_a) - 8);

    int i;

    for (i = 0; i < NTESTS; i++) {
        //Alice generates a public key
        crypto_kem_keypair(pk + 8, sk_a + 8);
        printf("DONE key pair generation!");

        //Bob derives a secret key and creates a response
        crypto_kem_enc(sendb + 8, key_b + 8, pk + 8);
        printf("DONE encapsulation!");

        //Alice uses Bobs response to get her secret key
        crypto_kem_dec(key_a + 8, sendb + 8, sk_a + 8);
        printf("DONE decapsulation!");

        if (memcmp(key_a + 8, key_b + 8, CRYPTO_BYTES)) {
            printf("ERROR KEYS\n");
        } else if (check_canary(key_a) || check_canary(key_a + sizeof(key_a) - 8) ||
                   check_canary(key_b) || check_canary(key_b + sizeof(key_b) - 8) ||
                   check_canary(pk) || check_canary(pk + sizeof(pk) - 8) ||
                   check_canary(sendb) || check_canary(sendb + sizeof(sendb) - 8) ||
                   check_canary(sk_a) || check_canary(sk_a + sizeof(sk_a) - 8)) {
            printf("ERROR canary overwritten\n");
        } else {
            printf("OK KEYS\n");
        }
        printf("+");
    }
    return 0;
}

static int test_invalid_sk_a(void) {
    unsigned char sk_a[CRYPTO_SECRETKEYBYTES];
    unsigned char key_a[CRYPTO_BYTES], key_b[CRYPTO_BYTES];
    unsigned char pk[CRYPTO_PUBLICKEYBYTES];
    unsigned char sendb[CRYPTO_CIPHERTEXTBYTES];
    int i;

    for (i = 0; i < NTESTS; i++) {
        //Alice generates a public key
        crypto_kem_keypair(pk, sk_a);

        //Bob derives a secret key and creates a response
        crypto_kem_enc(sendb, key_b, pk);

        //Replace secret key with random values
        randombytes(sk_a, CRYPTO_SECRETKEYBYTES);

        //Alice uses Bobs response to get her secre key
        crypto_kem_dec(key_a, sendb, sk_a);

        if (!memcmp(key_a, key_b, CRYPTO_BYTES)) {
            printf("ERROR invalid sk_a\n");
        } else {
            printf("OK invalid sk_a\n");
        }
        printf("+");
    }

    return 0;
}

static int test_invalid_ciphertext(void) {
    unsigned char sk_a[CRYPTO_SECRETKEYBYTES];
    unsigned char key_a[CRYPTO_BYTES], key_b[CRYPTO_BYTES];
    unsigned char pk[CRYPTO_PUBLICKEYBYTES];
    unsigned char sendb[CRYPTO_CIPHERTEXTBYTES];
    int i;
    size_t pos;

    for (i = 0; i < NTESTS; i++) {
        randombytes((unsigned char *)&pos, sizeof(size_t));

        //Alice generates a public key
        crypto_kem_keypair(pk, sk_a);

        //Bob derives a secret key and creates a response
        crypto_kem_enc(sendb, key_b, pk);

        // Change ciphertext to random value
        randombytes(sendb, sizeof(sendb));

        //Alice uses Bobs response to get her secret key
        crypto_kem_dec(key_a, sendb, sk_a);

        if (!memcmp(key_a, key_b, CRYPTO_BYTES)) {
            printf("ERROR invalid ciphertext\n");
        } else {
            printf("OK invalid ciphertext\n");
        }
        printf("+");
    }

    return 0;
}

void app_main(void)
{
    test_keys();
    test_invalid_sk_a();
    test_invalid_ciphertext();
    return;
}
