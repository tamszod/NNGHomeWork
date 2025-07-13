#pragma once

// Standard library includes
#include <map>
#include <string>
#include <set>

typedef std::map<std::wstring // street name
	, std::pair<std::set<std::uint16_t> // addresses
	, std::set<std::uint16_t>>>  // duplicate addresses
	StreetAddresses;