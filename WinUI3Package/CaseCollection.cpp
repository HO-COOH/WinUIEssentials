#include "pch.h"
#include "CaseCollection.h"
#if __has_include("CaseCollection.g.cpp")
#include "CaseCollection.g.cpp"
#endif
#include "ObjectCompare.h"

namespace winrt::WinUI3Package::implementation
{
	WinUI3Package::Case CaseCollection::EvaluateCases(winrt::Windows::Foundation::IInspectable const& value)
	{
		WinUI3Package::Case defaultCase{ nullptr };

		for (auto const& d : *this)
		{
			auto const& currentCase = d.as<WinUI3Package::Case>();
			if (currentCase.IsDefault())
			{
				if (defaultCase)
					throw winrt::hresult_invalid_argument(L"Multiple default cases found in CaseCollection");

				defaultCase = currentCase;
				continue;
			}

			if (internal::ConvertTypeEquals(currentCase.Value(), value))
				return currentCase;
		}

		if (!defaultCase)
			throw winrt::hresult_invalid_argument(L"No matched cases and no default case");
		return defaultCase;
	}
}
