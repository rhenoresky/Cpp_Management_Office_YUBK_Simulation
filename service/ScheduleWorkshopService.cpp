#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class ScheduleWorkshopService
{
private:
  vector<ScheduleWorkshop> schedules;
  HelperService helperService;
  UserService *userService;
  PlaceService *placeService;
  ItemService *itemService;
  ScheduleStudyService *scheduleStudyService;

public:
  ScheduleWorkshopService(HelperService helperService, UserService *userService, PlaceService *placeService, ItemService *itemService, ScheduleStudyService *scheduleStudyService)
  {
    this->helperService = helperService;
    this->userService = userService;
    this->placeService = placeService;
    this->itemService = itemService;
    this->scheduleStudyService = scheduleStudyService;
  }

  void addScheduleStudy()
  {
    string id = helperService.generateRandomId();
    tm date = helperService.createStructTmTimeNow();
    cout << "Masukan username MC: ";
  }
  void addSchedule()
  {
    string id = helperService.generateRandomId();
    tm date = helperService.createStructTmTimeNow();

    string usernameMc;
    userService->showUsers("TRAINER");
    cout << "Masukan username MC: ";
    getline(cin >> ws, usernameMc);
    int selectedUserMc = userService->findUser(usernameMc);
    if (selectedUserMc < 0)
    {
      cout << "Operasi dibatalkan! User tidak ada" << endl;
      return;
    }

    string usernameSpeaker;
    userService->showUsers("TRAINER");
    cout << "Masukan username pemateri: ";
    getline(cin >> ws, usernameSpeaker);
    int selectedUserSpeaker = userService->findUser(usernameSpeaker);
    if (selectedUserSpeaker < 0)
    {
      cout << "Operasi dibatalkan! User tidak ada" << endl;
      return;
    }

    int month;
    cout << "Masukan bulan dalam angka: ";
    cin >> month;

    int dayOfMonth;
    cout << "Masukan tanggal dalam angka: ";
    cin >> dayOfMonth;

    int hour;
    cout << "Masukan jam dalam format 24: ";
    cin >> hour;

    int minute;
    cout << "Masukan menit: ";
    cin >> minute;

    date.tm_mon = month - 1;
    date.tm_mday = dayOfMonth;
    date.tm_hour = hour;
    date.tm_min = minute;
    date.tm_sec = 0;

    if (checkUserHaveSchedule(usernameMc, date.tm_mon, date.tm_mday, date.tm_hour))
    {
      cout << "User sudah memiliki jadwal di waktu tersebut" << endl;
      return;
    }
    if (scheduleStudyService->checkUserHaveSchedule(usernameMc, date.tm_mon, date.tm_mday, date.tm_hour))
    {
      cout << "User sudah memiliki jadwal di waktu tersebut" << endl;
      return;
    }
    if (checkUserHaveSchedule(usernameSpeaker, date.tm_mon, date.tm_mday, date.tm_hour))
    {
      cout << "User sudah memiliki jadwal di waktu tersebut" << endl;
      return;
    }
    if (scheduleStudyService->checkUserHaveSchedule(usernameSpeaker, date.tm_mon, date.tm_mday, date.tm_hour))
    {
      cout << "User sudah memiliki jadwal di waktu tersebut" << endl;
      return;
    }

    string idPlace;
    placeService->showPlaces();
    cout << "Masukan id tempat workshop: ";
    getline(cin >> ws, idPlace);
    int selectedPlace = placeService->findPlace(idPlace);
    if (selectedPlace < 0)
    {
      cout << "Operasi dibatalkan! Tempat tidak ada" << endl;
      return;
    }

    string status = "NOT FINISHED";
    ScheduleWorkshop schedule(id, date, status, usernameMc, usernameSpeaker, idPlace);

    char confirm = 'N';
    while (confirm != 'Y')
    {
      itemService->showItems();
      string idItem;
      cout << "Masukan id item yang akan dipakai: ";
      getline(cin >> ws, idItem);
      int selectedItem = itemService->findItem(idItem);
      if (selectedItem < 0)
      {
        cout << "Operasi dibatalkan! Item tidak ada" << endl;
        return;
      }

      int amount;
      cout << "Masukan jumlah yang akan dipakai: ";
      cin >> amount;

      if (itemService->getItem(idItem)->getStock() < amount)
      {
        cout << "Stok tidak cukup silahkan perbarui stok terlebih dahulu" << endl;
        return;
      }

      int selectedItemInSchedule = schedule.findItem(idItem);
      if (selectedItemInSchedule >= 0)
      {
        schedule.getItem(idItem)->setStock(amount);
        itemService->getItem(idItem)->setStock(0 - amount);

        do
        {
          cout << "Apakah sudah selesai(Y/N)? ";
          cin >> confirm;
        } while (confirm != 'Y' && confirm != 'N');

        continue;
      }

      Item currentItem = *itemService->getItem(idItem);
      currentItem.setStock((0 - currentItem.getStock()) + amount);
      itemService->getItem(idItem)->setStock(0 - amount);
      schedule.pushItem(currentItem);

      do
      {
        cout << "Apakah sudah selesai(Y/N)? ";
        cin >> confirm;
      } while (confirm != 'Y' && confirm != 'N');
    }

    schedules.push_back(schedule);
  }

  void editDateSchedule()
  {
    showScheduleWorkshops("NOT FINISHED");
    string idSchedule;
    cout << "Masukan ID Jadwal Workshop: ";
    getline(cin >> ws, idSchedule);

    int selectedSchedule = findScheduleWorkshop(idSchedule);
    if (selectedSchedule < 0)
    {
      cout << "Jadwal tidak ada!" << endl;
      return;
    }

    tm date = schedules[selectedSchedule].getDate();
    int month;
    cout << "Masukan bulan dalam angka: ";
    cin >> month;

    int dayOfMonth;
    cout << "Masukan tanggal dalam angka: ";
    cin >> dayOfMonth;

    int hour;
    cout << "Masukan jam dalam format 24: ";
    cin >> hour;

    int minute;
    cout << "Masukan menit: ";
    cin >> minute;

    date.tm_mon = month - 1;
    date.tm_mday = dayOfMonth;
    date.tm_hour = hour;
    date.tm_min = minute;
    date.tm_sec = 0;

    schedules[selectedSchedule].setDate(date);
  }

  void showScheduleWorkshops(string status)
  {
    int number = 1;
    for (ScheduleWorkshop schedule : schedules)
    {
      if (schedule.getStatus() == status)
      {
        tm structDate = schedule.getDate();
        time_t date = mktime(&structDate);
        cout << number << ".Id: " << schedule.getId() << "\tUsername MC: " << schedule.getUsernameMC() << "\tUsername Pemateri: " << schedule.getUsernameSpeaker() << "\tWaktu: " << ctime(&date);
        number++;
      }
    }
  }

  void showAllScheduleWorkshops()
  {
    int number = 1;
    for (ScheduleWorkshop schedule : schedules)
    {
      tm structDate = schedule.getDate();
      time_t date = mktime(&structDate);
      cout << number << ".Id: " << schedule.getId() << "\tUsername MC: " << schedule.getUsernameMC() << "\tUsername Pemateri: " << schedule.getUsernameSpeaker() << "\tWaktu: " << ctime(&date);
      number++;
    }
  }

  int findScheduleWorkshop(string id)
  {
    for (int i = 0; i < schedules.size(); i++)
    {
      if (schedules[i].getId() == id)
      {
        return i;
      }
    }

    return -1;
  }

  void workshopScheduleCompletion()
  {
    showScheduleWorkshops("NOT FINISHED");
    string idSchedule;
    cout << "Masukan ID Jadwal Workshop: ";
    getline(cin >> ws, idSchedule);

    int selectedSchedule = findScheduleWorkshop(idSchedule);
    if (selectedSchedule < 0)
    {
      cout << "Jadwal tidak ada!" << endl;
      return;
    }

    char confirm = 'N';
    while (confirm != 'Y')
    {
      schedules[selectedSchedule].showItems();
      string idItem;
      cout << "Masukan id item yang tersisa: ";
      getline(cin >> ws, idItem);

      int amount;
      cout << "Masukan jumlah yang tersisa: ";
      cin >> amount;

      if (amount < 1)
      {
        cout << "Jumlah harus lebih dari 0" << endl;
        return;
      }

      if (schedules[selectedSchedule].getItem(idItem)->getStock() < amount)
      {
        cout << "Stok yang dikembalikan melebihi dari stok yang diambil" << endl;
        return;
      }

      itemService->getItem(idItem)->setStock(amount);
      schedules[selectedSchedule].getItem(idItem)->setStock(0 - amount);

      do
      {
        cout << "Apakah sudah selesai(Y/N)? ";
        cin >> confirm;
      } while (confirm != 'Y' && confirm != 'N');
    }

    schedules[selectedSchedule].setStatus("FINISHED");
  }

  void deleteSchedules()
  {
    showAllScheduleWorkshops();
    string idSchedule;
    cout << "Masukan ID Jadwal Workshop: ";
    getline(cin >> ws, idSchedule);

    int selectedSchedule = findScheduleWorkshop(idSchedule);
    if (selectedSchedule < 0)
    {
      cout << "Jadwal tidak ada!" << endl;
      return;
    }

    schedules.erase(schedules.begin() + selectedSchedule);
  }

  bool checkUserHaveSchedule(string username, int month, int dayOfMonth, int hour)
  {
    for (ScheduleWorkshop schedule : schedules)
    {
      if ((schedule.getUsernameMC() == username && schedule.getDate().tm_mon == month && schedule.getDate().tm_mday == dayOfMonth && schedule.getDate().tm_hour == hour) || (schedule.getUsernameSpeaker() == username && schedule.getDate().tm_mon == month && schedule.getDate().tm_mday == dayOfMonth && schedule.getDate().tm_hour == hour))
      {
        return true;
      }
    }
    return false;
  }
};
