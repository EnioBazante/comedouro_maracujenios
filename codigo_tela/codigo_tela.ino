#include <Wire.h> // Comunicação com o I2C que é o barramento do display LCD
#include <LiquidCrystal_I2C.h> // Controle do display LCD 


// Configurações do display I2C (endereço, colunas, linhas)
LiquidCrystal_I2C lcd(0x27, 16, 2);








void setup() {
  lcd.init(); // inicia o LCD
  lcd.setBacklight(HIGH);
  lcd.backlight();
  //lcd.clear(); // limpa o display
  //lcd.print("    Tempo     |    Qtd Ração   ");

  Serial.begin(9600);

  lcd.print("hello, world!");


}







void loop() {


}



