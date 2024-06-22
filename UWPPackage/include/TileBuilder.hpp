#pragma once
#include <winrt/Windows.Data.Xml.Dom.h>
#include <winrt/Windows.UI.Notifications.h>
#include <vector>


//https://learn.microsoft.com/en-us/windows/apps/design/shell/tiles-and-notifications/adaptive-tiles-schema
namespace TilesBuilder
{
	template<typename ValueType>
	struct PropertyValue
	{
		std::wstring_view name;
		std::optional<ValueType> value;

		template<typename T>
		PropertyValue& operator=(T&& newValue)
		{
			value.emplace(std::move(newValue)); //don't use std::forward here because we are all using value semantics
			return *this;
		}

		operator bool() const
		{
			return static_cast<bool>(value);
		}
	};

	namespace internals
	{
		/**
		 * @brief Create `XmlElement` for node that does not have children
		 * @param name Name of this node
		 * @param root The root `XmlDocument`
		 * @param ...properties Properties of this node
		 * @return XML representation of this toast node
		*/
		winrt::Windows::Data::Xml::Dom::XmlElement MakeElement(std::wstring_view name, winrt::Windows::Data::Xml::Dom::XmlDocument& root, auto&&... properties)
		{
			auto element = root.CreateElement(name);
			(element << ... << properties);
			return element;
		}

		/**
		 * @brief Create `XmlElement` for node that does have children
		 * @tparam Node Type of child nodes
		 * @param name Name of this node
		 * @param root The root `XmlDocument`
		 * @param nodes vector of child nodes
		 * @param ...properties Properties of this node
		 * @return XML representation of this toast nodes with all its child nodes
		*/
		template<typename Node>
		winrt::Windows::Data::Xml::Dom::XmlElement MakeElement(std::wstring_view name, winrt::Windows::Data::Xml::Dom::XmlDocument& root, std::vector<Node*>& nodes, auto&&... properties)
		{
			auto element = MakeElement(name, root, properties...);
			for (auto node : nodes)
				element.AppendChild(node->Get(root));
			return element;
		}
	}

