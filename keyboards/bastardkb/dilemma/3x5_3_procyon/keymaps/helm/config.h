/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 8

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

#define ENCODER_RESOLUTION 4

#ifdef AUTO_MOUSE_DEFAULT_LAYER
#undef AUTO_MOUSE_DEFAULT_LAYER
#endif
#define AUTO_MOUSE_DEFAULT_LAYER 4

#ifdef LED_DPI_INDICATOR_INDEX
#undef LED_DPI_INDICATOR_INDEX
#endif
#define LED_DPI_INDICATOR_INDEX 7

#ifdef RGBLIGHT_LED_COUNT
#undef RGBLIGHT_LED_COUNT
#endif
#define RGBLIGHT_LED_COUNT 72
/* El gesto de tres dedos ya está tomado por QMK: la máquina de gestos del
 * fallback de ratón del digitizer entra en estado "swipe" con tres contactos y,
 * con solo 5 mm de recorrido, inyecta pulsaciones de tecla REALES (por defecto
 * KC_ESC hacia abajo, KC_LEFT_GUI hacia arriba, botones 3 y 4 a los lados).
 * Eso no pasa por report_mouse_t, así que ningún filtro del keymap puede
 * suprimirlo: hay que apagarlo en origen.
 *
 * Los cuatro macros están protegidos con #ifndef en
 * quantum/digitizer_mouse_fallback.c y este config.h se pasa con -include a
 * TODAS las unidades de compilación, así que definirlos aquí gana sin tocar QMK.
 * Se usa el literal 0 (== KC_NO) y no el símbolo KC_NO porque config.h se
 * procesa antes que quantum/keycodes.h. register_code(KC_NO) retorna sin hacer
 * nada, de modo que el swipe queda mudo pero conserva su transición de estado,
 * que además CONTIENE el gesto: mientras dura no sale ni cursor ni rueda. */
#define DIGITIZER_SWIPE_LEFT_KC  0
#define DIGITIZER_SWIPE_RIGHT_KC 0
#define DIGITIZER_SWIPE_UP_KC    0
#define DIGITIZER_SWIPE_DOWN_KC  0
