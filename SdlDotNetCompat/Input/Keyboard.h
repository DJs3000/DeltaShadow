#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL_stdinc.h>
#include <SDL_keysym.h>
#include <SDL.h>

namespace SdlDotNetCompat {
namespace Input {

enum Key
{
    /// <summary>
    ///Unknown
    /// </summary>
    Unknown = SDLK_UNKNOWN,
    /// <summary>
    /// first
    /// </summary>
    First = Unknown,
    /// <summary>
    /// backspace. '\b'
    /// </summary>
    Backspace = SDLK_BACKSPACE,
    /// <summary>
    /// tab. '\t'
    /// </summary>
    Tab = SDLK_TAB,
    /// <summary>
    /// clear
    /// </summary>
    Clear = SDLK_CLEAR,
    /// <summary>
    /// return. '\r'
    /// </summary>
    Return = SDLK_RETURN,
    /// <summary>
    /// pause
    /// </summary>
    Pause = SDLK_PAUSE,
    /// <summary>
    /// escape. '^['
    /// </summary>
    Escape = SDLK_ESCAPE,
    /// <summary>
    /// space. ' '
    /// </summary>
    Space = SDLK_SPACE,
    /// <summary>
    /// exclaim. '!'
    /// </summary>
    ExclamationPoint = SDLK_EXCLAIM,
    /// <summary>
    /// quotedbl. '"'
    /// </summary>
    DoubleQuote = SDLK_QUOTEDBL,
    /// <summary>
    /// hash. '#'
    /// </summary>
    Hash = SDLK_HASH,
    /// <summary>
    /// dollar. '$'
    /// </summary>
    DollarSign = SDLK_DOLLAR,
    /// <summary>
    /// ampersand. '&amp;'
    /// </summary>
    Ampersand = SDLK_AMPERSAND,
    /// <summary>
    /// quote. '''
    /// </summary>
    Quote = SDLK_QUOTE,
    /// <summary>
    /// left parenthesis. '('
    /// </summary>
    LeftParenthesis = SDLK_LEFTPAREN,
    /// <summary>
    /// right parenthesis. ')'
    /// </summary>
    RightParenthesis = SDLK_RIGHTPAREN,
    /// <summary>
    /// asterisk. '*'
    /// </summary>
    Asterisk = SDLK_ASTERISK,
    /// <summary>
    /// plus sign. '+'
    /// </summary>
    Plus = SDLK_PLUS,
    /// <summary>
    /// comma. ','
    /// </summary>
    Comma = SDLK_COMMA,
    /// <summary>
    /// minus sign. '-'
    /// </summary>
    Minus = SDLK_MINUS,
    /// <summary>
    /// period. '.'
    /// </summary>
    Period = SDLK_PERIOD,
    /// <summary>
    /// forward slash. '/'
    /// </summary>
    Slash = SDLK_SLASH,
    /// <summary>
    /// 0
    /// </summary>
    Zero = SDLK_0,
    /// <summary>
    /// 1
    /// </summary>
    One = SDLK_1,
    /// <summary>
    /// 2
    /// </summary>
    Two = SDLK_2,
    /// <summary>
    /// 3
    /// </summary>
    Three = SDLK_3,
    /// <summary>
    /// 4
    /// </summary>
    Four = SDLK_4,
    /// <summary>
    /// 5
    /// </summary>
    Five = SDLK_5,
    /// <summary>
    /// 6
    /// </summary>
    Six = SDLK_6,
    /// <summary>
    /// 7
    /// </summary>
    Seven = SDLK_7,
    /// <summary>
    /// 8
    /// </summary>
    Eight = SDLK_8,
    /// <summary>
    /// 9
    /// </summary>
    Nine = SDLK_9,
    /// <summary>
    /// colon. ':'
    /// </summary>
    Colon = SDLK_COLON,
    /// <summary>
    /// semicolon. ';'
    /// </summary>
    Semicolon = SDLK_SEMICOLON,
    /// <summary>
    /// less-than sign. '&lt;'
    /// </summary>
    LessThan = SDLK_LESS,
    /// <summary>
    /// equals sign. '='
    /// </summary>
    Equals = SDLK_EQUALS,
    /// <summary>
    /// greater-than sign. '&gt;'
    /// </summary>
    GreaterThan = SDLK_GREATER,
    /// <summary>
    /// question mark. '?'
    /// </summary>
    QuestionMark = SDLK_QUESTION,
    /// <summary>
    /// at. '@'
    /// </summary>
    At = SDLK_AT,
    /*
    Skip uppercase letters
    */
    /// <summary>
    /// left bracket. '['
    /// </summary>
    LeftBracket = SDLK_LEFTBRACKET,
    /// <summary>
    /// backslash. '\'
    /// </summary>
    Backslash = SDLK_BACKSLASH,
    /// <summary>
    /// right bracket. ']'
    /// </summary>
    RightBracket = SDLK_RIGHTBRACKET,
    /// <summary>
    /// caret. '^'
    /// </summary>
    Caret = SDLK_CARET,
    /// <summary>
    /// underscore.'_'
    /// </summary>
    Underscore = SDLK_UNDERSCORE,
    /// <summary>
    /// grave. '`'
    /// </summary>
    BackQuote = SDLK_BACKQUOTE,
    /// <summary>
    /// a
    /// </summary>
    A = SDLK_a,
    /// <summary>
    /// b
    /// </summary>
    B = SDLK_b,
    /// <summary>
    /// c
    /// </summary>
    C = SDLK_c,
    /// <summary>
    /// d
    /// </summary>
    D = SDLK_d,
    /// <summary>
    /// e
    /// </summary>
    E = SDLK_e,
    /// <summary>
    /// f
    /// </summary>
    F = SDLK_f,
    /// <summary>
    /// g
    /// </summary>
    G = SDLK_g,
    /// <summary>
    /// h
    /// </summary>
    H = SDLK_h,
    /// <summary>
    /// i
    /// </summary>
    I = SDLK_i,
    /// <summary>
    /// j
    /// </summary>
    J = SDLK_j,
    /// <summary>
    /// k
    /// </summary>
    K = SDLK_k,
    /// <summary>
    /// l
    /// </summary>
    L = SDLK_l,
    /// <summary>
    /// m
    /// </summary>
    M = SDLK_m,
    /// <summary>
    /// n
    /// </summary>
    N = SDLK_n,
    /// <summary>
    /// o
    /// </summary>
    O = SDLK_o,
    /// <summary>
    /// p
    /// </summary>
    P = SDLK_p,
    /// <summary>
    /// q
    /// </summary>
    Q = SDLK_q,
    /// <summary>
    /// r
    /// </summary>
    R = SDLK_r,
    /// <summary>
    /// s
    /// </summary>
    S = SDLK_s,
    /// <summary>
    /// t
    /// </summary>
    T = SDLK_t,
    /// <summary>
    /// u
    /// </summary>
    U = SDLK_u,
    /// <summary>
    /// v
    /// </summary>
    V = SDLK_v,
    /// <summary>
    /// w
    /// </summary>
    W = SDLK_w,
    /// <summary>
    /// x
    /// </summary>
    X = SDLK_x,
    /// <summary>
    /// y
    /// </summary>
    Y = SDLK_y,
    /// <summary>
    /// z
    /// </summary>
    Z = SDLK_z,
    /// <summary>
    /// delete. '^?'
    /// </summary>
    Delete = SDLK_DELETE,
    /* End of ASCII mapped keysyms */

