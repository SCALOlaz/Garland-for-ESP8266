#pragma once
/*
  Effects and List
  SCALOlaz 10.07.2024 - 20.11.2024
  Разделено на два файла для удобства редактирования и оперирования
*/
#include "util.h"
#include "effects.h"

// Специальные функции
void clr() {    // Очистка экрана, общая, для всех эффектов

    if ((bool)db["toggle_clear_eff"]==true) {
        FastLED.clear();  // очистить
        FastLED.show();
    }
    loadingFlag = false;
 //   (uint8_t)db["selecteffect"]].sName;
 //   Serial.println(arrEff[(uint8_t)db["selecteffect"]].sName + " Start");
}
////////////////////////////////////////////////////////////////// Блеск
void addglitter(fract8 chanceOfGlitter) {
  if (random8(0, (chanceOfGlitter * 3)) < chanceOfGlitter) {
//      if ((int)db["num_leds"] <= 255) {
//          ledss[ random8((int)db["num_leds"]) ] += (uint32_t)db["glitter_color"]; //CRGB::White;
//} else {
          ledss[ random16((int)db["num_leds"]) ] += (uint32_t)db["glitter_color"];  //CRGB::White;
//      }
  }
}

////////////////////////////////////////////////////////////// Свечи

void addcandle() {
  uint16_t poz = (int)db["candless_start"];
  CRGBPalette16 myPal = candle_Pal;           // Палитра для свечей

    uint8_t kol = (int)db["num_leds"] / 9;   // Макс Количество свечей

    for (uint8_t x = 0; x < kol; x++) {
      ledss[ poz ] = ColorFromPalette(myPal, random8(255));
      poz += (int)db["candless_interval"];
    }

}

///////////////////////////////////////////////////////////////// Черный фон
void addbackground() {
  uint16_t i;

  for (i = 0; i < (int)db["num_leds"] ; i++)
    if ((ledss[i].r < 5) && (ledss[i].g < 5) && (ledss[i].b < 5)) {
        ledss[i].b += 5;    //CRGB(5, 5, 5);  // Fix for FastLED 3.6
//        ledss[i].g += 5;
//        ledss[i].r += 5;
    }
}
// ======================

bool direct;

////////////////////////////////////////////////////////////////// Бенгальский огонь
void addsparkler(uint8_t nut)       //Бенгальский огонь
// 0 - Бенгальский огонь
// 1 - 1 яркий светодиод
// 2 - метеорит
{
  uint8_t kol = 5;
  if ((int)db["num_leds"] < 10) {
    kol = (int)db["num_leds"] / 3;
  }

  int startled = (int)db["num_leds"]-1;

//  if (kol >= 2) {
    switch (nut) {
      case 0 :        //Бенгальский
          for (int x = 0; x < kol; x++) 
              ledss[startled - random8((int)db["spark_bengal_length"]) ] = (uint32_t)db["spark_bengal_color"];
          break;
      case 1 :        //1 яркий
          for (int x = 0; x < (int)db["spark_big_length"]; x++)
              ledss[startled - x] = (uint32_t)db["spark_big_color"];
          break;                                         
      case 2 :        //Метеорит
          ledss[startled - 1] = CRGB::White;
          ledss[startled - 2] = CRGB::Red;
          ledss[startled - 3] = CRGB::Violet;
          break;
    }
//  }
}

///////////////////////////////////////////////////////////////




byte hue = 0;
byte hstep = 4;

// *********** радуга заливка ***********
void rainbow() {
  if (loadingFlag) {
    clr();
  }
  if (direct) {
    hue += hstep;
    if (hue>=250) { 
        hue = 255;
        direct = false;
        hstep = random(4, 14);
    }
  }
  else {
    hue -= hstep;
    if (hue <=4) {
        hue = 0;
        direct = true;
        hstep = random(4, 14);
    }
  }
  for (int i = 0; i < (int)db["num_leds"]; i++)
//    ledss[i] = CHSV((byte)(hue + i * float(255 / ((int)db["num_leds"]/2) )), 255, 255);
    ledss[i] = ColorFromPalette(gCurrentPalette, (byte)(hue + i * float(255 / ((int)db["num_leds"]/2) )), 255, currentBlending);
}

