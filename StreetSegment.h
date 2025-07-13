#pragma once

// Project includes
#include "StreetAddresses.h"

// Standard library includes
#include <cstdint>
#include <string>
#include <set>
#include <map>

class OddStreetSegment;
class EvenStreetSegment;
class MixedStreetSegment;

class StreetSegment {
public:
	static OddStreetSegment* CreateOdd(std::wstring&& street_name, uint16_t from, uint16_t to);

	static EvenStreetSegment* CreateEven(std::wstring&& street_name, uint16_t from, uint16_t to);

	static MixedStreetSegment* CreateMixed(std::wstring&& street_name, uint16_t from, uint16_t to);

	/*
	 * @brief Inserts a street segment into a street addresses.
	 * 
	 * @param street_addresses The map of street addresses to insert into.
	 * 
	 * @return None.
	 */
	virtual void InsertTo(StreetAddresses& street_addresses) = 0;

	void Print() const;

	inline bool IsOddSequence() const { return false; };
	inline OddStreetSegment* AsOddSequence() { return nullptr; };
	inline bool IsEvenSequence() const { return false; };
	inline EvenStreetSegment* AsEvenSequence() { return nullptr; };
	inline bool IsMixedSequence() const { return false; };
	inline MixedStreetSegment* AsMixedSequence() { return nullptr; };

	virtual inline wchar_t const GetType() const = 0;

	virtual ~StreetSegment() {};

protected:
	StreetSegment(std::wstring&& street_name, uint16_t from, uint16_t to);

private:
	std::wstring _street_name;
	uint16_t _from;
	uint16_t _to;
};

class OddStreetSegment : public StreetSegment {
public:
	static OddStreetSegment* Create(std::wstring&& street_name, uint16_t from, uint16_t to);

	virtual void InsertTo(StreetAddresses& street_addresses) override;
	inline bool IsOddSequence() const { return true; };
	inline OddStreetSegment* AsOddSequence() { return this; };
	virtual inline wchar_t const GetType() const override { return L'O'; };
	virtual ~OddStreetSegment() {};

protected:
	OddStreetSegment(std::wstring&& street_name, uint16_t from, uint16_t to);
};

class EvenStreetSegment : public StreetSegment {
public:
	static EvenStreetSegment* Create(std::wstring&& street_name, uint16_t from, uint16_t to);

	virtual void InsertTo(StreetAddresses& street_addresses) override;
	inline bool IsEvenSequence() const { return true; };
	inline EvenStreetSegment* AsEvenSequence() { return this; };
	virtual inline wchar_t const GetType() const override { return L'E'; };
	virtual ~EvenStreetSegment() {};
protected:
	EvenStreetSegment(std::wstring&& street_name, uint16_t from, uint16_t to);
};

class MixedStreetSegment : public StreetSegment {
public:
	static MixedStreetSegment* Create(std::wstring&& street_name, uint16_t from, uint16_t to);

	virtual void InsertTo(StreetAddresses& street_addresses) override;
	virtual inline wchar_t const GetType() const override { return L'M'; };
	inline bool IsMixedSequence() const { return true; };
	inline MixedStreetSegment* AsMixedSequence() { return this; };
	virtual ~MixedStreetSegment() {};
protected:
	MixedStreetSegment(std::wstring&& street_name, uint16_t from, uint16_t to);
};