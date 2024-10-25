#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class AttendanceService
{
private:
  vector<Attendance> attendances;
  HelperService helperService;

public:
  AttendanceService(HelperService helperService)
  {
    this->helperService = helperService;
  }
  void addAttendance(string currentUsername)
  {
    string id = helperService.generateRandomId();
    tm date = helperService.createStructTmTimeNow();
    Attendance attendance(id, currentUsername, date);
    attendances.push_back(attendance);
    cout << "--- ABSEN BERHASIL ---" << endl;
  }

  void showAttendancesByDate()
  {
    int month;
    cout << "Masukan bulan: ";
    cin >> month;

    int dayOfMonth;
    cout << "Masukan tanggal: ";
    cin >> dayOfMonth;

    vector<Attendance> currentAttendance;
    for (Attendance attendance : attendances)
    {
      if (attendance.getDate().tm_mon == (month - 1) && attendance.getDate().tm_mday == dayOfMonth)
      {
        currentAttendance.push_back(attendance);
      }
    }

    showAttendances(currentAttendance);
  }

  void showAttendances(vector<Attendance> currentAttendance)
  {
    int number = 1;
    for (Attendance attendance : currentAttendance)
    {
      cout << endl;
      tm structDate = attendance.getDate();
      time_t date = mktime(&structDate);
      cout << number << ".Id: " << attendance.getId() << "\tUsername: " << attendance.getOwnerUsername() << "\tWaktu: " << ctime(&date);
      number++;
    }
  }

  void showAllAttendences()
  {
    showAttendances(attendances);
  }
};
