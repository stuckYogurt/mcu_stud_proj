#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "stdlib.h"
#include "stdio.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    while (1) {
        char symbol = getchar();
        printf("received char: %c [ ASCII code: %d ]\n", symbol, symbol);

        sleep_ms(1000);

    }
}