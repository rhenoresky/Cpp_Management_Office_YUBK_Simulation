#include <iostream>
#include <string>

using namespace std;

class Item
{
private:
  string id;
  string name;
  int stock;

public:
  Item(string id, string name, int stock)
  {
    this->id = id;
    this->name = name;
    this->stock = stock;
  }

  string getId()
  {
    return id;
  }
  string getName()
  {
    return name;
  }
  int getStock()
  {
    return stock;
  }
  void setName()
  {
    this->name = name;
  }
  void setStock(int stock)
  {
    this->stock += stock;
  }
};
