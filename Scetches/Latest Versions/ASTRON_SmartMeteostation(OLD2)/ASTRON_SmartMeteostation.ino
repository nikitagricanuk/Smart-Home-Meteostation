#include <TroykaMQ.h>
//#include <ArduinoJson.h>
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
    Serial.println("QWERTY2");
    if (SerialFlag == false) {
      delay(3000);

      //while (Serial.available() != 0)
      {

        char Other[528] = {0};
        char weather_0_description[128] = {0};
        char main_temp[64] = {0};
        char main_feels_like[64] = {0};
        char main_temp_min[64] = {0};
        char main_temp_max[64] = {0};
        char main_pressure[64] = {0};
        char main_humidity[64] = {0};
        char visibility[64] = {0};
        char wind_speed[64] = {0};
        char wind_deg[64] = {0};
        char clouds_all[64] = {0};
        char EndofLine[64] = {0};
        
        Serial.readBytesUntil(',', Other, 528);
        delay(300);
        /*
        Serial.readBytesUntil(',', weather_0_description, 128);
        delay(300);
        Serial.readBytesUntil(',', main_temp, 64);
        delay(300);
        
        Serial.readBytesUntil(',', main_feels_like, 64);
        delay(300);
        Serial.readBytesUntil(',', main_temp_min, 64);
        delay(300);
        Serial.readBytesUntil(',', main_temp_max, 64);
        delay(300);
        Serial.readBytesUntil(',', main_pressure, 64);
        delay(300);
        Serial.readBytesUntil(',', main_humidity, 64);
        delay(300);
        Serial.readBytesUntil(',', visibility, 64);
        delay(300);
        Serial.readBytesUntil(',', wind_speed, 64);
        delay(300);
        Serial.readBytesUntil(',', wind_deg, 64);
        delay(300);
        Serial.readBytesUntil(',', clouds_all, 64);
        delay(300);
        Serial.readBytesUntil('/end', EndofLine, 64);
        delay(300);
        */


        Serial.println("***");
        Serial.println(weather_0_description); //light shower snow
        Serial.println(main_temp); //-10.57
        Serial.println(main_feels_like); //-16.20
        Serial.println(main_temp_min); //-10.57
        Serial.println(main_temp_max); //-10.57
        Serial.println(main_pressure); //1025
        Serial.println(main_humidity); //85
        Serial.println(visibility); //3700
        Serial.println(wind_speed); //3
        Serial.println(wind_deg); //310
        Serial.println(clouds_all); //90
        Serial.println(EndofLine); // /end


      }

      //int amount = Serial.readBytesUntil("/end", WeatherData, 300);
      //WeatherData[amount] = NULL;


      /*Parser data(WeatherData, ",");
        int q = data.split();
        for (int i = 0; i < q; i++) {
        Serial.println(data[i]);
        }*/
    }
    else {
      SerialFlag = false;
      //String Other = Serial.readString();
    }

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
