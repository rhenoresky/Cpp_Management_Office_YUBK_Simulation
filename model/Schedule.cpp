#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Schedule
{
protected:
  string id;
  tm date;
  string status;

public:
  Schedule(string id, tm date, string status)
  {
    this->id = id;
    this->date = date;
    this->status = status;
  }
  string getId()
  {
    return id;
  }
  tm getDate()
  {
    return date;
  }
  string getStatus()
  {
    return status;
  }
  void setDate(tm date)
  {
    this->date = date;
  }
  void setStatus(string status)
  {
    this->status = status;
  }
};