void rainbow_beat() {                                       // The fill_rainbow call doesn't support brightness levels
  if (loadingFlag) {
      clr();
  }

    uint16_t beatA = beatsin8(17, 0, 255);                        // Starting hue
    uint16_t beatB = beatsin8(13, 0, 255);
    fill_rainbow(ledss, (int)db["num_leds"], (beatA + beatB) / 2, 8);        // Use FastLED's fill_rainbow routine.

} // rainbow_beat()

void rainbow_march() {                                           // The fill_rainbow call doesn't support brightness levels
  if (loadingFlag) {
      clr();
  }

    thisindex += thisrot * thisdir;
    fill_rainbow(ledss, (int)db["num_leds"], thisindex, thisdiff);               // I don't change deltahue on the fly as it's too fast near the end of the strip.

} // rainbow_march()

void rainbow_loft() {
  if (loadingFlag) {
      clr();
  }
  if (direct) {
    hue += hstep;
    if (hue>=250) { 
     //   hue = 255;
        direct = false;
        hstep = random(4, 14);
    }
  }
  else {
    hue -= hstep;
    if (hue <=4) {
     //   hue = 0;
        direct = true;
        hstep = random(4, 14);
    }
  }
  for (byte i = 0; i < (int)db["num_leds"]/2; i++) {
 //   ledss[i] = CHSV((byte)(hue + i * float(255 / ((int)db["num_leds"]/2) )), 255, 255);
    ledss[i]  = ColorFromPalette(gCurrentPalette, (byte)(hue + i * float(255 / ((int)db["num_leds"]/2) )), 255, currentBlending);
    int j = (int)db["num_leds"] - i - 1;
 //   ledss[j] = CHSV((byte)(hue + ((int)db["num_leds"] + i) * float(255 / ((int)db["num_leds"]/2) )), 255, 255);
    ledss[j] = ColorFromPalette(gCurrentPalette, (byte)(hue + ((int)db["num_leds"] + i) * float(255 / ((int)db["num_leds"]/2) )), 255, currentBlending);
  }
}

void sinelon() {
  if (loadingFlag) {
      clr();
  }
  if (direct) {
    hue += hstep;
    if (hue>=250) { 
        hue = 255;
        direct = false;
        hstep = random(4, 14);
    }
  }
  else {
    hue -= hstep;
    if (hue <=4) {
        hue = 0;
        direct = true;
        hstep = random(4, 14);
    }
  }
  fadeToBlackBy(ledss, (int)db["num_leds"], 5);
  byte pos = beatsin16(13, 0, (int)db["num_leds"] - 2);
//  ledss[pos] += CHSV((byte)(hue + pos * float(255 / ((int)db["num_leds"]/2) )), 255, 255);
  ledss[pos] += ColorFromPalette(gCurrentPalette, (byte)(hue + pos * float(255 / ((int)db["num_leds"]/2) )), 255, currentBlending);
//  ledss[pos+1] += CHSV((byte)(hue + pos * float(255 / ((int)db["num_leds"]/2) )), 255, 255);
  ledss[pos+1] += ColorFromPalette(gCurrentPalette, (byte)(hue + pos * float(255 / ((int)db["num_leds"]/2) )), 255, currentBlending);
}


void fire() {                                         // The fill_rainbow call doesn't support brightness levels
  if (loadingFlag) {
    clr();
  }
    uint16_t x = (int)db["num_leds"] / 10;
    uint16_t k1 =      random8(x * 2);       //Жар
    uint16_t k2 =      random8(x * 2) + k1;  //Огонь
    uint16_t k3 = x * 3 + random8(x * 4) + k2; //Пламя
    uint16_t k4 = (int)db["num_leds"] - 1;                //Дым

    if ((k4 - k2) < k3) {
      k3 = k4;
    }
    else {
      k3 = k3 + k2;
    }

    if (thisdir == 1) {        //направление
      fill_gradient_RGB(ledss, 0,  CRGB::White,  k1,       CRGB::Yellow);            //Градинет
      fill_gradient_RGB(ledss, k1, CRGB::Yellow, k2,       CRGB::Red);
      fill_gradient_RGB(ledss, k2, CRGB::Red, k3, CRGB::Black);

      if (k3 < k4) {
        fill_gradient_RGB(ledss, k3, CRGB::Black, k4, CRGB::Black);
      }

      for (uint16_t y = 0; y < x; y++) {
        ledss[random8(k2, (int)db["num_leds"] - 1)] = CRGB::Red;
      }
    }
    else {
      k1 = (int)db["num_leds"] - 1 - k1;                                                       //Поворот
      k2 = (int)db["num_leds"] - 1 - k2;
      if ((int)db["num_leds"]<255) {

          if (((int)db["num_leds"] - 1) < k3) {
            k3 = 0;
          }
          else {
            k3 = (int)db["num_leds"] - 1 - k3;
          }

      } else {
          k3 = (int)db["num_leds"] - 1 - k3;
      }
      fill_gradient_RGB(ledss, k1,  CRGB::White,  k4,       CRGB::Yellow);           //Градиент
      fill_gradient_RGB(ledss, k2, CRGB::Yellow, k1,       CRGB::Red);
      fill_gradient_RGB(ledss, k3, CRGB::Red, k2, CRGB::Black);

      if (k3 > 0) {
        fill_gradient_RGB(ledss, 0, CRGB::Black, k3, CRGB::Black);
      }

      for (uint16_t y = 0; y < x; y++) {
        ledss[random8(k2)] = CRGB::Red;
      }
    }
} // fire()

