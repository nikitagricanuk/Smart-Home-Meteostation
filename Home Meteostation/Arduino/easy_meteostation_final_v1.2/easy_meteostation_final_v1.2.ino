#include <VirtualWire.h>
#include <TroykaMQ.h>
#include <Ethernet.h>
#include <ArduinoJson.h>
#include <SHT21.h>  
#include <SoftwareSerial.h> // подключение библиотеки для работы с Software Serial 
#include <Nextion.h>
//#include  <Servo.h>  // библиотека для сервомоторов
#include <Wire.h>  // библиотека для протокола I2C
#include <SPI.h>  // Библиотека для работы с шиной SPI
#include <Adafruit_BMP280.h> // Библиотека для работы с датчиком BMP280


// имя для пина, к которому подключен датчик
#define PIN_MQ135         A0
// имя для пина, к которому подключен нагреватель датчика
#define PIN_MQ135_HEATER  11

// Nextion TX к пин 2, RX к пин 3 Arduino
SoftwareSerial nextion(18, 17);

// создаём объект для работы с датчиком
// и передаём ему номер пина выходного сигнала и нагревателя
MQ135 mq135(PIN_MQ135);



// создание объекта Nextion к порту на скорости 9600 бод
Nextion myNextion(nextion, 9600);

Adafruit_BMP280 bme; // I2C

SHT21 sht;


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

EthernetClient client;

char server[] = "api.openweathermap.org";

byte indic = 2;

//float h; // влажность
//float t; // температура
float f; //температура2
float p; //давление
//float q; // температура3
//float w; //влажность1
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


float humidity; 

unsigned long period1 = 0; //как часто печатать данные
unsigned long period2 = 0;
unsigned long timer = 0;

unsigned long minuts = 10 * 60000;  // продолжительность игры в минутах
unsigned long game_time = 0;
unsigned long game = 0;

unsigned long lastConnectionTime = 0;         
const unsigned long postingInterval = 10 * 1000;

String line;

boolean http = true;

const int sensorPin = 0;
int air_quality;
float air;

char str[5]; //вспомогательная строка для преобразований ASCII в число
  uint8_t buf [VW_MAX_MESSAGE_LEN];  //буфер для хранения принятых данных
  uint8_t buflen = VW_MAX_MESSAGE_LEN;  // max длина принятых данных

// служебные переменные
//char buf[10];



// создаем символ градуса и присваиваем имя "gradus"
//byte gradus[8] = {
//0b01100, 0b10010, 0b10010, 0b01100, 0b00000, 0b00000, 0b00000, 0b00000
//};

void setup() {
  Serial.begin(9600); // запуск последовательного порта
  myNextion.init();
  myNextion.setComponentText("city", "test");
 
  while (!Serial) {
    ; 
  }

  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); 
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
   
    Ethernet.begin(mac, ip, myDns);
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }

  delay(1000);



  // инициализация Nextion
  
  Serial.println("start");

  Wire.begin();

  //servo_h.attach(8);         // указываем порты для сервомоторов
  //servo_v.attach(7);


  if (!bme.begin(BMP280_ADDRESS - 1)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    delay(2000);
  }


  // включаем нагреватель
  vw_set_rx_pin(2); //D2 Вывод приемника VirtualWire
  vw_setup(1200); // Скорость соединения VirtualWire
  mq135.heaterPwrHigh();
  Serial.println("Heated sensor");
  attachInterrupt(0, buttonNex, CHANGE);
  attachInterrupt(4, GiveData, CHANGE); //подключаем приемник к пину 19!
}



