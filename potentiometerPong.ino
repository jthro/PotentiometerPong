#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
bool ballMod;
int ballDirection;
int playerOnePos[2];
int playerTwoPos[2];
int ballPos[2];
int randModifier;
int playerOneScore = 0;
int playerTwoScore = 0;


void reset() {
  lcd.begin(16, 2);
  ballPos[0] = 7;
  ballPos[1] = 0;
  ballMod = false;
  ballDirection = 1;
  render();
}

void render() {
  if (ballPos[0] > 7){
    lcd.setCursor(ballPos[0] - 1, ballPos[1]);
  } else {
    lcd.setCursor(ballPos[0], ballPos[1]);
  }
  lcd.write('o');
  lcd.setCursor(1, playerOnePos[1]);
  lcd.write('|');
  lcd.setCursor(14, playerTwoPos[1]);
  lcd.write('|');
}

void setup() {
  // put your setup code here, to run once:  
  playerOnePos[0] = 1;
  playerOnePos[1] = 0;
  playerTwoPos[0] = 15;
  playerTwoPos[1] = 0;
  Serial.begin(9600);
  reset();
  lcd.setCursor(3, 1);
  lcd.print("1");
  lcd.setCursor(2, 1);
  lcd.print("P");
  lcd.setCursor(12, 1);
  lcd.print("2");
  lcd.setCursor(11, 1);
  lcd.print("P");
  lcd.setCursor(6, 0);
  lcd.print("p");
  lcd.setCursor(8, 0);
  lcd.print("n");
  lcd.setCursor(9, 0);
  lcd.print("g");
  delay(1500);
}

void displayScore() {
  Serial.print("Player one score: ");
  Serial.print("\t");
  Serial.print(playerOneScore);
  Serial.print("\t");
  Serial.print("Player two score: ");
  Serial.print("\t");
  Serial.print(playerTwoScore);
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (analogRead(1) < 511) {
    playerOnePos[1] = 0;
  } else {
    playerOnePos[1] = 1;
  }

  if (analogRead(2) < 511) {
    playerTwoPos[1] = 0;
  } else {
    playerTwoPos[1] = 1;
  }

  if ((playerOnePos[0] == ballPos[0] && playerOnePos[1] == ballPos[1]) || (playerTwoPos[0] == ballPos[0] && playerTwoPos[1] == ballPos[1])) {
    ballDirection = -ballDirection;
    randModifier = random(0, 4);
  }

  if (randModifier == 3) {
    if (ballPos[1] == 0) {
      ballPos[1] = 1;
    } else if(ballPos[1] == 1) {
      ballPos[1] = 0;
    }
    randModifier = 0;
  }

  if (ballPos[0] < 0) {
    displayScore();
    reset();
  } else if(ballPos[0] > 15) {
    playerOneScore +=1;
    displayScore();
    reset();
  }

  ballPos[0] += ballDirection;
  
  render();
  delay(42);
  lcd.clear();
}
