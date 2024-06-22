#pragma once
#include <winrt/Windows.Data.Xml.Dom.h>
#include <format>
#include <winrt/Windows.UI.Notifications.h>
#include <string_view>

namespace TileTemplates
{
    namespace internal
    {
        template<typename Derived>
        class ITileBase : public winrt::Windows::UI::Notifications::TileNotification
        {
        protected:
            static auto loadXml(auto&&... args)
            {
                winrt::Windows::Data::Xml::Dom::XmlDocument doc;
                doc.LoadXml(std::format(Derived::m_schema, args...));
                return doc;
            }
        public:
            ITileBase(auto&&... args) : winrt::Windows::UI::Notifications::TileNotification{ loadXml(args...) }
            {
            }
        };

    }

    using Source = std::wstring_view;
    using String = std::wstring_view;

    class TileSqaure150x150Image : public internal::ITileBase<TileSqaure150x150Image>
    {
        friend class internal::ITileBase<TileSqaure150x150Image>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare150x150Image" fallback="TileSquareImage"><image id="1" src="{}"/></binding></visual></tile>)";
    public:
        TileSqaure150x150Image(Source imageSrc) : ITileBase{ imageSrc } {}
    };

    class TileSquare150x150Block : public internal::ITileBase<TileSquare150x150Block>
    {
        friend class internal::ITileBase<TileSquare150x150Block>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare150x150Block" fallback="TileSquareBlock"><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileSquare150x150Block(std::wstring_view text1, std::wstring_view text2) : ITileBase{ text1, text2 } {}
    };

    class TileSquare150x150Text01 : public internal::ITileBase<TileSquare150x150Text01>
    {
        friend class internal::ITileBase<TileSquare150x150Text01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare150x150Text01" fallback="TileSquareText01"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text></binding></visual></tile>)";
    public:
        TileSquare150x150Text01(String text1, String text2, String text3, String text4) : ITileBase{ text1, text2, text3, text4 } {}
    };

    class TileSquare150x150Text02 : public internal::ITileBase<TileSquare150x150Text02>
    {
        friend class internal::ITileBase<TileSquare150x150Text02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare150x150Text02" fallback="TileSquareText02"><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileSquare150x150Text02(String text1, String text2) : ITileBase{ text1, text2 } {}
    };

    class TileSquare150x150Text03 : public internal::ITileBase<TileSquare150x150Text03>
    {
        friend class internal::ITileBase<TileSquare150x150Text03>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare150x150Text03" fallback="TileSquareText03"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text></binding></visual></tile>)";
    public:
        TileSquare150x150Text03(String text1, String text2, String text3, String text4) : ITileBase{ text1, text2, text3, text4 } {}
    };

    class TileSquare150x150Text04 : public internal::ITileBase<TileSquare150x150Text04>
    {
        friend class internal::ITileBase<TileSquare150x150Text04>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare150x150Text04" fallback="TileSquareText04"><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileSquare150x150Text04(String text) : ITileBase{ text } {}
    };

    class TileSquare150x150PeekImageAndText01 : public internal::ITileBase<TileSquare150x150PeekImageAndText01>
    {
        friend class internal::ITileBase<TileSquare150x150PeekImageAndText01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare150x150PeekImageAndText01" fallback="TileSquarePeekImageAndText01"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text></binding></visual></tile>)";
    public:
        TileSquare150x150PeekImageAndText01(Source image, String text1, String text2, String text3, String text4)
            : ITileBase(image, text1, text2, text3, text4)
        {}
    };

    class TileSquare150x150PeekImageAndText02 : public internal::ITileBase<TileSquare150x150PeekImageAndText02>
    {
        friend class internal::ITileBase<TileSquare150x150PeekImageAndText02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare150x150PeekImageAndText02" fallback="TileSquarePeekImageAndText02"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileSquare150x150PeekImageAndText02(Source image, String text1, String text2)
            : ITileBase(image, text1, text2)
        {}
    };

    class TileSquare150x150PeekImageAndText03 : public internal::ITileBase<TileSquare150x150PeekImageAndText03>
    {
        friend class internal::ITileBase<TileSquare150x150PeekImageAndText03>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare150x150PeekImageAndText03" fallback="TileSquarePeekImageAndText03"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text></binding></visual></tile>)";
    public:
        TileSquare150x150PeekImageAndText03(Source image, String text1, String text2, String text3, String text4)
            : ITileBase(image, text1, text2, text3, text4)
        {}
    };

