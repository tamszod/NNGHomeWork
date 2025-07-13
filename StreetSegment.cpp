#pragma once

// Project includes
#include "StreetSegment.h"
#include "Task.h"

// Standard library includes
#include <string>
#include <format>
#include <iostream>

StreetSegment::StreetSegment(std::wstring&& street_name, uint16_t from, uint16_t to)
	: _street_name(std::move(street_name))
	, _from(from)
	, _to(to)
{

}

void StreetSegment::Print() const {
	std::wcout << std::format(L"{}: {} {} {}", _street_name, GetType(), _from, _to) << std::endl;
}

OddStreetSegment* StreetSegment::CreateOdd(std::wstring&& street_name, uint16_t from, uint16_t to)
{
	return OddStreetSegment::Create(std::move(street_name), from, to);
}

OddStreetSegment* OddStreetSegment::Create(std::wstring&& street_name, uint16_t from, uint16_t to)
{
	if (street_name.empty()) {
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
	if (street_name.empty()) {
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
	if (street_name.empty()) {
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

}


void OddStreetSegment::InsertTo(StreetAddresses& street_addresses) 
{

}

void MixedStreetSegment::InsertTo(StreetAddresses& street_addresses) 
{

}
