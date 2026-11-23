#pragma once
#include "FastLED.h"

// Gamma коррекция (Defalt Gamma = 2.8)
const uint8_t PROGMEM gammaR[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,
  2,  2,  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,
  5,  5,  5,  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,
  9,  9, 10, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 14, 14, 14,
  15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22,
  23, 24, 24, 25, 25, 26, 27, 27, 28, 29, 29, 30, 31, 31, 32, 33,
  33, 34, 35, 36, 36, 37, 38, 39, 40, 40, 41, 42, 43, 44, 45, 46,
  46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
  62, 63, 65, 66, 67, 68, 69, 70, 71, 73, 74, 75, 76, 78, 79, 80,
  81, 83, 84, 85, 87, 88, 89, 91, 92, 94, 95, 97, 98, 99, 101, 102,
  104, 105, 107, 109, 110, 112, 113, 115, 116, 118, 120, 121, 123, 125, 127, 128,
  130, 132, 134, 135, 137, 139, 141, 143, 145, 146, 148, 150, 152, 154, 156, 158,
  160, 162, 164, 166, 168, 170, 172, 174, 177, 179, 181, 183, 185, 187, 190, 192,
  194, 196, 199, 201, 203, 206, 208, 210, 213, 215, 218, 220, 223, 225, 227, 230
};

const uint8_t PROGMEM gammaG[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

const uint8_t PROGMEM gammaB[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,
  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,
  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  6,  7,  7,  7,  8,
  8,  8,  8,  9,  9,  9, 10, 10, 10, 10, 11, 11, 12, 12, 12, 13,
  13, 13, 14, 14, 15, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 19,
  20, 20, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 27, 27, 28, 28,
  29, 30, 30, 31, 32, 32, 33, 34, 34, 35, 36, 37, 37, 38, 39, 40,
  40, 41, 42, 43, 44, 44, 45, 46, 47, 48, 49, 50, 51, 51, 52, 53,
  54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 69, 70,
  71, 72, 73, 74, 75, 77, 78, 79, 80, 81, 83, 84, 85, 86, 88, 89,
  90, 92, 93, 94, 96, 97, 98, 100, 101, 103, 104, 106, 107, 109, 110, 112,
  113, 115, 116, 118, 119, 121, 122, 124, 126, 127, 129, 131, 132, 134, 136, 137,
  139, 141, 143, 144, 146, 148, 150, 152, 153, 155, 157, 159, 161, 163, 165, 167,
  169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 193, 196, 198, 200
};

// гамма-коррекция (более натуральные цвета)
uint32_t gammaCorrection(uint32_t color) {
  byte r = (color >> 16) & 0xFF;  // Extract the RR byte
  byte g = (color >> 8) & 0xFF;   // Extract the GG byte
  byte b = color & 0xFF;        // Extract the BB byte

  r = pgm_read_byte(&gammaR[r]);
  g = pgm_read_byte(&gammaG[g]);
  b = pgm_read_byte(&gammaB[b]);

  uint32_t newColor = ((long)(r & 0xff) << 16) + ((long)(g & 0xff) << 8) + ((long)b & 0xff);
  return newColor;
}

// gamma correction для expandColor
static const uint8_t PROGMEM
gamma5[] = {
  0x00, 0x01, 0x02, 0x03, 0x05, 0x07, 0x09, 0x0b,
  0x0e, 0x11, 0x14, 0x18, 0x1d, 0x22, 0x28, 0x2e,
  0x36, 0x3d, 0x46, 0x4f, 0x59, 0x64, 0x6f, 0x7c,
  0x89, 0x97, 0xa6, 0xb6, 0xc7, 0xd9, 0xeb, 0xff
},
gamma6[] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08,
  0x09, 0x0a, 0x0b, 0x0d, 0x0e, 0x10, 0x12, 0x13,
  0x15, 0x17, 0x19, 0x1b, 0x1d, 0x20, 0x22, 0x25,
  0x27, 0x2a, 0x2d, 0x30, 0x33, 0x37, 0x3a, 0x3e,
  0x41, 0x45, 0x49, 0x4d, 0x52, 0x56, 0x5b, 0x5f,
  0x64, 0x69, 0x6e, 0x74, 0x79, 0x7f, 0x85, 0x8b,
  0x91, 0x97, 0x9d, 0xa4, 0xab, 0xb2, 0xb9, 0xc0,
  0xc7, 0xcf, 0xd6, 0xde, 0xe6, 0xee, 0xf7, 0xff
};


// преобразовать цвет из 16 битного в 24 битный
static uint32_t expandColor(uint16_t color) {
  return ((uint32_t)pgm_read_byte(&gamma5[ color >> 11       ]) << 16) |
         ((uint32_t)pgm_read_byte(&gamma6[(color >> 5) & 0x3F]) <<  8) |
         pgm_read_byte(&gamma5[ color       & 0x1F]);
}

DEFINE_GRADIENT_PALETTE(candle_Pal) {
  0,   255,  0,  0,   //red
  90,   255, 255, 255, //full white
  180,   255, 255,  0,  //bright yellow
  255,   255, 255, 255
}; //full white

// From ColorWavesWithPalettes by Mark Kriegsman: https://gist.github.com/kriegsman/8281905786e8b2632aeb


// Gradient Color Palette definitions for 33 different cpt-city color palettes.
//    956 bytes of PROGMEM for all of the palettes together,
//   +618 bytes of PROGMEM for gradient palette code (AVR).
//  1,494 bytes total for all 34 color palettes and associated code.

