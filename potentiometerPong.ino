#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
bool ballMod;
int ballDirection;
int playerOnePos[2];
int playerTwoPos[2];
int ballPos[2];
int randModifier;


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  playerOnePos[0] = 1;
  playerOnePos[1] = 0;
  playerTwoPos[0] = 15;
  playerTwoPos[1] = 0;
  ballPos[0] = 7;
  ballPos[1] = 0;
  ballMod = false;
  ballDirection = 1;

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
    if (randModifier == 0) {
      ballMod = true;
    }
  }

  if (ballPos[0] < 0 || ballPos[0] > 15) {
    setup();
  }

  ballPos[0] += ballDirection;

  if (ballPos[0] == 7 && ballMod == true) {
    if (ballPos[1] == 0) {
      ballPos[1] = 1;
    } else {
      ballPos[1] == 0;
    }
    ballMod = false;
  }
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

  delay(42);
  lcd.clear();
  randModifier = random(0, 2);
}
