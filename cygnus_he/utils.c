#include "utils.h"
#include "config.h"

uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
    if (in_min == in_max) return x < in_min ? out_min : out_max;

    uint16_t a = x < in_min ? 0 : x - in_min;
    uint32_t result = ((uint32_t)a * (out_max - out_min)) / (in_max - in_min) + out_min;

    return (result > out_max) ? out_max : (uint16_t)result;
}


uint8_t normalize_hall_effect_value(uint16_t value){
    // converts basic ranges 512..0 (more magnetic flux - less) and 512..1024 (more magnetic flux - more)
    // to range 0..255 with increasing with magnetic flux growth

    // real accuracy depends on how is switch magnet strong and uses in matrix.c
    uint16_t adjusted = (value >= 512) ? (value - 512) : (512 - value);
    return (uint8_t)(adjusted >> 1);
};

uint8_t min(uint8_t a, uint8_t b){
    return (a < b) ? a : b;
}

uint8_t max(uint8_t a, uint8_t b){
    return (a > b) ? a : b;
}