// Gradient palette "ib_jul01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE(ib_jul01_gp) {
  0, 194,  1,  1,
  94,   1, 29, 18,
  132,  57, 131, 28,
  255, 113,  1,  1
};

// Gradient palette "es_vintage_57_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_57.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_vintage_57_gp) {
  0,   2,  1,  1,
  53,  18,  1,  0,
  104,  69, 29,  1,
  153, 167, 135, 10,
  255,  46, 56,  4
};

// Gradient palette "es_vintage_01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_vintage_01_gp) {
  0,   4,  1,  1,
  51,  16,  0,  1,
  76,  97, 104,  3,
  101, 255, 131, 19,
  127,  67,  9,  4,
  153,  16,  0,  1,
  229,   4,  1,  1,
  255,   4,  1,  1
};

// Gradient palette "es_rivendell_15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/rivendell/tn/es_rivendell_15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_rivendell_15_gp) {
  0,   1, 14,  5,
  101,  16, 36, 14,
  165,  56, 68, 30,
  242, 150, 156, 99,
  255, 150, 156, 99
};

// Gradient palette "rgi_15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/rgi/tn/rgi_15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

DEFINE_GRADIENT_PALETTE(rgi_15_gp) {
  0,   4,  1, 31,
  31,  55,  1, 16,
  63, 197,  3,  7,
  95,  59,  2, 17,
  127,   6,  2, 34,
  159,  39,  6, 33,
  191, 112, 13, 32,
  223,  56,  9, 35,
  255,  22,  6, 38
};

// Gradient palette "retro2_16_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ma/retro2/tn/retro2_16.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE(retro2_16_gp) {
  0, 188, 135,  1,
  255,  46,  7,  1
};

// Gradient palette "Analogous_1_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/red/tn/Analogous_1.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(Analogous_1_gp) {
  0,   3,  0, 255,
  63,  23,  0, 255,
  127,  67,  0, 255,
  191, 142,  0, 45,
  255, 255,  0,  0
};

// Gradient palette "es_pinksplash_08_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/pink_splash/tn/es_pinksplash_08.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_pinksplash_08_gp) {
  0, 126, 11, 255,
  127, 197,  1, 22,
  175, 210, 157, 172,
  221, 157,  3, 112,
  255, 157,  3, 112
};

// Gradient palette "es_pinksplash_07_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/pink_splash/tn/es_pinksplash_07.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_pinksplash_07_gp) {
  0, 229,  1,  1,
  61, 242,  4, 63,
  101, 255, 12, 255,
  127, 249, 81, 252,
  153, 255, 11, 235,
  193, 244,  5, 68,
  255, 232,  1,  5
};

// Gradient palette "Coral_reef_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/other/tn/Coral_reef.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(Coral_reef_gp) {
  0,  40, 199, 197,
  50,  10, 152, 155,
  96,   1, 111, 120,
  96,  43, 127, 162,
  139,  10, 73, 111,
  255,   1, 34, 71
};

// Gradient palette "es_ocean_breeze_068_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_068.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_ocean_breeze_068_gp) {
  0, 100, 156, 153,
  51,   1, 99, 137,
  101,   1, 68, 84,
  104,  35, 142, 168,
  178,   0, 63, 117,
  255,   1, 10, 10
};

// Gradient palette "es_ocean_breeze_036_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_036.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_ocean_breeze_036_gp) {
  0,   1,  6,  7,
  89,   1, 99, 111,
  153, 144, 209, 255,
  255,   0, 73, 82
};

// Gradient palette "departure_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/mjf/tn/departure.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 88 bytes of program space.

DEFINE_GRADIENT_PALETTE(departure_gp) {
  0,   8,  3,  0,
  42,  23,  7,  0,
  63,  75, 38,  6,
  84, 169, 99, 38,
  106, 213, 169, 119,
  116, 255, 255, 255,
  138, 135, 255, 138,
  148,  22, 255, 24,
  170,   0, 255,  0,
  191,   0, 136,  0,
  212,   0, 55,  0,
  255,   0, 55,  0
};

// Gradient palette "es_landscape_64_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/landscape/tn/es_landscape_64.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_landscape_64_gp) {
  0,   0,  0,  0,
  37,   2, 25,  1,
  76,  15, 115,  5,
  127,  79, 213,  1,
  128, 126, 211, 47,
  130, 188, 209, 247,
  153, 144, 182, 205,
  204,  59, 117, 250,
  255,   1, 37, 192
};

// Gradient palette "es_landscape_33_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/landscape/tn/es_landscape_33.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_landscape_33_gp) {
  0,   1,  5,  0,
  19,  32, 23,  1,
  38, 161, 55,  1,
  63, 229, 144,  1,
  66,  39, 142, 74,
  255,   1,  4,  1
};

// Gradient palette "rainbowsherbet_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ma/icecream/tn/rainbowsherbet.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(rainbowsherbet_gp) {
  0, 255, 33,  4,
  43, 255, 68, 25,
  86, 255,  7, 25,
  127, 255, 82, 103,
  170, 255, 255, 242,
  209,  42, 255, 22,
  255,  87, 255, 65
};

// Gradient palette "gr65_hult_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/hult/tn/gr65_hult.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(gr65_hult_gp) {
  0, 247, 176, 247,
  48, 255, 136, 255,
  89, 220, 29, 226,
  160,   7, 82, 178,
  216,   1, 124, 109,
  255,   1, 124, 109
};

