#include <iostream>
#include <string>

using namespace std;

class ScheduleStudy : public Schedule
{
private:
  string usernameTrainer;
  string subject;

public:
  ScheduleStudy(string id, tm date, string status, string usernameTrainer, string subject) : Schedule(id, date, status), usernameTrainer(usernameTrainer), subject(subject) {}
  string getUsernameTrainer()
  {
    return usernameTrainer;
  }
  string getSubject()
  {
    return subject;
  }
};