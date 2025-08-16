#include "matrix.h"
#include "analog.h"
#include "utils.h"

#define ROWS_PER_HAND (MATRIX_ROWS / 2)
static const pin_t mux_sel_pins[4] = {MUX_SEL0_PIN, MUX_SEL1_PIN, MUX_SEL2_PIN, MUX_SEL3_PIN};
static pin_t pin_matrix[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;

typedef struct {
    // absolute minimum value when key is released and released (individual key boundaries)
    uint8_t min_released_threshold;
    uint8_t max_pressed_threshold;
    // for rapid trigger:
    uint8_t released_rt_threshold; // value below is considered released
    uint8_t pressed_rt_threshold; // value above is considered pressed
    bool is_pressed; // key state
} analog_key_t;

static analog_key_t analog_keys[ROWS_PER_HAND][MATRIX_COLS];

void select_mux_channel(uint8_t addr) {
    if (addr > 0xF) return;

    for (uint8_t i = 0; i < 4; i++) {
        gpio_write_pin(mux_sel_pins[i], (addr >> i) & 1);
    }
}

bool process_rapid_trigger(analog_key_t *key, uint8_t pressed_percentage) {
    if (!key) return false;
    
    if (pressed_percentage >= key->pressed_rt_threshold) {
        key->is_pressed = true;
        key->pressed_rt_threshold = min(pressed_percentage, MAX_THRESHOLD);
        key->released_rt_threshold = max(key->pressed_rt_threshold - RAPID_TRIGGER_DELTA, MIN_THRESHOLD);
    }

    if (pressed_percentage <= key->released_rt_threshold) {
        key->is_pressed = false;
        key->released_rt_threshold = max(pressed_percentage, MIN_THRESHOLD);
        key->pressed_rt_threshold = min(key->released_rt_threshold + RAPID_TRIGGER_DELTA, MAX_THRESHOLD);
    }

    return key->is_pressed;
}


bool check_key_press(uint8_t row, uint8_t col) {
    if (row >= ROWS_PER_HAND || col >= MATRIX_COLS) {
        return false;
    }
    
    pin_t pin = pin_matrix[row][col];
    if (pin == NO_PIN) {
        return false;
    }

    select_mux_channel((row * MATRIX_COLS) + col);
    chThdSleepMicroseconds(30); // wait for mux to setup

    uint8_t pin_value = normalize_hall_effect_value(analogReadPin(pin));
    analog_key_t *key = &analog_keys[row][col];

    // refresh key max and min thresholds
    if (pin_value > key->max_pressed_threshold) {
        key->max_pressed_threshold = pin_value;
    }
    if (pin_value < key->min_released_threshold) {
        key->min_released_threshold = pin_value;
    }

    // todo: use raw, non-mapped to percentage value for better precision
    uint8_t pressed_percentage = map(
        pin_value,
        key->min_released_threshold,
        key->max_pressed_threshold,
        0, 100
    );
#ifdef RAPID_TRIGGER_ENABLED
    return process_rapid_trigger(key, pressed_percentage);
#else
    return pressed_percentage >= DEFAULT_THRESHOLD;
#endif
}

void matrix_init_custom(void) {
    // set mux select pins as output
    for (uint8_t i = 0; i < 4; i++) {
        gpio_set_pin_output(mux_sel_pins[i]);
    }

    for (uint8_t row = 0; row < ROWS_PER_HAND; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            // todo: set min and max thresholds based on real key value
            analog_keys[row][col].min_released_threshold = 0xFF; // it will recalculate itself later
             // low values of max_pressed_threshold leads to instant presses when keyboard plugs in
            analog_keys[row][col].max_pressed_threshold = 90;
            analog_keys[row][col].is_pressed = false;
            analog_keys[row][col].pressed_rt_threshold = DEFAULT_THRESHOLD;
            analog_keys[row][col].released_rt_threshold = MIN_THRESHOLD;
        }
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;
    matrix_row_t row_state = 0;

    for (uint8_t row = 0; row < ROWS_PER_HAND; row++) {
        row_state = 0;
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (check_key_press(row, col)) {
                row_state |= (1 << col);
            }
        }

        if (current_matrix[row] != row_state) {
            current_matrix[row] = row_state;
            matrix_has_changed = true;
        }
    }
    return matrix_has_changed;
}