#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ItemService
{
private:
  vector<Item> items;
  HelperService helperService;

public:
  ItemService(HelperService helperService)
  {
    this->helperService = helperService;
  }
  void addItem()
  {
    string id = helperService.generateRandomId();
    string name;
    cout << "Masukan nama barang: ";
    getline(cin >> ws, name);
    int stock;
    cout << "Tambah stok barang: ";
    cin >> stock;
    Item newItem(id, name, stock);
    items.push_back(newItem);
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
  void restockItem()
  {
    char confirm = 'N';
    while (confirm != 'Y')
    {
      showItems();
      string id;
      cout << "Masukan id: ";
      getline(cin >> ws, id);

      int selectedItem = findItem(id);
      if (selectedItem < 0)
      {
        cout << "Operasi dibatalkan! Item tidak ada" << endl;
        continue;
      }

      int stock;
      cout << "Masukan stok: ";
      cin >> stock;
      if (stock < 1)
      {
        cout << "Operasi dibatalkan! Stok harus lebih dari 0" << endl;
        continue;
      }
      items[selectedItem].setStock(stock);

      do
      {
        cout << "Apakah sudah selesai(Y/N)? ";
        cin >> confirm;
      } while (confirm != 'Y' && confirm != 'N');
    }
  }

  void deleteItem()
  {
    showItems();
    string id;
    cout << "Masukan id: ";
    getline(cin >> ws, id);

    int selectedItem = findItem(id);
    if (selectedItem < 0)
    {
      cout << "Operasi dibatalkan! Item tidak ada" << endl;
      return;
    }

    items.erase(items.begin() + selectedItem);
  }
};
