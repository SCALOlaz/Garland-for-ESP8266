#pragma once
//#include <SettingsAsync.h>
//#include <SettingsBase.h>
#include <SettingsGyver.h>
#include "effects.h"
#include "db.h"
#include "util.h"

int n_ll = NUM_LEDS;
//String a_lm = " (" + (String)EFLLen + ")"; //" (" + (String)EF_SIZE + ")";  // Общее число эффектов.  Уже не актуально
String a_ln = " (" + (String)(gGradientPaletteCount-1) + ")";

uint8_t tab = db["type"]; // 

uint8_t color_theme = db["selecttheme"];   // Тема морды
              const sets::Colors colors[] = {
                sets::Colors::Gray,
                sets::Colors::Red, sets::Colors::Orange, sets::Colors::Yellow,
                sets::Colors::Green, sets::Colors::Mint, sets::Colors::Aqua,
                sets::Colors::Blue, sets::Colors::Violet, sets::Colors::Pink
            };
            
// указывается заголовок меню, подключается база данных

const String settName() {
    String unique = "Christmass Light ";  // + vers;
    if (db["unique_name"].length()>1) {
        unique += ": '" + (String)db["unique_name"] + "'";
    } else {
        unique += vers;
    }
    return unique;
}

AutoOTA ota(VER, URL);

//SettingsAsync sett("Christmass Light " + vers, &db); // "Гирлянда"
SettingsGyver sett("Christmass Light " + vers, &db); // "Гирлянда"
//sets::Timer2 gentmr;
sets::Logger logger(300);

void init_tmr() {
//    int prd = db["auto_prd"];
//    gentmr.setTime(0, max(prd, 60));
//    if (db["toggle_autochange"].toBool()==true) gentmr.startInterval();
//    else gentmr.stop();
}

void get_ota_check() {
//      ota.checkUpdate();
      Serial.println("Check OTA Start");
      otaTimer = millis();
      Serial.print("Check OTA: ");
      String ver, notes;
      if (ota.checkUpdate(&ver, &notes)){
        Serial.print(ver);
        Serial.print(", ");
        Serial.print(notes);
        ota_ver = ver;
        ota_note = notes;
      } else {
          Serial.print("ERROR");
      }
      Serial.println('.');
      Serial.println("Check OTA End");
}

