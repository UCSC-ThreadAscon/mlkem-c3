set(kyber_dirs "kyber/ref"
               "kyber/ref/nistkat")

idf_component_register(SRCS "${kyber_dirs}"
                    INCLUDE_DIRS "${kyber_dirs}")
