#pragma once
#include <string>
#include <random>
#include <dwrite.h>

class TableTestData
{
    // First names
    static constexpr wchar_t const* FirstNames[] =
    {
        L"James", L"Mary", L"Robert", L"Patricia", L"Michael", L"Jennifer", L"William", L"Linda", L"David", L"Barbara",
        L"Richard", L"Elizabeth", L"Joseph", L"Susan", L"Thomas", L"Jessica", L"Charles", L"Sarah", L"Christopher", L"Karen",
        L"Daniel", L"Nancy", L"Matthew", L"Lisa", L"Anthony", L"Betty", L"Mark", L"Margaret", L"Donald", L"Sandra",
        L"Steven", L"Ashley", L"Paul", L"Kimberly", L"Andrew", L"Donna", L"Joshua", L"Carol", L"Kenneth", L"Michelle",
        L"Kevin", L"Emily", L"Brian", L"Melissa", L"George", L"Deborah", L"Edward", L"Stephanie", L"Ronald", L"Rebecca",
        L"Timothy", L"Sharon", L"Jason", L"Brenda", L"Jeffrey", L"Amber", L"Ryan", L"Anna", L"Jacob", L"Pamela",
        L"Gary", L"Nicole", L"Nicholas", L"Emma", L"Eric", L"Helen", L"Jonathan", L"Samantha", L"Stephen", L"Katherine"
    };

    // Last names
    static constexpr wchar_t const* LastNames[] =
    {
        L"Smith", L"Johnson", L"Williams", L"Brown", L"Jones", L"Garcia", L"Miller", L"Davis", L"Rodriguez", L"Martinez",
        L"Hernandez", L"Lopez", L"Gonzalez", L"Wilson", L"Anderson", L"Thomas", L"Taylor", L"Moore", L"Jackson", L"Martin",
        L"Lee", L"Perez", L"Thompson", L"White", L"Harris", L"Sanchez", L"Clark", L"Ramirez", L"Lewis", L"Robinson",
        L"Walker", L"Young", L"Allen", L"King", L"Wright", L"Scott", L"Torres", L"Peterson", L"Phillips", L"Campbell",
        L"Parker", L"Evans", L"Edwards", L"Collins", L"Reyes", L"Stewart", L"Morris", L"Morales", L"Murphy", L"Cook",
        L"Rogers", L"Morgan", L"Peterson", L"Cooper", L"Reed", L"Bell", L"Gomez", L"Murray", L"Freeman", L"Wells",
        L"Webb", L"Simpson", L"Stevens", L"Tucker", L"Porter", L"Hunter", L"Hicks", L"Crawford", L"Henry", L"Boyd"
    };

    // Job titles
    static constexpr wchar_t const* JobTitles[] =
    {
        L"Software Developer", L"Manager", L"Sales Representative", L"Accountant", L"Analyst",
        L"Engineer", L"Designer", L"Teacher", L"Consultant", L"Executive",
        L"Administrator", L"Coordinator", L"Director", L"Supervisor", L"Specialist",
        L"Technician", L"Operator", L"Clerk", L"Assistant", L"Officer",
        L"Agent", L"Associate", L"Architect", L"Planner", L"Scientist",
        L"Researcher", L"Programmer", L"Nurse", L"Doctor", L"Lawyer",
        L"Marketing Manager", L"Product Manager", L"Business Analyst", L"Data Scientist", L"DevOps Engineer"
    };

    // Department names
    static constexpr wchar_t const* Departments[] =
    {
        L"Sales", L"Marketing", L"Engineering", L"Finance", L"Human Resources",
        L"Operations", L"IT", L"Legal", L"Research", L"Development",
        L"Quality Assurance", L"Customer Service", L"Production", L"Logistics", L"Planning",
        L"Maintenance", L"Administration", L"Strategic Planning", L"Corporate Communications", L"Treasury"
    };

    // Street suffixes
    static constexpr wchar_t const* StreetSuffixes[] =
    {
        L"Street", L"Avenue", L"Road", L"Boulevard", L"Drive", L"Lane", L"Court", L"Circle",
        L"Way", L"Parkway", L"Plaza", L"Square", L"Trail", L"Ridge", L"Hill", L"Oak"
    };

    // Cities
    static constexpr wchar_t const* Cities[] =
    {
        L"New York", L"Los Angeles", L"Chicago", L"Houston", L"Phoenix",
        L"Philadelphia", L"San Antonio", L"San Diego", L"Dallas", L"San Jose",
        L"Austin", L"Jacksonville", L"Seattle", L"Denver", L"Boston",
        L"Portland", L"Miami", L"Atlanta", L"Las Vegas", L"Detroit"
    };

    // States
    static constexpr wchar_t const* States[] =
    {
        L"AL", L"AK", L"AZ", L"AR", L"CA", L"CO", L"CT", L"DE", L"FL", L"GA",
        L"HI", L"ID", L"IL", L"IN", L"IA", L"KS", L"KY", L"LA", L"ME", L"MD",
        L"MA", L"MI", L"MN", L"MS", L"MO", L"MT", L"NE", L"NV", L"NH", L"NJ",
        L"NM", L"NY", L"NC", L"ND", L"OH", L"OK", L"OR", L"PA", L"RI", L"SC",
        L"SD", L"TN", L"TX", L"UT", L"VT", L"VA", L"WA", L"WV", L"WI", L"WY"
    };

    static constexpr wchar_t const* Regions[] =
    {
        L"East", L"West", L"North", L"South"
    };

    // Genders
    static constexpr wchar_t const* Genders[] =
    {
        L"Male", L"Female", L"Non-binary", L"Genderfluid", L"Agender",
        L"Bigender", L"Genderqueer", L"Two-Spirit", L"Prefer not to say"
    };

    // Avatar seeds
    static constexpr wchar_t const* AvatarSeeds[] =
    {
        L"avatar1", L"avatar2", L"avatar3", L"avatar4", L"avatar5",
        L"avatar6", L"avatar7", L"avatar8", L"avatar9", L"avatar10"
    };

	std::mt19937 m_eng{ std::random_device{}() };
public:
    static constexpr wchar_t const* Columns[] =
    {
        L"Id", L"First Name", L"Last Name", L"Email", L"Gender", L"Dob", L"Active At", L"Is Active",
        L"Department", L"Designation", L"Address"
    };

    class Data
    {
        TableTestData& m_parent;
        int m_row;
    public:
        constexpr Data(TableTestData& parent, int row) : m_parent{parent}, m_row{row}
        {
        }

        std::wstring operator[](int column);
    };

    struct Header
    {
        struct Column
        {
            wchar_t const* Content;
			DWRITE_TEXT_ALIGNMENT HorizontalAlignment;
			DWRITE_PARAGRAPH_ALIGNMENT VerticalAlignment = DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
        };

        constexpr Column operator[](int column) const
        {
            return Column{ TableTestData::Columns[column], column == 0 ? DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER : DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING };
		}
    };

    friend class Data;

    constexpr Data operator[](int row)
    {
        return Data{*this, row};
    }

    constexpr Header Header() const
    {
        return {};
    }

    constexpr int Count() const
    {
        return static_cast<int>((std::min)({
            std::size(TableTestData::FirstNames),
            std::size(TableTestData::LastNames),
            std::size(TableTestData::Departments),
        }));
    }
};