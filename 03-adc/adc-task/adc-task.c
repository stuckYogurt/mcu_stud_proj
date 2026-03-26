#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "adc-task.h"
#include "../tick-handler/tick-handler.h"

#include "stdio.h"

const uint GPIO_PIN = 26;
const uint ADC_CH = 4;
const uint TEMP_CH = 4;

void adc_task_init() {
    
    adc_init();
    adc_set_temp_sensor_enabled(true);
    // adc_gpio_init(GPIO_PIN);

}

float adc_measure() {
    adc_select_input(ADC_CH);
    uint16_t voltage_counts = adc_read();
    return (float)voltage_counts * 3.3f / 4096;
}

float adc_temp() {
    adc_select_input(TEMP_CH);
    uint16_t voltage_counts = adc_read();
    float voltage = (float)voltage_counts * 3.3f / 4096;
    return 27.0f - (voltage - 0.706f) / 0.001721f;
}

void get_adc(const char*) {
    printf("%f\n", adc_measure());
}

void get_temp(const char*) {
    printf("%f C\n", 27.0f - (adc_measure() - 0.706f) / 0.001721f);
}


static uint64_t last_measurement_time = 0;
static const uint64_t ADC_TASK_MEAS_PERIOD_US = 100000;

void adc_task_handle(void) {
    uint64_t current_time = time_us_64();
    uint64_t time_diff = current_time - last_measurement_time;
    
    if (time_diff >= ADC_TASK_MEAS_PERIOD_US) {
        float voltage = adc_measure();
        float temp = adc_temp();
        
        printf("%f %f\n", voltage, temp);
        last_measurement_time = current_time;
    }
}

void tm_start(const char*) {
    resume_act("tm");
    printf("Measurements started\n");
}

void tm_stop(const char*) {
    freeze_act("tm");
    printf("Measurements stopped\n");
}