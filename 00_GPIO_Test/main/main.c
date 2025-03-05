/***************************************************************************************************************
*****************************    Author  : Ehab Magdy Abdullah                      ****************************
*****************************    Linkedin: https://www.linkedin.com/in/ehabmagdyy/  ****************************
*****************************    Youtube : https://www.youtube.com/@EhabMagdyy      ****************************
****************************************************************************************************************/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

void Led_Task(void *pvParameter);
void Button_Task(void *pvParameter);

#define TAG             "DIO Example"
#define LED_PIN         GPIO_NUM_2
#define BUTTON_PIN      GPIO_NUM_25

void app_main(void)
{
    ESP_LOGI(TAG, "ESP32 LED & Button Example!");
    xTaskCreate(&Led_Task, "Led_Task", 1024, NULL, 5, NULL);
    xTaskCreate(&Button_Task, "Button_Task", 1024, NULL, 5, NULL);
}

void Led_Task(void *pvParameter)
{
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    for(;;)
    {
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void Button_Task(void *pvParameter)
{
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLDOWN_ONLY);

    for(;;)
    {
        if(gpio_get_level(BUTTON_PIN))
            ESP_LOGI(TAG, "Button is pressed");
        else
            ESP_LOGI(TAG, "Button is not pressed");

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}