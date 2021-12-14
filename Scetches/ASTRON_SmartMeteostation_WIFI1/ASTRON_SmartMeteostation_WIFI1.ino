// GET запрос к http://api.openweathermap.org


#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SHT21.h>
#include <SoftwareSerial.h>
#include <Nextion.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <ASTRON_CCS811.h>

#define I2Cdelay 50 //50 for ESP, 0 for other platforms
#define addr ADDRESS //If doesn`t work - change to ALT_ADDRESS


// Nextion TX к пин 13, RX к пин 15 Arduino
SoftwareSerial nextion(13, 15);
//SoftwareSerial bluethooth(12, 14);
// создание объекта Nextion к порту на скорости 9600 бод
Nextion myNextion(nextion, 9600);

CCS811 sensor(I2Cdelay, addr);
Adafruit_BMP280 bme; // I2C
WiFiServer server(80);
SHT21 sht;

const char* ssid     = "Rostelekom_217_2.4G";         // тут SSID и пароль к WIFI
const char* password = "GP2F042484";

const char* host = "api.openweathermap.org";     // тут адрес сервера

String WeatherData;
unsigned long WeatherWait;
bool WeatherFlag = true;
bool SerialFlag = true;
bool AQIFlag = true;
bool WebServerType = false; // true - web server, false - mobile app

unsigned long period1 = 0; //как часто печатать данные
unsigned long period2 = 0;
unsigned long AQIRequest = 0;
unsigned long took = 0;

byte indic = 2;
int indic1 = 0;

int f; //температура2
int p; //давление
int humidity;

int air_co2;

float k; //предсказание погоды
float press_new;
float press_old;
float delta_press;

String AQIStatus;
String AQIStatus_web;
String AQILine;


int list_0_main_aqi;
float list_0_components_co;
float list_0_components_no;
float list_0_components_no2;
float list_0_components_o3;
float list_0_components_so2;
float list_0_components_pm2_5;
float list_0_components_pm10;
float list_0_components_nh3;

int main_temp;
int main_feels_like;
int main_temp_min;
int main_temp_max;
int main_pressure;
int main_humidity;
int visibility;
int wind_speed;
int wind_deg;
int clouds_all;

String WIFIip;
String APIID = "SomeAPI";
String CityName = "Irkutsk";
String Lat = "SomeLat";
String Lon = "SomeLon";
String errstat = "Init_OK";

void setup() {

  Init();

  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print(".... ");
  //Serial.println("");
  Serial.print("OK");
  Serial.println();
  Serial.println("IP address: ");
  WIFIip = WiFi.localIP().toString();
  Serial.println(WIFIip);
  Serial.println();

}

void loop() {
  if (millis () - WeatherWait > 900000 || WeatherFlag == true) {
    WeatherFlag = false;
    WeatherWait = millis();
    ParseWeather();
  }

  if (millis() - AQIRequest > 960000 || AQIFlag == true)
  {
    AQIFlag = false;
    AQIRequest = millis();
    AQIParse();
  }

  if (millis () - period1 > 7000) {
    period1 = millis();
    ReadFromSensors();
    // SendToAPP();
  }

  if (millis() - took > 2000) {
    SendToNextion();
  }

  WebServer();
}


void WeatherGet() {


  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {      /// подключаемся к серверу
    Serial.println("connection failed");
    return;
  }
  /// если подключились, отправляем чего от сервера хотим
  // сам GET запрос с ID и ключем
  client.println("GET /data/2.5/weather?q=" + CityName + "&mode=json&units=metric&APPID=" + APIID + " HTTP/1.1");
  // говорим к какому хосту обращаемся (на сервере может быть несколько сайтов)
  client.println("Host: api.openweathermap.org");
  // говорим что закончили
  client.println("Connection: close");
  client.println();

  delay(1000);  // ждем немного
  // читаем ответ и отправляем его в Serial
  while (client.available()) {
    WeatherData = client.readStringUntil('\r');
    Serial.print(WeatherData);
  }

  //Serial.println();
  //Serial.println("closing connection");
}

