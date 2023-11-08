#include "alarmHeader.hpp"

// prototype for ReadAlarmFile function
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

	    // Runs when the alarms.txt file cannot be found
        if (!inputFile.is_open()) {
            cout << "[-] Failed to open the input file." << endl;
            cout << "[*] Check if alarms.txt is located in :: C:/alarms.txt OR C:/PC_Alarm/alarms.txt" << endl;

            inputFile.close();

            ifstream soundFile("C:/beeper.mp3");
            ifstream soundFile2("C:/PC_Alarm/beeper.mp3");

            // check if mp3 file exists in specific locations
            if (soundFile.good())
            {
		    // Play sound for when an issue occurs
                system("C:/beeper.mp3");
            }
            else if (soundFile2.good())
            {
		    // Play sound for when an issue occurs
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
		// Mostly here incase something goes wrong the screen program doesnt quit
		// when the user is trying to read any debug outputs
            cin >> c;

            return 1;
        }
    }

	// Code below runs when alarms.txt is found and can be opened without error
    cout << "[+] alarms.txt was Found!" << endl;

    string line;
    string substring1;
    string substring2;

    while (std::getline(inputFile, line)) {
        if (line.length() >= 7) {
		
            // Extract Time components from string
            timeStr = line.substr(0, 5);
            modeStr = line.substr(5, 2);
		
            Alarm nAlarm;
            nAlarm.CreateMultiAlarm(timeStr, modeStr);
        }
    }

    inputFile.close(); // Close the file when done

    return 0;
}
