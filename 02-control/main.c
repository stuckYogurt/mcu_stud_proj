#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "stdlib.h"
#include "stdio.h"
#include "pico/stdlib.h"

#include "tick-handler/tick-handler.h"
#include "stdio-task/stdio-task.h"
#include "protocol-task/protocol-task.h"
#include "led-task/led-task.h"

#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"

void version_callback(const char* args)
{
    if (args != '\0') {
        printf("Arguments are unnecessary here, really\n");
    }

	printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VRSN);
}

void help_callback(const char* input) {
    for (uint i = 0; device_api[i].command_name; i++) {
        printf("\"%s\": %s", device_api[i].command_name, device_api[i].command_help);
    }
}

api_t device_api[] =
{
	{"version", version_callback, "get device name and firmware version"},
    {"led", led_task_state_set, "bro blinkin' like bip bip"} ,
	{NULL, NULL, NULL},
};

act_t ACTS[] = {
    {"led-task", false, led_task_blink},
    {NULL, NULL, NULL},
};

int main() {
    stdio_init_all();

    stdio_task_init();
    protocol_task_init(device_api);

    tick_handler_init(ACTS);

    while (1) {
        tick_handle();
        protocol_task_handle(stdio_task_handle());

    }
}