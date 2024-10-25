#include <iostream>
#include <string>

using namespace std;

class User
{
private:
  string username;
  string password;
  string fullname;
  string role;

public:
  User(string username, string password, string fullname, string role)
  {
    this->username = username;
    this->password = password;
    this->fullname = fullname;
    this->role = role;
  }
  string getUsername()
  {
    return username;
  }
  string getPassword()
  {
    return password;
  }
  string getFullname()
  {
    return fullname;
  }
  string getRole()
  {
    return role;
  }

  void setPassword(string password)
  {
    this->password = password;
  }
  void setFullname(string fullname)
  {
    this->fullname = fullname;
  }
  void setRole(string role)
  {
    this->role = role;
  }
};
