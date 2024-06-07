

int eixo_X= A0; //PINO REFERENTE A LIGAÇÃO DO EIXO X
int eixo_Y = A1; //PINO REFERENTE A LIGAÇÃO DO EIXO Y
int botao = 2; //PINO REFERENTE A LIGAÇÃO NO PINO KEY (EIXO Z)

void setup(){
  pinMode (botao, INPUT_PULLUP); //DEFINE A PORTA COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
  Serial.begin (9600); //INICIALIZA O MONITOR SERIAL
}
void loop(){
    switch(analogRead(eixo_X)){  // Lê o eixo x do analógico
      case(0):
      Serial.println("Cima");
      break;


      case(1023):
      Serial.println("Baixo");
      break;

    }

    switch(analogRead(eixo_Y)){  // Lê o eixo Y do analógico
      case(0):
      Serial.println("Esquerda");
      break;


      case(1023):                   // AVISA SE O CONTROLE ESTIVER PARA ESQUEDA OU DIREITA
      Serial.println("Direita");
      break;

    }
    if(digitalRead(botao) == LOW){            // AVISA QUANDO O BOTÃO FOR PRESSIONADO
      Serial.println("BOTAO PRESSIONADO"); 
    }


    delay(200); //INTERVALO DE 500 MILISSEGUNDOS
} 