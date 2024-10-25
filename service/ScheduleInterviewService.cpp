#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class ScheduleInterviewService
{
private:
  vector<ScheduleInterview> schedules;
  HelperService helperService;
  UserService *userService;

public:
  ScheduleInterviewService(HelperService helperService, UserService *userService)
  {
    this->helperService = helperService;
    this->userService = userService;
  }
  void addSchedule()
  {
    string id = helperService.generateRandomId();
    tm date = helperService.createStructTmTimeNow();

    string usernameHr;
    userService->showUsers("HR");
    cout << "Masukan username HR: ";
    getline(cin >> ws, usernameHr);
    int selectedHr = userService->findUser(usernameHr);
    if (selectedHr < 0)
    {
      cout << "Operasi dibatalkan! User tidak ada" << endl;
      return;
    }

    string usernameStudentCandidate;
    userService->showUsers("STUDENT CANDIDATE");
    cout << "Masukan username calon peserta: ";
    getline(cin >> ws, usernameStudentCandidate);
    int selectedStudentCandidate = userService->findUser(usernameStudentCandidate);
    if (selectedStudentCandidate < 0)
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
    cout << "Masukan jam dalam format 24jam: ";
    cin >> hour;

    int minute;
    cout << "Masukan menit: ";
    cin >> minute;

    date.tm_mon = month - 1;
    date.tm_mday = dayOfMonth;
    date.tm_hour = hour;
    date.tm_min = minute;
    date.tm_sec = 0;

    if (checkUserHaveSchedule(usernameHr, date.tm_mon, date.tm_mday, date.tm_hour))
    {
      cout << "User sudah memiliki jadwal di waktu tersebut" << endl;
      return;
    }
    if (checkUserHaveSchedule(usernameStudentCandidate, date.tm_mon, date.tm_mday, date.tm_hour))
    {
      cout << "User sudah memiliki jadwal di waktu tersebut" << endl;
      return;
    }

    string status = "NOT FINISHED";
    ScheduleInterview schedule(id, date, status, usernameHr, usernameStudentCandidate);
    schedules.push_back(schedule);
  }

  void editDateSchedule()
  {
    showScheduleInterviews("NOT FINISHED");
    string idSchedule;
    cout << "Masukan ID Jadwal Interview: ";
    getline(cin >> ws, idSchedule);

    int selectedSchedule = findScheduleInterview(idSchedule);
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

  void showScheduleInterviews(string status)
  {
    int number = 1;
    for (ScheduleInterview schedule : schedules)
    {
      if (schedule.getStatus() == status)
      {
        tm structDate = schedule.getDate();
        time_t date = mktime(&structDate);
        cout << number << ".Id: " << schedule.getId() << "\tUsername HR: " << schedule.getUsernameHr() << "\tUsername calon peserta: " << schedule.getUsernameCandidateStudent() << "\tWaktu: " << ctime(&date);
        number++;
      }
    }
  }

  void showScheduleInterviewsForStudentCandidate(string status, string username)
  {
    int number = 1;
    for (ScheduleInterview schedule : schedules)
    {
      if (schedule.getStatus() == status && schedule.getUsernameCandidateStudent() == username)
      {
        tm structDate = schedule.getDate();
        time_t date = mktime(&structDate);
        cout << number << ".Id: " << schedule.getId() << "\tUsername HR: " << schedule.getUsernameHr() << "\tUsername calon peserta: " << schedule.getUsernameCandidateStudent() << "\tWaktu: " << ctime(&date);
        number++;
      }
    }
  }

  void showAllScheduleInterviews()
  {
    int number = 1;
    for (ScheduleInterview schedule : schedules)
    {
      tm structDate = schedule.getDate();
      time_t date = mktime(&structDate);
      cout << number << ".Id: " << schedule.getId() << "\tUsername HR: " << schedule.getUsernameHr() << "\tUsername calon peserta: " << schedule.getUsernameCandidateStudent() << "\tWaktu: " << ctime(&date);
      number++;
    }
  }

  int findScheduleInterview(string id)
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

  void interviewScheduleCompletion()
  {
    showScheduleInterviews("NOT FINISHED");
    string idSchedule;
    cout << "Masukan ID Jadwal Interview: ";
    getline(cin >> ws, idSchedule);

    int selectedSchedule = findScheduleInterview(idSchedule);
    if (selectedSchedule < 0)
    {
      cout << "Jadwal tidak ada!" << endl;
      return;
    }

    char result;
    do
    {
      cout << "Apakah peserta yang bersangkutan lulus(Y/N)? ";
      cin >> result;
    } while (result != 'Y' && result != 'N');

    if (result == 'N')
    {
      userService->deleteUserByUsername(schedules[selectedSchedule].getUsernameCandidateStudent());
    }

    schedules[selectedSchedule].setStatus("FINISHED");
  }

  void deleteSchedule()
  {
    showAllScheduleInterviews();
    string idSchedule;
    cout << "Masukan ID Jadwal Interview: ";
    getline(cin >> ws, idSchedule);

    int selectedSchedule = findScheduleInterview(idSchedule);
    if (selectedSchedule < 0)
    {
      cout << "Jadwal tidak ada!" << endl;
      return;
    }

    schedules.erase(schedules.begin() + selectedSchedule);
  }

  bool checkUserHaveSchedule(string username, int month, int dayOfMonth, int hour)
  {
    for (ScheduleInterview schedule : schedules)
    {
      if ((schedule.getUsernameHr() == username && schedule.getDate().tm_mon == month && schedule.getDate().tm_mday == dayOfMonth && schedule.getDate().tm_hour == hour) || (schedule.getUsernameCandidateStudent() == username && schedule.getDate().tm_mon == month && schedule.getDate().tm_mday == dayOfMonth && schedule.getDate().tm_hour == hour))
      {
        return true;
      }
    }
    return false;
  }
};
