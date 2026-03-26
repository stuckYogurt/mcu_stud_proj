#include "hardware/adc.h"
#include "pico/stdlib.h"

#include "stdio.h"

const uint GPIO_PIN = 26;
const uint ADC_CH = 4;

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

void get_adc(const char*) {
    printf("%f\n", adc_measure());
}

void get_temp(const char*) {
    printf("%f C\n", 27.0f - (adc_measure() - 0.706f) / 0.001721f);
}