    /* International keyboard syms */
    /// <summary>
    /// 0xA0
    /// </summary>
    World0 = SDLK_WORLD_0,
    /// <summary>
    ///
    /// </summary>
    World1 = SDLK_WORLD_1,
    /// <summary>
    ///
    /// </summary>
    World2 = SDLK_WORLD_2,
    /// <summary>
    ///
    /// </summary>
    World3 = SDLK_WORLD_3,
    /// <summary>
    ///
    /// </summary>
    World4 = SDLK_WORLD_4,
    /// <summary>
    ///
    /// </summary>
    World5 = SDLK_WORLD_5,
    /// <summary>
    ///
    /// </summary>
    World6 = SDLK_WORLD_6,
    /// <summary>
    ///
    /// </summary>
    World7 = SDLK_WORLD_7,
    /// <summary>
    ///
    /// </summary>
    World8 = SDLK_WORLD_8,
    /// <summary>
    ///
    /// </summary>
    World9 = SDLK_WORLD_9,
    /// <summary>
    ///
    /// </summary>
    World10 = SDLK_WORLD_10,
    /// <summary>
    ///
    /// </summary>
    World11 = SDLK_WORLD_11,
    /// <summary>
    ///
    /// </summary>
    World12 = SDLK_WORLD_12,
    /// <summary>
    ///
    /// </summary>
    World13 = SDLK_WORLD_13,
    /// <summary>
    ///
    /// </summary>
    World14 = SDLK_WORLD_14,
    /// <summary>
    ///
    /// </summary>
    World15 = SDLK_WORLD_15,
    /// <summary>
    ///
    /// </summary>
    World16 = SDLK_WORLD_16,
    /// <summary>
    ///
    /// </summary>
    World17 = SDLK_WORLD_17,
    /// <summary>
    ///
    /// </summary>
    World18 = SDLK_WORLD_18,
    /// <summary>
    ///
    /// </summary>
    World19 = SDLK_WORLD_19,
    /// <summary>
    ///
    /// </summary>
    World20 = SDLK_WORLD_20,
    /// <summary>
    ///
    /// </summary>
    World21 = SDLK_WORLD_21,
    /// <summary>
    ///
    /// </summary>
    World22 = SDLK_WORLD_22,
    /// <summary>
    ///
    /// </summary>
    World23 = SDLK_WORLD_23,
    /// <summary>
    ///
    /// </summary>
    World24 = SDLK_WORLD_24,
    /// <summary>
    ///
    /// </summary>
    World25 = SDLK_WORLD_25,
    /// <summary>
    ///
    /// </summary>
    World26 = SDLK_WORLD_26,
    /// <summary>
    ///
    /// </summary>
    World27 = SDLK_WORLD_27,
    /// <summary>
    ///
    /// </summary>
    World28 = SDLK_WORLD_28,
    /// <summary>
    ///
    /// </summary>
    World29 = SDLK_WORLD_29,
    /// <summary>
    ///
    /// </summary>
    World30 = SDLK_WORLD_30,
    /// <summary>
    ///
    /// </summary>
    World31 = SDLK_WORLD_31,
    /// <summary>
    ///
    /// </summary>
    World32 = SDLK_WORLD_32,
    /// <summary>
    ///
    /// </summary>
    World33 = SDLK_WORLD_33,
    /// <summary>
    ///
    /// </summary>
    World34 = SDLK_WORLD_34,
    /// <summary>
    ///
    /// </summary>
    World35 = SDLK_WORLD_35,
    /// <summary>
    ///
    /// </summary>
    World36 = SDLK_WORLD_36,
    /// <summary>
    ///
    /// </summary>
    World37 = SDLK_WORLD_37,
    /// <summary>
    ///
    /// </summary>
    World38 = SDLK_WORLD_38,
    /// <summary>
    ///
    /// </summary>
    World39 = SDLK_WORLD_39,
    /// <summary>
    ///
    /// </summary>
    World40 = SDLK_WORLD_40,
    /// <summary>
    ///
    /// </summary>
    World41 = SDLK_WORLD_41,
    /// <summary>
    ///
    /// </summary>
    World42 = SDLK_WORLD_42,
    /// <summary>
    ///
    /// </summary>
    World43 = SDLK_WORLD_43,
    /// <summary>
    ///
    /// </summary>
    World44 = SDLK_WORLD_44,
    /// <summary>
    ///
    /// </summary>
    World45 = SDLK_WORLD_45,
    /// <summary>
    ///
    /// </summary>
    World46 = SDLK_WORLD_46,
    /// <summary>
    ///
    /// </summary>
    World47 = SDLK_WORLD_47,
    /// <summary>
    ///
    /// </summary>
    World48 = SDLK_WORLD_48,
    /// <summary>
    ///
    /// </summary>
    World49 = SDLK_WORLD_49,
    /// <summary>
    ///
    /// </summary>
    World50 = SDLK_WORLD_50,
    /// <summary>
    ///
    /// </summary>
    World51 = SDLK_WORLD_51,
    /// <summary>
    ///
    /// </summary>
    World52 = SDLK_WORLD_52,
    /// <summary>
    ///
    /// </summary>
    World53 = SDLK_WORLD_53,
    /// <summary>
    ///
    /// </summary>
    World54 = SDLK_WORLD_54,
    /// <summary>
    ///
    /// </summary>
    World55 = SDLK_WORLD_55,
    /// <summary>
    ///
    /// </summary>
    World56 = SDLK_WORLD_56,
    /// <summary>
    ///
    /// </summary>
    World57 = SDLK_WORLD_57,
    /// <summary>
    ///
    /// </summary>
    World58 = SDLK_WORLD_58,
    /// <summary>
    ///
    /// </summary>
    World59 = SDLK_WORLD_59,
    /// <summary>
    ///
    /// </summary>
    World60 = SDLK_WORLD_60,
    /// <summary>
    ///
    /// </summary>
    World61 = SDLK_WORLD_61,
    /// <summary>
    ///
    /// </summary>
    World62 = SDLK_WORLD_62,
    /// <summary>
    ///
    /// </summary>
    World63 = SDLK_WORLD_63,
    /// <summary>
    ///
    /// </summary>
    World64 = SDLK_WORLD_64,
    /// <summary>
    ///
    /// </summary>
    World65 = SDLK_WORLD_65,
    /// <summary>
    ///
    /// </summary>
    World66 = SDLK_WORLD_66,
    /// <summary>
    ///
    /// </summary>
    World67 = SDLK_WORLD_67,
    /// <summary>
    ///
    /// </summary>
    World68 = SDLK_WORLD_68,
    /// <summary>
    ///
    /// </summary>
    World69 = SDLK_WORLD_69,
    /// <summary>
    ///
    /// </summary>
    World70 = SDLK_WORLD_70,
    /// <summary>
    ///
    /// </summary>
    World71 = SDLK_WORLD_71,
    /// <summary>
    ///
    /// </summary>
    World72 = SDLK_WORLD_72,
    /// <summary>
    ///
    /// </summary>
    World73 = SDLK_WORLD_73,
    /// <summary>
    ///
    /// </summary>
    World74 = SDLK_WORLD_74,
    /// <summary>
    ///
    /// </summary>
    World75 = SDLK_WORLD_75,
    /// <summary>
    ///
    /// </summary>
    World76 = SDLK_WORLD_76,
    /// <summary>
    ///
    /// </summary>
    World77 = SDLK_WORLD_77,
    /// <summary>
    ///
    /// </summary>
    World78 = SDLK_WORLD_78,
    /// <summary>
    ///
    /// </summary>
    World79 = SDLK_WORLD_79,
    /// <summary>
    ///
    /// </summary>
    World80 = SDLK_WORLD_80,
    /// <summary>
    ///
    /// </summary>
    World81 = SDLK_WORLD_81,
    /// <summary>
    ///
    /// </summary>
    World82 = SDLK_WORLD_82,
    /// <summary>
    ///
    /// </summary>
    World83 = SDLK_WORLD_83,
    /// <summary>
    ///
    /// </summary>
    World84 = SDLK_WORLD_84,
    /// <summary>
    ///
    /// </summary>
    World85 = SDLK_WORLD_85,
    /// <summary>
    ///
    /// </summary>
    World86 = SDLK_WORLD_86,
    /// <summary>
    ///
    /// </summary>
    World87 = SDLK_WORLD_87,
    /// <summary>
    ///
    /// </summary>
    World88 = SDLK_WORLD_88,
    /// <summary>
    ///
    /// </summary>
    World89 = SDLK_WORLD_89,
    /// <summary>
    ///
    /// </summary>
    World90 = SDLK_WORLD_90,
    /// <summary>
    ///
    /// </summary>
    World91 = SDLK_WORLD_91,
    /// <summary>
    ///
    /// </summary>
    World92 = SDLK_WORLD_92,
    /// <summary>
    ///
    /// </summary>
    World93 = SDLK_WORLD_93,
    /// <summary>
    ///
    /// </summary>
    World94 = SDLK_WORLD_94,
    /// <summary>
    /// 0xFF
    /// </summary>
    World95 = SDLK_WORLD_95,