// Gradient palette "gr64_hult_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/hult/tn/gr64_hult.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(gr64_hult_gp) {
  0,   1, 124, 109,
  66,   1, 93, 79,
  104,  52, 65,  1,
  130, 115, 127,  1,
  150,  52, 65,  1,
  201,   1, 86, 72,
  239,   0, 55, 45,
  255,   0, 55, 45
};

// Gradient palette "GMT_drywet_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_drywet.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(GMT_drywet_gp) {
  0,  47, 30,  2,
  42, 213, 147, 24,
  84, 103, 219, 52,
  127,   3, 219, 207,
  170,   1, 48, 214,
  212,   1,  1, 111,
  255,   1,  7, 33
};

// Gradient palette "ib15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/general/tn/ib15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(ib15_gp) {
  0, 113, 91, 147,
  72, 157, 88, 78,
  89, 208, 85, 33,
  107, 255, 29, 11,
  141, 137, 31, 39,
  255,  59, 33, 89
};

// Gradient palette "Fuschia_7_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/fuschia/tn/Fuschia-7.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(Fuschia_7_gp) {
  0,  43,  3, 153,
  63, 100,  4, 103,
  127, 188,  5, 66,
  191, 161, 11, 115,
  255, 135, 20, 182
};

// Gradient palette "es_emerald_dragon_08_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/emerald_dragon/tn/es_emerald_dragon_08.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_emerald_dragon_08_gp) {
  0,  97, 255,  1,
  101,  47, 133,  1,
  178,  13, 43,  1,
  255,   2, 10,  1
};

// Gradient palette "lava_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/elem/tn/lava.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 52 bytes of program space.

DEFINE_GRADIENT_PALETTE(lava_gp) {
  0,   0,  0,  0,
  46,  18,  0,  0,
  96, 113,  0,  0,
  108, 142,  3,  1,
  119, 175, 17,  1,
  146, 213, 44,  2,
  174, 255, 82,  4,
  188, 255, 115,  4,
  202, 255, 156,  4,
  218, 255, 203,  4,
  234, 255, 255,  4,
  244, 255, 255, 71,
  255, 255, 255, 255
};

// Gradient palette "fire_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/elem/tn/fire.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(fire_gp) {
  0,   1,  1,  0,
  76,  32,  5,  0,
  146, 192, 24,  0,
  197, 220, 105,  5,
  240, 252, 255, 31,
  250, 252, 255, 111,
  255, 255, 255, 255
};

// Gradient palette "Colorfull_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Colorfull.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE(Colorfull_gp) {
  0,  10, 85,  5,
  25,  29, 109, 18,
  60,  59, 138, 42,
  93,  83, 99, 52,
  106, 110, 66, 64,
  109, 123, 49, 65,
  113, 139, 35, 66,
  116, 192, 117, 98,
  124, 255, 255, 137,
  168, 100, 180, 155,
  255,  22, 121, 174
};

// Gradient palette "Magenta_Evening_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Magenta_Evening.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(Magenta_Evening_gp) {
  0,  71, 27, 39,
  31, 130, 11, 51,
  63, 213,  2, 64,
  70, 232,  1, 66,
  76, 252,  1, 69,
  108, 123,  2, 51,
  255,  46,  9, 35
};

// Gradient palette "Pink_Purple_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Pink_Purple.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE(Pink_Purple_gp) {
  0,  19,  2, 39,
  25,  26,  4, 45,
  51,  33,  6, 52,
  76,  68, 62, 125,
  102, 118, 187, 240,
  109, 163, 215, 247,
  114, 217, 244, 255,
  122, 159, 149, 221,
  149, 113, 78, 188,
  183, 128, 57, 155,
  255, 146, 40, 123
};

// Gradient palette "Sunset_Real_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Real.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(Sunset_Real_gp) {
  0, 120,  0,  0,
  22, 179, 22,  0,
  51, 255, 104,  0,
  85, 167, 22, 18,
  135, 100,  0, 103,
  198,  16,  0, 130,
  255,   0,  0, 160
};

DEFINE_GRADIENT_PALETTE(Sunset_Yellow_gp) {
    0,  10, 62,123,
   36,  56,130,103,
   87, 153,225, 85,
  100, 199,217, 68,
  107, 255,207, 54,
  115, 247,152, 57,
  120, 239,107, 61,
  128, 247,152, 57,
  180, 255,207, 54,
  223, 255,227, 48,
  255, 255,248, 42};

// Gradient palette "es_autumn_19_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/autumn/tn/es_autumn_19.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 52 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_autumn_19_gp) {
  0,  26,  1,  1,
  51,  67,  4,  1,
  84, 118, 14,  1,
  104, 137, 152, 52,
  112, 113, 65,  1,
  122, 133, 149, 59,
  124, 137, 152, 52,
  135, 113, 65,  1,
  142, 139, 154, 46,
  163, 113, 13,  1,
  204,  55,  3,  1,
  249,  17,  1,  1,
  255,  17,  1,  1
};

// Gradient palette "BlacK_Blue_Magenta_White_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Blue_Magenta_White.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(BlacK_Blue_Magenta_White_gp) {
  0,   0,  0,  0,
  42,   0,  0, 45,
  84,   0,  0, 255,
  127,  42,  0, 255,
  170, 255,  0, 255,
  212, 255, 55, 255,
  255, 255, 255, 255
};

