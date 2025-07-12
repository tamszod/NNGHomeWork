// NNGHomeWork.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <locale>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <array>
#include <string_view>
#include <array>
#include <ranges>

const wchar_t* PARITY_SCHEMES[] = {L"M", L"O", L"E"};
#define arraylen(a) (sizeof(a) / sizeof((a)[0]))

int main()
{	
	setlocale(LC_ALL, "Hungarian_Hungary.1250"); // Set character encoding to Hungarian (Windows-1250)

	// Read the CSV file
	std::wfstream file;
	file.open(L"D:\\NNGHomeWork\\x64\\Debug\\network.csv", std::ios::in);
	if (!file.is_open()) {
		return 1;
	}

	std::vector<std::wstring> raw_data_list;
	std::wstring line;
	while (std::getline(file, line)) {
		if (line.empty()) continue;
		size_t street_name_pos = 0, street_name_length = 0, //16 - 17 // S
			street_type_pos = 0, street_type_length = 0, // 17 - 18
			schemeleft_pos = 0, schemeleft_length = 0, // 20 - 21
			fromleft_pos = 0, fromleft_length = 0, // 21 - 22
			toleft_pos = 0, toleft_length = 0, // 22 - 23
			schemeright_pos = 0, schemeright_length = 0, // 23 - 24
			fromright_pos = 0, fromright_length = 0, // 24 - 25
			toright_pos = 0, toright_length = 0, // 25 - 26
			comma_counter = 0; 
		for (size_t i = 0; i < line.size() && comma_counter < 26; ++i) {
			if (line[i] == L',') {
				comma_counter++;
				switch (comma_counter) {
					case 16: {
						street_name_pos = i + 2;
						break;
					}
					case 17: {
						street_name_length = i - street_name_pos - 1;
						street_type_pos = i + 2;
						break;
					}
					case 18: {
						street_type_length = i - street_type_pos - 1;
						break;
					}
					case 20: {
						schemeleft_pos = i + 2;
						break;
					}
					case 21: {
						schemeleft_length = i - schemeleft_pos - 1;
						fromleft_pos = i + 1;
						break;
					}
					case 22: {
						fromleft_length = i - fromleft_pos;
						toleft_pos = i + 1;
						break;
					}
					case 23: {
						toleft_length = i - toleft_pos;
						schemeright_pos = i + 2;
						break;
					}
					case 24: {
						schemeright_length = i - schemeright_pos - 1;
						fromright_pos = i + 1;
						break;
					}
					case 25: {
						fromright_length = i - fromright_pos;
						toright_pos = i + 1;
						break;
					}
					case 26: {
						toright_length = i - toright_pos;
						break;
					}
				}
			}
		}
		std::wstring schemeleft = line.substr(schemeleft_pos, schemeleft_length);
		std::wstring schemeright = line.substr(schemeright_pos, schemeright_length);
		size_t i = 0;
		while (i < arraylen(PARITY_SCHEMES)) {
			if (schemeleft == PARITY_SCHEMES[i] || schemeright == PARITY_SCHEMES[i]) {
				break;
			}
			++i;
		}
		if (i >= arraylen(PARITY_SCHEMES)) {
			continue;
		}

		std::wstring street = line.substr(street_name_pos, street_name_length) 
			+ L" " 
			+ line.substr(street_type_pos, street_type_length);
		std::wstring fromleft = line.substr(fromleft_pos, fromleft_length);
		std::wstring toleft = line.substr(toleft_pos, toleft_length);
		std::wstring fromright = line.substr(fromright_pos, fromright_length);
		std::wstring toright = line.substr(toright_pos, toright_length);
		std::wcout << street << L" "
			<< schemeleft << L" " << fromleft << L", " << toleft << L"; " << schemeright
			<< L" " << fromright << L", " << toright << std::endl;

	}

	//std::unordered_map<wchar_t[50+1+20] /*Street Name*/, std::set<uint16_t> /*Addresses*/> street_map;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