    /* Numeric keypad */
    /// <summary>
    /// keypad 0
    /// </summary>
    Keypad0 = SDLK_KP0,
    /// <summary>
    /// keypad 1
    /// </summary>
    Keypad1 = SDLK_KP1,
    /// <summary>
    /// keypad 2
    /// </summary>
    Keypad2 = SDLK_KP2,
    /// <summary>
    /// keypad 3
    /// </summary>
    Keypad3 = SDLK_KP3,
    /// <summary>
    /// keypad 4
    /// </summary>
    Keypad4 = SDLK_KP4,
    /// <summary>
    /// keypad 5
    /// </summary>
    Keypad5 = SDLK_KP5,
    /// <summary>
    /// keypad 6
    /// </summary>
    Keypad6 = SDLK_KP6,
    /// <summary>
    /// keypad 7
    /// </summary>
    Keypad7 = SDLK_KP7,
    /// <summary>
    /// keypad 8
    /// </summary>
    Keypad8 = SDLK_KP8,
    /// <summary>
    /// keypad 9
    /// </summary>
    Keypad9 = SDLK_KP9,
    /// <summary>
    /// keypad period. '.'
    /// </summary>
    KeypadPeriod = SDLK_KP_PERIOD,
    /// <summary>
    /// keypad divide. '/'
    /// </summary>
    KeypadDivide = SDLK_KP_DIVIDE,
    /// <summary>
    /// keypad multiply. '*'
    /// </summary>
    KeypadMultiply = SDLK_KP_MULTIPLY,
    /// <summary>
    /// keypad minus. '-'
    /// </summary>
    KeypadMinus = SDLK_KP_MINUS,
    /// <summary>
    /// keypad plus. '+'
    /// </summary>
    KeypadPlus = SDLK_KP_PLUS,
    /// <summary>
    /// keypad enter. '\r'
    /// </summary>
    KeypadEnter = SDLK_KP_ENTER,
    /// <summary>
    /// keypad equals. '='
    /// </summary>
    KeypadEquals = SDLK_KP_EQUALS,

