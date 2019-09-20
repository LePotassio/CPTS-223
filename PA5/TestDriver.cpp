#include "Scheduler.cpp"
//MAIN USED FOR TESTING FUNCTIONS BY TEXT INPUT FILE input.txt
int main(void) {
  ifstream infile;
  infile.open("input.txt");

  int processorsUser;
  cout << "Enter # processors: ";
  cin >> processorsUser;
  Scheduler schedule(processorsUser);

  string fileInput;
  string jobDes;
  int procs;
  string procsS;
  int ticks;
  string ticksS;

  int jobId = 1;
  int pos = 0;
  while(getline(infile, jobDes, ' ')) { //getLine(infile, fileInput, " ") || getLine(infile, fileInput, "\n")
    //jobDes = fileInput.substr(pos, fileInput.find(" "));
    getline(infile, procsS, ' ');
    getline(infile, ticksS, '\n');
    //cout << jobDes << " " << procsS << " " << ticksS << endl;
    procs = stoi(procsS);
    ticks = stoi(ticksS);
    //cout << jobDes << " " << procs << " " << ticks << endl;
    if(jobDes != "NULL") {
      schedule.InsertJob(jobId, jobDes, procs, ticks);
      jobId++;
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////
  //while schedule is not empty and running is not empty
  while(!schedule.isjobsempty() || !schedule.isrunningempty()) {
    schedule.RunJob(schedule.FindShortest());
    schedule.DecrementTimer();
  }

  infile.close();
  return 0;
}