// Gradient palette "BlacK_Magenta_Red_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Magenta_Red.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(BlacK_Magenta_Red_gp) {
  0,   0,  0,  0,
  63,  42,  0, 45,
  127, 255,  0, 255,
  191, 255,  0, 45,
  255, 255,  0,  0
};

// Gradient palette "BlacK_Red_Magenta_Yellow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Red_Magenta_Yellow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(BlacK_Red_Magenta_Yellow_gp) {
  0,   0,  0,  0,
  42,  42,  0,  0,
  84, 255,  0,  0,
  127, 255,  0, 45,
  170, 255,  0, 255,
  212, 255, 55, 45,
  255, 255, 255,  0
};

// Gradient palette "Blue_Cyan_Yellow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/Blue_Cyan_Yellow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(Blue_Cyan_Yellow_gp) {
  0,   0,  0, 255,
  63,   0, 55, 255,
  127,   0, 255, 255,
  191,  42, 255, 45,
  255, 255, 255,  0
};

// Gradient palette "bhw1_28_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_28.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_28_gp) {
  0,  75,  1, 221,
  30, 252, 73, 255,
  48, 169,  0, 242,
  119,   0, 149, 242,
  170,  43,  0, 242,
  206, 252, 73, 255,
  232,  78, 12, 214,
  255,   0, 149, 242
};

// New PALETTES from TachoLED ===============================================================================


DEFINE_GRADIENT_PALETTE(dkbluered_gp){
    0, 1, 0, 4,
    8, 1, 0, 13,
    17, 1, 0, 29,
    25, 1, 0, 52,
    33, 1, 0, 83,
    42, 1, 0, 123,
    51, 1, 0, 174,
    59, 1, 0, 235,
    68, 1, 2, 255,
    76, 4, 17, 255,
    84, 16, 45, 255,
    93, 37, 82, 255,
    102, 69, 127, 255,
    110, 120, 168, 255,
    119, 182, 217, 255,
    127, 255, 255, 255,
    135, 255, 217, 184,
    144, 255, 168, 123,
    153, 255, 127, 73,
    161, 255, 82, 40,
    170, 255, 45, 18,
    178, 255, 17, 5,
    186, 255, 2, 1,
    195, 234, 0, 1,
    204, 171, 0, 1,
    212, 120, 0, 1,
    221, 79, 0, 1,
    229, 48, 0, 1,
    237, 26, 0, 1,
    246, 12, 0, 1,
    255, 4, 0, 1};
DEFINE_GRADIENT_PALETTE(Optimus_Prime_gp){
    0, 5, 16, 18,
    25, 5, 16, 18,
    51, 7, 25, 39,
    76, 8, 38, 71,
    102, 64, 99, 106,
    127, 194, 189, 151,
    153, 182, 63, 42,
    178, 167, 6, 2,
    204, 100, 3, 1,
    229, 53, 1, 1,
    255, 53, 1, 1};

DEFINE_GRADIENT_PALETTE(warmGrad_gp){
    0, 252, 252, 172,
    25, 239, 255, 61,
    53, 247, 45, 17,
    76, 197, 82, 19,
    96, 239, 255, 61,
    124, 83, 4, 1,
    153, 247, 45, 17,
    214, 23, 15, 17,
    255, 1, 1, 1};

DEFINE_GRADIENT_PALETTE(coldGrad_gp){
    0, 66, 186, 192,
    43, 1, 22, 71,
    79, 2, 104, 142,
    117, 66, 186, 192,
    147, 2, 104, 142,
    186, 1, 22, 71,
    224, 2, 104, 142,
    255, 4, 27, 28};

DEFINE_GRADIENT_PALETTE(hotGrad_gp){
    0, 157, 21, 2,
    35, 229, 244, 16,
    73, 255, 44, 7,
    107, 142, 7, 1,
    153, 229, 244, 16,
    206, 142, 7, 1,
    255, 135, 36, 0};

DEFINE_GRADIENT_PALETTE(pinkGrad_gp){
    0, 249, 32, 145,
    28, 208, 1, 7,
    43, 249, 1, 19,
    56, 126, 152, 10,
    73, 234, 23, 84,
    89, 224, 45, 119,
    107, 232, 127, 158,
    127, 244, 13, 89,
    150, 188, 6, 52,
    175, 177, 70, 14,
    221, 194, 1, 8,
    255, 112, 0, 1};

DEFINE_GRADIENT_PALETTE(comfy_gp){
    0, 255, 255, 45,
    43, 208, 93, 1,
    137, 224, 1, 242,
    181, 159, 1, 29,
    255, 63, 4, 68};

DEFINE_GRADIENT_PALETTE(cyperpunk_gp){
    0, 3, 6, 72,
    38, 12, 50, 188,
    109, 217, 35, 1,
    135, 242, 175, 12,
    178, 161, 32, 87,
    255, 24, 6, 108};

DEFINE_GRADIENT_PALETTE(girl_gp){
    0, 103, 1, 10,
    33, 109, 1, 12,
    76, 159, 5, 48,
    119, 175, 55, 103,
    127, 175, 55, 103,
    178, 159, 5, 48,
    221, 109, 1, 12,
    255, 103, 1, 10};

DEFINE_GRADIENT_PALETTE(xmas_gp){
    0, 0, 12, 0,
    40, 0, 55, 0,
    66, 1, 117, 2,
    77, 1, 84, 1,
    81, 0, 55, 0,
    119, 0, 12, 0,
    153, 42, 0, 0,
    181, 121, 0, 0,
    204, 255, 12, 8,
    224, 121, 0, 0,
    244, 42, 0, 0,
    255, 42, 0, 0};