    class TileSquare150x150PeekImageAndText04 : public internal::ITileBase<TileSquare150x150PeekImageAndText04>
    {
        friend class internal::ITileBase<TileSquare150x150PeekImageAndText04>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare150x150PeekImageAndText04" fallback="TileSquarePeekImageAndText04"><image id="1" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileSquare150x150PeekImageAndText04(Source image, String text) : ITileBase{ image, text } {}
    };

    class TileWide310x150Image : public internal::ITileBase<TileWide310x150Image>
    {
        friend class internal::ITileBase<TileWide310x150Image>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150Image" fallback="TileWideImage"><image id="1" src="{}"/></binding></visual></tile>)";
    public:
        TileWide310x150Image(Source image) : ITileBase{ image } {}
    };

    class TileWide310x150ImageCollection : public internal::ITileBase<TileWide310x150ImageCollection>
    {
        friend class internal::ITileBase<TileWide310x150ImageCollection>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150ImageCollection" fallback="TileWideImageCollection"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><image id="4" src="{}"/><image id="5" src="{}"/></binding></visual></tile>)";
    public:
        TileWide310x150ImageCollection(Source image1, Source image2, Source image3, Source image4, Source image5)
            : ITileBase{ image1, image2, image3, image4, image5 }
        {}
    };

    class TileWide310x150ImageAndText01 : public internal::ITileBase<TileWide310x150ImageAndText01>
    {
        friend class internal::ITileBase<TileWide310x150ImageAndText01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150ImageAndText01" fallback="TileWideImageAndText01"><image id="1" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150ImageAndText01(Source image, String text) : ITileBase{ image, text } {}
    };

    class TileWide310x150ImageAndText02 : public internal::ITileBase<TileWide310x150ImageAndText02>
    {
        friend class internal::ITileBase<TileWide310x150ImageAndText02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150ImageAndText02" fallback="TileWideImageAndText02"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150ImageAndText02(Source image, String text1, String text2)
            : ITileBase{ image, text1, text2 }
        {}
    };

    class TileWide310x150BlockAndText01 : public internal::ITileBase<TileWide310x150BlockAndText01>
    {
        friend class internal::ITileBase<TileWide310x150BlockAndText01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150BlockAndText01" fallback="TileWideBlockAndText01"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150BlockAndText01(String text1, String text2, String text3, String text4, String text5, String text6)
            : ITileBase{ text1, text2, text3, text4, text5, text6 }
        {}
    };

    class TileWide310x150BlockAndText02 : public internal::ITileBase<TileWide310x150BlockAndText02>
    {
        friend class internal::ITileBase<TileWide310x150BlockAndText02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150BlockAndText02" fallback="TileWideBlockAndText02"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150BlockAndText02(String text1, String text2, String text3)
            : ITileBase{ text1, text2, text3 }
        {}
    };

    class TileWide310x150PeekImageCollection01 : public internal::ITileBase<TileWide310x150PeekImageCollection01>
    {
        friend class internal::ITileBase<TileWide310x150PeekImageCollection01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImageCollection01" fallback="TileWidePeekImageCollection01"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><image id="4" src="{}"/><image id="5" src="{}"/><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImageCollection01(Source image1, Source image2, Source image3, Source image4, Source image5, String text1, String text2)
            : ITileBase{ image1, image2, image3, image4, image5, text1, text2 }
        {}
    };

    class TileWide310x150PeekImageCollection02 : public internal::ITileBase<TileWide310x150PeekImageCollection02>
    {
        friend class internal::ITileBase<TileWide310x150PeekImageCollection02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImageCollection02" fallback="TileWidePeekImageCollection02"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><image id="4" src="{}"/><image id="5" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImageCollection02(Source image1, Source image2, Source image3, Source image4, Source image5, String text1, String text2, String text3, String text4, String text5)
            : ITileBase{ image1, image2, image3, image4, image5, text1, text2, text3, text4, text5 }
        {}
    };

    class TileWide310x150PeekImageCollection03 : public internal::ITileBase<TileWide310x150PeekImageCollection03>
    {
        friend class internal::ITileBase<TileWide310x150PeekImageCollection03>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImageCollection03" fallback="TileWidePeekImageCollection03"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><image id="4" src="{}"/><image id="5" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImageCollection03(Source image1, Source image2, Source image3, Source image4, Source image5, String text)
            : ITileBase{ image1, image2, image3, image4, image5, text }
        {}
    };

