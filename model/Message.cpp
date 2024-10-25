#include <iostream>
#include <string>

using namespace std;

class Message
{
private:
  string id;
  string ownerUsername;
  string destinationUsername;
  string content;
  tm date;

public:
  Message(string id, string ownerUsername, string destinationUsername, string content, tm date)
  {
    this->id = id,
    this->ownerUsername = ownerUsername;
    this->destinationUsername = destinationUsername;
    this->content = content;
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
  string getDestinationUsername()
  {
    return destinationUsername;
  }
  string getContent()
  {
    return content;
  }
  tm getDate()
  {
    return date;
  }
};
