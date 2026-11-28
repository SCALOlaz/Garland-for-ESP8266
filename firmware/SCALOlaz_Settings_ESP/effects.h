#pragma once
/*
  Effects and List
  SCALOlaz 10.07.2024 - 20.11.2024
  Разделено на два файла для удобства редактирования и оперирования
*/
#pragma once
#include "config.h"

//#define FASTLED_INTERNAL
//#define FASTLED_ALL_PINS_HARDWARE_SPI
#include "FastLED.h"
/*
enum EOrder {
  RGB=0012,
  RBG=0021,
  GRB=0102,
  GBR=0120,
  BRG=0201,
  BGR=0210
};
*/
constexpr int OFL_SIZE = 17;  // Count of Offline Size
int arrayOffline[OFL_SIZE] =
{
   15           // 15 секунд
,  60           // 1 минута
,  60*10        // 10 м
,  60*30        // 30 минут
,  60*60        // 1 час
,  60*120       // 2 часа
,  60*(3*60)    // 3 ч
,  60*(4*60)    // 4 ч
,  60*(5*60)    // 5 ч
,  60*360       // 6 часов
,  60*(7*60)    // 7 ч
,  60*(8*60)    // 8 ч
,  60*(9*60)    // 9 ч
,  60*(10*60)   // 10 ч
,  60*(11*60)   // 11 ч
,  60*(12*60)   // 12 часов
//,  60*(18*60)   // 18 ч
,  60*(24*60)   // 24 часа
//,  60*(36*60)   // 36 ч
};

constexpr int OTA_SIZE = 7;  // Count of Offline Size
int arrayOta[OTA_SIZE] =
{
   60           // 1 минута
,  60*60        // 1 час
,  60*(24*60)   // 24 часа
,  60*((24*60)*3.5)   // половина недели
,  60*((24*60)*7)   // 1 неделя
,  60*((24*60)*14)  // 2 недели
,  60*((24*60)*28)  // 4 недели
};

#include "util.h"
struct CRGB ledss[NUM_LEDS<1000 ? NUM_LEDS : 1000];  //(NUM_LEDS>900)?NUM_LEDS:900];

#define qsubd(x, b)  ((x>b)?wavebright:0)                     // A digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b)  ((x>b)?x-b:0)                            // Unsigned subtraction macro. if result <0, then => 0.

CRGBPalette16 gCurrentPalette;                               // Use palettes instead of direct CHSV or CRGB assignments
CRGBPalette16 gTargetPalette;                                // Also support smooth palette transitioning
CRGB solid = CRGB::Black;                                    // Цвет закраски
TBlendType currentBlending = LINEARBLEND;                     // NOBLEND or LINEARBLEND
extern const TProgmemRGBGradientPalettePtr gGradientPalettes[]; // These are for the fixed palettes in gradient_palettes.h
extern const uint8_t gGradientPaletteCount;                     // Total number of fixed palettes to display.
uint8_t gCurrentPaletteNumber = 0;                              // Current palette number from the 'playlist' of color palettes
uint8_t currentPatternIndex = 0;                                // Index number of which pattern is current

bool    candle = false;
uint8_t palchg = 3;                                           // Управление палитрой  3 - менять палитру автоматически иначе нет
uint8_t startindex = 0;                                       // С какого цвета начинать. Переменная для эффектов one_sin_pal.
uint8_t thisbeat;                                             // Переменная для эффектов juggle_pal.
uint8_t thiscutoff = 102;                                     // Если яркость ниже этой, то яркость = 0. Переменная для эффектов one_sin_pal и two_sin.
uint16_t thisdelay = 0;                                       // Задержка delay
uint8_t thisdiff = 1;                                         // Шаг изменения палитры. Переменная для эффектов confetti_pal, juggle_pal и rainbow_march.
int8_t  thisdir = 1;                                          // Направление движения эффекта. принимает значение -1 или 1.
uint8_t thisfade = 224;                                       // Скорость затухания. Переменная для эффектов confetti_pal и juggle_pal.
uint8_t thishue = 0;                                          // Оттенок Переменная для эффектов two_sin.
uint8_t thisindex = 0;                                        // Указатель ан элемент палитры
uint8_t thisinc = 1;                                          // Изменение начального цвета после каждого прохода. Переменная для эффектов confetti_pal и one_sin_pal.
int     thisphase = 0;                                        // Изменение фазы. Переменная для эффектов one_sin_pal, plasma и two_sin.
uint8_t thisrot = 1;                                          // Измение скорости вращения волны. В настоящее время 0.
int8_t  thisspeed = 4;                                        // Изменение стандартной скорости
uint8_t wavebright = 255;