DEFINE_GRADIENT_PALETTE(acid_gp){
    0, 0, 12, 0,
    61, 153, 239, 112,
    127, 0, 12, 0,
    165, 106, 239, 2,
    196, 167, 229, 71,
    229, 106, 239, 2,
    255, 0, 12, 0};

DEFINE_GRADIENT_PALETTE(blueSmoke_gp){
    0, 0, 0, 0,
    12, 1, 1, 3,
    53, 8, 1, 22,
    80, 4, 6, 89,
    119, 2, 25, 216,
    145, 7, 10, 99,
    186, 15, 2, 31,
    233, 2, 1, 5,
    255, 0, 0, 0};

DEFINE_GRADIENT_PALETTE(gummy_gp){
    0,
    8,
    47,
    5,
    31,
    77,
    122,
    6,
    63,
    249,
    237,
    7,
    95,
    232,
    51,
    1,
    127,
    215,
    0,
    1,
    159,
    47,
    1,
    3,
    191,
    1,
    7,
    16,
    223,
    52,
    22,
    6,
    255,
    239,
    45,
    1,
};

DEFINE_GRADIENT_PALETTE(leo_gp){
    0,
    0,
    0,
    0,
    16,
    0,
    0,
    0,
    32,
    0,
    0,
    0,
    18,
    0,
    0,
    0,
    64,
    16,
    8,
    0,
    80,
    80,
    40,
    0,
    96,
    16,
    8,
    0,
    112,
    0,
    0,
    0,
    128,
    0,
    0,
    0,
    144,
    0,
    0,
    0,
    160,
    0,
    0,
    0,
    176,
    0,
    0,
    0,
    192,
    0,
    0,
    0,
    208,
    0,
    0,
    0,
    224,
    0,
    0,
    0,
    240,
    0,
    0,
    0,
    255,
    0,
    0,
    0,
};


// PALETTES FROM  WLED ======================================================

DEFINE_GRADIENT_PALETTE(aurora_gp){
    0, 17, 177, 13,     // Greenish
    64, 121, 242, 5,    // Greenish
    128, 25, 173, 121,  // Turquoise
    192, 250, 77, 127,  // Pink
    255, 171, 101, 221  // Purple
};


DEFINE_GRADIENT_PALETTE(Beech_gp){
    0, 255,252,214,
   12, 255,252,214,
   22, 255,252,214,
   26, 190,191,115,
   28, 137,141, 52,
   28, 112,255,205,
   50,  51,246,214,
   71,  17,235,226,
   93,   2,193,199,
  120,   0,156,174,
  133,   1,101,115,
  136,   1, 59, 71,
  136,   7,131,170,
  208,   1, 90,151,
  255,   0, 56,133};

DEFINE_GRADIENT_PALETTE(Another_Sunset_gp){
    0, 110, 49, 11,
   29,  55, 34, 10,
   68,  22, 22,  9,
   68, 239,124,  8,
   97, 220,156, 27,
  124, 203,193, 61,
  178,  33, 53, 56,
  255,   0,  1, 52};
  
DEFINE_GRADIENT_PALETTE(fierce_ice_gp){
    0,   0,  0,  0,
   59,   0,  9, 45,
  119,   0, 38,255,
  149,   3,100,255,
  180,  23,199,255,
  217, 100,235,255,
  255, 255,255,255};

DEFINE_GRADIENT_PALETTE(Tertiary_01_gp){
    0,   0,  1,255,
   63,   3, 68, 45,
  127,  23,255,  0,
  191, 100, 68,  1,
  255, 255,  1,  4};

DEFINE_GRADIENT_PALETTE(Orange_Teal_gp){
    0,   0,150, 92,
   55,   0,150, 92,
  200, 255, 72,  0,
  255, 255, 72,  0};

DEFINE_GRADIENT_PALETTE(Tiamat_gp){
    0,   1,  2, 14, //gc
   33,   2,  5, 35, //gc from 47, 61,126
  100,  13,135, 92, //gc from 88,242,247
  120,  43,255,193, //gc from 135,255,253
  140, 247,  7,249, //gc from 252, 69,253
  160, 193, 17,208, //gc from 231, 96,237
  180,  39,255,154, //gc from 130, 77,213
  200,   4,213,236, //gc from 57,122,248
  220,  39,252,135, //gc from 177,254,255
  240, 193,213,253, //gc from 203,239,253
  255, 255,249,255};

DEFINE_GRADIENT_PALETTE(April_Night_gp){
    0,   1,  5, 45, //deep blue
   10,   1,  5, 45,
   25,   5,169,175, //light blue
   40,   1,  5, 45,
   61,   1,  5, 45,
   76,  45,175, 31, //green
   91,   1,  5, 45,
  112,   1,  5, 45,
  127, 249,150,  5, //yellow
  143,   1,  5, 45,
  162,   1,  5, 45,
  178, 255, 92,  0, //pastel orange
  193,   1,  5, 45,
  214,   1,  5, 45,
  229, 223, 45, 72, //pink
  244,   1,  5, 45,
  255,   1,  5, 45};

DEFINE_GRADIENT_PALETTE(Orangery_gp){
    0, 255, 95, 23,
   30, 255, 82,  0,
   60, 223, 13,  8,
   90, 144, 44,  2,
  120, 255,110, 17,
  150, 255, 69,  0,
  180, 158, 13, 11,
  210, 241, 82, 17,
  255, 213, 37,  4};

