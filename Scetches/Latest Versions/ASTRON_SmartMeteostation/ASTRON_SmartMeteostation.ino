#include <TroykaMQ.h>
#include <ArduinoJson.h>
#include <SHT21.h>  // include SHT21 library
#include <SoftwareSerial.h> // подключение библиотеки для работы с Software Serial
#include <Nextion.h>
#include <Wire.h>  // библиотека для протокола I2C
#include <Adafruit_BMP280.h> // Библиотека для работы с датчиком BMP280
#include "Parser.h"

#define PIN_MQ135         A0

#define PIN_MQ135_HEATER  11
MQ135 mq135(PIN_MQ135);

// Nextion TX к пин 2, RX к пин 3 Arduino
SoftwareSerial nextion(2, 3);
// создание объекта Nextion к порту на скорости 9600 бод
Nextion myNextion(nextion, 9600);

Adafruit_BMP280 bme; // I2C

SHT21 sht;

///////A1_System///////

const char* host = "api.openweathermap.org";     // тут адрес сервера

char WeatherServer[] = "api.openweathermap.org";
char NewsServer[] = "newsapi.org";

byte indic = 2;

//void myNextion_setComponentText(char* ID, char* string);

float f; //температура2
float p; //давление

float k; //предсказание погоды
float press_new;
float press_old;
float delta_press;

int t16;
int t12;
int t13;
int t17;
int t11;
int t15;


unsigned long OpenWeatherMap = 0;
unsigned long Weather = 0;
unsigned long took = 0;
unsigned long NewsAPI = 0;
unsigned long CoinAPI = 0;


float humidity; // variable to store hemidity

float air;

unsigned long period1 = 0; //как часто печатать данные
unsigned long period2 = 0;
unsigned long timer = 0;

unsigned long minuts = 10 * 60000;  // продолжительность игры в минутах
unsigned long game_time = 0;
unsigned long game = 0;

unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10 * 1000;

boolean http = true;
bool SerialFlag = true;

int indic1 = 0;

String line;
String Newsline;
String Coinsline;

//char str[5]; //вспомогательная строка для преобразований ASCII в число
//uint8_t buf [VW_MAX_MESSAGE_LEN];  //буфер для хранения принятых данных
//uint8_t buflen = VW_MAX_MESSAGE_LEN;  // max длина принятых данных

int cod;
const char* name1;
long id;
int timezone;

long sys_sunset;
long sys_sunrise;
const char* sys_country;
int sys_id;
int sys_type;

long dt;
int clouds_all;
int wind_deg;
int wind_speed;
int visibility;
int main_humidity;
int main_pressure;
float main_temp_max;
float main_temp_min;
float main_feels_like;
float main_temp;

const char* base;
const char* weather_0_icon;
const char* weather_0_description;
const char* weather_0_main;
int weather_0_id;
void setup() {
  Serial.begin(9600); // запуск последовательного порта
  myNextion.init();
  //Serial.println("NextionInit.... OK");
  Wire.begin();
  //Serial.println("WireInit.... OK");
  Serial.setTimeout(5000);

  if (!bme.begin(BMP280_ADDRESS - 1)) {
    Serial.println("BMP280Init.... Err");
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    delay(2000);
  }
  else {
    //Serial.println("BMP280Init.... OK");
  }
  Serial.println("Start");

}

void loop() {

  ///////A7_SystemFunctions///////
  //вычислительная часть
  //Serial.println("QWERTY");
  if (Serial.available() > 0) {
    String WeatherData;
    WeatherData = Serial.readStringUntil("\r");
    Serial.println(WeatherData);
    delay(3000);
    StaticJsonDocument<768> doc;

    DeserializationError error = deserializeJson(doc, WeatherData);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    float coord_lon = doc["coord"]["lon"]; // 104.2964
    float coord_lat = doc["coord"]["lat"]; // 52.2978

    JsonObject weather_0 = doc["weather"][0];
    int weather_0_id = weather_0["id"]; // 621
    const char* weather_0_main = weather_0["main"]; // "Snow"
    const char* weather_0_description = weather_0["description"]; // "shower snow"
    const char* weather_0_icon = weather_0["icon"]; // "13d"

    const char* base = doc["base"]; // "stations"

    JsonObject main = doc["main"];
    float main_temp = main["temp"]; // -8.57
    Serial.print("Temperature: ");
    Serial.println(main_temp);
    float main_feels_like = main["feels_like"]; // -15.57
    float main_temp_min = main["temp_min"]; // -8.57
    float main_temp_max = main["temp_max"]; // -8.57
    int main_pressure = main["pressure"]; // 1027
    int main_humidity = main["humidity"]; // 79

    int visibility = doc["visibility"]; // 1700

    int wind_speed = doc["wind"]["speed"]; // 10
    int wind_deg = doc["wind"]["deg"]; // 300

    float snow_1h = doc["snow"]["1h"]; // 0.27

    int clouds_all = doc["clouds"]["all"]; // 90

    long dt = doc["dt"]; // 1637396223

    JsonObject sys = doc["sys"];
    int sys_type = sys["type"]; // 1
    int sys_id = sys["id"]; // 8891
    const char* sys_country = sys["country"]; // "RU"
    long sys_sunrise = sys["sunrise"]; // 1637368336
    long sys_sunset = sys["sunset"]; // 1637399091

    int timezone = doc["timezone"]; // 28800
    long id = doc["id"]; // 2023469
    const char* name = doc["name"]; // "Irkutsk"
    int cod = doc["cod"]; // 200
  }
  if (millis () - period1 > 7000) {

    period1 = millis();

    f = bme.readTemperature();
    p = bme.readPressure();
    p = p * 0.0075;
    humidity = sht.getHumidity(); // get temp from SHT

    Serial.println();
    Serial.print("Temperature1: ");
    Serial.print(f, 1);
    Serial.println(" *C"); // println - с переносом строки print - без

    Serial.print("Humidity: ");
    Serial.println(humidity);

    Serial.print("Pressure: ");
    Serial.print(p, 1);
    Serial.print(" mmHg");

    if (indic == 0)
    {
      indic1 = 0;
      Serial.println("  rise");
      //myNextion.setComponentValue("va0", int(0));
    }
    if (indic == 1)
    {
      indic1 = 1;
      Serial.println("  fall");
      //myNextion.setComponentValue("va0", int(1));
    }
    if (indic == 2)
    {
      indic1 = 2;
      Serial.println("  without changes");
      //myNextion.setComponentValue("va0", int(2));
    }

  }

  // предсказание погоды
  if (millis () - period2 > 1800000)
  {
    if (k >= 6) // число циклов по 30мин в большом цикле
    {
      press_new = bme.readPressure();
      delta_press = press_new - press_old;
      if (delta_press > 65.0)
      {
        indic = 0;
      }
      else if (delta_press < -65.0)
      {
        indic = 1;
      }
      else
      {
        indic = 2;
      }
      press_new = press_old;
      k = 0;
      period2 = millis();
    }


    k ++;


  }




}

void Init() {
  Serial.begin(115200); // запуск последовательного порта
  myNextion.init();
  Serial.println("NextionInit.... OK");
  Wire.begin();
  Serial.println("WireInit.... OK");
  Serial.setTimeout(5000);

  if (!bme.begin(BMP280_ADDRESS - 1)) {
    Serial.println("BMP280Init.... Err");
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    delay(2000);
  }
  else {
    Serial.println("BMP280Init.... OK");
  }
}
