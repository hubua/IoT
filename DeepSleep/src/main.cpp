#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

//#include "esp_log.h"
//#include <iostream>

//#define DO_DEEP_SLEEP

#define BLINK_GPIO GPIO_NUM_2

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

    //std::string s = "abcd";

    //TODO Why loop does not stop on delay, but prints several items first

    int n = 0;

    /*
    UNCLEAR
    set monitor speed from sdkconfig
    filters and flags in ini
    */

    //int k = 1 / n;

    //printf("%d\n", k);

    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    for (int i = 0;; i = (i + 1) % 10)
    {
        for (int i = 0; i < 10; i++)
        {
            n++;
            printf("*");

        }
        
        int state = i % 2;
        gpio_set_level(BLINK_GPIO, state);
        
        printf("%d - state %d\n", n, state);

        vPortYield();
        delay(1000);
    }
    
#ifdef DO_DEEP_SLEEP
    const int deep_sleep_sec = 10;
    ESP_LOGI(TAG, "Entering deep sleep for %d seconds!", deep_sleep_sec);
    esp_deep_sleep(1000000LL * deep_sleep_sec);
#endif
}