uint8_t tcount = 0;

uint8_t freq1 = 11;
uint8_t freq2 = 23;
int8_t phase1 = 4;
int8_t phase2 = 18;
uint8_t allfreq = 32;                                         // Меняет частоту. Переменная для эффектов one_sin_pal и two_sin.
uint8_t bgclr = 0;                                            // Общий цвет фона. Переменная для эффектов matrix_pal и one_sin_pal.
uint8_t bgbri = 0;                                            // Общая фоновая яркость. Переменная для эффектов matrix_pal и one_sin_pal.

int last_brightness = 0;
//uint32_t autoplayTime = ((long)AUTOPLAY_PERIOD * 1000);

bool gotreload = 0;

#include "util.h"
#include "effects_list.h"


// залить все
void fillAll(CRGB color) {
  for (int i = 0; i < (int)db["num_leds"]; i++) {
    ledss[i] = color;
  }
}

// функция получения цвета пикселя по его номеру
uint32_t getPixColor(int thisPixel) {
  if (thisPixel < 0 || thisPixel > (int)db["num_leds"] - 1) return 0;
  return (((uint32_t)ledss[thisPixel].r << 16) | ((long)ledss[thisPixel].g << 8 ) | (long)ledss[thisPixel].b);
}


constexpr int EF_SIZE = 20;  // Кол-во записей массива эффектов. НЕ забываем считать
struct Eff_Items
{
  bool bBg;           // (bool) Разрешение заполнять чёрный фон в эффекте: 1 = yes, 0 = no
  bool bCand;         // (bool) Разрешение рисовать свечи в эффекте: 1 = yes, 0 = no
  bool bOver;         // (bool) Разрешить эффект, если диодов больше 256 (конфликты шумов фастледа)
  bool bPal;          // (bool) Эффект умеет в !поллитры!
  uint8_t iType;      // (byte) Спец.знак, для какого типа системы данный эффект, 100 - любой, 0 - гирлянда, 1 - матрица, 2 - лампа
  void (*func)();     // (void) Адрес функции эффекта на выполнение  
  String sName;       // (String) Отображаемое название эффекта
};
static Eff_Items arrEff[EF_SIZE] =  // Кол-во записей массива эффектов. НЕ забываем считать !!!!
{
   { 1, 1, 1, 1, 0, rainbow,          "Rainbow" }
  ,{ 1, 1, 1, 1, 0, rainbow_loft,     "Rainbow Loft" }
  ,{ 1, 1, 1, 0, 0, rainbow_beat,     "Rainbow Beat" }
  ,{ 1, 1, 1, 0, 0, rainbow_march,    "Rainbow March" }
  ,{ 1, 1, 1, 1, 0, sinelon,          "SineLon" }
  ,{ 1, 1, 1, 0, 0, fire,             "Fire" }
  ,{ 1, 1, 1, 0, 0, blendwave,        "Blend Wave" }
  ,{ 1, 1, 1, 1, 0, bigcandle,        "Big Candle" }
  ,{ 1, 1, 1, 1, 0, plasma,           "Plasma FX Pal" }
  ,{ 1, 1, 1, 1, 0, colorwaves,       "Color Waves Pal" }
  ,{ 1, 1, 1, 1, 0, two_sin,          "Two Sin Pal" }
  ,{ 1, 1, 1, 1, 0, three_sin_pal,    "Three Sin Pal" }
  ,{ 0, 1, 1, 1, 0, confetti_pal,     "Confetti Pal" } 
  ,{ 1, 1, 1, 1, 0, serendipitous_pal, "Confetti 2 Pal" } 
  ,{ 0, 1, 0, 1, 0, juggle_pal,       "Juggle Pal" }
  ,{ 1, 0, 1, 1, 0, matrix_pal,       "Matrix Pal" }
  ,{ 1, 1, 1, 1, 0, one_sin_pal,      "One Sin Pal" }
  ,{ 0, 1, 0, 1, 0, noise8_pal,       "Noise Pal" }
  ,{ 1, 1, 0, 1, 0, noise16_pal,      "Noise16 Pal" }
  ,{ 1, 1, 1, 1, 0, radiation,        "Radiation Pal" }
  // Несколько эффектов для Типа Лампа
  
  // Далее список эффектов для Типа Матрица
  
};
                  // Кол-во записей массива эффектов. НЕ забываем считать !!!


                  
