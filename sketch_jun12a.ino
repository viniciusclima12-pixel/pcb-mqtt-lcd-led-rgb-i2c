#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// MQTT
const char *BROKER = "broker.hivemq.com";
const int PORT = 1883;
const char *TOPIC = "forja/desenvolvimento/tarde";
int RED_PIN = 5;
int GREEN_PIN = 19;
int BLUE_PIN = 18;


WiFiManager wm;
WiFiClient espClient;
PubSubClient client(espClient);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("Mensagem recebida:");
  String leitura = "";
  for (int i = 0; i < length; i++)
  {
    leitura += (char)payload[i];
  }
  Serial.println(leitura);

  // Comece seu código aqui
  // { "command": "escrever", "value": "Teste"}
  String comand = leitura.substring(0, leitura.indexOf(","));
  String value = leitura.substring(0, leitura.indexOf(",") + 1);
  command.substring(value.indexOf(":") + 1);
  //{ "command": "escrever",
  // "valeu"; "Teste"
  if (leitura == "Ligar")
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    if (leitura == "Desligar")
    {
      digitalWrite(LED_BUILTIN, LOW);
    }else{
      if (leitura == "RESET")
      {
       
      
        wm.resetSettings();
        ESP.restart();
      }else{
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(leitura);
      }
      
    }
    
  }
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(21, 22);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.init();
  lcd.backlight();

  Serial.println("Conectando WiFi");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectando WiFi");
  bool connected = wm.autoConnect("Marco-Setup");
  if (!connected) {
    Serial.println("Falha ao conectar WiFi");
    ESP.restart();
  }
  Serial.println("WiFi conectado!");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi conectado!");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  client.setServer(BROKER, PORT);
  client.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected()) {
    while (!client.connected()) {
      Serial.println("Conectando MQTT...");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Conectando MQTT");
      String clientId = "ESP32-" + String(random(0xffff), HEX);
      if (client.connect(clientId.c_str())) {
        client.subscribe(TOPIC);
        Serial.println("Conectado ao MQTT");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Conectado!");
      } else {
        Serial.print("Conexão falhou: ");
        Serial.println(client.state());
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Conexão falhou:");
        lcd.setCursor(0, 1);
        lcd.print(client.state());
        delay(200);
      }
    }
  }
  client.loop();
}
