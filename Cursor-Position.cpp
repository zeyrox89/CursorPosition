//This is the fourth prototype of the mouse position code. This code works only on Windows.

#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>

//Clears the output line
void clearLine () {
    std::cout << "\r";
    
    for (int i=0; i<50; i++) {
        std::cout << ' ';
    }
    
    std::cout << "\r";
    std::cout << "Mouse Coordinates: ";
    std::cout.flush();
}


//Save the coordinates in the file
void saveCoordinates (std::string& path, int x, int y) {
    std::fstream File;
    File.open(path, std::ios::app);
    
    File << x << " - " << y << std::endl;
    File.close();
}


//Save the coordinates to the computer clipboard with this format: "xxxx - xxxx"
void copyToClipboard(int num1, int num2) {
    std::string text = std::to_string(num1) + " - " + std::to_string(num2);
    if (OpenClipboard(nullptr)) {
        EmptyClipboard();
        HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, text.size() + 1);
        if (hClipboardData) {
            char* pchData = static_cast<char*>(GlobalLock(hClipboardData));
            if (pchData) {
                strcpy_s(pchData, text.size() + 1, text.c_str());
                GlobalUnlock(hClipboardData);
                SetClipboardData(CF_TEXT, hClipboardData);
            }
        }
        CloseClipboard();
    }
}


int main() {
    
    std::string path = "coordinates.txt";
    
    //Create a new section for the new coordinates
    std::ofstream File(path, std::ios::app);

    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime); 

    int year = localTime->tm_year + 1900; 
    int month = localTime->tm_mon + 1;   
    int day = localTime->tm_mday;         
    int hour = localTime->tm_hour;      
    int minute = localTime->tm_min;    
    int second = localTime->tm_sec;     

    //Print the date and the time in the text file
    File << std::endl << std::endl << std::endl << std::endl;
    File << "Time: " << year << "-" << month << "-" << day << " " << hour << ":" << minute << ":" << second << std::endl;
    File << "-----------------------------------------------------------------" << std::endl;
    
    
    
    
    
    
    std::cout << "Mouse Coordinates: ";
    POINT Position;
    
    while (true) {
        GetCursorPos(&Position);
        int x = Position.x;
        int y = Position.y;
        std::cout << x << ", " << y;
        
        //Check if the "Enter" key was pressed
        if (_kbhit()) {
            int key = _getch();
            if (key == 13) {
                saveCoordinates(path, x, y);
                copyToClipboard(x, y);
            }
            if (key == 27) {
                break;
            }
        }
        
        Sleep(50);
        clearLine();
    }

    return 0;
}