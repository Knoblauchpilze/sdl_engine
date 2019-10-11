#ifndef    KEY_UTILS_HH
# define   KEY_UTILS_HH

# include <cstdint>
# include <SDL2/SDL.h>
# include "KeyModifier.hh"

namespace sdl {
  namespace core {
    namespace engine {

      /**
       * @brief - Convenience enumeration describing the handled keys by this type of
       *          event. Any key that is not defined here will be mapped to the `None`
       *          value.
       *          Note that this describes physical keys as logical position on the
       *          keyboard: in order to get the full set of keys we need to account
       *          for the modifiers and the keyboard layout.
       */
      enum class RawKey {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Zero,

        Return,
        Escape,
        BackSpace,
        Tab,
        Space,

        Minus,
        Equals,
        LeftBracket,
        RightBracket,
        Backslash,
        /* SDL_SCANCODE_NONUSHASH */
        Semicolon,
        Apostrophe,
        Grave,
        Comma,
        Period,
        Slash,
        CapsLock,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        PrintScreen,
        ScrollLock,
        Pause,
        Insert,
        Home,
        PageUp,
        Delete,
        End,
        PageDown,
        Right,
        Left,
        Down,
        Up,

        NumLockClear,
        KPDivide,
        KPMultiply,
        KPMinus,
        KPPlus,
        KPEnter,
        KP1,
        KP2,
        KP3,
        KP4,
        KP5,
        KP6,
        KP7,
        KP8,
        KP9,
        KP0,
        KPPeriod,

        /* SDL_SCANCODE_NONUSBACKSLASH */
        /* SDL_SCANCODE_APPLICATION */
        /* SDL_SCANCODE_POWER */
        /* SDL_SCANCODE_KP_EQUALS */
        /* SDL_SCANCODE_F13 */
        /* SDL_SCANCODE_F14 */
        /* SDL_SCANCODE_F15 */
        /* SDL_SCANCODE_F16 */
        /* SDL_SCANCODE_F17 */
        /* SDL_SCANCODE_F18 */
        /* SDL_SCANCODE_F19 */
        /* SDL_SCANCODE_F20 */
        /* SDL_SCANCODE_F21 */
        /* SDL_SCANCODE_F22 */
        /* SDL_SCANCODE_F23 */
        /* SDL_SCANCODE_F24 */
        /* SDL_SCANCODE_EXECUTE */
        /* SDL_SCANCODE_HELP */
        /* SDL_SCANCODE_MENU */
        /* SDL_SCANCODE_SELECT */
        /* SDL_SCANCODE_STOP */
        /* SDL_SCANCODE_AGAIN */
        /* SDL_SCANCODE_UNDO */
        /* SDL_SCANCODE_CUT */
        /* SDL_SCANCODE_COPY */
        /* SDL_SCANCODE_PASTE */
        /* SDL_SCANCODE_FIND */
        /* SDL_SCANCODE_MUTE */
        /* SDL_SCANCODE_VOLUMEUP */
        /* SDL_SCANCODE_VOLUMEDOWN */

        /* SDL_SCANCODE_KP_COMMA */
        /* SDL_SCANCODE_KP_EQUALSAS400 */

        /* SDL_SCANCODE_INTERNATIONAL1 */
        /* SDL_SCANCODE_INTERNATIONAL2 */
        /* SDL_SCANCODE_INTERNATIONAL3 */
        /* SDL_SCANCODE_INTERNATIONAL4 */
        /* SDL_SCANCODE_INTERNATIONAL5 */
        /* SDL_SCANCODE_INTERNATIONAL6 */
        /* SDL_SCANCODE_INTERNATIONAL7 */
        /* SDL_SCANCODE_INTERNATIONAL8 */
        /* SDL_SCANCODE_INTERNATIONAL9 */
        /* SDL_SCANCODE_LANG1 */
        /* SDL_SCANCODE_LANG2 */
        /* SDL_SCANCODE_LANG3 */
        /* SDL_SCANCODE_LANG4 */
        /* SDL_SCANCODE_LANG5 */
        /* SDL_SCANCODE_LANG6 */
        /* SDL_SCANCODE_LANG7 */
        /* SDL_SCANCODE_LANG8 */
        /* SDL_SCANCODE_LANG9 */

