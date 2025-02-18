#pragma once

#include <iostream>

namespace purple{
    
    const int EVENT_ACTION_BEGIN = 1;
    const int EVENT_ACTION_MOVE = 2;
    const int EVENT_ACTION_END = 3;
    const int EVENT_ACTION_CANCEL = 4;

    const int EVENT_ACTION_MOUSE_MIDDLE_BEGIN = 101;
    const int EVENT_ACTION_MOUSE_MIDDLE_MOVE = 102;
    const int EVENT_ACTION_MOUSE_MIDDLE_END = 103;

    const int EVENT_ACTION_MOUSE_RIGHT_BEGIN = 201;
    const int EVENT_ACTION_MOUSE_RIGHT_MOVE = 202;
    const int EVENT_ACTION_MOUSE_RIGHT_END = 203;

    const int EVENT_ACTION_KEYBOARD_PRESS = 10;   // 键盘按下事件
    const int EVENT_ACTION_KEYBOARD_REPEAT = 11;  // 键盘重复按下
    const int EVENT_ACTION_KEYBOARD_RELEASE = 12; // 键盘抬起事件

    // CODE KEY  for key borard
    const int CODE_KEY_SPACE = 32;
    const int CODE_KEY_APOSTROPHE = 39; /* ' */
    const int CODE_KEY_COMMA = 44;      /* , */
    const int CODE_KEY_MINUS = 45;      /* - */
    const int CODE_KEY_PERIOD = 46;     /* . */
    const int CODE_KEY_SLASH = 47;      /* / */
    const int CODE_KEY_0 = 48;
    const int CODE_KEY_1 = 49;
    const int CODE_KEY_2 = 50;
    const int CODE_KEY_3 = 51;
    const int CODE_KEY_4 = 52;
    const int CODE_KEY_5 = 53;
    const int CODE_KEY_6 = 54;
    const int CODE_KEY_7 = 55;
    const int CODE_KEY_8 = 56;
    const int CODE_KEY_9 = 57;
    const int CODE_KEY_SEMICOLON = 59; /* ; */
    const int CODE_KEY_EQUAL = 61;     /* = */
    const int CODE_KEY_A = 65;
    const int CODE_KEY_B = 66;
    const int CODE_KEY_C = 67;
    const int CODE_KEY_D = 68;
    const int CODE_KEY_E = 69;
    const int CODE_KEY_F = 70;
    const int CODE_KEY_G = 71;
    const int CODE_KEY_H = 72;
    const int CODE_KEY_I = 73;
    const int CODE_KEY_J = 74;
    const int CODE_KEY_K = 75;
    const int CODE_KEY_L = 76;
    const int CODE_KEY_M = 77;
    const int CODE_KEY_N = 78;
    const int CODE_KEY_O = 79;
    const int CODE_KEY_P = 80;
    const int CODE_KEY_Q = 81;
    const int CODE_KEY_R = 82;
    const int CODE_KEY_S = 83;
    const int CODE_KEY_T = 84;
    const int CODE_KEY_U = 85;
    const int CODE_KEY_V = 86;
    const int CODE_KEY_W = 87;
    const int CODE_KEY_X = 88;
    const int CODE_KEY_Y = 89;
    const int CODE_KEY_Z = 90;
    const int CODE_KEY_LEFT_BRACKET = 91;  /* [ */
    const int CODE_KEY_BACKSLASH = 92;     /* \ */
    const int CODE_KEY_RIGHT_BRACKET = 93; /* ] */
    const int CODE_KEY_GRAVE_ACCENT = 96;  /* ` */
    const int CODE_KEY_WORLD_1 = 161;      /* non-US #1 */
    const int CODE_KEY_WORLD_2 = 162;      /* non-US #2 */
    const int CODE_KEY_ESCAPE = 256;
    const int CODE_KEY_ENTER = 257;
    const int CODE_KEY_TAB = 258;
    const int CODE_KEY_BACKSPACE = 259;
    const int CODE_KEY_INSERT = 260;
    const int CODE_KEY_DELETE = 261;
    const int CODE_KEY_RIGHT = 262;
    const int CODE_KEY_LEFT = 263;
    const int CODE_KEY_DOWN = 264;
    const int CODE_KEY_UP = 265;
    const int CODE_KEY_PAGE_UP = 266;
    const int CODE_KEY_PAGE_DOWN = 267;
    const int CODE_KEY_HOME = 268;
    const int CODE_KEY_END = 269;
    const int CODE_KEY_CAPS_LOCK = 280;
    const int CODE_KEY_SCROLL_LOCK = 281;
    const int CODE_KEY_NUM_LOCK = 282;
    const int CODE_KEY_PRINT_SCREEN = 283;
    const int CODE_KEY_PAUSE = 284;
    const int CODE_KEY_F1 = 290;
    const int CODE_KEY_F2 = 291;
    const int CODE_KEY_F3 = 292;
    const int CODE_KEY_F4 = 293;
    const int CODE_KEY_F5 = 294;
    const int CODE_KEY_F6 = 295;
    const int CODE_KEY_F7 = 296;
    const int CODE_KEY_F8 = 297;
    const int CODE_KEY_F9 = 298;
    const int CODE_KEY_F10 = 299;
    const int CODE_KEY_F11 = 300;
    const int CODE_KEY_F12 = 301;
    const int CODE_KEY_F13 = 302;
    const int CODE_KEY_F14 = 303;
    const int CODE_KEY_F15 = 304;
    const int CODE_KEY_F16 = 305;
    const int CODE_KEY_F17 = 306;
    const int CODE_KEY_F18 = 307;
    const int CODE_KEY_F19 = 308;
    const int CODE_KEY_F20 = 309;
    const int CODE_KEY_F21 = 310;
    const int CODE_KEY_F22 = 311;
    const int CODE_KEY_F23 = 312;
    const int CODE_KEY_F24 = 313;
    const int CODE_KEY_F25 = 314;
    const int CODE_KEY_KP_0 = 320;
    const int CODE_KEY_KP_1 = 321;
    const int CODE_KEY_KP_2 = 322;
    const int CODE_KEY_KP_3 = 323;
    const int CODE_KEY_KP_4 = 324;
    const int CODE_KEY_KP_5 = 325;
    const int CODE_KEY_KP_6 = 326;
    const int CODE_KEY_KP_7 = 327;
    const int CODE_KEY_KP_8 = 328;
    const int CODE_KEY_KP_9 = 329;
    const int CODE_KEY_KP_DECIMAL = 330;
    const int CODE_KEY_KP_DIVIDE = 331;
    const int CODE_KEY_KP_MULTIPLY = 332;
    const int CODE_KEY_KP_SUBTRACT = 333;
    const int CODE_KEY_KP_ADD = 334;
    const int CODE_KEY_KP_ENTER = 335;
    const int CODE_KEY_KP_EQUAL = 336;
    const int CODE_KEY_LEFT_SHIFT = 340;
    const int CODE_KEY_LEFT_CONTROL = 341;
    const int CODE_KEY_LEFT_ALT = 342;
    const int CODE_KEY_LEFT_SUPER = 343;
    const int CODE_KEY_RIGHT_SHIFT = 344;
    const int CODE_KEY_RIGHT_CONTROL = 345;
    const int CODE_KEY_RIGHT_ALT = 346;
    const int CODE_KEY_RIGHT_SUPER = 347;
    const int CODE_KEY_MENU = 348;

    struct InputEvent {
        int action = 0;
        float x = 0.0f;
        float y = 0.0f;
        int code = -1;
        void *ptrParam = nullptr;
    };
}