    class TileWide310x150PeekImageCollection04 : public internal::ITileBase<TileWide310x150PeekImageCollection04>
    {
        friend class internal::ITileBase<TileWide310x150PeekImageCollection04>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImageCollection04" fallback="TileWidePeekImageCollection04"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><image id="4" src="{}"/><image id="5" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImageCollection04(Source image1, Source image2, Source image3, Source image4, Source image5, String text)
            : ITileBase{ image1, image2, image3, image4, image5, text }
        {}
    };

    class TileWide310x150PeekImageCollection05 : public internal::ITileBase<TileWide310x150PeekImageCollection05>
    {
        friend class internal::ITileBase<TileWide310x150PeekImageCollection05>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImageCollection05" fallback="TileWidePeekImageCollection05"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><image id="4" src="{}"/><image id="5" src="{}"/><image id="6" src="{}"/><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImageCollection05(Source image1, Source image2, Source image3, Source image4, Source image5, Source image6, String text1, String text2)
            : ITileBase{ image1, image2, image3, image4, image5, image6, text1, text2 }
        {}
    };

    class TileWide310x150PeekImageCollection06 : public internal::ITileBase<TileWide310x150PeekImageCollection06>
    {
        friend class internal::ITileBase<TileWide310x150PeekImageCollection06>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImageCollection06" fallback="TileWidePeekImageCollection06"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><image id="4" src="{}"/><image id="5" src="{}"/><image id="6" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImageCollection06(Source image1, Source image2, Source image3, Source image4, Source image5, Source image6, String text)
            : ITileBase{ image1, image2, image3, image4, image5, image6, text }
        {}
    };

    class TileWide310x150PeekImageAndText01 : public internal::ITileBase<TileWide310x150PeekImageAndText01>
    {
        friend class internal::ITileBase<TileWide310x150PeekImageAndText01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImageAndText01" fallback="TileWidePeekImageAndText01"><image id="1" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImageAndText01(Source image, String text) :ITileBase{ image, text } {}
    };

    class TileWide310x150PeekImageAndText02 : public internal::ITileBase<TileWide310x150PeekImageAndText02>
    {
        friend class internal::ITileBase<TileWide310x150PeekImageAndText02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImageAndText02" fallback="TileWidePeekImageAndText02"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImageAndText02(Source image, String text1, String text2, String text3, String text4, String text5)
            : ITileBase{ image, text1, text2, text3, text4, text5 }
        {}
    };

    class TileWide310x150PeekImage01 : public internal::ITileBase<TileWide310x150PeekImage01>
    {
        friend class internal::ITileBase<TileWide310x150PeekImage01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImage01" fallback="TileWidePeekImage01"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImage01(Source image, String text1, String text2) : ITileBase{ image, text1, text2 } {}
    };

    class TileWide310x150PeekImage02 : public internal::ITileBase<TileWide310x150PeekImage02>
    {
        friend class internal::ITileBase<TileWide310x150PeekImage02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImage02" fallback="TileWidePeekImage02"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImage02(Source image, String text1, String text2, String text3, String text4, String text5)
            : ITileBase{ image, text1, text2, text3, text4, text5 }
        {}
    };

    class TileWide310x150PeekImage03 : public internal::ITileBase<TileWide310x150PeekImage03>
    {
        friend class internal::ITileBase<TileWide310x150PeekImage03>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImage03" fallback="TileWidePeekImage03"><image id="1" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImage03(Source image, String text) : ITileBase{ image, text } {}
    };

    class TileWide310x150PeekImage04 : public internal::ITileBase<TileWide310x150PeekImage04>
    {
        friend class internal::ITileBase<TileWide310x150PeekImage04>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImage04" fallback="TileWidePeekImage04"><image id="1" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImage04(Source image, String text) : ITileBase{ image, text } {}
    };

    class TileWide310x150PeekImage05 : public internal::ITileBase<TileWide310x150PeekImage05>
    {
        friend class internal::ITileBase<TileWide310x150PeekImage05>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImage05" fallback="TileWidePeekImage05"><image id="1" src="{}"/><image id="2" src="{}"/><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImage05(Source image1, Source image2, String text1, String text2)
            : ITileBase{ image1, image2, text1, text2 }
        {}
    };

