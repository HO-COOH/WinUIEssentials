#include "pch.h"
#include "ModernMessageBoxPage.xaml.h"
#if __has_include("ModernMessageBoxPage.g.cpp")
#include "ModernMessageBoxPage.g.cpp"
#endif


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    winrt::hstring ModernMessageBoxPage::ClassicMessageBoxOutput()
    {
        switch (m_classicMessageBoxReturn)
        {
			case IDABORT: return L"IDABORT";
			case IDCANCEL: return L"IDCANCEL";
			case IDCONTINUE: return L"IDCONTINUE";
			case IDIGNORE: return L"IDIGNORE";
			case IDNO: return L"IDNO";
			case IDOK: return L"IDOK";
			case IDRETRY: return L"IDRETRY";
			case IDTRYAGAIN: return L"IDTRYAGAIN";
			case IDYES: return L"IDYES";
			default: return L"Unknown Return Value";
        }
    }


	void ModernMessageBoxPage::Button_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		classicMessageBoxReturn(MessageBoxW(
			NULL,
			L"This is a classic message box from WinUI3 Example.",
			L"Classic Message Box",
			getClassicMessageBoxFlags()
		));
	}

	UINT ModernMessageBoxPage::getClassicMessageBoxFlags()
	{
		return getClassicMessageBoxButtons(ClassicMessageBoxButtonsSelction().SelectedIndex()) 
			| getClassicMessageBoxIcon(ClassicMessageBoxIconSelection().SelectedIndex()) 
			| getClassicMessageBoxDefaultButton(ClassicMessageBoxDefaultButtonSelection().SelectedIndex());
	}

	UINT ModernMessageBoxPage::getClassicMessageBoxButtons(int selection)
	{
		switch (selection)
		{
			case 0: return MB_ABORTRETRYIGNORE;
			case 1: return MB_CANCELTRYCONTINUE;
			case 2: return MB_HELP;
			case 3: return MB_OK;
			case 4: return MB_OKCANCEL;
			case 5: return MB_RETRYCANCEL;
			case 6: return MB_YESNO;
			case 7: return MB_YESNOCANCEL;
			default: throw winrt::hresult_invalid_argument(L"Invalid selection for ClassicMessageBoxButtonsSelection.");
		}
	}

	UINT ModernMessageBoxPage::getClassicMessageBoxIcon(int selection)
	{
		switch (selection)
		{
			case 0: return MB_ICONEXCLAMATION;
			case 1: return MB_ICONWARNING;
			case 2: return MB_ICONINFORMATION;
			case 3: return MB_ICONASTERISK;
			case 4: return MB_ICONQUESTION;
			case 5: return MB_ICONSTOP;
			case 6: return MB_ICONERROR;
			case 7: return MB_ICONHAND;
			default: return {};
		}
	}

	UINT ModernMessageBoxPage::getClassicMessageBoxDefaultButton(int selection)
	{
		switch(selection)
		{
			case 0: return MB_DEFBUTTON1;
			case 1: return MB_DEFBUTTON2;
			case 2: return MB_DEFBUTTON3;
			case 3: return MB_DEFBUTTON4;
			default: throw winrt::hresult_invalid_argument(L"Invalid selection for ClassicMessageBoxDefaultButtonSelection.");
		}
	}

	void ModernMessageBoxPage::classicMessageBoxReturn(int value)
	{
		if(m_classicMessageBoxReturn != value)
		{
			m_classicMessageBoxReturn = value;
			raisePropertyChange(L"ClassicMessageBoxOutput");
		}
	}


	void ModernMessageBoxPage::Button_Click_1(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Package::ModernMessageBox::ShowAsync(
			nullptr,
			L"This is a modern message box from WinUI3 Example.",
			L"Modern Message Box",
			getClassicMessageBoxFlags()
		);
	}

}