void Init() {
  Serial.begin(9600); // запуск последовательного порта
  //bluethooth.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("#");
  }
  Serial.print("|");
  Serial.println();
  myNextion.init();
  Serial.println("NextionInit.... OK");
  Wire.begin();
  Serial.println("WireInit.... OK");
  server.begin();
  Serial.println(("Server.... OK"));
  Serial.setTimeout(5000);

  if (!sensor.begin()) {
    Serial.println("CCS811Init.... Err");
    errstat = "CCS_Err";
  }
  else {
    Serial.println("CCS811Init.... OK");
  }
  delay(1000);

  if (!bme.begin(BMP280_ADDRESS - 1)) {
    Serial.println("BMP280Init.... Err");
    errstat = "BMP_Err";
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    delay(2000);
  }
  else {
    Serial.println("BMP280Init.... OK");
  }


}

void AQIGet() {
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {      /// подключаемся к серверу
    Serial.println("connection failed");
    return;
  }
  /// если подключились, отправляем чего от сервера хотим
  // сам GET запрос с ID и ключем
  client.println("GET /data/2.5/air_pollution?lat=" + Lat + "&lon=" + Lon + "&appid=" + APIID + " HTTP/1.1");
  // говорим к какому хосту обращаемся (на сервере может быть несколько сайтов)
  client.println("Host: api.openweathermap.org");
  // говорим что закончили
  client.println("Connection: close");
  client.println();

  delay(1000);  // ждем немного
  // читаем ответ и отправляем его в Serial
  while (client.available()) {
    AQILine = client.readStringUntil('\r');
    Serial.print(AQILine);
  }

  Serial.println();
  Serial.println("closing connection");
}

