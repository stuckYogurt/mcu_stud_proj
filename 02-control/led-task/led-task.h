#pragma once

#include "pico/stdlib.h"
#include "hardware/gpio.h"

typedef enum
{
	LED_STATE_OFF = 0,
	LED_STATE_ON = 1,
	LED_STATE_BLINK = 2,
} led_state_t;

void led_task_blink();

void led_task_state_set(led_state_t state);

void led_task_init(const uint ledPin);

void led_task_handle(char* command_string);