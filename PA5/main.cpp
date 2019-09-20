#include "Scheduler.cpp"

bool tick(int &idcount, Scheduler &schedule);


//FOR THE USER INPUT SYTLE MAIN
int main(void) {
  int processorsUser;
  cout << "Enter # processors: ";
  cin >> processorsUser;
  Scheduler schedule(processorsUser);

  int idcount = 1;
  bool inserted;
  do {
    inserted = tick(idcount, schedule);
    if(inserted == true) {
      cout << "Job ID Inserted: " << idcount - 1 << endl;
    } else {
      cout << "insertion failed or not done" << endl;
    }
  } while (/*!schedule.isjobsempty() || !schedule.isrunningempty()*/1);//now exits when user says exit as desc
//prompt
//insert
//decrement
//release
//find
}
bool tick(int &idcount, Scheduler &schedule) {//decidede to place tick as a function in maion instead
  string jobDes;
  int procs;
  int ticks;
  string addjob;
  bool inserted;
  do {
    cout << "Would you like to add a new job?(y/n): ";//prompts if user even wants to add a job during the tick
    cin >> addjob;
  } while (addjob != "y" && addjob != "n");
  inserted = false;
  if(addjob == "y") {
    cout << "Enter a description: ";
    cin >> jobDes;
    if(jobDes != "exit") {
      cout << "Enter a n-proc: ";
      cin >> procs;
      cout << "Enter a n-tick: ";
      cin >> ticks;
    }
    if(jobDes == "exit") {
      exit(0);
    }
    if(jobDes != "NULL" && addjob == "y") {
      inserted = schedule.InsertJob(idcount, jobDes, procs, ticks);
      if(inserted == true) {
        idcount++;
      }
    }
  }

  schedule.DecrementTimer();
  //find
  if(!schedule.isjobsempty()) {
    schedule.RunJob(schedule.FindShortest());//decides if shortest can be run and if so adds to running vector and deletes from priority queue
  }
  return inserted;
}
