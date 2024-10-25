#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class ScheduleStudyService
{
private:
  vector<ScheduleStudy> schedules;
  HelperService helperService;
  UserService *userService;

public:
  ScheduleStudyService(HelperService helperService, UserService *userService)
  {
    this->helperService = helperService;
    this->userService = userService;
  }

  void addSchedule()
  {
    userService->showUsers("TRAINER");
    string usernameTrainer;
    cout << "Masukan username trainer: ";
    getline(cin >> ws, usernameTrainer);

    int selectedTrainer = userService->findUser(usernameTrainer);
    if (selectedTrainer < 0)
    {
      cout << "Trainer tidak ada!" << endl;
      return;
    }

    string id = helperService.generateRandomId();
    tm date = helperService.createStructTmTimeNow();
    string status = "NOT FINISHED";

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

    if (checkUserHaveSchedule(usernameTrainer, date.tm_mon, date.tm_mday, date.tm_hour))
    {
      cout << "User sudah memiliki jadwal di waktu tersebut" << endl;
      return;
    }

    string subject;
    cout << "Masukan mata pelajaran: ";
    getline(cin >> ws, subject);

    ScheduleStudy schedule(id, date, status, usernameTrainer, subject);
    schedules.push_back(schedule);
  }

  void editDateSchedule()
  {
    showScheduleStudys("NOT FINISHED");
    string idSchedule;
    cout << "Masukan ID Jadwal Study: ";
    getline(cin >> ws, idSchedule);

    int selectedSchedule = findScheduleStudy(idSchedule);
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

  void showScheduleStudys(string status)
  {
    int number = 1;
    for (ScheduleStudy schedule : schedules)
    {
      if (schedule.getStatus() == status)
      {
        tm structDate = schedule.getDate();
        time_t date = mktime(&structDate);
        cout << number << ".Id: " << schedule.getId() << "\tUsername Trainer: " << schedule.getUsernameTrainer() << "\tMata pelajaran: " << schedule.getSubject() << "\tWaktu: " << ctime(&date);
        number++;
      }
    }
  }

  void showAllScheduleStudys()
  {
    int number = 1;
    for (ScheduleStudy schedule : schedules)
    {
      tm structDate = schedule.getDate();
      time_t date = mktime(&structDate);
      cout << number << ".Id: " << schedule.getId() << "\tUsername Trainer: " << schedule.getUsernameTrainer() << "\tMata pelajaran: " << schedule.getSubject() << "\tWaktu: " << ctime(&date);
      number++;
    }
  }

  int findScheduleStudy(string id)
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

  void studyScheduleCompletion()
  {
    showScheduleStudys("NOT FINISHED");
    string idSchedule;
    cout << "Masukan ID Jadwal Belajar: ";
    getline(cin >> ws, idSchedule);

    int selectedSchedule = findScheduleStudy(idSchedule);
    if (selectedSchedule < 0)
    {
      cout << "Jadwal tidak ada!" << endl;
      return;
    }

    schedules[selectedSchedule].setStatus("FINISHED");
  }

  void deleteSchedule()
  {
    showAllScheduleStudys();
    showScheduleStudys("NOT FINISHED");
    string idSchedule;
    cout << "Masukan ID Jadwal Study: ";
    getline(cin >> ws, idSchedule);

    int selectedSchedule = findScheduleStudy(idSchedule);
    if (selectedSchedule < 0)
    {
      cout << "Jadwal tidak ada!" << endl;
      return;
    }

    schedules.erase(schedules.begin() + selectedSchedule);
  }

  bool checkUserHaveSchedule(string username, int month, int dayOfMonth, int hour)
  {
    for (ScheduleStudy schedule : schedules)
    {
      if (schedule.getUsernameTrainer() == username && schedule.getDate().tm_mon == month && schedule.getDate().tm_mday == dayOfMonth && schedule.getDate().tm_hour == hour)
      {
        return true;
      }
    }
    return false;
  }
};
