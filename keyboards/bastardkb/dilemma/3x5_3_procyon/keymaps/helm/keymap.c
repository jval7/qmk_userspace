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
    /* Cruceta en I J K L: la flecha arriba sube a la I y las tres restantes
       quedan bajo índice, corazón y anular en la fila de reposo. Antes iban las
       cuatro en fila (←↓↑→ sobre J K L '), que obliga a traducir "arriba" a una
       posición horizontal. La cruceta coincide con la forma del gesto. */
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, XXXXXXX,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,
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
    /* QK_BOOT y EE_CLR SOLO en la mitad derecha. Venían duplicados en las
       cuatro esquinas superiores, y esta capa se enciende sola al tocar el
       trackpad (es AUTO_MOUSE_DEFAULT_LAYER): dejar el salto al bootloader y el
       borrado de la EEPROM bajo los meñiques de las dos manos es tentar a la
       suerte. Con una sola copia siguen estando accesibles y hay la mitad de
       superficie por la que dispararlos sin querer. */
    XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT,
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

/* El hook layer_state_set_user vive ahora al FINAL de este fichero, fusionado
 * con la publicación de la capa activa por Raw HID (mensaje 0xB4).
 *
 * No es un capricho de orden: layer_state_set_user solo puede definirse UNA vez
 * en la unidad de compilación. Si el sniping automático se quedara aquí y la
 * publicación de capa estuviera abajo, el enlazado fallaría con «multiple
 * definition» en cuanto se descomentara DILEMMA_AUTO_SNIPING_ON_LAYER (línea 32
 * de este fichero). La llamada a dilemma_set_pointer_sniping_enabled se
 * conserva íntegra, con su #ifdef, dentro del hook fusionado. */

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
#    define HELM_MSG_CAPA     0xB4 // capa activa más alta, solo por flanco

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

/* ---- Capa activa (mensaje 0xB4) ----------------------------------------
 *
 * El host dibuja las capas del teclado y necesita saber cuál está activa para
 * cambiar el dibujo mientras se mantiene pulsada la tecla que la activa. Casi
 * todas las capas de este keymap se alcanzan con LT(), o sea manteniendo, más
 * la capa auto-mouse que se enciende sola al mover el trackpad.
 *
 * DOS VARIABLES Y NO UNA, igual que con el pestillo: una la escribe el hook de
 * cambio de capa y la otra recuerda lo último que se mandó al host. La
 * comparación entre ambas es lo que produce el flanco. Publicar en bucle está
 * prohibido en este fichero por una razón medida: raw_hid_send termina en
 * usb_endpoint_in_send con un timeout de 100 ms, así que un host que deje de
 * drenar el endpoint congelaría el bucle principal.
 *
 * volatile es aquí una formalidad, no una necesidad: el hook de capa y
 * housekeeping_task_user corren los dos en el hilo del bucle principal de QMK,
 * no hay ISR de por medio. Se marca por coherencia con el resto del estado de
 * este fichero y para que un futuro escritor desde interrupción no muerda. */
static volatile uint8_t g_helm_capa     = 0;    // capa efectiva más alta ahora
static uint8_t          g_helm_capa_pub = 0xFF; // 0xFF = nunca publicada aún

/* El contrato con el host reserva UN byte para el índice, con rango 0..7. Hoy
 * eso se cumple solo: VIA fija DYNAMIC_KEYMAP_LAYER_COUNT en 8, con lo que
 * layer_state_t es uint8_t y get_highest_layer() no puede devolver más de 7.
 * Si alguien sube el número de capas, esto revienta en compilación en vez de
 * mandar un índice truncado que el host interpretaría como otra capa. */
_Static_assert(MAX_LAYER <= 8, "El mensaje 0xB4 lleva la capa en un byte con rango 0..7");

/* Anota la capa efectiva. Deliberadamente NO publica: esta función se llama
 * desde el hook de cambio de capa, que corre en pleno camino de procesado de
 * teclas; un raw_hid_send ahí puede costar hasta 100 ms y se sentiría como
 * teclas perdidas. La publicación la hace housekeeping_task_user por flanco. */
