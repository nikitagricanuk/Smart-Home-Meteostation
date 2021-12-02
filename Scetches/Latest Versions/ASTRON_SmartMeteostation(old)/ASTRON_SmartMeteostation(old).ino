#include <TroykaMQ.h>
//#include <Ethernet.h>
#include <ArduinoJson.h>
#include <SHT21.h>  // include SHT21 library
//#include <SoftwareSerial.h> // подключение библиотеки для работы с Software Serial
//#include <Nextion.h>
#include <Wire.h>  // библиотека для протокола I2C
//#include <SPI.h>  // Библиотека для работы с шиной SPI
#include <Adafruit_BMP280.h> // Библиотека для работы с датчиком BMP280
//#include <VirtualWire.h>
#include <ESP8266WiFi.h>

const char* ssid     = "WLAN1";         // тут SSID и пароль к WIFI
const char* password = "1231234123";

#define PIN_MQ135         A0

#define PIN_MQ135_HEATER  11
MQ135 mq135(PIN_MQ135);
//Nextion myNextion;

//Nextion nextion(2, 3);
//Nextion myNextion(nextion, 9600);
//HardwareSerial nextion(2, 3);

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

/*
  int cod;
  int message;
  int cnt;

  long list_0_dt;



  int list_0_main_temp;
  float list_0_main_feels_like;
  int list_0_main_temp_min;
  float list_0_main_temp_max;
  int list_0_main_pressure;
  int list_0_main_sea_level;
  int list_0_main_grnd_level;
  int list_0_main_humidity;
  float list_0_main_temp_kf;


  int list_0_weather_0_id;
  const char* list_0_weather_0_main;
  const char* list_0_weather_0_description;
  const char* list_0_weather_0_icon;

  int list_0_clouds_all;


  float list_0_wind_speed;
  int list_0_wind_deg;
  float list_0_wind_gust;

  int list_0_visibility;
  float list_0_pop;

  float list_0_snow_3h;

  const char* list_0_sys_pod;

  const char* list_0_dt_txt;


  long list_1_dt;


  float list_1_main_temp;
  float list_1_main_feels_like;
  float list_1_main_temp_min;
  float list_1_main_temp_max;
  int list_1_main_pressure;
  int list_1_main_sea_level;
  int list_1_main_grnd_level;
  int list_1_main_humidity;
  float list_1_main_temp_kf;


  int list_1_weather_0_id;
  const char* list_1_weather_0_main;
  const char* list_1_weather_0_description;
  const char* list_1_weather_0_icon;

  int list_1_clouds_all;


  float list_1_wind_speed;
  int list_1_wind_deg;
  float list_1_wind_gust;

  int list_1_visibility;
  int list_1_pop;

  const char* list_1_sys_pod;

  const char* list_1_dt_txt;


  long list_2_dt;


  float list_2_main_temp; // -0.73
  float list_2_main_feels_like; // -3.07
  float list_2_main_temp_min; // -1.09
  float list_2_main_temp_max; // -0.73
  int list_2_main_pressure; // 1015
  int list_2_main_sea_level; // 1015
  int list_2_main_grnd_level; // 961
  int list_2_main_humidity; // 69
  float list_2_main_temp_kf; // 0.36


  int list_2_weather_0_id;
  const char* list_2_weather_0_main;
  const char* list_2_weather_0_description;
  const char* list_2_weather_0_icon;

  int list_2_clouds_all;


  float list_2_wind_speed;
  int list_2_wind_deg;
  float list_2_wind_gust;

  int list_2_visibility;
  int list_2_pop;

  const char* list_2_sys_pod;

  const char* list_2_dt_txt;


  long list_3_dt;


  float list_3_main_temp;
  float list_3_main_feels_like;
  float list_3_main_temp_min;
  float list_3_main_temp_max;
  int list_3_main_pressure;
  int list_3_main_sea_level;
  int list_3_main_grnd_level;
  int list_3_main_humidity;
  int list_3_main_temp_kf;


  int list_3_weather_0_id;
  const char* list_3_weather_0_main;
  const char* list_3_weather_0_description;
  const char* list_3_weather_0_icon;

  int list_3_clouds_all;


  float list_3_wind_speed;
  int list_3_wind_deg;
  float list_3_wind_gust;

  int list_3_visibility;
  int list_3_pop;

  const char* list_3_sys_pod;

  const char* list_3_dt_txt;


  long list_4_dt;


  float list_4_main_temp;
  float list_4_main_feels_like;
  float list_4_main_temp_min;
  float list_4_main_temp_max;
  int list_4_main_pressure;
  int list_4_main_sea_level;
  int list_4_main_grnd_level;
  int list_4_main_humidity;
  int list_4_main_temp_kf;


  int list_4_weather_0_id;
  const char* list_4_weather_0_main;
  const char* list_4_weather_0_description;
  const char* list_4_weather_0_icon;

  int list_4_clouds_all;


  float list_4_wind_speed;
  int list_4_wind_deg;
  float list_4_wind_gust;

  int list_4_visibility;
  float list_4_pop;

  float list_4_snow_3h;

  const char* list_4_sys_pod;

  const char* list_4_dt_txt;


  long list_5_dt;


  float list_5_main_temp;
  float list_5_main_feels_like;
  float list_5_main_temp_min;
  float list_5_main_temp_max;
  int list_5_main_pressure;
  int list_5_main_sea_level;
  int list_5_main_grnd_level;
  int list_5_main_humidity;
  int list_5_main_temp_kf;


  int list_5_weather_0_id;
  const char* list_5_weather_0_main;
  const char* list_5_weather_0_description;
  const char* list_5_weather_0_icon;

  int list_5_clouds_all;


  float list_5_wind_speed;
  int list_5_wind_deg;
  float list_5_wind_gust;

  int list_5_visibility;
  float list_5_pop;

  const char* list_5_sys_pod;

  const char* list_5_dt_txt;


  long list_6_dt;


  float list_6_main_temp;
  float list_6_main_feels_like;
  float list_6_main_temp_min;
  float list_6_main_temp_max;
  int list_6_main_pressure;
  int list_6_main_sea_level;
  int list_6_main_grnd_level;
  int list_6_main_humidity;
  int list_6_main_temp_kf;


  int list_6_weather_0_id;
  const char* list_6_weather_0_main;
  const char* list_6_weather_0_description;
  const char* list_6_weather_0_icon;

  int list_6_clouds_all;


  float list_6_wind_speed;
  int list_6_wind_deg;
  float list_6_wind_gust;

  int list_6_visibility;
  float list_6_pop;

  const char* list_6_sys_pod;

  const char* list_6_dt_txt;


  long list_7_dt;


  float list_7_main_temp;
  float list_7_main_feels_like;
  float list_7_main_temp_min;
  float list_7_main_temp_max;
  int list_7_main_pressure;
  int list_7_main_sea_level;
  int list_7_main_grnd_level;
  int list_7_main_humidity;
  int list_7_main_temp_kf;


  int list_7_weather_0_id;
  const char* list_7_weather_0_main;
  const char* list_7_weather_0_description;
  const char* list_7_weather_0_icon;

  int list_7_clouds_all;


  float list_7_wind_speed;
  int list_7_wind_deg;
  float list_7_wind_gust;

  int list_7_visibility;
  float list_7_pop;

  const char* list_7_sys_pod;

  const char* list_7_dt_txt;


  long list_8_dt;


  float list_8_main_temp;
  float list_8_main_feels_like;
  float list_8_main_temp_min;
  float list_8_main_temp_max;
  int list_8_main_pressure;
  int list_8_main_sea_level;
  int list_8_main_grnd_level;
  int list_8_main_humidity;
  int list_8_main_temp_kf;


  int list_8_weather_0_id;
  const char* list_8_weather_0_main;
  const char* list_8_weather_0_description;
  const char* list_8_weather_0_icon;

  int list_8_clouds_all;


  float list_8_wind_speed;
  int list_8_wind_deg;
  float list_8_wind_gust;

  int list_8_visibility;
  int list_8_pop;

  const char* list_8_sys_pod;

  const char* list_8_dt_txt;


  long list_9_dt;


  float list_9_main_temp;
  float list_9_main_feels_like;
  float list_9_main_temp_min;
  float list_9_main_temp_max;
  int list_9_main_pressure;
  int list_9_main_sea_level;
  int list_9_main_grnd_level;
  int list_9_main_humidity;
  int list_9_main_temp_kf;


  int list_9_weather_0_id;
  const char* list_9_weather_0_main;
  const char* list_9_weather_0_description;
  const char* list_9_weather_0_icon;

  int list_9_clouds_all;


  float list_9_wind_speed;
  int list_9_wind_deg;
  float list_9_wind_gust;

  int list_9_visibility;
  int list_9_pop;

  const char* list_9_sys_pod;

  const char* list_9_dt_txt;


  long list_10_dt;


  float list_10_main_temp;
  float list_10_main_feels_like;
  float list_10_main_temp_min;
  float list_10_main_temp_max;
  int list_10_main_pressure;
  int list_10_main_sea_level;
  int list_10_main_grnd_level;
  int list_10_main_humidity;
  int list_10_main_temp_kf;


  int list_10_weather_0_id;
  const char* list_10_weather_0_main;
  const char* list_10_weather_0_description;
  const char* list_10_weather_0_icon;

  int list_10_clouds_all;


  float list_10_wind_speed;
  int list_10_wind_deg;
  float list_10_wind_gust;

  int list_10_visibility;
  int list_10_pop;

  const char* list_10_sys_pod;

  const char* list_10_dt_txt;


  long list_11_dt;


  float list_11_main_temp;
  float list_11_main_feels_like;
  float list_11_main_temp_min;
  float list_11_main_temp_max;
  int list_11_main_pressure;
  int list_11_main_sea_level;
  int list_11_main_grnd_level;
  int list_11_main_humidity;
  int list_11_main_temp_kf;


  int list_11_weather_0_id;
  const char* list_11_weather_0_main;
  const char* list_11_weather_0_description;
  const char* list_11_weather_0_icon;

  int list_11_clouds_all;


  float list_11_wind_speed;
  int list_11_wind_deg;
  float list_11_wind_gust;

  int list_11_visibility;
  int list_11_pop;

  const char* list_11_sys_pod;

  const char* list_11_dt_txt;


  long list_12_dt;


  float list_12_main_temp;
  float list_12_main_feels_like;
  float list_12_main_temp_min;
  float list_12_main_temp_max;
  int list_12_main_pressure;
  int list_12_main_sea_level;
  int list_12_main_grnd_level;
  int list_12_main_humidity;
  int list_12_main_temp_kf;


  int list_12_weather_0_id;
  const char* list_12_weather_0_main;
  const char* list_12_weather_0_description;
  const char* list_12_weather_0_icon;

  int list_12_clouds_all;


  float list_12_wind_speed;
  int list_12_wind_deg;
  float list_12_wind_gust;

  int list_12_visibility;
  int list_12_pop;

  const char* list_12_sys_pod;

  const char* list_12_dt_txt;


  long list_13_dt;


  float list_13_main_temp;
  float list_13_main_feels_like;
  float list_13_main_temp_min;
  float list_13_main_temp_max;
  int list_13_main_pressure;
  int list_13_main_sea_level;
  int list_13_main_grnd_level;
  int list_13_main_humidity;
  int list_13_main_temp_kf;


  int list_13_weather_0_id;
  const char* list_13_weather_0_main;
  const char* list_13_weather_0_description;
  const char* list_13_weather_0_icon;

  int list_13_clouds_all;


  float list_13_wind_speed;
  int list_13_wind_deg;
  float list_13_wind_gust;

  int list_13_visibility;
  int list_13_pop;

  const char* list_13_sys_pod;

  const char* list_13_dt_txt;


  long list_14_dt;


  float list_14_main_temp;
  int list_14_main_feels_like;
  float list_14_main_temp_min;
  float list_14_main_temp_max;
  int list_14_main_pressure;
  int list_14_main_sea_level;
  int list_14_main_grnd_level;
  int list_14_main_humidity;
  int list_14_main_temp_kf;


  int list_14_weather_0_id;
  const char* list_14_weather_0_main;
  const char* list_14_weather_0_description;
  const char* list_14_weather_0_icon;

  int list_14_clouds_all;


  float list_14_wind_speed;
  int list_14_wind_deg;
  float list_14_wind_gust;

  int list_14_visibility;
  int list_14_pop;

  const char* list_14_sys_pod;

  const char* list_14_dt_txt;


  long list_15_dt;


  float list_15_main_temp;
  float list_15_main_feels_like;
  float list_15_main_temp_min;
  float list_15_main_temp_max;
  int list_15_main_pressure;
  int list_15_main_sea_level;
  int list_15_main_grnd_level;
  int list_15_main_humidity;
  int list_15_main_temp_kf;


  int list_15_weather_0_id;
  const char* list_15_weather_0_main;
  const char* list_15_weather_0_description;
  const char* list_15_weather_0_icon;

  int list_15_clouds_all;


  float list_15_wind_speed;
  int list_15_wind_deg;
  float list_15_wind_gust;

  int list_15_visibility;
  int list_15_pop;

  const char* list_15_sys_pod;

  const char* list_15_dt_txt;


  long list_16_dt;


  float list_16_main_temp;
  float list_16_main_feels_like;
  float list_16_main_temp_min;
  float list_16_main_temp_max;
  int list_16_main_pressure;
  int list_16_main_sea_level;
  int list_16_main_grnd_level;
  int list_16_main_humidity;
  int list_16_main_temp_kf;


  int list_16_weather_0_id;
  const char* list_16_weather_0_main;
  const char* list_16_weather_0_description;
  const char* list_16_weather_0_icon;

  int list_16_clouds_all;


  float list_16_wind_speed;
  int list_16_wind_deg;
  float list_16_wind_gust;

  int list_16_visibility;
  int list_16_pop;

  const char* list_16_sys_pod;

  const char* list_16_dt_txt;


  long list_17_dt;


  int list_17_main_temp;
  float list_17_main_feels_like;
  int list_17_main_temp_min;
  int list_17_main_temp_max;
  int list_17_main_pressure;
  int list_17_main_sea_level;
  int list_17_main_grnd_level;
  int list_17_main_humidity;
  int list_17_main_temp_kf;


  int list_17_weather_0_id; // 800
  const char* list_17_weather_0_main; // "Clear"
  const char* list_17_weather_0_description; // "clear sky"
  const char* list_17_weather_0_icon;

  int list_17_clouds_all;


  float list_17_wind_speed;
  int list_17_wind_deg;
  float list_17_wind_gust;

  int list_17_visibility;
  int list_17_pop;

  const char* list_17_sys_pod;

  const char* list_17_dt_txt;


  long list_18_dt;


  float list_18_main_temp;
  float list_18_main_feels_like;
  float list_18_main_temp_min;
  float list_18_main_temp_max;
  int list_18_main_pressure;
  int list_18_main_sea_level;
  int list_18_main_grnd_level;
  int list_18_main_humidity;
  int list_18_main_temp_kf;


  int list_18_weather_0_id;
  const char* list_18_weather_0_main;
  const char* list_18_weather_0_description;
  const char* list_18_weather_0_icon;

  int list_18_clouds_all;


  float list_18_wind_speed;
  int list_18_wind_deg;
  float list_18_wind_gust;

  int list_18_visibility;
  int list_18_pop;

  const char* list_18_sys_pod;

  const char* list_18_dt_txt;


  long list_19_dt;


  float list_19_main_temp; // 4.5
  float list_19_main_feels_like; // 3.42
  float list_19_main_temp_min; // 4.5
  float list_19_main_temp_max; // 4.5
  int list_19_main_pressure; // 1012
  int list_19_main_sea_level; // 1012
  int list_19_main_grnd_level; // 960
  int list_19_main_humidity; // 59
  int list_19_main_temp_kf; // 0


  int list_19_weather_0_id; // 801
  const char* list_19_weather_0_main; // "Clouds"
  const char* list_19_weather_0_description; // "few clouds"
  const char* list_19_weather_0_icon; // "02d"

  int list_19_clouds_all; // 16


  float list_19_wind_speed; // 1.47
  int list_19_wind_deg; // 154
  float list_19_wind_gust; // 2.51

  int list_19_visibility; // 10000
  int list_19_pop; // 0

  const char* list_19_sys_pod; // "d"

  const char* list_19_dt_txt;


  long list_20_dt;


  float list_20_main_temp;
  float list_20_main_feels_like;
  float list_20_main_temp_min;
  float list_20_main_temp_max;
  int list_20_main_pressure;
  int list_20_main_sea_level;
  int list_20_main_grnd_level;
  int list_20_main_humidity;
  int list_20_main_temp_kf;


  int list_20_weather_0_id;
  const char* list_20_weather_0_main;
  const char* list_20_weather_0_description;
  const char* list_20_weather_0_icon;

  int list_20_clouds_all;


  float list_20_wind_speed;
  int list_20_wind_deg;
  float list_20_wind_gust;

  int list_20_visibility;
  int list_20_pop;

  const char* list_20_sys_pod;

  const char* list_20_dt_txt;


  long list_21_dt;


  float list_21_main_temp;
  float list_21_main_feels_like;
  float list_21_main_temp_min;
  float list_21_main_temp_max;
  int list_21_main_pressure;
  int list_21_main_sea_level;
  int list_21_main_grnd_level;
  int list_21_main_humidity;
  int list_21_main_temp_kf;


  int list_21_weather_0_id;
  const char* list_21_weather_0_main;
  const char* list_21_weather_0_description;
  const char* list_21_weather_0_icon;

  int list_21_clouds_all;


  float list_21_wind_speed;
  int list_21_wind_deg;
  float list_21_wind_gust;

  int list_21_visibility;
  int list_21_pop;

  const char* list_21_sys_pod;

  const char* list_21_dt_txt;


  long list_22_dt;


  int list_22_main_temp;
  float list_22_main_feels_like;
  int list_22_main_temp_min;
  int list_22_main_temp_max;
  int list_22_main_pressure;
  int list_22_main_sea_level;
  int list_22_main_grnd_level;
  int list_22_main_humidity;
  int list_22_main_temp_kf;


  int list_22_weather_0_id;
  const char* list_22_weather_0_main;
  const char* list_22_weather_0_description;
  const char* list_22_weather_0_icon;

  int list_22_clouds_all;


  float list_22_wind_speed;
  int list_22_wind_deg;
  float list_22_wind_gust;

  int list_22_visibility;
  int list_22_pop;

  const char* list_22_sys_pod;

  const char* list_22_dt_txt;


  long list_23_dt;


  float list_23_main_temp;
  float list_23_main_feels_like;
  float list_23_main_temp_min;
  float list_23_main_temp_max;
  int list_23_main_pressure;
  int list_23_main_sea_level;
  int list_23_main_grnd_level;
  int list_23_main_humidity;
  int list_23_main_temp_kf;


  int list_23_weather_0_id;
  const char* list_23_weather_0_main;
  const char* list_23_weather_0_description;
  const char* list_23_weather_0_icon;

  int list_23_clouds_all;


  float list_23_wind_speed;
  int list_23_wind_deg;
  float list_23_wind_gust;

  int list_23_visibility;
  int list_23_pop;

  const char* list_23_sys_pod;

  const char* list_23_dt_txt;


  long list_24_dt;


  float list_24_main_temp;
  float list_24_main_feels_like;
  float list_24_main_temp_min;
  float list_24_main_temp_max;
  int list_24_main_pressure;
  int list_24_main_sea_level;
  int list_24_main_grnd_level;
  int list_24_main_humidity;
  int list_24_main_temp_kf;


  int list_24_weather_0_id;
  const char* list_24_weather_0_main;
  const char* list_24_weather_0_description;
  const char* list_24_weather_0_icon;

  int list_24_clouds_all;


  float list_24_wind_speed;
  int list_24_wind_deg;
  float list_24_wind_gust;

  int list_24_visibility;
  int list_24_pop;

  const char* list_24_sys_pod;

  const char* list_24_dt_txt;


  long list_25_dt;


  float list_25_main_temp;
  float list_25_main_feels_like;
  float list_25_main_temp_min;
  float list_25_main_temp_max;
  int list_25_main_pressure;
  int list_25_main_sea_level;
  int list_25_main_grnd_level;
  int list_25_main_humidity;
  int list_25_main_temp_kf;


  int list_25_weather_0_id;
  const char* list_25_weather_0_main;
  const char* list_25_weather_0_description;
  const char* list_25_weather_0_icon;

  int list_25_clouds_all;


  float list_25_wind_speed;
  int list_25_wind_deg;
  float list_25_wind_gust;

  int list_25_visibility;
  float list_25_pop;

  const char* list_25_sys_pod;

  const char* list_25_dt_txt;


  long list_26_dt;


  float list_26_main_temp;
  float list_26_main_feels_like;
  float list_26_main_temp_min;
  float list_26_main_temp_max;
  int list_26_main_pressure;
  int list_26_main_sea_level;
  int list_26_main_grnd_level;
  int list_26_main_humidity;
  int list_26_main_temp_kf;


  int list_26_weather_0_id;
  const char* list_26_weather_0_main;
  const char* list_26_weather_0_description;
  const char* list_26_weather_0_icon;

  int list_26_clouds_all;


  float list_26_wind_speed;
  int list_26_wind_deg;
  float list_26_wind_gust;

  int list_26_visibility;
  float list_26_pop;

  const char* list_26_sys_pod;

  const char* list_26_dt_txt;


  long list_27_dt;


  float list_27_main_temp;
  float list_27_main_feels_like;
  float list_27_main_temp_min;
  float list_27_main_temp_max;
  int list_27_main_pressure;
  int list_27_main_sea_level;
  int list_27_main_grnd_level;
  int list_27_main_humidity;
  int list_27_main_temp_kf;


  int list_27_weather_0_id;
  const char* list_27_weather_0_main;
  const char* list_27_weather_0_description;
  const char* list_27_weather_0_icon;

  int list_27_clouds_all;


  float list_27_wind_speed;
  int list_27_wind_deg;
  float list_27_wind_gust;

  int list_27_visibility;
  int list_27_pop;

  const char* list_27_sys_pod;

  const char* list_27_dt_txt;


  long list_28_dt;


  float list_28_main_temp;
  float list_28_main_feels_like;
  float list_28_main_temp_min;
  float list_28_main_temp_max;
  int list_28_main_pressure;
  int list_28_main_sea_level;
  int list_28_main_grnd_level;
  int list_28_main_humidity;
  int list_28_main_temp_kf;


  int list_28_weather_0_id;
  const char* list_28_weather_0_main;
  const char* list_28_weather_0_description;
  const char* list_28_weather_0_icon;

  int list_28_clouds_all;


  float list_28_wind_speed;
  int list_28_wind_deg;
  float list_28_wind_gust;

  int list_28_visibility;
  int list_28_pop;

  const char* list_28_sys_pod;

  const char* list_28_dt_txt;


  long list_29_dt;


  float list_29_main_temp;
  float list_29_main_feels_like;
  float list_29_main_temp_min;
  float list_29_main_temp_max;
  int list_29_main_pressure;
  int list_29_main_sea_level;
  int list_29_main_grnd_level;
  int list_29_main_humidity;
  int list_29_main_temp_kf;


  int list_29_weather_0_id;
  const char* list_29_weather_0_main;
  const char* list_29_weather_0_description;
  const char* list_29_weather_0_icon;

  int list_29_clouds_all;


  float list_29_wind_speed;
  int list_29_wind_deg;
  float list_29_wind_gust;

  int list_29_visibility;
  int list_29_pop;

  const char* list_29_sys_pod;

  const char* list_29_dt_txt;


  long list_30_dt;


  float list_30_main_temp;
  float list_30_main_feels_like;
  float list_30_main_temp_min;
  float list_30_main_temp_max;
  int list_30_main_pressure;
  int list_30_main_sea_level;
  int list_30_main_grnd_level;
  int list_30_main_humidity;
  int list_30_main_temp_kf;


  int list_30_weather_0_id;
  const char* list_30_weather_0_main;
  const char* list_30_weather_0_description;
  const char* list_30_weather_0_icon;

  int list_30_clouds_all;


  float list_30_wind_speed;
  int list_30_wind_deg;
  float list_30_wind_gust;

  int list_30_visibility;
  int list_30_pop;

  const char* list_30_sys_pod;

  const char* list_30_dt_txt;


  long list_31_dt;


  float list_31_main_temp;
  float list_31_main_feels_like;
  float list_31_main_temp_min;
  float list_31_main_temp_max;
  int list_31_main_pressure;
  int list_31_main_sea_level;
  int list_31_main_grnd_level;
  int list_31_main_humidity;
  int list_31_main_temp_kf;


  int list_31_weather_0_id;
  const char* list_31_weather_0_main;
  const char* list_31_weather_0_description;
  const char* list_31_weather_0_icon;

  int list_31_clouds_all;


  float list_31_wind_speed;
  int list_31_wind_deg;
  float list_31_wind_gust;

  int list_31_visibility;
  int list_31_pop;

  const char* list_31_sys_pod;

  const char* list_31_dt_txt;


  long list_32_dt;


  float list_32_main_temp;
  float list_32_main_feels_like;
  float list_32_main_temp_min;
  float list_32_main_temp_max;
  int list_32_main_pressure;
  int list_32_main_sea_level;
  int list_32_main_grnd_level;
  int list_32_main_humidity;
  int list_32_main_temp_kf;


  int list_32_weather_0_id;
  const char* list_32_weather_0_main;
  const char* list_32_weather_0_description;
  const char* list_32_weather_0_icon;

  int list_32_clouds_all;


  float list_32_wind_speed;
  int list_32_wind_deg;
  float list_32_wind_gust;

  int list_32_visibility;
  int list_32_pop;

  const char* list_32_sys_pod;

  const char* list_32_dt_txt;


  long list_33_dt;


  float list_33_main_temp;
  int list_33_main_feels_like;
  float list_33_main_temp_min;
  float list_33_main_temp_max;
  int list_33_main_pressure;
  int list_33_main_sea_level;
  int list_33_main_grnd_level;
  int list_33_main_humidity;
  int list_33_main_temp_kf;


  int list_33_weather_0_id;
  const char* list_33_weather_0_main;
  const char* list_33_weather_0_description;
  const char* list_33_weather_0_icon;

  int list_33_clouds_all;


  float list_33_wind_speed;
  int list_33_wind_deg;
  float list_33_wind_gust;

  int list_33_visibility;
  int list_33_pop;

  const char* list_33_sys_pod;

  const char* list_33_dt_txt;


  long list_34_dt;


  float list_34_main_temp;
  float list_34_main_feels_like;
  float list_34_main_temp_min;
  float list_34_main_temp_max;
  int list_34_main_pressure;
  int list_34_main_sea_level;
  int list_34_main_grnd_level;
  int list_34_main_humidity;
  int list_34_main_temp_kf;


  int list_34_weather_0_id;
  const char* list_34_weather_0_main;
  const char* list_34_weather_0_description;
  const char* list_34_weather_0_icon;

  int list_34_clouds_all;


  float list_34_wind_speed;
  int list_34_wind_deg;
  float list_34_wind_gust;

  int list_34_visibility;
  int list_34_pop;

  const char* list_34_sys_pod;

  const char* list_34_dt_txt;


  long list_35_dt;


  float list_35_main_temp;
  float list_35_main_feels_like;
  float list_35_main_temp_min;
  float list_35_main_temp_max;
  int list_35_main_pressure;
  int list_35_main_sea_level;
  int list_35_main_grnd_level;
  int list_35_main_humidity;
  int list_35_main_temp_kf;


  int list_35_weather_0_id;
  const char* list_35_weather_0_main;
  const char* list_35_weather_0_description;
  const char* list_35_weather_0_icon;

  int list_35_clouds_all;


  float list_35_wind_speed;
  int list_35_wind_deg;
  float list_35_wind_gust;

  int list_35_visibility;
  float list_35_pop;

  const char* list_35_sys_pod;

  const char* list_35_dt_txt;


  long list_36_dt;


  float list_36_main_temp;
  float list_36_main_feels_like;
  float list_36_main_temp_min;
  float list_36_main_temp_max;
  int list_36_main_pressure;
  int list_36_main_sea_level;
  int list_36_main_grnd_level;
  int list_36_main_humidity;
  int list_36_main_temp_kf;


  int list_36_weather_0_id;
  const char* list_36_weather_0_main;
  const char* list_36_weather_0_description;
  const char* list_36_weather_0_icon;

  int list_36_clouds_all;


  float list_36_wind_speed;
  int list_36_wind_deg;
  float list_36_wind_gust;

  int list_36_visibility;
  float list_36_pop;

  const char* list_36_sys_pod;

  const char* list_36_dt_txt;


  long list_37_dt;


  float list_37_main_temp;
  float list_37_main_feels_like;
  float list_37_main_temp_min;
  float list_37_main_temp_max;
  int list_37_main_pressure;
  int list_37_main_sea_level;
  int list_37_main_grnd_level;
  int list_37_main_humidity;
  int list_37_main_temp_kf;


  int list_37_weather_0_id;
  const char* list_37_weather_0_main;
  const char* list_37_weather_0_description;
  const char* list_37_weather_0_icon;

  int list_37_clouds_all;


  float list_37_wind_speed;
  int list_37_wind_deg;
  float list_37_wind_gust;

  int list_37_visibility;
  int list_37_pop;

  const char* list_37_sys_pod;

  const char* list_37_dt_txt;


  long list_38_dt;


  float list_38_main_temp;
  float list_38_main_feels_like;
  float list_38_main_temp_min;
  float list_38_main_temp_max;
  int list_38_main_pressure;
  int list_38_main_sea_level;
  int list_38_main_grnd_level;
  int list_38_main_humidity;
  int list_38_main_temp_kf;


  int list_38_weather_0_id;
  const char* list_38_weather_0_main;
  const char* list_38_weather_0_description;
  const char* list_38_weather_0_icon;

  int list_38_clouds_all;


  float list_38_wind_speed;
  int list_38_wind_deg;
  float list_38_wind_gust;

  int list_38_visibility;
  int list_38_pop;

  const char* list_38_sys_pod;

  const char* list_38_dt_txt;


  long list_39_dt;


  int list_39_main_temp;
  float list_39_main_feels_like;
  int list_39_main_temp_min;
  int list_39_main_temp_max;
  int list_39_main_pressure;
  int list_39_main_sea_level;
  int list_39_main_grnd_level;
  int list_39_main_humidity;
  int list_39_main_temp_kf;


  int list_39_weather_0_id;
  const char* list_39_weather_0_main;
  const char* list_39_weather_0_description;
  const char* list_39_weather_0_icon;

  int list_39_clouds_all;


  float list_39_wind_speed;
  int list_39_wind_deg;
  float list_39_wind_gust;

  int list_39_visibility;
  int list_39_pop;

  const char* list_39_sys_pod;

  const char* list_39_dt_txt;


  long city_id;
  const char* city_name;

  float city_coord_lat;
  float city_coord_lon;

  const char* city_country;
  long city_population;
  int city_timezone;
  long city_sunrise;
  long city_sunset;
*/
///////A2_Setup///////
void setup() {
  Serial.begin(115200);
  delay(10);



  // в сетапе как обычно подключаемся к сети

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // инициализация Nextion
  //myNextion.init();
  Serial.println("start");

  Wire.begin();
  //vw_set_rx_pin(2); //D2 Вывод приемника VirtualWire
  //vw_setup(1200); // Скорость соединения VirtualWire

  if (!bme.begin(BMP280_ADDRESS - 1)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    delay(2000);
  }

  //vw_set_rx_pin(2);
  //vw_setup(1200);

  //  mq135.heaterPwrHigh();
  Serial.println("Heated sensor");
  //attachInterrupt(3, buttonNex, CHANGE);
  //attachInterrupt(4, GiveOutsideData, CHANGE);
}

