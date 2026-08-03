/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include QMK_KEYBOARD_H

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNCTION,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_POINTER,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
};

// Automatically enable sniping-mode on the pointer layer.
// #define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_FUN LT(LAYER_FUNCTION, KC_TAB)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_split_3x5_3(
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
       LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G, KC_H, LSFT_T(KC_J), LCTL_T(KC_K), LALT_T(KC_L), LGUI_T(KC_QUOT),
       PT_Z,    RALT_T(KC_X),    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  RALT_T(KC_DOT), PT_SLSH,
                      ESC_MED, TAB_FUN, SPC_NAV, ENT_SYM, BSP_NUM, KC_MUTE
  ),

/*
 * Layers used on the Dilemma.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */

/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
  [LAYER_FUNCTION] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F12,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_SCRL,   KC_F4,   KC_F5,   KC_F6,  KC_F11,
    XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAUS,   KC_F1,   KC_F2,   KC_F3,  KC_F10,
                      XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
  [LAYER_NAVIGATION] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_CAPS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
    XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX,  KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,
                      XXXXXXX, XXXXXXX, _______,  KC_ENT, KC_BSPC, KC_DEL
  ),

/**
 * \brief Media layer.
 *
 * Tertiary left- and right-hand layer is media and RGB control.  This layer is
 * symmetrical to accomodate the left- and right-hand trackball.
 */
  [LAYER_MEDIA] = LAYOUT_split_3x5_3(
    XXXXXXX, RM_PREV, RM_TOGG, RM_NEXT, XXXXXXX, XXXXXXX, RM_PREV, RM_TOGG, RM_NEXT, XXXXXXX,
    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      _______, KC_MPLY, KC_MSTP, KC_MSTP, KC_MPLY, KC_MUTE
  ),

/** \brief Mouse emulation and pointer functions. */
  [LAYER_POINTER] = LAYOUT_split_3x5_3(
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    _______, DRGSCRL, SNIPING, MS_BTN3, XXXXXXX, XXXXXXX, MS_BTN3, SNIPING, DRGSCRL, _______,
                      MS_BTN3, MS_BTN2, MS_BTN1, MS_BTN1, MS_BTN2, MS_BTN3
  ),

/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
  [LAYER_NUMERAL] = LAYOUT_split_3x5_3(
    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL, XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
     KC_DOT,    KC_1,    KC_2,    KC_3, KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX,
                       KC_DOT, KC_MINS,    KC_0, XXXXXXX, _______, XXXXXXX
  ),

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
  [LAYER_SYMBOLS] = LAYOUT_split_3x5_3(
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX,
                      KC_RPRN,  KC_GRV, KC_UNDS, _______, XXXXXXX, XXXXXXX
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_BASE]       = {ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_FUNCTION]   = {ENCODER_CCW_CW(KC_DOWN, KC_UP),    ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [LAYER_NAVIGATION] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),  ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_MEDIA]      = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),  ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_POINTER]    = {ENCODER_CCW_CW(RM_HUED, RM_HUEU),  ENCODER_CCW_CW(RM_SATD, RM_SATU)},
    [LAYER_NUMERAL]    = {ENCODER_CCW_CW(RM_VALD, RM_VALU),  ENCODER_CCW_CW(RM_SPDD, RM_SPDU)},
    [LAYER_SYMBOLS]    = {ENCODER_CCW_CW(RM_PREV, RM_NEXT),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
};
// clang-format on
#endif // ENCODER_MAP_ENABLE

/* ------------------------------------------------------------------------
 * Publicación del número de dedos apoyados hacia el host (Raw HID).
 *
 * El sensor (Procyon / maXTouch) es multitáctil y el firmware ya sabe cuántos
 * contactos hay: los usa para elegir el gesto (1 = cursor, 2 = scroll,
 * 3 = swipe). Ese dato nunca llega al host, porque macOS no envía el feature
 * report que conmutaría el firmware a modo trackpad y se queda emitiendo solo
 * ratón (X/Y/rueda). Sin él, la app del host no puede distinguir "dedos
 * apoyados para frenar" de "sin tocar".
 *
 * NOTA sobre el punto de enganche: lo natural sería el hook digitizer_task_user,
 * pero el módulo bk_pointing_device define digitizer_task_kb SIN reenviar la
 * llamada al hook de usuario (su propio comentario lo reconoce), así que ese
 * hook nunca se ejecuta. Por eso aquí se consulta el estado con la API pública
 * digitizer_get_state() desde housekeeping_task_user, que sí corre siempre.
 * ------------------------------------------------------------------------ */