    class TileWide310x150PeekImage06 : public internal::ITileBase<TileWide310x150PeekImage06>
    {
        friend class internal::ITileBase<TileWide310x150PeekImage06>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150PeekImage06" fallback="TileWidePeekImage06"><image id="1" src="{}"/><image id="2" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150PeekImage06(Source image1, Source image2, String text) : ITileBase{ image1, image2, text } {}
    };

    class TileWide310x150SmallImageAndText01 : public internal::ITileBase<TileWide310x150SmallImageAndText01>
    {
        friend class internal::ITileBase<TileWide310x150SmallImageAndText01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150SmallImageAndText01" fallback="TileWideSmallImageAndText01"><image id="1" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150SmallImageAndText01(Source image, String text) : ITileBase{ image, text } {}
    };

    class TileWide310x150SmallImageAndText02 : public internal::ITileBase<TileWide310x150SmallImageAndText02>
    {
        friend class internal::ITileBase<TileWide310x150SmallImageAndText02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150SmallImageAndText02" fallback="TileWideSmallImageAndText02"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150SmallImageAndText02(Source image, String text1, String text2, String text3, String text4, String text5)
            : ITileBase{ image, text1, text2, text3, text4, text5 }
        {}
    };

    class TileWide310x150SmallImageAndText03 : public internal::ITileBase<TileWide310x150SmallImageAndText03>
    {
        friend class internal::ITileBase<TileWide310x150SmallImageAndText03>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150SmallImageAndText03" fallback="TileWideSmallImageAndText03"><image id="1" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150SmallImageAndText03(Source image, String text) : ITileBase{ image, text } {}
    };

    class TileWide310x150SmallImageAndText04 : public internal::ITileBase<TileWide310x150SmallImageAndText04>
    {
        friend class internal::ITileBase<TileWide310x150SmallImageAndText04>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150SmallImageAndText04" fallback="TileWideSmallImageAndText04"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150SmallImageAndText04(Source image, String text1, String text2)
            : ITileBase{ image, text1, text2 }
        {}
    };

    class TileWide310x150SmallImageAndText05 : public internal::ITileBase<TileWide310x150SmallImageAndText05>
    {
        friend class internal::ITileBase<TileWide310x150SmallImageAndText05>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150SmallImageAndText05" fallback="TileWideSmallImageAndText05"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150SmallImageAndText05(Source image, String text1, String text2)
            : ITileBase{ image, text1, text2 }
        {}
    };

    class TileWide310x150Text01 : public internal::ITileBase<TileWide310x150Text01>
    {
        friend class internal::ITileBase<TileWide310x150Text01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150Text01" fallback="TileWideText01"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150Text01(String text1, String text2, String text3, String text4, String text5)
            : ITileBase{ text1, text2, text3, text4, text5 }
        {}
    };

    class TileWide310x150Text02 : public internal::ITileBase<TileWide310x150Text02>
    {
        friend class internal::ITileBase<TileWide310x150Text02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150Text02" fallback="TileWideText02"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150Text02(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9 }
        {}
    };

    class TileWide310x150Text03 : public internal::ITileBase<TileWide310x150Text03>
    {
        friend class internal::ITileBase<TileWide310x150Text03>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150Text03" fallback="TileWideText03"><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150Text03(String text) : ITileBase{ text } {}
    };

    class TileWide310x150Text04 : public internal::ITileBase<TileWide310x150Text04>
    {
        friend class internal::ITileBase<TileWide310x150Text04>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150Text04" fallback="TileWideText04"><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150Text04(String text) : ITileBase{ text } {}
    };

    class TileWide310x150Text05 : public internal::ITileBase<TileWide310x150Text05>
    {
        friend class internal::ITileBase<TileWide310x150Text05>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150Text05" fallback="TileWideText05"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150Text05(String text1, String text2, String text3, String text4, String text5)
            : ITileBase{ text1, text2, text3, text4, text5 }
        {}
    };

    class TileWide310x150Text06 : public internal::ITileBase<TileWide310x150Text06>
    {
        friend class internal::ITileBase<TileWide310x150Text06>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150Text06" fallback="TileWideText06"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text><text id="10">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150Text06(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9, String text10)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9, text10 }
        {}
    };