        /* SDL_SCANCODE_ALTERASE */
        /* SDL_SCANCODE_SYSREQ */
        /* SDL_SCANCODE_CANCEL */
        /* SDL_SCANCODE_CLEAR */
        /* SDL_SCANCODE_PRIOR */
        /* SDL_SCANCODE_RETURN2 */
        /* SDL_SCANCODE_SEPARATOR */
        /* SDL_SCANCODE_OUT */
        /* SDL_SCANCODE_OPER */
        /* SDL_SCANCODE_CLEARAGAIN */
        /* SDL_SCANCODE_CRSEL */
        /* SDL_SCANCODE_EXSEL */

        /* SDL_SCANCODE_KP_00 */
        /* SDL_SCANCODE_KP_000 */
        /* SDL_SCANCODE_THOUSANDSSEPARATOR */
        /* SDL_SCANCODE_DECIMALSEPARATOR */
        /* SDL_SCANCODE_CURRENCYUNIT */
        /* SDL_SCANCODE_CURRENCYSUBUNIT */
        /* SDL_SCANCODE_KP_LEFTPAREN */
        /* SDL_SCANCODE_KP_RIGHTPAREN */
        /* SDL_SCANCODE_KP_LEFTBRACE */
        /* SDL_SCANCODE_KP_RIGHTBRACE */
        /* SDL_SCANCODE_KP_TAB */
        /* SDL_SCANCODE_KP_BACKSPACE */
        /* SDL_SCANCODE_KP_A */
        /* SDL_SCANCODE_KP_B */
        /* SDL_SCANCODE_KP_C */
        /* SDL_SCANCODE_KP_D */
        /* SDL_SCANCODE_KP_E */
        /* SDL_SCANCODE_KP_F */
        /* SDL_SCANCODE_KP_XOR */
        /* SDL_SCANCODE_KP_POWER */
        /* SDL_SCANCODE_KP_PERCENT */
        /* SDL_SCANCODE_KP_LESS */
        /* SDL_SCANCODE_KP_GREATER */
        /* SDL_SCANCODE_KP_AMPERSAND */
        /* SDL_SCANCODE_KP_DBLAMPERSAND */
        /* SDL_SCANCODE_KP_VERTICALBAR */
        /* SDL_SCANCODE_KP_DBLVERTICALBAR */
        /* SDL_SCANCODE_KP_COLON */
        /* SDL_SCANCODE_KP_HASH */
        /* SDL_SCANCODE_KP_SPACE */
        /* SDL_SCANCODE_KP_AT */
        /* SDL_SCANCODE_KP_EXCLAM */
        /* SDL_SCANCODE_KP_MEMSTORE */
        /* SDL_SCANCODE_KP_MEMRECALL */
        /* SDL_SCANCODE_KP_MEMCLEAR */
        /* SDL_SCANCODE_KP_MEMADD */
        /* SDL_SCANCODE_KP_MEMSUBTRACT */
        /* SDL_SCANCODE_KP_MEMMULTIPLY */
        /* SDL_SCANCODE_KP_MEMDIVIDE */
        /* SDL_SCANCODE_KP_PLUSMINUS */
        /* SDL_SCANCODE_KP_CLEAR */
        /* SDL_SCANCODE_KP_CLEARENTRY */
        /* SDL_SCANCODE_KP_BINARY */
        /* SDL_SCANCODE_KP_OCTAL */
        /* SDL_SCANCODE_KP_DECIMAL */
        /* SDL_SCANCODE_KP_HEXADECIMAL */

        LeftCtrl,
        LeftShift,
        LeftAlt,
        LeftCommand,
        RightCtrl,
        RightShift,
        RightAlt,
        RightCommand,

        /* SDL_SCANCODE_MODE */
        /* SDL_SCANCODE_AUDIONEXT */
        /* SDL_SCANCODE_AUDIOPREV */
        /* SDL_SCANCODE_AUDIOSTOP */
        /* SDL_SCANCODE_AUDIOPLAY */
        /* SDL_SCANCODE_AUDIOMUTE */
        /* SDL_SCANCODE_MEDIASELECT */
        /* SDL_SCANCODE_WWW */
        /* SDL_SCANCODE_MAIL */
        /* SDL_SCANCODE_CALCULATOR */
        /* SDL_SCANCODE_COMPUTER */
        /* SDL_SCANCODE_AC_SEARCH */
        /* SDL_SCANCODE_AC_HOME */
        /* SDL_SCANCODE_AC_BACK */
        /* SDL_SCANCODE_AC_FORWARD */
        /* SDL_SCANCODE_AC_STOP */
        /* SDL_SCANCODE_AC_REFRESH */
        /* SDL_SCANCODE_AC_BOOKMARKS */

