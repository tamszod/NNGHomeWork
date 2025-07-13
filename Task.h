#pragma once

// Project includes
#include "StreetSegment.h"

// Standard library includes
#include <vector>
#include <memory>

enum class TaskError {
	None,
	FilePathError,
	FileOpenError,
	UnimplementedError,
	ErrorCount
};

class Task {

public:
	Task();

	bool Read(const wchar_t* file_path);

	bool Solve();

	TaskError GetLastError() const;

	bool Clear();

	~Task() { Clear(); }

private:
	void _SetLastError(TaskError error);

	// Helpers for Reading
	bool _ReadLine(const std::wstring& line, size_t& street_name_pos, size_t& street_name_length, size_t& street_type_pos, 
		size_t& street_type_length, size_t& schemeleft_pos, size_t& schemeleft_length, size_t& fromleft_pos, size_t& fromleft_length, 
		size_t& toleft_pos, size_t& toleft_length, size_t& schemeright_pos, size_t& schemeright_length, size_t& fromright_pos, 
		size_t& fromright_length, size_t& toright_pos, size_t& toright_length);

	StreetSegment* _ParseSchemeAsStreetSegment(const std::wstring& line, const std::wstring& scheme, size_t street_name_pos,
		size_t street_name_length, size_t street_type_pos, size_t street_type_length, size_t from_pos,
		size_t from_length, size_t to_pos, size_t to_length);

	std::vector <std::unique_ptr<StreetSegment>> _segments;
	TaskError _last_error;
};