static inline void helm_anotar_capa(uint8_t capa) {
    g_helm_capa = capa;
}

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
/* ---- Filtro contra el temblor del sensor --------------------------------
 *
 * El trackpad capta ruido de la red eléctrica cuando el chasis del Mac flota
 * (basta tocarlo con la mano para que el temblor desaparezca: el cuerpo hace de
 * camino a tierra). El arreglo bueno es eléctrico, pero se puede atenuar mucho
 * aquí, y hay una razón física para que funcione: el ruido está en 50-60 Hz y
 * el movimiento humano no pasa de ~10 Hz. Son separables POR FRECUENCIA, que es
 * lo que hace inútil una zona muerta — el temblor y un movimiento lento tienen
 * amplitudes parecidas, pero no ritmos parecidos.
 *
 * Paso bajo exponencial en coma fija. ALFA_MIN fija el corte con el dedo
 * quieto: con este hook corriendo a 1 kHz, alfa/256 = 16/256 da unos 10 Hz,
 * justo debajo del ruido y por encima de cualquier gesto.
 *
 * El corte se ABRE con la velocidad para no añadir retardo al mover: un paso
 * bajo fijo a 10 Hz haría el puntero perezoso. La clave está en medir esa
 * velocidad sobre la señal YA FILTRADA y no sobre la cruda: el ruido tiene
 * media cero, así que al filtrarlo se cancela y en reposo la velocidad medida
 * es casi nula. Con la señal cruda el propio temblor abriría el filtro que
 * debía eliminarlo.
 *
 * DOS POLOS, no uno. Con un solo polo a 10 Hz el ruido de 50 Hz se atenúa unas
 * cinco veces, y eso dejaba temblor visible. Encadenar un segundo polo lleva la
 * atenuación a unas veinticinco, porque cada uno multiplica por su propia
 * caída. Sale mucho más barato en retardo que bajar el corte a la mitad: el
 * retardo crece de forma lineal con el número de polos, y la atenuación de
 * forma geométrica. */
#    define HELM_FILTRO_Q        8   // bits fraccionarios

/* Escalado con redondeo SIMÉTRICO, y no es un detalle.
 *
 * El desplazamiento de bits redondea hacia menos infinito, también con
 * negativos. En un filtro realimentado eso no se promedia: con entrada de media
 * cero, un valor positivo pequeño recibe un -1 que debía ser -0.1, y uno
 * negativo pequeño recibe un 0 que debía ser +0.1. El filtro se queda atascado
 * en un negativo pequeño en vez de en cero, ese residuo constante entra en el
 * acumulador de fracción y el puntero DERIVA solo hacia arriba y a la
 * izquierda. Visto en hardware antes de encontrarlo aquí.
 *
 * Redondeando al entero más cercano y tratando igual los dos signos, los
 * errores se reparten simétricos y una entrada de media cero vuelve a dar
 * salida de media cero. */
static inline int32_t helm_escala(int32_t valor, int32_t alfa) {
    const int32_t medio   = 1 << (HELM_FILTRO_Q - 1);
    const int32_t producto = valor * alfa;
    return producto >= 0 ? (producto + medio) >> HELM_FILTRO_Q
                         : -((-producto + medio) >> HELM_FILTRO_Q);
}

#    define HELM_FILTRO_ALFA_MIN 16  // dedo quieto: corte ~10 Hz
#    define HELM_FILTRO_PEND     24  // cuánto abre el corte por unidad de velocidad

/* ---- Compensación de deriva ---------------------------------------------
 *
 * Con el dedo apoyado y quieto, el sensor reporta un desplazamiento NETO
 * sostenido: medido en este teclado, 72 px hacia arriba en diez segundos, casi
 * todo en Y. No es temblor —el temblor tiene media cero y se cancela—, es una
 * componente continua, y por eso el paso bajo de arriba no la toca: la deriva
 * es baja frecuencia y atraviesa el filtro intacta. Suavizar más solo la hace
 * más visible al quitarle el ruido que la disimulaba.
 *
 * Origen probable: el acoplamiento de red no es uniforme sobre la superficie
 * del pad, así que el centroide que calcula el sensor se corre de forma
 * sistemática hacia donde el ruido es mayor.
 *
 * Se corrige restando una media MUY lenta del propio desplazamiento, que es un
 * bloqueador de continua. La clave es que esa media solo se actualiza CON EL
 * DEDO EN REPOSO: si se dejara correr durante un movimiento real acabaría
 * aprendiéndoselo y frenándolo, que es el fallo clásico de estos
 * compensadores. */
/* Media por BLOQUES, no media exponencial. El primer intento usaba una
 * exponencial con alfa muy pequeña y no funcionó: la deriva medida es de 0.007
 * px por ciclo, y el redondeo al entero más cercano descarta todo lo que no
 * llegue a medio paso, así que la base no se movía nunca. Sumar un bloque
 * entero y dividir al final no pierde nada, por pequeña que sea la señal. */
