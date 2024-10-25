#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <bits/stdc++.h>

using namespace std;

class MessageService
{
private:
  vector<Message> messages;
  HelperService helperService;
  UserService *userService;

public:
  MessageService(HelperService helperService, UserService *userService)
  {
    this->helperService = helperService;
    this->userService = userService;
  }
  void sendMessage(string ownerUsername)
  {
    string id = helperService.generateRandomId();
    tm date = helperService.createStructTmTimeNow();
    userService->showAllUserExceptStudentCandidate(ownerUsername);
    string destinationUsername;
    cout << "Masukan username tujuan: ";
    getline(cin >> ws, destinationUsername);

    if (userService->findUser(destinationUsername) < 0)
    {
      cout << "User tidak ada" << endl;
      return;
    }

    string content;
    cout << "Masukan pesan: ";
    getline(cin >> ws, content);

    Message message(id, ownerUsername, destinationUsername, content, date);

    messages.push_back(message);
  }

  void showIncomingMessages(string currentUsername)
  {
    userService->showAllUserExceptStudentCandidate(currentUsername);
    string messengerUsername;
    cout << "Mau cek pesan dari siapa? masukan usernamenya: ";
    getline(cin >> ws, messengerUsername);

    if (userService->findUser(messengerUsername) < 0)
    {
      cout << "User tidak ada" << endl;
      return;
    }

    vector<Message> currentMessages;
    for (Message message : messages)
    {
      if (message.getDestinationUsername() == currentUsername && message.getOwnerUsername() == messengerUsername)
      {
        currentMessages.push_back(message);
      }
    }

    reverse(currentMessages.begin(), currentMessages.end());
    for (Message message : currentMessages)
    {
      cout << endl;
      tm structDate = message.getDate();
      time_t date = mktime(&structDate);
      cout << "Id: " << message.getId() << "\tUsername pengirim: " << message.getOwnerUsername() << "\tPesan: " << message.getContent() << "\tWaktu: " << ctime(&date);
    }
  }

  void showSentMessages(string currentUsername)
  {
    userService->showAllUserExceptStudentCandidate(currentUsername);
    string destinationUsername;
    cout << "Mau cek riwayat pengiriman pesan kesiapa? masukan usernamenya: ";
    getline(cin >> ws, destinationUsername);

    if (userService->findUser(destinationUsername) < 0)
    {
      cout << "User tidak ada" << endl;
      return;
    }

    vector<Message> currentMessages;
    for (Message message : messages)
    {
      if (message.getDestinationUsername() == destinationUsername && message.getOwnerUsername() == currentUsername)
      {
        currentMessages.push_back(message);
      }
    }

    reverse(currentMessages.begin(), currentMessages.end());
    for (Message message : currentMessages)
    {
      cout << endl;
      tm structDate = message.getDate();
      time_t date = mktime(&structDate);
      cout << "Id: " << message.getId() << "\tUsername tujuan: " << message.getDestinationUsername() << "\tPesan: " << message.getContent() << "\tWaktu: " << ctime(&date);
    }
  }

  void showMessages(vector<Message> currentMessages)
  {
    for (Message message : currentMessages)
    {
      cout << endl;
      tm structDate = message.getDate();
      time_t date = mktime(&structDate);
      cout << "Id: " << message.getId() << "\tUsername pengirim: " << message.getOwnerUsername() << "\tUsername tujuan: " << message.getDestinationUsername() << "\tPesan: " << message.getContent() << "\tWaktu: " << ctime(&date);
    }
  }
};
