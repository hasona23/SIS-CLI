#pragma once
#include <iostream>
using namespace std;


static const char ASCII_BOTTOM_RIGHT_CORNER = 188;
static const char ASCII_TOP_LEFT_CORNER = 201;
static const char ASCII_TOP_RIGHT_CORNER = 187;
static const char ASCII_VERTICAL_LINE = 186;
static const char ASCII_HORIZONTAL_LINE = 205;
static const char ASCII_BOTTOM_LEFT_CORNER = 200;

inline static void PressEnterPause()
{
	std::cout << "Press Enter to Continue...";
	std::cin.ignore();
	std::cin.get();
}
inline static void DisplayTitle(const char title[]) {
	int space = 7;
	int length = strlen(title);
	cout << ASCII_TOP_LEFT_CORNER;
	for (int i = 0; i < 14 + length; i++) cout << ASCII_HORIZONTAL_LINE;
	cout << ASCII_TOP_RIGHT_CORNER << '\n' << ASCII_VERTICAL_LINE;
	for (int i = 0; i < 7; i++) cout << " ";
	cout << title;
	for (int i = 0; i < 7; i++) cout << " ";
	cout << ASCII_VERTICAL_LINE << '\n' << ASCII_BOTTOM_LEFT_CORNER;
	for (int i = 0; i < 14 + length; i++) cout << ASCII_HORIZONTAL_LINE;
	cout << ASCII_BOTTOM_RIGHT_CORNER << '\n' << '\n';

}
inline static void RemoveSpaces(char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == ' ')
		{
			for (int j = i; j < strlen(str); j++)
			{
				str[j] = str[j + 1];
			}
			i--;
		}
	}
}
inline static void RemoveSpaces(std::string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			for (int j = i; j < str.length(); j++)
			{
				str[j] = str[j + 1];
			}
			i--;
		}
	}
}