#    define HELM_BASE_BLOQUE 512  // ciclos por bloque (~0,5 s a 1 kHz)

report_mouse_t pointing_device_task_user(report_mouse_t report) {
    static mouse_xy_report_t pending_x = 0, pending_y = 0, out_x = 0, out_y = 0;
    static uint32_t          last_cycle = 0;
    static int32_t           filtro_x = 0, filtro_y = 0;   // Q8, primer polo
    static int32_t           filtro2_x = 0, filtro2_y = 0; // Q8, segundo polo
    static int32_t           base_x = 0, base_y = 0;       // Q8, deriva aprendida en reposo
    static int32_t           suma_x = 0, suma_y = 0;       // acumulador del bloque
    static uint16_t          bloque = 0;                   // ciclos acumulados
    static int32_t           resto_x = 0, resto_y = 0;     // Q8, fracción sin emitir

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
        filtro_x = filtro_y = filtro2_x = filtro2_y = base_x = base_y = resto_x = resto_y = 0;
        suma_x = suma_y = 0;
        bloque = 0;
        report.x = report.y = 0;
        report.h = report.v = 0;
        return report;
    }

    /* Con tres dedos o más nunca debe salir rueda: si se mantienen apoyados más
     * de un segundo el core devuelve el gesto al estado de scroll, y a partir de
     * ahí tres contactos caen en la rama de la rueda. */
    if (g_helm_contacts >= 3) {
        pending_x = pending_y = out_x = out_y = 0;
        filtro_x = filtro_y = filtro2_x = filtro2_y = base_x = base_y = resto_x = resto_y = 0;
        suma_x = suma_y = 0;
        bloque = 0;
        report.x = report.y = 0;
        report.h = report.v = 0;
        return report;
    }

    if (g_helm_contacts == 0) {
        // Tirar lo retenido: es el salto del despegue. El filtro también se
        // reinicia, para que el gesto siguiente no arrastre la cola de este.
        pending_x = pending_y = out_x = out_y = 0;
        filtro_x = filtro_y = filtro2_x = filtro2_y = base_x = base_y = resto_x = resto_y = 0;
        suma_x = suma_y = 0;
        bloque = 0;
        report.x = report.y = 0;
        return report;
    }

    // El guardia por milisegundo es necesario porque este hook se llama DOS
    // veces por ciclo (el módulo bk_pointing_device y pointing_device_task_kb).
    const uint32_t now = timer_read32();
    if (now != last_cycle) {
        last_cycle = now;

        /* Velocidad medida sobre lo YA filtrado: en reposo vale casi cero
           porque el ruido se cancela, así que el filtro se queda cerrado. */
        const int32_t vel  = (labs(filtro2_x) + labs(filtro2_y)) >> HELM_FILTRO_Q;
        int32_t       alfa = HELM_FILTRO_ALFA_MIN + vel * HELM_FILTRO_PEND;
        if (alfa > (1 << HELM_FILTRO_Q)) alfa = 1 << HELM_FILTRO_Q;

        filtro_x += helm_escala(((int32_t)report.x << HELM_FILTRO_Q) - filtro_x, alfa);
        filtro_y += helm_escala(((int32_t)report.y << HELM_FILTRO_Q) - filtro_y, alfa);
        filtro2_x += helm_escala(filtro_x - filtro2_x, alfa);
        filtro2_y += helm_escala(filtro_y - filtro2_y, alfa);

        /* La línea base solo aprende con el dedo quieto. En cuanto hay
           movimiento real se congela y el bloque en curso se descarta, para que
           no se aprenda el gesto. */
        if (vel == 0) {
            suma_x += filtro2_x;
            suma_y += filtro2_y;
            if (++bloque >= HELM_BASE_BLOQUE) {
                base_x = suma_x / HELM_BASE_BLOQUE;
                base_y = suma_y / HELM_BASE_BLOQUE;
                suma_x = suma_y = 0;
                bloque = 0;
            }
        } else {
            suma_x = suma_y = 0;
            bloque = 0;
        }

        /* Acumular la fracción: sin esto un movimiento lento se redondearía a
           cero en cada ciclo y el puntero no arrancaría nunca. */
        resto_x += filtro2_x - base_x;
        resto_y += filtro2_y - base_y;
        const int32_t paso_x = resto_x >> HELM_FILTRO_Q;
        const int32_t paso_y = resto_y >> HELM_FILTRO_Q;
        resto_x -= paso_x << HELM_FILTRO_Q;
        resto_y -= paso_y << HELM_FILTRO_Q;

        out_x     = pending_x;
        out_y     = pending_y;
        pending_x = (mouse_xy_report_t)paso_x;
        pending_y = (mouse_xy_report_t)paso_y;
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

    /* Capa activa. Mismo criterio que los otros dos mensajes: SOLO por flanco.
     * Si la capa cambia dos veces entre dos vueltas del bucle, el host recibe
     * únicamente la última, que es lo correcto: le interesa el estado, no el
     * historial. En el primer paso tras el arranque g_helm_capa_pub vale 0xFF,
     * así que se publica la capa real una vez sin esperar a que cambie; si el
     * USB todavía no está activo el envío retorna en el acto, sin bloquear. */
    if (g_helm_capa != g_helm_capa_pub) {
        g_helm_capa_pub = g_helm_capa;
        uint8_t msg[32] = {0};
        msg[0]          = HELM_MSG_CAPA;
        msg[1]          = g_helm_capa;
        raw_hid_send(msg, sizeof(msg)); // 32 bytes exactos: otra longitud se descarta en silencio
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

/* ------------------------------------------------------------------------
 * Hooks de cambio de capa.
 *
 * PUNTO DE ENGANCHE. layer_state_set_user es del keymap y está libre: el módulo
 * bastardkb/bk_pointing_device engancha su ajuste de precisión en
 * layer_state_set_bk_pointing_device, que cuelga de layer_state_set_modules,
 * una cadena distinta de la de usuario (quantum/action_layer.c llama primero a
 * los módulos, luego al teclado y este al usuario). Lo único que competía por
 * este nombre era el bloque de sniping automático que vivía arriba en este
 * mismo fichero, y por eso está fusionado aquí en lugar de duplicado.
 *
 * QUÉ ES «LA CAPA ACTIVA». get_highest_layer(layer_state | default_layer_state).
 * El OR no es adorno: esa es exactamente la máscara con la que QMK resuelve qué
 * keycode entrega una tecla en layer_switch_get_layer(), o sea la definición de
 * capa efectiva del propio firmware. layer_state por sí solo ignora la capa por
 * defecto; hoy esa es la 0 y daría igual, pero VIA está activo con 8 capas
 * dinámicas y basta un DF() asignado desde la interfaz para que la base deje de
 * ser la 0 y la señal empiece a mentir.
 *
 * Matiz asumido a propósito: get_highest_layer devuelve el bit más alto
 * encendido, mientras que layer_switch_get_layer va bajando y se salta las capas
 * cuya tecla concreta es transparente. Para dibujar la capa en pantalla queremos
 * lo primero — qué capa está puesta —, no lo segundo, que depende de qué tecla
 * se mire.
 *
 * NO SE ENVÍA DESDE AQUÍ. Este hook corre dentro del procesado de teclas y
 * raw_hid_send puede bloquear hasta 100 ms. Solo se anota un byte; publica
 * housekeeping_task_user, por flanco, como el resto de mensajes del fichero.
 *
 * La capa auto-mouse no necesita nada aparte: se enciende y apaga con
 * layer_on/layer_off, que pasan por layer_state_set y disparan este mismo hook
 * igual que un LT. En este keymap esa capa es la 4, LAYER_POINTER.
 * ------------------------------------------------------------------------ */
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
#    endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RAW_ENABLE
    /* Se lee el PARÁMETRO, no la global: layer_state_set asigna layer_state
     * DESPUÉS de llamar a los hooks, así que aquí dentro la global todavía tiene
     * el valor viejo. La capa por defecto sí se toma de su global, que esta
     * transición no cambia. */
    helm_anotar_capa(get_highest_layer(state | default_layer_state));
#endif // RAW_ENABLE

    return state;
}

/* Simétrico del anterior para la capa por defecto. Con el keymap tal cual está
 * no se ejecuta nunca —no hay ningún DF() en las siete capas—, pero VIA permite
 * reasignar teclas en caliente y un DF() puesto desde la interfaz cambiaría la
 * base sin tocar layer_state, dejando la señal congelada en la capa anterior.
 * Aquí el cruce es el inverso: la global es la de las capas momentáneas y el
 * parámetro es la capa por defecto que entra en vigor. */
layer_state_t default_layer_state_set_user(layer_state_t state) {
#ifdef RAW_ENABLE
    helm_anotar_capa(get_highest_layer(layer_state | state));
#endif // RAW_ENABLE

    return state;
}
