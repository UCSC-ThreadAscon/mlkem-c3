set(mlkem_embedded_dirs
    "mlkem-c-embedded/fips202"
    "mlkem-c-embedded/mlkem")

idf_component_register(SRC_DIRS "${mlkem_embedded_dirs}"
                       SRCS "mlkem-c-embedded/hal/notrandombytes.c"
                       INCLUDE_DIRS "${mlkem_embedded_dirs}"
                                    "mlkem-c-embedded/hal"
                       PRIV_REQUIRES "esp_hal_wdt")
