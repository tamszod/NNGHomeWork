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
	enum class Type {
		Undefined = 0,
		Odd,
		Even,
		Mixed,
		Last
	};

	static OddStreetSegment* CreateOdd(std::wstring&& street_name, uint16_t from, uint16_t to);

	static EvenStreetSegment* CreateEven(std::wstring&& street_name, uint16_t from, uint16_t to);

	static MixedStreetSegment* CreateMixed(std::wstring&& street_name, uint16_t from, uint16_t to);

	static StreetSegment* Create(std::wstring street_name, StreetSegment::Type type, uint16_t from, uint16_t to);


	class Utils {
	public:
		/*
		 * @brief Converts a StreetSegment::Type to a wide character representation.
		 * 
		 * @param type The type to convert.
		 * 
		 * @return The wide character representation of the type.
		 */
		static inline const wchar_t& GetTypeW(StreetSegment::Type type);

		/*
		 * @brief Formats a street segment into a wide string.
		 *
		 * @param street_name The name of the street.
		 * @param type The type of the street segment.
		 * @param form The starting address of the segment.
		 * @param to The ending address of the segment.
		 *
		 * @return A formatted string representing the street segment.
		 */
		static inline std::wstring Format(const std::wstring& street_name, const wchar_t& type, uint16_t form, uint16_t to);

	private:
		inline static constexpr const wchar_t* _TypeNameCast = L" OEM";
	};


	/*
	 * @brief Inserts a street segment into the street address sets.
	 * 
	 * @param street_addresses The map of street addresses to insert into.
	 * 
	 * @return None.
	 */
	virtual void InsertTo(StreetAddresses& street_addresses) = 0;

	/*
	 * @brief Prints the street segment to standard output.
	 * 
	 * @return None.
	 */
	void Print() const;

	inline bool IsOddSequence() const { return false; };
	inline OddStreetSegment* AsOddSequence() { return nullptr; };
	inline bool IsEvenSequence() const { return false; };
	inline EvenStreetSegment* AsEvenSequence() { return nullptr; };
	inline bool IsMixedSequence() const { return false; };
	inline MixedStreetSegment* AsMixedSequence() { return nullptr; };

	virtual inline wchar_t const GetType() const = 0;
	inline const std::wstring& GetStreetName() const { return _street_name; };
	inline const uint16_t GetFrom() const { return _from; };
	inline const uint16_t GetTo() const { return _to; };

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
	virtual inline wchar_t const GetType() const override { return StreetSegment::Utils::GetTypeW(StreetSegment::Type::Odd); };
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
	virtual inline wchar_t const GetType() const override { return StreetSegment::Utils::GetTypeW(StreetSegment::Type::Even); };
	virtual ~EvenStreetSegment() {};
protected:
	EvenStreetSegment(std::wstring&& street_name, uint16_t from, uint16_t to);
};

class MixedStreetSegment : public StreetSegment {
public:
	static MixedStreetSegment* Create(std::wstring&& street_name, uint16_t from, uint16_t to);

	virtual void InsertTo(StreetAddresses& street_addresses) override;
	virtual inline wchar_t const GetType() const override { return StreetSegment::Utils::GetTypeW(StreetSegment::Type::Mixed); };
	inline bool IsMixedSequence() const { return true; };
	inline MixedStreetSegment* AsMixedSequence() { return this; };
	virtual ~MixedStreetSegment() {};
protected:
	MixedStreetSegment(std::wstring&& street_name, uint16_t from, uint16_t to);
};