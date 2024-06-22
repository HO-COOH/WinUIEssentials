#pragma once
#include <winrt/Windows.UI.Notifications.h>
#include <winrt/Windows.Data.Xml.Dom.h>
#include <format>

namespace ToastTemplates
{
    namespace internal
    {
        template<typename Derived>
        class IToastBase
        {
        protected:
            static auto loadXml(auto&&... args)
            {
                winrt::Windows::Data::Xml::Dom::XmlDocument doc;
                doc.LoadXml(std::format(Derived::m_schema, args...));
                return doc;
            }
        };
    }

    class BodyTextOnly : 
        internal::IToastBase<BodyTextOnly>, 
        public winrt::Windows::UI::Notifications::ToastNotification
    {
    public:
        BodyTextOnly(std::wstring_view bodyText): 
            winrt::Windows::UI::Notifications::ToastNotification{loadXml(bodyText)}
        {
        }
    private:
        constexpr auto static m_schema = LR"(<toast>
    <visual>
        <binding template="ToastText01">
            <text id="1">{}</text>
        </binding>  
    </visual>
</toast>)";
        friend class IToastBase<BodyTextOnly>;
    };
    using ToastText01 = BodyTextOnly;

    class SingleLineHeaderWithBody : 
        internal::IToastBase<SingleLineHeaderWithBody>, 
        public winrt::Windows::UI::Notifications::ToastNotification
    {
    public:
        SingleLineHeaderWithBody(std::wstring_view header, std::wstring_view body) : 
            winrt::Windows::UI::Notifications::ToastNotification{loadXml(header, body)}
        {
        }
    private:
        constexpr auto static m_schema = LR"(<toast>
    <visual>
        <binding template="ToastText02">
            <text id="1">{}</text>
            <text id="2">{}</text>
        </binding>  
    </visual>
</toast>)";
        friend class internal::IToastBase<SingleLineHeaderWithBody>;
    };
    using ToastText02 = SingleLineHeaderWithBody;

    class TwoLineHeaderWithBody : 
        internal::IToastBase<TwoLineHeaderWithBody>,
        public winrt::Windows::UI::Notifications::ToastNotification
    {
    public:
        TwoLineHeaderWithBody(std::wstring_view header, std::wstring_view body) :
            winrt::Windows::UI::Notifications::ToastNotification{loadXml(header, body)}
        {
        }
    private:
        constexpr auto static m_schema = LR"(<toast>
    <visual>
        <binding template="ToastText03">
            <text id="1">{}</text>
            <text id="2">{}</text>
        </binding>  
    </visual>
</toast>)";
        friend class internal::IToastBase<TwoLineHeaderWithBody>;
    };
    using ToastText03 = TwoLineHeaderWithBody;

    class HeaderWithTwoSingleLineBody : 
        internal::IToastBase<HeaderWithTwoSingleLineBody>,
        public winrt::Windows::UI::Notifications::ToastNotification
    {
    public:
        HeaderWithTwoSingleLineBody(std::wstring_view header, std::wstring_view body1, std::wstring_view body2) :
            winrt::Windows::UI::Notifications::ToastNotification{loadXml(header, body1, body2)}
        {
        }
    private:
        constexpr auto static m_schema = LR"(<toast>
    <visual>
        <binding template="ToastText04">
            <text id="1">{}</text>
            <text id="2">{}</text>
            <text id="3">{}</text>
        </binding>  
    </visual>
</toast>)";
        friend class internal::IToastBase<HeaderWithTwoSingleLineBody>;
    };
    using ToastText04 = HeaderWithTwoSingleLineBody;

    class ImageWithBodyOnly : 
        internal::IToastBase<ImageWithBodyOnly>,
        public winrt::Windows::UI::Notifications::ToastNotification
    {
    public:
        ImageWithBodyOnly(std::wstring_view image, std::wstring_view header) : 
            winrt::Windows::UI::Notifications::ToastNotification{loadXml(image, header)}
        {
        }
    private:
        constexpr auto static m_schema = LR"(<toast>
    <visual>
        <binding template="ToastImageAndText01">
            <image id="1" src="{0}" alt="{0}"/>
            <text id="1">{1}</text>
        </binding>  
    </visual>
</toast>)";
        friend class internal::IToastBase<ImageWithBodyOnly>;
    };
    using ToastImageAndText01 = ImageWithBodyOnly;

    class ImageWithHeaderAndBody : 
        internal::IToastBase<ImageWithHeaderAndBody>,
        public winrt::Windows::UI::Notifications::ToastNotification
    {
    public:
        ImageWithHeaderAndBody(std::wstring_view image, std::wstring_view header, std::wstring_view body) : 
            winrt::Windows::UI::Notifications::ToastNotification{loadXml(image, header, body)}
        {
        }
    private:
        constexpr auto static m_schema = LR"(<toast>
    <visual>
        <binding template="ToastImageAndText02">
            <image id="1" src="{0}" alt="{0}"/>
            <text id="1">{1}</text>
            <text id="2">{2}</text>
        </binding>  
    </visual>
</toast>)";
        friend class internal::IToastBase<ImageWithHeaderAndBody>;
    };
    using ToastImageAndText02 = ImageWithHeaderAndBody;

    class ImageWithTwoLineHeaderAndBody : 
        internal::IToastBase<ImageWithTwoLineHeaderAndBody>,
        public winrt::Windows::UI::Notifications::ToastNotification
    {
    public:
        ImageWithTwoLineHeaderAndBody(std::wstring_view image, std::wstring_view header, std::wstring_view body) :
            winrt::Windows::UI::Notifications::ToastNotification{loadXml(image, header, body)}
        {
        }
    private:
        constexpr auto static m_schema = LR"(<toast>
    <visual>
        <binding template="ToastImageAndText03">
            <image id="1" src="{0}" alt="{0}"/>
            <text id="1">{1}</text>
            <text id="2">{2}</text>
        </binding>  
    </visual>
</toast>)";
        friend class internal::IToastBase<ImageWithTwoLineHeaderAndBody>;
    };
    using ToastImageAndText03 = ImageWithTwoLineHeaderAndBody;

    class ImageWithHeaderAndTwoSingleLineBody : 
        internal::IToastBase<ImageWithHeaderAndTwoSingleLineBody>,
        public winrt::Windows::UI::Notifications::ToastNotification
    {
    public:
        ImageWithHeaderAndTwoSingleLineBody(std::wstring_view image, std::wstring_view header, std::wstring_view body1, std::wstring_view body2) :
            winrt::Windows::UI::Notifications::ToastNotification{loadXml(image, header, body1, body2)}
        {
        }
    private:
        constexpr auto static m_schema = LR"(<toast>
    <visual>
        <binding template="ToastImageAndText04">
            <image id="1" src="{0}" alt="{0}"/>
            <text id="1">{1}</text>
            <text id="2">{2}</text>
            <text id="3">{3}</text>
        </binding>  
    </visual>
</toast>)";
        friend class internal::IToastBase<ImageWithHeaderAndTwoSingleLineBody>;
    };
    using ToastImageAndText04 = ImageWithHeaderAndTwoSingleLineBody;
}