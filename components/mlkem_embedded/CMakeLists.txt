set(mlkem_embedded_dirs
    "mlkem-c-embedded/fips202"
    "random"
    "mlkem-c-embedded/mlkem")

idf_component_register(SRC_DIRS "${mlkem_embedded_dirs}"
                       INCLUDE_DIRS "${mlkem_embedded_dirs}"
                       PRIV_REQUIRES "esp_hal_wdt")
