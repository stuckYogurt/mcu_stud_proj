#include "ctype.h"

#include "led-task.h"
#include "tick-handler.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

const uint LED_PIN = 25;
const uint LED_BLINK_PERIOD_US_DEF = 500000;
uint LED_BLINK_PERIOD_US = 500000;

uint64_t led_ts;
bool led_state;

void led_task_blink() {
    if (time_us_64() > led_ts) {
        led_ts = time_us_64() + (LED_BLINK_PERIOD_US / 2);
        led_state = !led_state;
        if (led_state) {
            gpio_put(LED_PIN, 1);
        } else {
            gpio_put(LED_PIN, 0);
        }
    }
}

void led_task_init(const uint LED_PIN) {
    led_ts = 0;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

}

void led_task_handle(const char* command_string) {
    if (!strcmp((command_string), "on")) {
        freeze_act("led-task");
        gpio_put(LED_PIN, 1);
        return;
    }
    else if (!strcmp((command_string), "off")) {
        freeze_act("led-task");
        gpio_put(LED_PIN, 0);
        return;
    }
    else if (strstr((command_string), "blink")) {
        char* space_symbol = strchr(command_string, ' ');

        if (space_symbol)
        {
            char* end;
            LED_BLINK_PERIOD_US = strtol(space_symbol + 1, &end, 10);
            if (end <= space_symbol + 1) {
                printf("Default %i us period applied\n", LED_BLINK_PERIOD_US_DEF);
                LED_BLINK_PERIOD_US = LED_BLINK_PERIOD_US_DEF;
            }
        }
        else {
            printf("Default %i us period applied\n", LED_BLINK_PERIOD_US_DEF);
            LED_BLINK_PERIOD_US = LED_BLINK_PERIOD_US_DEF;
        }


        resume_act("led-task");
        return;
    }

    printf("Undefined \"%s\"\n", command_string);

}