    /* Arrows + Home/End pad */
    /// <summary>
    /// up arrow
    /// </summary>
    UpArrow = SDLK_UP,
    /// <summary>
    /// down arrow
    /// </summary>
    DownArrow = SDLK_DOWN,
    /// <summary>
    /// right arrow
    /// </summary>
    RightArrow = SDLK_RIGHT,
    /// <summary>
    /// left arrow
    /// </summary>
    LeftArrow = SDLK_LEFT,
    /// <summary>
    /// insert
    /// </summary>
    Insert = SDLK_INSERT,
    /// <summary>
    /// home
    /// </summary>
    Home = SDLK_HOME,
    /// <summary>
    /// end
    /// </summary>
    End = SDLK_END,
    /// <summary>
    /// page up
    /// </summary>
    PageUp = SDLK_PAGEUP,
    /// <summary>
    /// page down
    /// </summary>
    PageDown = SDLK_PAGEDOWN,

    /* Function keys */
    /// <summary>
    /// F1
    /// </summary>
    F1 = SDLK_F1,
    /// <summary>
    /// F2
    /// </summary>
    F2 = SDLK_F2,
    /// <summary>
    /// F3
    /// </summary>
    F3 = SDLK_F3,
    /// <summary>
    /// F4
    /// </summary>
    F4 = SDLK_F4,
    /// <summary>
    /// F5
    /// </summary>
    F5 = SDLK_F5,
    /// <summary>
    /// F6
    /// </summary>
    F6 = SDLK_F6,
    /// <summary>
    /// F7
    /// </summary>
    F7 = SDLK_F7,
    /// <summary>
    /// F8
    /// </summary>
    F8 = SDLK_F8,
    /// <summary>
    /// F9
    /// </summary>
    F9 = SDLK_F9,
    /// <summary>
    /// F10
    /// </summary>
    F10 = SDLK_F10,
    /// <summary>
    /// F11
    /// </summary>
    F11 = SDLK_F11,
    /// <summary>
    /// F12
    /// </summary>
    F12 = SDLK_F12,
    /// <summary>
    /// F13
    /// </summary>
    F13 = SDLK_F13,
    /// <summary>
    /// F14
    /// </summary>
    F14 = SDLK_F14,
    /// <summary>
    /// F15
    /// </summary>
    F15 = SDLK_F15,