#include "effects_list.h"               // Эффекты гирлянды, и лампы
// #include "effects_list_matrix.h"     // Эффекты матрицы (Проще было разделить так, чем колхозить туеву хучу if-ов)


String swg = "No Effects";  // Default Array

int EFLLen = 0;

String a_lm = ""; //" (" + (String)EF_SIZE + ")";  // Общее число эффектов.  Уже не актуально

void eff_list(uint8_t tp) {  // Соберём строку из массива имён.
  static String swh = "";
//  Serial.print("Effect List Create with Type = "); Serial.println(tp);
  // tp - Тип системы: 0 - гирлянда, 1 - лампа (считай та-же гирлянда, только ещё постоянный цвет есть)
  swh.clear();
  swg.clear();
  EFLLen = 0;
  for (int i = 0; i < EF_SIZE; i++) {
    if ( arrEff[i].iType == tp || arrEff[i].iType == 100 ) {
        swh += arrEff[i].sName;
//        Serial.println(arrEff[i].sName);
        if (arrEff[i].bOver == 0) swh += " 💊";
        if (arrEff[i].bPal == 0) swh += " 💢";
        if (i < (EF_SIZE - 1) && EF_SIZE > 1) swh += ";";
        EFLLen++;
      }
  }
  if (swh != "") swg = swh; else swg = (String) "No effects";  // Если собралась не пустая строка, передаём её в общее дел
  if (swh == "") db["selecteffect"] = 0;
//  a_lm = " (" + (String)EFLLen + ")";   // Кол-во эффектов для режима
  Serial.println("Effect List Create Complete: "); Serial.println(swg);
}

String palwg = "Not Defined";  // Default Array of Palettes

void pal_list() {
      static String wg = "";
      //palwg = FPSTR(paletteNames);  // Почему-то отказался от такого вида, в том числе в массиве
      byte i_end = gGradientPaletteNamesCount-1;  //sizeof(paletteNames);  // gGradientPaletteCount
      Serial.print("Palettes Count: ");Serial.println(i_end);
      for (byte i=0; i<i_end; i++) {
          wg += (String)paletteNames[i];    // Строковые уже не влезают! :(
       //   if (i<10) wg += "0";
       //   wg += (String)i;
          if (i < (i_end-1)) wg += ";";
      }
      if (wg != "") palwg = wg;
      Serial.println("Palettes List Create");
}

String getTimedLine(int tmt) {
    if (tmt < 0) return "err";
    String act = "";
    int l_tmt = tmt;
    if (tmt >= 604800) {
        act += (String)(tmt/604800) + LANG(TIME_WEEK); // Недели
        tmt = tmt - ((tmt/604800)*604800);
    }
    if (tmt >= 86400 && tmt < 604800) {
        act += (String)(tmt/86400) + LANG(TIME_DAY); // Дни
        tmt = tmt - ((tmt/86400)*86400);
    }
    if (tmt >= 3600 && tmt < 86400) {
        act += (String)(tmt/3600) + LANG(TIME_HRS); // Часы
        tmt = tmt - ((tmt/3600)*3600);
    }
    if (tmt >= 60 && tmt < 3600) {
        act += (String)(tmt/60) + LANG(TIME_MIN);    // Минуты
        tmt = tmt - ((tmt/60)*60);
    } 
    if (tmt<60 && tmt>0 && l_tmt<=180) act += (String)tmt + LANG(TIME_S);     // Секунды, 
                                                                              // так-же рисуем секунды если времени меньше 180 сек
    return act;
}

