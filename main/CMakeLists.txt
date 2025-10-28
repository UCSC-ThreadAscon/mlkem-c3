macro(start_delimiter)

    message("---------------------------------------------------------------------------------")
    message("")

endmacro(start_delimiter)

macro(end_delimiter)

    message("")
    message("---------------------------------------------------------------------------------")

endmacro(end_delimiter)

# idf_component_register(SRCS "hello_world.c" "main.c"
#                       PRIV_REQUIRES spi_flash mlkem-native
#                       INCLUDE_DIRS "include")

idf_component_register(SRCS "hello_world.c" "main.c"
                      PRIV_REQUIRES spi_flash mlkem_embedded
                      INCLUDE_DIRS "include")

# idf_component_register(SRCS "hello_world.c" "main.c"
#                       PRIV_REQUIRES spi_flash kyber
#                       INCLUDE_DIRS "include")

# idf_component_register(SRCS "hello_world.c" "main.c"
#                       PRIV_REQUIRES spi_flash
#                       INCLUDE_DIRS "include")