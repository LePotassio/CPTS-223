#include "VectorMyJosephus.cpp"

string determineTime(auto start, auto end);
string determineTimeBasic(auto start, auto end);
string determineTimeAvg(double avg);
int main(void) {

  int N = 512;
  int M = 64;

  int lastPos = 0;
  VectorMyJosephus *game = new VectorMyJosephus(N, M);
  //game->eliminateNext();
  auto startGame = chrono::steady_clock::now();
  game->printAll();
  std::cout << "\n" << std::endl;

  auto startElimTotal = chrono::steady_clock::now();
  while(game->getSize() > 1) {
    lastPos = game->eliminateNext(lastPos);
    game->printAll();
    std::cout << "\n" << std::endl;
  }
  auto endElimTotal = chrono::steady_clock::now();

  cout << game->getElimSeq();
  cout<< "Winner: " << game->getCircle().begin()->getPosition() << endl;
  auto endGame = chrono::steady_clock::now();

  string totalGameTime = determineTime(startGame, endGame);
  cout << "Total Game Runtime: " << totalGameTime << endl;

  double avg = stoi(determineTimeBasic(startElimTotal, endElimTotal)) / (N - 1);
  cout << "Avg Elim Time: " << determineTimeAvg(avg) << endl;
}


string determineTime(auto start, auto end) {
  ostringstream convert;
  if(chrono::duration_cast<chrono::seconds>(end - start).count() != 0) {
      convert << chrono::duration_cast<chrono::seconds>(end - start).count();
      string convertS = convert.str();
    return convertS + " seconds";
  }
  if(chrono::duration_cast<chrono::milliseconds>(end - start).count() != 0) {
    //cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
    convert << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    string convertS = convert.str();
  return convertS + " milliseconds";
  }
  if(chrono::duration_cast<chrono::microseconds>(end - start).count() != 0) {
    convert << chrono::duration_cast<chrono::microseconds>(end - start).count();
    string convertS = convert.str();
    return convertS + " microseconds";
  }
  convert << chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  string convertS = convert.str();
  return convertS + " nanoseconds";
}

string determineTimeBasic(auto start, auto end) {
  ostringstream convert;
  convert << chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  string convertS = convert.str();
  return convertS;
}

string determineTimeAvg(double avg) {
  if(avg / 1000000000 != 0) {
    avg = avg / 1000000000;
    return to_string(avg) + " seconds";
  }
  if(avg / 1000000 != 0) {
    avg = avg / 1000000;
    return to_string(avg) + " milliseconds";
  }
  if(avg / 1000 != 0) {
    avg = avg / 1000;
    return to_string(avg) + " microseconds";
  }
  return to_string(avg) + " nanoseconds";
}
