 #pragma once
/*
  Language
  SCALOlaz 10.07.2024 - 20.11.2024
  Разделено на два файла для удобства редактирования и оперирования ключами
  Ключи (langkeys.h) и значения в локализациях (g_strings) должны идти в одинаковом порядке!
*/

#include "util.h"

#define LANG(x) LangManager::getString(LangManager::x)

constexpr int LNG_SIZE = 1;  // Count of Languages

static String arrayLangs[LNG_SIZE] =
{
// Дефолтная локаль должна идти первой, из неё могут браться неизменяемые отображения для других локалей,
// например единицы измерения времени, расстояний и подобное.
  "Русский"
//, "English" 
//  
// Add here some LangName
};


class LangManager
{
  public:
#include "langkeys.h"
    static String &getString(Strings x) {
      return (g_strings[i_language][x] != "") ? g_strings[i_language][x] : g_strings[0][x];
    }
  private:
    LangManager() { }
    ~LangManager() { }
    static String g_strings[LNG_SIZE][LAST];
    static String g_names[LAST];
};

String lwg = "var1;var2";  // Default Array for Language Select Widget

void lang_prepare_number() {
  if (db.get("selectlang")) {
    Serial.print("Language in DB: "); Serial.println(db.get("selectlang"));
    i_language = db.get("selectlang");
  }
  else i_language = 0;
}
void lang_init() {  // Соберём строку из массива имён.
  static String swh = "";
  for (int i = 0; i < LNG_SIZE; i++) {
    swh += arrayLangs[i];
    if (i < (LNG_SIZE - 1) && LNG_SIZE > 1) swh += ";";
  }
  if (swh != "") lwg = swh;  // Если собралась не пустая строка, передаём её в общее дело
  lang_prepare_number();
}


// Translate Area =============================================================

