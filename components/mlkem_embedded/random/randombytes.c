// SPDX-License-Identifier: Apache-2.0
#include "randombytes.h"

#include <esp_random.h>
int randombytes(uint8_t *obuf, size_t len) {
    // NOTE:
    // After enabling the internal entropy source (SAR ADC), random numbers are generated based on the thermal noise in the system and the asynchronous clock mismatch.
    // For more detail please refer to https://docs.espressif.com/projects/esp-idf/en/v5.3/esp32c3/api-reference/system/random.html and the technical reference manual
    esp_fill_random(obuf, len);

    return 0;
}