DEFINE_GRADIENT_PALETTE(Sakura_gp){
    0, 196, 19, 10,
   65, 255, 69, 45,
  130, 223, 45, 72,
  195, 255, 82,103,
  255, 223, 13, 17};
  
DEFINE_GRADIENT_PALETTE(Atlantica_gp){  
    0,   0, 28,112, //#001C70
   50,  32, 96,255, //#2060FF
  100,   0,243, 45,
  150,  12, 95, 82, //#0C5F52
  200,  25,190, 95, //#19BE5F
  255,  40,170, 80};//#28AA50

DEFINE_GRADIENT_PALETTE(C9_gp){
    0, 184,  4,  0, //red
   60, 184,  4,  0,
   65, 144, 44,  2, //amber
  125, 144, 44,  2,
  130,   4, 96,  2, //green
  190,   4, 96,  2,
  195,   7,  7, 88, //blue
  255,   7,  7, 88};
  
DEFINE_GRADIENT_PALETTE(C9_2_gp){  
    0,   6, 126,   2, //green
   45,   6, 126,   2,
   45,   4,  30, 114, //blue
   90,   4,  30, 114,
   90, 255,   5,   0, //red
  135, 255,   5,   0,
  135, 196,  57,   2, //amber
  180, 196,  57,   2,
  180, 137,  85,   2, //yellow
  255, 137,  85,   2};

DEFINE_GRADIENT_PALETTE(C9_new_gp){
    0, 255,   5,   0, //red
   60, 255,   5,   0,
   60, 196,  57,   2, //amber (start 61?)
  120, 196,  57,   2,
  120,   6, 126,   2, //green (start 126?)
  180,   6, 126,   2,
  180,   4,  30, 114, //blue (start 191?)
  255,   4,  30, 114};

DEFINE_GRADIENT_PALETTE(temperature_gp){
    0,   1, 27,105,
   14,   1, 40,127,
   28,   1, 70,168,
   42,   1, 92,197,
   56,   1,119,221,
   70,   3,130,151,
   84,  23,156,149,
   99,  67,182,112,
  113, 121,201, 52,
  127, 142,203, 11,
  141, 224,223,  1,
  155, 252,187,  2,
  170, 247,147,  1,
  184, 237, 87,  1,
  198, 229, 43,  1,
  226, 171,  2,  2,
  240,  80,  3,  3,
  255,  80,  3,  3};

DEFINE_GRADIENT_PALETTE(Aurora2_gp){
      0,  17, 177,  13,    //Greenish
     64, 121, 242,   5,    //Greenish
    128,  25, 173, 121,    //Turquoise
    192, 250,  77, 127,    //Pink
    255, 171, 101, 221     //Purple
  };

DEFINE_GRADIENT_PALETTE(retro_clown_gp){
    0, 227,101,  3,
  117, 194, 18, 19,
  255,  92,  8,192};

DEFINE_GRADIENT_PALETTE(candy_gp){
    0, 229,227,  1,
   15, 227,101,  3,
  142,  40,  1, 80,
  198,  17,  1, 79,
  255,   0,  0, 45};

DEFINE_GRADIENT_PALETTE(candy2_gp){
    0,  39, 33, 34,
   25,   4,  6, 15,
   48,  49, 29, 22,
   73, 224,173,  1,
   89, 177, 35,  5,
  130,   4,  6, 15,
  163, 255,114,  6,
  186, 224,173,  1,
  211,  39, 33, 34,
  255,   1,  1,  1};

DEFINE_GRADIENT_PALETTE(toxy_reaf_gp){
    0,   1,221, 53,
  255,  73,  3,178};

DEFINE_GRADIENT_PALETTE(fairy_reaf_gp){
    0, 184,  1,128,
  160,   1,193,182,
  219, 153,227,190,
  255, 255,255,255};

DEFINE_GRADIENT_PALETTE(semi_blue_gp){  
    0,   0,  0,  0,
   12,   1,  1,  3,
   53,   8,  1, 22,
   80,   4,  6, 89,
  119,   2, 25,216,
  145,   7, 10, 99,
  186,  15,  2, 31,
  233,   2,  1,  5,
  255,   0,  0,  0};

DEFINE_GRADIENT_PALETTE(pink_candy_gp){ 
    0, 255,255,255,
   45,   7, 12,255,
  112, 227,  1,127,
  112, 227,  1,127,
  140, 255,255,255,
  155, 227,  1,127,
  196,  45,  1, 99,
  255, 255,255,255};

DEFINE_GRADIENT_PALETTE(red_reaf_gp){ 
    0,   3, 13, 43,
  104,  78,141,240,
  188, 255,  0,  0,
  255,  28,  1,  1};

DEFINE_GRADIENT_PALETTE(aqua_flash_gp){ 
    0,   0,  0,  0,
   66,  57,227,233,
   96, 255,255,  8,
  124, 255,255,255,
  153, 255,255,  8,
  188,  57,227,233,
  255,   0,  0,  0};

DEFINE_GRADIENT_PALETTE(yelblu_hot_gp){ 
    0,   4,  2,  9,
   58,  16,  0, 47,
  122,  24,  0, 16,
  158, 144,  9,  1,
  183, 179, 45,  1,
  219, 220,114,  2,
  255, 234,237,  1};

