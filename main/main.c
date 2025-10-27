/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "main.h"

#if (CONFIG_MLKEM == 1)
  #define MLK_CONFIG_API_PARAMETER_SET 512
  #define MLK_CONFIG_API_NAMESPACE_PREFIX mlkem
  #include "mlkem_native/mlkem/mlkem_native.h"
  #include "test_only_rng/notrandombytes.h"
#elif (CONFIG_MLKEM != 0)
  #include "kem.h"
  #include "randombytes.h"
#endif

void app_main(void)
{
#if (CONFIG_MLKEM == 0)
  hello_world();
#else
  unsigned char pk[CRYPTO_PUBLICKEYBYTES];
  unsigned char sk[CRYPTO_SECRETKEYBYTES];

  esp_fill_random(pk, sizeof(pk));
  esp_fill_random(sk, sizeof(sk));

  crypto_kem_keypair(pk, sk);
#endif
    return;
}
