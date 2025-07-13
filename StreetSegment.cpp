#pragma once

// Project includes
#include "StreetSegment.h"
#include "Task.h"

// Standard library includes
#include <string>
#include <format>
#include <iostream>
#include <algorithm>
#include <cassert>

StreetSegment::StreetSegment(std::wstring&& street_name, uint16_t from, uint16_t to)
	: _street_name(std::move(street_name))
	, _from(from)
	, _to(to)
{

}

inline const wchar_t& StreetSegment::Utils::GetTypeW(StreetSegment::Type type) {
	size_t index = static_cast<size_t>(type);
	if (index >= static_cast<size_t>(StreetSegment::Type::Last)) {
		assert(false && "Type is out of bounds");
		return _TypeNameCast[0]; // Return the first element as a fallback
	}
	return StreetSegment::Utils::_TypeNameCast[index];
}

inline std::wstring StreetSegment::Utils::Format(const std::wstring& street_name, const wchar_t& type, uint16_t form, uint16_t to) {
	return std::format(L"{}: {} {} {}", street_name, type, form, to);
}

void StreetSegment::Print() const {
	std::wcout << StreetSegment::Utils::Format(_street_name, GetType(), _from, _to) << std::endl;
}

StreetSegment* StreetSegment::Create(std::wstring street_name, StreetSegment::Type type, uint16_t from, uint16_t to){
	switch (type) {
	case StreetSegment::Type::Odd:
		return CreateOdd(std::move(street_name), from, to);
	case StreetSegment::Type::Even:
		return CreateEven(std::move(street_name), from, to);
	case StreetSegment::Type::Mixed:
		return CreateMixed(std::move(street_name), from, to);
	default:
		return nullptr; // Undefined or Last type
	}
}

OddStreetSegment* StreetSegment::CreateOdd(std::wstring&& street_name, uint16_t from, uint16_t to)
{
	return OddStreetSegment::Create(std::move(street_name), from, to);
}

OddStreetSegment* OddStreetSegment::Create(std::wstring&& street_name, uint16_t from, uint16_t to)
{
	if (street_name.empty() && street_name == L" ") {
		return nullptr;
	}
	return new OddStreetSegment(std::move(street_name), from, to);
}

OddStreetSegment::OddStreetSegment(std::wstring&& street_name, uint16_t from, uint16_t to)
	: StreetSegment(std::move(street_name), from, to)
{

}

EvenStreetSegment* StreetSegment::CreateEven(std::wstring&& street_name, uint16_t from, uint16_t to)
{
	return EvenStreetSegment::Create(std::move(street_name), from, to);
}

EvenStreetSegment* EvenStreetSegment::Create(std::wstring&& street_name, uint16_t from, uint16_t to)
{
	if (street_name.empty()){

		return nullptr;
	}
	return new EvenStreetSegment(std::move(street_name), from, to);
}

EvenStreetSegment::EvenStreetSegment(std::wstring&& street_name, uint16_t from, uint16_t to)
	: StreetSegment(std::move(street_name), from, to)
{

}

MixedStreetSegment* StreetSegment::CreateMixed(std::wstring&& street_name, uint16_t from, uint16_t to)
{
	return MixedStreetSegment::Create(std::move(street_name), from, to);
}

MixedStreetSegment* MixedStreetSegment::Create(std::wstring&& street_name, uint16_t from, uint16_t to)
{
	if (street_name.empty() && street_name == L" ") {
		return nullptr;
	}
	return new MixedStreetSegment(std::move(street_name), from, to);
}

MixedStreetSegment::MixedStreetSegment(std::wstring&& street_name, uint16_t from, uint16_t to)
	: StreetSegment(std::move(street_name), from, to)
{

}

void EvenStreetSegment::InsertTo(StreetAddresses& street_addresses) 
{
	auto& [addresses, duplicates] = street_addresses[GetStreetName()];
	uint16_t from = GetFrom();
	uint16_t to = GetTo();
	if (from % 2 == 1) {
		from += 1;
	}
	for (uint16_t i = from; i <= to; i += 2) {
		auto result = addresses.insert(i);
		auto& it = result.first;
		auto is_included = !result.second;
		if (is_included) {
			duplicates.insert(i);
		}
	}
}

void OddStreetSegment::InsertTo(StreetAddresses& street_addresses) 
{
	auto& [addresses, duplicates] = street_addresses[GetStreetName()];
	uint16_t from = GetFrom();
	uint16_t to = GetTo();
	if (from % 2 == 0) {
		from += 1;
	}
	for (uint16_t i = from; i <= to; i += 2) {
		auto result = addresses.insert(i);
		auto& it = result.first;
		auto is_included = !result.second;
		if (is_included) {
			duplicates.insert(i);
		}
	}
}

void MixedStreetSegment::InsertTo(StreetAddresses& street_addresses) 
{
	auto& [addresses, duplicates] = street_addresses[GetStreetName()];
	uint16_t from = GetFrom();
	uint16_t to = GetTo();

	for (uint16_t i = from; i <= to; ++i) {
		auto result = addresses.insert(i);
		auto& it = result.first;
		auto is_included = !result.second;
		if (is_included) {
			duplicates.insert(i);
		}
	}

}
