
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void Led_Task(void *pvParameter);
void Button_Task(void *pvParameter);

#define LED_GPIO        GPIO_NUM_2
#define BUTTON_GPIO     GPIO_NUM_25

void app_main(void)
{
    printf("ESP32 LED & Button Example!\n");
    xTaskCreate(&Led_Task, "Led_Task", 1024, NULL, 5, NULL);
    xTaskCreate(&Button_Task, "Button_Task", 1024, NULL, 5, NULL);
}

void Led_Task(void *pvParameter)
{
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    for(;;)
    {
        gpio_set_level(LED_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void Button_Task(void *pvParameter)
{
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_GPIO, GPIO_PULLDOWN_ONLY);

    for(;;)
    {
        gpio_get_level(BUTTON_GPIO) ? printf("Button is pressed\n") : printf("Button is not pressed\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}