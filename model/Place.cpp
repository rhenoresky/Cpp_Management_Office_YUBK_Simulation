#include <iostream>
#include <string>

using namespace std;

class Place
{
private:
  string id;
  string name;
  string location;

public:
  Place(string id, string name, string location)
  {
    this->id = id;
    this->name = name;
    this->location = location;
  }
  string getId()
  {
    return id;
  }
  string getName()
  {
    return name;
  }
  string getLocation()
  {
    return location;
  }
  void setName(string name)
  {
    this->name = name;
  }
  void setLocation(string location)
  {
    this->location = location;
  }
};
