if(CONFIG_MLKEM EQUAL 2)

  idf_component_register(SRCS "hello_world.c" "main.c"
                        PRIV_REQUIRES spi_flash "mlkem_embedded"
                        INCLUDE_DIRS "include")

elseif(CONFIG_MLKEM EQUAL 4)

  idf_component_register(SRCS "hello_world.c" "main.c"
                        PRIV_REQUIRES spi_flash "kyber"
                        INCLUDE_DIRS "include")

else()

  idf_component_register(SRCS "hello_world.c" "main.c"
                        PRIV_REQUIRES spi_flash
                        INCLUDE_DIRS "include")

endif()