// билдер! Тут строится наше окно настроек
static void build(sets::Builder& b) {

//    b.HTML("", R"(<style>.icon.bars.menubutton {display: none; }</style> )");

  String a_ll = " (" + LANG(MAX) + (String)n_ll + ")";  // Да, каждый билд собираем эту строчку.
/*
//{ sets::GuestAccess g(b);
//    if (b.beginGroup("")) {
//        b.Select(SH("selectlang"), "Language:", lwg);  // Поменяли язык
//        b.endGroup();
//    }
//} // -- sets::GuestAccess
*/

//        static uint8_t tab = db["type"]; // статическая
        
    if (b.beginGroup("")) {
     
        if (b.build.granted && b.beginMenu(LANG(SETTINGS) )) {
		    {          
			    {
            if (b.beginGroup(LANG(SETTINGSPROTECT) )) {
                b.Pass(SH("sys_pass"), "🔑 " + LANG(SETTINGSPASSWORD) );
                b.endGroup();
            }

        //    if (b.beginGroup(LANG(CUSTOMNAME)) ) {
                b.Input(SH("unique_name"), LANG(CUSTOMNAMELEN));
        //        b.endGroup(); }
   
            color_theme = db["selecttheme"];  // Костыль
            if (b.Select(SH("selecttheme"), LANG(COLORTHEME), "Gray;Red;Orange;Yellow;Green;Mint;Aqua;Blue;Violet;Pink", &color_theme)) {
            //    sett.config.theme = colors[(uint8_t)db["selecttheme"]];
                sett.config.theme = colors[color_theme];
                db["selecttheme"] = (uint8_t)color_theme;
                Serial.print("Widget Select Color Theme to: ");Serial.println((uint8_t)db["selecttheme"]);
                b.reload();
            }


            if (b.beginGroup(LANG(SYSPARAM))) {
                b.HTML("", R"(<style>.widget { padding: 3px 10px; }.tab { border-radius: 9px 9px 0 0;box-shadow: inset 0 3px 5px var(--shadow);text-align: center;width: 100%; }</style> )");
                tab = db["type"]; // Костыль
                if (b.Tabs(SH("type"), "Garland;Just Lamp" /*LANG(SYSPARAMLIST)*/, &tab)) {
                    db["type"] = (uint8_t)tab;
                    Serial.print("Widget Tab Change Type to: ");Serial.println((uint8_t)db["type"]);
                //    eff_list(db["type"]); // пересобираем список эффектов
                    // при нажатии перезагружаемся и выходим

                    // Если сменили тип системы, с меньшим списком эффектов
                //    db["selecteffect"] = 0;
                //    effectsTimer = millis()+ 50000;
                    
                    b.reload();
                    return;
                }
                tab = db["type"]; // Костыль есчо раз
                      
                if (tab == 0 || tab == 1) {
                    b.Slider(SH("num_leds"), LANG(MAXLEDS) + a_ll, 1, NUM_LEDS, 1, "");
                } 
                if (tab == 2) {
                  if (b.beginRow("", sets::DivType::Block)) {    // Line, Block, Default 
                    b.Input( " Ширина:" ); 
                    b.Input( " Высота:" ); 
                  b.endRow(); }
                    b.Select( "Метод раскладки:", "Змейка;Зиг-Заг" );
                    b.Select( "Точка подключения:", "Слева внизу;Справа внизу;Справа вверху;Слева вверху" );
                //    b.Input( "Текзт, бегающий по матрасу:" );
                //    b.Switch( "Рисовать время" );
                //    b.Button( "какая-то кнопка например" );               
                } else if (tab == 1) {
                    b.Input( "какой-то инпут допустим" );
                }
                
                b.endGroup();
            }  
            
          }
          if (b.beginGroup("")) {
            if (b.beginMenu(LANG(WIFISETTINGS) )) {

            if (b.beginGroup("")) {
                b.Select(SH("selectwifi"), /*"🌐 " +*/ LANG(WIFILIST), s_networks);  // Выкатываем список найденных сетей
{
                  b.Input(SH("wifi_ssid"), "📶 SSID"); // сюда должно прописаться значение из списка сетей
                  b.Pass(SH("wifi_pass"), "🔑 " + LANG(WIFIPASSWORD) );
                  if (WiFi.status() != WL_CONNECTED)
                      b.Button(SH("wifi_save"), LANG(WIFICONNECT), sets::Colors::Green);  // Подключить
                  else
                      b.Button(SH("wifi_unsave"), LANG(WIFIDISCONNECT), sets::Colors::Blue);  // Отключить

}
                b.Switch(SH("wifiselpos"), LANG(WIFISORT) );
                b.Switch(SH("wifiapoff"), LANG(WIFIAPDISABLE) );
                b.endGroup();
            }
                b.Paragraph(SH("para_wifi"), LANG(PARAGRAPH) + ":", LANG(PARAGRTEXT_WIFI) );  // Переделать в форматируемую строку
                b.endMenu();
            }

				
				      if (b.beginMenu(LANG(LEDPARAM) )) {
					
           //     b.Slider(SH("num_leds"), LANG(MAXLEDS) + a_ll, 1, NUM_LEDS, 1, "");
                // LEDOFFSET
                b.Slider(SH("maxbrightness"), LANG(MAXBRIGHTNESS), 20, 100, 1, " %");
            //    if (b.beginRow("")) {
            //        b.Switch(SH("toggleoffset"), "" );
            //        b.Slider(SH("selectledoffset"), LANG(LEDOFFSET), 1, 10, 1, "");
            //        b.endRow();
            //    }
                if (b.beginRow("")) {
                    b.Switch(SH("togglepower"), "" );
                    b.Slider(SH("selectpower"), LANG(LEDPOWER), 500, 8000, 500, " mA");
                    b.endRow();
                }   

                if (b.beginGroup("")) {
                  b.Select(SH("selectledorder"), LANG(COLORORDER), "RGB;RBG;GRB;GBR;BRG;BGR");
                  if (b.beginRow(LANG(COLORORDERTEST), sets::DivType::Block)) {
                      b.Button(SH("b_red"), "RED", sets::Colors::Red);
                      b.Button(SH("b_green"), "GREEN", sets::Colors::Green);
                      b.Button(SH("b_blue"), "BLUE", sets::Colors::Blue);
                      b.endRow();
                  }
                  b.endGroup();
                }
				          b.Paragraph(SH("para_led"), LANG(PARAGRAPH) + ":", LANG(PARAGRTEXT_LED) );  // Переделать в форматируемую строку
					        b.endMenu();
                }

            
                if (b.beginMenu("* TimeOut's")) {
                    if (b.beginGroup("")) {
                        b.Slider(SH("timeoutsel"), "Select TimeOut  (* 100)", 0, 1000, 50, " ms.");
                        b.Slider(SH("timeoutreq"), "Request TimeOut (* 2000)", 500, 3000, 100, " ms.");
                        b.Slider(SH("timeoutupd"), "Update TimeOut (* 2500)", 500, 3000, 100, " ms.");
						            //b.Slider(SH("timeoutpin"), "Ping TimeOut (* 2500)", 500, 3000, 100, " ms.");
                        b.endGroup();
                    }
                    b.endMenu();
                }


              b.Button(SH("restart"), "Restart ESP", sets::Colors::Red);
              b.endGroup();
            }
            
            if (useOTA && b.beginGroup("")) {
                b.Switch(SH("toggleota"), LANG(AUTOOTA) );
                b.Select(SH("select_otaenable"), LANG(AUTOOTATIME), otaline);

                b.Button(SH("getota"), LANG(SEARCHAUTOOTA), sets::Colors::Green);
                b.endGroup();
            }
		    }
/*
//{ sets::GuestAccess g(b);

      if (b.beginGroup(LANG(LABELAUDIO) )) {
          b.Switch(SH("toggle_mic"), LANG(ONOFFMIC) );
          b.Switch(SH("toggle_mic_reaction"), "Reaction to sound in effects");
          b.endGroup();
      }
      // Ахтунг! На есп8266, без некислой заморочки, оба этих "датчика" работать не будут! Только один из них единомоментно
      if (b.beginGroup(LANG(LABELETC) )) {
          b.Switch("sw2"_h, "Включить датчик освещения");

          b.endGroup();
      }

//} //-- LANG(SETTINGS
*/
		b.Paragraph(SH("para_master"), LANG(PARAGRAPH) + ":", LANG(PARAGRTEXT_MASTER) );  // Переделать в форматируемую строку
        b.endMenu();  // не забываем завершить меню
    }
    
      
      { sets::GuestAccess g(b);
          b.Switch(SH("toggleleds"), LANG(ONOFFGARLAND) );

          if (b.beginRow("")) {
              b.Switch(SH("toggle_autoenable"), "");
              b.Select(SH("select_autoenable"), LANG(AUTOONGARLAND), offline);
          b.endRow();
          }
          if (db["toggle_autoenable"]) {
                b.Label(SH("counter_autoenable"), LANG(AOGOFFSET), " ", sets::Colors::Green);  // Осталось времени
          }
          
          if (b.beginRow("")) {
              b.Switch(SH("toggle_autodisable"), "");
              b.Select(SH("select_autodisable"), LANG(AUTOOFFGARLAND), offline);
          b.endRow();
          }
          if (db["toggle_autodisable"]) {
                b.Label(SH("counter_autodisable"), LANG(AOGOFFSET), " ", sets::Colors::Green);  // Осталось времени
          }
          b.Slider(SH("brightness"), LANG(BRIGHTNESS), 1, 100, 1, " %");
      } //-- sets::GuestAccess
        b.endGroup();  // НЕ ЗАБЫВАЕМ ЗАВЕРШИТЬ ГРУППУ
    } //-- b.beginGroup("") 61

{ sets::GuestAccess g(b);

    if (b.beginGroup("")) {
        if (b.beginMenu(LANG(EFFSETTINGS) )) {
            if (b.beginGroup("")) {
                b.Switch(SH("toggle_onlypall"), LANG(ONLIPALEFF) );
                b.Switch(SH("toggle_pallchange"), LANG(ONOFFPALETTES) );
           //     b.Label("palettename"_h, LANG(PALLNAME) + ":", (String)paletteNames[gCurrentPaletteNumber], sets::Colors::Green);
                b.Select(SH("selectpalette"), LANG(PALLLIST) + a_ln + ":", palwg);
                b.Switch(SH("toggle_clear_eff"), LANG(ONOFFCLR) );
                b.Switch(SH("toggle_background"), LANG(ONOFFFILLINGBKG) );

                if (b.beginRow("")) {
                    b.Switch(SH("toggle_glitter"), /*LANG(ONOFFCANDLESS)*/ "" );
                    if (b.beginMenu(LANG(GLITTERSETTINGS) )) {
                        if (b.beginGroup("")) {
                        //    b.Switch(SH("toggle_glitter"), LANG(ONOFFGLITTER) );
                            b.Slider(SH("glitter_chance"), "Вероятность отрисовки", 5, 40, 5, "");
                            b.Color(SH("glitter_color"), "Цвет наложения");
                            b.endGroup();
                        }  
                        b.endMenu();
                    }
                    b.endRow();
                }
                               
                if (b.beginRow("")) {
                    b.Switch(SH("toggle_candless"), /*LANG(ONOFFCANDLESS)*/ "" );
                    if (b.beginMenu(LANG(CANDLESSSETTINGS) )) {
                        if (b.beginGroup("")) {
                        //    b.Switch(SH("toggle_candless"), LANG(ONOFFCANDLESS) );
                            b.Slider(SH("candless_start"), LANG(CANDLESSFIRST), 1, 30, 1, "");
                            b.Slider(SH("candless_interval"), LANG(CANDLESSINTERVAL), 10, 30, 1, "");
                            b.endGroup();
                        }  
                        b.endMenu();
                    }
                    b.endRow();
                }
                if (b.beginRow("")) {
                b.Switch(SH("toggle_spark"), /*LANG(ONOFFSPARK)*/ "" );
                if (b.beginMenu(LANG(SPARKSETTINGS) )) {
                    if (b.beginGroup("")) {
                    //    b.Switch(SH("toggle_spark"), LANG(ONOFFSPARK) );
                        b.Select(SH("selectsparkmode"), LANG(SPARKMODE), "Bengal Fire;Big Star"); // ;Meteorite
                        b.Switch(SH("toggle_sparkautochange"), LANG(SPARKSRANDOM) );
                        b.endGroup();
                    }
                    if (b.beginGroup("Bengal Fire")) {
                        b.Slider(SH("spark_bengal_length"), "Кол-во диодов", 5, 50, 1, "");
                        b.Color(SH("spark_bengal_color"), "Цвет (без учёта палитр!)");
                        b.endGroup();
                    }
                    if (b.beginGroup("Big Star")) {
                        b.Slider(SH("spark_big_length"), "Кол-во", 1, 50, 1, "");
                        b.Color(SH("spark_big_color"), "Цвет");
                        b.endGroup();
                    }
                    b.endMenu();
                }
                b.endRow();
                }
                b.endGroup();
            }  
            b.endMenu();  // не забываем завершить меню
        }
        
        b.Select(SH("selecteffect"), LANG(EFFECTLIST) + a_lm +":", swg);
        b.Label("palettename2"_h, LANG(PALLNAME) + ":", (String)paletteNames[gCurrentPaletteNumber], sets::Colors::Green);
        b.Slider(SH("eff_speed"), LANG(EFFECTSPEED), 20, 180, 5, LANG(TIME_MS));
        if (b.Switch(SH("toggle_autochange"), LANG(EFFECTSACHANGE) )) b.reload();
        if (db["toggle_autochange"]) {
            b.Slider(SH("eff_interval"), LANG(EFFECTSINTERVAL), 5, 200, 5, LANG(TIME_S));
        }

        b.endGroup();  // НЕ ЗАБЫВАЕМ ЗАВЕРШИТЬ ГРУППУ
    }
    
    if (b.beginGroup("")) {
        if (b.beginMenu(LANG(PARAGRAPH) )) {
            b.Paragraph(SH("para_guest"), LANG(PARAGRNAME), LANG(MAINPAGE) + " " + vers + "\n" + LANG(PARAGRTEXT_GUEST) + "\n\n" + LANG(PARAGRTEXT_EXT) + "\n\nZippozend (aka SCALOlaz), Oct. 2024 +");
            b.endMenu();
        }
        b.endGroup();
    }

} // End GuestAccess

/*
    if (b.beginGroup("")) {
        if (b.beginMenu("Экскременты")) {
            if (b.beginGroup("")) {
                // логгер, в него печатаем выше
                b.Log(SH("logger"), logger);
                b.Button(SH("log_clear"), "Clear Log", sets::Colors::Yellow);
                b.endGroup();
            }        
        b.endMenu();
        }
    b.endGroup();
    }
*/
      if (b.build.granted && b.Confirm("ota_update"_h)) {
        Serial.print("Confirmed: ");Serial.println((uint8_t)b.build.value);
          if (b.build.value.toBool()) {
              Serial.println("OTA update! Wait please");
              
              ota.updateNow();
              delay(2000);
              ESP.restart();
              b.reload();
          }
      }
    
  // можно узнать, было ли действие по виджету
    if (b.build.isAction()) {
    switch (b.build.id) {
       case SH("selecttheme"):
          Serial.print("isAction Change Theme to: ");Serial.println((uint8_t)b.build.value);
          db["selecttheme"] = (uint8_t)b.build.value;
          db.update();
          break;
          
       case SH("type"):
          Serial.print("isAction Change Type to: ");Serial.println((uint8_t)b.build.value);
          db["type"] = (uint8_t)b.build.value;
          db.update();
          eff_list(db["type"]); // Пересобираем список эффектов
          break;
          
      case SH("sys_pass"):
          sett.setPass((String)b.build.value);
          break;
      case SH("selectlang"): // Махнули Язык оболочки на другой
          i_language = (uint8_t)b.build.value;
          b.reload();
          break;
      case SH("selectwifi"):  // Махнули вафлю на другую, её надо вонзить в поле SSID
          i_wifinet = b.build.value;  // Оно вонзится в апдейтере
          db["wifi_ssid"] = (String)netnames[i_wifinet];
          db.update();
          break;
      case SH("wifiapoff"):
          if (WiFi.localIP()) {
              WiFi.softAPdisconnect(db["wifiapoff"]);
          }
          if (b.build.value == "0") WiFi.softAP(APName);
          break;
      case SH("wifi_save"):
          db.update();
          if (db["wifi_ssid"].length() && (String)"No networks found" != (String)db["wifi_ssid"]) {
              ESP.restart();
          }
          break;
      case SH("wifi_unsave"):
          db.update();
          WiFi.disconnect(false);
          break;
      case SH("restart"):
          db.update();
          FastLED.clear(true);
          delay(1000);  // Попробуем притормозить МК, а вдруг эксепшен пропадёт ))
          ESP.restart();
          break;
      case SH("log_clear"):
          logger.clear();
          break;
      case SH("selecteffect"):
          db["toggle_autochange"] = false;
          Serial.print("Change effect to: ");Serial.println((uint8_t)b.build.value);
          if (db["toggle_pallchange"]) palChange();
          if (db["toggle_spark"] && db["toggle_sparkautochange"]) sparkChange();
          thisdir = thisdir * -1; // random(0,1);
          db.update();
          loadingFlag = true;          
          b.reload();
          break;
      case SH("selectpalette"):
          db["toggle_pallchange"] = false;
          Serial.print("Change palette to: ");Serial.println((uint8_t)b.build.value); //Serial.println(db["selectpalette"]);
          gCurrentPaletteNumber = (uint8_t)b.build.value;   //db["selectpalette"];
          gCurrentPalette /*gTargetPalette*/ = gGradientPalettes[gCurrentPaletteNumber];
          db.update();
          break;
      case SH("selectledorder"):
          db.update();
          Serial.print("Change LEDS RGB ORDER to: ");Serial.println((uint8_t)b.build.value);
          logger.print("Change LEDS RGB ORDER to: ");logger.println((uint8_t)b.build.value);
          break;
      case SH("eff_speed"):
          db.update();
          Serial.println("Change speed");
          break;
      case SH("toggleleds"):
          db.update();
          setCountAutoenable();
          setCountAutodisable();
          db["toggle_autoenable"] = false;
          db["toggle_autodisable"] = false;
          b.reload();
          Serial.println("On-Off Garland");
      //    if (eff_work==false) eff_work=true;
          break;
      case SH("brightness"):
      case SH("maxbrightness"):
          db.update();
          break;
      case SH("b_red"):
          testRGB(CRGB::Red);
          break;
      case SH("b_green"):
          testRGB(CRGB::Green);
          break;
      case SH("b_blue"):
          testRGB(CRGB::Blue);
          break;
      case SH("toggle_autochange"):
          Serial.print("Change Autochange to: ");Serial.println((uint8_t)b.build.value);
          effectsTimer = millis();
          break;
      case SH("toggle_autoenable"):
          db.update();
          onlineTimer = millis();
          setCountAutoenable();
          b.reload();
          Serial.print("Change Autoenable to: ");Serial.println((uint8_t)b.build.value);
          break;     
      case SH("select_autoenable"):
          db.update();
          setCountAutoenable();
          Serial.print("Change Autoenable time to: ");Serial.println(getTimedLine(arrayOffline[(uint8_t)b.build.value]));
          break;
      case SH("toggle_autodisable"):
          db.update();
          offlineTimer = millis();
          setCountAutodisable();
          b.reload();
          Serial.print("Change Autodisable to: ");Serial.println((uint8_t)b.build.value);
          break;     
      case SH("select_autodisable"):
          db.update();
          setCountAutodisable();
          Serial.print("Change Autodisable time to: ");Serial.println(getTimedLine(arrayOffline[(uint8_t)b.build.value]));
          break;
       case SH("getota"):
          Serial.print("isAction Manual, ");
          get_ota_check();
          break;
    }

    logger.print("Turn widget: 0x");
    logger.println(b.build.id, HEX);
  }
}


