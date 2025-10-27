/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "main.h"

#if MLKEM_NATIVE
  #define MLK_CONFIG_API_PARAMETER_SET 512
  #define MLK_CONFIG_API_NAMESPACE_PREFIX mlkem
  #include "mlkem_native.h"

  #define CHECK(x)                                              \
    do                                                          \
    {                                                           \
      int rc;                                                   \
      rc = (x);                                                 \
      if (!rc)                                                  \
      {                                                         \
        fprintf(stderr, "ERROR (%s,%d)\n", __FILE__, __LINE__); \
        return;                                                 \
      }                                                         \
    } while (0)
#elif (MLKEM_C_EMBEDDED || CRYSTALS_KYBER)
  #include "kem.h"
#endif

void app_main(void)
{

#if (CONFIG_MLKEM == 0)
  hello_world();
#elif MLKEM_NATIVE
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];

  esp_fill_random(pk, sizeof(pk));
  esp_fill_random(sk, sizeof(sk));

  CHECK(crypto_kem_keypair(pk, sk) == 0);
#elif (MLKEM_C_EMBEDDED || CRYSTALS_KYBER)
  unsigned char pk[CRYPTO_PUBLICKEYBYTES];
  unsigned char sk[CRYPTO_SECRETKEYBYTES];

  esp_fill_random(pk, sizeof(pk));
  esp_fill_random(sk, sizeof(sk));

  crypto_kem_keypair(pk, sk);
#endif
    return;
}
