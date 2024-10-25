#include <iostream>
#include <string>

using namespace std;

class Attendance
{
private:
  string id;
  string ownerUsername;
  tm date;

public:
  Attendance(string id, string ownerUsername, tm date)
  {
    this->id = id;
    this->ownerUsername = ownerUsername;
    this->date = date;
  }

  string getId()
  {
    return id;
  }
  string getOwnerUsername()
  {
    return ownerUsername;
  }
  tm getDate()
  {
    return date;
  }
};
