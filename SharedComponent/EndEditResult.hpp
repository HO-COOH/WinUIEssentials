#pragma once

struct EndEditResult
{
	int displayRow{ -1 };			//display row
	int sourceRow{ -1 };
	int column{ -1 };
	winrt::Windows::Foundation::IInspectable value;
	bool changed{};
	bool isString{};
};