void blendwave() {
    if (loadingFlag) {
      clr();
    }
    CRGB clr1;
    CRGB clr2;
    uint8_t speed;
    uint8_t loc1;

        speed = beatsin8(6, 0, 255);
        clr1 = blend(CHSV(beatsin8(3, 0, 255), 255, 255), CHSV(beatsin8(4, 0, 255), 255, 255), speed);
        clr2 = blend(CHSV(beatsin8(4, 0, 255), 255, 255), CHSV(beatsin8(3, 0, 255), 255, 255), speed);
        if ((int)db["num_leds"]<255) {
            loc1 = beatsin8(10, 0, (int)db["num_leds"] - 1);
        } else {
            loc1 = beatsin16(10, 0, (int)db["num_leds"] - 1);
        }
        fill_gradient_RGB(ledss, 0, clr2, loc1, clr1);
        fill_gradient_RGB(ledss, loc1, clr2, (int)db["num_leds"] - 1, clr1);

} // blendwave()



void plasma() {
  if (loadingFlag) {
    clr();
    if (loadingFlag==false){
        freq1 = random(5, 33);
        freq2 = random(5, 33);
        phase1 = random(5, 33);
        phase2 = random(5, 33);
    }
  }
  int thisPhase = beatsin8(phase1, -64, 64);                                              // Setting phase change for a couple of waves.
  int thatPhase = beatsin8(phase2, -64, 64);
  uint16_t k;

    for (k = 0; k < (int)db["num_leds"]; k++) {                                                    // For each of the LED's in the strand, set a brightness based on a wave as follows:
      int colorIndex = cubicwave8((k * freq1) + thisPhase) / 2 + cos8((k * freq2) + thatPhase) / 2; // Create a wave and add a phase change and add another wave with its own phase change.. Hey, you can even change the frequencies if you wish, but don't change on the fly.
      int thisBright = qsuba(colorIndex, beatsin8(7, 0, 96));                               // qsub gives it a bit of 'black' dead space by setting sets a minimum value. If colorIndex < current value of beatsin8(), then bright = 0. Otherwise, bright = colorIndex..
      ledss[k] = ColorFromPalette(gCurrentPalette, colorIndex, thisBright, currentBlending);  // Let's now add the foreground colour.
    }
} // plasma()

byte l_var;

void bigcandle() {
  if (loadingFlag) {
    clr();
    if (loadingFlag==false){
        thisdelay = random(10, 25);
        palchg = 0;
        l_var = random(0, 1);
    }
  }
    uint16_t x;
    for (x = 0; x < (int)db["num_leds"]; x++) {
      if (l_var == 1) {
          //Вариант  efimova1969
          uint8_t flicker = random16(1, 80);
      //    ledss[x] = CRGB(255 - flicker * 2, 150 - flicker, flicker / 2);
          ledss[x] = ColorFromPalette(gCurrentPalette, (255 - flicker * 2, 150 - flicker, flicker / 2), 255, currentBlending);
      } else {
          uint8_t flicker = random16(1, 25);
      //    ledss[x] = CRGB(255 - flicker * 2, 63 - flicker, flicker / 2);
          ledss[x] = ColorFromPalette(gCurrentPalette, (255 - flicker * 2, 63 - flicker, flicker / 2), 255, currentBlending);
      }
    }
} // candles()

