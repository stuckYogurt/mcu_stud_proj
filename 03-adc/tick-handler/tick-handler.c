#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "tick-handler.h"
#include "string.h"
#include "stdio.h"

act_t* ACTS;

void tick_handler_init(act_t* acts) {
    ACTS = acts;
}

void tick_handle() {
    for (size_t i = 0; ACTS[i].name; i++) {
        if (ACTS[i].active) {
            ACTS[i].act();
        }
    }
}

void freeze_act (char* actName) {
    for (size_t i = 0; ACTS[i].name; i++) {
        if (!strcmp(ACTS[i].name, actName)) {
            ACTS[i].active = false;
            return;
        }
    }
    printf("Act \"%s\" not found\n", actName);
}

void resume_act (char* actName) {
    for (size_t i = 0; ACTS[i].name; i++) {
        if (!strcmp(ACTS[i].name, actName)) {
            ACTS[i].active = true;
            return;
        }
    }
    printf("Act \"%s\" not found\n", actName);
}