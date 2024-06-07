  #include <Wire.h>               // Comunicação com o I2C que é o barramento do display LCD
  #include <LiquidCrystal_I2C.h>  // Controle do display LCD
  #include <Stepper.h> // Biblioteca do step motor
  #include "RTClib.h" //INCLUSÃO DA BIBLIOTECA


  DateTime now; //CHAMADA DE FUNÇÃO

  RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231


  int numHoras = 0;  // Número de horas a serem cadastradas
  int horas[24];      // Array para armazenar os horários
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




  // VER AQUI ////////
  const int pino = A0;         // Pino analógico para o eio  do joystick
  const int pinoY = A1;         // Pino analógico para o eio Y do joystick
  const int botao = 5;          // Pino digital para o botão do joystick

  int joyX = 0;                    // Sera usado na funcao joystick() para medir a sua altura
  int joyY = 0;                    // Sera usado na funcao joystick() para medir a sua altura


  int configuracoes;    // variável que controla o menu

  int horarioagora = 0;

  //int tempoRacao = 0;
  int i = 0; 
  int voltas = 5;


  int racaoNaHora(){
    for(int j = 0; j < 24; j++){

      if (horaAgora() == horas[j]){
        dispensarRacao();
        delay(60000);
      }

      
    }
    
  }

  int horaAgora () {
      now = rtc.now(); //CHAMADA DE FUNÇÃO

      byte hrs = (now.hour());
      byte min = (now.minute());

      horarioagora = ((hrs*100)+min);
      

      // Serial.print("hrs: ");
      // Serial.println(hrs);
      // Serial.print("min: ");
      // Serial.println(min);

    return horarioagora;
  }

  int joystick() {  // Função que retorna valor do joystick

    // Os returns são beaseados no numPad
    // 8  ==  CIMA
    // 4  ==  ESQUERDA
    // 2  ==  BAIO
    // 6  ==  DIREITA
    // ATENÇÃO == girar o botão muda o sentido disso



      joyX = analogRead(pino);

      if (joyX >= 1019 && joyY < 1019 && joyY > 10) {
        delay(150);
        return (8);
        
      } else if (joyX <= 10 && joyY < 1019 && joyY > 10) {
        delay(150);
        return (2);
        

      }
    


      joyY = analogRead(pinoY);

      if (joyY >= 1019 && joyX < 1019 && joyX > 10) {
        delay(150);
        return (4);

      } else if (joyY <= 10 && joyX < 1019 && joyX > 10){
        delay(150);
        return (6);

      }else{
        return (0);
        delay(200);
      }
    

  }

  int menuHoras(int h, int m, int i) {


    // Função feita apenas para mostrar a série de displays no menu durante o trocarHoras()
    // pega o índice do horas[] soma um e coloca como a ordem do horário

    // mostra "Qual o horário", depois a hora e os minutos separados por ":""
    
    lcd.setCursor(0, 0);
    lcd.print("Qual horario ");
    lcd.print(i+1);
    lcd.print("?");
    lcd.setCursor(0, 1);
    if (h < 10 || h == 88){
        switch(h){
          case(88):
            lcd.print("  ");
            delay(300);

          case(0):
            lcd.print("00");
            break;
          case(1):
            lcd.print("01");
            break;
          case(2):
            lcd.print("02");
            break;
          case(3):
            lcd.print("03");
            break;
          case(4):
            lcd.print("04");
            break;
          case(5):
            lcd.print("05");
            break;
          case(6):
            lcd.print("06");
            break;
          case(7):
            lcd.print("07");
            break;
          case(8):
            lcd.print("08");
            break;
          case(9):
            lcd.print("09");
            break;
        }
    }else{
      lcd.print(h);
    }


      lcd.setCursor(2, 1);
      lcd.print(":");
      lcd.setCursor(3, 1);

    if (m < 10 || m == 88){
        switch(m){
          case(88):
            lcd.print("  ");
            delay(300);

          case(0):
            lcd.print("00");
            break;
          case(1):
            lcd.print("01");
            break;
          case(2):
            lcd.print("02");
            break;
          case(3):
            lcd.print("03");
            break;
          case(4):
            lcd.print("04");
            break;
          case(5):
            lcd.print("05");
            break;
          case(6):
            lcd.print("06");
            break;
          case(7):
            lcd.print("07");
            break;
          case(8):
            lcd.print("08");
            break;
          case(9):
            lcd.print("09");
            break;
        }
    }else{
      lcd.print(m);
    }
  //tem uma malandragem aqui, existe um bug pra quando a opção muda da hora pros minutos
  // a gente colocou um valor quando isso ocorre, quando esse valor aparece nessa função
  // gera dois espaços vazios repetidamente, dando a impressão de piscar 

    
  // o bug em questão é resolvido aqui, onde aparecia 88 agora aparecem espaços vazios
    lcd.setCursor(5, 1);
    lcd.print("  ");      

    
  }



  int verHora(){
    int sovousuarahora = ((horaAgora()) - ((horaAgora())/100)*100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print((horaAgora() / 100));
    lcd.print(":");
    lcd.print(sovousuarahora);

    delay(3000);
    lcd.clear();
  }



  int menu(int config) {
    
    config = (config % 5);

    if (config != 4){
      lcd.backlight();
    }

    switch (config) {
      case 0: 
        lcd.setCursor(0, 0);
        lcd.print("[1]Dispensar Agr   ");
        if (digitalRead(botao) == 0){
        dispensarRacao();
        } 
        // colocar tempo de girar o motor suficiente pra cair uma boa quantidade de ração, vamo medir no olhometro msm
        break;
      case 1:
        lcd.setCursor(0, 0);
        lcd.print("[2]Definir Horas");
        if (digitalRead(botao) == 0){
          quantidadeDeHorarios();
        }
        break;
      case 2: 
        lcd.setCursor(0, 0);
        lcd.print("[3]Qtd Racao    ");
        delay(300);
        
        if (digitalRead(botao) == 0){
          delay(400);
          lcd.clear();
          while(true){
            lcd.setCursor(0, 1);
            lcd.print(15*voltas);
            lcd.print("g");          
            
            delay(600);
            if (joystick() == 4 && voltas != 0) {
              voltas -= 1;
            }
            if (joystick() == 6) {
              voltas += 1;
            }

            

            if (digitalRead(botao) == 0){
              lcd.clear();
              break;
            }
        }
        }
        break;

      case 3: 
        lcd.setCursor(0, 0);
        lcd.print("[4]Ver a Hora     ");
        if (digitalRead(botao) == 0){
          verHora();
        } 
        break;
      case 4:
        lcd.noBacklight();
        break;
      }  
  }

  int trocarHora(int ind) {   //(int ind, int horas[])
    delay(600);
    int opcao = 1;
    // int ind = 0;

  


    int hora = (horas[ind] / 100);
    int minuto = horas[ind] - ((horas[ind]/100)*100);

    menuHoras(hora, minuto, ind);

    // escreve o horário na tela


    
    while ((digitalRead(botao)) == 1){

      

      if (joystick() == 6){
        opcao = 1;
        menuHoras(88, minuto, ind);
        lcd.setCursor(0,1);
        lcd.print(hora);
        }
        
      if (joystick() == 4){
        opcao = 2;
        menuHoras(hora, 88, ind);
        lcd.setCursor(3,1);
        lcd.print(minuto);
        }


      switch (opcao){
      

      case(1):
        if (joystick() == 8){

          hora += 1;
          hora = hora % 24;
          menuHoras(hora, minuto, ind);
          break;

        }
        if (joystick() == 2 && hora != 0){
          
          hora -= 1;
          hora = hora % 24;
          menuHoras(hora, minuto, ind);
          break;
        }
    
      case(2):
        if (joystick() == 8){

          minuto += 1;
          minuto = minuto % 60;
          menuHoras(hora, minuto, ind);
          break;
        }
        if (joystick() == 2 && minuto != 0){	
          
          minuto -= 1;
          minuto = minuto % 60;
          menuHoras(hora, minuto, ind);
          break;
        }
      }
    }
    
    horas[ind] = ((hora*100) + minuto);
    lcd.clear();

    for(int j = 0; j != 23; j++){

      Serial.print(j);
      Serial.print(":");
      Serial.println(horas[j]);
      
    }
  }

  void dispensarRacao() {
    myStepper.step(voltas*2000);
    // setado como uma volta completa
    // 2000 = volta completa
  }

  int quantidadeDeHorarios() {
      int numHoras = 1;


      while (true) {
        lcd.setCursor(0, 0);
        lcd.print ("Quantas vezes?  ");
        lcd.setCursor(0, 1);
        lcd.print (numHoras);

                                // função contadora que serve como índice dos horários

      if (joystick() == 8 && numHoras < 23){

        numHoras += 1;
        lcd.clear();
      }
      if (joystick() == 2 && numHoras != 0){

        numHoras -= 1;
        lcd.clear();
      }
      delay(600);

      

      if ((digitalRead(botao)) == 0){
      
        while(i < numHoras){
          trocarHora(i);  
          i += 1;
          delay(200);
        }
      break;
      }
      
    }

  }


  void setup() {
    lcd.init();                    // inicia o LCD
    lcd.backlight();               // incia o backlight do lcd
    pinMode(botao, INPUT_PULLUP);  // Configura o pino do botão do joystick como entrada com pull-up
    Serial.begin(9600);
    myStepper.setSpeed(160);
    
    configuracoes = 1;
    if(! rtc.begin()) { // SE O RTC NÃO FOR INICIALIZADO, FAZ
      Serial.println("DS3231 não encontrado"); //IMPRIME O TEXTO NO MONITOR SERIAL
      while(1); //SEMPRE ENTRE NO LOOP
    }

      for(int j = 0; j != 23; j++){

      Serial.print(j);
      Serial.print(":");
      Serial.println(horas[j]);
      
    }
    



    //Atencao, o código abaixo ajusta o horário
    //So tire o comentario se for para ajustar o horario
    //A pilha precisa ser tirada e colocada do módulo

    //if(rtc.lostPower()){ //SE RTC FOI LIGADO PELA PRIMEIRA VEZ / FICOU SEM ENERGIA / ESGOTOU A BATERIA, FAZ
      
    // rtc.adjust(DateTime(F(_DATE), F(TIME_))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
    // rtc.adjust(DateTime(2024, 5, 31, 20, 27, 00)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
    //}

  }

  void loop() {

    racaoNaHora();
    // Serial.println(joystick());


    menu(configuracoes);
    if (joystick() == 2 && configuracoes != 0) {
        configuracoes -= 1;
      }
    if (joystick() == 8) {
        configuracoes += 1;
      }
    
    // for(int j = 0; j != 23; j++){

    //   Serial.print(j);
    //   Serial.print(":");
    //   Serial.println(horas[j]);
      
    // }

    

  }