    /* Key state modifier keys */
    /// <summary>
    /// numlock
    /// </summary>
    NumLock = SDLK_NUMLOCK,
    /// <summary>
    /// capslock
    /// </summary>
    CapsLock = SDLK_CAPSLOCK,
    /// <summary>
    /// scrollock
    /// </summary>
    ScrollLock = SDLK_SCROLLOCK,
    /// <summary>
    /// right shift
    /// </summary>
    RightShift = SDLK_RSHIFT,
    /// <summary>
    /// left shift
    /// </summary>
    LeftShift = SDLK_LSHIFT,
    /// <summary>
    /// right ctrl
    /// </summary>
    RightControl = SDLK_RCTRL,
    /// <summary>
    /// left ctrl
    /// </summary>
    LeftControl = SDLK_LCTRL,
    /// <summary>
    /// right alt
    /// </summary>
    RightAlt = SDLK_RALT,
    /// <summary>
    /// left alt
    /// </summary>
    LeftAlt = SDLK_LALT,
    /// <summary>
    /// right meta
    /// </summary>
    RightMeta = SDLK_RMETA,
    /// <summary>
    /// left meta
    /// </summary>
    LeftMeta = SDLK_LMETA,
    /// <summary>
    /// Left "Windows" key
    /// </summary>
    LeftWindows = SDLK_LSUPER,
    /// <summary>
    /// Right "Windows" key
    /// </summary>
    RightWindows = SDLK_RSUPER,
    /// <summary>
    /// "Alt Gr" key. Mode key
    /// </summary>
    Mode = SDLK_MODE,
    /// <summary>
    /// Multi-key compose key
    /// </summary>
    Compose = SDLK_COMPOSE,