DEFINE_GRADIENT_PALETTE(lite_light_gp){ 
    0,   0,  0,  0,
    9,   1,  1,  1,
   40,   5,  5,  6,
   66,   5,  5,  6,
  101,  10,  1, 12,
  255,   0,  0,  0};

DEFINE_GRADIENT_PALETTE(red_flash_gp){ 
    0,   0,  0,  0,
   99, 227,  1,  1,
  130, 249,199, 95,
  155, 227,  1,  1,
  255,   0,  0,  0};

DEFINE_GRADIENT_PALETTE(blink_red_gp){ 
    0,   1,  1,  1,
   43,   4,  1, 11,
   76,  10,  1,  3,
  109, 161,  4, 29,
  127, 255, 86,123,
  165, 125, 16,160,
  204,  35, 13,223,
  255,  18,  2, 18};

DEFINE_GRADIENT_PALETTE(red_shift_gp){ 
    0,  31,  1, 27,
   45,  34,  1, 16,
   99, 137,  5,  9,
  132, 213,128, 10,
  175, 199, 22,  1,
  201, 199,  9,  6,
  255,   1,  0,  1};

DEFINE_GRADIENT_PALETTE(red_tide_gp){ 
    0, 247,  5,  0,
   28, 255, 67,  1,
   43, 234, 88, 11,
   58, 234,176, 51,
   84, 229, 28,  1,
  114, 113, 12,  1,
  140, 255,225, 44,
  168, 113, 12,  1,
  196, 244,209, 88,
  216, 255, 28,  1,
  255,  53,  1,  1};

// From TachoLED
/*
const TProgmemRGBPalette16 WoodFireColors_p PROGMEM = {CRGB::Black, 0x330e00, 0x661c00, 0x992900, 0xcc3700, CRGB::OrangeRed, 0xff5800, 0xff6b00, 0xff7f00, 0xff9200, CRGB::Orange, 0xffaf00, 0xffb900, 0xffc300, 0xffcd00, CRGB::Gold};             //* рыжий
const TProgmemRGBPalette16 NormalFire_p PROGMEM = {CRGB::Black, 0x330000, 0x660000, 0x990000, 0xcc0000, CRGB::Red, 0xff0c00, 0xff1800, 0xff2400, 0xff3000, 0xff3c00, 0xff4800, 0xff5400, 0xff6000, 0xff6c00, 0xff7800};                             // красный
const TProgmemRGBPalette16 LithiumFireColors_p PROGMEM = {CRGB::Black, 0x240707, 0x470e0e, 0x6b1414, 0x8e1b1b, CRGB::FireBrick, 0xc14244, 0xd16166, 0xe08187, 0xf0a0a9, CRGB::Pink, 0xff9ec0, 0xff7bb5, 0xff59a9, 0xff369e, CRGB::DeepPink};        //* пастель
const TProgmemRGBPalette16 SodiumFireColors_p PROGMEM = {CRGB::Black, 0x332100, 0x664200, 0x996300, 0xcc8400, CRGB::Orange, 0xffaf00, 0xffb900, 0xffc300, 0xffcd00, CRGB::Gold, 0xf8cd06, 0xf0c30d, 0xe9b913, 0xe1af1a, CRGB::Goldenrod};           //* Yellow
const TProgmemRGBPalette16 CopperFireColors_p PROGMEM = {CRGB::Black, 0x001a00, 0x003300, 0x004d00, 0x006600, CRGB::Green, 0x239909, 0x45b313, 0x68cc1c, 0x8ae626, CRGB::GreenYellow, 0x94f530, 0x7ceb30, 0x63e131, 0x4bd731, CRGB::LimeGreen};     //* Green
const TProgmemRGBPalette16 AlcoholFireColors_p PROGMEM = {CRGB::Black, 0x000033, 0x000066, 0x000099, 0x0000cc, CRGB::Blue, 0x0026ff, 0x004cff, 0x0073ff, 0x0099ff, CRGB::DeepSkyBlue, 0x1bc2fe, 0x36c5fd, 0x51c8fc, 0x6ccbfb, CRGB::LightSkyBlue};  //* Blue
*/