String offline = "1 min;30 min";  // Default Array

void offline_list() {  // Соберём строку из массива имён.
  static String ofl = "";
  for (int i = 0; i < OFL_SIZE; i++) {

    ofl += getTimedLine(arrayOffline[i]);
    if (i < (OFL_SIZE - 1) && OFL_SIZE > 1) ofl += ";";
  }
  if (ofl != "") offline = ofl;  // Если собралась не пустая строка, передаём её в общее дело
}

String otaline = "1 min;30 min";  // Default Array

void otaline_list() {  // Соберём строку из массива имён.
  static String otaa = "";
  for (int i = 0; i < OTA_SIZE; i++) {

    otaa += getTimedLine(arrayOta[i]);
    if (i < (OTA_SIZE - 1) && OTA_SIZE > 1) otaa += ";";
  }
  if (otaa != "") otaline = otaa;  // Если собралась не пустая строка, передаём её в общее дело
}

void doBrightness() {
    if ((int)db["brightness"]>(int)db["maxbrightness"]) db["brightness"]=(int)db["maxbrightness"];
    if (last_brightness != (int)db["brightness"]) {
      int br = 255 * ((int)db["brightness"]) / 100.0;
      FastLED.setBrightness(br /*(int)db["brightness"]*/);
      last_brightness = (int)db["brightness"];
      Serial.print("Brightness Change: last_b = "); Serial.print(last_brightness);Serial.print("% ; br = ");Serial.println(br);
//      logger.print("Brightness: "); logger.print(br); logger.print(" = "); logger.print(last_brightness); logger.println("%");
    }
}
void get_Order(){ // напролом  "RGB;RBG;GRB;GBR;BRG;BGR"
                  // Изучить: https://community.alexgyver.ru/threads/fastled-nastraivaem-piny-i-porjadok-cvetov-na-letu-ili-kak-rabotat-s-nasledovaniem-klassov-v-c.9732/
    int offs = 0;
    if (db["toggleoffset"].toBool()) {
      offs = db["selectledoffset"].toInt();
      Serial.print("Led Offset: ");Serial.println(offs);
    }
    Serial.print("Set RGB ORDER, ");
    switch (db["selectledorder"].toInt()) {
        case 0: FastLED.addLeds<WS2812B, LED_PIN, RGB>(ledss, offs, NUM_LEDS).setCorrection( TypicalLEDStrip ); Serial.println("LO: RGB"); break;
        case 1: FastLED.addLeds<WS2812B, LED_PIN, RBG>(ledss, offs, NUM_LEDS).setCorrection( TypicalLEDStrip ); Serial.println("LO: RBG"); break;
        case 2: FastLED.addLeds<WS2812B, LED_PIN, GRB>(ledss, offs, NUM_LEDS).setCorrection( TypicalLEDStrip ); Serial.println("LO: GRB"); break;
        case 3: FastLED.addLeds<WS2812B, LED_PIN, GBR>(ledss, offs, NUM_LEDS).setCorrection( TypicalLEDStrip ); Serial.println("LO: GBR"); break;
        case 4: FastLED.addLeds<WS2812B, LED_PIN, BRG>(ledss, offs, NUM_LEDS).setCorrection( TypicalLEDStrip ); Serial.println("LO: BRG"); break;
        case 5: FastLED.addLeds<WS2812B, LED_PIN, BGR>(ledss, offs, NUM_LEDS).setCorrection( TypicalLEDStrip ); Serial.println("LO: BGR"); break;
        default: break;
  }
}

void testRGB(CRGB color) {
    db["toggleleds"] = false;
    eff_work = false;
    fillAll(color);
    doBrightness();
    FastLED.show();
}