String LangManager::g_strings[LNG_SIZE][LAST] =
{
  // Русский
  {
    "Гирлянда 'Christmass Light'",
    "Обновить страницу",  // REFRESH
    "Настройки",
    "Настройки доп. эффектов",
    "Настройка 'Свечи'",
    "Настройка 'Spark'",
    "Настройка 'Блеск'",
    "Защита настроек",
    "Пароль на важные настройки",
    "Основные параметры LED",
    "Вкл-выкл.", // ONOFFGARLAND
    "Автовкл. через:",  //
    "Автовыкл. через:",  //AUTOOFFGARLAND
    "Осталось:",
    
    "Количество LED-ов",
    "* Пропуск первых LED-ов",
    "* Порядок цветов LED:",
    "Тест цвета после перезапуска",
    
    "* Лимит тока БП:",
    "Яркость",
    "Лимит максимальной яркости",
    "Звук",
    "Прочее",
    "Эффекты",
    "Скорость эффекта",
    "Автосмена эффектов",
    "Интервал смены эффектов",
    "Включить микрофон",  // Microphone
    "Очищать всё между эффектами",
    "Включить 'Свечи'",
    "Позиция первой из свечей",
    "Интервал между свечами",
    "Автосмена палитр",
    "Текущая палитра",
    "Палитры",
    "Только палитровые эффекты",
    "Включить 'Блеск'",
    "Заполнять чёрный фон",
    "Включить 'Spark'",
    "Вид 'Spark':",
    "Случайный вид 'Spark'",
    "Настройки WiFi",
    "WiFi рядом:",
    "Подключиться", // WIFICONNECT
    "Отключиться", // WIFIDISCONNECT
    "Пароль",
    "* Сортировать сети по мощности",
    "Отключить AP на ESP",
    "Очистить БД (сброс настроек)",
    "✅ Информация",    // Information:
    "* - Изменение параметра требует рестарт ESP.\n\n Сразу после первого подключения, установите пароль на Важные Настройки. Вход с паролем осуществляется в Меню в правом верхнем углу.\n\n Настройки WiFi в данной версии, используются только для удобного управления с ПК/ноутбука. Ничего более.",
    " Выберите вашу WiFi сеть из выпадающего списка, укажите пароль и подключитесь.\n\n Отключение AP - выключает Точку Доступа в ESP, система перестанет определяться в поиске WiFi сетей, управлять ей можно будет ТОЛЬКО с ПК/ноутбука, при условии что заданы параметры домашней WiFi.",
    " Лимит яркости задаёт ограничение, чтобы любопытные не смогли крутить яркость на максимум (например для публичных гирлянд).\n\n Порядок цветов у разных производителей адресных лент - разный.",
    " О проекте:",
    " Этот проект основан на проекте 'Christmass Light' by AlexGyver, который в свою очередь, базировался на проекте 'Notamesh', который был переработан из проекта Andrew Tuline, на Ардуино NANO и адресной ленте/гирлянде WS2812b.\n\n Я перевёл проект на ESP8266. Постарался сохранить идентичность эффектов и дополнений, лишь чуточку добавив :)",
    "'💊' - эффекты, которые не будут работать при количестве диодов выше 255 (баг библиотеки FastLED)\n'💢' - эффекты без поддержки палитр.",
    "макс.",
    "* Кастомное имя Системы",
    "* Имя Системы (макс. 6 симв.):",
    "Цветовая Тема контролов:",

    "Вкл.Выкл. автопоиск прошивки",
    "Интервал поиска:",
    "Проверить обновление прошивки",
    "Обновим прошивку?",
    
    "Тип Системы и её параметры",
    "Гирлянда;Лампа;Матрица",
    
    " мс.",
    " c. ",    // секунд
    " мин. ",  // минут
    " час. ",  // часов
    " дн. ",   // дней
    " нед. ",  // недель
  },
/*
 *    АХТУНГ!!! С какого-то момента, перевод на инглиш не соответствует порядку ключей для русского языка. 
 *    Поэтому не надобно подключать инглиш без разбора и сравнения.
 *    Слава пассатижам, китайскую и беларусскую локаль я сам удалил отседова. Мешанина нам не нужна
  // English
  {
    "The 'Christmass Light'",
    "Refresh the page",       // REFRESH
    "System Settings",
    "Effects Settings",
    "'Candless' Settings",
    "'Spark' Settings",
    "Settings Protection",
    "Password for important settings",
    "LED parameters",
    "On-Off a garland",   // ONOFFGARLAND
    "LED's count",
    "Garland brightness",
    "Maximum brightness limit",
    "Audio",
    "Other",
    "Effects List",
    "The speed of the effect",
    "Auto-change effects",
    "Effect change interval",
    "Enable microphone",  // Microphone
    "Clear everything between effects",
    "Enable 'Candless'",
    "First candle position",
    "Led's count between candles",
    "Auto-change palettes",
    "The current palette",
    "List of palettes",
    "Enable 'Glitter'",
    "Filling Black Background",
    "Enable 'Spark'",
    "'Spark' Mode:",
    "'Spark' Random Mode",
    "WiFi Settings",
    "Network List:",
    "Connect", // WIFICONNECT
    "Disconnect", // WIFIDISCONNECT
    "Password",
    "Sort networks by capacity",
    "Disable AP on ESP",
    "Clear the database (reset settings)",
    "✅ Information",   // Information:
    "Immediately after the first connection, set a password for Important Settings. This way, you will save this part of the project from external interference (Login with a password is done in the Menu in the upper right corner).\n\nThe WiFi settings in this version are used only for convenient control of the garland from a PC/laptop. Nothing more.\n\nSpecify the number of diodes for your garland, and the maximum brightness that users can set, on the main project settings page.",
    "About Project:",
    "This project is based on the 'Christmass Light' project by AlexGyver, which in turn was based on the 'Notamesh' project, which was reworked from the Andrew Tuline project, on the Arduino NANO and the WS2812b address ribbon/garland.\n\n Thanks to the appearance of an easy and convenient 'Settings' constructor library by AlexGyver, I transferred the project to ESP8266.\n\n Tried to save the identity of effects and additions, just adding a little bit :)",
    "In the list of effects, the '💊' icon indicates effects that will not work with the number of diodes above 255",
    "max.",
    " ms.",
    " s.",
  },
*/
};