// Single array of defined cpt-city color palettes.
// This will let us programmatically choose one based on
// a number, rather than having to activate each explicitly
// by name every time.
// Since it is const, this array could also be moved
// into PROGMEM to save SRAM, but for simplicity of illustration
// we'll keep it in a regular SRAM array.
//
// This list of color palettes acts as a "playlist"; you can
// add or delete, or re-arrange as you wish.
const TProgmemRGBGradientPalettePtr gGradientPalettes[] = {
  Sunset_Real_gp,
  Sunset_Yellow_gp,
  es_rivendell_15_gp,
  es_ocean_breeze_036_gp,
  rgi_15_gp,
  retro2_16_gp,
  Analogous_1_gp,
  es_pinksplash_08_gp,
  Coral_reef_gp,
  es_ocean_breeze_068_gp,
  es_pinksplash_07_gp,
  es_vintage_01_gp,
  departure_gp,
  es_landscape_64_gp,
  es_landscape_33_gp,
  rainbowsherbet_gp,
  gr65_hult_gp,
  gr64_hult_gp,
  GMT_drywet_gp,
  ib_jul01_gp,
  es_vintage_57_gp,
  ib15_gp,
  Fuschia_7_gp,
  es_emerald_dragon_08_gp,
  lava_gp,
  fire_gp,
  Colorfull_gp,
  Magenta_Evening_gp,
  Pink_Purple_gp,
  es_autumn_19_gp,
  BlacK_Blue_Magenta_White_gp,
  BlacK_Magenta_Red_gp,
  BlacK_Red_Magenta_Yellow_gp,
  Blue_Cyan_Yellow_gp,
  bhw1_28_gp,
  
    // From TachoLED ===================
    dkbluered_gp,
    Optimus_Prime_gp,
    warmGrad_gp,
    coldGrad_gp,
    hotGrad_gp,
    pinkGrad_gp,
    comfy_gp,
    cyperpunk_gp,
    girl_gp,
    xmas_gp,
    acid_gp,
    blueSmoke_gp,
    gummy_gp,
    leo_gp,
    aurora_gp,
    
    // from WLED  ====================
    Beech_gp,
    Another_Sunset_gp,
    fierce_ice_gp,
    Tertiary_01_gp,
    Orange_Teal_gp,
    Tiamat_gp,
    April_Night_gp,
    Orangery_gp,
    Sakura_gp,
    Atlantica_gp,
    C9_gp,
    C9_2_gp,
    C9_new_gp,
    temperature_gp,
    Aurora2_gp,
    retro_clown_gp,
    candy_gp,
    candy2_gp,
    toxy_reaf_gp,
    fairy_reaf_gp,
    semi_blue_gp,
    pink_candy_gp,
    red_reaf_gp,
    aqua_flash_gp,
    yelblu_hot_gp,
    lite_light_gp,
    red_flash_gp,
    blink_red_gp,
    red_shift_gp,
    red_tide_gp
  // From TachoLED ===========
//    HeatColors_p,

//    WoodFireColors_p,
//    NormalFire_p,
//    LithiumFireColors_p,
//    SodiumFireColors_p,
//    CopperFireColors_p,
//    AlcoholFireColors_p,
//    LavaColors_p,
//    PartyColors_p,
//    RainbowColors_p,
//    RainbowStripeColors_p,
//    CloudColors_p,
//    OceanColors_p,
//    ForestColors_p,
};

const uint8_t gGradientPaletteNamesCount = 80;

String paletteNames[gGradientPaletteNamesCount] = {
  "Sunset_Real_gp",
  "Sunset_Yellow_gp",
  "es_rivendell_15_gp",
  "es_ocean_breeze_036_gp",
  "rgi_15_gp",
  "retro2_16_gp",
  "Analogous_1_gp",
  "es_pinksplash_08_gp",
  "Coral_reef_gp",
  "es_ocean_breeze_068_gp",
  "es_pinksplash_07_gp",
  "es_vintage_01_gp",
  "departure_gp",
  "es_landscape_64_gp",
  "es_landscape_33_gp",
  "rainbowsherbet_gp",
  "gr65_hult_gp",
  "gr64_hult_gp",
  "GMT_drywet_gp",
  "ib_jul01_gp",
  "es_vintage_57_gp",
  "ib15_gp",
  "Fuschia_7_gp",
  "es_emerald_dragon_08_gp",
  "lava_gp",
  "fire_gp",
  "Colorfull_gp",
  "Magenta_Evening_gp",
  "Pink_Purple_gp",
  "es_autumn_19_gp",
  "BlacK_Blue_Magenta_White_gp",
  "BlacK_Magenta_Red_gp",
  "BlacK_Red_Magenta_Yellow_gp",
  "Blue_Cyan_Yellow_gp",
  "bhw1_28_gp"

    "dkbluered_gp",
    "Optimus_Prime_gp",
    "warmGrad_gp",
    "coldGrad_gp",
    "hotGrad_gp",
    "pinkGrad_gp",
    "comfy_gp",
    "cyperpunk_gp",
    "girl_gp",
    "xmas_gp",
    "acid_gp",
    "blueSmoke_gp",
    "gummy_gp",
    "leo_gp",
    "aurora_gp",
    "Beech_gp",
    "Another_Sunset_gp",
    "fierce_ice_gp",
    "Tertiary_01_gp",
    "Orange_Teal_gp",
    "Tiamat_gp",
    "April_Night_gp",
    "Orangery_gp",
    "Sakura_gp",
    "Atlantica_gp",
    "C9_gp",
    "C9_2_gp",
    "C9_new_gp",
    "temperature_gp",
    "Aurora2_gp",
    "retro_clown_gp",
    "candy_gp",
    "candy2_gp",
    "toxy_reaf_gp",
    "fairy_reaf_gp",
    "semi_blue_gp",
    "pink_candy_gp",
    "red_reaf_gp",
    "aqua_flash_gp",
    "yelblu_hot_gp",
    "lite_light_gp",
    "red_flash_gp",
    "blink_red_gp",
    "red_shift_gp",
    "red_tide_gp"
};

  // From TachoLED ===========
//    HeatColors_p,
//    WoodFireColors_p,
//    NormalFire_p,
//    LithiumFireColors_p,
//    SodiumFireColors_p,
//    CopperFireColors_p,
//    AlcoholFireColors_p,
//    LavaColors_p,
//    PartyColors_p,
//    RainbowColors_p,
//    RainbowStripeColors_p,
//    CloudColors_p,
//    OceanColors_p,
//    ForestColors_p,



// Count of how many cpt-city gradients are defined:
const uint8_t gGradientPaletteCount =
    sizeof(gGradientPalettes) / sizeof(TProgmemRGBGradientPalettePtr);
