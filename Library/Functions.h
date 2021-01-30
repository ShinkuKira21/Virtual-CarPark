//Windows/Linux commands // Author: Edward Patch

#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
class Functions 
{
    protected:
		// 0 = Windows, 1 = Linux
		const int operatingSystemConf = 0;
        std::stringstream stream;
        std::string uInput;
        char cInput;
        double nInput;
        
        time_t t;
        tm* localTime;

    public:
        void PauseSystem() 
        { 
			//Windows
			if (operatingSystemConf == 0)
				system("Pause");

            //Instead of system("Pause");
            //Send to my text input and ask the user to press enter :/
            
			//Linux:
			else
				TextInput("Press enter to continue...");
        }

        void ClearSystem()
        {
			//Windows:
			if(operatingSystemConf == 0)
				system("CLS");

			//Linux:
			else
				std::cout << "\033[2J";
        }

        char CharInput(std::string msg)
        {
            std::cout << msg;

            cInput = getchar();

            return cInput;
        }

        void CharsInput(std::string msg, char* aCInput, int size)
        {
            std::cout << msg;

            std::cin.getline(aCInput, size);
        }

        std::string TextInput(std::string msg)
        {
            std::cout << msg;

            getline(std::cin, uInput);

            return uInput;
        }

        double NumberInput(std::string msg)
        {
            std::cout << msg;

            getline(std::cin, uInput);
            stream.str(uInput);
            stream >> nInput;
            stream.clear();

            return nInput; 
        }

        double TextToNumber(std::string input)
        {
            stream.str(input);
            stream >> nInput;
            stream.clear();
            
            return nInput;
        }

        std::string NumberToText(double input)
        {
            return std::to_string(input);
        }

        char TextToChar(std::string input)
        {
            stream.str(input);
            stream >> cInput;
            stream.clear();

            return cInput;
        }

        // Latest Feature <3 || Should work on Windows and Linux (Not tested Linux yet)
        std::string ColorText(std::string input, int FG, int BG, int opt = 1)
        {
            return "\033[" + std::to_string(opt) + ";" + std::to_string(BG) + ";" + std::to_string(FG) + "m" + input + "\033[0m";
        }

        // Date Logic
        std::string GetStringDate()
        {
            // gets current time stamp
            time_t t = time(0);

            // gets local time based on machine configuration
            tm* localTime = new tm(); localtime_s(localTime, &t);

            // creates a date string "31/12/2000"
            return std::to_string(localTime->tm_mday) + "/" + std::to_string(1 + localTime->tm_mon) + "/" + std::to_string(1900 + localTime->tm_year);
        }

        int GetDay() 
        { 
            localTime = new tm();

            t = time(0);
            localtime_s(localTime, &t);

            return localTime->tm_mday;
        }

        int GetMonth()
        {
            localTime = new tm();

            t = time(0);
            localtime_s(localTime, &t);

            return 1 + localTime->tm_mon;
        }

        int GetYear()
        {
            localTime = new tm();

            t = time(0);
            localtime_s(localTime, &t);

            return 1900 + localTime->tm_year;
        }
};