    class TileWide310x150Text07 : public internal::ITileBase<TileWide310x150Text07>
    {
        friend class internal::ITileBase<TileWide310x150Text07>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150Text07" fallback="TileWideText07"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150Text07(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9 }
        {}
    };

    class TileWide310x150Text08 : public internal::ITileBase<TileWide310x150Text08>
    {
        friend class internal::ITileBase<TileWide310x150Text08>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150Text08" fallback="TileWideText08"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text><text id="10">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150Text08(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9, String text10)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9, text10 }
        {}
    };

    class TileWide310x150Text09 : public internal::ITileBase<TileWide310x150Text09>
    {
        friend class internal::ITileBase<TileWide310x150Text09>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150Text09" fallback="TileWideText09"><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150Text09(String text1, String text2)
            : ITileBase{ text1, text2 }
        {}
    };

    class TileWide310x150Text10 : public internal::ITileBase<TileWide310x150Text10>
    {
        friend class internal::ITileBase<TileWide310x150Text10>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150Text10" fallback="TileWideText10"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150Text10(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9 }
        {}
    };

    class TileWide310x150Text11 : public internal::ITileBase<TileWide310x150Text11>
    {
        friend class internal::ITileBase<TileWide310x150Text11>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150Text11" fallback="TileWideText11"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text><text id="10">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150Text11(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9, String text10)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9, text10 }
        {}
    };

    class TileSquare310x310BlockAndText01 : public internal::ITileBase<TileSquare310x310BlockAndText01>
    {
        friend class internal::ITileBase<TileSquare310x310BlockAndText01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310BlockAndText01"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310BlockAndText01(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9 }
        {}
    };

    class TileSquare310x310BlockAndText02 : public internal::ITileBase<TileSquare310x310BlockAndText02>
    {
        friend class internal::ITileBase<TileSquare310x310BlockAndText02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310BlockAndText02"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310BlockAndText02(Source image, String text1, String text2, String text3, String text4, String text5, String text6, String text7)
            : ITileBase{ image, text1, text2, text3, text4, text5, text6, text7 }
        {}
    };

    class TileSquare310x310Image : public internal::ITileBase<TileSquare310x310Image>
    {
        friend class internal::ITileBase<TileSquare310x310Image>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310Image"><image id="1" src="{}"/></binding></visual></tile>)";
    public:
        TileSquare310x310Image(Source image) : ITileBase{ image } {}
    };

    class TileSquare310x310ImageAndText01 : public internal::ITileBase<TileSquare310x310ImageAndText01>
    {
        friend class internal::ITileBase<TileSquare310x310ImageAndText01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310ImageAndText01"><image id="1" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310ImageAndText01(Source image, String text) : ITileBase{ image, text } {}
    };

    class TileSquare310x310ImageAndText02 : public internal::ITileBase<TileSquare310x310ImageAndText02>
    {
        friend class internal::ITileBase<TileSquare310x310ImageAndText02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310ImageAndText02"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310ImageAndText02(Source image, String text1, String text2) : ITileBase{ image, text1, text2 } {}
    };

    class TileSquare310x310ImageAndTextOverlay01 : public internal::ITileBase<TileSquare310x310ImageAndTextOverlay01>
    {
        friend class internal::ITileBase<TileSquare310x310ImageAndTextOverlay01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310ImageAndTextOverlay01"><image id="1" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310ImageAndTextOverlay01(Source image, String text) : ITileBase{ image, text } {}
    };

    class TileSquare310x310ImageAndTextOverlay02 : public internal::ITileBase<TileSquare310x310ImageAndTextOverlay02>
    {
        friend class internal::ITileBase<TileSquare310x310ImageAndTextOverlay02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310ImageAndTextOverlay02"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310ImageAndTextOverlay02(Source image, String text1, String text2) : ITileBase{ image, text1, text2 } {}
    };

    class TileSquare310x310ImageAndTextOverlay03 : public internal::ITileBase<TileSquare310x310ImageAndTextOverlay03>
    {
        friend class internal::ITileBase<TileSquare310x310ImageAndTextOverlay03>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310ImageAndTextOverlay03"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310ImageAndTextOverlay03(Source image, String text1, String text2, String text3, String text4)
            : ITileBase{ image, text1, text2, text3, text4 }
        {}
    };

