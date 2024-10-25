#include <iostream>
#include <string>

using namespace std;

class ScheduleInterview : public Schedule
{
private:
  string usernameHr;
  string usernameCandidateStudent;

public:
  ScheduleInterview(string id, tm date, string status, string usernameHr, string usernameCandidateStudent) : Schedule(id, date, status), usernameHr(usernameHr), usernameCandidateStudent(usernameCandidateStudent) {};
  string getUsernameHr()
  {
    return usernameHr;
  }
  string getUsernameCandidateStudent()
  {
    return usernameCandidateStudent;
  }
  void setUsernameHr(string usernameHr)
  {
    this->usernameHr = usernameHr;
  }
  void setUsernameCandidateStudent(string usernameCandidateStudent)
  {
    this->usernameCandidateStudent = usernameCandidateStudent;
  }
};