void loop()  {
  Serial.println("hello");

  if (millis() - OpenWeatherMap > 900000 || http == true)
  {
    OpenWeatherMap = millis();

    jsonGet();

    StaticJsonDocument<2000> doc;                   /// буфер на 2000 символов
    DeserializationError error = deserializeJson(doc, line);     // скармиваем String
    if (error) {
      Serial.println("deserializeJson() failed with code:");
      Serial.print(error.c_str());// если ошибка, сообщаем об этом
      jsonGet();                                         // пинаем сервер еще раз
      return;                                             // и запускаем заного
    }


    /// отправка в Serial
    Serial.println();
    String name1 = doc["name"];                           // достаем имя,
    Serial.print("name:");
    Serial.println(name1);
    myNextion.setComponentText("city", String(name1));

    float tempC = doc["main"]["temp"];                   // достаем температуру из структуры main
    tempC = round(tempC);
    t15 = tempC;
    //float tempC = tempK - 273.15;                         // переводим кельвины в цельси
    Serial.print("temp: ");
    Serial.print(t15);                                  // отправляем значение в сериал
    Serial.println(" C");
    myNextion.setComponentText("t15", String(t15));
    if (t15 != 0)
    {
      http = false;
    }

    float tempClike = doc["main"]["feels_like"];            // и так далее
    //float tempCmin = tempKmin - 273.15;
    tempClike = round(tempClike);
    t11 = tempClike;
    Serial.print("temp min: ");
    Serial.print(t11);
    Serial.println(" C");
    myNextion.setComponentText("t11", String(t11));

    float clouds = doc["clouds"]["all"];
    clouds = round(clouds);
    t17 = clouds;
    //float tempCmax = tempKmax - 273.15;
    Serial.print("temp max: ");
    Serial.print(t17);
    Serial.println(" C");
    myNextion.setComponentText("t17", String(t17));

    int pressurehPa = doc["main"]["pressure"];
    float pressure = pressurehPa / 1.333;
    pressure = round(pressure);
    t13 = pressure;
    Serial.print("pressure: ");
    Serial.print(t13);
    Serial.println(" mmHc");
    myNextion.setComponentText("t13", String(t13));

    int humidity = doc["main"]["humidity"];
    humidity = round(humidity);
    t12 = humidity;
    Serial.print("humidity: ");
    Serial.print(t12);
    Serial.println(" %");
    myNextion.setComponentText("t12", String(t12));

    float windspeed = doc["wind"]["speed"];
    windspeed = round(windspeed);
    t16 = windspeed;
    Serial.print("wind speed: ");
    Serial.print(t16);
    Serial.println(" m/s");
    myNextion.setComponentText("t16", String(t16));

    //int winddeg = doc["wind"]["deg"];
    //Serial.print("wind deg :");
    //Serial.println(winddeg);


    Serial.println();
    Serial.println();

  }


  //вычислительная часть
  if (millis () - period1 > 7000)
  {


 if (!mq135.isCalibrated() && mq135.heatingCompleted()) {
    // выполняем калибровку датчика на чистом воздухе
    mq135.calibrate();
    // если известно сопротивление датчика на чистом воздухе 
    // можно его указать вручную, допустим 160
    mq135.calibrate(14.88);
    // выводим сопротивление датчика в чистом воздухе (Ro) в serial-порт
    Serial.print("Ro = ");
    Serial.println(mq135.getRo());
  }
  // если прошёл интевал нагрева датчика
  // и калибровка была совершена
  if (mq135.isCalibrated() && mq135.heatingCompleted()) {
    // выводим отношения текущего сопротивление датчика
    // к сопротивлению датчика в чистом воздухе (Rs/Ro)
    Serial.print("Ratio: ");
    Serial.print(mq135.readRatio());
    // выводим значения газов в ppm
    Serial.print("\tCO2: ");
    Serial.print(mq135.readCO2());
    Serial.println(" ppm");
    myNextion.setComponentText("co2", String(mq135.readCO2()));
  }
    f = bme.readTemperature();
    p = bme.readPressure();
    p = p * 0.0075;


    humidity = sht.getHumidity(); 

    Serial.print("Temperature1: ");
    Serial.print(f, 1);
    Serial.println(" *C"); 

 
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
      Serial.println("  rise");
    }
    if (indic == 1)
    {
      Serial.println("  fall");
    }
    if (indic == 2)
    {
      Serial.println("  without changes");
    }


    

    myNextion.setComponentText("t1", String(f));
    myNextion.setComponentText("t3", String(humidity));
    myNextion.setComponentText("t5", String(p));
  }

  // предсказание погоды
  if (millis () - period2 > 1800000)
  {
    if (k >= 6)// число циклов по 30мин в большом цикле
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
    Serial.println("debug");
    Serial.print("temp: ");
    Serial.println(t15);
    myNextion.setComponentText("t15", String(t15));
    Serial.print("templike: ");
    Serial.println(t11);
    myNextion.setComponentText("t11", String(t11));
    Serial.print("clouds: ");
    Serial.println(t17);
    myNextion.setComponentText("t17", String(t17));
    Serial.print("pressure: ");
    Serial.println(t13);
    myNextion.setComponentText("t13", String(t13));
    Serial.print("humidity: ");
    Serial.println(t12);
    myNextion.setComponentText("t12", String(t12));
    Serial.print("wind speed: ");
    Serial.println(t16);
    myNextion.setComponentText("t16", String(t16));
  }



  while (client.available()) {
    line = client.readStringUntil('\r');
    Serial.print(line);
  }




}


