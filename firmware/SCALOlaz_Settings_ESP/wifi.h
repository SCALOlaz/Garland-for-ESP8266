#pragma once
// Для поднятия важности себе, читаем https://www.arduino.cc/reference/en/libraries/wifi/

/*
  WiFi utilites
  SCALOlaz 10.07.2024 - 20.11.2024
*/

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

//#include "util.h"

String s_networks = "No networks found";  // Дефолтная мессага, если не найдём вафельки
int i_wifinet = -1;

constexpr int MAX_NAMES = 20;             // Максимум запезей в списоке
String netnames[MAX_NAMES];               // С этим списком сетей будем работать всю сессию

String getLevel(int lvl) {
    String s_lvl = "";
//    lvl = lvl + 100; //*(-1);
    return (String)lvl + "dBm";           // Уроверь мощности вифи в попугаях
}

void wifi_init() {
  Serial.print("=== Wifi Networks: ");
  int n = WiFi.scanNetworks();            // Скока вокруг этого г%вна... капец
  if (n == 0)
    Serial.println(s_networks);
  else {
    Serial.println(n);
    int indices[n];

    for (int i = 0; i < n; i++) {
      indices[i] = i;
    }
    // Какой-то древний вид сортировки по уровню сигнала
    if (db["wifiselpos"]) {           // Будем сортировать список вифи?
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i])) {
                    std::swap(indices[i], indices[j]);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {   // Дебаг списка сетей и их мощность
      Serial.print(WiFi.SSID(indices[i]));
      Serial.print("  level: ");
      Serial.print(WiFi.RSSI(indices[i]));
      Serial.print(" key: ");
      Serial.println(WiFi.encryptionType(indices[i]));
    }
    
/*  Returns
    byte : value represents the type of encryption
    TKIP (WPA) = 2 WEP = 5 CCMP (WPA) = 4 NONE = 7 AUTO = 8
 */
    String swh = "";
        String my_ssid = (String)db["wifi_ssid"];
        for (int i = 0; i < n; i++) {
          if (i < MAX_NAMES) {      
              swh += WiFi.SSID(indices[i]); // + " (" + WiFi.RSSI(indices[i]) + " dBm";   // Добавляем говяшек в текст
              swh += "  ";
              if (WiFi.encryptionType(indices[i])==7) swh +=""; else swh +=" 🔐";  // Запаролено, распаролено
              swh += getLevel(WiFi.RSSI(indices[i]));                               // Завершили упражнение
              netnames[i] = WiFi.SSID(indices[i]);                                  // Запишем в массив только имя сети
              // Вот эта строчка видимо, иногда неправильно выполняет свою функцию, отчего JSON в Settings шлёт ошибку, пока не пнёшь весь колхоз, и он
              // заново не перестроит список вафель.
              if ((String)WiFi.SSID(indices[i]) == my_ssid) db["selectwifi"] = i;   // i_sortchanged = i;  // 
          }
          if (i < (n - 1) && n > 1 && i < (MAX_NAMES - 1)) swh += ";";       // Если список ещё не окончен, поставим разделитель
        }

    if (swh != "") s_networks = swh;              // Мы точно собрали какой-то набор вафель?
  }
  delay(100);                                     // Остужаем модуль вифи ЕСП, штоп не задымился
}
