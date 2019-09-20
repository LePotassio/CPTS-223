#include "Player.cpp"


class Board {
public:
  Board(int m);
  ~Board();


  int getN();
  void setN(int newN);
  bool Insert(int ID, int x, int y);
  bool Find(int ID);


  void PrintByID();
  bool Remove(int ID);
  bool MoveTo(int ID, int xDes, int yDes);
private:

  int n;//player count
  int m;
  map<int, Player> board;
  //map<int, string> boardS;
};
Board::Board(int m) {
  this->m = m;
  n = 0;
}
Board::~Board() {

}

int Board::getN() {
  return n;
}
void Board::setN(int newN) {
  n = newN;
}

bool Board::Insert(int ID, int x, int y) {
  //id already taken
  if(this->Find(ID) == true) {
    cout << "Ayyy, player ID taken" << endl;
    return false;
  }
  //out of bounds
  if(x >= m || y >= m) {
    return false;
  }
  //position already occupied

  map<int, Player>::iterator itr;
  itr = board.begin();
  while(itr != board.end()) {
    if(itr->second.getX() == x && itr->second.getY() == y) {
      cout << "Ayyy, player space already occupied" << endl;
      return false;
    }
    itr++;
  }

  //can insert
  Player newP(ID, x, y);
  board.insert(pair<int, Player> (ID, newP));
  //string cord = tostring(x);
  //cord += ",";
  //cord.append(y);
  n++;
  return true;
}

bool Board::Find(int ID) {
  auto temp = board.find(ID);
  if (temp != board.end()) {
    return true;
  }
  return false;
  /*
  map<int, Person>:: itr;
  itr = board.begin();
  while(itr != board.end()) {
    if() {
      return 1;
    }
    itr++;
  }
  */
}

void Board::PrintByID() {
  map<int, Player>::iterator itr;
  itr = board.begin();
  while(itr != board.end()) {
    cout << "ID: " << itr->second.getID() << " (X,Y): " << itr->second.getX() << "," << itr->second.getY() << endl;
    itr++;
  }
  cout << "\n";
}

bool Board::Remove(int ID) {
  map<int, Player>::iterator itr;
  itr = board.begin();
  while(itr != board.end()) {
    if(itr->second.getID() == ID) {
      board.erase(ID);
      n--;
      return true;
    }
    itr++;
  }
  return false;
}

bool Board::MoveTo(int ID, int xDes, int yDes) {
  if(this->Find(ID) == 0) {
    return false;
  }
  if(xDes >= m || yDes >= m) {
    cout << "Ayyy, movement out of bounds" << endl;
    return false;
  }

  auto temp = board.find(ID);

  //CHECK MOVEMENT
  if((xDes == temp->second.getX() || yDes == temp->second.getY()) || abs(xDes - temp->second.getX()) == abs(yDes - temp->second.getY())) {

    map<int, Player>::iterator itr;
    itr = board.begin();
    while(itr != board.end()) {
      if(itr->second.getX() == xDes && itr->second.getY() == yDes) {
        cout << "Removing player: " << itr->second.getID() << endl;
        Remove(itr->second.getID());
        n--;
        break;
      }
      itr++;
    }

    this->Remove(ID);
    this->Insert(ID, xDes, yDes);
    return true;
  }
  cout << "Ayyy, invalid player movement" << endl;//Failed move check
  return false;
}