void colorwaves() {
  if (loadingFlag) {
    clr();
  }
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
  uint16_t i;

    uint8_t brightdepth = beatsin88(341, 96, 224);
    uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
    uint8_t msmultiplier = beatsin88(147, 23, 60);
    uint16_t hue16 = sHue16;//gHue * 256;
    uint16_t hueinc16 = beatsin88(113, 300, 1500);
    uint16_t ms = millis();
    uint16_t deltams = ms - sLastMillis ;
    sLastMillis  = ms;
    sPseudotime += deltams * msmultiplier;
    sHue16 += deltams * beatsin88(400, 5, 9);
    uint16_t brightnesstheta16 = sPseudotime;

    for (i = 0 ; i < (int)db["num_leds"]; i++) {
      hue16 += hueinc16;
      uint8_t hue8 = hue16 / 256;
      uint16_t h16_128 = hue16 >> 7;

      if (h16_128 & 0x100) {
        hue8 = 255 - (h16_128 >> 1);
      }
      else {
        hue8 = h16_128 >> 1;
      }

      brightnesstheta16  += brightnessthetainc16;
      uint16_t b16 = sin16(brightnesstheta16) + 32768;
      uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
      uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
      bri8 += (255 - brightdepth);
      uint8_t index = hue8;
      //index = triwave8( index);
      index = scale8(index, 240);
      CRGB newcolor = ColorFromPalette(gCurrentPalette, index, bri8);

      if (thisdir == 1) {       //направление
        nblend(ledss[((int)db["num_leds"] - 1) - i], newcolor, 128);
      }
      else {
        nblend(ledss[i], newcolor, 128);
      }
    }
}


void confetti_pal() {                                                                                               // random colored speckles that blink in and fade smoothly
  if (loadingFlag) {
    clr();
    if (loadingFlag==false){
        thisdelay = 20;
        thisinc = random(1, 8);
        thisfade = random(1, 16);
        thisdiff = random(1, 8)*8;
    }
  }
    fadeToBlackBy(ledss, (int)db["num_leds"], thisfade);        //Затухание светодиодов на значение thisfade
    uint16_t pos = random16((int)db["num_leds"]);
    ledss[pos] = ColorFromPalette(gCurrentPalette, thisindex + random8(thisdiff) / 4, 255, currentBlending);    // Munge the values and pick a colour from the palette
    thisindex = thisindex + thisinc;                                                                                  // base palette counter increments here.
} // confetti_pal()

uint16_t Xorig = 0x013;
uint16_t Yorig = 0x021;
uint16_t X = Xorig;
uint16_t Y = Yorig;
uint16_t Xn;
uint16_t Yn;


void serendipitous_pal() {
  if (loadingFlag) {
      clr();
  }
  EVERY_N_SECONDS(5) {
    X = Xorig;
    Y = Yorig;
  }
  Xn = X - (Y / 2); Yn = Y + (Xn / 2);
  X = Xn;
  Y = Yn;
  
    fadeToBlackBy(ledss, (int)db["num_leds"], 2);                     // 8 bit, 1 = slow, 255 = fast
    thisindex = (sin8(X) + cos8(Y)) / 2;
    ledss[X % ((int)db["num_leds"])] = ColorFromPalette(gCurrentPalette, thisindex, 255, currentBlending);

} // serendipitous_pal()

uint8_t numdots;

void juggle_pal() {                                           // Several colored dots, weaving in and out of sync with each other
  if (loadingFlag) {
    clr();
    if (loadingFlag==false){
        thisdelay = 10;
        numdots = random(1, 3)*2;
        thisbeat = random(1, 3)*4;
        thisfade = random(1, 8)*4;
        thisdiff = random(1, 8)*8;
    }
  }
    thisindex = 0;                                              // Reset the hue values.
    fadeToBlackBy(ledss, (int)db["num_leds"], thisfade);                  //Затухание к черному

    for (uint16_t i = 0; i < numdots; i++) {
      ledss[beatsin16(thisbeat + i + numdots, 0, (int)db["num_leds"] - 1)] += ColorFromPalette(gCurrentPalette, thisindex, 255, currentBlending);  // Munge the values and pick a colour from the palette
      thisindex += thisdiff;
    }
} // juggle_pal()


int wave1;
int wave2;
int wave3;
uint16_t mul1;
uint16_t mul2;
uint16_t mul3;