#ifdef RAW_ENABLE
#    include "raw_hid.h"
#    include "digitizer.h"
#    include "suspend.h"

/* ========================================================================
 * Estado del trackpad: conteo de dedos, filtro antideriva y pestillo de
 * arrastre ("clic fijado" con tres dedos).
 *
 * El sensor (Procyon / maXTouch) es multitáctil y el firmware sabe cuántos
 * contactos hay, pero ese dato nunca llega al host: macOS no envía el feature
 * report que conmutaría el firmware a modo trackpad, así que se queda emitiendo
 * ratón (X/Y/rueda) y los dedos se pierden por el camino.
 *
 * PUNTO DE ENGANCHE: digitizer_task_user. El módulo bk_pointing_device define
 * digitizer_task_kb y NO reenvía al hook de usuario, cortando la cadena
 * kb -> user de QMK; hay un PARCHE LOCAL en el módulo que reañade la llamada.
 * Ese parche vive en un submódulo git sin commitear: si desaparece, este hook
 * deja de ejecutarse. Por eso todo lo de aquí abajo degrada a "no hacer nada"
 * (g_helm_signal_ok nunca se arma) y jamás a "botón izquierdo pulsado para
 * siempre".
 * ======================================================================== */

/* Cabeceras de los mensajes Raw HID. Quedan fuera de los command IDs de VIA
 * (0x01-0x15 y 0xFF) y del prefijo 0x90 de Argos, que comparten endpoint. */
#    define HELM_MSG_CONTACTS 0xB0 // conteo de dedos, solo por flanco
#    define HELM_MSG_PESTILLO 0xB3 // estado del clic fijado

/* Volcados de diagnóstico (0xB1 y 0xB2). Apagados: raw_hid_send puede bloquear
 * hasta 100 ms y esos mensajes salían desde dentro del bucle de escaneo, justo
 * lo que no interesa mientras hay un arrastre en curso. Poner a 1 para volver a
 * instrumentar. */
#    define HELM_DIAG 0

/* ---- Constantes del pestillo ------------------------------------------- */

/* Los tres dedos deben sostenerse este tiempo antes de conmutar. No es un lujo:
 * el sensor necesita varios ciclos de integración para declarar un contacto, de
 * modo que el conteo pasa por 1 y por 2 antes de asentarse en 3, y un roce
 * durante un scroll de dos dedos puede tocar el 3 un instante. */
#    define HELM_CONFIRMA_MS 60

/* Silencio de cursor Y rueda alrededor de CUALQUIER cambio del número de
 * contactos, en las dos direcciones. La bajada es la importante: el core calcula
 * el desplazamiento solo con fingers[0], y ese array se reempaqueta al levantar
 * un dedo, así que fingers[0] cambia de identidad y "x - last_x" produce un
 * salto del tamaño de la separación entre dedos. Con el botón enclavado eso
 * sería un arrastre de selección de pantalla entera. La subida lo necesita para
 * matar el tirón de rueda del paso por dos dedos. */
#    define HELM_TRANSICION_MS 80

/* Red de seguridad: soltar el pestillo si pasa este tiempo sin ningún dedo. Un
 * botón izquierdo pulsado que nadie suelta es el peor fallo posible. */
#    define HELM_TIMEOUT_MS 30000

/* Motivo publicado en el byte 3 del mensaje 0xB3. */
#    define HELM_MOTIVO_GESTO   0
#    define HELM_MOTIVO_TIMEOUT 1
#    define HELM_MOTIVO_SEGURIDAD 2

