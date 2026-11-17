#pragma once

// maps X from range [in_min; in_max] to range [out_min; out_max]
uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

// converts ranges from 0..512 (descending) and 512..1024 (ascending) to range 0..255 (ascending)
uint8_t normalize_hall_effect_value(uint16_t value);

// max and min of two given values
uint8_t min(uint8_t a, uint8_t b);
uint8_t max(uint8_t a, uint8_t b);