void three_sin_pal() {
  if (loadingFlag) {
      clr();
  }
    wave1 += beatsin8(10, -4, 4) * thisdir;
    wave2 += beatsin8(15, -2, 2) * thisdir;
    wave3 += beatsin8(12, -3, 3) * thisdir;
    uint16_t k;

    for (k = 0; k < (int)db["num_leds"]; k++) {
      uint16_t tmp = sin8(mul1 * k + wave1) + sin8(mul1 * k + wave2) + sin8(mul1 * k + wave3);
      ledss[k] = ColorFromPalette(gCurrentPalette, tmp, 255, currentBlending);
    }
} // three_sin_pal()


void matrix_pal() {                                           // One line matrix
  if (loadingFlag) {
      clr();
  }
  if (thisrot) {
    thisindex++;    // Increase palette index to change colours on the fly
  }
    if (random8(90) > 80) {
      if (thisdir == -1) {
        ledss[0] = ColorFromPalette(gCurrentPalette, thisindex, 255, currentBlending);    // Foreground matrix colour
      }
      else {
        ledss[(int)db["num_leds"] - 1] = ColorFromPalette(gCurrentPalette, thisindex, 255, currentBlending);
      }
    }
    else {
      if (thisdir == -1) {
        ledss[0] = CHSV(bgclr, 255, bgbri);    // Background colour
      }
      else {
        ledss[(int)db["num_leds"] - 1] = CHSV(bgclr, 255, bgbri);
      }
    }

    uint16_t i;

    if (thisdir == -1) {                                                                              // Move the foreground colour down the line.
      for (i = (int)db["num_leds"] - 1; i > 0 ; i--) {
        ledss[i] = ledss[i - 1];
      }
    }
    else {
      for (i = 0; i < (int)db["num_leds"] - 1 ; i++) {
        ledss[i] = ledss[i + 1];
      }
    }
} // matrix_pal()

uint16_t dist = 12345;         // A random number for our noise generator.
uint16_t scale = 30;          // Wouldn't recommend changing this on the fly, or the animation will be really blocky.

void noise8_pal() {
  if (loadingFlag) {
      clr();
      if (loadingFlag==false){
          dist = random(100, 12345);
          scale = random(9, 35);
      }
  }
    for (uint16_t i = 0; i < (int)db["num_leds"]; i++) {  // Just ONE loop to fill up the LED array as all of the pixels change.
      uint16_t index = inoise8(i * scale, dist + i * scale) % 255; // Get a value from the noise function. I'm using both x and y axis.
      ledss[i] = ColorFromPalette(gCurrentPalette, index, 255, currentBlending); // With that value, look up the 8 bit colour palette value and assign it to the current LED.
    }

    dist += beatsin8(10, 1, 4) * thisdir;                 // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.
                                                          // In some sketches, I've used millis() instead of an incremented counter. Works a treat.
} // noise8_pal()


uint32_t  x, hue_time;                                        // x & hue_time values
uint16_t octaves = 2;     //2                                  // how many octaves to use for the brightness
uint16_t hue_octaves = 3; //3                                  // how many octaves to use for the hue
int xscale = 5771;      //57771                              // the 'distance' between points on the x axis
uint32_t hxy = 3213;    //43213                              // not sure about this
int hue_scale = 23;      //1                                  // the 'distance' between points for the hue noise
int hue_speed = 1;       //31                                 // how fast we move through hue noise
uint16_t x_speed = 0;     //331                                // adjust this value to move along the x axis between frames
uint16_t hxyinc = 3;       //3

void noise16_pal() {
    if (loadingFlag) {
        clr();
        if (loadingFlag==false){
            octaves = random(2, 6);
            hue_octaves = random(2, 6);
            xscale = random(2222, 6666);
            hue_scale = random(10, 26);
            hue_speed = random(1, 21);
            x_speed = random(0, 221); 
        }
    }
    fill_noise16(ledss, (int)db["num_leds"], octaves, x, xscale, hue_octaves, hxy, hue_scale, hue_time, x_speed);

    hxy += hxyinc * thisdir;
    x += x_speed * thisdir;
    hue_time += hue_speed * thisdir;
} // noise16_pal()