// это апдейтер. Функция вызывается, когда вебморда запрашивает обновления
void update(sets::Updater& u) {
    if (gotreload) {
        sett.reload();
        gotreload=false;      
    }
//  u.update("palettename"_h, (String)paletteNames[gCurrentPaletteNumber]);
  u.update("palettename2"_h, "(" + (String)gCurrentPaletteNumber + ") " + (String)paletteNames[gCurrentPaletteNumber]);
//  u.update(SH("selecteffect"), (int)dmode );  // Принудительно апаем виджет! В новых версиях Settings это починено.
  u.update(SH("logger"), logger);
  
  // можно отправить значение по имени (хэшу) виджета
  // Ловим изменение выбранной сети, и применяем
  if (i_wifinet != -1) {  // Обновим ОДИН раз
    u.update(SH("wifi_ssid"), (String)netnames[i_wifinet]);
    i_wifinet = -1;
  }

  if ( db["toggleleds"] == false && db["toggle_autoenable"].toBool()==true ) {
      u.update(SH("counter_autoenable"), (String)getTimedLine((coeffectsTimerON-(millis()/1000))));
//      Serial.print("Online Elapse: ");Serial.println((String)getTimedLine((coeffectsTimerON-(millis()/1000))));
  } else
      u.update(SH("counter_autoenable"), "--");
      
  if ( db["toggleleds"] == true && db["toggle_autodisable"].toBool()==true ) {
      u.update(SH("counter_autodisable"), (String)getTimedLine((coeffectsTimerOFF-(millis()/1000))));
//      Serial.print("Offline Elapse: ");Serial.println((String)getTimedLine((coeffectsTimerOFF-(millis()/1000))));
  } else
      u.update(SH("counter_autodisable"), "--");
  // примечание: при ручных изменениях в базе данных отправлять новые значения не нужно!
  // библиотека сделает это сама =)
  
  if (ota.hasUpdate()) u.update("ota_update"_h, "Your Version: " + vers + "New Version: v." + ota_ver + "\r\nNote: " + ota_note + "\r\n" + LANG(OTADONE) /*"Доступно обновление. Обновить прошивку?"*/);
}


