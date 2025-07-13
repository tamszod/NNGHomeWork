#pragma once

// Project includes
#include "Task.h"
#include "StreetSegment.h"

// Standard library includes
#include <fstream>
#include <sstream>

Task::Task() 
	: _last_error(TaskError::None) 
{

}

bool Task::Read(const wchar_t* file_path) {

	if (!file_path || !*file_path)
	{
		_SetLastError(TaskError::FilePathError);
		return false;
	}

	std::wfstream file;

	file.open(file_path, std::ios::in);

	if (!file.is_open()) 
	{
		_SetLastError(TaskError::FileOpenError);
		return false;
	}

	std::wstring line;
	while (std::getline(file, line)) {
		size_t street_name_pos = 0, street_name_length = 0, 
			street_type_pos = 0, street_type_length = 0, 
			schemeleft_pos = 0, schemeleft_length = 0,
			fromleft_pos = 0, fromleft_length = 0, 
			toleft_pos = 0, toleft_length = 0, 
			schemeright_pos = 0, schemeright_length = 0, 
			fromright_pos = 0, fromright_length = 0, 
			toright_pos = 0, toright_length = 0; 

		// Read the line and extract positions and lengths of the required fields
		if (!_ReadLine(line, street_name_pos, street_name_length,
			street_type_pos, street_type_length,
			schemeleft_pos, schemeleft_length,
			fromleft_pos, fromleft_length,
			toleft_pos, toleft_length,
			schemeright_pos, schemeright_length,
			fromright_pos, fromright_length,
			toright_pos, toright_length)) 
		{
			continue;
		}

		// left street scheme
		std::wstring schemeleft = line.substr(schemeleft_pos, schemeleft_length);
		if (auto segment = _ParseSchemeAsStreetSegment(line, schemeleft, street_name_pos, 
			street_name_length,	street_type_pos, street_type_length, fromleft_pos, 
			fromleft_length, toleft_pos, toleft_length)) 
		{
			_segments.emplace_back(segment);
		}

		// right street scheme
		std::wstring schemeright = line.substr(schemeright_pos, schemeright_length);
		if (auto segment = _ParseSchemeAsStreetSegment(line, schemeright, street_name_pos, 
			street_name_length,	street_type_pos, street_type_length, fromright_pos, 
			fromright_length,	toright_pos, toright_length)) 
		{
			_segments.emplace_back(segment);
		}
	}

	for (auto& segment : _segments) 
	{
		segment->Print();
	}

	return true;
}

bool Task::_ReadLine(
	  const std::wstring& line
	, size_t& street_name_pos,	size_t& street_name_length //16 - 17
	, size_t& street_type_pos,	size_t& street_type_length // 17 - 18
	, size_t& schemeleft_pos,	size_t& schemeleft_length  // 20 - 21
	, size_t& fromleft_pos,		size_t& fromleft_length // 21 - 22
	, size_t& toleft_pos,		size_t& toleft_length // 22 - 23
	, size_t& schemeright_pos,	size_t& schemeright_length // 23 - 24
	, size_t& fromright_pos,	size_t& fromright_length // 24 - 25
	, size_t& toright_pos,		size_t& toright_length // 25 - 26
) {
	if (line.empty()) 
	{
		return false;
	}
	size_t comma_counter = 0;
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
	return comma_counter >= 26; // Successfuly read a line with all required fields
}

StreetSegment* Task::_ParseSchemeAsStreetSegment(
	  const std::wstring& line
	, const std::wstring& scheme
	, size_t street_name_pos
	, size_t street_name_length
	, size_t street_type_pos
	, size_t street_type_length
	, size_t from_pos
	, size_t from_length
	, size_t to_pos
	, size_t to_length
	) {
	StreetSegment* street_segment = nullptr;
	if (!scheme.empty()) {
		std::wstring street = line.substr(street_name_pos, street_name_length)
			+ L" "
			+ line.substr(street_type_pos, street_type_length);
		int from = std::stoi(line.substr(from_pos, from_length));
		int to = std::stoi(line.substr(to_pos, to_length));
		if (scheme == L"E") {
			street_segment = StreetSegment::CreateEven(std::move(street), from, to);
		}
		else if (scheme == L"O") {
			street_segment = StreetSegment::CreateOdd(std::move(street), from, to);
		}
		else if (scheme == L"M") {
			street_segment = StreetSegment::CreateMixed(std::move(street), from, to);
		}
	}
	return street_segment;
}

bool Task::Solve() {
	_SetLastError(TaskError::UnimplementedError);
	return false;
}

TaskError Task::GetLastError() const {
	return _last_error;
}

bool Task::Clear() {
	_segments.clear();
	_last_error = TaskError::None;
	return true;
}

void Task::_SetLastError(TaskError error) {
	_last_error = error;
}