    class TileSquare310x310ImageCollectionAndText01 : public internal::ITileBase<TileSquare310x310ImageCollectionAndText01>
    {
        friend class internal::ITileBase<TileSquare310x310ImageCollectionAndText01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310ImageCollectionAndText01"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><image id="4" src="{}"/><image id="5" src="{}"/><text id="1">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310ImageCollectionAndText01(Source image1, Source image2, Source image3, Source image4, Source image5, String text)
            : ITileBase{ image1, image2, image3, image4, image5, text }
        {}
    };

    class TileSquare310x310ImageCollectionAndText02 : public internal::ITileBase<TileSquare310x310ImageCollectionAndText02>
    {
        friend class internal::ITileBase<TileSquare310x310ImageCollectionAndText02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310ImageCollectionAndText02"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><image id="4" src="{}"/><image id="5" src="{}"/><text id="1">{}</text><text id="2">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310ImageCollectionAndText02(Source image1, Source image2, Source image3, Source image4, Source image5, String text1, String text2)
            : ITileBase{ image1, image2, image3, image4, image5, text1, text2 }
        {}
    };

    class TileSquare310x310ImageCollection : public internal::ITileBase<TileSquare310x310ImageCollection>
    {
        friend class internal::ITileBase<TileSquare310x310ImageCollection>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310ImageCollection"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><image id="4" src="{}"/><image id="5" src="{}"/></binding></visual></tile>)";
    public:
        TileSquare310x310ImageCollection(Source image1, Source image2, Source image3, Source image4, Source image5)
            : ITileBase{ image1, image2, image3, image4, image5 }
        {}
    };

    class TileSquare310x310SmallImagesAndTextList01 : public internal::ITileBase<TileSquare310x310SmallImagesAndTextList01>
    {
        friend class internal::ITileBase<TileSquare310x310SmallImagesAndTextList01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310SmallImagesAndTextList01"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310SmallImagesAndTextList01(Source image1, Source image2, Source image3, String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9)
            : ITileBase{ image1, image2, image3, text1, text2, text3, text4, text5, text6, text7, text8, text9 }
        {}
    };

    class TileSquare310x310SmallImagesAndTextList02 : public internal::ITileBase<TileSquare310x310SmallImagesAndTextList02>
    {
        friend class internal::ITileBase<TileSquare310x310SmallImagesAndTextList02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310SmallImagesAndTextList02"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310SmallImagesAndTextList02(Source image1, Source image2, Source image3, String text1, String text2, String text3)
            : ITileBase{ image1, image2, image3, text1, text2, text3 }
        {}
    };

    class TileSquare310x310SmallImagesAndTextList03 : public internal::ITileBase<TileSquare310x310SmallImagesAndTextList03>
    {
        friend class internal::ITileBase<TileSquare310x310SmallImagesAndTextList03>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310SmallImagesAndTextList03"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310SmallImagesAndTextList03(Source image1, Source image2, Source image3, String text1, String text2, String text3, String text4, String text5, String text6)
            : ITileBase{ image1, image2, image3, text1, text2, text3, text4, text5, text6 }
        {}
    };

    class TileSquare310x310SmallImagesAndTextList04 : public internal::ITileBase<TileSquare310x310SmallImagesAndTextList04>
    {
        friend class internal::ITileBase<TileSquare310x310SmallImagesAndTextList04>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310SmallImagesAndTextList04"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310SmallImagesAndTextList04(Source image1, Source image2, Source image3, String text1, String text2, String text3, String text4, String text5, String text6)
            : ITileBase{ image1, image2, image3, text1, text2, text3, text4, text5, text6 }
        {}
    };

    class TileSquare310x310Text01 : public internal::ITileBase<TileSquare310x310Text01>
    {
        friend class internal::ITileBase<TileSquare310x310Text01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310Text01"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text><text id="10">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310Text01(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9, String text10)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9, text10 }
        {}
    };

    class TileSquare310x310Text02 : public internal::ITileBase<TileSquare310x310Text02>
    {
        friend class internal::ITileBase<TileSquare310x310Text02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310Text02"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text><text id="10">{}</text><text id="11">{}</text><text id="12">{}</text><text id="13">{}</text><text id="14">{}</text><text id="15">{}</text><text id="16">{}</text><text id="17">{}</text><text id="18">{}</text><text id="19">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310Text02(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9, String text10, String text11, String text12, String text13, String text14, String text15, String text16, String text17, String text18, String text19)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11, text12, text13, text14, text15, text16, text17, text18, text19 }
        {}
    };

