#pragma once

namespace winrt::PackageRoot::implementation
{
	struct Table;
}

class TableOverlayManager
{
	//winrt::WinUINamespace::UI::Xaml::Controls::Canvas m_canvas{ nullptr };
	winrt::WinUINamespace::UI::Xaml::Controls::UIElementCollection m_canvasChildren{ nullptr };
	winrt::PackageRoot::implementation::Table& m_table;
	int m_row = 0;
public:
	TableOverlayManager(winrt::PackageRoot::implementation::Table& table);

	void OnInitializedComponent();

	void SetCellContent(
		int row,
		int column,
		winrt::Windows::Foundation::IInspectable const& cellObject
	);
};