///////A3_ParseWeather///////
void loop()  {
  if (millis() - OpenWeatherMap > 900000 || http == true)
  {


    OpenWeatherMap = millis();


    jsonGet();

    StaticJsonDocument<12288> doc;                   /// буфер на 2000 символов
    DeserializationError error = deserializeJson(doc, line);     // скармиваем String
    if (error) {
      Serial.println("deserializeJson() failed with code:");
      Serial.print(error.c_str());// если ошибка, сообщаем об этом
      jsonGet();                                         // пинаем сервер еще раз
      return;                                             // и запускаем заного
    }

    float coord_lon = doc["coord"]["lon"]; // 104.2964
    float coord_lat = doc["coord"]["lat"]; // 52.2978

    JsonObject weather_0 = doc["weather"][0];
    weather_0_id = weather_0["id"]; // 800
    weather_0_main = weather_0["main"]; // "Clear"
    weather_0_description = weather_0["description"]; // "clear sky"
    weather_0_icon = weather_0["icon"]; // "01d"

    base = doc["base"]; // "stations"

    JsonObject main = doc["main"];
    main_temp = main["temp"]; // 8.43
    main_feels_like = main["feels_like"]; // 6.07
    main_temp_min = main["temp_min"]; // 8.43
    main_temp_max = main["temp_max"]; // 8.43
    main_pressure = main["pressure"]; // 1022
    main_humidity = main["humidity"]; // 49

    visibility = doc["visibility"]; // 10000

    wind_speed = doc["wind"]["speed"]; // 4
    wind_deg = doc["wind"]["deg"]; // 310

    clouds_all = doc["clouds"]["all"]; // 0

    dt = doc["dt"]; // 1634971242

    JsonObject sys = doc["sys"];
    sys_type = sys["type"]; // 1
    sys_id = sys["id"]; // 8891
    sys_country = sys["country"]; // "RU"
    sys_sunrise = sys["sunrise"]; // 1634946097
    sys_sunset = sys["sunset"]; // 1634982745

    timezone = doc["timezone"]; // 28800
    id = doc["id"]; // 2023469
    name1 = doc["name"]; // "Irkutsk"
    cod = doc["cod"]; // 200


    /*
        cod = doc["cod"]; // "200"
        message = doc["message"]; // 0
        cnt = doc["cnt"]; // 40

        JsonArray list = doc["list"];

        JsonObject list_0 = list[0];
        list_0_dt = list_0["dt"]; // 1618412400

        JsonObject list_0_main = list_0["main"];
        list_0_main_temp = list_0_main["temp"]; // 0
        list_0_main_feels_like = list_0_main["feels_like"]; // -2.24
        list_0_main_temp_min = list_0_main["temp_min"]; // 0
        list_0_main_temp_max = list_0_main["temp_max"]; // 0.68
        list_0_main_pressure = list_0_main["pressure"]; // 1017
        list_0_main_sea_level = list_0_main["sea_level"]; // 1017
        list_0_main_grnd_level = list_0_main["grnd_level"]; // 967
        list_0_main_humidity = list_0_main["humidity"]; // 69
        list_0_main_temp_kf = list_0_main["temp_kf"]; // -0.68

        JsonObject list_0_weather_0 = list_0["weather"][0];
        list_0_weather_0_id = list_0_weather_0["id"]; // 600
        list_0_weather_0_main = list_0_weather_0["main"]; // "Snow"
        list_0_weather_0_description = list_0_weather_0["description"]; // "light snow"
        list_0_weather_0_icon = list_0_weather_0["icon"]; // "13n"

        list_0_clouds_all = list_0["clouds"]["all"]; // 20

        JsonObject list_0_wind = list_0["wind"];
        list_0_wind_speed = list_0_wind["speed"]; // 1.83
        list_0_wind_deg = list_0_wind["deg"]; // 266
        list_0_wind_gust = list_0_wind["gust"]; // 4.23

        list_0_visibility = list_0["visibility"]; // 10000
        list_0_pop = list_0["pop"]; // 0.24

        list_0_snow_3h = list_0["snow"]["3h"]; // 0.25

        list_0_sys_pod = list_0["sys"]["pod"]; // "n"

        list_0_dt_txt = list_0["dt_txt"]; // "2021-04-14 15:00:00"

        JsonObject list_1 = list[1];
        list_1_dt = list_1["dt"]; // 1618423200

        JsonObject list_1_main = list_1["main"];
        list_1_main_temp = list_1_main["temp"]; // -0.07
        list_1_main_feels_like = list_1_main["feels_like"]; // -2.14
        list_1_main_temp_min = list_1_main["temp_min"]; // -0.21
        list_1_main_temp_max = list_1_main["temp_max"]; // -0.07
        list_1_main_pressure = list_1_main["pressure"]; // 1017
        list_1_main_sea_level = list_1_main["sea_level"]; // 1017
        list_1_main_grnd_level = list_1_main["grnd_level"]; // 964
        list_1_main_humidity = list_1_main["humidity"]; // 71
        list_1_main_temp_kf = list_1_main["temp_kf"]; // 0.14

        JsonObject list_1_weather_0 = list_1["weather"][0];
        list_1_weather_0_id = list_1_weather_0["id"]; // 802
        list_1_weather_0_main = list_1_weather_0["main"]; // "Clouds"
        list_1_weather_0_description = list_1_weather_0["description"]; // "scattered clouds"
        list_1_weather_0_icon = list_1_weather_0["icon"]; // "03n"

        list_1_clouds_all = list_1["clouds"]["all"]; // 46

        JsonObject list_1_wind = list_1["wind"];
        list_1_wind_speed = list_1_wind["speed"]; // 1.7
        list_1_wind_deg = list_1_wind["deg"]; // 219
        list_1_wind_gust = list_1_wind["gust"]; // 3.8

        list_1_visibility = list_1["visibility"]; // 10000
        list_1_pop = list_1["pop"]; // 0

        list_1_sys_pod = list_1["sys"]["pod"]; // "n"

        list_1_dt_txt = list_1["dt_txt"]; // "2021-04-14 18:00:00"

        JsonObject list_2 = list[2];
        list_2_dt = list_2["dt"]; // 1618434000

        JsonObject list_2_main = list_2["main"];
        list_2_main_temp = list_2_main["temp"]; // -0.73
        list_2_main_feels_like = list_2_main["feels_like"]; // -3.07
        list_2_main_temp_min = list_2_main["temp_min"]; // -1.09
        list_2_main_temp_max = list_2_main["temp_max"]; // -0.73
        list_2_main_pressure = list_2_main["pressure"]; // 1015
        list_2_main_sea_level = list_2_main["sea_level"]; // 1015
        list_2_main_grnd_level = list_2_main["grnd_level"]; // 961
        list_2_main_humidity = list_2_main["humidity"]; // 69
        list_2_main_temp_kf = list_2_main["temp_kf"]; // 0.36

        JsonObject list_2_weather_0 = list_2["weather"][0];
        list_2_weather_0_id = list_2_weather_0["id"]; // 803
        list_2_weather_0_main = list_2_weather_0["main"]; // "Clouds"
        list_2_weather_0_description = list_2_weather_0["description"]; // "broken clouds"
        list_2_weather_0_icon = list_2_weather_0["icon"]; // "04n"

        list_2_clouds_all = list_2["clouds"]["all"]; // 69

        JsonObject list_2_wind = list_2["wind"];
        list_2_wind_speed = list_2_wind["speed"]; // 1.82
        list_2_wind_deg = list_2_wind["deg"]; // 161
        list_2_wind_gust = list_2_wind["gust"]; // 2.68

        list_2_visibility = list_2["visibility"]; // 10000
        list_2_pop = list_2["pop"]; // 0

        list_2_sys_pod = list_2["sys"]["pod"]; // "n"

        list_2_dt_txt = list_2["dt_txt"]; // "2021-04-14 21:00:00"

        JsonObject list_3 = list[3];
        list_3_dt = list_3["dt"]; // 1618444800

        JsonObject list_3_main = list_3["main"];
        list_3_main_temp = list_3_main["temp"]; // 1.22
        list_3_main_feels_like = list_3_main["feels_like"]; // -1.63
        list_3_main_temp_min = list_3_main["temp_min"]; // 1.22
        list_3_main_temp_max = list_3_main["temp_max"]; // 1.22
        list_3_main_pressure = list_3_main["pressure"]; // 1013
        list_3_main_sea_level = list_3_main["sea_level"]; // 1013
        list_3_main_grnd_level = list_3_main["grnd_level"]; // 960
        list_3_main_humidity = list_3_main["humidity"]; // 55
        list_3_main_temp_kf = list_3_main["temp_kf"]; // 0

        JsonObject list_3_weather_0 = list_3["weather"][0];
        list_3_weather_0_id = list_3_weather_0["id"]; // 804
        list_3_weather_0_main = list_3_weather_0["main"]; // "Clouds"
        list_3_weather_0_description = list_3_weather_0["description"]; // "overcast clouds"
        list_3_weather_0_icon = list_3_weather_0["icon"]; // "04d"

        list_3_clouds_all = list_3["clouds"]["all"]; // 97

        JsonObject list_3_wind = list_3["wind"];
        list_3_wind_speed = list_3_wind["speed"]; // 2.55
        list_3_wind_deg = list_3_wind["deg"]; // 208
        list_3_wind_gust = list_3_wind["gust"]; // 5.54

        list_3_visibility = list_3["visibility"]; // 10000
        list_3_pop = list_3["pop"]; // 0

        list_3_sys_pod = list_3["sys"]["pod"]; // "d"

        list_3_dt_txt = list_3["dt_txt"]; // "2021-04-15 00:00:00"

        JsonObject list_4 = list[4];
        list_4_dt = list_4["dt"]; // 1618455600

        JsonObject list_4_main = list_4["main"];
        list_4_main_temp = list_4_main["temp"]; // 3.03
        list_4_main_feels_like = list_4_main["feels_like"]; // -1.06
        list_4_main_temp_min = list_4_main["temp_min"]; // 3.03
        list_4_main_temp_max = list_4_main["temp_max"]; // 3.03
        list_4_main_pressure = list_4_main["pressure"]; // 1013
        list_4_main_sea_level = list_4_main["sea_level"]; // 1013
        list_4_main_grnd_level = list_4_main["grnd_level"]; // 961
        list_4_main_humidity = list_4_main["humidity"]; // 61
        list_4_main_temp_kf = list_4_main["temp_kf"]; // 0

        JsonObject list_4_weather_0 = list_4["weather"][0];
        list_4_weather_0_id = list_4_weather_0["id"]; // 600
        list_4_weather_0_main = list_4_weather_0["main"]; // "Snow"
        list_4_weather_0_description = list_4_weather_0["description"]; // "light snow"
        list_4_weather_0_icon = list_4_weather_0["icon"]; // "13d"

        list_4_clouds_all = list_4["clouds"]["all"]; // 100

        JsonObject list_4_wind = list_4["wind"];
        list_4_wind_speed = list_4_wind["speed"]; // 4.88
        list_4_wind_deg = list_4_wind["deg"]; // 284
        list_4_wind_gust = list_4_wind["gust"]; // 8.13

        list_4_visibility = list_4["visibility"]; // 10000
        list_4_pop = list_4["pop"]; // 0.49

        list_4_snow_3h = list_4["snow"]["3h"]; // 0.24

        list_4_sys_pod = list_4["sys"]["pod"]; // "d"

        list_4_dt_txt = list_4["dt_txt"]; // "2021-04-15 03:00:00"

        JsonObject list_5 = list[5];
        list_5_dt = list_5["dt"]; // 1618466400

        JsonObject list_5_main = list_5["main"];
        list_5_main_temp = list_5_main["temp"]; // 5.08
        list_5_main_feels_like = list_5_main["feels_like"]; // 0.4
        list_5_main_temp_min = list_5_main["temp_min"]; // 5.08
        list_5_main_temp_max = list_5_main["temp_max"]; // 5.08
        list_5_main_pressure = list_5_main["pressure"]; // 1016
        list_5_main_sea_level = list_5_main["sea_level"]; // 1016
        list_5_main_grnd_level = list_5_main["grnd_level"]; // 964
        list_5_main_humidity = list_5_main["humidity"]; // 48
        list_5_main_temp_kf = list_5_main["temp_kf"]; // 0

        JsonObject list_5_weather_0 = list_5["weather"][0];
        list_5_weather_0_id = list_5_weather_0["id"]; // 804
        list_5_weather_0_main = list_5_weather_0["main"]; // "Clouds"
        list_5_weather_0_description = list_5_weather_0["description"]; // "overcast clouds"
        list_5_weather_0_icon = list_5_weather_0["icon"]; // "04d"

        list_5_clouds_all = list_5["clouds"]["all"]; // 100

        JsonObject list_5_wind = list_5["wind"];
        list_5_wind_speed = list_5_wind["speed"]; // 7.62
        list_5_wind_deg = list_5_wind["deg"]; // 334
        list_5_wind_gust = list_5_wind["gust"]; // 12.76

        list_5_visibility = list_5["visibility"]; // 10000
        list_5_pop = list_5["pop"]; // 0.8

        list_5_sys_pod = list_5["sys"]["pod"]; // "d"

        list_5_dt_txt = list_5["dt_txt"]; // "2021-04-15 06:00:00"

        JsonObject list_6 = list[6];
        list_6_dt = list_6["dt"]; // 1618477200

        JsonObject list_6_main = list_6["main"];
        list_6_main_temp = list_6_main["temp"]; // 4.89
        list_6_main_feels_like = list_6_main["feels_like"]; // 0.22
        list_6_main_temp_min = list_6_main["temp_min"]; // 4.89
        list_6_main_temp_max = list_6_main["temp_max"]; // 4.89
        list_6_main_pressure = list_6_main["pressure"]; // 1018
        list_6_main_sea_level = list_6_main["sea_level"]; // 1018
        list_6_main_grnd_level = list_6_main["grnd_level"]; // 966
        list_6_main_humidity = list_6_main["humidity"]; // 44
        list_6_main_temp_kf = list_6_main["temp_kf"]; // 0

        JsonObject list_6_weather_0 = list_6["weather"][0];
        list_6_weather_0_id = list_6_weather_0["id"]; // 804
        list_6_weather_0_main = list_6_weather_0["main"]; // "Clouds"
        list_6_weather_0_description = list_6_weather_0["description"]; // "overcast clouds"
        list_6_weather_0_icon = list_6_weather_0["icon"]; // "04d"

        list_6_clouds_all = list_6["clouds"]["all"]; // 86

        JsonObject list_6_wind = list_6["wind"];
        list_6_wind_speed = list_6_wind["speed"]; // 7.44
        list_6_wind_deg = list_6_wind["deg"]; // 332
        list_6_wind_gust = list_6_wind["gust"]; // 14.56

        list_6_visibility = list_6["visibility"]; // 10000
        list_6_pop = list_6["pop"]; // 0.41

        list_6_sys_pod = list_6["sys"]["pod"]; // "d"

        list_6_dt_txt = list_6["dt_txt"]; // "2021-04-15 09:00:00"

        JsonObject list_7 = list[7];
        list_7_dt = list_7["dt"]; // 1618488000

        JsonObject list_7_main = list_7["main"];
        list_7_main_temp = list_7_main["temp"]; // 1.38
        list_7_main_feels_like = list_7_main["feels_like"]; // -3.06
        list_7_main_temp_min = list_7_main["temp_min"]; // 1.38
        list_7_main_temp_max = list_7_main["temp_max"]; // 1.38
        list_7_main_pressure = list_7_main["pressure"]; // 1023
        list_7_main_sea_level = list_7_main["sea_level"]; // 1023
        list_7_main_grnd_level = list_7_main["grnd_level"]; // 970
        list_7_main_humidity = list_7_main["humidity"]; // 57
        list_7_main_temp_kf = list_7_main["temp_kf"]; // 0

        JsonObject list_7_weather_0 = list_7["weather"][0];
        list_7_weather_0_id = list_7_weather_0["id"]; // 803
        list_7_weather_0_main = list_7_weather_0["main"]; // "Clouds"
        list_7_weather_0_description = list_7_weather_0["description"]; // "broken clouds"
        list_7_weather_0_icon = list_7_weather_0["icon"]; // "04n"

        list_7_clouds_all = list_7["clouds"]["all"]; // 54

        JsonObject list_7_wind = list_7["wind"];
        list_7_wind_speed = list_7_wind["speed"]; // 4.76
        list_7_wind_deg = list_7_wind["deg"]; // 326
        list_7_wind_gust = list_7_wind["gust"]; // 10.33

        list_7_visibility = list_7["visibility"]; // 10000
        list_7_pop = list_7["pop"]; // 0.03

        list_7_sys_pod = list_7["sys"]["pod"]; // "n"

        list_7_dt_txt = list_7["dt_txt"]; // "2021-04-15 12:00:00"

        JsonObject list_8 = list[8];
        list_8_dt = list_8["dt"]; // 1618498800

        JsonObject list_8_main = list_8["main"];
        list_8_main_temp = list_8_main["temp"]; // -0.55
        list_8_main_feels_like = list_8_main["feels_like"]; // -3.71
        list_8_main_temp_min = list_8_main["temp_min"]; // -0.55
        list_8_main_temp_max = list_8_main["temp_max"]; // -0.55
        list_8_main_pressure = list_8_main["pressure"]; // 1025
        list_8_main_sea_level = list_8_main["sea_level"]; // 1025
        list_8_main_grnd_level = list_8_main["grnd_level"]; // 972
        list_8_main_humidity = list_8_main["humidity"]; // 69
        list_8_main_temp_kf = list_8_main["temp_kf"]; // 0

        JsonObject list_8_weather_0 = list_8["weather"][0];
        list_8_weather_0_id = list_8_weather_0["id"]; // 804
        list_8_weather_0_main = list_8_weather_0["main"]; // "Clouds"
        list_8_weather_0_description = list_8_weather_0["description"]; // "overcast clouds"
        list_8_weather_0_icon = list_8_weather_0["icon"]; // "04n"

        list_8_clouds_all = list_8["clouds"]["all"]; // 93

        JsonObject list_8_wind = list_8["wind"];
        list_8_wind_speed = list_8_wind["speed"]; // 2.53
        list_8_wind_deg = list_8_wind["deg"]; // 294
        list_8_wind_gust = list_8_wind["gust"]; // 7.07

        list_8_visibility = list_8["visibility"]; // 10000
        list_8_pop = list_8["pop"]; // 0

        list_8_sys_pod = list_8["sys"]["pod"]; // "n"

        list_8_dt_txt = list_8["dt_txt"]; // "2021-04-15 15:00:00"

        JsonObject list_9 = list[9];
        list_9_dt = list_9["dt"]; // 1618509600

        JsonObject list_9_main = list_9["main"];
        list_9_main_temp = list_9_main["temp"]; // -1.65
        list_9_main_feels_like = list_9_main["feels_like"]; // -3.95
        list_9_main_temp_min = list_9_main["temp_min"]; // -1.65
        list_9_main_temp_max = list_9_main["temp_max"]; // -1.65
        list_9_main_pressure = list_9_main["pressure"]; // 1026
        list_9_main_sea_level = list_9_main["sea_level"]; // 1026
        list_9_main_grnd_level = list_9_main["grnd_level"]; // 972
        list_9_main_humidity = list_9_main["humidity"]; // 73
        list_9_main_temp_kf = list_9_main["temp_kf"]; // 0

        JsonObject list_9_weather_0 = list_9["weather"][0];
        list_9_weather_0_id = list_9_weather_0["id"]; // 804
        list_9_weather_0_main = list_9_weather_0["main"]; // "Clouds"
        list_9_weather_0_description = list_9_weather_0["description"]; // "overcast clouds"
        list_9_weather_0_icon = list_9_weather_0["icon"]; // "04n"

        list_9_clouds_all = list_9["clouds"]["all"]; // 88

        JsonObject list_9_wind = list_9["wind"];
        list_9_wind_speed = list_9_wind["speed"]; // 1.7
        list_9_wind_deg = list_9_wind["deg"]; // 256
        list_9_wind_gust = list_9_wind["gust"]; // 3.01

        list_9_visibility = list_9["visibility"]; // 10000
        list_9_pop = list_9["pop"]; // 0

        list_9_sys_pod = list_9["sys"]["pod"]; // "n"

        list_9_dt_txt = list_9["dt_txt"]; // "2021-04-15 18:00:00"

        JsonObject list_10 = list[10];
        list_10_dt = list_10["dt"]; // 1618520400

        JsonObject list_10_main = list_10["main"];
        list_10_main_temp = list_10_main["temp"]; // -2.06
        list_10_main_feels_like = list_10_main["feels_like"]; // -4.44
        list_10_main_temp_min = list_10_main["temp_min"]; // -2.06
        list_10_main_temp_max = list_10_main["temp_max"]; // -2.06
        list_10_main_pressure = list_10_main["pressure"]; // 1025
        list_10_main_sea_level = list_10_main["sea_level"]; // 1025
        list_10_main_grnd_level = list_10_main["grnd_level"]; // 971
        list_10_main_humidity = list_10_main["humidity"]; // 77
        list_10_main_temp_kf = list_10_main["temp_kf"]; // 0

        JsonObject list_10_weather_0 = list_10["weather"][0];
        list_10_weather_0_id = list_10_weather_0["id"]; // 802
        list_10_weather_0_main = list_10_weather_0["main"]; // "Clouds"
        list_10_weather_0_description = list_10_weather_0["description"]; // "scattered clouds"
        list_10_weather_0_icon = list_10_weather_0["icon"]; // "03n"

        list_10_clouds_all = list_10["clouds"]["all"]; // 36

        JsonObject list_10_wind = list_10["wind"];
        list_10_wind_speed = list_10_wind["speed"]; // 1.71
        list_10_wind_deg = list_10_wind["deg"]; // 164
        list_10_wind_gust = list_10_wind["gust"]; // 2.04

        list_10_visibility = list_10["visibility"]; // 10000
        list_10_pop = list_10["pop"]; // 0

        list_10_sys_pod = list_10["sys"]["pod"]; // "n"

        list_10_dt_txt = list_10["dt_txt"]; // "2021-04-15 21:00:00"

        JsonObject list_11 = list[11];
        list_11_dt = list_11["dt"]; // 1618531200

        JsonObject list_11_main = list_11["main"];
        list_11_main_temp = list_11_main["temp"]; // 1.23
        list_11_main_feels_like = list_11_main["feels_like"]; // -1.06
        list_11_main_temp_min = list_11_main["temp_min"]; // 1.23
        list_11_main_temp_max = list_11_main["temp_max"]; // 1.23
        list_11_main_pressure = list_11_main["pressure"]; // 1023
        list_11_main_sea_level = list_11_main["sea_level"]; // 1023
        list_11_main_grnd_level = list_11_main["grnd_level"]; // 971
        list_11_main_humidity = list_11_main["humidity"]; // 57
        list_11_main_temp_kf = list_11_main["temp_kf"]; // 0

        JsonObject list_11_weather_0 = list_11["weather"][0];
        list_11_weather_0_id = list_11_weather_0["id"]; // 803
        list_11_weather_0_main = list_11_weather_0["main"]; // "Clouds"
        list_11_weather_0_description = list_11_weather_0["description"]; // "broken clouds"
        list_11_weather_0_icon = list_11_weather_0["icon"]; // "04d"

        list_11_clouds_all = list_11["clouds"]["all"]; // 57

        JsonObject list_11_wind = list_11["wind"];
        list_11_wind_speed = list_11_wind["speed"]; // 2.03
        list_11_wind_deg = list_11_wind["deg"]; // 168
        list_11_wind_gust = list_11_wind["gust"]; // 3.74

        list_11_visibility = list_11["visibility"]; // 10000
        list_11_pop = list_11["pop"]; // 0

        list_11_sys_pod = list_11["sys"]["pod"]; // "d"

        list_11_dt_txt = list_11["dt_txt"]; // "2021-04-16 00:00:00"

        JsonObject list_12 = list[12];
        list_12_dt = list_12["dt"]; // 1618542000

        JsonObject list_12_main = list_12["main"];
        list_12_main_temp = list_12_main["temp"]; // 7.28
        list_12_main_feels_like = list_12_main["feels_like"]; // 5.05
        list_12_main_temp_min = list_12_main["temp_min"]; // 7.28
        list_12_main_temp_max = list_12_main["temp_max"]; // 7.28
        list_12_main_pressure = list_12_main["pressure"]; // 1020
        list_12_main_sea_level = list_12_main["sea_level"]; // 1020
        list_12_main_grnd_level = list_12_main["grnd_level"]; // 969
        list_12_main_humidity = list_12_main["humidity"]; // 32
        list_12_main_temp_kf = list_12_main["temp_kf"]; // 0

        JsonObject list_12_weather_0 = list_12["weather"][0];
        list_12_weather_0_id = list_12_weather_0["id"]; // 804
        list_12_weather_0_main = list_12_weather_0["main"]; // "Clouds"
        list_12_weather_0_description = list_12_weather_0["description"]; // "overcast clouds"
        list_12_weather_0_icon = list_12_weather_0["icon"]; // "04d"

        list_12_clouds_all = list_12["clouds"]["all"]; // 97

        JsonObject list_12_wind = list_12["wind"];
        list_12_wind_speed = list_12_wind["speed"]; // 3.3
        list_12_wind_deg = list_12_wind["deg"]; // 179
        list_12_wind_gust = list_12_wind["gust"]; // 4.6

        list_12_visibility = list_12["visibility"]; // 10000
        list_12_pop = list_12["pop"]; // 0

        list_12_sys_pod = list_12["sys"]["pod"]; // "d"

        list_12_dt_txt = list_12["dt_txt"]; // "2021-04-16 03:00:00"

        JsonObject list_13 = list[13];
        list_13_dt = list_13["dt"]; // 1618552800

        JsonObject list_13_main = list_13["main"];
        list_13_main_temp = list_13_main["temp"]; // 11.84
        list_13_main_feels_like = list_13_main["feels_like"]; // 9.71
        list_13_main_temp_min = list_13_main["temp_min"]; // 11.84
        list_13_main_temp_max = list_13_main["temp_max"]; // 11.84
        list_13_main_pressure = list_13_main["pressure"]; // 1017
        list_13_main_sea_level = list_13_main["sea_level"]; // 1017
        list_13_main_grnd_level = list_13_main["grnd_level"]; // 966
        list_13_main_humidity = list_13_main["humidity"]; // 24
        list_13_main_temp_kf = list_13_main["temp_kf"]; // 0

        JsonObject list_13_weather_0 = list_13["weather"][0];
        list_13_weather_0_id = list_13_weather_0["id"]; // 803
        list_13_weather_0_main = list_13_weather_0["main"]; // "Clouds"
        list_13_weather_0_description = list_13_weather_0["description"]; // "broken clouds"
        list_13_weather_0_icon = list_13_weather_0["icon"]; // "04d"

        list_13_clouds_all = list_13["clouds"]["all"]; // 68

        JsonObject list_13_wind = list_13["wind"];
        list_13_wind_speed = list_13_wind["speed"]; // 2.49
        list_13_wind_deg = list_13_wind["deg"]; // 194
        list_13_wind_gust = list_13_wind["gust"]; // 3.44

        list_13_visibility = list_13["visibility"]; // 10000
        list_13_pop = list_13["pop"]; // 0

        list_13_sys_pod = list_13["sys"]["pod"]; // "d"

        list_13_dt_txt = list_13["dt_txt"]; // "2021-04-16 06:00:00"

        JsonObject list_14 = list[14];
        list_14_dt = list_14["dt"]; // 1618563600

        JsonObject list_14_main = list_14["main"];
        list_14_main_temp = list_14_main["temp"]; // 12.92
        list_14_main_feels_like = list_14_main["feels_like"]; // 11
        list_14_main_temp_min = list_14_main["temp_min"]; // 12.92
        list_14_main_temp_max = list_14_main["temp_max"]; // 12.92
        list_14_main_pressure = list_14_main["pressure"]; // 1015
        list_14_main_sea_level = list_14_main["sea_level"]; // 1015
        list_14_main_grnd_level = list_14_main["grnd_level"]; // 964
        list_14_main_humidity = list_14_main["humidity"]; // 28
        list_14_main_temp_kf = list_14_main["temp_kf"]; // 0

        JsonObject list_14_weather_0 = list_14["weather"][0];
        list_14_weather_0_id = list_14_weather_0["id"]; // 803
        list_14_weather_0_main = list_14_weather_0["main"]; // "Clouds"
        list_14_weather_0_description = list_14_weather_0["description"]; // "broken clouds"
        list_14_weather_0_icon = list_14_weather_0["icon"]; // "04d"

        list_14_clouds_all = list_14["clouds"]["all"]; // 58

        JsonObject list_14_wind = list_14["wind"];
        list_14_wind_speed = list_14_wind["speed"]; // 3.08
        list_14_wind_deg = list_14_wind["deg"]; // 162
        list_14_wind_gust = list_14_wind["gust"]; // 3.24

        list_14_visibility = list_14["visibility"]; // 10000
        list_14_pop = list_14["pop"]; // 0

        list_14_sys_pod = list_14["sys"]["pod"]; // "d"

        list_14_dt_txt = list_14["dt_txt"]; // "2021-04-16 09:00:00"

        JsonObject list_15 = list[15];
        list_15_dt = list_15["dt"]; // 1618574400

        JsonObject list_15_main = list_15["main"];
        list_15_main_temp = list_15_main["temp"]; // 6.54
        list_15_main_feels_like = list_15_main["feels_like"]; // 4.59
        list_15_main_temp_min = list_15_main["temp_min"]; // 6.54
        list_15_main_temp_max = list_15_main["temp_max"]; // 6.54
        list_15_main_pressure = list_15_main["pressure"]; // 1015
        list_15_main_sea_level = list_15_main["sea_level"]; // 1015
        list_15_main_grnd_level = list_15_main["grnd_level"]; // 964
        list_15_main_humidity = list_15_main["humidity"]; // 53
        list_15_main_temp_kf = list_15_main["temp_kf"]; // 0

        JsonObject list_15_weather_0 = list_15["weather"][0];
        list_15_weather_0_id = list_15_weather_0["id"]; // 802
        list_15_weather_0_main = list_15_weather_0["main"]; // "Clouds"
        list_15_weather_0_description = list_15_weather_0["description"]; // "scattered clouds"
        list_15_weather_0_icon = list_15_weather_0["icon"]; // "03d"

        list_15_clouds_all = list_15["clouds"]["all"]; // 35

        JsonObject list_15_wind = list_15["wind"];
        list_15_wind_speed = list_15_wind["speed"]; // 2.68
        list_15_wind_deg = list_15_wind["deg"]; // 142
        list_15_wind_gust = list_15_wind["gust"]; // 4.91

        list_15_visibility = list_15["visibility"]; // 10000
        list_15_pop = list_15["pop"]; // 0

        list_15_sys_pod = list_15["sys"]["pod"]; // "d"

        list_15_dt_txt = list_15["dt_txt"]; // "2021-04-16 12:00:00"

        JsonObject list_16 = list[16];
        list_16_dt = list_16["dt"]; // 1618585200

        JsonObject list_16_main = list_16["main"];
        list_16_main_temp = list_16_main["temp"]; // 3.45
        list_16_main_feels_like = list_16_main["feels_like"]; // 1.22
        list_16_main_temp_min = list_16_main["temp_min"]; // 3.45
        list_16_main_temp_max = list_16_main["temp_max"]; // 3.45
        list_16_main_pressure = list_16_main["pressure"]; // 1014
        list_16_main_sea_level = list_16_main["sea_level"]; // 1014
        list_16_main_grnd_level = list_16_main["grnd_level"]; // 962
        list_16_main_humidity = list_16_main["humidity"]; // 60
        list_16_main_temp_kf = list_16_main["temp_kf"]; // 0

        JsonObject list_16_weather_0 = list_16["weather"][0];
        list_16_weather_0_id = list_16_weather_0["id"]; // 800
        list_16_weather_0_main = list_16_weather_0["main"]; // "Clear"
        list_16_weather_0_description = list_16_weather_0["description"]; // "clear sky"
        list_16_weather_0_icon = list_16_weather_0["icon"]; // "01n"

        list_16_clouds_all = list_16["clouds"]["all"]; // 6

        JsonObject list_16_wind = list_16["wind"];
        list_16_wind_speed = list_16_wind["speed"]; // 2.33
        list_16_wind_deg = list_16_wind["deg"]; // 160
        list_16_wind_gust = list_16_wind["gust"]; // 4.16

        list_16_visibility = list_16["visibility"]; // 10000
        list_16_pop = list_16["pop"]; // 0

        list_16_sys_pod = list_16["sys"]["pod"]; // "n"

        list_16_dt_txt = list_16["dt_txt"]; // "2021-04-16 15:00:00"

        JsonObject list_17 = list[17];
        list_17_dt = list_17["dt"]; // 1618596000

        JsonObject list_17_main = list_17["main"];
        list_17_main_temp = list_17_main["temp"]; // 2
        list_17_main_feels_like = list_17_main["feels_like"]; // -0.04
        list_17_main_temp_min = list_17_main["temp_min"]; // 2
        list_17_main_temp_max = list_17_main["temp_max"]; // 2
        list_17_main_pressure = list_17_main["pressure"]; // 1013
        list_17_main_sea_level = list_17_main["sea_level"]; // 1013
        list_17_main_grnd_level = list_17_main["grnd_level"]; // 961
        list_17_main_humidity = list_17_main["humidity"]; // 64
        list_17_main_temp_kf = list_17_main["temp_kf"]; // 0

        JsonObject list_17_weather_0 = list_17["weather"][0];
        list_17_weather_0_id = list_17_weather_0["id"]; // 800
        list_17_weather_0_main = list_17_weather_0["main"]; // "Clear"
        list_17_weather_0_description = list_17_weather_0["description"]; // "clear sky"
        list_17_weather_0_icon = list_17_weather_0["icon"]; // "01n"

        list_17_clouds_all = list_17["clouds"]["all"]; // 8

        JsonObject list_17_wind = list_17["wind"];
        list_17_wind_speed = list_17_wind["speed"]; // 1.93
        list_17_wind_deg = list_17_wind["deg"]; // 150
        list_17_wind_gust = list_17_wind["gust"]; // 2.33

        list_17_visibility = list_17["visibility"]; // 10000
        list_17_pop = list_17["pop"]; // 0

        list_17_sys_pod = list_17["sys"]["pod"]; // "n"

        list_17_dt_txt = list_17["dt_txt"]; // "2021-04-16 18:00:00"

        JsonObject list_18 = list[18];
        list_18_dt = list_18["dt"]; // 1618606800

        JsonObject list_18_main = list_18["main"];
        list_18_main_temp = list_18_main["temp"]; // 0.96
        list_18_main_feels_like = list_18_main["feels_like"]; // -1.07
        list_18_main_temp_min = list_18_main["temp_min"]; // 0.96
        list_18_main_temp_max = list_18_main["temp_max"]; // 0.96
        list_18_main_pressure = list_18_main["pressure"]; // 1012
        list_18_main_sea_level = list_18_main["sea_level"]; // 1012
        list_18_main_grnd_level = list_18_main["grnd_level"]; // 960
        list_18_main_humidity = list_18_main["humidity"]; // 72
        list_18_main_temp_kf = list_18_main["temp_kf"]; // 0

        JsonObject list_18_weather_0 = list_18["weather"][0];
        list_18_weather_0_id = list_18_weather_0["id"]; // 801
        list_18_weather_0_main = list_18_weather_0["main"]; // "Clouds"
        list_18_weather_0_description = list_18_weather_0["description"]; // "few clouds"
        list_18_weather_0_icon = list_18_weather_0["icon"]; // "02n"

        list_18_clouds_all = list_18["clouds"]["all"]; // 19

        JsonObject list_18_wind = list_18["wind"];
        list_18_wind_speed = list_18_wind["speed"]; // 1.79
        list_18_wind_deg = list_18_wind["deg"]; // 145
        list_18_wind_gust = list_18_wind["gust"]; // 1.71

        list_18_visibility = list_18["visibility"]; // 10000
        list_18_pop = list_18["pop"]; // 0

        list_18_sys_pod = list_18["sys"]["pod"]; // "n"

        list_18_dt_txt = list_18["dt_txt"]; // "2021-04-16 21:00:00"

        JsonObject list_19 = list[19];
        list_19_dt = list_19["dt"]; // 1618617600

        JsonObject list_19_main = list_19["main"];
        list_19_main_temp = list_19_main["temp"]; // 4.5
        list_19_main_feels_like = list_19_main["feels_like"]; // 3.42
        list_19_main_temp_min = list_19_main["temp_min"]; // 4.5
        list_19_main_temp_max = list_19_main["temp_max"]; // 4.5
        list_19_main_pressure = list_19_main["pressure"]; // 1012
        list_19_main_sea_level = list_19_main["sea_level"]; // 1012
        list_19_main_grnd_level = list_19_main["grnd_level"]; // 960
        list_19_main_humidity = list_19_main["humidity"]; // 59
        list_19_main_temp_kf = list_19_main["temp_kf"]; // 0

        JsonObject list_19_weather_0 = list_19["weather"][0];
        list_19_weather_0_id = list_19_weather_0["id"]; // 801
        list_19_weather_0_main = list_19_weather_0["main"]; // "Clouds"
        list_19_weather_0_description = list_19_weather_0["description"]; // "few clouds"
        list_19_weather_0_icon = list_19_weather_0["icon"]; // "02d"

        list_19_clouds_all = list_19["clouds"]["all"]; // 16

        JsonObject list_19_wind = list_19["wind"];
        list_19_wind_speed = list_19_wind["speed"]; // 1.47
        list_19_wind_deg = list_19_wind["deg"]; // 154
        list_19_wind_gust = list_19_wind["gust"]; // 2.51

        list_19_visibility = list_19["visibility"]; // 10000
        list_19_pop = list_19["pop"]; // 0

        list_19_sys_pod = list_19["sys"]["pod"]; // "d"

        list_19_dt_txt = list_19["dt_txt"]; // "2021-04-17 00:00:00"

        JsonObject list_20 = list[20];
        list_20_dt = list_20["dt"]; // 1618628400

        JsonObject list_20_main = list_20["main"];
        list_20_main_temp = list_20_main["temp"]; // 12.67
        list_20_main_feels_like = list_20_main["feels_like"]; // 10.91
        list_20_main_temp_min = list_20_main["temp_min"]; // 12.67
        list_20_main_temp_max = list_20_main["temp_max"]; // 12.67
        list_20_main_pressure = list_20_main["pressure"]; // 1009
        list_20_main_sea_level = list_20_main["sea_level"]; // 1009
        list_20_main_grnd_level = list_20_main["grnd_level"]; // 959
        list_20_main_humidity = list_20_main["humidity"]; // 35
        list_20_main_temp_kf = list_20_main["temp_kf"]; // 0

        JsonObject list_20_weather_0 = list_20["weather"][0];
        list_20_weather_0_id = list_20_weather_0["id"]; // 800
        list_20_weather_0_main = list_20_weather_0["main"]; // "Clear"
        list_20_weather_0_description = list_20_weather_0["description"]; // "clear sky"
        list_20_weather_0_icon = list_20_weather_0["icon"]; // "01d"

        list_20_clouds_all = list_20["clouds"]["all"]; // 9

        JsonObject list_20_wind = list_20["wind"];
        list_20_wind_speed = list_20_wind["speed"]; // 1.22
        list_20_wind_deg = list_20_wind["deg"]; // 168
        list_20_wind_gust = list_20_wind["gust"]; // 1.88

        list_20_visibility = list_20["visibility"]; // 10000
        list_20_pop = list_20["pop"]; // 0

        list_20_sys_pod = list_20["sys"]["pod"]; // "d"

        list_20_dt_txt = list_20["dt_txt"]; // "2021-04-17 03:00:00"

        JsonObject list_21 = list[21];
        list_21_dt = list_21["dt"]; // 1618639200

        JsonObject list_21_main = list_21["main"];
        list_21_main_temp = list_21_main["temp"]; // 17.5
        list_21_main_feels_like = list_21_main["feels_like"]; // 15.91
        list_21_main_temp_min = list_21_main["temp_min"]; // 17.5
        list_21_main_temp_max = list_21_main["temp_max"]; // 17.5
        list_21_main_pressure = list_21_main["pressure"]; // 1006
        list_21_main_sea_level = list_21_main["sea_level"]; // 1006
        list_21_main_grnd_level = list_21_main["grnd_level"]; // 957
        list_21_main_humidity = list_21_main["humidity"]; // 23
        list_21_main_temp_kf = list_21_main["temp_kf"]; // 0

        JsonObject list_21_weather_0 = list_21["weather"][0];
        list_21_weather_0_id = list_21_weather_0["id"]; // 800
        list_21_weather_0_main = list_21_weather_0["main"]; // "Clear"
        list_21_weather_0_description = list_21_weather_0["description"]; // "clear sky"
        list_21_weather_0_icon = list_21_weather_0["icon"]; // "01d"

        list_21_clouds_all = list_21["clouds"]["all"]; // 6

        JsonObject list_21_wind = list_21["wind"];
        list_21_wind_speed = list_21_wind["speed"]; // 0.73
        list_21_wind_deg = list_21_wind["deg"]; // 168
        list_21_wind_gust = list_21_wind["gust"]; // 2.26

        list_21_visibility = list_21["visibility"]; // 10000
        list_21_pop = list_21["pop"]; // 0

        list_21_sys_pod = list_21["sys"]["pod"]; // "d"

        list_21_dt_txt = list_21["dt_txt"]; // "2021-04-17 06:00:00"

        JsonObject list_22 = list[22];
        list_22_dt = list_22["dt"]; // 1618650000

        JsonObject list_22_main = list_22["main"];
        list_22_main_temp = list_22_main["temp"]; // 18
        list_22_main_feels_like = list_22_main["feels_like"]; // 16.43
        list_22_main_temp_min = list_22_main["temp_min"]; // 18
        list_22_main_temp_max = list_22_main["temp_max"]; // 18
        list_22_main_pressure = list_22_main["pressure"]; // 1004
        list_22_main_sea_level = list_22_main["sea_level"]; // 1004
        list_22_main_grnd_level = list_22_main["grnd_level"]; // 955
        list_22_main_humidity = list_22_main["humidity"]; // 22
        list_22_main_temp_kf = list_22_main["temp_kf"]; // 0

        JsonObject list_22_weather_0 = list_22["weather"][0];
        list_22_weather_0_id = list_22_weather_0["id"]; // 802
        list_22_weather_0_main = list_22_weather_0["main"]; // "Clouds"
        list_22_weather_0_description = list_22_weather_0["description"]; // "scattered clouds"
        list_22_weather_0_icon = list_22_weather_0["icon"]; // "03d"

        list_22_clouds_all = list_22["clouds"]["all"]; // 26

        JsonObject list_22_wind = list_22["wind"];
        list_22_wind_speed = list_22_wind["speed"]; // 2.29
        list_22_wind_deg = list_22_wind["deg"]; // 184
        list_22_wind_gust = list_22_wind["gust"]; // 4.38

        list_22_visibility = list_22["visibility"]; // 10000
        list_22_pop = list_22["pop"]; // 0

        list_22_sys_pod = list_22["sys"]["pod"]; // "d"

        list_22_dt_txt = list_22["dt_txt"]; // "2021-04-17 09:00:00"

        JsonObject list_23 = list[23];
        list_23_dt = list_23["dt"]; // 1618660800

        JsonObject list_23_main = list_23["main"];
        list_23_main_temp = list_23_main["temp"]; // 7.14
        list_23_main_feels_like = list_23_main["feels_like"]; // 2.98
        list_23_main_temp_min = list_23_main["temp_min"]; // 7.14
        list_23_main_temp_max = list_23_main["temp_max"]; // 7.14
        list_23_main_pressure = list_23_main["pressure"]; // 1009
        list_23_main_sea_level = list_23_main["sea_level"]; // 1009
        list_23_main_grnd_level = list_23_main["grnd_level"]; // 958
        list_23_main_humidity = list_23_main["humidity"]; // 71
        list_23_main_temp_kf = list_23_main["temp_kf"]; // 0

        JsonObject list_23_weather_0 = list_23["weather"][0];
        list_23_weather_0_id = list_23_weather_0["id"]; // 802
        list_23_weather_0_main = list_23_weather_0["main"]; // "Clouds"
        list_23_weather_0_description = list_23_weather_0["description"]; // "scattered clouds"
        list_23_weather_0_icon = list_23_weather_0["icon"]; // "03d"

        list_23_clouds_all = list_23["clouds"]["all"]; // 44

        JsonObject list_23_wind = list_23["wind"];
        list_23_wind_speed = list_23_wind["speed"]; // 7.93
        list_23_wind_deg = list_23_wind["deg"]; // 309
        list_23_wind_gust = list_23_wind["gust"]; // 14.44

        list_23_visibility = list_23["visibility"]; // 10000
        list_23_pop = list_23["pop"]; // 0

        list_23_sys_pod = list_23["sys"]["pod"]; // "d"

        list_23_dt_txt = list_23["dt_txt"]; // "2021-04-17 12:00:00"

        JsonObject list_24 = list[24];
        list_24_dt = list_24["dt"]; // 1618671600

        JsonObject list_24_main = list_24["main"];
        list_24_main_temp = list_24_main["temp"]; // 3.95
        list_24_main_feels_like = list_24_main["feels_like"]; // -0.45
        list_24_main_temp_min = list_24_main["temp_min"]; // 3.95
        list_24_main_temp_max = list_24_main["temp_max"]; // 3.95
        list_24_main_pressure = list_24_main["pressure"]; // 1015
        list_24_main_sea_level = list_24_main["sea_level"]; // 1015
        list_24_main_grnd_level = list_24_main["grnd_level"]; // 963
        list_24_main_humidity = list_24_main["humidity"]; // 72
        list_24_main_temp_kf = list_24_main["temp_kf"]; // 0

        JsonObject list_24_weather_0 = list_24["weather"][0];
        list_24_weather_0_id = list_24_weather_0["id"]; // 804
        list_24_weather_0_main = list_24_weather_0["main"]; // "Clouds"
        list_24_weather_0_description = list_24_weather_0["description"]; // "overcast clouds"
        list_24_weather_0_icon = list_24_weather_0["icon"]; // "04n"

        list_24_clouds_all = list_24["clouds"]["all"]; // 95

        JsonObject list_24_wind = list_24["wind"];
        list_24_wind_speed = list_24_wind["speed"]; // 6.02
        list_24_wind_deg = list_24_wind["deg"]; // 329
        list_24_wind_gust = list_24_wind["gust"]; // 10.2

        list_24_visibility = list_24["visibility"]; // 10000
        list_24_pop = list_24["pop"]; // 0

        list_24_sys_pod = list_24["sys"]["pod"]; // "n"

        list_24_dt_txt = list_24["dt_txt"]; // "2021-04-17 15:00:00"

        JsonObject list_25 = list[25];
        list_25_dt = list_25["dt"]; // 1618682400

        JsonObject list_25_main = list_25["main"];
        list_25_main_temp = list_25_main["temp"]; // 2.45
        list_25_main_feels_like = list_25_main["feels_like"]; // -1.36
        list_25_main_temp_min = list_25_main["temp_min"]; // 2.45
        list_25_main_temp_max = list_25_main["temp_max"]; // 2.45
        list_25_main_pressure = list_25_main["pressure"]; // 1017
        list_25_main_sea_level = list_25_main["sea_level"]; // 1017
        list_25_main_grnd_level = list_25_main["grnd_level"]; // 964
        list_25_main_humidity = list_25_main["humidity"]; // 57
        list_25_main_temp_kf = list_25_main["temp_kf"]; // 0

        JsonObject list_25_weather_0 = list_25["weather"][0];
        list_25_weather_0_id = list_25_weather_0["id"]; // 804
        list_25_weather_0_main = list_25_weather_0["main"]; // "Clouds"
        list_25_weather_0_description = list_25_weather_0["description"]; // "overcast clouds"
        list_25_weather_0_icon = list_25_weather_0["icon"]; // "04n"

        list_25_clouds_all = list_25["clouds"]["all"]; // 98

        JsonObject list_25_wind = list_25["wind"];
        list_25_wind_speed = list_25_wind["speed"]; // 4.13
        list_25_wind_deg = list_25_wind["deg"]; // 332
        list_25_wind_gust = list_25_wind["gust"]; // 6.19

        list_25_visibility = list_25["visibility"]; // 10000
        list_25_pop = list_25["pop"]; // 0.01

        list_25_sys_pod = list_25["sys"]["pod"]; // "n"

        list_25_dt_txt = list_25["dt_txt"]; // "2021-04-17 18:00:00"

        JsonObject list_26 = list[26];
        list_26_dt = list_26["dt"]; // 1618693200

        JsonObject list_26_main = list_26["main"];
        list_26_main_temp = list_26_main["temp"]; // 0.73
        list_26_main_feels_like = list_26_main["feels_like"]; // -2.43
        list_26_main_temp_min = list_26_main["temp_min"]; // 0.73
        list_26_main_temp_max = list_26_main["temp_max"]; // 0.73
        list_26_main_pressure = list_26_main["pressure"]; // 1016
        list_26_main_sea_level = list_26_main["sea_level"]; // 1016
        list_26_main_grnd_level = list_26_main["grnd_level"]; // 964
        list_26_main_humidity = list_26_main["humidity"]; // 66
        list_26_main_temp_kf = list_26_main["temp_kf"]; // 0

        JsonObject list_26_weather_0 = list_26["weather"][0];
        list_26_weather_0_id = list_26_weather_0["id"]; // 804
        list_26_weather_0_main = list_26_weather_0["main"]; // "Clouds"
        list_26_weather_0_description = list_26_weather_0["description"]; // "overcast clouds"
        list_26_weather_0_icon = list_26_weather_0["icon"]; // "04n"

        list_26_clouds_all = list_26["clouds"]["all"]; // 100

        JsonObject list_26_wind = list_26["wind"];
        list_26_wind_speed = list_26_wind["speed"]; // 2.78
        list_26_wind_deg = list_26_wind["deg"]; // 339
        list_26_wind_gust = list_26_wind["gust"]; // 3.98

        list_26_visibility = list_26["visibility"]; // 10000
        list_26_pop = list_26["pop"]; // 0.03

        list_26_sys_pod = list_26["sys"]["pod"]; // "n"

        list_26_dt_txt = list_26["dt_txt"]; // "2021-04-17 21:00:00"

        JsonObject list_27 = list[27];
        list_27_dt = list_27["dt"]; // 1618704000

        JsonObject list_27_main = list_27["main"];
        list_27_main_temp = list_27_main["temp"]; // 1.21
        list_27_main_feels_like = list_27_main["feels_like"]; // -0.69
        list_27_main_temp_min = list_27_main["temp_min"]; // 1.21
        list_27_main_temp_max = list_27_main["temp_max"]; // 1.21
        list_27_main_pressure = list_27_main["pressure"]; // 1016
        list_27_main_sea_level = list_27_main["sea_level"]; // 1016
        list_27_main_grnd_level = list_27_main["grnd_level"]; // 964
        list_27_main_humidity = list_27_main["humidity"]; // 68
        list_27_main_temp_kf = list_27_main["temp_kf"]; // 0

        JsonObject list_27_weather_0 = list_27["weather"][0];
        list_27_weather_0_id = list_27_weather_0["id"]; // 804
        list_27_weather_0_main = list_27_weather_0["main"]; // "Clouds"
        list_27_weather_0_description = list_27_weather_0["description"]; // "overcast clouds"
        list_27_weather_0_icon = list_27_weather_0["icon"]; // "04d"

        list_27_clouds_all = list_27["clouds"]["all"]; // 86

        JsonObject list_27_wind = list_27["wind"];
        list_27_wind_speed = list_27_wind["speed"]; // 1.72
        list_27_wind_deg = list_27_wind["deg"]; // 359
        list_27_wind_gust = list_27_wind["gust"]; // 2.14

        list_27_visibility = list_27["visibility"]; // 10000
        list_27_pop = list_27["pop"]; // 0

        list_27_sys_pod = list_27["sys"]["pod"]; // "d"

        list_27_dt_txt = list_27["dt_txt"]; // "2021-04-18 00:00:00"

        JsonObject list_28 = list[28];
        list_28_dt = list_28["dt"]; // 1618714800

        JsonObject list_28_main = list_28["main"];
        list_28_main_temp = list_28_main["temp"]; // 5.2
        list_28_main_feels_like = list_28_main["feels_like"]; // 5.2
        list_28_main_temp_min = list_28_main["temp_min"]; // 5.2
        list_28_main_temp_max = list_28_main["temp_max"]; // 5.2
        list_28_main_pressure = list_28_main["pressure"]; // 1014
        list_28_main_sea_level = list_28_main["sea_level"]; // 1014
        list_28_main_grnd_level = list_28_main["grnd_level"]; // 962
        list_28_main_humidity = list_28_main["humidity"]; // 52
        list_28_main_temp_kf = list_28_main["temp_kf"]; // 0

        JsonObject list_28_weather_0 = list_28["weather"][0];
        list_28_weather_0_id = list_28_weather_0["id"]; // 804
        list_28_weather_0_main = list_28_weather_0["main"]; // "Clouds"
        list_28_weather_0_description = list_28_weather_0["description"]; // "overcast clouds"
        list_28_weather_0_icon = list_28_weather_0["icon"]; // "04d"

        list_28_clouds_all = list_28["clouds"]["all"]; // 94

        JsonObject list_28_wind = list_28["wind"];
        list_28_wind_speed = list_28_wind["speed"]; // 1.09
        list_28_wind_deg = list_28_wind["deg"]; // 89
        list_28_wind_gust = list_28_wind["gust"]; // 1.45

        list_28_visibility = list_28["visibility"]; // 10000
        list_28_pop = list_28["pop"]; // 0

        list_28_sys_pod = list_28["sys"]["pod"]; // "d"

        list_28_dt_txt = list_28["dt_txt"]; // "2021-04-18 03:00:00"

        JsonObject list_29 = list[29];
        list_29_dt = list_29["dt"]; // 1618725600

        JsonObject list_29_main = list_29["main"];
        list_29_main_temp = list_29_main["temp"]; // 9.29
        list_29_main_feels_like = list_29_main["feels_like"]; // 8.88
        list_29_main_temp_min = list_29_main["temp_min"]; // 9.29
        list_29_main_temp_max = list_29_main["temp_max"]; // 9.29
        list_29_main_pressure = list_29_main["pressure"]; // 1011
        list_29_main_sea_level = list_29_main["sea_level"]; // 1011
        list_29_main_grnd_level = list_29_main["grnd_level"]; // 960
        list_29_main_humidity = list_29_main["humidity"]; // 41
        list_29_main_temp_kf = list_29_main["temp_kf"]; // 0

        JsonObject list_29_weather_0 = list_29["weather"][0];
        list_29_weather_0_id = list_29_weather_0["id"]; // 804
        list_29_weather_0_main = list_29_weather_0["main"]; // "Clouds"
        list_29_weather_0_description = list_29_weather_0["description"]; // "overcast clouds"
        list_29_weather_0_icon = list_29_weather_0["icon"]; // "04d"

        list_29_clouds_all = list_29["clouds"]["all"]; // 88

        JsonObject list_29_wind = list_29["wind"];
        list_29_wind_speed = list_29_wind["speed"]; // 1.46
        list_29_wind_deg = list_29_wind["deg"]; // 155
        list_29_wind_gust = list_29_wind["gust"]; // 2.15

        list_29_visibility = list_29["visibility"]; // 10000
        list_29_pop = list_29["pop"]; // 0

        list_29_sys_pod = list_29["sys"]["pod"]; // "d"

        list_29_dt_txt = list_29["dt_txt"]; // "2021-04-18 06:00:00"

        JsonObject list_30 = list[30];
        list_30_dt = list_30["dt"]; // 1618736400

        JsonObject list_30_main = list_30["main"];
        list_30_main_temp = list_30_main["temp"]; // 10.51
        list_30_main_feels_like = list_30_main["feels_like"]; // 8.66
        list_30_main_temp_min = list_30_main["temp_min"]; // 10.51
        list_30_main_temp_max = list_30_main["temp_max"]; // 10.51
        list_30_main_pressure = list_30_main["pressure"]; // 1009
        list_30_main_sea_level = list_30_main["sea_level"]; // 1009
        list_30_main_grnd_level = list_30_main["grnd_level"]; // 959
        list_30_main_humidity = list_30_main["humidity"]; // 40
        list_30_main_temp_kf = list_30_main["temp_kf"]; // 0

        JsonObject list_30_weather_0 = list_30["weather"][0];
        list_30_weather_0_id = list_30_weather_0["id"]; // 802
        list_30_weather_0_main = list_30_weather_0["main"]; // "Clouds"
        list_30_weather_0_description = list_30_weather_0["description"]; // "scattered clouds"
        list_30_weather_0_icon = list_30_weather_0["icon"]; // "03d"

        list_30_clouds_all = list_30["clouds"]["all"]; // 44

        JsonObject list_30_wind = list_30["wind"];
        list_30_wind_speed = list_30_wind["speed"]; // 2.45
        list_30_wind_deg = list_30_wind["deg"]; // 162
        list_30_wind_gust = list_30_wind["gust"]; // 2.04

        list_30_visibility = list_30["visibility"]; // 10000
        list_30_pop = list_30["pop"]; // 0

        list_30_sys_pod = list_30["sys"]["pod"]; // "d"

        list_30_dt_txt = list_30["dt_txt"]; // "2021-04-18 09:00:00"

        JsonObject list_31 = list[31];
        list_31_dt = list_31["dt"]; // 1618747200

        JsonObject list_31_main = list_31["main"];
        list_31_main_temp = list_31_main["temp"]; // 4.66
        list_31_main_feels_like = list_31_main["feels_like"]; // 0.99
        list_31_main_temp_min = list_31_main["temp_min"]; // 4.66
        list_31_main_temp_max = list_31_main["temp_max"]; // 4.66
        list_31_main_pressure = list_31_main["pressure"]; // 1011
        list_31_main_sea_level = list_31_main["sea_level"]; // 1011
        list_31_main_grnd_level = list_31_main["grnd_level"]; // 959
        list_31_main_humidity = list_31_main["humidity"]; // 58
        list_31_main_temp_kf = list_31_main["temp_kf"]; // 0

        JsonObject list_31_weather_0 = list_31["weather"][0];
        list_31_weather_0_id = list_31_weather_0["id"]; // 802
        list_31_weather_0_main = list_31_weather_0["main"]; // "Clouds"
        list_31_weather_0_description = list_31_weather_0["description"]; // "scattered clouds"
        list_31_weather_0_icon = list_31_weather_0["icon"]; // "03d"

        list_31_clouds_all = list_31["clouds"]["all"]; // 42

        JsonObject list_31_wind = list_31["wind"];
        list_31_wind_speed = list_31_wind["speed"]; // 4.84
        list_31_wind_deg = list_31_wind["deg"]; // 168
        list_31_wind_gust = list_31_wind["gust"]; // 9.93

        list_31_visibility = list_31["visibility"]; // 10000
        list_31_pop = list_31["pop"]; // 0

        list_31_sys_pod = list_31["sys"]["pod"]; // "d"

        list_31_dt_txt = list_31["dt_txt"]; // "2021-04-18 12:00:00"

        JsonObject list_32 = list[32];
        list_32_dt = list_32["dt"]; // 1618758000

        JsonObject list_32_main = list_32["main"];
        list_32_main_temp = list_32_main["temp"]; // 1.82
        list_32_main_feels_like = list_32_main["feels_like"]; // -0.84
        list_32_main_temp_min = list_32_main["temp_min"]; // 1.82
        list_32_main_temp_max = list_32_main["temp_max"]; // 1.82
        list_32_main_pressure = list_32_main["pressure"]; // 1013
        list_32_main_sea_level = list_32_main["sea_level"]; // 1013
        list_32_main_grnd_level = list_32_main["grnd_level"]; // 961
        list_32_main_humidity = list_32_main["humidity"]; // 75
        list_32_main_temp_kf = list_32_main["temp_kf"]; // 0

        JsonObject list_32_weather_0 = list_32["weather"][0];
        list_32_weather_0_id = list_32_weather_0["id"]; // 802
        list_32_weather_0_main = list_32_weather_0["main"]; // "Clouds"
        list_32_weather_0_description = list_32_weather_0["description"]; // "scattered clouds"
        list_32_weather_0_icon = list_32_weather_0["icon"]; // "03n"

        list_32_clouds_all = list_32["clouds"]["all"]; // 28

        JsonObject list_32_wind = list_32["wind"];
        list_32_wind_speed = list_32_wind["speed"]; // 2.47
        list_32_wind_deg = list_32_wind["deg"]; // 172
        list_32_wind_gust = list_32_wind["gust"]; // 5.93

        list_32_visibility = list_32["visibility"]; // 10000
        list_32_pop = list_32["pop"]; // 0

        list_32_sys_pod = list_32["sys"]["pod"]; // "n"

        list_32_dt_txt = list_32["dt_txt"]; // "2021-04-18 15:00:00"

        JsonObject list_33 = list[33];
        list_33_dt = list_33["dt"]; // 1618768800

        JsonObject list_33_main = list_33["main"];
        list_33_main_temp = list_33_main["temp"]; // 0.81
        list_33_main_feels_like = list_33_main["feels_like"]; // -2
        list_33_main_temp_min = list_33_main["temp_min"]; // 0.81
        list_33_main_temp_max = list_33_main["temp_max"]; // 0.81
        list_33_main_pressure = list_33_main["pressure"]; // 1013
        list_33_main_sea_level = list_33_main["sea_level"]; // 1013
        list_33_main_grnd_level = list_33_main["grnd_level"]; // 961
        list_33_main_humidity = list_33_main["humidity"]; // 80
        list_33_main_temp_kf = list_33_main["temp_kf"]; // 0

        JsonObject list_33_weather_0 = list_33["weather"][0];
        list_33_weather_0_id = list_33_weather_0["id"]; // 802
        list_33_weather_0_main = list_33_weather_0["main"]; // "Clouds"
        list_33_weather_0_description = list_33_weather_0["description"]; // "scattered clouds"
        list_33_weather_0_icon = list_33_weather_0["icon"]; // "03n"

        list_33_clouds_all = list_33["clouds"]["all"]; // 48

        JsonObject list_33_wind = list_33["wind"];
        list_33_wind_speed = list_33_wind["speed"]; // 2.44
        list_33_wind_deg = list_33_wind["deg"]; // 150
        list_33_wind_gust = list_33_wind["gust"]; // 5.68

        list_33_visibility = list_33["visibility"]; // 10000
        list_33_pop = list_33["pop"]; // 0

        list_33_sys_pod = list_33["sys"]["pod"]; // "n"

        list_33_dt_txt = list_33["dt_txt"]; // "2021-04-18 18:00:00"

        JsonObject list_34 = list[34];
        list_34_dt = list_34["dt"]; // 1618779600

        JsonObject list_34_main = list_34["main"];
        list_34_main_temp = list_34_main["temp"]; // -0.4
        list_34_main_feels_like = list_34_main["feels_like"]; // -1.98
        list_34_main_temp_min = list_34_main["temp_min"]; // -0.4
        list_34_main_temp_max = list_34_main["temp_max"]; // -0.4
        list_34_main_pressure = list_34_main["pressure"]; // 1015
        list_34_main_sea_level = list_34_main["sea_level"]; // 1015
        list_34_main_grnd_level = list_34_main["grnd_level"]; // 962
        list_34_main_humidity = list_34_main["humidity"]; // 79
        list_34_main_temp_kf = list_34_main["temp_kf"]; // 0

        JsonObject list_34_weather_0 = list_34["weather"][0];
        list_34_weather_0_id = list_34_weather_0["id"]; // 802
        list_34_weather_0_main = list_34_weather_0["main"]; // "Clouds"
        list_34_weather_0_description = list_34_weather_0["description"]; // "scattered clouds"
        list_34_weather_0_icon = list_34_weather_0["icon"]; // "03n"

        list_34_clouds_all = list_34["clouds"]["all"]; // 25

        JsonObject list_34_wind = list_34["wind"];
        list_34_wind_speed = list_34_wind["speed"]; // 1.36
        list_34_wind_deg = list_34_wind["deg"]; // 188
        list_34_wind_gust = list_34_wind["gust"]; // 1.73

        list_34_visibility = list_34["visibility"]; // 10000
        list_34_pop = list_34["pop"]; // 0

        list_34_sys_pod = list_34["sys"]["pod"]; // "n"

        list_34_dt_txt = list_34["dt_txt"]; // "2021-04-18 21:00:00"

        JsonObject list_35 = list[35];
        list_35_dt = list_35["dt"]; // 1618790400

        JsonObject list_35_main = list_35["main"];
        list_35_main_temp = list_35_main["temp"]; // 2.24
        list_35_main_feels_like = list_35_main["feels_like"]; // -0.72
        list_35_main_temp_min = list_35_main["temp_min"]; // 2.24
        list_35_main_temp_max = list_35_main["temp_max"]; // 2.24
        list_35_main_pressure = list_35_main["pressure"]; // 1016
        list_35_main_sea_level = list_35_main["sea_level"]; // 1016
        list_35_main_grnd_level = list_35_main["grnd_level"]; // 964
        list_35_main_humidity = list_35_main["humidity"]; // 76
        list_35_main_temp_kf = list_35_main["temp_kf"]; // 0

        JsonObject list_35_weather_0 = list_35["weather"][0];
        list_35_weather_0_id = list_35_weather_0["id"]; // 803
        list_35_weather_0_main = list_35_weather_0["main"]; // "Clouds"
        list_35_weather_0_description = list_35_weather_0["description"]; // "broken clouds"
        list_35_weather_0_icon = list_35_weather_0["icon"]; // "04d"

        list_35_clouds_all = list_35["clouds"]["all"]; // 54

        JsonObject list_35_wind = list_35["wind"];
        list_35_wind_speed = list_35_wind["speed"]; // 2.89
        list_35_wind_deg = list_35_wind["deg"]; // 309
        list_35_wind_gust = list_35_wind["gust"]; // 5.53

        list_35_visibility = list_35["visibility"]; // 10000
        list_35_pop = list_35["pop"]; // 0.01

        list_35_sys_pod = list_35["sys"]["pod"]; // "d"

        list_35_dt_txt = list_35["dt_txt"]; // "2021-04-19 00:00:00"

        JsonObject list_36 = list[36];
        list_36_dt = list_36["dt"]; // 1618801200

        JsonObject list_36_main = list_36["main"];
        list_36_main_temp = list_36_main["temp"]; // 3.25
        list_36_main_feels_like = list_36_main["feels_like"]; // 1.68
        list_36_main_temp_min = list_36_main["temp_min"]; // 3.25
        list_36_main_temp_max = list_36_main["temp_max"]; // 3.25
        list_36_main_pressure = list_36_main["pressure"]; // 1016
        list_36_main_sea_level = list_36_main["sea_level"]; // 1016
        list_36_main_grnd_level = list_36_main["grnd_level"]; // 964
        list_36_main_humidity = list_36_main["humidity"]; // 88
        list_36_main_temp_kf = list_36_main["temp_kf"]; // 0

        JsonObject list_36_weather_0 = list_36["weather"][0];
        list_36_weather_0_id = list_36_weather_0["id"]; // 804
        list_36_weather_0_main = list_36_weather_0["main"]; // "Clouds"
        list_36_weather_0_description = list_36_weather_0["description"]; // "overcast clouds"
        list_36_weather_0_icon = list_36_weather_0["icon"]; // "04d"

        list_36_clouds_all = list_36["clouds"]["all"]; // 100

        JsonObject list_36_wind = list_36["wind"];
        list_36_wind_speed = list_36_wind["speed"]; // 1.7
        list_36_wind_deg = list_36_wind["deg"]; // 291
        list_36_wind_gust = list_36_wind["gust"]; // 2.55

        list_36_visibility = list_36["visibility"]; // 4768
        list_36_pop = list_36["pop"]; // 0.02

        list_36_sys_pod = list_36["sys"]["pod"]; // "d"

        list_36_dt_txt = list_36["dt_txt"]; // "2021-04-19 03:00:00"

        JsonObject list_37 = list[37];
        list_37_dt = list_37["dt"]; // 1618812000

        JsonObject list_37_main = list_37["main"];
        list_37_main_temp = list_37_main["temp"]; // 7.46
        list_37_main_feels_like = list_37_main["feels_like"]; // 7.46
        list_37_main_temp_min = list_37_main["temp_min"]; // 7.46
        list_37_main_temp_max = list_37_main["temp_max"]; // 7.46
        list_37_main_pressure = list_37_main["pressure"]; // 1013
        list_37_main_sea_level = list_37_main["sea_level"]; // 1013
        list_37_main_grnd_level = list_37_main["grnd_level"]; // 962
        list_37_main_humidity = list_37_main["humidity"]; // 59
        list_37_main_temp_kf = list_37_main["temp_kf"]; // 0

        JsonObject list_37_weather_0 = list_37["weather"][0];
        list_37_weather_0_id = list_37_weather_0["id"]; // 804
        list_37_weather_0_main = list_37_weather_0["main"]; // "Clouds"
        list_37_weather_0_description = list_37_weather_0["description"]; // "overcast clouds"
        list_37_weather_0_icon = list_37_weather_0["icon"]; // "04d"

        list_37_clouds_all = list_37["clouds"]["all"]; // 99

        JsonObject list_37_wind = list_37["wind"];
        list_37_wind_speed = list_37_wind["speed"]; // 1.12
        list_37_wind_deg = list_37_wind["deg"]; // 164
        list_37_wind_gust = list_37_wind["gust"]; // 1.59

        list_37_visibility = list_37["visibility"]; // 10000
        list_37_pop = list_37["pop"]; // 0

        list_37_sys_pod = list_37["sys"]["pod"]; // "d"

        list_37_dt_txt = list_37["dt_txt"]; // "2021-04-19 06:00:00"

        JsonObject list_38 = list[38];
        list_38_dt = list_38["dt"]; // 1618822800

        JsonObject list_38_main = list_38["main"];
        list_38_main_temp = list_38_main["temp"]; // 11.13
        list_38_main_feels_like = list_38_main["feels_like"]; // 9.5
        list_38_main_temp_min = list_38_main["temp_min"]; // 11.13
        list_38_main_temp_max = list_38_main["temp_max"]; // 11.13
        list_38_main_pressure = list_38_main["pressure"]; // 1008
        list_38_main_sea_level = list_38_main["sea_level"]; // 1008
        list_38_main_grnd_level = list_38_main["grnd_level"]; // 958
        list_38_main_humidity = list_38_main["humidity"]; // 46
        list_38_main_temp_kf = list_38_main["temp_kf"]; // 0

        JsonObject list_38_weather_0 = list_38["weather"][0];
        list_38_weather_0_id = list_38_weather_0["id"]; // 803
        list_38_weather_0_main = list_38_weather_0["main"]; // "Clouds"
        list_38_weather_0_description = list_38_weather_0["description"]; // "broken clouds"
        list_38_weather_0_icon = list_38_weather_0["icon"]; // "04d"

        list_38_clouds_all = list_38["clouds"]["all"]; // 81

        JsonObject list_38_wind = list_38["wind"];
        list_38_wind_speed = list_38_wind["speed"]; // 1.42
        list_38_wind_deg = list_38_wind["deg"]; // 127
        list_38_wind_gust = list_38_wind["gust"]; // 3.21

        list_38_visibility = list_38["visibility"]; // 10000
        list_38_pop = list_38["pop"]; // 0

        list_38_sys_pod = list_38["sys"]["pod"]; // "d"

        list_38_dt_txt = list_38["dt_txt"]; // "2021-04-19 09:00:00"

        JsonObject list_39 = list[39];
        list_39_dt = list_39["dt"]; // 1618833600

        JsonObject list_39_main = list_39["main"];
        list_39_main_temp = list_39_main["temp"]; // 7
        list_39_main_feels_like = list_39_main["feels_like"]; // 5.29
        list_39_main_temp_min = list_39_main["temp_min"]; // 7
        list_39_main_temp_max = list_39_main["temp_max"]; // 7
        list_39_main_pressure = list_39_main["pressure"]; // 1008
        list_39_main_sea_level = list_39_main["sea_level"]; // 1008
        list_39_main_grnd_level = list_39_main["grnd_level"]; // 957
        list_39_main_humidity = list_39_main["humidity"]; // 61
        list_39_main_temp_kf = list_39_main["temp_kf"]; // 0

        JsonObject list_39_weather_0 = list_39["weather"][0];
        list_39_weather_0_id = list_39_weather_0["id"]; // 804
        list_39_weather_0_main = list_39_weather_0["main"]; // "Clouds"
        list_39_weather_0_description = list_39_weather_0["description"]; // "overcast clouds"
        list_39_weather_0_icon = list_39_weather_0["icon"]; // "04d"

        list_39_clouds_all = list_39["clouds"]["all"]; // 90

        JsonObject list_39_wind = list_39["wind"];
        list_39_wind_speed = list_39_wind["speed"]; // 2.47
        list_39_wind_deg = list_39_wind["deg"]; // 176
        list_39_wind_gust = list_39_wind["gust"]; // 5.26

        list_39_visibility = list_39["visibility"]; // 10000
        list_39_pop = list_39["pop"]; // 0

        list_39_sys_pod = list_39["sys"]["pod"]; // "d"

        list_39_dt_txt = list_39["dt_txt"]; // "2021-04-19 12:00:00"

        JsonObject city = doc["city"];
        city_id = city["id"]; // 2023469
        city_name = city["name"]; // "Irkutsk"

        city_coord_lat = city["coord"]["lat"]; // 52.2978
        city_coord_lon = city["coord"]["lon"]; // 104.2964

        city_country = city["country"]; // "RU"
        city_population = city["population"]; // 586695
        city_timezone = city["timezone"]; // 28800
        city_sunrise = city["sunrise"]; // 1618351675
        city_sunset = city["sunset"]; // 1618401475
    */

    Serial.println();
    Serial.println();

  }


  ///////A4_ParseNews///////
  if (millis() - NewsAPI > 1200000) {
    Serial.println("tisha");

    NewsAPI = millis();


    NewsGet();

    StaticJsonDocument<24576> doc;                   /// буфер на 2000 символов
    DeserializationError error = deserializeJson(doc, Newsline);     // скармиваем String
    if (error) {
      Serial.println("deserializeJson() failed with code:");
      Serial.print(error.c_str());// если ошибка, сообщаем об этом
      NewsGet();                                         // пинаем сервер еще раз
      return;                                             // и запускаем заного
    }

    const char* status = doc["status"]; // "ok"
    int totalResults = doc["totalResults"]; // 33

    JsonArray articles = doc["articles"];

    JsonObject articles_0 = articles[0];

    JsonObject articles_0_title = articles_0["title"];
  }


  ///////A5_ParseCoins///////
  if (millis() - CoinAPI > 1200000) {
    CoinsGet();

    StaticJsonDocument<3072> doc;                   /// буфер на 2000 символов
    DeserializationError error = deserializeJson(doc, Coinsline);     // скармиваем String
    if (error) {
      Serial.println("deserializeJson() failed with code:");
      Serial.print(error.c_str());// если ошибка, сообщаем об этом
      CoinsGet();                                         // пинаем сервер еще раз
      return;                                             // и запускаем заного
    }

    bool success = doc["success"]; // true
    const char* terms = doc["terms"]; // "https://currencylayer.com/terms"
    const char* privacy = doc["privacy"]; // "https://currencylayer.com/privacy"
    long timestamp = doc["timestamp"]; // 1618366397
    const char* source = doc["source"]; // "USD"

    JsonObject quotes = doc["quotes"];
    float quotes_USDAED = quotes["USDAED"]; // 3.673203
    double quotes_USDAFN = quotes["USDAFN"]; // 77.597632
    double quotes_USDALL = quotes["USDALL"]; // 103.14994
    double quotes_USDAMD = quotes["USDAMD"]; // 519.430131
    float quotes_USDANG = quotes["USDANG"]; // 1.794987
    float quotes_USDAOA = quotes["USDAOA"]; // 634.4402
    double quotes_USDARS = quotes["USDARS"]; // 92.613497
    float quotes_USDAUD = quotes["USDAUD"]; // 1.308584
    float quotes_USDAWG = quotes["USDAWG"]; // 1.8
    float quotes_USDAZN = quotes["USDAZN"]; // 1.702782
    float quotes_USDBAM = quotes["USDBAM"]; // 1.644716
    float quotes_USDBBD = quotes["USDBBD"]; // 2.019106
    double quotes_USDBDT = quotes["USDBDT"]; // 84.793969
    float quotes_USDBGN = quotes["USDBGN"]; // 1.63546
    float quotes_USDBHD = quotes["USDBHD"]; // 0.376967
    int quotes_USDBIF = quotes["USDBIF"]; // 1966
    int quotes_USDBMD = quotes["USDBMD"]; // 1
    float quotes_USDBND = quotes["USDBND"]; // 1.342219
    float quotes_USDBOB = quotes["USDBOB"]; // 6.89487
    float quotes_USDBRL = quotes["USDBRL"]; // 5.717503
    float quotes_USDBSD = quotes["USDBSD"]; // 0.999966
    double quotes_USDBTC = quotes["USDBTC"]; // 0.000015807275
    double quotes_USDBTN = quotes["USDBTN"]; // 75.392423
    double quotes_USDBWP = quotes["USDBWP"]; // 10.952789
    float quotes_USDBYN = quotes["USDBYN"]; // 2.637262
    int quotes_USDBYR = quotes["USDBYR"]; // 19600
    float quotes_USDBZD = quotes["USDBZD"]; // 2.015658
    float quotes_USDCAD = quotes["USDCAD"]; // 1.254545
    double quotes_USDCDF = quotes["USDCDF"]; // 1997.99986
    float quotes_USDCHF = quotes["USDCHF"]; // 0.92049
    float quotes_USDCLF = quotes["USDCLF"]; // 0.025662
    double quotes_USDCLP = quotes["USDCLP"]; // 708.099929
    float quotes_USDCNY = quotes["USDCNY"]; // 6.541798
    float quotes_USDCOP = quotes["USDCOP"]; // 3668.5
    double quotes_USDCRC = quotes["USDCRC"]; // 613.098542
    int quotes_USDCUC = quotes["USDCUC"]; // 1
    float quotes_USDCUP = quotes["USDCUP"]; // 26.5
    double quotes_USDCVE = quotes["USDCVE"]; // 92.795312
    double quotes_USDCZK = quotes["USDCZK"]; // 21.671024
    double quotes_USDDJF = quotes["USDDJF"]; // 177.720473
    float quotes_USDDKK = quotes["USDDKK"]; // 6.22025
    double quotes_USDDOP = quotes["USDDOP"]; // 56.949489
    double quotes_USDDZD = quotes["USDDZD"]; // 132.270196
    double quotes_USDEGP = quotes["USDEGP"]; // 15.690686
    double quotes_USDERN = quotes["USDERN"]; // 15.001732
    double quotes_USDETB = quotes["USDETB"]; // 41.374984
    float quotes_USDEUR = quotes["USDEUR"]; // 0.836335
    float quotes_USDFJD = quotes["USDFJD"]; // 2.0594
    float quotes_USDFKP = quotes["USDFKP"]; // 0.726901
    float quotes_USDGBP = quotes["USDGBP"]; // 0.727015
    float quotes_USDGEL = quotes["USDGEL"]; // 3.424977
    float quotes_USDGGP = quotes["USDGGP"]; // 0.726901
    float quotes_USDGHS = quotes["USDGHS"]; // 5.785025
    float quotes_USDGIP = quotes["USDGIP"]; // 0.726901
    double quotes_USDGMD = quotes["USDGMD"]; // 51.050084
    double quotes_USDGNF = quotes["USDGNF"]; // 10004.999427
    float quotes_USDGTQ = quotes["USDGTQ"]; // 7.717426
    double quotes_USDGYD = quotes["USDGYD"]; // 209.806205
    float quotes_USDHKD = quotes["USDHKD"]; // 7.77164
    double quotes_USDHNL = quotes["USDHNL"]; // 24.124971
    float quotes_USDHRK = quotes["USDHRK"]; // 6.331199
    double quotes_USDHTG = quotes["USDHTG"]; // 81.699379
    double quotes_USDHUF = quotes["USDHUF"]; // 300.67981
    float quotes_USDIDR = quotes["USDIDR"]; // 14629.5
    float quotes_USDILS = quotes["USDILS"]; // 3.29341
    float quotes_USDIMP = quotes["USDIMP"]; // 0.726901
    double quotes_USDINR = quotes["USDINR"]; // 75.193103
    float quotes_USDIQD = quotes["USDIQD"]; // 1462.5
    double quotes_USDIRR = quotes["USDIRR"]; // 42105.000128
    double quotes_USDISK = quotes["USDISK"]; // 126.88033
    float quotes_USDJEP = quotes["USDJEP"]; // 0.726901
    double quotes_USDJMD = quotes["USDJMD"]; // 147.997931
    float quotes_USDJOD = quotes["USDJOD"]; // 0.709035
    double quotes_USDJPY = quotes["USDJPY"]; // 108.876008
    double quotes_USDKES = quotes["USDKES"]; // 106.903646
    double quotes_USDKGS = quotes["USDKGS"]; // 84.791302
    double quotes_USDKHR = quotes["USDKHR"]; // 4044.999793
    double quotes_USDKMF = quotes["USDKMF"]; // 412.624999
    double quotes_USDKPW = quotes["USDKPW"]; // 899.999742
    double quotes_USDKRW = quotes["USDKRW"]; // 1121.92498
    float quotes_USDKWD = quotes["USDKWD"]; // 0.30167
    float quotes_USDKYD = quotes["USDKYD"]; // 0.833288
    double quotes_USDKZT = quotes["USDKZT"]; // 433.847706
    double quotes_USDLAK = quotes["USDLAK"]; // 9420.000164
    double quotes_USDLBP = quotes["USDLBP"]; // 1524.013683
    double quotes_USDLKR = quotes["USDLKR"]; // 201.495774
    double quotes_USDLRD = quotes["USDLRD"]; // 172.594895
    float quotes_USDLSL = quotes["USDLSL"]; // 14.64992
    float quotes_USDLTL = quotes["USDLTL"]; // 2.95274
    float quotes_USDLVL = quotes["USDLVL"]; // 0.60489
    float quotes_USDLYD = quotes["USDLYD"]; // 4.519842
    float quotes_USDMAD = quotes["USDMAD"]; // 8.948951
    double quotes_USDMDL = quotes["USDMDL"]; // 17.889585
    double quotes_USDMGA = quotes["USDMGA"]; // 3775.000018
    double quotes_USDMKD = quotes["USDMKD"]; // 51.560022
    double quotes_USDMMK = quotes["USDMMK"]; // 1409.970567
    double quotes_USDMNT = quotes["USDMNT"]; // 2850.304767
    float quotes_USDMOP = quotes["USDMOP"]; // 8.006812
    double quotes_USDMRO = quotes["USDMRO"]; // 356.999828
    double quotes_USDMUR = quotes["USDMUR"]; // 40.346255
    float quotes_USDMVR = quotes["USDMVR"]; // 15.46968
    double quotes_USDMWK = quotes["USDMWK"]; // 785.000565
    float quotes_USDMXN = quotes["USDMXN"]; // 20.07568
    float quotes_USDMYR = quotes["USDMYR"]; // 4.130497
    double quotes_USDMZN = quotes["USDMZN"]; // 61.789987
    double quotes_USDNAD = quotes["USDNAD"]; // 14.649801
    double quotes_USDNGN = quotes["USDNGN"]; // 382.000447
    double quotes_USDNIO = quotes["USDNIO"]; // 35.060127
    float quotes_USDNOK = quotes["USDNOK"]; // 8.4677
    double quotes_USDNPR = quotes["USDNPR"]; // 120.62818
    float quotes_USDNZD = quotes["USDNZD"]; // 1.41794
    float quotes_USDOMR = quotes["USDOMR"]; // 0.384971
    float quotes_USDPAB = quotes["USDPAB"]; // 0.999966
    float quotes_USDPEN = quotes["USDPEN"]; // 3.613503
    float quotes_USDPGK = quotes["USDPGK"]; // 3.535007
    float quotes_USDPHP = quotes["USDPHP"]; // 48.5195
    double quotes_USDPKR = quotes["USDPKR"]; // 152.849732
    float quotes_USDPLN = quotes["USDPLN"]; // 3.81847
    double quotes_USDPYG = quotes["USDPYG"]; // 6243.955767
    float quotes_USDQAR = quotes["USDQAR"]; // 3.641012
    float quotes_USDRON = quotes["USDRON"]; // 4.116022
    double quotes_USDRSD = quotes["USDRSD"]; // 98.876518
    double quotes_USDRUB = quotes["USDRUB"]; // 76.011501
    int quotes_USDRWF = quotes["USDRWF"]; // 980
    float quotes_USDSAR = quotes["USDSAR"]; // 3.751051
    float quotes_USDSBD = quotes["USDSBD"]; // 7.990698
    double quotes_USDSCR = quotes["USDSCR"]; // 17.315268
    double quotes_USDSDG = quotes["USDSDG"]; // 381.500709
    float quotes_USDSEK = quotes["USDSEK"]; // 8.50423
    float quotes_USDSGD = quotes["USDSGD"]; // 1.33893
    float quotes_USDSHP = quotes["USDSHP"]; // 0.726901
    double quotes_USDSLL = quotes["USDSLL"]; // 10224.999648
    double quotes_USDSOS = quotes["USDSOS"]; // 586.000092
    double quotes_USDSRD = quotes["USDSRD"]; // 14.153991
    double quotes_USDSTD = quotes["USDSTD"]; // 20711.276062
    float quotes_USDSVC = quotes["USDSVC"]; // 8.750021
    double quotes_USDSYP = quotes["USDSYP"]; // 1257.602226
    double quotes_USDSZL = quotes["USDSZL"]; // 14.649736
    double quotes_USDTHB = quotes["USDTHB"]; // 31.457497
    double quotes_USDTJS = quotes["USDTJS"]; // 11.401758
    float quotes_USDTMT = quotes["USDTMT"]; // 3.51
    float quotes_USDTND = quotes["USDTND"]; // 2.760499
    float quotes_USDTOP = quotes["USDTOP"]; // 2.287102
    float quotes_USDTRY = quotes["USDTRY"]; // 8.10926
    float quotes_USDTTD = quotes["USDTTD"]; // 6.789248
    float quotes_USDTWD = quotes["USDTWD"]; // 28.4435
    double quotes_USDTZS = quotes["USDTZS"]; // 2318.999557
    double quotes_USDUAH = quotes["USDUAH"]; // 28.027162
    double quotes_USDUGX = quotes["USDUGX"]; // 3624.972669
    int quotes_USDUSD = quotes["USDUSD"]; // 1
    double quotes_USDUYU = quotes["USDUYU"]; // 44.108817
    double quotes_USDUZS = quotes["USDUZS"]; // 10501.999947
    double quotes_USDVEF = quotes["USDVEF"]; // 213830222338.07285
    float quotes_USDVND = quotes["USDVND"]; // 23070.5
    double quotes_USDVUV = quotes["USDVUV"]; // 109.527726
    float quotes_USDWST = quotes["USDWST"]; // 2.531453
    double quotes_USDXAF = quotes["USDXAF"]; // 551.618383
    float quotes_USDXAG = quotes["USDXAG"]; // 0.039386
    float quotes_USDXAU = quotes["USDXAU"]; // 0.000573
    float quotes_USDXCD = quotes["USDXCD"]; // 2.70255
    float quotes_USDXDR = quotes["USDXDR"]; // 0.701425
    double quotes_USDXOF = quotes["USDXOF"]; // 551.504108
    double quotes_USDXPF = quotes["USDXPF"]; // 100.298067
    double quotes_USDYER = quotes["USDYER"]; // 250.324976
    float quotes_USDZAR = quotes["USDZAR"]; // 14.50605
    double quotes_USDZMK = quotes["USDZMK"]; // 9001.195535
    double quotes_USDZMW = quotes["USDZMW"]; // 22.174681
    double quotes_USDZWL = quotes["USDZWL"]; // 322.000062
  }

  ///////A6_ParseFacts///////

  ///////A7_SystemFunctions///////
  //вычислительная часть
  if (millis () - period1 > 7000)
  {

    if (!mq135.isCalibrated() && mq135.heatingCompleted()) {

      mq135.calibrate();

      mq135.calibrate(160);

      Serial.print("Ro = ");
      Serial.println(mq135.getRo());
    }

    if (mq135.isCalibrated() && mq135.heatingCompleted()) {

      air = mq135.readCO2();
      Serial.print("Ratio: ");
      Serial.print(mq135.readRatio());
      // выводим значения газов в ppm
      Serial.print("\tCO2: ");
      Serial.print(mq135.readCO2());
      Serial.println(" ppm");
      //myNextion_setComponentText("co2", String(mq135.readCO2()));
    }

    f = bme.readTemperature();
    p = bme.readPressure();
    p = p * 0.0075;

    //temp = sht.getTemperature();  // get temp from SHT
    humidity = sht.getHumidity(); // get temp from SHT

    Serial.print("Temperature1: ");
    Serial.print(f, 1);
    Serial.println(" *C"); // println - с переносом строки print - без


    // Serial.print("Temp: ");      // print readings
    //Serial.print(temp);
    Serial.print("\t Humidity: ");
    Serial.println(humidity);

    Serial.print ("Air Quality is ");
    Serial.print (air);
    Serial.print (" PPM ");

    Serial.print("Pressure: ");
    Serial.print(p, 1);
    Serial.print(" torr");
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


    //Serial.print("Humidity: ");
    // Serial.print(w, 1);  // отправляем значение температуры на монитор
    // Serial.println(" "); // пустая строка
    //Serial.println(" "); // пустая строка



    // отправляем значение температуры на монитор

    /*
        lcd.setCursor(0, 0); // ставим курсор на 1 символ первой строки
        lcd.print("  VIVA GYMNASIUM N2 ");    // используем латинские буквы

        lcd.setCursor(0, 1); // ставим курсор на 3 символ второй строки
        lcd.print("Temperature: ");      // используем латинские буквы
        lcd.print(f, 1);        // выводим значение влажности на LCD
        lcd.print(char(1));  // выводим знак "градус"
        lcd.print("C");


        lcd.setCursor(0, 2); // ставим курсор на 3 символ второй строки
        lcd.print("Pressure: ");      // используем латинские буквы
        lcd.print(p, 1);        // выводим значение влажности на LCD
        lcd.print(" torr");


        lcd.setCursor(0, 3); // ставим курсор на 3 символ второй строки
        lcd.print("Humidity: ");      // используем латинские буквы
        lcd.print(h, 1);        // выводим значение влажности на LCD
        lcd.print(" %   ");
    */

    myNextion_setComponentText("t1", String(f));
    //myNextion_setComponentText("t3", String(humidity));
    //myNextion_setComponentText("t5", String(p));
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
  if (millis () - took > 2000)
  {
    if (indic1 == 0) {
      //myNextion.setComponentValue("va0", int(0));
    }
    else if (indic1 == 1) {
      //myNextion.setComponentValue("va0", int(1));
    }
    else {
      //myNextion.setComponentValue("va0", int(2));
    }
    Serial.println("debug");
    Serial.print("temp: ");
    Serial.println(t15);
    //myNextion_setComponentText("t15", String(t15));
    Serial.print("templike: ");
    Serial.println(t11);
    //myNextion_setComponentText("t11", String(t11));
    Serial.print("clouds: ");
    Serial.println(t17);
    //myNextion_setComponentText("t17", String(t17));
    Serial.print("pressure: ");
    Serial.println(t13);
    //myNextion_setComponentText("t13", String(t13));
    Serial.print("humidity: ");
    Serial.println(t12);
    //myNextion_setComponentText("t12", String(t12));
    Serial.print("wind speed: ");
    Serial.println(t16);
    //myNextion_setComponentText("t16", String(t16));
  }
  /*
    vw_rx_start();  // готовность приема
    buflen = VW_MAX_MESSAGE_LEN; //размер буфера задавать каждый раз
    if (vw_have_message()) { //ждем приема
    if (vw_get_message(buf, &buflen)) // Если данные приняты
    {
    vw_rx_stop(); //останавливаем прием и парсим:
    for (byte i = 0; i < 3; i++) // получить первые три байта
    str[i] = buf[i]; //
    str[3] = '\0';
    if ((str[0] == 'D') && (str[1] == 'A') && (str[2] == 'H')) {
    //сигнатура правильная, датчик обнаружен
    for (byte i = 3; i < 7; i++) // Получить четыре байта температуры
      str[i - 3] = buf[i]; // упаковать их в строку
    int tmpr = atoi(str); //преобразовать в целое число
    tmpr = tmpr - 2731; //вычесть 2731, получаем в десятых долях Цельсия
    //здесь можно поделить на 10 и преобразовать во float, если надо
    // здесь выводим температуру куда-то
    // влажность:
    for (byte i = 7; i < 11; i++) // Получить четыре байта влажности
      str[i - 7] = buf[i]; // упаковать их в строку
    int hh = atoi(str); //преобразовать в целое число
    hh = (hh - 1000) / 10;
    if (hh > 99) hh = 99; //получаем влажность в %, целое число
    //выводим куда-то
    } //end проверка сигнатуры DAT
    } //end данные приняты
    } //прием
  */



}

///////A8_JsonGet///////
void jsonGet() {

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {      /// подключаемся к серверу
    Serial.println("connection failed");
    return;
  }
  Serial.println("connected");
  // Make a HTTP request:
  client.println("GET /data/2.5/weather?q=Irkutsk&mode=json&units=metric&APPID=e9c015f4b101ce12f7d6ef877380cf27 HTTP/1.1");
  client.println("Host: api.openweathermap.org");
  client.println("Connection: close");
  client.println();



  //"+perem+"


  while (client.available()) {
    line = client.readStringUntil('\r');
    Serial.println(line);
  }

  Serial.println();
  Serial.println("closing connection");

}

///////A9_FactsGet///////

///////B1_NewsGet///////
void NewsGet() {

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {      /// подключаемся к серверу
    Serial.println("connection failed");
    return;
  }

  Serial.println("connected");
  // Make a HTTP request:
  client.println("GET https://newsapi.org/v2/top-headlines?country=ru&apiKey=a89c41848d64496982b694f40b35e3b7 HTTP/1.1");
  client.println("Host: newsapi.org");
  client.println("Connection: close");
  client.println();

  //"+perem+"


  while (client.available()) {
    Newsline = client.readStringUntil('\r');
    Serial.println(Newsline);
    Serial.println("Newsline");
  }

}

///////B2_CoinsGet///////
void CoinsGet() {

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {      /// подключаемся к серверу
    Serial.println("connection failed");
    return;
  }

  Serial.println("connected");
  // Make a HTTP request:
  client.println("GET https://newsapi.org/v2/top-headlines?country=ru&apiKey=a89c41848d64496982b694f40b35e3b7 HTTP/1.1");
  client.println("Host: newsapi.org");
  client.println("Connection: close");
  client.println();


  //"+perem+"


  while (client.available()) {
    Coinsline = client.readStringUntil('\r');
    Serial.println(Coinsline);
    Serial.println("Coinsline");
  }

}

uint8_t Cmd_End[3] = {0xFF, 0xFF, 0xFF};

void myNextion_setComponentText(char* ID, String string) {
  char buf[50];
  int len = sprintf (buf, "%s.txt=\"%s\"", ID, string);
  Serial.write(len);
  Serial.write(Cmd_End, 3);
}