    class TileSquare310x310Text03 : public internal::ITileBase<TileSquare310x310Text03>
    {
        friend class internal::ITileBase<TileSquare310x310Text03>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310Text03"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text><text id="10">{}</text><text id="11">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310Text03(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9, String text10, String text11)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11 }
        {}
    };

    class TileSquare310x310Text04 : public internal::ITileBase<TileSquare310x310Text04>
    {
        friend class internal::ITileBase<TileSquare310x310Text04>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310Text04"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text><text id="10">{}</text><text id="11">{}</text><text id="12">{}</text><text id="13">{}</text><text id="14">{}</text><text id="15">{}</text><text id="16">{}</text><text id="17">{}</text><text id="18">{}</text><text id="19">{}</text><text id="20">{}</text><text id="21">{}</text><text id="22">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310Text04(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9, String text10, String text11, String text12, String text13, String text14, String text15, String text16, String text17, String text18, String text19, String text20, String text21, String text22)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11, text12, text13, text14, text15, text16, text17, text18, text19, text20, text21, text22 }
        {}
    };

    class TileSquare310x310Text05 : public internal::ITileBase<TileSquare310x310Text05>
    {
        friend class internal::ITileBase<TileSquare310x310Text05>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310Text05"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text><text id="10">{}</text><text id="11">{}</text><text id="12">{}</text><text id="13">{}</text><text id="14">{}</text><text id="15">{}</text><text id="16">{}</text><text id="17">{}</text><text id="18">{}</text><text id="19">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310Text05(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9, String text10, String text11, String text12, String text13, String text14, String text15, String text16, String text17, String text18, String text19)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11, text12, text13, text14, text15, text16, text17, text18, text19 }
        {}
    };

    class TileSquare310x310Text06 : public internal::ITileBase<TileSquare310x310Text06>
    {
        friend class internal::ITileBase<TileSquare310x310Text06>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310Text06"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text><text id="10">{}</text><text id="11">{}</text><text id="12">{}</text><text id="13">{}</text><text id="14">{}</text><text id="15">{}</text><text id="16">{}</text><text id="17">{}</text><text id="18">{}</text><text id="19">{}</text><text id="20">{}</text><text id="21">{}</text><text id="22">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310Text06(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9, String text10, String text11, String text12, String text13, String text14, String text15, String text16, String text17, String text18, String text19, String text20, String text21, String text22)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11, text12, text13, text14, text15, text16, text17, text18, text19, text20, text21, text22 }
        {}
    };

    class TileSquare310x310Text07 : public internal::ITileBase<TileSquare310x310Text07>
    {
        friend class internal::ITileBase<TileSquare310x310Text07>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310Text07"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text><text id="10">{}</text><text id="11">{}</text><text id="12">{}</text><text id="13">{}</text><text id="14">{}</text><text id="15">{}</text><text id="16">{}</text><text id="17">{}</text><text id="18">{}</text><text id="19">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310Text07(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9, String text10, String text11, String text12, String text13, String text14, String text15, String text16, String text17, String text18, String text19)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11, text12, text13, text14, text15, text16, text17, text18, text19 }
        {}
    };

    class TileSquare310x310Text08 : public internal::ITileBase<TileSquare310x310Text08>
    {
        friend class internal::ITileBase<TileSquare310x310Text08>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310Text08"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text><text id="10">{}</text><text id="11">{}</text><text id="12">{}</text><text id="13">{}</text><text id="14">{}</text><text id="15">{}</text><text id="16">{}</text><text id="17">{}</text><text id="18">{}</text><text id="19">{}</text><text id="20">{}</text><text id="21">{}</text><text id="22">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310Text08(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9, String text10, String text11, String text12, String text13, String text14, String text15, String text16, String text17, String text18, String text19, String text20, String text21, String text22)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11, text12, text13, text14, text15, text16, text17, text18, text19, text20, text21, text22 }
        {}
    };

    class TileSquare310x310TextList01 : public internal::ITileBase<TileSquare310x310TextList01>
    {
        friend class internal::ITileBase<TileSquare310x310TextList01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310TextList01"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text><text id="8">{}</text><text id="9">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310TextList01(String text1, String text2, String text3, String text4, String text5, String text6, String text7, String text8, String text9)
            : ITileBase{ text1, text2, text3, text4, text5, text6, text7, text8, text9 }
        {}
    };

