#include <iostream>
#include <string>
#include <queue>
#include <fstream>

using namespace std;
//Job class is very simple, contains data member for id, description, processors needed and ticks needed and their getters and setters, aslo a comparison overload
class Job {
public:

  Job(int newid, string newdes, int newprocs, int newticks);
  ~Job();

  int getid();
  string getdes();
  int getprocs();
  int getticks();

  void setid(int newid);
  void setdes(string newdes);
  void setprocs(int newprocs);
  void setticks(int newticks);

  friend bool operator <(const Job lhs, const Job rhs);

private:
  int job_id;
  string job_des;
  int n_procs;
  int n_ticks;
};

Job::Job(int newid, string newdes, int newprocs, int newticks) {
  job_id = newid;
  job_des = newdes;
  n_procs = newprocs;
  n_ticks = newticks;
}
Job::~Job() {

}

int Job::getid() {
  return job_id;
}
string Job::getdes() {
  return job_des;
}
int Job::getprocs() {
  return n_procs;
}
int Job::getticks() {
  return n_ticks;
}

void Job::setid(int newid) {
  job_id = newid;
}
void Job::setdes(string newdes) {
  job_des = newdes;
}
void Job::setprocs(int newprocs) {
  n_procs = newprocs;
}
void Job::setticks(int newticks) {
  n_ticks = newticks;
}

bool operator< (const Job lhs, const Job rhs) {//used to make jobs comparable
  if(lhs.n_ticks < rhs.n_ticks) {
    return true;
  }
  return false;
}
