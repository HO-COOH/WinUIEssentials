#pragma once

#include "CodeSource.g.h"
#include <functional>

namespace winrt::PackageRoot::implementation
{
    struct CodeSource : CodeSourceT<CodeSource>
    {
        CodeSource();

        winrt::hstring Code();
        void Code(winrt::hstring const& value);

        winrt::Windows::Foundation::Uri CodeUrl();
        void CodeUrl(winrt::Windows::Foundation::Uri const& value);

        winrt::Windows::Foundation::Uri FileUri();
        void FileUri(winrt::Windows::Foundation::Uri const& value);

        winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::ControlExampleSubstitution> Substitutions();

        std::function<void(std::wstring const& value)> ValueChanged;
        std::wstring FormatCode();

        winrt::PackageRoot::Language CodeLanguage();
        
        winrt::PackageRoot::Language m_codeLanguage;
    private:
        winrt::hstring m_code;
        winrt::Windows::Foundation::Uri m_codeUrl{ nullptr };
        winrt::Windows::Foundation::Uri m_fileUri{ nullptr };
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::PackageRoot::ControlExampleSubstitution> m_substitutions = winrt::single_threaded_observable_vector<winrt::PackageRoot::ControlExampleSubstitution>();

        template<typename String, typename... Args>
        static auto vFormat(String&& code, Args&&... args)
        {
            return std::vformat(code, std::make_wformat_args(args...));
        }
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct CodeSource : CodeSourceT<CodeSource, implementation::CodeSource>
    {
    };
}
