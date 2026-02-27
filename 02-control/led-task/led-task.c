#include "ctype.h"

#include "led-task.h"
#include "tick-handler.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"

const uint LED_PIN = 25;
const uint LED_BLINK_PERIOD_US_DEF = 500000;
uint LED_BLINK_PERIOD_US = 500000;

uint64_t led_ts;
led_state_t led_state;

void led_task_blink() {
    if (time_us_64() > led_ts) {
        led_ts = time_us_64() + (LED_BLINK_PERIOD_US / 2);
        gpio_put(LED_PIN, 1);
    }
}

void led_task_init(const uint LED_PIN) {
    led_ts = 0;
    led_state = LED_STATE_OFF;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

}

void led_task_handle(char* command_string) {
    if (!strcmp(tolower(command_string), "on")) {
        freeze_act("led-task");
        led_state = LED_STATE_ON;
        return;
    }
    else if (!strcmp(tolower(command_string), "off")) {
        freeze_act("led-task");
        led_state = LED_STATE_OFF;
        return;
    }
    else if (!strstr(tolower(command_string), "blink")) {
        char* space_symbol = strchr(command_string, ' ');

        if (space_symbol)
        {
            char* end;
            LED_BLINK_PERIOD_US = strtol(space_symbol + 1, end, 10);
            if (end == space_symbol + 1) {
                printf("Standard %i ms period applied\n", LED_BLINK_PERIOD_US_DEF);
                LED_BLINK_PERIOD_US = LED_BLINK_PERIOD_US_DEF;
            }
        }
        else {
            printf("Standard %i us period applied\n", LED_BLINK_PERIOD_US_DEF);
            LED_BLINK_PERIOD_US = LED_BLINK_PERIOD_US_DEF;
        }


        resume_act("led-task");
        led_state = LED_STATE_BLINK;
        return;
    }

    printf("Undefined \"%s\"\n", command_string);

}