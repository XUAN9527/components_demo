idf_component_register(SRCS "drv_ble.c"
                    INCLUDE_DIRS "include"
                    REQUIRES bt
                    REQUIRES nvs_flash)