void jsonGet() {




  {
   
    Serial.println("knopa");
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /data/2.5/weather?q=Irkutsk&mode=json&units=metric&APPID=e9c015f4b101ce12f7d6ef877380cf27 HTTP/1.1");
      client.println("Host: api.openweathermap.org");
      client.println("Connection: close");
      client.println();
    }
    else {

      Serial.println("connection failed");
    }


    delay(1000);
    while (client.available()) {
      line = client.readStringUntil('\r');
      Serial.println("line");
      Serial.println(line);
    }

    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting.");
      client.stop();


    }
  }
}
void buttonNex() {
String message = myNextion.listen(); //check for message
  if (message == "65 17 0C 01 FF FF FF ") {
    //myNextion.buttonToggle(button1State, "b0", 0, 2);
    //кухня
  }
  if (message == "65 17 0D 01 FF FF FF ") {
    //myNextion.buttonToggle(button2State, "b1", 0, 2);
    //гостинная
  }
  if (message == "65 17 0E 01 FF FF FF ") {
    //myNextion.buttonToggle(button2State, "b1", 0, 2);
    //зал
  }
  if (message == "65 17 0F 01 FF FF FF ") {
    //myNextion.buttonToggle(button2State, "b1", 0, 2);
    //коридор
  }
  if (message == "65 17 10 01 FF FF FF ") {
    //myNextion.buttonToggle(button2State, "b1", 0, 2);
    //спальня
  }
  if (message == "65 17 11 01 FF FF FF ") {
    //myNextion.buttonToggle(button2State, "b1", 0, 2);
    //туалет
  }
    if (message == "65 10 19 01 FF FF FF ") {
    //myNextion.buttonToggle(button2State, "b1", 0, 2);
    http = true;
    jsonGet();
  }
}
void GiveData() {
vw_rx_start();  // готовность приема
  buflen = VW_MAX_MESSAGE_LEN; //размер буфера задавать каждый раз
 if (vw_have_message()) { //ждем приема
 if (vw_get_message(buf, &buflen)) // Если данные приняты
  {
    vw_rx_stop(); //останавливаем прием и парсим:
        for (byte i=0; i<3; i++)  // получить первые три байта
                str[i]= buf[i]; // 
                str[3]='\0';
      if ((str[0]=='D')&&(str[1]=='A')&&(str[2]=='H')) {
//сигнатура правильная, датчик обнаружен
       for (byte i=3;i<7;i++)  // Получить четыре байта температуры
                str[i-3]= buf[i]; // упаковать их в строку
      int tmpr=atoi(str); //преобразовать в целое число
      tmpr=tmpr-2731; //вычесть 2731, получаем в десятых долях Цельсия
//здесь можно поделить на 10 и преобразовать во float, если надо
 Serial.println(tmpr); // здесь выводим температуру куда-то
// влажность:
      for (byte i=7;i<11;i++)  // Получить четыре байта влажности
                str[i-7]= buf[i]; // упаковать их в строку
      int hh = atoi(str); //преобразовать в целое число
      hh=(hh-1000)/10;
      if (hh>99) hh=99; //получаем влажность в %, целое число
Serial.println(hh); //выводим куда-то
   } //end проверка сигнатуры DAT
  } //end данные приняты
 } //прием 
}
