#pragma once
#define VER "3.6"
#define NAME "Garland"
#define URL "SCALOlaz/Garland-for-ESP8266/master/project.json"
bool useOTA = true; // Использовать автопоиск новой прошивки или нет?

String APNver = "APGarland ";   // Кастомим Имя Точки Доступа ЕСП

// Все настройки находятся в "морде", подключитесь к точке доступа ЕСП, и настраивайте.
// Здесь - минимум, который и трогать не нужно в принципе.

// ========== Лента ==========

#define LED_PIN D4            // пин ESP8266, куда подключена лента ws2812b или гирлянда ws2812b

#define LED_BRIGHTNESS 30     // стартовая яркость (0-255)
//#define CURRENT_LIMIT 0    // лимит по току в миллиамперах, автоматически управляет яркостью (пожалей свой блок питания!) 0 - выключить лимит

#define NUM_LEDS 1000          // Максимум LED-ов. От этого зависит размер буфера

#define LOG 123               // закомментировать, если не нужен вывод в Serial. Экономия рамы в МК


/* 
 *  0 = "Русский",
 *  1 = "English",
*/
uint8_t i_language = 0;                   // Стартовый язык морды: 0 - русский

boolean loadingFlag = true;               // Не трогаем

// ========== Морда Управления - Settings ==========
String vers = "v." + (String)VER;                     // Номер ревизии

String APName = APNver + vers;
//const String APName = (db["ap_name"]!="")?APNver + db["ap_name"]:APNver + v_vers;