void eff_init() {
    pinMode(LED_PIN, OUTPUT);
    get_Order();
    FastLED.clear();
    FastLED.setBrightness(0);
    FastLED.show();
    delay(5);
    FastLED.show();
//    if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
    if (db["togglepower"].toBool()) {
        FastLED.setMaxPowerInVoltsAndMilliamps(5, (int)db["selectpower"]);
        Serial.print("MaxPower Set: ");Serial.println((int)db["selectpower"]);
    }

    randomSeed(analogRead(0) + analogRead(0));    // пинаем генератор случайных чисел
    eff_list(db["type"]);
    if (eff_work) doBrightness();
    
    pal_list();
    gCurrentPalette = gGradientPalettes[0];
    if ((uint8_t)db["selectpalette"] <= gGradientPaletteCount) 
        gCurrentPaletteNumber = (uint8_t)db["selectpalette"];
    else {
        gCurrentPaletteNumber = random8(0, gGradientPaletteCount);  //Случайно поменяем палитру
        db["selectpalette"] = gCurrentPaletteNumber;   
    }
    
    gCurrentPalette /*gTargetPalette*/ = gGradientPalettes[gCurrentPaletteNumber];
    Serial.print("Palette Set to: ");Serial.println(gCurrentPaletteNumber);

    offline_list();
    otaline_list();
   
}

void palChange() {
    gCurrentPalette = gTargetPalette;
    gCurrentPaletteNumber = random8(0, gGradientPaletteCount-1);  //Случайно поменяем палитру
    gCurrentPalette /*gTargetPalette*/ = gGradientPalettes[gCurrentPaletteNumber];
    db["selectpalette"] = gCurrentPaletteNumber;
    
    Serial.print("Palette AutoChange to: ");Serial.println(gCurrentPaletteNumber);
}

void sparkChange() {
    db["selectsparkmode"] = (uint8_t) random8(0, 2);
    Serial.print("Spark AutoChange to: ");Serial.println(db["selectsparkmode"]);
}

uint32_t playTimer;
uint32_t effectsTimer = millis();
uint32_t offlineTimer = millis();
uint32_t onlineTimer = millis();

uint32_t coeffectsTimerOFF = 0;
uint32_t coeffectsTimerON = 0;

int dmode = (int)db["selecteffect"];

void setCountAutoenable() {
  if ( db["toggleleds"] == false && db["toggle_autoenable"].toBool()==true ) {
    onlineTimer = millis();
    coeffectsTimerON = (millis()/1000)+(int)arrayOffline[(uint8_t)db["select_autoenable"]];
  }
}
void setCountAutodisable() {
  if ( db["toggleleds"] == true && db["toggle_autodisable"].toBool()==true ) {
    offlineTimer = millis();
    coeffectsTimerOFF = (millis()/1000)+(int)arrayOffline[(uint8_t)db["select_autodisable"]];
  }
}

