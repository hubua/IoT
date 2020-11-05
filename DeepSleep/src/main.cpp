#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "esp_log.h"
#include <iostream>

//#define DO_DEEP_SLEEP

static const char *TAG = "example";

/* Variable holding number of times ESP32 restarted since first boot.
 * It is placed into RTC memory using RTC_DATA_ATTR and
 * maintains its value when ESP32 wakes from deep sleep.
 */
RTC_DATA_ATTR static int boot_count = 0;

extern "C"
{
    void app_main();
}

//FIXME ms not really millisecond
void delay(uint32_t ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

void app_main()
{
#ifdef DO_DEEP_SLEEP
    ++boot_count;
    ESP_LOGI(TAG, "Boot count: %d!", boot_count);
#endif

    std::string s = "abcd";

    //TODO Why loop does not stop on delay, but prints several items first

    for (int i = 0;; i = (i + 1) % 10)
    {
        //printf("%d_%s ", i, s.c_str());
        std::cout << i;
        vPortYield();
        delay(1000);
    }
    
#ifdef DO_DEEP_SLEEP
    const int deep_sleep_sec = 10;
    ESP_LOGI(TAG, "Entering deep sleep for %d seconds!", deep_sleep_sec);
    esp_deep_sleep(1000000LL * deep_sleep_sec);
#endif
}