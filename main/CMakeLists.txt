idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS ""
                    PRIV_REQUIRES letter_shell drv_ble
                    REQUIRES nvs_flash
                    )
