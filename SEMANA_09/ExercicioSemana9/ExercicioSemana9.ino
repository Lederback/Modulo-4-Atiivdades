#include <LiquidCrystal_I2C.h>

const int I2C_SDA = 2;
const int I2C_SCL = 1;

int ldcColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, ldcColumns, lcdRows);

int option;
String senha;
String login;
bool logado = false;
bool cadastrada = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(RGB_BUILTIN, OUTPUT);

  Wire.begin(I2C_SDA, I2C_SCL);

  lcd.init();
  lcd.backlight();
}

void loop() {
  if (!logado)
  {
    if (!cadastrada)
    {
      Serial.print("Cadastre a senha\n");

      while(Serial.available() == 0){}
      senha = Serial.readString();
    }

    if (senha.length() == 5){
      if (!cadastrada){
        Serial.print("Tamanho válido!\n");
        cadastrada = true;
      }

      Serial.print("Informe a senha\n");

      while(Serial.available() == 0){}

      login = Serial.readString();

      if (senha == login)
      {
        Serial.print("Senha correta!\n");

        lcd.setCursor(0, 0);
        lcd.print("Senha correta");

        neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0);

        delay(1000);

        lcd.clear();

        digitalWrite(RGB_BUILTIN, LOW);
        logado = true;
      }
      else {
        Serial.print("Senha incorreta!\n");

        lcd.setCursor(0, 0);
        lcd.print("Senha incorreta");

        neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0);

        delay(1000);

        lcd.clear();

        digitalWrite(RGB_BUILTIN, LOW);
      }
    }
    else {
      Serial.print("Tamanho inválido!\n");
    }
  }
}
