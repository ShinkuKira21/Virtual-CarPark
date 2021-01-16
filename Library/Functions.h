//Windows/Linux commands // Author: Edward Patch

#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Functions 
{
    protected:
		// 0 = Windows, 1 = Linux
		const int operatingSystemConf = 0;
        std::stringstream stream;
        std::string uInput;
        char cInput;
        double nInput;
        
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
};