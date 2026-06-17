int LED_PIN[] = {3, 5, 6};

void setup()
{
  Serial.begin(9600);

  for(int i = 0; i < 3; i++){
    pinMode(LED_PIN[i], OUTPUT);
  }
}

void loop()
{
  if(Serial.available())
  {
    String color = Serial.readString();
    color.trim();

    // desliga tudo
    analogWrite(LED_PIN[0], 255);
    analogWrite(LED_PIN[1], 255);
    analogWrite(LED_PIN[2], 255);

    // vermelho
    if(color == "Vermelho")
    {
      analogWrite(LED_PIN[0], 0);
      analogWrite(LED_PIN[1], 255);
      analogWrite(LED_PIN[2], 255);
    }

    // verde
    if(color == "Verde")
    {
      analogWrite(LED_PIN[0], 255);
      analogWrite(LED_PIN[1], 0);
      analogWrite(LED_PIN[2], 255);
    }

    // azul
    if(color == "Azul")
    {
      analogWrite(LED_PIN[0], 255);
      analogWrite(LED_PIN[1], 255);
      analogWrite(LED_PIN[2], 0);
    }

    // amarelo
    if(color == "Amarelo")
    {
      analogWrite(LED_PIN[0], 0);
      analogWrite(LED_PIN[1], 0);
      analogWrite(LED_PIN[2], 255);
    }

    // roxo
    if(color == "Roxo")
    {
      analogWrite(LED_PIN[0], 0);
      analogWrite(LED_PIN[1], 255);
      analogWrite(LED_PIN[2], 0);
    }

    // ciano
    if(color == "Ciano")
    {
      analogWrite(LED_PIN[0], 255);
      analogWrite(LED_PIN[1], 0);
      analogWrite(LED_PIN[2], 0);
    }

    // verde claro
    if(color == "Verde claro")
    {
      analogWrite(LED_PIN[0], 255 - 165);
      analogWrite(LED_PIN[1], 255 - 255);
      analogWrite(LED_PIN[2], 255 - 97);
    }
    // verde claro
    if(color == "Vomito")
    {
      analogWrite(LED_PIN[0], 255 - 139);
      analogWrite(LED_PIN[1], 255 - 200);
      analogWrite(LED_PIN[2], 255 - 82);
    }
  }

  delay(100);
}