void WebServer() {
  if (WebServerType == true) {
    WiFiClient client = server.available();
    if (!client) {
      return;
    }
    Serial.println(F("new client"));

    client.setTimeout(5000); // default is 1000

    // Read the first line of the request
    String req = client.readStringUntil('\r');
    Serial.println(F("request: "));
    Serial.println(req);







    while (client.available()) {

      client.read();
    }


    client.print("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head>");
    client.println("<title>Meteostation</title>");
    client.println("<link rel='icon' type='image/png' href='https://image.flaticon.com/icons/png/512/1163/1163661.png' />");
    client.println("<meta charset='UTF-8'>");

    client.println("<style>");

    client.println("* {");
    client.println("margin: 0;");
    client.println("padding: 0;");
    client.println("}");

    client.println("body, html {");
    client.println("background: #0a0a0a;");
    client.println("}");

    client.println("#S0 {");
    client.println("background: #454647;");
    client.println("margin: 0px;");
    client.println("padding: 0px;");
    client.println("width: 100vw;");
    client.println("height: 0vw, 100vw;");
    client.println("vertical-align: top;");
    client.println("}");

    client.println("#S1 {");
    client.println("font-family: Bahnschrift;");
    client.println("margin: 0px;");
    client.println("}");

    client.println("#S2 {");
    client.println("font-family: Bahnschrift;");
    client.println("color: #e1e3e6;");
    client.println("background: #71aaeb;");
    client.println("}");

    client.println(".Value-wrapper {");
    client.println("display: block;");
    client.println("width: 100%;");
    client.println("float: left;");
    client.println("transition: width .2s;");
    client.println("}");

    client.println("@media only screen and (min-width: 450px) {");
    client.println(".Value-wrapper {");
    client.println("width: 50%;");
    client.println("}");
    client.println("}");

    client.println("@media only screen and (min-width: 768px) {");
    client.println(".Value-wrapper {");
    client.println("width: 33.333%;");
    client.println("}");
    client.println("}");

    client.println("@media only screen and (min-width: 1000px) {");
    client.println(".Value-wrapper {");
    client.println("width: 25%;");
    client.println("}");
    client.println("}");

    client.println(".Value {");
    client.println("display: block;");
    client.println("border: 1px solid #71aaeb;");
    client.println("border-radius: 3px;");
    client.println("position: relative;");
    client.println("background: #5d5f61;");
    client.println("margin: 10px;");
    client.println("text-decoration: none;");
    client.println("color: #474747;");
    client.println("z-index: 0;");
    client.println("height: 200px;");
    client.println("}");

    client.println(".Text {");
    client.println("margin: 3px;");
    client.println("font-family: Bahnschrift;");
    client.println("text-align: center;");
    client.println("font-size: 50px;");
    client.println("color: #e1e3e6;");
    client.println("}");

    client.println(".TextS {");
    client.println("margin: 3px;");
    client.println("font-family: Bahnschrift;");
    client.println("font-size: 30px;");
    client.println("color: #e1e3e6;");
    client.println("}");

    client.println("</style>");

    client.println("</head>");

    client.println("<body>");
    client.println("<h1 id='S0'><left><span style='text-indent:20px' id='S1'>Smart</span> <span id='S2'>Meteostation</span></left></h1>");

    client.println("<ul class='Grid'>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>Температура (дома):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(f);
    client.println(" °C</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>Влажность (дома):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(humidity);
    client.println(" %</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>Давление (дома):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(p);
    client.println(" мм.рт.ст</h1>");
    client.println("</a>");
    client.println("</li>");
    /*
      client.println("<li class='Value-wrapper'>");
      client.println("<a href='' class='Value'>");
      client.println("<p class='TextS'>CO2 (дома):</p>");
      client.println("<br />");
      client.println("<h1 class='Text'>");
      client.println(main_humidity);
      client.println(" %</h1>");
      client.println("</a>");
      client.println("</li>");
    */
    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>Температура (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(main_temp);
    client.println(" °C</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>Ощущается как (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(main_feels_like);
    client.println(" °C</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>Влажность (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(main_humidity);
    client.println(" %</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>Давление (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(main_pressure);
    client.println(" мм.рт.ст</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>Облачность (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(clouds_all);
    client.println(" %</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>Скорость ветра (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(wind_speed);
    client.println(" м/с</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>Направление ветра (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(wind_deg);
    client.println(" °</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>AQI (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(AQIStatus_web);
    client.println("</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>CO (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(list_0_components_co);
    client.println(" μg/m3</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>NO (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(list_0_components_no);
    client.println(" μg/m3</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>NO2 (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(list_0_components_no2);
    client.println(" μg/m3</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>O3 (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(list_0_components_o3);
    client.println(" μg/m3</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>SO2 (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(list_0_components_so2);
    client.println(" μg/m3</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>PM2.5 (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(list_0_components_pm2_5);
    client.println(" μg/m3</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>PM10 (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(list_0_components_pm10);
    client.println(" μg/m3</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("<li class='Value-wrapper'>");
    client.println("<a href='' class='Value'>");
    client.println("<p class='TextS'>NH3 (на улице):</p>");
    client.println("<br />");
    client.println("<h1 class='Text'>");
    client.println(list_0_components_nh3);
    client.println(" μg/m3</h1>");
    client.println("</a>");
    client.println("</li>");

    client.println("</ul>");
    client.println("</body>");
    client.println("</html>");

    Serial.println(F("Disconnecting from client"));
  }
  else {

    WiFiClient client = server.available();
    if (!client) {
      return;
    }
    Serial.println(F("new client"));

    client.setTimeout(5000); // default is 1000

    // Read the first line of the request
    String req = client.readStringUntil('\r');
    Serial.println(F("request: "));
    Serial.println(req);

    while (client.available()) {

      client.read();
    }


    client.print("{\"errstat\":\"" + errstat + "\",\"Homedata\":{\"htemp\":" + f + ",\"hhum\":" + humidity + ",\"hpress\":" + p + ",\"hco2\":" + air_co2 + "},\"Outdata\":{\"outtemp\":" + main_temp +
  ",\"outfl\":" + main_feels_like + ",\"outpress\":" + main_pressure + ",\"outhum\":" + main_humidity + ",\"outvis\":" + visibility + ",\"outwindspeed\":" + wind_speed + ",\"outwinddirection\":" + wind_deg +
  ",\"outclouds\":" + clouds_all + "},\"Airdata\":{\"outco\":" + list_0_components_co + ",\"outno\":" + list_0_components_no + ",\"outno2\":" + list_0_components_no2 + ",\"outo3\":" + list_0_components_o3 +
  ",\"outso2\":" + list_0_components_so2 + ",\"outpm2_5\":" + list_0_components_pm2_5 + ",\"outpm10\":" + list_0_components_pm10 + ",\"outnh3\":" + list_0_components_nh3 + ",\"outaqi\":\"" + AQIStatus_web + "\"},\"city\":\"" + CityName + "\"}");
  }
  
}


void ParseWeather() {
  WeatherGet();
  //Serial.print(WeatherData);


  StaticJsonDocument<1024> doc;

  DeserializationError error = deserializeJson(doc, WeatherData);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    WeatherFlag = true;
    return;
  }
  Serial.println();
  float coord_lon = doc["coord"]["lon"]; // 38.9769
  float coord_lat = doc["coord"]["lat"]; // 45.0328

  JsonObject weather_0 = doc["weather"][0];
  int weather_0_id = weather_0["id"]; // 800
  const char* weather_0_main = weather_0["main"]; // "Clear"
  String weather_0_description = weather_0["description"]; // "clear sky"
  //Serial.print("Description: ");
  //Serial.println(weather_0_description);
  const char* weather_0_icon = weather_0["icon"]; // "01d"

  const char* base = doc["base"]; // "stations"

  JsonObject main = doc["main"];
  main_temp = main["temp"]; // 282.04
  Serial.print("Temperature: ");
  Serial.println(main_temp);
  main_feels_like = main["feels_like"]; // 279.79
  Serial.print("Feels like: ");
  Serial.println(main_feels_like);
  main_temp_min = main["temp_min"]; // 282.03
  Serial.print("Temperature(min): ");
  Serial.println(main_temp_min);
  main_temp_max = main["temp_max"]; // 283.63
  Serial.print("Temperature(max): ");
  Serial.println(main_temp_max);
  main_pressure = main["pressure"]; // 1021
  main_pressure = main_pressure / 1.333;
  Serial.print("Pressure: ");
  Serial.println(main_pressure);
  main_humidity = main["humidity"]; // 60
  Serial.print("Humidity: ");
  Serial.println(main_humidity);
  visibility = doc["visibility"]; // 10000
  visibility = visibility / 1000;
  Serial.print("Visibility: ");
  Serial.println(visibility);
  wind_speed = doc["wind"]["speed"]; // 4
  Serial.print("Wind speed: ");
  Serial.println(wind_speed);
  wind_deg = doc["wind"]["deg"]; // 60
  Serial.print("Wind direction: ");
  Serial.println(wind_deg);
  clouds_all = doc["clouds"]["all"]; // 0
  Serial.print("Cloud cover: ");
  Serial.println(clouds_all);
  long dt = doc["dt"]; // 1637240975

  JsonObject sys = doc["sys"];
  int sys_type = sys["type"]; // 2
  long sys_id = sys["id"]; // 2012251
  const char* sys_country = sys["country"]; // "RU"
  long sys_sunrise = sys["sunrise"]; // 1637209557
  long sys_sunset = sys["sunset"]; // 1637243572

  int timezone = doc["timezone"]; // 10800
  long id = doc["id"]; // 542420
  const char* city = doc["name"]; // "Krasnodar"
  Serial.print("City: ");
  Serial.println(city);
  int cod = doc["cod"]; // 200

  Serial.println();
}

void AQIParse() {
  //if ( millis() - Weather > 3000)
  {

    //Weather = millis();
    AQIGet();
  }
  StaticJsonDocument<400> doc;
  DeserializationError error = deserializeJson(doc, AQILine);
  if (error) {
    Serial.println("deserializeJson() failed with code:");
    Serial.print(error.c_str());
    AQIFlag = true;
    //WeatherFlag = true;
    AQIGet();
    return;
  }


  /// отправка в Serial
  Serial.println();

  JsonObject list_0 = doc["list"][0];

  list_0_main_aqi = list_0["main"]["aqi"];

  if (list_0_main_aqi == 1) {
    AQIStatus = "Good";
    AQIStatus_web = "Хорошо";
  }
  else if (list_0_main_aqi == 2) {
    AQIStatus = "Fair";
    AQIStatus_web = "Приемлемо";
  }
  else if (list_0_main_aqi == 3) {
    AQIStatus = "Moderate";
    AQIStatus_web = "Умеренно";
  }
  else if (list_0_main_aqi == 4) {
    AQIStatus = "Poor";
    AQIStatus_web = "Плохо";
  }
  else {
    AQIStatus = "Very Poor";
    AQIStatus_web = "Очень плохо";
  }

  Serial.print("AQI: ");
  Serial.print(list_0_main_aqi);
  Serial.print(" - ");
  Serial.println(AQIStatus_web);

  JsonObject list_0_components = list_0["components"];

  list_0_components_co = list_0_components["co"];
  Serial.print("CO: ");
  Serial.print(list_0_components_co);
  Serial.println(" μg/m3");

  list_0_components_no = list_0_components["no"];
  Serial.print("NO: ");
  Serial.print(list_0_components_no);
  Serial.println(" μg/m3");

  list_0_components_no2 = list_0_components["no2"];
  Serial.print("NO2: ");
  Serial.print(list_0_components_no2);
  Serial.println(" μg/m3");

  list_0_components_o3 = list_0_components["o3"];
  Serial.print("O3: ");
  Serial.print(list_0_components_o3);
  Serial.println(" μg/m3");

  list_0_components_so2 = list_0_components["so2"];
  Serial.print("SO2: ");
  Serial.print(list_0_components_so2);
  Serial.println(" μg/m3");

  list_0_components_pm2_5 = list_0_components["pm2_5"];
  Serial.print("PM2.5: ");
  Serial.print(list_0_components_pm2_5);
  Serial.println(" μg/m3");

  list_0_components_pm10 = list_0_components["pm10"];
  Serial.print("PM10: ");
  Serial.print(list_0_components_pm10);
  Serial.println(" μg/m3");

  list_0_components_nh3 = list_0_components["nh3"];
  Serial.print("NH3: ");
  Serial.print(list_0_components_nh3);
  Serial.println(" μg/m3");

  Serial.println();
}

void ReadFromSensors() {
  f = bme.readTemperature();
  p = bme.readPressure();
  p = p * 0.0075;
  humidity = sht.getHumidity(); // get temp from SHT

  if (sensor.readCO2() != 0) air_co2 = sensor.readCO2();
  Serial.println();
  Serial.print("CO2: ");
  Serial.print(air_co2);
  Serial.println(" ppm");

  Serial.print("Temperature1: ");
  Serial.print(f, 1);
  Serial.println(" *C"); // println - с переносом строки print - без

  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("Pressure: ");
  Serial.print(p, 1);
  Serial.print(" mmHg");



  //    f = round(f);
  //    p = round(p);
  //    humidity = round(humidity);

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

void SendToNextion() {
  myNextion.setComponentText("outtemp", String(main_temp));
  myNextion.setComponentText("outtempMax", String(main_temp_max));
  myNextion.setComponentText("outtempMin", String(main_temp_min));
  myNextion.setComponentText("outfl", String(main_feels_like));
  myNextion.setComponentText("outpress", String(main_pressure));
  myNextion.setComponentText("outhum", String(main_humidity));
  myNextion.setComponentText("outvis", String(visibility));
  myNextion.setComponentText("outws", String(wind_speed));
  myNextion.setComponentText("outwd", String(wind_deg));
  myNextion.setComponentText("outcloud", String(clouds_all));

  myNextion.setComponentText("htemp", String(f));
  myNextion.setComponentText("hhum", String(humidity));
  myNextion.setComponentText("hpress", String(p));
  myNextion.setComponentText("hco2", String(air_co2));

  myNextion.setComponentText("outco", String(list_0_components_co));
  myNextion.setComponentText("outno", String(list_0_components_no));
  myNextion.setComponentText("outno2", String(list_0_components_no2));
  myNextion.setComponentText("outo3", String(list_0_components_o3));
  myNextion.setComponentText("outso2", String(list_0_components_so2));
  myNextion.setComponentText("outpm25", String(list_0_components_pm2_5));
  myNextion.setComponentText("outpm10", String(list_0_components_pm10));
  myNextion.setComponentText("outnh3", String(list_0_components_nh3));
  myNextion.setComponentText("outaqi", String(AQIStatus_web));
  myNextion.setComponentText("IPaddress", String(WIFIip));
}
/*
  void SendToAPP() {
  Serial.println("{\"errstat\":\"" + errstat + "\",\"Homedata\":{\"htemp\":" + f + ",\"hhum\":" + humidity + ",\"hpress\":" + p + ",\"hco2\":" + air_co2 + "},\"Outdata\":{\"outtemp\":" + main_temp +
  ",\"outfl\":" + main_feels_like + ",\"outpress\":" + main_pressure + ",\"outhum\":" + main_humidity + ",\"outvis\":" + visibility + ",\"outwindspeed\":" + wind_speed + ",\"outwinddirection\":" + wind_deg +
  ",\"outcloud\":" + clouds_all + "},\"Airdata\":{\"outco\":" + list_0_components_co + ",\"outno\":" + list_0_components_no + ",\"outno2\":" + list_0_components_no2 + ",\"outo3\":" + list_0_components_o3 +
  ",\"outso2\":" + list_0_components_so2 + ",\"outpm2_5\":" + list_0_components_pm2_5 + ",\"outpm10\":" + list_0_components_pm10 + ",\"outnh3\":" + list_0_components_nh3 + ",\"outaqi\":\"" + AQIStatus_web + "\"},\"city\":\"" + CityName + "\"}");

  bluethooth.println("{\"errstat\":\"" + errstat + "\",\"Homedata\":{\"htemp\":" + f + ",\"hhum\":" + humidity + ",\"hpress\":" + p + ",\"hco2\":" + air_co2 + "},\"Outdata\":{\"outtemp\":" + main_temp +
  ",\"outfl\":" + main_feels_like + ",\"outpress\":" + main_pressure + ",\"outhum\":" + main_humidity + ",\"outvis\":" + visibility + ",\"outwindspeed\":" + wind_speed + ",\"outwinddirection\":" + wind_deg +
  ",\"outcloud\":" + clouds_all + "},\"Airdata\":{\"outco\":" + list_0_components_co + ",\"outno\":" + list_0_components_no + ",\"outno2\":" + list_0_components_no2 + ",\"outo3\":" + list_0_components_o3 +
  ",\"outso2\":" + list_0_components_so2 + ",\"outpm2_5\":" + list_0_components_pm2_5 + ",\"outpm10\":" + list_0_components_pm10 + ",\"outnh3\":" + list_0_components_nh3 + ",\"outaqi\":\"" + AQIStatus_web + "\"},\"city\":\"" + CityName + "\"}");
  }
*/
