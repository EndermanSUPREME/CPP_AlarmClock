#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <chrono>
#include <windows.h>

using std::cout; using std::cin; using std::endl;
using std::time; using std::ctime; using std::string;
using std::chrono::system_clock;
using std::ifstream;

#ifndef ALARM_HPP
#define ALARM_HPP
class Alarm
{
public:
	Alarm();

    void CreateAlarm()
    {
        while (userInputTime.length() - 1 != 4)
        {
            cout << "Enter time [Ex 09:30]: " << endl;
            cin >> userInputTime;

            cout << userInputTime.length() - 1 << endl;

            if (userInputTime.length() - 1 == 4)
            {
                // 01234
                // 09:10
                if (userInputTime[3] - '0' < 0 || userInputTime[3] - '0' > 5)
                {
                    cout << "[-] Bad Minute Given!" << endl;

                    userInputTime = "";
                    continue;
                }

                if (userInputTime[4] - '0' < 0 || userInputTime[4] - '0' > 9)
                {
                    cout << "[-] Bad Minute Given!" << endl;

                    userInputTime = "";
                    continue;
                }
            }
            else
            {
                cout << "[-] BAD FORMAT! Ensure time format is --> HH:MM" << endl;
            }
        }

        bool isPM = (userInputTimeMode == "Pm" || userInputTimeMode == "pM" || userInputTimeMode == "PM" || userInputTimeMode == "pm");
        bool isAM = (userInputTimeMode == "Am" || userInputTimeMode == "aM" || userInputTimeMode == "AM" || userInputTimeMode == "am");

        while (!isPM && !isAM)
        {
            cout << "Is this time AM or PM?: " << endl;
            cin >> userInputTimeMode;

            isPM = (userInputTimeMode == "Pm" || userInputTimeMode == "pM" || userInputTimeMode == "PM" || userInputTimeMode == "pm");
            isAM = (userInputTimeMode == "Am" || userInputTimeMode == "aM" || userInputTimeMode == "AM" || userInputTimeMode == "am");
        }

        // if PM we need to add 12 to the time
        if (isPM)
        {
            // 12:mm PM --> 12:00
 
            // if the user enters in 12:mm PM we cant add 12 to this

            //  userInputTime.length() - 1 != 4 ==> 09:23
            //  userInputTime.length() - 1 != 3 ==> 9:23

                int oldHour;
                int militaryHour;


                oldHour = userInputTime[1] - '0';
                militaryHour = (oldHour + 12); // 13-21

                // cout << (militaryHour / 10) << endl;
                // cout << (militaryHour % 10) << endl;
                
                if (userInputTime[0] - '0' != 1)
                {
                    userInputTime[0] = '0' + (militaryHour / 10);
                    userInputTime[1] = '0' + (militaryHour % 10);
                }
                else
                {
                    userInputTime[0] = '0' + 2;
                    userInputTime[1] = '0' + (militaryHour % 10);
                }
        }

        cout << "[+] Alarm Set for :: " << userInputTime << endl;

        // preopen web browser
        ShellExecute(0, 0, L"https://google.com/", 0, 0, 0);
        
        // bring console into focus
        Sleep(1500);
        ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);

        Internal(userInputTime);
    }

    void CreateMultiAlarm(string setTime, string setMode)
    {
        userInputTime = setTime;
        userInputTimeMode = setMode;

        bool isPM = (userInputTimeMode == "Pm" || userInputTimeMode == "pM" || userInputTimeMode == "PM" || userInputTimeMode == "pm");
        bool isAM = (userInputTimeMode == "Am" || userInputTimeMode == "aM" || userInputTimeMode == "AM" || userInputTimeMode == "am");

        while (!isPM && !isAM)
        {
            cout << "Is this time AM or PM?: " << endl;
            cin >> userInputTimeMode;

            isPM = (userInputTimeMode == "Pm" || userInputTimeMode == "pM" || userInputTimeMode == "PM" || userInputTimeMode == "pm");
            isAM = (userInputTimeMode == "Am" || userInputTimeMode == "aM" || userInputTimeMode == "AM" || userInputTimeMode == "am");
        }

        // if PM we need to add 12 to the time
        if (isPM)
        {
            // 12:mm PM --> 12:00

            // if the user enters in 12:mm PM we cant add 12 to this

            //  userInputTime.length() - 1 != 4 ==> 09:23
            //  userInputTime.length() - 1 != 3 ==> 9:23

            int oldHour;
            int militaryHour;


            oldHour = userInputTime[1] - '0';
            militaryHour = (oldHour + 12); // 13-21

            // cout << (militaryHour / 10) << endl;
            // cout << (militaryHour % 10) << endl;

            if (userInputTime[0] - '0' != 1)
            {
                userInputTime[0] = '0' + (militaryHour / 10);
                userInputTime[1] = '0' + (militaryHour % 10);
            }
            else
            {
                userInputTime[0] = '0' + 2;
                userInputTime[1] = '0' + (militaryHour % 10);
            }
        }

        cout << "[+] Alarm Set for :: " << userInputTime << endl;

        Internal(userInputTime);
    }

    void Internal(string alarmTime)
    {
        t_c = sysClock.to_time_t(sysClock.now());

        // Format and extract the hour and minute
        snprintf(timeString, sizeof(timeString), "%02d:%02d", timeInfo.tm_hour, timeInfo.tm_min);

        // cout << "The system clock time is currently: " << timeString << endl;

        while (timeString != alarmTime)
        {
            if (localtime_s(&timeInfo, &t_c) == 0)
            {
                t_c = sysClock.to_time_t(sysClock.now());

                snprintf(timeString, sizeof(timeString), "%02d:%02d", timeInfo.tm_hour, timeInfo.tm_min);

                // cout << "The system clock time is currently: " << timeString << endl;
                // cout << "The alarm time is currently: " << alarmTime << endl;

                if (timeString == alarmTime)
                {
                    ShellExecute(0, 0, L"https://youtu.be/Je0kb9pYsdo?si=P6WhSTYiZLUsmfNC", 0, 0, SW_SHOW);

                    // cout << "=============================\n=============================\n=============================\n=============================" << endl;
                }

                // sleep for 1 second
                Sleep(1000);
            }
        }
    }

private:
    system_clock sysClock;
    time_t t_c = sysClock.to_time_t(sysClock.now());
    string userInputTime, userInputTimeMode;

    struct tm timeInfo = {};
    char timeString[6] = {'0', '0', '0', '0', '0', '0'}; // Buffer to hold the hh:mm part
};

Alarm::Alarm()
{
    cout << "WELCOME USER!" << endl;
}

#endif // ALARM_HPP