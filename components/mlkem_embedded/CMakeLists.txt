set(mlkem_embedded_dirs
    "mlkem-c-embedded/fips202"
    "mlkem-c-embedded/mlkem")


if(CONFIG_IDF_TARGET STREQUAL "esp32c3")

  list(APPEND mlkem_embedded_dirs "mlkem-c-embedded/hal")

else()

  list(APPEND mlkem_embedded_dirs "random")

endif()

idf_component_register(SRC_DIRS "${mlkem_embedded_dirs}"
                       INCLUDE_DIRS "${mlkem_embedded_dirs}"
                       PRIV_REQUIRES "esp_hal_wdt" "bootloader_support" "hal")
