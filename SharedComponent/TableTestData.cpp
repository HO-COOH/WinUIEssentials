#include "pch.h"
#include "TableTestData.hpp"

std::wstring TableTestData::Data::operator[](int column)
{
    switch (column)
    {
        case 0: // Id
            return std::to_wstring(m_row + 1).c_str();
        case 1: // First Name
            return FirstNames[std::uniform_int_distribution{ 0ull, std::size(FirstNames) -1 }(m_parent.m_eng)];
        case 2: // Last Name
            return LastNames[std::uniform_int_distribution{ 0ull, std::size(FirstNames) -1 }(m_parent.m_eng)];
        case 3: // Email
        {
            auto const rnd = std::uniform_int_distribution{ 0ull, std::size(FirstNames) -1 }(m_parent.m_eng);
            return std::format(L"{}.{}@example.com", FirstNames[rnd], LastNames[rnd]);
        }
		case 4: // Gender
			return Genders[std::uniform_int_distribution{ 0ull, std::size(Genders) -1 }(m_parent.m_eng)];
        case 5: // Dob
        {
            auto const year = std::uniform_int_distribution{ 1950, 2000 }(m_parent.m_eng);
            auto const month = std::uniform_int_distribution{ 1, 12 }(m_parent.m_eng);
            auto const day = std::uniform_int_distribution{ 1, 28 }(m_parent.m_eng);
            return std::format(L"{:02}/{:02}/{}", month, day, year);
		}
        case 6: // Active At
        {
            auto const hour = std::uniform_int_distribution{ 0, 23 }(m_parent.m_eng);
            auto const minute = std::uniform_int_distribution{ 0, 59}(m_parent.m_eng);
            return std::format(L"{}:{:02}", hour, minute);
		}
        case 7: // Is Active
			return m_parent.m_eng() % 2 == 0 ? L"Yes" : L"No";
		case 8: // Department
			return Departments[std::uniform_int_distribution{ 0ull, std::size(Departments) - 1 }(m_parent.m_eng)];
		case 9: // Designation
			return JobTitles[std::uniform_int_distribution{ 0ull, std::size(JobTitles) - 1 }(m_parent.m_eng)];
		case 10: // Address
        {
			auto streetNumber = std::uniform_int_distribution{ 1, 9999 }(m_parent.m_eng);
            auto streetName = FirstNames[std::uniform_int_distribution{ 0ull, std::size(FirstNames) - 1 }(m_parent.m_eng)];
			auto suffix = StreetSuffixes[std::uniform_int_distribution{ 0ull, std::size(StreetSuffixes) - 1 }(m_parent.m_eng)];
			auto city = Cities[std::uniform_int_distribution{ 0ull, std::size(Cities) - 1 }(m_parent.m_eng)];
			auto state = States[std::uniform_int_distribution{ 0ull, std::size(States) - 1 }(m_parent.m_eng)];
			auto zip = std::uniform_int_distribution{ 10000, 99999 }(m_parent.m_eng);
			return std::format(L"{} {} {}, {}, {} {}", streetNumber, streetName, suffix, city, state, zip);
        }
        default:
            return L"Other data";
    }
}