void one_sin_pal() {
  if (loadingFlag) {
      clr();
  }
  startindex += thisinc;
  thisindex = startindex;
  thisphase += thisdir;                                                                       // You can change direction and speed individually.
  uint16_t k;

    for (k = 0; k < (int)db["num_leds"]; k++) {                                                         // For each of the LED's in the strand, set a brightness based on a wave as follows:
      int thisbright = qsubd(cubicwave8((k * allfreq) + thisphase), thiscutoff);                // qsub sets a minimum value called thiscutoff. If < thiscutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
      ledss[k] = CHSV(bgclr, 255, bgbri);                                                        // First set a background colour, but fully saturated.
      ledss[k] += ColorFromPalette(gCurrentPalette, thisindex + k * thisinc, thisbright, currentBlending);
      thisindex += thisrot;
    }
} // one_sin()

uint16_t thathue = 140;                                        // You can change the starting hue for other wave.
uint16_t thatrot = 0;                                          // You can change how quickly the hue rotates for the other wave. Currently 0.
int16_t thatspeed = 4;                                         // You can change the speed, and use negative values.
int thatphase = 0;                                            // Phase change value gets calculated.
uint16_t thatcutoff = 192;                                     // You can change the cutoff value to display that wave. Lower value = longer wave.

void two_sin() {                                                              // This is the heart of this program. Sure is short.
  if (loadingFlag) {
      clr();
      if (loadingFlag==false){
          thathue = random(50, 140);
          thatrot = random(0, 16);
          thatspeed = random(4, 20);
          thatcutoff = random(10, 255);
      }
  }

    thisphase += thisspeed * thisdir;
    thatphase += thatspeed * thisdir;
    thishue = thishue + thisrot;                                                // Hue rotation is fun for thiswave.
    thathue = thathue + thatrot;                                                // It's also fun for thatwave.
    uint16_t k;

    for (k = 0; k < (int)db["num_leds"]; k++) {
      int thisbright = qsuba(cubicwave8((k * allfreq) + thisphase), thiscutoff); // qsub sets a minimum value called thiscutoff. If < thiscutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
      int thatbright = qsuba(cubicwave8((k * allfreq) + 128 + thatphase), thatcutoff); // This wave is 180 degrees out of phase (with the value of 128).
      ledss[k] = ColorFromPalette(gCurrentPalette, thishue, thisbright, currentBlending);
      ledss[k] += ColorFromPalette(gCurrentPalette, thathue, thatbright, currentBlending);
    }

} // two_sin()

void radiation() {
  if (loadingFlag) {
      clr();
      if (loadingFlag==false){
          thathue = random(50, 140);
          thatrot = random(7, 15);
          thatspeed = random(9, 20);
          thatcutoff = random(30, 255);
      }
  }
  int N3  = (int)db["num_leds"] / 3;
  int N6  = (int)db["num_leds"] / 6;
  int N12 = (int)db["num_leds"] / 12;
  if (thisdir) {
    thisphase += thisspeed * thisdir;
    thatphase += thatspeed * thisdir;
    thishue = thishue + thisrot;                                                // Hue rotation is fun for thiswave.
    thathue = thathue + thatrot;
    hue++;
  } else {
    thisphase -= thisspeed * thisdir;
    thatphase -= thatspeed * thisdir;
    thishue = thishue - thisrot;                                                // Hue rotation is fun for thiswave.
    thathue = thathue - thatrot; 
    hue--;
  }
    
  for (int i = 0; i < N6; i++ ) {    //-HACKY, I KNOW...
    tcount = tcount + .08;
    if (tcount > 3.14) {
      tcount = 0.0;
    }
    int thisbright = int(sin(tcount) * 255);
    int thisbreght = qsuba(cubicwave8((i * allfreq) + thisphase), thiscutoff); // qsub sets a minimum value called thiscutoff. If < thiscutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
    int thatbright = qsuba(cubicwave8((i * allfreq) + int(cos(tcount) * 128) + thatphase), thatcutoff);
    int j0 = (hue + i + (int)db["num_leds"] - N12) % (int)db["num_leds"];
    int j1 = (j0 + N3) % (int)db["num_leds"];
    int j2 = (j1 + N3) % (int)db["num_leds"];
    ledss[j0] = ColorFromPalette(gCurrentPalette, thathue, thisbreght + thisbright, currentBlending);
    ledss[j1] = ColorFromPalette(gCurrentPalette, thishue, thisbreght, currentBlending);
    ledss[j2] = ColorFromPalette(gCurrentPalette, thishue, thatbright, currentBlending);
  }
 
}
