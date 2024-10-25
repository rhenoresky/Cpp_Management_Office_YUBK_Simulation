#include <iostream>
#include <string>
#include <vector>

using namespace std;

class UserService
{
private:
  vector<User> users;
  HelperService helperService;

public:
  UserService(HelperService helperService)
  {
    this->helperService = helperService;
    User user("Naruto", "Naruto", "Naruto", "HR");
    this->users.push_back(user);
  }
  void addUser()
  {
    string username;
    cout << "Masukan username: ";
    getline(cin >> ws, username);

    int selectedUser = findUser(username);
    if (selectedUser >= 0)
    {
      cout << "Operasi dibatalkan! User sudah ada" << endl;
      return;
    }

    string password;
    cout << "Masukan password: ";
    getline(cin >> ws, password);
    string fullname;
    cout << "Masukan nama lengkap: ";
    getline(cin >> ws, fullname);
    string role = helperService.selectRole();
    if (role == "!VALID")
    {
      cout << "Operasi dibatalkan! Role tidak ada" << endl;
      return;
    }

    User user(username, password, fullname, role);
    users.push_back(user);
  }

  void changeStudentCandidateToStudent()
  {
    showUsers("STUDENT CANDIDATE");
    string username;
    cout << "Masukan username: ";
    getline(cin >> ws, username);

    int selectedUser = findUser(username);
    if (selectedUser < 0)
    {
      cout << "Operasi dibatalkan! User tidak ada" << endl;
      return;
    }

    users[selectedUser].setRole("STUDENT");
  }

  void editUser()
  {
    string role = helperService.selectRole();
    if (role == "!VALID")
    {
      cout << "Operasi dibatalkan! Role tidak ada" << endl;
      return;
    }
    showUsers(role);
    string username;
    cout << "Masukan username: ";
    getline(cin >> ws, username);

    int selectedUser = findUser(username);
    if (selectedUser < 0)
    {
      cout << "Operasi dibatalkan! User tidak ada" << endl;
      return;
    }

    string newPassword;
    cout << "Masukan password baru: ";
    getline(cin >> ws, newPassword);
    string newFullname;
    cout << "Masukan nama lengkap baru: ";
    getline(cin >> ws, newFullname);
    string newRole = helperService.selectRole();
    if (newRole == "!VALID")
    {
      cout << "Operasi dibatalkan! Role tidak ada" << endl;
      return;
    }
    users[selectedUser].setPassword(newPassword);
    users[selectedUser].setFullname(newFullname);
    users[selectedUser].setRole(newRole);
  }

  void showUsers(string role)
  {
    int number = 1;
    for (User user : users)
    {
      if (user.getRole() == role)
      {
        cout << number << ".Username: " << user.getUsername() << "\tNama: " << user.getFullname() << endl;
        number++;
      }
    }
  }

  void showAllUserExceptStudentCandidate(string currentUsername)
  {
    int number = 1;
    for (User user : users)
    {
      if (user.getRole() != "STUDENT CANDIDATE" && user.getUsername() != currentUsername)
      {
        cout << number << ".Username: " << user.getUsername() << "\tNama: " << user.getFullname() << endl;
        number++;
      }
    }
  }

  void showUsersByRole()
  {
    string role = helperService.selectRole();
    if (role == "!VALID")
    {
      cout << "Operasi dibatalkan! Role tidak ada" << endl;
      return;
    }
    showUsers(role);
  }

  int findUser(string username)
  {
    for (int i = 0; i < users.size(); i++)
    {
      if (users[i].getUsername() == username)
      {
        return i;
      }
    }

    return -1;
  }
  User *getUserByIndex(int currentUser)
  {
    return &users[currentUser];
  }
  User *getUserByUsername(string username)
  {
    int selectedUser = findUser(username);
    return &users[selectedUser];
  }

  void deleteUser()
  {
    string role = helperService.selectRole();
    if (role == "!VALID")
    {
      cout << "Operasi dibatalkan! Role tidak ada" << endl;
      return;
    }
    showUsers(role);
    string username;
    cout << "Masukan username: ";
    getline(cin >> ws, username);

    int selectedUser = findUser(username);
    if (selectedUser == 0)
    {
      cout << "User default tidak bisa dihapus!" << endl;
      return;
    }

    if (selectedUser < 0)
    {
      cout << "Operasi dibatalkan! User tidak ada" << endl;
      return;
    }

    users.erase(users.begin() + selectedUser);
  }

  int login()
  {
    string username;
    cout << "Masukan username: ";
    getline(cin >> ws, username);

    int selectedUser = findUser(username);
    if (selectedUser < 0)
    {
      cout << "Operasi dibatalkan! User tidak ada" << endl;
      return -1;
    }

    string password;
    cout << "Masukan password: ";
    getline(cin >> ws, password);

    if (users[selectedUser].getPassword() != password)
    {
      cout << "Password salah!" << endl;
      return -1;
    }

    return selectedUser;
  }

  void deleteUserByUsername(string username)
  {
    int selectedUser = findUser(username);
    users.erase(users.begin() + selectedUser);
  }

  bool checkUserHaveScheduleWorkshop(vector<ScheduleWorkshop> schedules, string username, int dayOfMonth)
  {
    for (ScheduleWorkshop schedule : schedules)
    {
      if ((schedule.getUsernameMC() == username && schedule.getDate().tm_mday == dayOfMonth) || (schedule.getUsernameSpeaker() == username && schedule.getDate().tm_mday == dayOfMonth))
      {
        return true;
      }
    }
    return false;
  }

  bool checkUserHaveScheduleStudy(vector<ScheduleStudy> schedules, string username, int dayOfMonth)
  {
    for (ScheduleStudy schedule : schedules)
    {
      if (schedule.getUsernameTrainer() == username && schedule.getDate().tm_mday == dayOfMonth)
      {
        return true;
      }
    }
    return false;
  }
};