/* ÚNICO escritor: digitizer_task_user. La versión anterior también escribía
 * desde housekeeping_task_user con digitizer_get_state(); ese segundo escritor
 * corre a ritmo del bucle principal (después de keyboard_task), mientras que el
 * estado del digitizer solo se refresca cuando dispara el pin de movimiento, de
 * modo que las dos escrituras publicaban muestras de instantes distintos. Para
 * un filtro eso solo añadía ruido; para una detección por flanco es fatal. */
static volatile uint8_t g_helm_contacts = 0;

/* Señal validada: nada se activa hasta haber visto un contacto real. Si el
 * parche del módulo desaparece, el resultado es "no hace nada". */
static bool g_helm_signal_ok = false;

static volatile bool     g_helm_pestillo      = false; // botón izquierdo enclavado
static volatile bool     g_helm_pendiente     = false; // gesto de 3 dedos sin confirmar
static volatile bool     g_helm_rearmado      = true;  // histéresis: listo para conmutar
static volatile uint32_t g_helm_ts_transicion = 0;     // último cambio del conteo
static volatile uint32_t g_helm_ts_tres       = 0;     // instante en que se vieron 3
static volatile uint32_t g_helm_ts_sin_dedos  = 0;     // instante del último despegue total
static bool              g_helm_pestillo_pub  = false; // último estado publicado al host

/* Suelta el botón de verdad, sin esperar al siguiente ciclo del task. Se usa en
 * los caminos de apagado y suspensión, donde no habrá siguiente ciclo. */
static void helm_soltar_pestillo_ya(void) {
    if (!g_helm_pestillo) return;
    g_helm_pestillo  = false;
    g_helm_pendiente = false;
    report_mouse_t r = pointing_device_get_report();
    r.buttons        = 0;
    pointing_device_set_report(r);
    pointing_device_send();
}

static void helm_publicar_pestillo(uint8_t motivo) {
    /* raw_hid_send exige exactamente 32 bytes (RAW_EPSIZE) y descarta en
     * silencio cualquier otra longitud; la constante no está expuesta a los
     * keymaps, así que se usa el literal. */
    uint8_t msg[32] = {0};
    msg[0] = HELM_MSG_PESTILLO;
    msg[1] = g_helm_pestillo ? 1 : 0;
    msg[2] = g_helm_contacts;
    msg[3] = motivo;
    raw_hid_send(msg, sizeof(msg));
    g_helm_pestillo_pub = g_helm_pestillo;
}

/* Llamado desde el módulo bk_pointing_device (parcheado para encadenar). Aquí
 * los contactos son los recién leídos del sensor y este hook corre UNA vez por
 * lectura, así que es el sitio correcto para detectar flancos. Pero solo corre
 * cuando el pin de movimiento (GP12) dispara: con tres dedos muy quietos podría
 * no volver a ejecutarse, por eso la CONFIRMACIÓN temporal se hace en
 * housekeeping_task_user, que sí corre siempre. */
