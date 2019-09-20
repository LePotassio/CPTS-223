#include <string>
#include <iostream>
#include <map>
#include <cmath>

using namespace std;
//Not much to say about player class, very simple
class Player  {
public:
  Player(int ID, int x, int y);
  ~Player();

  int getX();
  int getY();
  int getID();

  void setX(int x);
  void setY(int y);
  void setID(int ID);
private:
  int xPos;
  int yPos;
  int playerId;
};

Player::Player(int ID, int x, int y) {
  playerId = ID;
  xPos = x;
  yPos = y;
}
Player::~Player() {

}


int Player::getX() {
  return xPos;
}
int Player::getY() {
  return yPos;
}


int Player::getID() {
  return playerId;
}


void Player::setX(int x) {
  xPos = x;
}
void Player::setY(int y) {
  yPos = y;
}

void Player::setID(int ID) {
  playerId = ID;
}
