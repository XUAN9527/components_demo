#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
//#include "drv_usart.h"
//#include "drv_adc.h"
//#include "drv_gpio.h"
//#include "drv_ble.h"
#include "shell_port.h"
#include "log.h"
#include "nvs_flash.h"
#include <inttypes.h>
#include "drv_ble.h"

static const char *TAG = "sample test";

void app_main(void)
{
	esp_err_t ret;

    // Initialize NVS.
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

	esp_log_level_set(TAG, ESP_LOG_INFO);
	ESP_LOGI(TAG,"this is a test program");
	// mcu_usart1_init();
    
	userShellInit();
	drv_ble_init();

	logInfo("log info!");
	logDebug("log debug!");
	logWarning("log warning!");
	logError("log error!");
	while(1)
	{
		logDebug("log loop!");
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}