#pragma warning (disable : 4068 ) 
#include <Arduino.h>

#define SETT_NO_TABLE   

#include "config.h"
#include "db.h"

#include <AutoOTA.h>
extern AutoOTA ota;

#include <DBConnector.h>
DBConnector wifi(&db, db["wifi_ssid"], db["wifi_pass"]/*, APName.c_str();*/);

bool eff_work = db["toggleleds"];
String ota_ver = "";
String ota_note = "";

#include "util.h"
#include "lang.h"
#include "wifi.h"

uint32_t otaTimer;  // = millis();;

//#include "util.h"
#include "effects.h"
#include "settings.h"



void setup() {
  delay(1000);    // power-up safety delay
  Serial.begin(115200);
  Serial.println("");
  // инициализация базы данных начальными значениями
  db_init();
  if (db["unique_name"].length()>1) {
  //    APName = APName + v_vers; // Добавим Точке доступа уникальный ID (когда дохуя таких гирлянд в доме)
      APName += " '" + db["unique_name"].toString() + "'";
  }
  eff_init();  // Подготовка списка Эффектов

  /*  Покачто эту фичу WiFiConnect-а не юзаем. Нам хватает стандартных.
      // подключение и реакция на подключение или ошибку
      wifi.onConnect([]() {
          Serial.print("Connected! ");
          Serial.println(WiFi.localIP());
      });
      wifi.onError([]() {
          Serial.print("Error! start AP ");
          Serial.println(WiFi.softAPIP());
      });
      wifi.connect();
  */
  

  // ======= AP =======
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(APName);

  Serial.println("AP IP: " + WiFi.softAPIP().toString());

  // ======= STA =======
  bool wifi_ok = false;

  if (db["wifi_ssid"].length() && (String)"No networks found" != (String)db["wifi_ssid"]) {
    Serial.print("SSID: ");Serial.println(db["wifi_ssid"]);
    WiFi.begin(db["wifi_ssid"], db["wifi_pass"]);
    wifi_ok = true;
    Serial.print("Connecting");
    int tries = 20;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      if (!--tries) {
        wifi_ok = false;
        break;
      }
    }
    Serial.println("");
    
    if (wifi_ok == false) {
        Serial.print("Connection Error. ");
        Serial.printf("Connection status: %d\n", WiFi.status());
        WiFi.printDiag(Serial);
    } else {
        Serial.println("Local IP: " + WiFi.localIP().toString());

        // Disconnection SoftAP
        if (db["wifiapoff"] == true) WiFi.softAPdisconnect(true);
    }
  } else {
    Serial.println("STA not configured");
  }
  Serial.println("");

  //db.dump(Serial);

  wifi_init();
  // ======== SETTINGS ========
  sett_init();
  // ======== CLOCK ========
  lang_init();
}

void LOGln(String str = "") {
  Serial.println(str);
//  Serial.printf("RAM: %d, PSRAM: %d\n", ESP.getFreeHeap(), ESP.getFreePsram());
  Serial.print("getFreeHeap: "); Serial.println(ESP.getFreeHeap());

}
bool rheap = false;

void loop() {
  // тикер, вызывать в лупе
  eff_tick(); // рисуем эффекты на ленте/гирлянде
  sett.tick();  // рисуем вебморду
  ota.tick();
  wifi.tick();  // слушаем вифи (хотя нафига мы слушаем, непонятно, у нас другой метод подключения)
  if (rheap==false) {
      Serial.print("getFreeHeap: "); Serial.println(ESP.getFreeHeap());
      rheap = true;
  }
  if (useOTA && db["toggleota"]== true) ota_check();
}

void ota_check() {
  if (millis() - otaTimer > (int)arrayOta[db["select_otaenable"]]*1000 /*(24ul * 60 * 60 * 1000)*/ ) {
      get_ota_check();
  }
}