void sett_init() {
  sett.begin();
//  sett.config.theme = colors[color_theme];
  sett.config.theme = colors[(uint8_t)db["selecttheme"]];
  Serial.print("Set Color Theme to: ");Serial.println((uint8_t)db["selecttheme"]);
  
  sett.onBuild(build);
  sett.onUpdate(update);
  sett.useAutoUpdates(true);
  if (db["sys_pass"] != "") {
      sett.setPass((String)db["sys_pass"]);
  }
  if (db["num_leds"] > NUM_LEDS)
      db["num_leds"] = NUM_LEDS;
    // настройки вебморды
    sett.config.requestTout = db["timeoutreq"];
    sett.config.sliderTout = db["timeoutsel"]?db["timeoutsel"]:200;
    sett.config.updateTout = db["timeoutupd"];
	  //sett.config.updatePing = db["timeoutpin"];

  sett.setTitle(settName());
  sett.setVersion(vers.c_str()); // vers
  sett.setProjectInfo(LANG(MAINPAGE).c_str(), "https://t.me/AlexGyverChat/484661/588262");
  setCountAutodisable();
  setCountAutoenable();
  sett.setPacketSize(2048); // Размер пакета, которым швыряемся туда-сюда. Дефолт 1024

}

void sett_tick() {
  sett.tick();
}
