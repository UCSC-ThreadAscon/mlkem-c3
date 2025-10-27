idf_component_register(SRCS "hello_world.c" "main.c"
                       PRIV_REQUIRES spi_flash "kyber"
                       INCLUDE_DIRS "include")
