#pragma once

#include "pico/stdlib.h"
#include "hardware/gpio.h"

typedef void(*tick_act)();

typedef struct {
    char* name;
    bool active;
    tick_act act;
} act_t;

void tick_handler_init(act_t* acts);

void tick_handle();

void freeze_act (char* actName);

void resume_act (char* actName);