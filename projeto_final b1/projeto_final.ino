#include <Wire.h>               // Comunicação com o I2C que é o barramento do display LCD
#include <LiquidCrystal_I2C.h>  // Controle do display LCD
#include <Stepper.h> // Biblioteca do step motor
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA




RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231


int numHoras = 0;  // Número de horas a serem cadastradas
//int horas[24];      // Array para armazenar os horários
int horaAGR = 0;





// Variáveis do step motor
const int stepsPerRevolution = 200;
#define in1 11
#define in2 10
#define in3 9
#define in4 8

// Configurações do step motor (passo, pino1, pino2, pino3, pino4)
Stepper myStepper (stepsPerRevolution, in4, in2, in3, in1);








LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configurações do display I2C (endereço, colunas, linhas)





const int pino = A0;         // Pino analógico para o eio  do joystick
const int pinoY = A1;         // Pino analógico para o eio Y do joystick
const int botao = 5;          // Pino digital para o botão do joystick

int joyX = 0;                    // Sera usado na funcao joystick() para medir a sua altura
int joyY = 0;                    // Sera usado na funcao joystick() para medir a sua altura


int configuracoes = 0;    // variável que controla o menu

int horarioagora = 0;


int horaAgora () {
    DateTime now = rtc.now(); //CHAMADA DE FUNÇÃO

    byte hrs = (now.hour());
    byte min = (now.minute());

    int teste = ((hrs*100) + min);

    Serial.println(teste);
    


  return (teste);
}


int joystick() {  // Função que retorna valor do joystick

  // Os returns são beaseados no numPad
  // 8  ==  CIMA
  // 4  ==  ESQUERDA
  // 2  ==  BAIO
  // 6  ==  DIREITA
  // ATENÇÃO == girar o botão muda o sentido disso



    joyX = analogRead(pino);

    if (joyX >= 1019) {
      
      return (8);
      
      delay(200);
    } else if (joyX <= 10){
      return (2);
      delay(200);

    }
  


    joyY = analogRead(pinoY);

    if (joyY >= 1000) {
      return (4);

    } else if (joyY <= 10){
      return (6);

    }else{
      return (0);
    }
  

}

int menuHoras(int h, int m, int i) {
  lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Qual horario ");
	lcd.print(i+1);
	lcd.print("?");
	lcd.setCursor(0, 1);
	lcd.print(h);
	lcd.setCursor(2, 1);
	lcd.print(":");
	lcd.setCursor(3, 1);
	lcd.print(m);
}

int menu(int config) {
  config = (config% 5);
  switch (config) {
    
    case 0:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("[1]Dispensar Agora");
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("[2]Horas");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("[3]Definir Horas");
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("[4]Qtd Racao");
      break;
    case 4:
      lcd.noBacklight();
      break;
  }
}

int trocarHora(int ind, int horas[]) {

  int opcao = 0;

  // horas[ind] -> 1743


  int hora = (horas[ind] / 100);
  int minuto = horas[ind] - ((horas[ind]/100)*100);

  menuHoras(hora, minuto, ind);

  // escreve o horário na tela



  while ((digitalRead(botao)) == 1){

    

  	if (joystick() == 4){
  		opcao = 1;

  		}
  	if (joystick() == 6){
  		opcao = 2;

  		}
  	switch (opcao){
    
  	case(1):
  		if (joystick() == 8 && hora < 24){
  			hora += 1;
  			menuHoras(hora, minuto, ind);
        delay(200);
        break;

  		}
  		if (joystick() == 2 && hora != 0){
  			hora -= 1;
  			menuHoras(hora, minuto, ind);
        delay(200);
        break;
  		}
  
  	case(2):
  		if (joystick() == 8 && minuto < 59){
  			minuto += 1;
  			menuHoras(hora, minuto, ind);
        delay(200);
        break;
  		}
  		if (joystick() == 2 && minuto != 0){
  			minuto -= 1;
  			menuHoras(hora, minuto, ind);
        delay(200);
        break;
  		}

  	}

  }




  horas[ind] = ((hora*100) + minuto);
  //return 
}

void dispensarRacao() {
  myStepper.step(2000);
  // setado como uma volta completa
  // 2000 = volta completa
}

int quantidadeDeHorarios() {
     while (digitalRead(botao) == 1) {

     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print ("Quantas horas?");
     lcd.setCursor(0, 1);
     lcd.print (numHoras);

     if (joystick() == 8 && numHoras < 23){
       numHoras += 1;
       lcd.clear();

     }
     if (joystick() == 2 && numHoras != 0){
       numHoras -= 1;
       lcd.clear();

     }


     if ((digitalRead(botao)) == 0){

       return (numHoras);
       break;

     }
     delay(500);
  }
}






void setup() {
  lcd.init();                    // inicia o LCD
  lcd.backlight();               // incia o backlight do lcd
  pinMode(botao, INPUT_PULLUP);  // Configura o pino do botão do joystick como entrada com pull-up
  Serial.begin(9600);
  myStepper.setSpeed(160);
  
  //quantidadeDeHorarios();

  //Atencao, o código abaixo ajusta o horário
  //So tire o comentario se for para ajustar o horario
  //A pilha precisa ser tirada e colocada do módulo

  //if(rtc.lostPower()){ //SE RTC FOI LIGADO PELA PRIMEIRA VEZ / FICOU SEM ENERGIA / ESGOTOU A BATERIA, FAZ
    
   // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
   // rtc.adjust(DateTime(2024, 5, 31, 20, 27, 00)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
   //}

}

void loop() {
  Serial.println(horaAgora());


}


  // nowDT = rtc.now();
  // byte myHrs = nowDT.hour();
  // byte myMin = nowDT.minute();
  // byte mySec = nowDT.second();

  // teste = (myHrs*100) + myMin;
  // Serial.println(teste);