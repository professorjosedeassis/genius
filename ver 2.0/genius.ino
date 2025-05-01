/**
   Jogo de memória (GENIUS)
   @author Professor José de Assis
   @version 2.0
   @link https://roboticapratica.com.br/
*/

/*
  Vetor usado para armazenar a sequência da rodada.
  "16" é o número máximo de rodadas (0 a 15).
  Você pode aumentar este valor para deixar o jogo
  mais difícil, neste caso alterar também a linha 82.
*/
int sequencia[16] = {};

/*
  Vetores uados para associar o botão com a cor do LED
  e nota musical correspondente:
  ------------------------------------------------
  | Índice | Botão     | LED              | Nota |
  ------------------------------------------------
  |  [0]   | botão 8   | led 2 (verde)    | DÓ   |
  ------------------------------------------------
  |  [1]   | botão 9   | led 3 (vermelho) | RÉ   |
  ------------------------------------------------
  |  [2]   | botão 10  | led 4 (azul)     | MI   |
  ------------------------------------------------
  |  [3]   | botão 11  | led 5 (amarelo)  | FÁ   |
  ------------------------------------------------
*/
int botoes[4] = {8, 9, 10, 11};
int leds[4] = {2, 3, 4, 5};
int tons[4] = {262, 294, 330, 349};

// variáveis usadas para determinar a dificuldade do jogo
int dificuldade1 = 1000; // tempo de espera da rodada
int dificuldade2 = 300; // velocidade de reprodução da sequência
int dificuldade3 = 200; // velocidade de reprodução da sequência

// variáveis usadas no apoio a lógica do jogo
int rodada = 0;
int passo = 0;
int botaoPressionado = 0;
bool gameOver = false;

void setup() {
  // Leds
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  // Buzzer
  pinMode(6, OUTPUT);
  // Botões
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  // referência a inicialização da função random()
  randomSeed(analogRead(A0));
}

void loop() {
  // validação GAME OVER
  if (gameOver == true) {
    efeito1();
  } else {
    // lógica principal
    proximaRodada();
    reproduzirSequencia();
    aguardarJogador();
    delay(dificuldade1);

    // aumentar a dificuldade à partir da 8ª rodada
    if (rodada > 7) {
      dificuldade1 = 500;
      dificuldade2 = 150;
      dificuldade3 = 100;
    }

    // vencedor (jogador chegou até a última rodada)
    if (rodada == 15) {
      efeito3();
      gameOver = true;
    }
  }
}

/* Função que sorteia a sequência da próxima rodada */
void proximaRodada() {
   RandomSeed(analogRead(A0));
  sequencia[rodada] = random(4);
  rodada = rodada + 1;
}

/* Função que reproduz a sequência da rodada */
void reproduzirSequencia() {
  for (int i = 0; i < rodada; i++) {
    tone(6, tons[sequencia[i]]);
    digitalWrite(leds[sequencia[i]], HIGH);
    delay(dificuldade2); 
    noTone(6);
    digitalWrite(leds[sequencia[i]], LOW);
    delay(dificuldade3); 
  }
}

/* Função que aguarda o jogador */
void aguardarJogador() {
  for (int i = 0; i < rodada; i++) {
    bool jogadaEfetuada = false;
    while (!jogadaEfetuada) {
      for (int i = 0; i <= 3; i++) {
        if (digitalRead(botoes[i]) == 0) {
          botaoPressionado = i;
          tone(6, tons[i]);
          digitalWrite(leds[i], HIGH);
          delay(300);
          digitalWrite(leds[i], LOW);
          noTone(6);
          jogadaEfetuada = true;
        }
      }
    }
    //verificar a jogada
    if (sequencia[passo] != botaoPressionado) {
      efeito2();
      gameOver = true;
      break;
    }
    passo = passo + 1;
  }
  passo = 0;
}

/***** Efeitos luminosos / sonoros *****/

/* Game over */
void efeito1() {
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(1000);
}

/* Errou a sequência */
void efeito2() {
  for (int i = 0; i <= 3; i++) {
    tone (6, 70);
    digitalWrite(leds[i], HIGH);
    delay(100);
    digitalWrite(leds[i], LOW);
    noTone(6);
  }
}

/* Campeão !!! */
void efeito3() {
  // melodia (notas musicais)
  int nota[] = {660, 660, 660, 510, 660, 770, 380, 510, 380, 320, 440, 480, 450, 430, 380, 660, 760, 860, 700, 760, 660, 520, 580, 480, 510, 380, 320, 440, 480, 450, 430, 380, 660, 760, 860, 700, 760, 660, 520, 580, 480, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 500, 760, 720, 680, 620, 650, 1020, 1020, 1020, 380, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 585, 550, 500, 380, 500, 500, 500, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 500, 760, 720, 680, 620, 650, 1020, 1020, 1020, 380, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 585, 550, 500, 380, 500, 500, 500, 500, 500, 500, 500, 580, 660, 500, 430, 380, 500, 500, 500, 500, 580, 660, 870, 760, 500, 500, 500, 500, 580, 660, 500, 430, 380, 660, 660, 660, 510, 660, 770, 380};
  // duraçao de cada nota da melodia
  int duracaoNota[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 80, 100, 100, 100, 80, 50, 100, 80, 50, 80, 80, 80, 80, 100, 100, 100, 100, 80, 100, 100, 100, 80, 50, 100, 80, 50, 80, 80, 80, 80, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 200, 80, 80, 80, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 200, 80, 80, 80, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 60, 80, 60, 80, 80, 80, 80, 80, 80, 60, 80, 60, 80, 80, 80, 80, 80, 60, 80, 60, 80, 80, 80, 80, 80, 80, 100, 100, 100, 100, 100, 100, 100};
  // pausa depois que cada nota da melodia é reproduzida
  int pausaNota[] = {150, 300, 300, 100, 300, 550, 575, 450, 400, 500, 300, 330, 150, 300, 200, 200, 150, 300, 150, 350, 300, 150, 150, 500, 450, 400, 500, 300, 330, 150, 300, 200, 200, 150, 300, 150, 350, 300, 150, 150, 500, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 220, 300, 100, 150, 150, 300, 300, 300, 150, 300, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 420, 450, 420, 360, 300, 300, 150, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 220, 300, 100, 150, 150, 300, 300, 300, 150, 300, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 420, 450, 420, 360, 300, 300, 150, 300, 150, 300, 350, 150, 350, 150, 300, 150, 600, 150, 300, 350, 150, 150, 550, 325, 600, 150, 300, 350, 150, 350, 150, 300, 150, 600, 150, 300, 300, 100, 300, 550, 575};
  for (int i = 0; i < 156; i++) {
    tone(6, nota[i], duracaoNota[i]);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(15);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(pausaNota[i]);
    noTone(6);
  }
}
