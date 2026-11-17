#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _LEFT,
    _RIGHT,
    _ADJUST,
};

// LEFT HAND HOME ROW MODS QWERTY
#define CTL_A MT(MOD_LCTL, KC_A)
#define ALT_S MT(MOD_LALT, KC_S)
#define GUI_D MT(MOD_LGUI, KC_D)
#define SHT_F MT(MOD_LSFT, KC_F)

// RIGHT HAND HOME ROW MODS QWERTY
#define SHT_J MT(MOD_RSFT, KC_J)
#define GUI_K MT(MOD_LGUI, KC_K)
#define ALT_L MT(MOD_LALT, KC_L)
#define CTL_S MT(MOD_LCTL, KC_SCLN)

// LAYER ALIASES
#define LEFT LT(_LEFT, KC_TAB)
#define RIGHT MO(_RIGHT)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM combo_bspc[] = {SHT_J, GUI_K, COMBO_END};
const uint16_t PROGMEM combo_minus[] = {GUI_D, SHT_F, COMBO_END};
const uint16_t PROGMEM combo_quot[] = {SHT_J, GUI_K, ALT_L, COMBO_END};
combo_t key_combos[] = {
    COMBO(combo_quot, KC_QUOT),
    COMBO(combo_bspc, KC_BSPC),
    COMBO(combo_minus, KC_MINS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
     //╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷
        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,       KC_Y,    KC_U,     KC_I,     KC_O,     KC_P,
        CTL_A,    ALT_S,    GUI_D,    SHT_F,    KC_G,       KC_H,    SHT_J,    GUI_K,    ALT_L,    CTL_S,
        KC_SLSH,  KC_Z,     KC_X,     KC_C,     KC_V,       KC_B,    KC_N,     KC_M,     KC_COMM,  KC_DOT,
                            KC_GRV,   LEFT,     KC_SPC,     KC_SPC,  RIGHT,    KC_ESC
    ),
    [_LEFT] = LAYOUT(
     //╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷
        KC_DEL,   KC_F1,    KC_F2,    KC_F3,    KC_F4,      KC_EQL,  KC_7,     KC_8,     KC_9,     KC_PSLS,
        _______,  KC_F5,    KC_F6,    KC_F7,    KC_F8,      KC_MINS, KC_4,     KC_5,     KC_6,     _______,
        KC_PSCR,  KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_PDOT, KC_1,     KC_2,     KC_3,     KC_GRV,
                            _______,  _______,  KC_ENT,     KC_ENT,  ADJUST,   KC_0
    ),
    [_RIGHT] = LAYOUT(
     //╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷
        _______,  _______,  _______,  _______,  _______,    KC_PGUP, KC_INS,   KC_UP,    KC_DEL,   KC_LBRC,
        KC_LCTL,  KC_LALT,  KC_LGUI,  KC_LSFT,  KC_ESC,     KC_PGDN, KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_RBRC,
        _______,  _______,  _______,  _______,  _______,    _______, KC_HOME,  _______,  KC_END,   KC_BSLS,
                            _______,  ADJUST,    KC_ENT,    KC_ENT,  _______,  _______
    ),
    [_ADJUST] = LAYOUT(
     //╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷
        QK_BOOT,  _______,  _______,  _______,  KC_LCAP,    _______, KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,
        _______,  _______,  _______,  _______,  _______,    _______, KC_VOLD,  KC_MUTE,  KC_VOLU,  _______,
        _______,  _______,  _______,  _______,  _______,    _______, _______,  _______,  _______,  _______,
                            _______,  _______,  _______,    _______, _______,  _______
    ),
};