    // Miscellaneous function keys
    /// <summary>
    /// help
    /// </summary>
    Help = SDLK_HELP,
    /// <summary>
    /// print-screen
    /// </summary>
    Print = SDLK_PRINT,
    /// <summary>
    /// SysRq
    /// </summary>
    SysRQ = SDLK_SYSREQ,
    /// <summary>
    /// break
    /// </summary>
    Break = SDLK_BREAK,
    /// <summary>
    /// menu
    /// </summary>
    Menu = SDLK_MENU,
    /// <summary>
    /// Power Macintosh power key
    /// </summary>
    Power = SDLK_POWER,
    /// <summary>
    /// Some european keyboards
    /// </summary>
    Euro = SDLK_EURO,
    /// <summary>
    /// Atari keyboard has Undo
    /// </summary>
    Undo = SDLK_UNDO,

    // Add any other keys here
    /// <summary>
    ///
    /// </summary>
    Last = SDLK_LAST
};


namespace ModifierKeys
{
   enum
   {
   /// <summary>
   /// No modifiers applicable
   /// </summary>
   None = KMOD_NONE,
   /// <summary>
   /// Left Shift is down
   /// </summary>
   LeftShift = KMOD_LSHIFT,
   /// <summary>
   /// Right Shift is down
   /// </summary>
   RightShift = KMOD_RSHIFT,
   /// <summary>
   /// Left Control is down
   /// </summary>
   LeftControl = KMOD_LCTRL,
   /// <summary>
   /// Right Control is down
   /// </summary>
   RightControl = KMOD_RCTRL,
   /// <summary>
   /// Left Alt is down
   /// </summary>
   LeftAlt = KMOD_LALT,
   /// <summary>
   /// Right Alt is down
   /// </summary>
   RightAlt = KMOD_RALT,
   /// <summary>
   /// Left Meta is down
   /// </summary>
   LeftMeta = KMOD_LMETA,
   /// <summary>
   /// Right Meta is down
   /// </summary>
   RightMeta = KMOD_RMETA,
   /// <summary>
   /// Numlock is down
   /// </summary>
   NumLock = KMOD_NUM,
   /// <summary>
   /// Capslock is down
   /// </summary>
   Caps = KMOD_CAPS,
   /// <summary>
   ///
   /// </summary>
   Mode = KMOD_MODE,
   /// <summary>
   ///
   /// </summary>
   ReserveKey = KMOD_RESERVED,
   /// <summary>
   /// Both CTRL Keys
   /// </summary>
   ControlKeys = (KMOD_LCTRL | KMOD_RCTRL),
   /// <summary>
   /// Both SHIFT keys.
   /// </summary>
   ShiftKeys = (KMOD_LSHIFT | KMOD_RSHIFT),
   /// <summary>
   /// Both ALT keys.
   /// </summary>
   AltKeys = (KMOD_LALT | KMOD_RALT),
   /// <summary>
   /// Both META keys.
   /// </summary>
   MetaKeys = (KMOD_LMETA | KMOD_RMETA)
   };
}

namespace Focus
{
   enum Enum
   {
      Mouse       = SDL_APPMOUSEFOCUS
    , Keboard     = SDL_APPINPUTFOCUS
    , Application = SDL_APPACTIVE
   };
}

class Keyboard
{
public:
   Keyboard();
};

} // namespace Input
} // namespace SdlDotNetCompat

#endif // KEYBOARD_H
