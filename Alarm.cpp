#include "alarmHeader.hpp"

int ReadAlarmFile();

int main()
{
	char c;
	cout << "Do you want multiple alarms? [Y/n]: ";
	cin >> c;
	cout << endl;

	if (c == 'n' || c == 'N')
	{
		Alarm nAlarm;
        nAlarm.CreateAlarm();
	}
	else
	{
        // preopen web browser
        ShellExecute(0, 0, L"https://google.com/", 0, 0, 0);

        // bring console into focus
        Sleep(1500);
        ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);

		ReadAlarmFile();
	}
}

int ReadAlarmFile()
{
    ifstream inputFile;
    inputFile.open("C:/alarms.txt"); // Open the input file (replace "input.txt" with your file's path)

    if (!inputFile.is_open()) {
        cout << "[-] Failed to open the input file." << endl;
        cout << "[*] Searching for File inside C:/PC_Alarm/alarms.txt" << endl;

        inputFile.open("C:/PC_Alarm/alarms.txt");

        if (!inputFile.is_open()) {
            cout << "[-] Failed to open the input file." << endl;
            cout << "[*] Check if alarms.txt is located in :: C:/alarms.txt OR C:/PC_Alarm/alarms.txt" << endl;

            inputFile.close();

            ifstream soundFile("C:/beeper.mp3");
            ifstream soundFile2("C:/PC_Alarm/beeper.mp3");

            // Play sound for when an issue occurs
            if (soundFile.good())
            {
                system("C:/beeper.mp3");
            }
            else if (soundFile2.good())
            {
                system("C:/PC_Alarm/beeper.mp3");
            }
            else
            {
                cout << "[-] Sound File Missing!\nNothing Located in either C:/beeper.mp3 OR C:/PC_Alarm/beeper.mp3" << endl;
            }

            Sleep(1500);
            ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);
            
            char c;
            cout << "Press Enter to Continue" << endl;
            cin >> c;

            return 1;
        }
    }

    cout << "[+] alarms.txt was Found!" << endl;

    string line;
    string substring1;
    string substring2;

    while (std::getline(inputFile, line)) {
        if (line.length() >= 7) {
            // Extract characters 0-4 into substring1 and characters 5-6 into substring2
            substring1 = line.substr(0, 5);
            substring2 = line.substr(5, 2);

            // Do something with the substrings (e.g., print or process them)
            // std::cout << "Substring 1: " << substring1 << " Substring 2: " << substring2 << std::endl;
            Alarm nAlarm;
            nAlarm.CreateMultiAlarm(substring1, substring2);
        }
    }

    inputFile.close(); // Close the file when done

    return 0;
}