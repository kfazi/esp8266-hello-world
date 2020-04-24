#include <cstdint>
#include <cstdio>

extern "C"
{
#include "freertos/FreeRTOS.h"

#include "driver/gpio.h"
#include "driver/uart.h"
#include "freertos/task.h"
#include "spi_flash.h"
}

static void blink_task(void*)
{
    gpio_set_direction(GPIO_NUM_0, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(GPIO_NUM_0, GPIO_FLOATING);

    while (true)
    {
        printf("Turning off the LED\n");
        gpio_set_level(GPIO_NUM_0, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("Turning on the LED\n");
        gpio_set_level(GPIO_NUM_0, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    vTaskDelete(nullptr);
}

static void setup()
{
    esp_log_level_set("*", ESP_LOG_NONE);

    uart_set_baudrate(UART_NUM_0, 115200);
    uart_set_word_length(UART_NUM_0, UART_DATA_8_BITS);
    uart_set_stop_bits(UART_NUM_0, UART_STOP_BITS_1);
    uart_set_parity(UART_NUM_0, UART_PARITY_DISABLE);

    printf("Flash size: %lu\n", spi_flash_get_chip_size());

    xTaskCreate(&blink_task, "blink", 2048, nullptr, tskIDLE_PRIORITY, nullptr);
}

extern "C"
{
    void app_main()
    {
        setup();
    }
}
