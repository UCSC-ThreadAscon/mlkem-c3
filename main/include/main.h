#pragma once

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_random.h"

#define MLKEM_NATIVE (CONFIG_MLKEM == 1)
#define MLKEM_C_EMBEDDED (CONFIG_MLKEM == 2)
#define CRYSTALS_KYBER (CONFIG_MLKEM == 4)

void hello_world(void);