        /* SDL_SCANCODE_BRIGHTNESSDOWN */
        /* SDL_SCANCODE_BRIGHTNESSUP */
        /* SDL_SCANCODE_DISPLAYSWITCH */
        /* SDL_SCANCODE_KBDILLUMTOGGLE */
        /* SDL_SCANCODE_KBDILLUMDOWN */
        /* SDL_SCANCODE_KBDILLUMUP */
        /* SDL_SCANCODE_EJECT */
        /* SDL_SCANCODE_SLEEP */

        /* SDL_SCANCODE_APP1 */
        /* SDL_SCANCODE_APP2 */

        /* SDL_SCANCODE_AUDIOREWIND */
        /* SDL_SCANCODE_AUDIOFASTFORWARD */
        /* SDL_NUM_SCANCODES */

        None
      };

      /**
       * @brief - Convenience enumeration describing the handled keys by this type
       *          of event. Note that compared to the `RawKey` state we add some more
       *          keys which comes from interpretation of the keyboard layout. As an
       *          example the `Ampersand` key is not part of the `RawKey` enumeration
       *          because there's no physical keys linked to it, but it is part of the
       *          interpreted keys as the french layout as a logical key (matching a
       *          physical key defined in `RawKey`) which is an `Ampersand`.
       */
      enum class Key {
        SDLK_RETURN = '\r',
        SDLK_ESCAPE = '\033',
        SDLK_BACKSPACE = '\b',
        SDLK_TAB = '\t',
        SDLK_SPACE = ' ',
        SDLK_EXCLAIM = '!',
        SDLK_QUOTEDBL = '"',
        SDLK_HASH = '#',
        SDLK_PERCENT = '%',
        SDLK_DOLLAR = '$',
        SDLK_AMPERSAND = '&',
        SDLK_QUOTE = '\'',
        SDLK_LEFTPAREN = '(',
        SDLK_RIGHTPAREN = ')',
        SDLK_ASTERISK = '*',
        SDLK_PLUS = '+',
        SDLK_COMMA = ',',
        SDLK_MINUS = '-',
        SDLK_PERIOD = '.',
        SDLK_SLASH = '/',
        SDLK_0 = '0',
        SDLK_1 = '1',
        SDLK_2 = '2',
        SDLK_3 = '3',
        SDLK_4 = '4',
        SDLK_5 = '5',
        SDLK_6 = '6',
        SDLK_7 = '7',
        SDLK_8 = '8',
        SDLK_9 = '9',
        SDLK_COLON = ':',
        SDLK_SEMICOLON = ';',
        SDLK_LESS = '<',
        SDLK_EQUALS = '=',
        SDLK_GREATER = '>',
        SDLK_QUESTION = '?',
        SDLK_AT = '@',
        /*
          Skip uppercase letters
        */
        SDLK_LEFTBRACKET = '[',
        SDLK_BACKSLASH = '\\',
        SDLK_RIGHTBRACKET = ']',
        SDLK_CARET = '^',
        SDLK_UNDERSCORE = '_',
        SDLK_BACKQUOTE = '`',
        SDLK_a = 'a',
        SDLK_b = 'b',
        SDLK_c = 'c',
        SDLK_d = 'd',
        SDLK_e = 'e',
        SDLK_f = 'f',
        SDLK_g = 'g',
        SDLK_h = 'h',
        SDLK_i = 'i',
        SDLK_j = 'j',
        SDLK_k = 'k',
        SDLK_l = 'l',
        SDLK_m = 'm',
        SDLK_n = 'n',
        SDLK_o = 'o',
        SDLK_p = 'p',
        SDLK_q = 'q',
        SDLK_r = 'r',
        SDLK_s = 's',
        SDLK_t = 't',
        SDLK_u = 'u',
        SDLK_v = 'v',
        SDLK_w = 'w',
        SDLK_x = 'x',
        SDLK_y = 'y',
        SDLK_z = 'z',

        SDLK_CAPSLOCK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK),

