#include <iostream>
#include <string>

using namespace std;

#include "./model/Schedule.cpp"
#include "./model/Item.cpp"
#include "./model/Attendance.cpp"
#include "./model/Message.cpp"
#include "./model/Place.cpp"
#include "./model/ScheduleInterview.cpp"
#include "./model/ScheduleStudy.cpp"
#include "./model/ScheduleWorkshop.cpp"
#include "./model/User.cpp"
#include "./service/HelperService.cpp"
#include "./service/ItemService.cpp"
#include "./service/UserService.cpp"
#include "./service/PlaceService.cpp"
#include "./service/AttendanceService.cpp"
#include "./service/MessageService.cpp"
#include "./service/ScheduleInterviewService.cpp"
#include "./service/ScheduleStudyService.cpp"
#include "./service/ScheduleWorkshopService.cpp"
#include "./service/MainMenu.cpp"

int main()
{
  HelperService helperService;
  ItemService itemService(helperService);
  UserService userService(helperService);
  PlaceService placeService(helperService);
  AttendanceService attendanceService(helperService);
  MessageService messageService(helperService, &userService);
  ScheduleInterviewService scheduleInterviewService(helperService, &userService);
  ScheduleStudyService scheduleStudyService(helperService, &userService);
  ScheduleWorkshopService scheduleWorkshopService(helperService, &userService, &placeService, &itemService, &scheduleStudyService);
  MainMenu mainMenu(helperService, &userService, &scheduleInterviewService, &scheduleWorkshopService, &scheduleStudyService, &attendanceService, &itemService, &placeService, &messageService);
  mainMenu.showMainMenus();
}