bool digitizer_task_user(digitizer_t *const digitizer_state) {
    uint8_t contactos = 0;
    for (int i = 0; i < DIGITIZER_CONTACT_COUNT; i++) {
        if (digitizer_state->contacts[i].type == FINGER && digitizer_state->contacts[i].tip) {
            contactos++;
        }
    }

    const uint8_t  previos = g_helm_contacts;
    const uint32_t ahora   = timer_read32();

    if (contactos != previos) {
        /* La ventana de silencio solo se arma en transiciones MULTITÁCTILES.
         * Empezar o terminar un movimiento normal (0 <-> 1 dedo) no debe
         * silenciar nada: ahí no hay reindexado de fingers[0] que produzca
         * saltos, y silenciar 80 ms el arranque de cada movimiento se sentiría
         * como una zona muerta al empezar a apuntar. */
        if (contactos >= 2 || previos >= 2) {
            g_helm_ts_transicion = ahora;
        }

        if (contactos >= 3 && previos < 3) {
            /* Flanco de subida a tres dedos: se ABRE una solicitud, no se
             * conmuta todavía. g_helm_rearmado impide que un mismo gesto
             * conmute dos veces si el conteo baila entre 2 y 3. */
            g_helm_ts_tres   = ahora;
            g_helm_pendiente = g_helm_rearmado;
        } else if (contactos < 3) {
            g_helm_pendiente = false; // el gesto se deshizo antes de confirmarse
        }

        if (contactos <= 1) {
            g_helm_rearmado = true; // histéresis: hay que soltar para volver a conmutar
        }
        if (contactos == 0) {
            g_helm_ts_sin_dedos = ahora;
        }
    }

    g_helm_contacts = contactos;
    if (contactos > 0) g_helm_signal_ok = true;

#    if HELM_DIAG
    /* Volcado del contacto 0 tal cual lo entrega el sensor. */
    static uint32_t last_dump = 0;
    if (timer_elapsed32(last_dump) > 300) {
        last_dump = timer_read32();
        uint8_t m[32] = {0};
        m[0]  = 0xB2;
        m[1]  = contactos;
        m[2]  = (uint8_t)digitizer_state->contacts[0].type;
        m[3]  = digitizer_state->contacts[0].tip;
        m[4]  = digitizer_state->contacts[0].in_range;
        m[5]  = digitizer_state->contacts[0].confidence;
        m[6]  = digitizer_state->contacts[0].x & 0xFF;
        m[7]  = digitizer_state->contacts[0].x >> 8;
        m[8]  = digitizer_state->contacts[0].y & 0xFF;
        m[9]  = digitizer_state->contacts[0].y >> 8;
        m[10] = (uint8_t)digitizer_state->contacts[1].type;
        m[11] = digitizer_state->contacts[1].tip;
        raw_hid_send(m, sizeof(m));
    }
#    endif
    return false;
}

/* ------------------------------------------------------------------------
 * Retención de un ciclo contra el arrastre al despegar el dedo.
 *
 * Al levantar el dedo la huella se deforma antes de desaparecer y el sensor
 * reporta un salto espurio. La cura es emitir el desplazamiento con un ciclo de
 * retraso: lo que quede sin emitir cuando el dedo desaparece —el salto— se
 * descarta y nunca llega al host.
 *
 * POR QUÉ UN SOLO CICLO Y NO MÁS. Se probó una retención adaptativa y profunda
 * (14 ciclos apuntando, 2 en movimiento franco) y quitaba más rebote, pero el
 * cambio de profundidad vaciaba doce ciclos acumulados en un ÚNICO reporte, y
 * ese tirón se percibe como un cursor hipersensible. La retención fija de un
 * ciclo no puede producir ráfagas: entra un desplazamiento por ciclo y sale
 * uno, siempre. Se prefiere un resto de rebote a un cursor impredecible.
 * ------------------------------------------------------------------------ */
