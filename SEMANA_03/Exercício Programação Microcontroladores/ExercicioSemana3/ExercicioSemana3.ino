#define LED 10
#define LED2 9
#define LED3 18
#define LED4 7
#define BUZZER 2
#define LDR 4
#define BUTTON1 45
#define BUTTON2 37

int normalizedValue;
int fullNumbersCounter = 0;
int binaryArray[4] = {0, 0, 0, 0};
int fullNumbers[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
}

void tom(char buzzer, int frequencia, int duracao){
  float periodo = 1000.0/frequencia;
  for (int i = 0; i< duracao/(periodo); i++){
    digitalWrite(buzzer, HIGH);
    delayMicroseconds(periodo*500);
    digitalWrite(buzzer, LOW);
    delayMicroseconds(periodo*500);
  }
}

int normalize(int actualValue)
{
  int newValue = (actualValue * 15) / 2670;

  return newValue;  
}

void convertToBinary(int decimal)
{
  for(int i=0; decimal>0; i++)    
  {    
    binaryArray[i] = decimal%2;    
    decimal = decimal/2;
  }
}

void makeSound(int value)
{
  switch(value)
  {
    case 0:
      tom(BUZZER, 500, 500);
      break;
    case 1:
      tom(BUZZER, 750, 500);
      break;
    case 2:
      tom(BUZZER, 1000, 500);
      break;
    case 3:
      tom(BUZZER, 1250, 500);
      break;
    case 4:
      tom(BUZZER, 1500, 500);
      break;
    case 5:
      tom(BUZZER, 1750, 500);
      break;
    case 6:
      tom(BUZZER, 2000, 500);
      break;
    case 7:
      tom(BUZZER, 2250, 500);
      break;
    case 8:
      tom(BUZZER, 2500, 500);
      break;
    case 9:
      tom(BUZZER, 2750, 500);
      break;
    case 10:
      tom(BUZZER, 3000, 500);
      break;
    case 11:
      tom(BUZZER, 3250, 500);
      break;
    case 12:
      tom(BUZZER, 3500, 500);
      break;
    case 13:
      tom(BUZZER, 3750, 500);
      break;
    case 14:
      tom(BUZZER, 4000, 500);
      break;
    case 15:
      tom(BUZZER, 4250, 500);
      break;
  }
}

void turnUpLeds()
{
  digitalWrite(LED, binaryArray[3]);
  digitalWrite(LED2, binaryArray[2]);
  digitalWrite(LED3, binaryArray[1]);
  digitalWrite(LED4, binaryArray[0]);
  
  delay(200);

  digitalWrite(LED, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  binaryArray[0] = 0;
  binaryArray[1] = 0;
  binaryArray[2] = 0;
  binaryArray[3] = 0;
}

void loop() {
  int button1Input = digitalRead(BUTTON1);
  int button2Input = digitalRead(BUTTON2);

  if (button1Input == 0)
  {
    if (fullNumbersCounter < 10)
    {
      Serial.println("leu");
      int ldrValue = analogRead(LDR);
      normalizedValue = normalize(ldrValue);

      fullNumbers[fullNumbersCounter] = normalizedValue;

      fullNumbersCounter += 1;

      convertToBinary(normalizedValue);

      makeSound(normalizedValue);

      turnUpLeds();
    }
    else
    {
      tom(BUZZER, 5000, 500);
      delay(250);
      tom(BUZZER, 5000, 500);
      delay(250);
      tom(BUZZER, 5000, 500);
    }
  }

  if (button2Input == 0)
  {
    Serial.println("tocou");
    rodar();
  }
}

void rodar()
{
  for (int i = 0; i < sizeof(fullNumbers)/4; i ++)
  {
    makeSound(fullNumbers[i]);
    convertToBinary(fullNumbers[i]);
    turnUpLeds();
  }

  fullNumbersCounter = 0;
}