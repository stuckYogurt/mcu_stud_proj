#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "stdlib.h"
#include "stdio.h"
#include "pico/stdlib.h"

#include "adc-task/adc-task.h"
#include "tick-handler/tick-handler.h"
#include "stdio-task/stdio-task.h"
#include "protocol-task/protocol-task.h"
#include "led-task/led-task.h"
#include "adc-task/adc-task.h"

#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"

const uint LED_PIN_DEF = 25;

void version_callback(const char* args);
void help_callback(const char* input);

const api_t device_api[] =
{
	{"version", version_callback, "get device name and firmware version"},
    {"help", help_callback, "help like for help"},

    {"led", led_task_handle, "bro blinkin' like bip bip"},

    {"get_adc", get_adc, "adc voltage in V"},
    {"get_temp", get_temp, "internal temp"},
    {"tm_start", tm_start, "start measure"},
    {"tm_stop", tm_stop, "stop measure"},

	{NULL, NULL, NULL},
};

act_t POSSIBLE_ACTS[] = {
    {"led-task", false, led_task_blink},
    {"tm", false, adc_task_handle},
    {NULL, NULL, NULL},
};

void version_callback(const char* args)
{
    if (*args != '\0') {
        printf("Arguments are unnecessary here, really\n");
    }

	printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VRSN);
}

void help_callback(const char* input) {
    for (uint i = 0; device_api[i].command_name; i++) {
        printf("\"%s\": %s\n", device_api[i].command_name, device_api[i].command_help);
    }
}



int main() {
    stdio_init_all();

    stdio_task_init();
    protocol_task_init(device_api);

    led_task_init(LED_PIN_DEF);
    adc_task_init();
    tick_handler_init(POSSIBLE_ACTS);

    while (1) {
        tick_handle();
        protocol_task_handle(stdio_task_handle());

    }
}