        SDLK_F1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1),
        SDLK_F2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2),
        SDLK_F3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3),
        SDLK_F4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4),
        SDLK_F5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5),
        SDLK_F6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6),
        SDLK_F7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7),
        SDLK_F8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8),
        SDLK_F9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9),
        SDLK_F10 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10),
        SDLK_F11 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11),
        SDLK_F12 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12),

        SDLK_PRINTSCREEN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN),
        SDLK_SCROLLLOCK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK),
        SDLK_PAUSE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE),
        SDLK_INSERT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT),
        SDLK_HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME),
        SDLK_PAGEUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP),
        SDLK_DELETE = '\177',
        SDLK_END = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END),
        SDLK_PAGEDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN),
        SDLK_RIGHT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
        SDLK_LEFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
        SDLK_DOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
        SDLK_UP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),

        SDLK_NUMLOCKCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR),
        SDLK_KP_DIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE),
        SDLK_KP_MULTIPLY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY),
        SDLK_KP_MINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
        SDLK_KP_PLUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
        SDLK_KP_ENTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
        SDLK_KP_1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
        SDLK_KP_2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
        SDLK_KP_3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
        SDLK_KP_4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
        SDLK_KP_5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
        SDLK_KP_6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
        SDLK_KP_7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
        SDLK_KP_8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
        SDLK_KP_9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
        SDLK_KP_0 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
        SDLK_KP_PERIOD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),

        SDLK_APPLICATION = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION),
        SDLK_POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER),
        SDLK_KP_EQUALS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS),
        SDLK_F13 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13),
        SDLK_F14 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14),
        SDLK_F15 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15),
        SDLK_F16 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16),
        SDLK_F17 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17),
        SDLK_F18 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18),
        SDLK_F19 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19),
        SDLK_F20 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20),
        SDLK_F21 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21),
        SDLK_F22 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22),
        SDLK_F23 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23),
        SDLK_F24 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24),
        SDLK_EXECUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE),
        SDLK_HELP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HELP),
        SDLK_MENU = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU),
        SDLK_SELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT),
        SDLK_STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP),
        SDLK_AGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN),
        SDLK_UNDO = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO),
        SDLK_CUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT),
        SDLK_COPY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY),
        SDLK_PASTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE),
        SDLK_FIND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND),
        SDLK_MUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE),
        SDLK_VOLUMEUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP),
        SDLK_VOLUMEDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN),
        SDLK_KP_COMMA = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA),
        SDLK_KP_EQUALSAS400 =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),

        SDLK_ALTERASE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE),
        SDLK_SYSREQ = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ),
        SDLK_CANCEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL),
        SDLK_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR),
        SDLK_PRIOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR),
        SDLK_RETURN2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RETURN2),
        SDLK_SEPARATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR),
        SDLK_OUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT),
        SDLK_OPER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER),
        SDLK_CLEARAGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN),
        SDLK_CRSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL),
        SDLK_EXSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL),

        SDLK_KP_00 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00),
        SDLK_KP_000 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000),
        SDLK_THOUSANDSSEPARATOR =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
        SDLK_DECIMALSEPARATOR =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
        SDLK_CURRENCYUNIT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT),
        SDLK_CURRENCYSUBUNIT =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
        SDLK_KP_LEFTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN),
        SDLK_KP_RIGHTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN),
        SDLK_KP_LEFTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE),
        SDLK_KP_RIGHTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE),
        SDLK_KP_TAB = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB),
        SDLK_KP_BACKSPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE),
        SDLK_KP_A = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A),
        SDLK_KP_B = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B),
        SDLK_KP_C = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C),
        SDLK_KP_D = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D),
        SDLK_KP_E = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E),
        SDLK_KP_F = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F),
        SDLK_KP_XOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR),
        SDLK_KP_POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER),
        SDLK_KP_PERCENT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT),
        SDLK_KP_LESS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS),
        SDLK_KP_GREATER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER),
        SDLK_KP_AMPERSAND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND),
        SDLK_KP_DBLAMPERSAND =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
        SDLK_KP_VERTICALBAR =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
        SDLK_KP_DBLVERTICALBAR =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
        SDLK_KP_COLON = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON),
        SDLK_KP_HASH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH),
        SDLK_KP_SPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE),
        SDLK_KP_AT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT),
        SDLK_KP_EXCLAM = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM),
        SDLK_KP_MEMSTORE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE),
        SDLK_KP_MEMRECALL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL),
        SDLK_KP_MEMCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR),
        SDLK_KP_MEMADD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD),
        SDLK_KP_MEMSUBTRACT =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
        SDLK_KP_MEMMULTIPLY =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
        SDLK_KP_MEMDIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE),
        SDLK_KP_PLUSMINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS),
        SDLK_KP_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR),
        SDLK_KP_CLEARENTRY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY),
        SDLK_KP_BINARY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY),
        SDLK_KP_OCTAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL),
        SDLK_KP_DECIMAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL),
        SDLK_KP_HEXADECIMAL =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),

        SDLK_LCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL),
        SDLK_LSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT),
        SDLK_LALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT),
        SDLK_LGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI),
        SDLK_RCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL),
        SDLK_RSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT),
        SDLK_RALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT),
        SDLK_RGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI),

        SDLK_MODE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE),

        SDLK_AUDIONEXT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIONEXT),
        SDLK_AUDIOPREV = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPREV),
        SDLK_AUDIOSTOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOSTOP),
        SDLK_AUDIOPLAY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPLAY),
        SDLK_AUDIOMUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOMUTE),
        SDLK_MEDIASELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIASELECT),
        SDLK_WWW = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WWW),
        SDLK_MAIL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MAIL),
        SDLK_CALCULATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALCULATOR),
        SDLK_COMPUTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COMPUTER),
        SDLK_AC_SEARCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH),
        SDLK_AC_HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME),
        SDLK_AC_BACK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK),
        SDLK_AC_FORWARD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD),
        SDLK_AC_STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP),
        SDLK_AC_REFRESH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH),
        SDLK_AC_BOOKMARKS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS),

        SDLK_BRIGHTNESSDOWN =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
        SDLK_BRIGHTNESSUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSUP),
        SDLK_DISPLAYSWITCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DISPLAYSWITCH),
        SDLK_KBDILLUMTOGGLE =
            SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
        SDLK_KBDILLUMDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMDOWN),
        SDLK_KBDILLUMUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMUP),
        SDLK_EJECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EJECT),
        SDLK_SLEEP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP),
        SDLK_APP1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP1),
        SDLK_APP2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP2),

        SDLK_AUDIOREWIND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOREWIND),
        SDLK_AUDIOFASTFORWARD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOFASTFORWARD)
      };

      /**
       * @brief - Converts the input `SDL` scan code to an equivalent key enumeration. If no such
       *          conversion can be performed the value `None` is used.
       *          Note that a scan code is linked to a physical position of a key on the keyboard
       *          and does not take into consideration the layout of the keyboard.
       * @param k - the `SDL` scan code to convert.
       * @return - the enumeration value corresponding to the input `SDL` code or `None` if no
       *           such value exist.
       */
      RawKey
      fromSDLScancode(const SDL_Scancode& k);

      /**
       * @brief - Converts the input `SDL` key modifier to an equivalent enumeration. If no such
       *          conversion can be performed the value `None` is used.
       * @param m - the `SDL` modifier to convert.
       * @return - the enumeration value corresponding to the input `SDL` code or `None` if no
       *           such value exist.
       */
      KeyModifier
      fromSDLMod(std::uint16_t m);

      /**
       * @brief - Used to determine whether the input key corresponds to a alphanumeric character.
       * @param k - the key which should be checked for the alphanumeric status.
       * @return - `true` if the key is alphanumeric (i.e. belongs to `[a-A-Z0-9]`) and `false` if
       *           this is not the case.
       */
      bool
      isKeyAlphanumeric(const Key& k) noexcept;

      /**
       * @brief - Used to determine whether the input key can be displayed or not. This allows to
       *          filter special key which do not have a visual representation (like modifiers and
       *          motion keys).
       * @param k - the key which should be checked for displayability.
       * @return - `true` if the key can be displayed and `false` if this is not the case.
       */
      bool
      isKeyPrintable(const Key& k) noexcept;

      /**
       * @brief - Returns the character value associated to the input key. Works well for alphanumeric
       *          characters and return '\0' for non alphanumeric values.
       *          Note that one can check whether a character is alphanumeric using the above method.
       * @param k - the key for which the corresponding character should be retrieved.
       * @param m - the modifier currently set. Might modify the corresponding character returned.
       * @return - the character corresponding to the input key or '\0' if no character can be associated
       *           to the key.
       */
      char
      getCharFromKey(const Key& k,
                     const KeyModifier& m) noexcept;

    }
  }
}

# include "KeyUtils.hxx"

#endif    /* KEY_UTILS_HH */
