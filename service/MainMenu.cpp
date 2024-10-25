#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MainMenu
{
private:
  vector<string> mainMenus;
  vector<string> hrMenus;
  vector<string> coMenus;
  vector<string> trainerMenus;
  vector<string> studentMenus;
  vector<string> studentCandidateMenus;
  HelperService helperService;
  UserService *userService;
  ScheduleInterviewService *scheduleInterviewService;
  ScheduleWorkshopService *scheduleWorkshopService;
  ScheduleStudyService *scheduleStudyService;
  AttendanceService *attendanceService;
  ItemService *itemService;
  PlaceService *placeService;
  MessageService *messageService;

public:
  MainMenu(HelperService helperService, UserService *userService, ScheduleInterviewService *scheduleInterviewService, ScheduleWorkshopService *scheduleWorkshopService, ScheduleStudyService *scheduleStudyService, AttendanceService *attendanceService, ItemService *itemService, PlaceService *placeService, MessageService *messageService)
  {
    this->mainMenus = {"Login", "Keluar"};
    this->hrMenus = {"Tambah user", "Edit user", "Tampilkan user", "Hapus user", "Terima calon peserta staditek", "Buat jadwal interview", "Edit tanggal jadwal interview", "Penyelesaian jadwal interview", "Lihat jadwal interview", "Hapus jadwal interview", "Lihat jadwal workshop", "Lihat jadwal belajar", "Lakukan absen", "Lihat semua absen", "Lihat absen berdasarkan tanggal", "Kirim pesan", "Pesan terkirim", "Pesan masuk", "Keluar"};
    this->coMenus = {"Tambah jadwal workshop", "Edit tanggal jadwal workshop", "Penyelesaian jadwal workshop", "Lihat jadwal workshop", "Hapus jadwal workshop", "Tambah item", "Restok item", "Hapus item", "Tampilkan item", "Tambah tempat", "Tampilkan tempat", "Hapus tempat", "Lakukan absen", "Kirim pesan", "Pesan terkirim", "Pesan masuk", "Keluar"};
    this->trainerMenus = {"Tambah jadwal belajar", "Edit tanggal jadwal belajar", "Penyelesaian jadwal belajar", "Lihat jadwal belajar", "Hapus jadwal belajar", "Lihat jadwal workshop", "Lakukan absen", "Kirim pesan", "Pesan terkirim", "Pesan masuk", "Keluar"};
    this->studentMenus = {"Lihat jadwal belajar", "Lihat jadwal workshop", "Lakukan absen", "Kirim pesan", "Pesan terkirim", "Pesan masuk", "Keluar"};
    this->studentCandidateMenus = {"Lihat jadwal interview", "Keluar"};
    this->helperService = helperService;
    this->userService = userService;
    this->scheduleInterviewService = scheduleInterviewService;
    this->scheduleWorkshopService = scheduleWorkshopService;
    this->scheduleStudyService = scheduleStudyService;
    this->attendanceService = attendanceService;
    this->itemService = itemService;
    this->placeService = placeService;
    this->messageService = messageService;
  }

  void showMainMenus()
  {
    char confirm = 'N';
    int selectedMenu = helperService.loopingMenus("Menu Utama", mainMenus);
    switch (selectedMenu)
    {
    case 1:
    {
      int currentUser = userService->login();
      string role = userService->getUserByIndex(currentUser)->getRole();

      if (role == "HR")
      {
        showHrMenus(currentUser);
      }
      else if (role == "CO")
      {
        showCoMenus(currentUser);
      }
      else if (role == "TRAINER")
      {
        showTrainerMenus(currentUser);
      }
      else if (role == "STUDENT")
      {
        showStudentMenus(currentUser);
      }
      else if (role == "STUDENT CANDIDATE")
      {
        showStudentCandidateMenus(currentUser);
      }
      else
      {
        cout << "Silahkan coba kembali" << endl;
      }
    }
    break;
    case 2:
      cout << "Apakah anda yakin ingin keluar(Y/N)? ";
      cin >> confirm;
      break;
    default:
      cout << "Pilihan tidak ada!" << endl;
      break;
    }

    if (confirm == 'Y')
    {
      return;
    }

    showMainMenus();
  }

  void showHrMenus(int currentHr)
  {
    char confirm = 'N';
    int selectedMenu = helperService.loopingMenus("Menu Human Resources", hrMenus);
    switch (selectedMenu)
    {
    case 1:
      userService->addUser();
      break;
    case 2:
      userService->editUser();
      break;
    case 3:
      userService->showUsersByRole();
      break;
    case 4:
      userService->deleteUser();
      break;
    case 5:
      userService->changeStudentCandidateToStudent();
      break;
    case 6:
      scheduleInterviewService->addSchedule();
      break;
    case 7:
      scheduleInterviewService->editDateSchedule();
      break;
    case 8:
      scheduleInterviewService->interviewScheduleCompletion();
      break;
    case 9:
      scheduleInterviewService->showScheduleInterviews("NOT FINISHED");
      break;
    case 10:
      scheduleInterviewService->deleteSchedule();
      break;
    case 11:
      scheduleWorkshopService->showScheduleWorkshops("NOT FINISHED");
      break;
    case 12:
      scheduleStudyService->showScheduleStudys("NOT FINISHED");
      break;
    case 13:
    {
      string currentUsername = userService->getUserByIndex(currentHr)->getUsername();
      attendanceService->addAttendance(currentUsername);
    }
    break;
    case 14:
      attendanceService->showAllAttendences();
      break;
    case 15:
      attendanceService->showAttendancesByDate();
      break;
    case 16:
    {
      string currentUsername = userService->getUserByIndex(currentHr)->getUsername();
      messageService->sendMessage(currentUsername);
    }
    break;
    case 17:
    {
      string currentUsername = userService->getUserByIndex(currentHr)->getUsername();
      messageService->showSentMessages(currentUsername);
    }
    break;
    case 18:
    {
      string currentUsername = userService->getUserByIndex(currentHr)->getUsername();
      messageService->showIncomingMessages(currentUsername);
    }
    break;
    case 19:
      cout << "Apakah anda yakin ingin keluar(Y/N)? ";
      cin >> confirm;
      break;
    default:
      cout << "Pilihan tidak ada!" << endl;
      break;
    }

    if (confirm == 'Y')
    {
      return;
    }

    showHrMenus(currentHr);
  }

  void showCoMenus(int currentCo)
  {
    char confirm = 'N';
    int selectedMenu = helperService.loopingMenus("Menu Community Officer", coMenus);
    switch (selectedMenu)
    {
    case 1:
      scheduleWorkshopService->addSchedule();
      break;
    case 2:
      scheduleWorkshopService->editDateSchedule();
      break;
    case 3:
      scheduleWorkshopService->workshopScheduleCompletion();
      break;
    case 4:
      scheduleWorkshopService->showScheduleWorkshops("NOT FINISHED");
      break;
    case 5:
      scheduleWorkshopService->deleteSchedules();
      break;
    case 6:
      itemService->addItem();
      break;
    case 7:
      itemService->restockItem();
      break;
    case 8:
      itemService->deleteItem();
      break;
    case 9:
      itemService->showItems();
      break;
    case 10:
      placeService->addPlace();
      break;
    case 11:
      placeService->showPlaces();
      break;
    case 12:
      placeService->deletePlace();
      break;
    case 13:
    {
      string currentUsername = userService->getUserByIndex(currentCo)->getUsername();
      attendanceService->addAttendance(currentUsername);
    }
    break;
    case 14:
    {
      string currentUsername = userService->getUserByIndex(currentCo)->getUsername();
      messageService->sendMessage(currentUsername);
    }
    break;
    case 15:
    {
      string currentUsername = userService->getUserByIndex(currentCo)->getUsername();
      messageService->showSentMessages(currentUsername);
    }
    break;
    case 16:
    {
      string currentUsername = userService->getUserByIndex(currentCo)->getUsername();
      messageService->showIncomingMessages(currentUsername);
    }
    break;
    case 17:
      cout << "Apakah anda yakin ingin keluar(Y/N)? ";
      cin >> confirm;
      break;
    default:
      cout << "Pilihan tidak ada!" << endl;
      break;
    }

    if (confirm == 'Y')
    {
      return;
    }

    showCoMenus(currentCo);
  }

  void showTrainerMenus(int currentTrainer)
  {
    char confirm = 'N';
    int selectedMenu = helperService.loopingMenus("Menu Trainer", trainerMenus);
    switch (selectedMenu)
    {
    case 1:
      scheduleStudyService->addSchedule();
      break;
    case 2:
      scheduleStudyService->editDateSchedule();
      break;
    case 3:
      scheduleStudyService->studyScheduleCompletion();
      break;
    case 4:
      scheduleStudyService->showScheduleStudys("NOT FINISHED");
      break;
    case 5:
      scheduleStudyService->deleteSchedule();
      break;
    case 6:
      scheduleWorkshopService->showScheduleWorkshops("NOT FINISHED");
      break;
    case 7:
    {
      string currentUsername = userService->getUserByIndex(currentTrainer)->getUsername();
      attendanceService->addAttendance(currentUsername);
    }
    break;
    case 8:
    {
      string currentUsername = userService->getUserByIndex(currentTrainer)->getUsername();
      messageService->sendMessage(currentUsername);
    }
    break;
    case 9:
    {
      string currentUsername = userService->getUserByIndex(currentTrainer)->getUsername();
      messageService->showSentMessages(currentUsername);
    }
    break;
    case 10:
    {
      string currentUsername = userService->getUserByIndex(currentTrainer)->getUsername();
      messageService->showIncomingMessages(currentUsername);
    }
    break;
    case 11:
      cout << "Apakah anda yakin ingin keluar(Y/N)? ";
      cin >> confirm;
      break;
    default:
      cout << "Pilihan tidak ada!" << endl;
      break;
    }

    if (confirm == 'Y')
    {
      return;
    }

    showTrainerMenus(currentTrainer);
  }

  void showStudentMenus(int currentStudent)
  {
    char confirm = 'N';
    int selectedMenu = helperService.loopingMenus("Menu Peserta", studentMenus);
    switch (selectedMenu)
    {
    case 1:
      scheduleStudyService->showScheduleStudys("NOT FINISHED");
      break;
    case 2:
      scheduleWorkshopService->showScheduleWorkshops("NOT FINISHED");
      break;
    case 3:
    {
      string currentUsername = userService->getUserByIndex(currentStudent)->getUsername();
      attendanceService->addAttendance(currentUsername);
    }
    break;
    case 4:
    {
      string currentUsername = userService->getUserByIndex(currentStudent)->getUsername();
      messageService->sendMessage(currentUsername);
    }
    break;
    case 5:
    {
      string currentUsername = userService->getUserByIndex(currentStudent)->getUsername();
      messageService->showSentMessages(currentUsername);
    }
    break;
    case 6:
    {
      string currentUsername = userService->getUserByIndex(currentStudent)->getUsername();
      messageService->showIncomingMessages(currentUsername);
    }
    break;
    case 7:
      cout << "Apakah anda yakin ingin keluar(Y/N)? ";
      cin >> confirm;
      break;
    default:
      cout << "Pilihan tidak ada!" << endl;
      break;
    }

    if (confirm == 'Y')
    {
      return;
    }

    showStudentMenus(currentStudent);
  }

  void showStudentCandidateMenus(int currentStudentCandidate)
  {
    char confirm = 'N';
    int selectedMenu = helperService.loopingMenus("Menu calon peserta", studentCandidateMenus);
    switch (selectedMenu)
    {
    case 1:
    {
      string currentUsername = userService->getUserByIndex(currentStudentCandidate)->getUsername();
      scheduleInterviewService->showScheduleInterviewsForStudentCandidate("NOT FINISHED", currentUsername);
    }
    break;
    case 2:
      cout << "Apakah anda yakin ingin keluar(Y/N)? ";
      cin >> confirm;
      break;
    default:
      cout << "Pilihan tidak ada!" << endl;
      break;
    }

    if (confirm == 'Y')
    {
      return;
    }

    showStudentCandidateMenus(currentStudentCandidate);
  }
};
