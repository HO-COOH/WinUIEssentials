#include "pch.h"
#include "CodeSource.h"
#if __has_include("CodeSource.g.cpp")
#include "CodeSource.g.cpp"
#endif
#include "ControlExampleSubstitution.h"

namespace winrt::WinUI3Example::implementation
{
    CodeSource::CodeSource()
    {
        m_substitutions.VectorChanged([this](
            winrt::Windows::Foundation::Collections::IObservableVector<winrt::WinUI3Example::ControlExampleSubstitution> const& sender, 
            winrt::Windows::Foundation::Collections::IVectorChangedEventArgs const& arg)
        {
            if (arg.CollectionChange() == winrt::Windows::Foundation::Collections::CollectionChange::ItemInserted)
            {
                winrt::get_self<ControlExampleSubstitution>(sender.GetAt(arg.Index()))->ValueChanged = [this]() {
                    if (ValueChanged)
                        ValueChanged(formatCode());
                };
            }
        });
    }
    winrt::hstring CodeSource::Code()
    {
        return m_code;
    }
    void CodeSource::Code(winrt::hstring const& value)
    {
        m_code = value;
    }
    winrt::Windows::Foundation::Uri CodeSource::CodeUrl()
    {
        return m_codeUrl;
    }
    void CodeSource::CodeUrl(winrt::Windows::Foundation::Uri const& value)
    {
        m_codeUrl = value;
    }
    winrt::Windows::Foundation::Uri CodeSource::FileUri()
    {
        return m_fileUri;
    }
    void CodeSource::FileUri(winrt::Windows::Foundation::Uri const& value)
    {
        m_fileUri = value;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Example::ControlExampleSubstitution> CodeSource::Substitutions()
    {
        return m_substitutions;
    }
    std::wstring CodeSource::formatCode()
    {
        auto const numSubstitutions = Substitutions().Size();
        switch (numSubstitutions)
        {
        case 0:
            return std::wstring{ m_code };
        case 1:
            return vFormat(m_code, m_substitutions.GetAt(0).Value());
        case 2:
            return vFormat(
                m_code,
                m_substitutions.GetAt(0).Value(),
                m_substitutions.GetAt(1).Value());
        case 3:
            return vFormat(
                m_code,
                m_substitutions.GetAt(0).Value(),
                m_substitutions.GetAt(1).Value(),
                m_substitutions.GetAt(2).Value()
            );
        case 4:
            return vFormat(
                m_code,
                m_substitutions.GetAt(0).Value(),
                m_substitutions.GetAt(1).Value(),
                m_substitutions.GetAt(2).Value(),
                m_substitutions.GetAt(3).Value()
            );
        case 5:
            return vFormat(
                m_code,
                m_substitutions.GetAt(0).Value(),
                m_substitutions.GetAt(1).Value(),
                m_substitutions.GetAt(2).Value(),
                m_substitutions.GetAt(3).Value(),
                m_substitutions.GetAt(4).Value()
            );
        case 6:
            return vFormat(
                m_code,
                m_substitutions.GetAt(0).Value(),
                m_substitutions.GetAt(1).Value(),
                m_substitutions.GetAt(2).Value(),
                m_substitutions.GetAt(3).Value(),
                m_substitutions.GetAt(4).Value(),
                m_substitutions.GetAt(5).Value()
            );
        default:
            //Too many substitutions?
            assert(false);
        }
    }
}