void eff_tick() {
  if (db["toggleleds"] == true) {
    doBrightness();
    if ( (millis() - effectsTimer > ((int)db["eff_interval"]*1000)) && db["toggle_autochange"].toBool()==true) {
        dmode = random(0, EF_SIZE);
        
        while ( 
          (dmode == (int)db["selecteffect"] && EFLLen > 0)
          || ((int)db["num_leds"] > 255 && arrEff[dmode].bOver == 0) 
          || (db["toggle_onlypall"].toBool() == true && arrEff[dmode].bPal == 0) 
          // Если сменили тип системы, с меньшим списком эффектов
       //   || ((uint8_t)arrEff[dmode].iType != (uint8_t)db["type"] || (uint8_t)arrEff[dmode].iType != 100) 
        ) {
            dmode = random(0, EF_SIZE);
          }
        db["selecteffect"] = dmode;
        db.update();
        Serial.print("Time to Change Effect: ");Serial.println(dmode);
        loadingFlag = true;
        if (db["toggle_pallchange"] == true) palChange();
        if (db["toggle_spark"] == true && db["toggle_sparkautochange"]) sparkChange();
        thisdir = thisdir * -1;              // random(0,1); //                       // Меняем направление
        effectsTimer = millis();
        Serial.print("getFreeHeap: "); Serial.println(ESP.getFreeHeap());
    }

    if ( db["toggleleds"] == true && (millis() - offlineTimer >= ((int)arrayOffline[db["select_autodisable"]]*1000) && db["toggle_autodisable"].toBool()==true) ){
        Serial.println("Time to Offline Garland is Now");
        db["toggleleds"] = false;   // выключить гирлянду
        if(db["autodisandencicle"]==false) db["toggle_autodisable"] = false; // Выключить автоотключение гирлянды
        eff_work = false;   // уходим в ожидание чуда
        setCountAutoenable();
        gotreload = true;
    }
    if (!eff_work) {
        last_brightness--;
        eff_work = true;
        Serial.println("Wake UP");
    }
    
    bool showFlag = false;
    
    if (millis() - playTimer > (int)db["eff_speed"]) {
        if (
            (uint8_t)db["selecteffect"] > EF_SIZE 
            || ((int)db["num_leds"]>255 && arrEff[(uint8_t)db["selecteffect"]].bOver==0) 
            || (db["toggle_onlypall"].toBool()==true && arrEff[(uint8_t)db["selecteffect"]].bPal==0) 
            // Если сменили тип системы, с меньшим списком эффектов
        //    || (arrEff[(uint8_t)db["selecteffect"]].iType != (uint8_t)db["type"] || arrEff[(uint8_t)db["selecteffect"]].iType != 100 )
        ) {
            dmode = random(0, EF_SIZE);
            while (
              dmode == (int)db["selecteffect"] 
              || ((int)db["num_leds"] > 255 && arrEff[dmode].bOver == 0) 
              || (db["toggle_onlypall"].toBool() == true && arrEff[dmode].bPal == 0) 
              // Если сменили тип системы, с меньшим списком эффектов
          //    || ((uint8_t)arrEff[dmode].iType != (uint8_t)db["type"] || (uint8_t)arrEff[dmode].iType != 100) 
            ) {
                dmode = random(0, EF_SIZE);        
              }
            db["selecteffect"] = dmode;
            db.update();
            Serial.print("Ooooops! Effect bOver Detected! New generation ! : "); Serial.println(dmode);       
        }
        
        (*arrEff[(uint8_t)db["selecteffect"]].func)();          // рисуем выбранный ЭФФЕКТ

        if (db["toggle_background"] && arrEff[(uint8_t)db["selecteffect"]].bBg == true)
            addbackground();                                        // Убираем чёрный фон

        //    radiation();
            
        if (db["toggle_candless"] && arrEff[(uint8_t)db["selecteffect"]].bCand == true)
            addcandle();                                            // Рисуем свечи
        if (db["toggle_glitter"])
            addglitter((int)db["glitter_chance"]);                                         // Рисуем глиттер, что бы это ни было
        if (db["toggle_spark"])
            addsparkler(db["selectsparkmode"]);
        showFlag = true;    
        playTimer = millis();
    }

    if (showFlag) {
//      FastLED.clear();
      FastLED.show();
      delay(5);
      FastLED.show();
    }
  } else {    
    if (eff_work) {
        FastLED.clear();
        FastLED.clearData();   
        FastLED.setBrightness(0);

        FastLED.show();
        delay(5);
        FastLED.show();
        delay(5);
        eff_work = false;
        Serial.println("Shut UP");
    }

    if ( db["toggleleds"] == false && (millis() - onlineTimer >= ((int)arrayOffline[db["select_autoenable"]]*1000) && db["toggle_autoenable"].toBool()==true) ) {
        Serial.println("Time to Online Garland is Now");
        db["toggleleds"] = true;   // включить гирлянду
        if(db["autodisandencicle"]==false) db["toggle_autoenable"] = false; // Выключить автоотключение гирлянды
        eff_work = true;   // уходим в ожидание чуда
        setCountAutodisable();
        gotreload = true;
    }
  }
}