report_mouse_t pointing_device_task_user(report_mouse_t report) {
    static mouse_xy_report_t pending_x = 0, pending_y = 0, out_x = 0, out_y = 0;
    static uint32_t          last_cycle = 0;

    /* PESTILLO — lo PRIMERO de todo, por delante de los retornos tempranos: el
     * caso que hay que sostener es justamente "cero contactos", porque el
     * usuario levanta y repone el dedo a propósito en mitad del arrastre.
     *
     * Se reaplica en CADA invocación porque pointing_device_task reasigna
     * local_mouse_report entero con lo que devuelve el driver, y el driver del
     * digitizer ignora el report que recibe y devuelve su propio estático: no
     * hay persistencia de buttons que aprovechar. Es un OR idempotente, así que
     * la doble invocación por ciclo (módulo + pointing_device_task_kb) da igual.
     *
     * La máscara de BTN2/BTN3 no es paranoia: el tap-to-click del core elige el
     * botón según cuántos dedos tuvo el toque (2 → derecho, 3 → central), y un
     * menú contextual en mitad de un arrastre es siempre ruido. */
    if (g_helm_pestillo) {
        report.buttons |= MOUSE_BTN1;
        report.buttons &= (uint8_t) ~(MOUSE_BTN2 | MOUSE_BTN3);
    }

    if (!g_helm_signal_ok) return report; // señal no validada: no tocar nada más

    /* Ventana de transición. Solo se LEE la marca de tiempo; el escritor es
     * digitizer_task_user, que corre una vez por lectura del sensor. Tirar la
     * cola aquí es idempotente, así que la doble invocación no molesta. */
    if (timer_elapsed32(g_helm_ts_transicion) < HELM_TRANSICION_MS) {
        pending_x = pending_y = out_x = out_y = 0;
        report.x = report.y = 0;
        report.h = report.v = 0;
        return report;
    }

    /* Con tres dedos o más nunca debe salir rueda: si se mantienen apoyados más
     * de un segundo el core devuelve el gesto al estado de scroll, y a partir de
     * ahí tres contactos caen en la rama de la rueda. */
    if (g_helm_contacts >= 3) {
        pending_x = pending_y = out_x = out_y = 0;
        report.x = report.y = 0;
        report.h = report.v = 0;
        return report;
    }

    if (g_helm_contacts == 0) {
        // Tirar lo retenido: es el salto del despegue.
        pending_x = pending_y = out_x = out_y = 0;
        report.x = report.y = 0;
        return report;
    }

    // El guardia por milisegundo es necesario porque este hook se llama DOS
    // veces por ciclo (el módulo bk_pointing_device y pointing_device_task_kb).
    const uint32_t now = timer_read32();
    if (now != last_cycle) {
        last_cycle = now;
        out_x     = pending_x;
        out_y     = pending_y;
        pending_x = report.x;
        pending_y = report.y;
    }
    report.x = out_x;
    report.y = out_y;
    return report;
}

#    ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
/* Sin esto la capa auto-mouse se queda encendida MIENTRAS DURE el pestillo: la
 * implementación de QMK devuelve "activo" ante cualquier bit de buttons y no
 * evalúa la expiración mientras siga activa. Esa capa es LAYER_POINTER, que
 * lleva QK_BOOT y EE_CLR en las cuatro esquinas superiores, así que dejarla
 * clavada durante un arrastre largo no es cosmético.
 *
 * Se replica el acumulador de movimiento del core porque su contexto es privado
 * y no hay forma de delegar en la implementación original. El core reinicia el
 * acumulador en cuanto la capa se activa; aquí se hace lo mismo al devolver
 * verdadero, que es equivalente a efectos prácticos. */
bool auto_mouse_activation(report_mouse_t mouse_report) {
    static int16_t acum_x = 0, acum_y = 0, acum_h = 0, acum_v = 0;

    if (g_helm_pestillo) {
        mouse_report.buttons &= (uint8_t)~MOUSE_BTN1;
    }
    acum_x += mouse_report.x;
    acum_y += mouse_report.y;
    acum_h += mouse_report.h;
    acum_v += mouse_report.v;

    const bool activo = abs(acum_x) > AUTO_MOUSE_THRESHOLD || abs(acum_y) > AUTO_MOUSE_THRESHOLD || abs(acum_h) > AUTO_MOUSE_THRESHOLD || abs(acum_v) > AUTO_MOUSE_THRESHOLD || mouse_report.buttons;
    if (activo) {
        acum_x = acum_y = acum_h = acum_v = 0;
    }
    return activo;
}
#    endif

/* Pulsar y soltar MS_BTN1 (capa POINTER) con el pestillo puesto emitiría un
 * BTN1-UP real: la versión de QMK borra el bit y ENVÍA de inmediato, fuera del
 * task, así que el OR del pestillo no se reaplica hasta el ciclo siguiente y el
 * host ve un clic espurio que suelta el arrastre. Se repone el bit antes del
 * envío. Todo con API pública; no hace falta tocar QMK. */
