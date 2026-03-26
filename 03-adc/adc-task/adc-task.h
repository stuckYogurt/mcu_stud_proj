#pragma once

void adc_task_init();

float adc_measure();

void get_adc(const char*);

void get_temp(const char*);


void adc_task_handle(void);

void tm_start(const char*);

void tm_stop(const char*);