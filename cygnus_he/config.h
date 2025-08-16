#pragma once

// GPIOs for multiplexer selector
#define MUX_SEL0_PIN GP6
#define MUX_SEL1_PIN GP7
#define MUX_SEL2_PIN GP8
#define MUX_SEL3_PIN GP9
#define MUX_DATA_PIN GP29

/* RP2040- and hardware-specific config */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64

// For mapped to 0..100 range values // todo: use raw values instead of % for better precision
// Dont make min and max close to 0 and 100, it can cause buttons not to trigger or instatrigger
#define MAX_THRESHOLD 90
#define MIN_THRESHOLD 10
// May be changed of you need more precious tuning
#define DEFAULT_THRESHOLD 20    // In range of 0..100. Can be interpreted as %


#define RAPID_TRIGGER_ENABLED
#define RAPID_TRIGGER_DELTA 5  // how much in % you shuld move key to release or press it again

#define SERIAL_USART_TX_PIN GP1
#define MASTER_LEFT
