#pragma once
#include <winrt/Microsoft.UI.Xaml.Data.h>
namespace MvvmHelper
{
	/**
	 * @brief Helper class for supporting `INotifyPropertyChanged`
	 * @tparam Self Should be the implementation type
	 * @code{.cpp}
	 *     struct MyViewModel : MyViewModelT<MyViewModel>, MvvmHelper::PropertyCHangeHelper<MyViewModel>
	 * @endcode
	*/
	template<typename Self>
	class PropertyChangeHelper
	{
	public:
#pragma region EventBoilerPlate
		winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& value)
		{
			return m_propertyChanged.add(value);
		}

		void PropertyChanged(winrt::event_token const& token)
		{
			m_propertyChanged.remove(token);
		}
#pragma endregion

		/**
		 * @brief raise ProperyChanged event for a property name
		 * @param propertyName Name of the property
		*/
		void raisePropertyChange(wchar_t const* propertyName)
		{
			m_propertyChanged(*(static_cast<Self*>(this)), winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ propertyName });
		}

		/**
		 * @brief Compare the current property value to `newValue` and raise the PropertyChange event conditionally
		 * @tparam T Type of the value
		 * @param property The property
		 * @param newValue
		 * @param propertyName Name of the property
		*/
		template<typename T>
		void compareAndRaise(auto& property, T&& newValue, wchar_t const* propertyName)
		{
			if (property != newValue)
			{
				property = std::forward<T>(newValue);
				raisePropertyChange(propertyName);
			}
		}
	private:
		winrt::event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
	};
}