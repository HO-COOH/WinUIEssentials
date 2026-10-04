#pragma once

class CaptionButton
{
public:

	enum Value
	{
		None,
		Minimize,
		Maximize,
		Close
	};

	constexpr CaptionButton(Value v) : m_value{ v } {}
	constexpr operator Value() const noexcept { return m_value; }

	constexpr static CaptionButton FromHitTest(LRESULT hitTest)
	{
		switch (hitTest)
		{
			case HTMINBUTTON:   return CaptionButton::Minimize;
			case HTMAXBUTTON:   return CaptionButton::Maximize;
			case HTCLOSE:       return CaptionButton::Close;
			default:            return CaptionButton::None;
		}
	}

	[[nodiscard]] bool IsEnabled(HWND hwnd) const;
private:
	Value m_value;
};