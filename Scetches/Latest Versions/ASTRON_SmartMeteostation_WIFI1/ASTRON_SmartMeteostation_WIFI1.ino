// GET запрос к http://api.openweathermap.org


#include <ESP8266WiFi.h>
#include <ArduinoJson.h>


const char* ssid     = "Rostelekom_217_2.4G";         // тут SSID и пароль к WIFI
const char* password = "GP2F042484";

const char* host = "api.openweathermap.org";     // тут адрес сервера

String WeatherData;
unsigned long WeatherWait;
bool WeatherFlag = true;
bool SerialFlag = true;

void setup() {
  Serial.begin(9600);
  delay(10);


  // в сетапе как обычно подключаемся к сети
  /*
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
  */
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  /*
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  */


}

void loop() {
  //900000
  if (millis () - WeatherWait > 50000 || WeatherFlag == true) {
    WeatherFlag = false;
    WeatherWait = millis();
    Get();
    Serial.print(WeatherData);
    /*
      StaticJsonDocument<1024> doc;

      DeserializationError error = deserializeJson(doc, WeatherData);

      if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
      }

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
      float main_temp = main["temp"]; // 282.04
      //Serial.print("Temperature: ");
      //Serial.println(main_temp);
      float main_feels_like = main["feels_like"]; // 279.79
      //Serial.print("Feels like: ");
      //Serial.println(main_feels_like);
      float main_temp_min = main["temp_min"]; // 282.03
      //Serial.print("Temperature(min): ");
      //Serial.println(main_temp_min);
      float main_temp_max = main["temp_max"]; // 283.63
      //Serial.print("Temperature(max): ");
      //Serial.println(main_temp_max);
      int main_pressure = main["pressure"]; // 1021
      //Serial.print("Pressure: ");
      //Serial.println(main_pressure);
      int main_humidity = main["humidity"]; // 60
      //Serial.print("Humidity: ");
      //Serial.println(main_humidity);
      int visibility = doc["visibility"]; // 10000
      //Serial.print("Visibility: ");
      //Serial.println(visibility);
      int wind_speed = doc["wind"]["speed"]; // 4
      //Serial.print("Wind speed: ");
      //Serial.println(wind_speed);
      int wind_deg = doc["wind"]["deg"]; // 60
      //Serial.print("Wind direction: ");
      //Serial.println(wind_deg);
      int clouds_all = doc["clouds"]["all"]; // 0
      //Serial.print("Cloud cover: ");
      //Serial.println(clouds_all);
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
      //Serial.print("City: ");
      //Serial.println(city);
      int cod = doc["cod"]; // 200
      //Serial.println(";:_:;");

      String FinalData = "sys," + weather_0_description + "," + main_temp  + "," + main_feels_like
                       + "," + main_temp_min + "," + main_temp_max + "," + main_pressure + ","
                       + main_humidity + "," + visibility + "," + wind_speed + "," + wind_deg + "," + clouds_all
                       + "," + "/end";
      if (SerialFlag == false) {

      Serial.println(FinalData);
      //Serial.println(millis());
      }
      else {
      SerialFlag = false;
      Serial.println(FinalData);
      delay(5000);
      Serial.println(FinalData);
      }
      }
    */
  }
}

  void Get() {


    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {      /// подключаемся к серверу
      Serial.println("connection failed");
      return;
    }
    /// если подключились, отправляем чего от сервера хотим
    // сам GET запрос с ID и ключем
    client.println("GET /data/2.5/weather?q=Irkutsk&mode=json&units=metric&APPID=e9c015f4b101ce12f7d6ef877380cf27 HTTP/1.1");
    // говорим к какому хосту обращаемся (на сервере может быть несколько сайтов)
    client.println("Host: api.openweathermap.org");
    // говорим что закончили
    client.println("Connection: close");
    client.println();

    delay(1000);  // ждем немного
    // читаем ответ и отправляем его в Serial
    while (client.available()) {
      WeatherData = client.readStringUntil('\r');
      //Serial.print(WeatherData);
    }

    //Serial.println();
    //Serial.println("closing connection");
  }
