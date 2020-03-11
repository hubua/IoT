#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include <iostream>

extern "C" {
    void app_main(void);
}

void app_main()
{
    std::string s = "hello cpp 2";
    std::cout << s << std::endl;
    printf("hello %s", s.c_str);
   
}