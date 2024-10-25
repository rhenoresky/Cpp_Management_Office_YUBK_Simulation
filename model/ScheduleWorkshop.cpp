#include <iostream>
#include <string>

using namespace std;

class ScheduleWorkshop : public Schedule
{
private:
  vector<Item> items;
  string usernameMC;
  string usernameSpeaker;
  string idPlace;

public:
  ScheduleWorkshop(string id, tm date, string status, string usernameMC, string usernameSpeaker, string idPlace) : Schedule(id, date, status), usernameMC(usernameMC), usernameSpeaker(usernameSpeaker), idPlace(idPlace) {}
  vector<Item> *getItems()
  {
    return &items;
  }
  string getUsernameMC()
  {
    return usernameMC;
  }
  string getUsernameSpeaker()
  {
    return usernameSpeaker;
  }
  string getIdPlace()
  {
    return idPlace;
  }
  void setIdPlace(string idPlace)
  {
    this->idPlace = idPlace;
  }
  void showItems()
  {
    int number = 1;
    for (Item item : items)
    {
      cout << number << ".Id: " << item.getId() << "\tNama: " << item.getName() << "\tStok: " << item.getStock() << endl;
      number++;
    }
  }
  int findItem(string id)
  {
    for (int i = 0; i < items.size(); i++)
    {
      if (items[i].getId() == id)
      {
        return i;
      }
    }

    return -1;
  }
  Item *getItem(string id)
  {
    int selectedItem = findItem(id);
    return &items[selectedItem];
  }
  void pushItem(Item item)
  {
    this->items.push_back(item);
  }
};
