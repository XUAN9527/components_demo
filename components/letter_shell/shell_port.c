/**
 * @file shell_port.c
 * @author Letter (NevermindZZT@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-02-22
 * 
 * @copyright (c) 2019 Letter
 * 
 */

#include "shell.h"
#include "freertos/FreeRTOS.h"
#include "driver/uart.h"
#include "log.h"

#define     LETTER_SHELL_UART      UART_NUM_1

Shell shell;
Log uartLog;
char shellBuffer[512];

void uartLogWrite(char *buffer, short len)
{
    if (uartLog.shell)
    {
        shellWriteEndLine(uartLog.shell, buffer, len);
    }
}

/**
 * @brief 用户shell写
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return unsigned short 写入实际长度
 */
signed short userShellWrite(char *data, unsigned short len)
{
    return uart_write_bytes(LETTER_SHELL_UART, data, len);
}


/**
 * @brief 用户shell读
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return unsigned short 读取实际长度
 */
signed short userShellRead(char *data, unsigned short len)
{
    return uart_read_bytes(LETTER_SHELL_UART, (uint8_t *)data, len, portMAX_DELAY);
}


/**
 * @brief 用户shell初始化
 * 
 */
void userShellInit(void)
{
    uart_config_t uartConfig = {
        .baud_rate = 921600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(LETTER_SHELL_UART, &uartConfig);
    uart_driver_install(LETTER_SHELL_UART, 256 * 2, 0, 0, NULL, 0);
    uart_set_pin(LETTER_SHELL_UART, 4, 5, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    shell.write = userShellWrite;
    shell.read = userShellRead;
    shellInit(&shell, shellBuffer, 512);

    uartLog.write = uartLogWrite;
    uartLog.active = true;
    uartLog.level = LOG_DEBUG;
    logRegister(&uartLog, &shell);

    xTaskCreate(shellTask, "shell", 2048, &shell, tskIDLE_PRIORITY, NULL);
}

static void reboot(void)
{
    esp_restart();
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC)|SHELL_CMD_DISABLE_RETURN, reboot, reboot,system software reset);