    class TileSquare310x310TextList02 : public internal::ITileBase<TileSquare310x310TextList02>
    {
        friend class internal::ITileBase<TileSquare310x310TextList02>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310TextList02"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310TextList02(String text1, String text2, String text3) : ITileBase{ text1, text2, text3 }
        {}
    };

    class TileSquare310x310TextList03 : public internal::ITileBase<TileSquare310x310TextList03>
    {
        friend class internal::ITileBase<TileSquare310x310TextList03>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310TextList03"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310TextList03(String text1, String text2, String text3, String text4, String text5, String text6)
            : ITileBase{ text1, text2, text3, text4, text5, text6 }
        {}
    };

    class TileSquare310x310SmallImageAndText01 : public internal::ITileBase<TileSquare310x310SmallImageAndText01>
    {
        friend class internal::ITileBase<TileSquare310x310SmallImageAndText01>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310SmallImageAndText01"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310SmallImageAndText01(Source image, String text1, String text2, String text3)
            : ITileBase{ image, text1, text2, text3 }
        {}
    };

    class TileSquare310x310SmallImagesAndTextList05 : public internal::ITileBase<TileSquare310x310SmallImagesAndTextList05>
    {
        friend class internal::ITileBase<TileSquare310x310SmallImagesAndTextList05>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310SmallImagesAndTextList05"><image id="1" src="{}"/><image id="2" src="{}"/><image id="3" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text><text id="6">{}</text><text id="7">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310SmallImagesAndTextList05(Source image1, Source image2, Source image3, String text1, String text2, String text3, String text4, String text5, String text6, String text7)
            : ITileBase{ image1, image2, image3, text1, text2, text3, text4, text5, text6, text7 }
        {}
    };

    class TileSquare310x310Text09 : public internal::ITileBase<TileSquare310x310Text09>
    {
        friend class internal::ITileBase<TileSquare310x310Text09>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare310x310Text09"><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text><text id="4">{}</text><text id="5">{}</text></binding></visual></tile>)";
    public:
        TileSquare310x310Text09(String text1, String text2, String text3, String text4, String text5)
            : ITileBase{ text1, text2, text3, text4, text5 }
        {}
    };

    class TileSquare71x71IconWithBadge : public internal::ITileBase<TileSquare71x71IconWithBadge>
    {
        friend class internal::ITileBase<TileSquare71x71IconWithBadge>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare71x71IconWithBadge"><image id="1" src="{}"/></binding></visual></tile>)";
    public:
        TileSquare71x71IconWithBadge(Source image) : ITileBase{ image } {}
    };

    class TileSquare150x150IconWithBadge : public internal::ITileBase<TileSquare150x150IconWithBadge>
    {
        friend class internal::ITileBase<TileSquare150x150IconWithBadge>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare150x150IconWithBadge"><image id="1" src="{}"/></binding></visual></tile>)";
    public:
        TileSquare150x150IconWithBadge(Source image) : ITileBase{ image } {}
    };

    class TileWide310x150IconWithBadgeAndText : public internal::ITileBase<TileWide310x150IconWithBadgeAndText>
    {
        friend class internal::ITileBase<TileWide310x150IconWithBadgeAndText>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileWide310x150IconWithBadgeAndText"><image id="1" src="{}"/><text id="1">{}</text><text id="2">{}</text><text id="3">{}</text></binding></visual></tile>)";
    public:
        TileWide310x150IconWithBadgeAndText(Source image, String text1, String text2, String text3)
            : ITileBase{ image, text1, text2, text3 }
        {}
    };

    class TileSquare71x71Image : public internal::ITileBase<TileSquare71x71Image>
    {
        friend class internal::ITileBase<TileSquare71x71Image>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileSquare71x71Image"><image id="1" src="{}"/></binding></visual></tile>)";
    public:
        TileSquare71x71Image(Source image) : ITileBase{ image } {}
    };

    class TileTall150x310Image : public internal::ITileBase<TileTall150x310Image>
    {
        friend class internal::ITileBase<TileTall150x310Image>;
        constexpr auto static m_schema = LR"(<tile><visual version="4"><binding template="TileTall150x310Image"><image id="1" src="{}"/></binding></visual></tile>)";
    public:
        TileTall150x310Image(Source image) : ITileBase{ image } {}
    };
}