	struct INodeBase
	{
		virtual winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) = 0;
	};


	template<typename T, typename...AcceptTypes>
	concept Accept = (std::is_same_v<std::remove_reference_t<T>, AcceptTypes> || ...);

	template<typename Derived, typename...ChildType>
	class ISupportChild
	{
	protected:
		std::vector<INodeBase*> m_child;
	public:
		template<typename...T> requires (Accept<T, ChildType...> && ...)
			Derived& operator()(T&&... children)
		{
			(m_child.push_back(&children), ...);
			return static_cast<Derived&>(*this);
		}
	};

	template<int Min, int Max>
	class LimitedInt
	{
		int m_value;
	public:

		LimitedInt(int value) : m_value{ value }
		{
			assert(value >= Min && value <= Max);
		}

		LimitedInt& operator=(int value)
		{
			m_value = value;
			return *this;
		}

		constexpr operator int() const noexcept
		{
			return m_value;
		}
	};
	inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<int> const& value)
	{
		if (value)
		{
			element.SetAttribute(value.name, winrt::to_hstring(*value.value));
		}
		return element;
	}
	template<int Min, int Max>
	inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<LimitedInt<Min, Max>> const& value)
	{
		if (value)
		{
			element << PropertyValue<int>{.name = value.name, .value = static_cast<int>(*value.value)};
		}
		return element;
	}


	class Tile;
	class Visual;
	class Binding;
	class Image;
	class Text;
	class Group;
	class Subgroup;

	enum class Branding
	{
		None,
		Logo,
		Name,
		NameAndLogo
	};
	inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<Branding> const& value)
	{
		if (value)
		{
			switch (*value.value)
			{
			case Branding::None:  element.SetAttribute(value.name, L"none"); break;
			case Branding::Logo: element.SetAttribute(value.name, L"logo"); break;
			case Branding::Name: element.SetAttribute(value.name, L"name"); break;
			case Branding::NameAndLogo: element.SetAttribute(value.name, L"nameAndLogo"); break;
			default: break;
			}
		}
		return element;
	}

	enum class TileTemplateNameV3
	{
		TileMedium,
		TileSmall,
		TileWide,
		TileLarge,
		TileSquare150x150Block,
		TileSquare150x150Image,
		TileSquare150x150PeekImageAndText01,
		TileSquare150x150PeekImageAndText02,
		TileSquare150x150PeekImageAndText03,
		TileSquare150x150PeekImageAndText04,
		TileSquare150x150Text01,
		TileSquare150x150Text02,
		TileSquare150x150Text03,
		TileSquare150x150Text04,
		TileSquare310x310BlockAndText01,
		TileSquare310x310BlockAndText02,
		TileSquare310x310Image,
		TileSquare310x310ImageAndText01,
		TileSquare310x310ImageAndText02,
		TileSquare310x310ImageAndTextOverlay01,
		TileSquare310x310ImageAndTextOverlay02,
		TileSquare310x310ImageAndTextOverlay03,
		TileSquare310x310ImageCollection,
		TileSquare310x310ImageCollectionAndText01,
		TileSquare310x310ImageCollectionAndText02,
		TileSquare310x310SmallImagesAndTextList01,
		TileSquare310x310SmallImagesAndTextList02,
		TileSquare310x310SmallImagesAndTextList03,
		TileSquare310x310SmallImagesAndTextList04,
		TileSquare310x310Text01,
		TileSquare310x310Text02,
		TileSquare310x310Text03,
		TileSquare310x310Text04,
		TileSquare310x310Text05,
		TileSquare310x310Text06,
		TileSquare310x310Text07,
		TileSquare310x310Text08,
		TileSquare310x310TextList01,
		TileSquare310x310TextList02,
		TileSquare310x310TextList03,
		TileWide310x150BlockAndText01,
		TileWide310x150BlockAndText02,
		TileWide310x150Image,
		TileWide310x150ImageAndText01,
		TileWide310x150ImageAndText02,
		TileWide310x150ImageCollection,
		TileWide310x150PeekImage01,
		TileWide310x150PeekImage02,
		TileWide310x150PeekImage03,
		TileWide310x150PeekImage04,
		TileWide310x150PeekImage05,
		TileWide310x150PeekImage06,
		TileWide310x150PeekImageAndText01,
		TileWide310x150PeekImageAndText02,
		TileWide310x150PeekImageCollection01,
		TileWide310x150PeekImageCollection02,
		TileWide310x150PeekImageCollection03,
		TileWide310x150PeekImageCollection04,
		TileWide310x150PeekImageCollection05,
		TileWide310x150PeekImageCollection06,
		TileWide310x150SmallImageAndText01,
		TileWide310x150SmallImageAndText02,
		TileWide310x150SmallImageAndText03,
		TileWide310x150SmallImageAndText04,
		TileWide310x150SmallImageAndText05,
		TileWide310x150Text01,
		TileWide310x150Text02,
		TileWide310x150Text03,
		TileWide310x150Text04,
		TileWide310x150Text05,
		TileWide310x150Text06,
		TileWide310x150Text07,
		TileWide310x150Text08,
		TileWide310x150Text09,
		TileWide310x150Text10,
		TileWide310x150Text11,
		TileSquare71x71Image,
		TileSquare71x71IconWithBadge,
		TileSquare150x150IconWithBadge,
		TileWide310x150IconWithBadgeAndText
	};
	inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<TileTemplateNameV3> const& value)
	{
		if (value)
		{
			switch (*value.value)
			{
			case TileTemplateNameV3::TileMedium: element.SetAttribute(value.name, L"TileMedium"); break;
			case TileTemplateNameV3::TileSmall: element.SetAttribute(value.name, L"TileSmall"); break;
			case TileTemplateNameV3::TileWide: element.SetAttribute(value.name, L"TileWide"); break;
			case TileTemplateNameV3::TileLarge: element.SetAttribute(value.name, L"TileLarge"); break;
			case TileTemplateNameV3::TileSquare150x150Block: element.SetAttribute(value.name, L"TileSquare150x150Block"); break;
			case TileTemplateNameV3::TileSquare150x150Image: element.SetAttribute(value.name, L"TileSquare150x150Image"); break;
			case TileTemplateNameV3::TileSquare150x150PeekImageAndText01: element.SetAttribute(value.name, L"TileSquare150x150PeekImageAndText01"); break;
			case TileTemplateNameV3::TileSquare150x150PeekImageAndText02: element.SetAttribute(value.name, L"TileSquare150x150PeekImageAndText02"); break;
			case TileTemplateNameV3::TileSquare150x150PeekImageAndText03: element.SetAttribute(value.name, L"TileSquare150x150PeekImageAndText03"); break;
			case TileTemplateNameV3::TileSquare150x150PeekImageAndText04: element.SetAttribute(value.name, L"TileSquare150x150PeekImageAndText04"); break;
			case TileTemplateNameV3::TileSquare150x150Text01: element.SetAttribute(value.name, L"TileSquare150x150Text01"); break;
			case TileTemplateNameV3::TileSquare150x150Text02: element.SetAttribute(value.name, L"TileSquare150x150Text02"); break;
			case TileTemplateNameV3::TileSquare150x150Text03: element.SetAttribute(value.name, L"TileSquare150x150Text03"); break;
			case TileTemplateNameV3::TileSquare150x150Text04: element.SetAttribute(value.name, L"TileSquare150x150Text04"); break;
			case TileTemplateNameV3::TileSquare310x310BlockAndText01: element.SetAttribute(value.name, L"TileSquare310x310BlockAndText01"); break;
			case TileTemplateNameV3::TileSquare310x310BlockAndText02: element.SetAttribute(value.name, L"TileSquare310x310BlockAndText02"); break;
			case TileTemplateNameV3::TileSquare310x310Image: element.SetAttribute(value.name, L"TileSquare310x310Image"); break;
			case TileTemplateNameV3::TileSquare310x310ImageAndText01: element.SetAttribute(value.name, L"TileSquare310x310ImageAndText01"); break;
			case TileTemplateNameV3::TileSquare310x310ImageAndText02: element.SetAttribute(value.name, L"TileSquare310x310ImageAndText02"); break;
			case TileTemplateNameV3::TileSquare310x310ImageAndTextOverlay01: element.SetAttribute(value.name, L"TileSquare310x310ImageAndTextOverlay01"); break;
			case TileTemplateNameV3::TileSquare310x310ImageAndTextOverlay02: element.SetAttribute(value.name, L"TileSquare310x310ImageAndTextOverlay02"); break;
			case TileTemplateNameV3::TileSquare310x310ImageAndTextOverlay03: element.SetAttribute(value.name, L"TileSquare310x310ImageAndTextOverlay03"); break;
			case TileTemplateNameV3::TileSquare310x310ImageCollection: element.SetAttribute(value.name, L"TileSquare310x310ImageCollection"); break;
			case TileTemplateNameV3::TileSquare310x310ImageCollectionAndText01: element.SetAttribute(value.name, L"TileSquare310x310ImageCollectionAndText01"); break;
			case TileTemplateNameV3::TileSquare310x310ImageCollectionAndText02: element.SetAttribute(value.name, L"TileSquare310x310ImageCollectionAndText02"); break;
			case TileTemplateNameV3::TileSquare310x310SmallImagesAndTextList01: element.SetAttribute(value.name, L"TileSquare310x310SmallImagesAndTextList01"); break;
			case TileTemplateNameV3::TileSquare310x310SmallImagesAndTextList02: element.SetAttribute(value.name, L"TileSquare310x310SmallImagesAndTextList02"); break;
			case TileTemplateNameV3::TileSquare310x310SmallImagesAndTextList03: element.SetAttribute(value.name, L"TileSquare310x310SmallImagesAndTextList03"); break;
			case TileTemplateNameV3::TileSquare310x310SmallImagesAndTextList04: element.SetAttribute(value.name, L"TileSquare310x310SmallImagesAndTextList04"); break;
			case TileTemplateNameV3::TileSquare310x310Text01: element.SetAttribute(value.name, L"TileSquare310x310Text01"); break;
			case TileTemplateNameV3::TileSquare310x310Text02: element.SetAttribute(value.name, L"TileSquare310x310Text02"); break;
			case TileTemplateNameV3::TileSquare310x310Text03: element.SetAttribute(value.name, L"TileSquare310x310Text03"); break;
			case TileTemplateNameV3::TileSquare310x310Text04: element.SetAttribute(value.name, L"TileSquare310x310Text04"); break;
			case TileTemplateNameV3::TileSquare310x310Text05: element.SetAttribute(value.name, L"TileSquare310x310Text05"); break;
			case TileTemplateNameV3::TileSquare310x310Text06: element.SetAttribute(value.name, L"TileSquare310x310Text06"); break;
			case TileTemplateNameV3::TileSquare310x310Text07: element.SetAttribute(value.name, L"TileSquare310x310Text07"); break;
			case TileTemplateNameV3::TileSquare310x310Text08: element.SetAttribute(value.name, L"TileSquare310x310Text08"); break;
			case TileTemplateNameV3::TileSquare310x310TextList01: element.SetAttribute(value.name, L"TileSquare310x310TextList01"); break;
			case TileTemplateNameV3::TileSquare310x310TextList02: element.SetAttribute(value.name, L"TileSquare310x310TextList02"); break;
			case TileTemplateNameV3::TileSquare310x310TextList03: element.SetAttribute(value.name, L"TileSquare310x310TextList03"); break;
			case TileTemplateNameV3::TileWide310x150BlockAndText01: element.SetAttribute(value.name, L"TileWide310x150BlockAndText01"); break;
			case TileTemplateNameV3::TileWide310x150BlockAndText02: element.SetAttribute(value.name, L"TileWide310x150BlockAndText02"); break;
			case TileTemplateNameV3::TileWide310x150Image: element.SetAttribute(value.name, L"TileWide310x150Image"); break;
			case TileTemplateNameV3::TileWide310x150ImageAndText01: element.SetAttribute(value.name, L"TileWide310x150ImageAndText01"); break;
			case TileTemplateNameV3::TileWide310x150ImageAndText02: element.SetAttribute(value.name, L"TileWide310x150ImageAndText02"); break;
			case TileTemplateNameV3::TileWide310x150ImageCollection: element.SetAttribute(value.name, L"TileWide310x150ImageCollection"); break;
			case TileTemplateNameV3::TileWide310x150PeekImage01: element.SetAttribute(value.name, L"TileWide310x150PeekImage01"); break;
			case TileTemplateNameV3::TileWide310x150PeekImage02: element.SetAttribute(value.name, L"TileWide310x150PeekImage02"); break;
			case TileTemplateNameV3::TileWide310x150PeekImage03: element.SetAttribute(value.name, L"TileWide310x150PeekImage03"); break;
			case TileTemplateNameV3::TileWide310x150PeekImage04: element.SetAttribute(value.name, L"TileWide310x150PeekImage04"); break;
			case TileTemplateNameV3::TileWide310x150PeekImage05: element.SetAttribute(value.name, L"TileWide310x150PeekImage05"); break;
			case TileTemplateNameV3::TileWide310x150PeekImage06: element.SetAttribute(value.name, L"TileWide310x150PeekImage06"); break;
			case TileTemplateNameV3::TileWide310x150PeekImageAndText01: element.SetAttribute(value.name, L"TileWide310x150PeekImageAndText01"); break;
			case TileTemplateNameV3::TileWide310x150PeekImageAndText02: element.SetAttribute(value.name, L"TileWide310x150PeekImageAndText02"); break;
			case TileTemplateNameV3::TileWide310x150PeekImageCollection01: element.SetAttribute(value.name, L"TileWide310x150PeekImageCollection01"); break;
			case TileTemplateNameV3::TileWide310x150PeekImageCollection02: element.SetAttribute(value.name, L"TileWide310x150PeekImageCollection02"); break;
			case TileTemplateNameV3::TileWide310x150PeekImageCollection03: element.SetAttribute(value.name, L"TileWide310x150PeekImageCollection03"); break;
			case TileTemplateNameV3::TileWide310x150PeekImageCollection04: element.SetAttribute(value.name, L"TileWide310x150PeekImageCollection04"); break;
			case TileTemplateNameV3::TileWide310x150PeekImageCollection05: element.SetAttribute(value.name, L"TileWide310x150PeekImageCollection05"); break;
			case TileTemplateNameV3::TileWide310x150PeekImageCollection06: element.SetAttribute(value.name, L"TileWide310x150PeekImageCollection06"); break;
			case TileTemplateNameV3::TileWide310x150SmallImageAndText01: element.SetAttribute(value.name, L"TileWide310x150SmallImageAndText01"); break;
			case TileTemplateNameV3::TileWide310x150SmallImageAndText02: element.SetAttribute(value.name, L"TileWide310x150SmallImageAndText02"); break;
			case TileTemplateNameV3::TileWide310x150SmallImageAndText03: element.SetAttribute(value.name, L"TileWide310x150SmallImageAndText03"); break;
			case TileTemplateNameV3::TileWide310x150SmallImageAndText04: element.SetAttribute(value.name, L"TileWide310x150SmallImageAndText04"); break;
			case TileTemplateNameV3::TileWide310x150SmallImageAndText05: element.SetAttribute(value.name, L"TileWide310x150SmallImageAndText05"); break;
			case TileTemplateNameV3::TileWide310x150Text01: element.SetAttribute(value.name, L"TileWide310x150Text01"); break;
			case TileTemplateNameV3::TileWide310x150Text02: element.SetAttribute(value.name, L"TileWide310x150Text02"); break;
			case TileTemplateNameV3::TileWide310x150Text03: element.SetAttribute(value.name, L"TileWide310x150Text03"); break;
			case TileTemplateNameV3::TileWide310x150Text04: element.SetAttribute(value.name, L"TileWide310x150Text04"); break;
			case TileTemplateNameV3::TileWide310x150Text05: element.SetAttribute(value.name, L"TileWide310x150Text05"); break;
			case TileTemplateNameV3::TileWide310x150Text06: element.SetAttribute(value.name, L"TileWide310x150Text06"); break;
			case TileTemplateNameV3::TileWide310x150Text07: element.SetAttribute(value.name, L"TileWide310x150Text07"); break;
			case TileTemplateNameV3::TileWide310x150Text08: element.SetAttribute(value.name, L"TileWide310x150Text08"); break;
			case TileTemplateNameV3::TileWide310x150Text09: element.SetAttribute(value.name, L"TileWide310x150Text09"); break;
			case TileTemplateNameV3::TileWide310x150Text10: element.SetAttribute(value.name, L"TileWide310x150Text10"); break;
			case TileTemplateNameV3::TileWide310x150Text11: element.SetAttribute(value.name, L"TileWide310x150Text11"); break;
			case TileTemplateNameV3::TileSquare71x71Image: element.SetAttribute(value.name, L"TileSquare71x71Image"); break;
			case TileTemplateNameV3::TileSquare71x71IconWithBadge: element.SetAttribute(value.name, L"TileSquare71x71IconWithBadge"); break;
			case TileTemplateNameV3::TileSquare150x150IconWithBadge: element.SetAttribute(value.name, L"TileSquare150x150IconWithBadge"); break;
			case TileTemplateNameV3::TileWide310x150IconWithBadgeAndText: element.SetAttribute(value.name, L"TileWide310x150IconWithBadgeAndText"); break;
			default: break;
			}
		}
		return element;
	}

	enum class TileTemplateNameV1
	{
		TileSmall,
		TileMedium,
		TileWide,
		TileLarge
	};
	inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<TileTemplateNameV1> const& value)
	{
		if (value)
		{
			switch (*value.value)
			{
			case TileTemplateNameV1::TileSmall: element.SetAttribute(value.name, L"tileSmall"); break;
			case TileTemplateNameV1::TileMedium:element.SetAttribute(value.name, L"tileMedium"); break;
			case TileTemplateNameV1::TileWide: element.SetAttribute(value.name, L"tileWide"); break;
			case TileTemplateNameV1::TileLarge:element.SetAttribute(value.name, L"tileLarge"); break;
			default: break;
			}
		}
		return element;
	}

	enum class TextStacking
	{
		Top,
		Center,
		Bottom
	};
	inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<TextStacking> const& value)
	{
		if (value)
		{
			switch (*value.value)
			{
			case TextStacking::Top: element.SetAttribute(value.name, L"top"); break;
			case TextStacking::Center: element.SetAttribute(value.name, L"center"); break;
			case TextStacking::Bottom: element.SetAttribute(value.name, L"bottom"); break;
			default:
				break;
			}
		}
		return element;
	}

	enum class Placement
	{
		Inline,
		Background,
		Peek
	};
	inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<Placement> const& value)
	{
		if (value)
		{
			switch (*value.value)
			{
			case Placement::Inline: element.SetAttribute(value.name, L"inline"); break;
			case Placement::Background: element.SetAttribute(value.name, L"background"); break;
			case Placement::Peek: element.SetAttribute(value.name, L"peek"); break;
			}
		}
		return element;
	}

	enum class HintCrop
	{
		None,
		Circle
	};
	inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<HintCrop> const& value)
	{
		if (value)
		{
			switch (*value.value)
			{
			case HintCrop::None: element.SetAttribute(value.name, L"none"); break;
			case HintCrop::Circle:element.SetAttribute(value.name, L"circle"); break;
			default:
				break;
			}
		}
		return element;
	}

	enum class HintAlign
	{
		Stretch,
		Left,
		Center,
		Right
	};
	inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<HintAlign> const& value)
	{
		if (value)
		{
			switch (*value.value)
			{
			case HintAlign::Stretch: element.SetAttribute(value.name, L"stretch"); break;
			case HintAlign::Left: element.SetAttribute(value.name, L"left"); break;
			case HintAlign::Center: element.SetAttribute(value.name, L"center"); break;
			case HintAlign::Right: element.SetAttribute(value.name, L"right"); break;
			default:
				break;
			}
		}
		return element;
	}

	enum class TextStyle
	{
		/// <summary>
		/// Style is determined by the renderer.
		/// </summary>
		Default,

		/// <summary>
		/// Default value. Paragraph font size, normal weight and opacity.
		/// </summary>
		Caption,

		/// <summary>
		/// Same as Caption but with subtle opacity.
		/// </summary>
		CaptionSubtle,

		/// <summary>
		/// H5 font size.
		/// </summary>
		Body,


		BodySubtle,
		Base,
		BaseSubtle,
		Subtitle,
		SubtitleSubtle,
		Title,
		TitleSubtle,
		TitleNumeral,
		Subheader,
		SubheaderSubtle,
		SubheaderNumeral,
		Header,
		HeaderSubtle,
		HeaderNumeral
	};
	inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<TextStyle> const& value)
	{
		if (value)
		{
			switch (*value.value)
			{
			case TextStyle::Default: element.SetAttribute(value.name, L"default"); break;
			case TextStyle::Caption: element.SetAttribute(value.name, L"caption"); break;
			case TextStyle::CaptionSubtle: element.SetAttribute(value.name, L"captionSubtle"); break;
			case TextStyle::Body: element.SetAttribute(value.name, L"body"); break;
			case TextStyle::BodySubtle: element.SetAttribute(value.name, L"bodySubtle"); break;
			case TextStyle::Base: element.SetAttribute(value.name, L"base"); break;
			case TextStyle::BaseSubtle: element.SetAttribute(value.name, L"baseSubtle"); break;
			case TextStyle::Subtitle: element.SetAttribute(value.name, L"subtitle"); break;
			case TextStyle::SubtitleSubtle: element.SetAttribute(value.name, L"subtitleSubtle"); break;
			case TextStyle::Title: element.SetAttribute(value.name, L"title"); break;
			case TextStyle::TitleSubtle: element.SetAttribute(value.name, L"titleSubtle"); break;
			case TextStyle::TitleNumeral: element.SetAttribute(value.name, L"titleNumeral"); break;
			case TextStyle::Subheader: element.SetAttribute(value.name, L"subheader"); break;
			case TextStyle::SubheaderSubtle: element.SetAttribute(value.name, L"subheaderSubtle"); break;
			case TextStyle::SubheaderNumeral: element.SetAttribute(value.name, L"subheaderNumeral"); break;
			case TextStyle::Header: element.SetAttribute(value.name, L"header"); break;
			case TextStyle::HeaderSubtle: element.SetAttribute(value.name, L"headerSubtle"); break;
			case TextStyle::HeaderNumeral: element.SetAttribute(value.name, L"headerNumeral"); break;
			default:
				break;
			}
		}
		return element;
	}

	using String = std::wstring;
	inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<String> const& value)
	{
		if (value)
		{
			element.SetAttribute(value.name, *value.value);
		}
		return element;
	}
	inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<bool> const& value)
	{
		if (value)
			element.SetAttribute(value.name, *value.value ? L"true" : L"false");
		return element;
	}


	class Visual : public INodeBase, public ISupportChild<Visual, Binding>
	{
		PropertyValue<int> m_version{ L"version" };
		PropertyValue<String> m_lang{ L"lang" };
		PropertyValue<String> m_baseUri{ L"baseUri" };
		PropertyValue<Branding> m_branding{ L"branding" };
		PropertyValue<bool> m_addImageQuery{ L"addImageQuery" };
		PropertyValue<String> m_contentId{ L"contentId" };
		PropertyValue<String> m_displayName{ L"displayName" };
	public:
		Visual& Version(int value)
		{
			m_version = value;
			return *this;
		}

		Visual& Lang(String value)
		{
			m_lang = value;
			return *this;
		}

		Visual& BaseUri(String value)
		{
			m_baseUri = value;
			return *this;
		}

		Visual& Branding(Branding value)
		{
			m_branding = value;
			return *this;
		}

		Visual& AddImageQuery(bool value)
		{
			m_addImageQuery = value;
			return *this;
		}

		Visual& ContentId(String value)
		{
			m_contentId = value;
			return *this;
		}

		Visual& DisplayName(String value)
		{
			m_displayName = value;
			return *this;
		}
		winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
		{
			return internals::MakeElement(L"visual", root, m_child, m_version, m_lang, m_baseUri, m_branding, m_addImageQuery, m_contentId, m_displayName);
		}
	};

	class Binding : public INodeBase, public ISupportChild<Binding, Image, Text, Group>
	{
		PropertyValue<TileTemplateNameV3> m_template{ L"template" };
		PropertyValue<TileTemplateNameV1> m_fallback{ L"fallback" };
		PropertyValue<String> m_lang{ L"lang" };
		PropertyValue<String> m_baseUri{ L"baseUri" };
		PropertyValue<Branding> m_branding{ L"branding" };
		PropertyValue<bool> m_addImageQuery{ L"addImageQuery" };
		PropertyValue<String> m_displayName{ L"displayName" };
		PropertyValue<TextStacking> m_hintTextStacking{ L"hint-textStacking" };
		PropertyValue<LimitedInt<0, 100>> m_hintOverlay{ L"hint-overlay" };
	public:
		Binding& Template(TileTemplateNameV3 value)
		{
			m_template = value;
			return *this;
		}
		Binding& Fallback(TileTemplateNameV1 value)
		{
			m_fallback = value;
			return *this;
		}
		Binding& Lang(String value)
		{
			m_lang = value;
			return *this;
		}
		Binding& BaseUri(String value)
		{
			m_baseUri = value;
			return *this;
		}
		Binding& Branding(Branding value)
		{
			m_branding = value;
			return *this;
		}
		Binding& AddImageQuery(bool value)
		{
			m_addImageQuery = value;
			return *this;
		}
		Binding& DisplayName(String value)
		{
			m_displayName = value;
			return *this;
		}
		Binding& HintTextStacking(TextStacking value)
		{
			m_hintTextStacking = value;
			return *this;
		}
		Binding& HintOverlay(int value)
		{
			m_hintOverlay = value;
			return *this;
		}
		winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
		{
			return internals::MakeElement(L"binding", root, m_child, m_template, m_fallback, m_lang, m_baseUri, m_branding, m_addImageQuery, m_displayName, m_hintTextStacking, m_hintOverlay);
		}
	};

	class Image : public INodeBase
	{
		PropertyValue<String> m_src{ L"src" };
		PropertyValue<Placement> m_placement{ L"placement" };
		PropertyValue<String> m_alt{ L"alt" };
		PropertyValue<bool> m_addImageQuery{ L"addImageQuery" };
		PropertyValue<HintCrop> m_hintCrop{ L"hint-crop" };
		PropertyValue<bool> m_hintRemoveMargin{ L"hint-removeMargin" };
		PropertyValue<HintAlign> m_hintAlign{ L"hint-align" };
	public:
		Image& Src(String value)
		{
			m_src = value;
			return *this;
		}
		Image& Placement(Placement value)
		{
			m_placement = value;
			return *this;
		}
		Image& Alt(String value)
		{
			m_alt = value;
			return *this;
		}
		Image& AddImageQuery(bool value)
		{
			m_addImageQuery = value;
			return *this;
		}
		Image& HintCrop(HintCrop value)
		{
			m_hintCrop = value;
			return *this;
		}
		Image& HintRemoveMargin(bool value)
		{
			m_hintRemoveMargin = value;
			return *this;
		}
		Image& HintAlign(HintAlign value)
		{
			m_hintAlign = value;
			return *this;
		}
		winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
		{
			return internals::MakeElement(L"image", root, m_src, m_placement, m_alt, m_addImageQuery, m_hintCrop, m_hintRemoveMargin, m_hintAlign);
		}
	};

	class Text : public INodeBase
	{
		PropertyValue<String> m_lang{ L"lang" };
		PropertyValue<TextStyle> m_hintStyle{ L"hint-style" };
		PropertyValue<bool> m_hintWrap{ L"hint-wrap" };
		PropertyValue<int> m_hintMaxLines{ L"hint-maxLines" };
		PropertyValue<int> m_hintMinLines{ L"hint-minLines" };
		PropertyValue<HintAlign> m_hintAlign{ L"hint-align" };
		String m_text;
	public:
		Text& Lang(String value)
		{
			m_lang = value;
			return *this;
		}
		Text& HintStyle(TextStyle value)
		{
			m_hintStyle = value;
			return *this;
		}
		Text& HintWrap(bool value)
		{
			m_hintWrap = value;
			return *this;
		}
		Text& HintMaxLines(int value)
		{
			m_hintMaxLines = value;
			return *this;
		}
		Text& HintMinLines(int value)
		{
			m_hintMinLines = value;
			return *this;
		}
		Text& HintAlign(HintAlign value)
		{
			m_hintAlign = value;
			return *this;
		}
		Text& operator()(String text)
		{
			m_text = std::move(text);
			return *this;
		}

		winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
		{
			auto element = internals::MakeElement(L"text", root, m_lang, m_hintStyle, m_hintWrap, m_hintMaxLines, m_hintMinLines, m_hintAlign);
			element.InnerText(std::move(m_text));
			return element;
		}
	};

	class Group : public INodeBase, public ISupportChild<Group, Subgroup>
	{
	public:
		winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
		{
			return internals::MakeElement(L"group", root, m_child);
		}

	};

	class Subgroup : public INodeBase, public ISupportChild<Subgroup, Text, Image>
	{
		PropertyValue<LimitedInt<0, 100>> m_hintWeight{ L"hint-weight" };
		PropertyValue<TextStacking> m_hintTextStacking{ L"hint-textStacking" };
	public:
		Subgroup& HintWeight(int value)
		{
			m_hintWeight = value;
			return *this;
		}
		Subgroup& HintTextStacking(TextStacking value)
		{
			m_hintTextStacking = value;
			return *this;
		}

		winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
		{
			return internals::MakeElement(L"subgroup", root, m_child,
				m_hintWeight, m_hintTextStacking);
		}
	};

	class Tile
	{
		winrt::Windows::Data::Xml::Dom::XmlDocument m_doc;
	public:
		template<typename...T> requires (Accept<T, Visual> || ...)
			Tile& operator()(T&&... child)
		{
			auto tileElement = m_doc.CreateElement(L"tile");
			(tileElement.AppendChild(child.Get(m_doc)), ...);
			m_doc.AppendChild(tileElement);
			return *this;
		}
		operator winrt::Windows::UI::Notifications::TileNotification()
		{
			auto str = m_doc.GetXml();
			return winrt::Windows::UI::Notifications::TileNotification{ m_doc };
		}
	};
}