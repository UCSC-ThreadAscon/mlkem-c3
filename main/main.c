/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "main.h"

#include "kem.h"
#include "randombytes.h"

void app_main(void)
{
#if (CONFIG_MLKEM == 0)
  hello_world();
#elif (CONFIG_MLKEM == 2)
  unsigned char pk[CRYPTO_PUBLICKEYBYTES];
  unsigned char sk[CRYPTO_SECRETKEYBYTES];

  esp_fill_random(pk, sizeof(pk));
  esp_fill_random(sk, sizeof(sk));

  crypto_kem_keypair(pk, sk);
#elif (CONFIG_MLKEM == 4)
  unsigned char pk[CRYPTO_PUBLICKEYBYTES];
  unsigned char sk[CRYPTO_SECRETKEYBYTES];

  esp_fill_random(pk, sizeof(pk));
  esp_fill_random(sk, sizeof(sk));

  crypto_kem_keypair(pk, sk);
#endif
    return;
}
