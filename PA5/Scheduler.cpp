#include "Job.cpp"

using namespace std;
class myComparator//adapted from https://www.geeksforgeeks.org/implement-min-heap-using-stl/
{
public:
    int operator() (Job& a, Job& b)
    {
        return a.getticks() > b.getticks();
    }
};

class Scheduler {
public:
  Scheduler(int processors);
  ~Scheduler();

  bool InsertJob(int job_id, string job_des, int n_procs, int n_ticks);
  Job FindShortest();
  void DeleteShortest();
  bool CheckAvaliability(int procs);
  bool RunJob(Job runner);
  void DecrementTimer();
  void ReleaseProcs(Job runner);
  bool isjobsempty();
  bool isrunningempty();

private:
  //Priority Queue
  priority_queue<Job, vector<Job>, myComparator> jobs;
  int p;
  vector<Job> running;
};


Scheduler::Scheduler(int processors) {//user defined processor cap assigned when created
  p = processors;
}

Scheduler::~Scheduler() {

}


bool Scheduler::InsertJob(int job_id, string job_des, int n_procs, int n_ticks) {//inserts jobs into the pq
  if(n_procs > 0 && n_procs <= p && n_ticks > 0) {
    Job newJob(job_id, job_des, n_procs, n_ticks);
    jobs.push(newJob);
    cout << "Job added:" << job_id << "|Needed processors:" << n_procs << "|Needed ticks:"  << n_ticks << endl;
    return true;
  }
  if(n_ticks > 0) {
    cout << "n_ticks is below 0! not inserted" << endl;
  } else {
    cout << "not enough avaliable procssors! not inserted" << endl;
  }
  return false;
}

Job Scheduler::FindShortest() {
  return jobs.top();
}

void Scheduler::DeleteShortest() {
  jobs.pop();
}

bool Scheduler::CheckAvaliability(int procs) {//is the program going to esceed our avaliable proc number?
  if(procs <= p) {
    return true;
  }
  return false;
}

bool Scheduler::RunJob(Job runner) {//add to running vector and remove from pq
  if(this->CheckAvaliability(runner.getprocs()) && !jobs.empty()) {
    p -= runner.getprocs();
    running.push_back(runner);
    this->DeleteShortest();
    return true;
  }
  return false;
}

void Scheduler::DecrementTimer() {//every tick advances running jobs
  vector<Job>::iterator itr;
  if(!running.empty()) {
    itr = running.begin();
    //cout << itr->getdes() << endl;
  }
  while (!running.empty() && itr != running.end()) {
    itr->setticks(itr->getticks() - 1);
    //cout << "reached" << endl;
    if(itr->getticks() == 0) {
      cout << "Finished job:" << itr->getdes() << "|Needed processors:" << itr->getprocs() << "|No more needed ticks" << endl;
      ReleaseProcs(*itr);
      running.erase(itr);
      itr = running.begin();
    } else {
      itr++;
    }
  }
}

void Scheduler::ReleaseProcs(Job runner) {
  p += runner.getprocs();
}

bool Scheduler::isjobsempty() {
  return jobs.empty();
}


bool Scheduler::isrunningempty() {
  return running.empty();
}
