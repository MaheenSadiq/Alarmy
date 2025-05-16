#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <MMsystem.h>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>
#include<string>
using namespace std;
using namespace sf;


class Display;
class Alarm;
class Sound;


class Sound
{
protected:
    int select = 0, num = 0;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
public:
    virtual void dis() {};
    void selectsound()
    {
        SetConsoleTextAttribute(h, 5);
        cout << setw(53) << "Select Sound:" << endl;
        cout << setw(50) << "Sound 1" << endl;
        cout << setw(50) << "Sound 2" << endl;
        cout << setw(50) << "Sound 3" << endl;
        cout << setw(50) << "Sound 4" << endl;
        cin >> select;
        SetConsoleTextAttribute(h, 2);
        cout << setw(58) << "Sound selected succesfully" << endl;
        cout << endl;
        SetConsoleTextAttribute(h, 12);
        cout << setw(55) << "Press 0 to return" << endl;
        cout << setw(50);
        cin >> num;
        if (num == 0)
        {
            system("cls");
            dis();
        }
    }


    void playingsound()
    {
        switch (select)
        {
        case 1:
        { PlaySound(TEXT("alarm1.wav"), NULL, SND_FILENAME | SND_ASYNC);
        break;
        }
        case 2:
        { PlaySound(TEXT("alarm2.wav"), NULL, SND_FILENAME | SND_ASYNC);
        break;
        }
        case 3:
        { PlaySound(TEXT("alarm3.wav"), NULL, SND_FILENAME | SND_ASYNC);
        break;
        }
        case 4:
        { PlaySound(TEXT("alarm4.wav"), NULL, SND_FILENAME | SND_ASYNC);
        break;
        }
        }
    }
};


class Alarm
{
protected:
  
    HANDLE enter = GetStdHandle(STD_OUTPUT_HANDLE);
    static const int MAX_ALARMS = 20;
    tm alarms[MAX_ALARMS];
    int n = 0, h = 0, m = 0, s = 0;

public:
    virtual void dis() {};
    virtual void playingsound() {};
    void settime()
    {
        time_t T = time(0);
        tm* current = localtime(&T);
        SetConsoleTextAttribute(enter, 11);
        cout << "Date:" << __DATE__;
        cout << "\nTime: " << current->tm_hour << ":" << current->tm_min << ":" << current->tm_sec << endl;
    }

    void setalarm()
    {
        SetConsoleTextAttribute(enter, 6);
        cout << setw(50) << "Enter number of alarms : ";
        cin >> n;
        cout << setw(57) << "Enter time to set alarm (HH:MM:SS): " << endl;
        for (int i = 0; i < n; i++)
        {
            cout << setw(43) << "Alarm " << i + 1 << ": ";
            cin >> alarms[i].tm_hour;
            cin >> alarms[i].tm_min;
            cin >> alarms[i].tm_sec;
        }
        SetConsoleTextAttribute(enter, 11);
        cout << setw(57) << "Alarm(s) set successfully for:" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << setw(43) << "Alarm " << i + 1 << ": " << alarms[i].tm_hour << ":" << alarms[i].tm_min << ":" << alarms[i].tm_sec << endl;
        }
    }

    void alarmringing()
    {
        
        int x;
        time_t T;
        tm* current;
        do
        {
            T = time(0);
            current = localtime(&T);
            for (int i = 0; i < n; i++)
            {
                if (current->tm_hour == alarms[i].tm_hour && current->tm_min == alarms[i].tm_min && current->tm_sec == alarms[i].tm_sec)
                {
                    SetConsoleTextAttribute(enter, 4);
                    cout << setw(50) << "AlARM TRIGGERED" << endl;
                    PlaySound(TEXT("alarm1.wav"), NULL, SND_FILENAME | SND_ASYNC);

                }
            }
            Sleep(1000);
        } while (true);
        SetConsoleTextAttribute(enter, 12);
        cout << endl;
        cout << setw(55) << "Press 1 to return and 0 to exit";
        cin >> x;
        if (x == 1) {
            system("cls");
            dis();
        }
        else if (x == 0) {
            exit(0);
        }
    }

};


class Display : public Sound, public Alarm
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
public:
    void dis()
    {

        int n;
        SetConsoleTextAttribute(h, 11);
        cout << "Date:" << __DATE__ << endl;
        cout << "Time:" << __TIME__ << endl;
        SetConsoleTextAttribute(h, 6);
        cout << setw(48) << "1)Set ALARM" << endl;
        cout << setw(50) << "2)SELECT SOUND" << endl;
        cout << setw(50) << "3)SELECT LEVEL" << endl;
        cout << setw(45) << "4)EXIT" << endl;
        cout << endl;
        SetConsoleTextAttribute(h, 12);
        cout << setw(55) << "Press number to select:";
        cin >> n;
        system("cls");
        switch (n)
        {
        case 1:
        {
            settime();
            setalarm();
            Alarm::alarmringing();
            break;
        }
        case 2:
        {
            selectsound();
            Sound::playingsound();
            break;
        }
        case 3: {
            int num;
            SetConsoleTextAttribute(h, 11);
            cout << "Date:" << __DATE__ << endl;
            cout << "Time:" << __TIME__ << endl;
            SetConsoleTextAttribute(h, 6);
            cout << setw(50) << "Select Level" << endl;
            cout << setw(50) << "1)Easy" << endl;
            cout << setw(52) << "2)Medium" << endl;
            cout << setw(54) << "3)Difficult" << endl;
            cin >> num;
            SetConsoleTextAttribute(h, 2);
            cout << setw(55) << "Level selected succesfully" << endl;
            cout << endl;
            SetConsoleTextAttribute(h, 12);
            cout << setw(55) << "Press 0 to return" << endl;
            cout << setw(50);
            cin >> num;
            if (num == 0)
            {
                system("cls");
                dis();
            }

        }
        case 4: { exit(0); }
        }
    }
};