void pointing_device_keycode_handler(uint16_t keycode, bool pressed) {
    if (IS_MOUSEKEY_BUTTON(keycode)) {
        report_mouse_t r = pointing_device_get_report();
        r.buttons        = pointing_device_handle_buttons(r.buttons, pressed, (pointing_device_buttons_t)(keycode - QK_MOUSE_BUTTON_1));
        if (g_helm_pestillo) r.buttons |= MOUSE_BTN1;
        pointing_device_set_report(r);
        pointing_device_send();
    }
}

/* clear_keyboard() limpia mods, teclas y mousekey, pero NO el report del
 * pointing device. Sin esto, saltar al bootloader con el pestillo puesto dejaría
 * el botón izquierdo pulsado en el host hasta el siguiente arranque. No se
 * publica por Raw HID aquí: el envío puede bloquear hasta 100 ms y el teclado ya
 * se está apagando. */
bool shutdown_user(bool jump_to_bootloader) {
    helm_soltar_pestillo_ya();
    return true;
}

/* En suspensión el task del pointing device sigue corriendo pero un report
 * idéntico no se reenvía, así que tras el resume el firmware creería el botón
 * pulsado y el host no lo tendría. Se suelta al dormir. Es idempotente: esta
 * función se invoca repetidamente durante la suspensión. */
void suspend_power_down_user(void) {
    helm_soltar_pestillo_ya();
}

void housekeeping_task_user(void) {
    if (!is_keyboard_master()) return;

    static uint8_t last_contacts = 0xFF;

    /* Confirmación del gesto de tres dedos. Va aquí y no en digitizer_task_user
     * porque aquel hook solo corre cuando el pin de movimiento dispara: con tres
     * dedos muy quietos podría no volver a ejecutarse y la confirmación no
     * llegaría nunca. Este sí corre en cada vuelta del bucle principal. */
    if (g_helm_pendiente && g_helm_contacts >= 3 && timer_elapsed32(g_helm_ts_tres) >= HELM_CONFIRMA_MS) {
        g_helm_pestillo  = !g_helm_pestillo;
        g_helm_pendiente = false;
        g_helm_rearmado  = false; // hasta bajar a <=1 dedo no se vuelve a conmutar
    }

    /* Red de seguridad. El conteo puede quedar congelado si el sensor deja de
     * emitir, así que el criterio es tiempo sin dedos, no número de ciclos. */
    if (g_helm_pestillo && g_helm_contacts == 0 && timer_elapsed32(g_helm_ts_sin_dedos) > HELM_TIMEOUT_MS) {
        g_helm_pestillo = false;
        helm_publicar_pestillo(HELM_MOTIVO_TIMEOUT);
    }

    /* Publicaciones SOLO por flanco: raw_hid_send puede bloquear hasta 100 ms si
     * el host deja de drenar el endpoint, así que nunca debe ir en bucle. */
    if (g_helm_pestillo != g_helm_pestillo_pub) {
        helm_publicar_pestillo(HELM_MOTIVO_GESTO);
    }
    if (g_helm_contacts != last_contacts) {
        last_contacts   = g_helm_contacts;
        uint8_t msg[32] = {0};
        msg[0]          = HELM_MSG_CONTACTS;
        msg[1]          = g_helm_contacts;
        msg[2]          = g_helm_pestillo ? 1 : 0;
        raw_hid_send(msg, sizeof(msg));
    }

#    if HELM_DIAG
    /* Latido cada 500 ms con el conteo y el estado crudo del sensor. */
    static uint32_t last_beat = 0;
    if (timer_elapsed32(last_beat) > 500) {
        last_beat            = timer_read32();
        const digitizer_t st = digitizer_get_state();
        uint8_t msg[32]      = {0};
        msg[0]               = 0xB1;
        msg[1]               = g_helm_contacts;
        for (int i = 0; i < DIGITIZER_CONTACT_COUNT && i < 5; i++) {
            msg[2 + i * 2] = (uint8_t)st.contacts[i].type;
            msg[3 + i * 2] = st.contacts[i].tip ? 1 : 0;
        }
        raw_hid_send(msg, sizeof(msg));
    }
#    endif
}
#endif
