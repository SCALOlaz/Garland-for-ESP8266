#pragma once
#include <GyverDBFile.h>

#include <LittleFS.h>
GyverDBFile db(&LittleFS, "data.db");
/*
  // ключи для хранения в базе данных
  DB_KEYS(kk,
    wifi_ssid,
    wifi_pass,
    selectlang,    // Выбор Языка
  );
*/
void db_init() {
  LittleFS.begin();
  db.begin();
  db.init("wifi_ssid", "");
  db.init("wifi_pass", "");

  db.init("sys_pass", "");
  db.init("unique_name", "");
  
  // не двигать по списку!
  db.init("selectlang", (int)i_language);   // Выбор Языка
  db.init("selectwifi", (uint8_t)0);
  db.init("wifiapoff", (bool)0);
  db.init("wifiselpos", (bool)1);   // Сортировать сети по мощности
  
  db.init("toggleleds", (bool)1);
  db.init("toggle_autochange", (bool)0);

  db.init("num_leds", (int)20);
  db.init("selectledoffset", (uint8_t)0);
  db.init("toggleoffset", (bool)0);
  db.init("selectledorder", (uint8_t)0);

  db.init("togglepower", (bool)0);
  db.init("selectpower", (int)1000);
  
  db.init("brightness", 30);
  db.init("maxbrightness", 50);
  db.init("eff_interval", 30);
  db.init("eff_speed", 100);
  db.init("toggle_clear_eff", (bool)0);
  db.init("toggle_candless", (bool)0);
  db.init("candless_start", (int)5);
  db.init("candless_interval", (int)20);
  db.init("toggle_glitter", (bool)0);
  db.init("toggle_background", (bool)1);
//  db.init("background_color", 0x32266d);
  db.init("toggle_pallchange", (bool)1);
  db.init("toggle_onlypall", (bool)0);
  
  db.init("toggle_spark", (bool)0);
  db.init("selectsparkmode", (uint8_t)2);
  db.init("toggle_sparkautochange", (bool)0);
  db.init("spark_big_length", (int)1);
  db.init("spark_big_color", 0xff0000);
  db.init("spark_bengal_length", (int)5);
  db.init("spark_bengal_color", 0xffffff);
  
  db.init("glitter_chance", (int)20);
  db.init("glitter_color", 0xffffff);  
  
  db.init("selecteffect", (uint8_t)0);  
  db.init("selectpalette", (uint8_t)0);
  
  db.init("timeoutsel", (int)400);
  db.init("timeoutreq", (int)3000);
  db.init("timeoutupd", (int)1000);
  db.init("timeoutpin", (int)2500);

  db.init("toggle_autoenable", (bool)0);
  db.init("select_autoenable", (uint8_t)1);
  db.init("counter_autoenable", "");
  
  db.init("toggle_autodisable", (bool)0);
  db.init("select_autodisable", (uint8_t)1);
  db.init("counter_autodisable", "");

  db.init("autodisandencicle", (bool)0);
  
  db.init("selecttheme", (uint8_t)4);

  db.init("toggleota", (bool)0);
  db.init("select_otaenable", (uint8_t)5);
  
  db.init("type", (uint8_t)0);
  
//  db.init("logger", "");
  
  Serial.println("DB Init");
}
