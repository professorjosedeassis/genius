/**
   Arduino GENIUS
   @author Professor José de Assis
   https://www.youtube.com/playlist?list=PLbEOwbQR9lqzta3bQTkwDWtkne6I8LOBg
*/

/***************** variáveis globais *******************/

int sequencia[32] = {};
int botoes[4] = {8, 9, 10, 11};
int leds[4] = {2, 3, 4, 5};
int tons[4] = {262, 294, 330, 349};
int rodada = 0;
int passo = 0;
bool game_over = false;

void setup() {
  // Leds
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  // Buzzer
  pinMode(7, OUTPUT);
  // Botões
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
}

void loop() {
  proximaRodada();
  reproduzirSequencia();
  aguardarJogador();
  // estrutura usada para reiniciar todas as variáveis (novo jogo)
  if (game_over == true) {
    sequencia[32] = {};
    rodada = 0;
    passo = 0;
    game_over = false;
  }
  delay(1000);
}

/************************* Funções **************************/

void proximaRodada() {
  RandomSeed(analogRead(A0));
  randomSeed(analogRead(A0));
  int sorteio = random(4);
  sequencia[rodada] = sorteio;
  rodada = rodada + 1;
  //Serial.print(sorteio);
}

void reproduzirSequencia() {
  for (int i = 0; i < rodada; i++) {
    tone(7, tons[sequencia[i]]);
    digitalWrite(leds[sequencia[i]], HIGH);
    delay(500);
    noTone(7);
    digitalWrite(leds[sequencia[i]], LOW);
    delay(100);
  }
}

void aguardarJogador() {
  int botao_pressionado = 0;
  for (int i = 0; i < rodada; i++) {
    bool jogada_efetuada = false;
    while (!jogada_efetuada) {
      for (int i = 0; i <= 3; i++) {
        if (digitalRead(botoes[i]) == HIGH) {
          botao_pressionado = i;
          tone(7, tons[i]);
          digitalWrite(leds[i], HIGH);
          delay(300);
          digitalWrite(leds[i], LOW);
          noTone(7);
          jogada_efetuada = true;
        }
      }
    }
    //verificar a jogada
    if (sequencia[passo] != botao_pressionado) {
      //efeito luminoso/sonoro indicando que o jogador perdeu
      for (int i = 0; i <= 3; i++) {
        tone (7, 70);
        digitalWrite(leds[i], HIGH);
        delay(100);
        digitalWrite(leds[i], LOW);
        noTone(7);
      }
      game_over = true;
      break;
    }
    passo = passo + 1;
  }
  passo = 0;
}
