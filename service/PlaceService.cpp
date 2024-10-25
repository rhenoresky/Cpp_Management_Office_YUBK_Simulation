#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PlaceService
{
private:
  vector<Place> places;
  HelperService helperService;

public:
  PlaceService(HelperService helperService)
  {
    this->helperService = helperService;
  }

  void addPlaceItem()
  {
    string id = helperService.generateRandomId();
    string name;
    cout << "Masukan nama anda: ";
  }

  void addPlace()
  {
    string id = helperService.generateRandomId();
    string name;
    cout << "Masukan nama tempat: ";
    getline(cin >> ws, name);

    string location;
    cout << "Masukan detail lokasi: ";
    getline(cin >> ws, location);

    Place place(id, name, location);
    places.push_back(place);
  }

  void showPlaces()
  {
    int number = 1;
    for (Place place : places)
    {
      cout << number << ".Id: " << place.getId() << "\tNama: " << place.getName() << "\tLokasi: " << place.getLocation() << endl;
      number++;
    }
  }

  int findPlace(string id)
  {
    for (int i = 0; i < places.size(); i++)
    {
      if (places[i].getId() == id)
      {
        return i;
      }
    }

    return -1;
  }
  Place *getPlace(string id)
  {
    int selectedPlace = findPlace(id);
    return &places[selectedPlace];
  }
  void deletePlace()
  {
    showPlaces();
    string id;
    cout << "Masukan id: ";
    getline(cin >> ws, id);

    int selectedPlace = findPlace(id);
    if (selectedPlace < 0)
    {
      cout << "Operasi dibatalkan! Tempat tidak ada" << endl;
      return;
    }

    places.erase(places.begin() + selectedPlace);
  }
};
