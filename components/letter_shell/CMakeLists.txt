idf_component_register(
    SRCS "shell.c"
         "shell_ext.c"
         "shell_port.c"
         "log.c"
         "shell_companion.c"
         "shell_cmd_list.c"
         "shell_ext.c"
    INCLUDE_DIRS "include"
    LDFRAGMENTS "shell.lf"
    # PRIV_REQUIRES led
    REQUIRES esp_driver_uart
)