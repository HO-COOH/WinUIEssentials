#pragma once
#include <variant>
#include "TableCellDataWrapper.h"
#include "EndEditResult.hpp"

class TableD2DContent;

class EditControlOverlay
{
	int m_editingRow{ -1 };			//display row
	int m_editingSourceRow{ -1 };	//source row
	int m_editingColumn{ -1 };
	winrt::hstring m_previousContent;
	winrt::Windows::Foundation::IInspectable m_previousValue;
	winrt::PackageRoot::TableCellDataWrapper m_dataContext{ nullptr };
	winrt::weak_ref<winrt::WinUINamespace::UI::Xaml::FrameworkElement> m_editControl;
	bool m_isString{};
public:
	//`dataContext` becomes the control's DataContext, so an EditTemplate binds to
	//`Value` (TwoWay) the same way an ItemTemplate does; its setter calls ITableData::SetData.
	[[nodiscard]] winrt::WinUINamespace::UI::Xaml::FrameworkElement MakeControl(
		winrt::WinUINamespace::UI::Xaml::DataTemplate const& dataTemplate,
		winrt::PackageRoot::TableCellDataWrapper const& dataContext,
		bool isString,
		int row,
		int sourceRow,
		int column
	);

	//Commit the edit control's pending bindings, redraw a string cell with its final content,
	//and return the edit's outcome. The caller removes the control from Canvas.
	[[nodiscard]] EndEditResult Remove(TableD2DContent& d2dContent);
	operator bool() const;
};
