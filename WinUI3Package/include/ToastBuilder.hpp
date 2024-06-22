#pragma once
#include <optional>
#include <type_traits>
#include <vector>
#include <string_view>
#include <winrt/Windows.Data.Xml.Dom.h>
#include <winrt/Windows.UI.Notifications.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Microsoft.Windows.AppNotifications.h>
#include <unordered_map>
#include <functional>

namespace ToastBuilder
{
    /**
     * @brief A class for handling toast notification activator, where instances of `Action` automatically add handlers to.
     * @details See documentation of `class Action` to see how to add a handler. Then you can either handle toast activation by inheriting your `App` class from this class
       (if you are only handling toast activation event), then add a `using` statement, like this
     * @code{.cpp}
     *  //App.h
     *  struct App : AppT<App>, ToastBuilder::ToastNotificationHandler
     *  {
     *      //...
     *      using ToastBuilder::ToastNotificationHandler::OnActivated;
     *  };
     * @endcode
     *
     * Or you can have other handlers, then you check whether the activation is handled by this toast notification handler
     * @code{.cpp}
     *  struct App : AppT<App>
     *  {
     *      void OnActivated(winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs const& args)
            {
                if (ToastNotificationHandler::OnActivated(args))
                    return;
                else
                {
                    //pass the args to other handlers
                }
            }
     *  };
     * @endcode
    */
    class ToastNotificationHandler
    {
    public:
        using ToastArgumentType = winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs;
    private:
        std::unordered_map<winrt::hstring, std::function<void(ToastArgumentType)>> m_actionHandler;

        ToastNotificationHandler()
        {
            auto manager = winrt::Microsoft::Windows::AppNotifications::AppNotificationManager::Default();
            manager.NotificationInvoked([](auto sender, winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs const& args)
                {
                    OnActivated(args);
                });
            manager.Register();
        }
    public:


        static ToastNotificationHandler& GetInstance()
        {
            static ToastNotificationHandler s_instance;
            return s_instance;
        }

        /**
         * @brief Called by the destructor of `class Action`, so it automatically add a handler if there is one.
         * @tparam Handler Should be in the form of `void(winrt::Windows::ApplicationModel::Activation::ToastNotificationActivatedEventArgs)`
         * @param arg Argument of `Action`, used as a unique id to the ToastNotificationActivatedEventArgs
         * @param handler The handler
        */
        template<typename Handler>
        void HandleAction(winrt::hstring arg, Handler&& handler)
        {
            m_actionHandler.emplace(arg, std::forward<Handler>(handler));
        }

        /**
         * @brief See documentation of this class
         * @retval true if the Activation is handled
         * @retval false if the Activation is not handled
        */
        static bool OnActivated(winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs const& args)
        {
            if (auto iter = GetInstance().m_actionHandler.find(args.Argument()); iter != GetInstance().m_actionHandler.end())
            {
                iter->second(args);
                return true;
            }
            return false;
        }
    };
#pragma region ForwardDeclaration
    class Toast;
    class Visual;
    class Binding;
    class Image;
    class Text;
    class Progress;
    class Group;
    class Subgroup;
    class Audio;
    class Commands;
    class Command;
    class Actions;
    class Action;
    class Input;
    class Selection;
    class Header;
#pragma endregion

#pragma region Enums
    enum Placement
    {
        Attribution,
        ContextMenu,
        AppLogoOverride,
        Hero
    };
    enum ToastDuration
    {
        Long,
        Short
    };
    enum ToastScenario
    {
        Reminder,
        Alarm,
        IncomingCall,
        Urgent
    };
    enum Crop
    {
        Circle
    };
    enum CommandId
    {
        Snooze,
        Dismiss,
        Video,
        Voice,
        Decline,
    };
    enum ActivationType
    {
        Foreground,
        Background,
        Protocol
    };

    enum ButtonStyle
    {
        Success,
        Critical
    };
    enum InputType
    {
        text,
        Selection
    };
#pragma endregion

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

#pragma region XmlAttributeSetters
    inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<std::wstring> const& value)
    {
        if (value)
            element.SetAttribute(value.name, *value.value);
        return element;
    }

    inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<int> const& value)
    {
        if (value)
            element.SetAttribute(value.name, winrt::to_hstring(*value.value));
        return element;
    }

    inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<Placement> const& value)
    {
        if (value)
        {
            switch (*value.value)
            {
            case Placement::Attribution:
                element.SetAttribute(value.name, L"attribution");
                break;
            case Placement::ContextMenu:
                element.SetAttribute(value.name, L"contextmenu");
                break;
            case Placement::AppLogoOverride:
                element.SetAttribute(value.name, L"appLogoOverride");
                break;
            case Placement::Hero:
                element.SetAttribute(value.name, L"hero");
                break;
            default:
                break;
            }
        }
        return element;
    }

    inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<bool> const& value)
    {
        if (value)
            element.SetAttribute(value.name, *value.value ? L"true" : L"false");
        return element;
    }

    inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<CommandId> const& value)
    {
        if (value)
        {
            switch (*value.value)
            {
            case CommandId::Snooze:
                element.SetAttribute(value.name, L"snooze");
                break;
            case CommandId::Dismiss:
                element.SetAttribute(value.name, L"dismiss");
                break;
            case CommandId::Video:
                element.SetAttribute(value.name, L"video");
                break;
            case CommandId::Voice:
                element.SetAttribute(value.name, L"voice");
                break;
            case CommandId::Decline:
                element.SetAttribute(value.name, L"decline");
                break;
            default:
                break;
            }
        }
        return element;
    }

    inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<ToastScenario> const& value)
    {
        if (value)
        {
            switch (*value.value)
            {
            case ToastScenario::Alarm:
                element.SetAttribute(value.name, L"decline");
                break;
            case ToastScenario::IncomingCall:
                element.SetAttribute(value.name, L"incomingCall");
                break;
            case ToastScenario::Reminder:
                element.SetAttribute(value.name, L"reminder");
                break;
            case ToastScenario::Urgent:
                element.SetAttribute(value.name, L"urgent");
                break;
            default:
                break;
            }
        }
        return element;
    }

    inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<Crop> const& value)
    {
        if (value)
        {
            element.SetAttribute(value.name, L"circle");
        }
        return element;
    }

    inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<ActivationType> const& value)
    {
        if (value)
        {
            switch (*value.value)
            {
            case ActivationType::Foreground:
                element.SetAttribute(value.name, L"foreground");
                break;
            case ActivationType::Background:
                element.SetAttribute(value.name, L"background");
                break;
            case ActivationType::Protocol:
                element.SetAttribute(value.name, L"protocol");
                break;
            default:
                break;
            }
        }
        return element;
    }

    inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<InputType> const& value)
    {
        if (value)
        {
            switch (*value.value)
            {
            case InputType::text:
                element.SetAttribute(value.name, L"text");
                break;
            case InputType::Selection:
                element.SetAttribute(value.name, L"selection");
                break;
            default:
                break;
            }
        }
        return element;
    }

    inline winrt::Windows::Data::Xml::Dom::XmlElement& operator<<(winrt::Windows::Data::Xml::Dom::XmlElement& element, PropertyValue<ToastDuration> const& value)
    {
        if (value)
        {
            switch (*value.value)
            {
            case ToastDuration::Long:
                element.SetAttribute(value.name, L"long");
                break;
            case ToastDuration::Short:
                element.SetAttribute(value.name, L"short");
                break;
            default:
                break;
            }
        }
        return element;
    }
#pragma endregion

    /**
     * @brief Base class for a toast node, child class need to override the `Get()` method which should create its `XmlElement` representing this node
     * @tparam Parent For limiting child type. That is the `Parent` type only accepts `IToastNode<Parent>` child in its `operator()(auto&&...)`
     *
    */
    template<typename Parent>
    struct IToastNode
    {
        virtual winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) = 0;
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

#pragma region NodesType
    class Toast
    {
        PropertyValue<std::wstring> m_launch{ L"launch" };
        PropertyValue<ToastDuration> m_duration{ L"duration" };
        PropertyValue<std::wstring> m_displayTimeStamp{ L"displayTimeStamp" };
        PropertyValue<ToastScenario> m_scenario{ L"scenario" };
        PropertyValue<bool> m_useButtonStyle{ L"useButtonStyle" };
        winrt::Windows::Data::Xml::Dom::XmlDocument m_doc;
    public:

        Toast& Launch(std::wstring launch)
        {
            m_launch = launch;
            return *this;
        }

        Toast& Duration(ToastDuration duration)
        {
            m_duration = duration;
            return *this;
        }

        Toast& DisplayTimeStamp(std::wstring displayTimeStamp)
        {
            m_displayTimeStamp = displayTimeStamp;
            return *this;
        }

        Toast& Scenario(ToastScenario scenario)
        {
            m_scenario = scenario;
            return *this;
        }

        Toast& UseButtonStyle(bool useButtonStyle)
        {
            m_useButtonStyle = useButtonStyle;
            return *this;
        }

        template<typename... T> requires (std::is_base_of_v<IToastNode<Toast>, std::remove_reference_t<T>> && ...)
            Toast& operator()(T&& ...child)
        {
            auto toastElement = m_doc.CreateElement(L"toast");
            (toastElement.AppendChild(child.Get(m_doc)), ...);

            toastElement
                << m_launch
                << m_duration
                << m_displayTimeStamp
                << m_scenario
                << m_useButtonStyle;

            m_doc.AppendChild(toastElement);

            auto xml = m_doc.GetXml();
            return *this;
        }

        operator winrt::Windows::UI::Notifications::ToastNotification()
        {
            return winrt::Windows::UI::Notifications::ToastNotification{ m_doc };
        }
    };

    class Visual : IToastNode<Toast>
    {
        PropertyValue<int> m_version{ L"version" };
        PropertyValue<std::wstring> m_lang{ L"lang" };
        PropertyValue<std::wstring> m_baseUri{ L"baseUri" };
        PropertyValue<std::wstring> m_branding{ L"branding" };
        PropertyValue<bool> m_addImageQuery{ L"addImageQuery" };
        std::vector<Binding*> m_child;
    public:
        Visual& Version(int version)
        {
            m_version = version;
            return *this;
        }

        Visual& Lang(std::wstring lang)
        {
            m_lang = lang;
            return *this;
        }

        Visual& BaseUri(std::wstring baseUri)
        {
            m_baseUri = baseUri;
            return *this;
        }

        Visual& Branding(std::wstring branding)
        {
            m_branding = branding;
            return *this;
        }

        Visual& AddImageQuery(bool addImageQuery)
        {
            m_addImageQuery = addImageQuery;
            return *this;
        }

        template<typename...T>   requires (std::is_same_v<std::remove_reference_t<T>, Binding> && ...)
            Visual& operator()(T&&... bindings)
        {
            (m_child.push_back(&bindings), ...);
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root)
        {
            return internals::MakeElement(L"visual", root, m_child, m_version, m_lang, m_baseUri);
        }
    };

    class Binding : public IToastNode<Visual>
    {
        PropertyValue<std::wstring> m_template{ L"template", L"ToastGeneric" };
        PropertyValue<std::wstring> m_fallback{ L"fallback" };
        PropertyValue<std::wstring> m_lang{ L"lang" };
        PropertyValue<bool> m_addImageQuery{ L"addImageQuery" };
        PropertyValue<std::wstring> m_baseUri{ L"baseUri" };
        PropertyValue<std::wstring> m_branding{ L"branding" }; //not used
        std::vector<IToastNode<Binding>*> m_child;
    public:
        Binding& Template(std::wstring templateType)
        {
            m_template = templateType;
            return *this;
        }

        Binding& Fallback(std::wstring fallback)
        {
            m_fallback = fallback;
            return *this;
        }

        Binding& Lang(std::wstring lang)
        {
            m_lang = lang;
            return *this;
        }

        Binding& AddImageQuery(bool addImageQuery)
        {
            m_addImageQuery = addImageQuery;
            return *this;
        }

        Binding& BaseUri(std::wstring baseUri)
        {
            m_baseUri = baseUri;
            return *this;
        }

        Binding& Branding(std::wstring branding)
        {
            m_branding = branding;
            return *this;
        }


        template<typename... T> requires (std::is_base_of_v<IToastNode<Binding>, std::remove_reference_t<T>> && ...)
            Binding& operator()(T&&... children)
        {
            OutputDebugString(std::to_wstring(sizeof...(T)).data());
            (m_child.push_back(&children), ...);
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            return internals::MakeElement(L"binding", root, m_child, m_template, m_fallback, m_lang, m_addImageQuery, m_baseUri, m_branding);
        }

    };

    class Image : public IToastNode<Binding>
    {
        PropertyValue<int> m_id{ L"id" };
        PropertyValue<std::wstring> m_src{ L"src" };
        PropertyValue<std::wstring> m_alt{ L"alt" };
        PropertyValue<bool> m_addImageQuery{ L"addImageQuery" };
        PropertyValue<Placement> m_placement{ L"placement" };
        PropertyValue<Crop> m_hintCrop{ L"hint-crop" };
    public:
        Image& Id(int id)
        {
            m_id = id;
            return *this;
        }

        Image& Src(std::wstring src)
        {
            m_src = src;
            return *this;
        }

        Image& Alt(std::wstring alt)
        {
            m_alt = alt;
            return *this;
        }

        Image& AddImageQuery(bool addImageQuery)
        {
            m_addImageQuery = addImageQuery;
            return *this;
        }

        Image& Placement(Placement placement)
        {
            m_placement = placement;
            return *this;
        }

        Image& HintCrop(Crop crop)
        {
            m_hintCrop = crop;
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            return internals::MakeElement(L"image", root, m_id, m_src, m_alt, m_addImageQuery, m_placement, m_hintCrop);
        }
    };

    class Text : public IToastNode<Binding>
    {
        PropertyValue<int> m_id{ L"id" };
        PropertyValue<std::wstring> m_lang{ L"lang" };
        PropertyValue<Placement> m_placement{ L"placement" };
        PropertyValue<bool> m_hintCallScenarioCenterAlign{ L"hint-callScenarioCenterAlign" };
        std::wstring m_text;
    public:
        Text& Id(int id)
        {
            m_id = id;
            return *this;
        }


        Text& Lang(std::wstring lang)
        {
            m_lang = lang;
            return *this;
        }

        Text& Placement(Placement placement)
        {
            m_placement = placement;
            return *this;
        }

        Text& HintCallScenarioCenterAlign(bool hint_callScenarioCenterAlign)
        {
            m_hintCallScenarioCenterAlign = hint_callScenarioCenterAlign;
            return *this;
        }

        Text& operator()(std::wstring text)
        {
            m_text = std::move(text);
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            auto element = internals::MakeElement(L"text", root, m_id, m_lang, m_placement, m_hintCallScenarioCenterAlign);
            element.InnerText(std::move(m_text));
            return element;
        }
    };

    class Progress : public IToastNode<Binding>
    {
        PropertyValue<std::wstring> m_title{ L"title" };
        PropertyValue<std::wstring> m_status{ L"status" };
        PropertyValue<std::wstring> m_value{ L"value" };
        PropertyValue<std::wstring> m_valueStringOverride{ L"valueStringOverride" };
    public:
        Progress& Title(std::wstring title)
        {
            m_title = title;
            return *this;
        }

        Progress& Status(std::wstring status)
        {
            m_status = status;
            return *this;
        }

        Progress& Value(std::wstring value)
        {
            m_value = value;
            return *this;
        }

        Progress& ValueStringOverride(std::wstring valueStringOverride)
        {
            m_valueStringOverride = valueStringOverride;
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            return internals::MakeElement(L"progress", root, m_title, m_status, m_value, m_valueStringOverride);
        }
    };

    class Subgroup : IToastNode<Group>
    {
        std::vector<IToastNode<Subgroup>*> m_child;
    public:
        template<typename... T> requires (std::disjunction_v<std::is_same<std::remove_reference_t<T>, Text>, std::is_same<std::remove_reference_t<T>, Image>> && ...)
            Subgroup& operator()(T&& ... elements)
        {
            (m_child.push_back(&elements), ...);
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            return internals::MakeElement(L"subgroup", root, m_child);
        }
    };

    class Group : IToastNode<Binding>
    {
        Subgroup* m_subgroup{};
    public:
        Group& operator()(Subgroup&& subgroup)
        {
            m_subgroup = &subgroup;
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            auto element = internals::MakeElement(L"group", root);
            if (m_subgroup)
                element.AppendChild(m_subgroup->Get(root));
            return element;
        }
    };

    class Audio : public IToastNode<Toast>
    {
        PropertyValue<std::wstring> m_src{ L"src", L"ms-winsoundevent:Notification.Default" };
        PropertyValue<bool> m_loop{ L"loop" };
        PropertyValue<bool> m_silent{ L"silent" };
    public:
        Audio& Src(std::wstring src)
        {
            if (!src.empty())
                m_src = src;
            return *this;
        }

        Audio& Loop(bool loop)
        {
            m_loop = loop;
            return *this;
        }

        Audio& Silent(bool silent)
        {
            m_silent = silent;
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            return internals::MakeElement(L"audio", root, m_src, m_loop, m_silent);
        }

        //Built-in non-looping sound, set Loop to false or leave it as default
        //https://learn.microsoft.com/en-us/uwp/schemas/tiles/toastschema/element-audio
        constexpr static auto Default = L"ms-winsoundevent:Notification.Default";
        constexpr static auto IM = L"ms-winsoundevent:Notification.IM";
        constexpr static auto Mail = L"ms-winsoundevent:Notification.Mail";
        constexpr static auto Reminder = L"ms-winsoundevent:Notification.Reminder";
        constexpr static auto SMS = L"ms-winsoundevent:Notification.SMS";

        //Built-in looping sound, set Loop to true
        struct Looping
        {
            constexpr static auto Alarm = L"ms-winsoundevent:Notification.Alarm";
            constexpr static auto Alarm2 = L"ms-winsoundevent:Notification.Looping.Alarm2";
            constexpr static auto Alarm3 = L"ms-winsoundevent:Notification.Looping.Alarm3";
            constexpr static auto Alarm4 = L"ms-winsoundevent:Notification.Looping.Alarm4";
            constexpr static auto Alarm5 = L"ms-winsoundevent:Notification.Looping.Alarm5";
            constexpr static auto Alarm6 = L"ms-winsoundevent:Notification.Looping.Alarm6";
            constexpr static auto Alarm7 = L"ms-winsoundevent:Notification.Looping.Alarm7";
            constexpr static auto Alarm8 = L"ms-winsoundevent:Notification.Looping.Alarm8";
            constexpr static auto Alarm9 = L"ms-winsoundevent:Notification.Looping.Alarm9";
            constexpr static auto Alarm10 = L"ms-winsoundevent:Notification.Looping.Alarm10";
            constexpr static auto Call = L"ms-winsoundevent:Notification.Looping.Call";
            constexpr static auto Call2 = L"ms-winsoundevent:Notification.Looping.Call2";
            constexpr static auto Call3 = L"ms-winsoundevent:Notification.Looping.Call3";
            constexpr static auto Call4 = L"ms-winsoundevent:Notification.Looping.Call4";
            constexpr static auto Call5 = L"ms-winsoundevent:Notification.Looping.Call5";
            constexpr static auto Call6 = L"ms-winsoundevent:Notification.Looping.Call6";
            constexpr static auto Call7 = L"ms-winsoundevent:Notification.Looping.Call7";
            constexpr static auto Call8 = L"ms-winsoundevent:Notification.Looping.Call8";
            constexpr static auto Call9 = L"ms-winsoundevent:Notification.Looping.Call9";
            constexpr static auto Call10 = L"ms-winsoundevent:Notification.Looping.Call10";
        };
    };

    class Commands : public IToastNode<Toast>
    {
        PropertyValue<ToastScenario> m_scenario{ L"scenario" };
        std::vector<Command*> m_child;
    public:
        Commands& Scenario(ToastScenario scenario)
        {
            m_scenario = scenario;
            return *this;
        }

        template<typename... T> requires (std::is_same_v<std::remove_reference_t<T>, Command> && ...)
            Commands& operator()(T&&... command)
        {
            (m_child.push_back(&command), ...);
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            return internals::MakeElement(L"commands", root, m_child, m_scenario);
        }
    };

    class Command : public IToastNode<Commands>
    {
        PropertyValue<CommandId> m_id{ L"id" };
        PropertyValue<std::wstring> m_arguments{ L"arguments" };
    public:
        Command& Id(CommandId id)
        {
            m_id = id;
            return *this;
        }

        Command& Arguments(std::wstring arguments)
        {
            m_arguments = arguments;
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            return internals::MakeElement(L"command", root, m_id, m_arguments);
        }
    };

    class Actions : public IToastNode<Toast>
    {
        std::vector<IToastNode<Actions>*> m_child;
    public:
        template<typename... T> requires (std::is_same_v<std::remove_reference_t<T>, Action> && ...)
            Actions& operator()(T&&... actions)
        {
            (m_child.push_back(&actions), ...);
            return *this;
        }
        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            return internals::MakeElement(L"actions", root, m_child);
        }
    };

    class Action : public IToastNode<Actions>
    {
        PropertyValue<std::wstring> m_content{ L"content" };
        PropertyValue<std::wstring> m_arguments{ L"arguments" };
        PropertyValue<ActivationType> m_activationType{ L"activationType" };
        PropertyValue<Placement> m_placement{ L"placement" };
        PropertyValue<std::wstring> m_imageUri{ L"imageUri" };
        PropertyValue<std::wstring> m_hintInputId{ L"hint-inputid" };
        PropertyValue<std::wstring> m_hintButtonStyle{ L"hint-buttonStyle" };
        PropertyValue<std::wstring> m_hintToolTip{ L"hint-toolTip" };
        std::function<void(ToastNotificationHandler::ToastArgumentType)> m_handler;
    public:
        Action& Content(std::wstring content)
        {
            m_content = content;
            return *this;
        }

        Action& Arguments(std::wstring arguments)
        {
            m_arguments = arguments;
            return *this;
        }

        Action& ActivationType(ActivationType type)
        {
            m_activationType = type;
            return *this;
        }

        Action& Placement(Placement placement)
        {
            m_placement = placement;
            return *this;
        }

        Action& ImageUri(std::wstring imageUri)
        {
            m_imageUri = imageUri;
            return *this;
        }

        Action& HintInputId(std::wstring hintInputId)
        {
            m_hintInputId = hintInputId;
            return *this;
        }

        Action& HintButtonStyle(std::wstring hintButtonStyle)
        {
            m_hintButtonStyle = hintButtonStyle;
            return *this;
        }

        Action& HintToolTip(std::wstring hintToolTip)
        {
            m_hintToolTip = hintToolTip;
            return *this;
        }

        /**
         * @brief Handles the click action
         * @tparam Handler Type of the handler function, should be `void(winrt::Windows::ApplicationModel::Activation::ToastNotificationActivatedEventArgs)`
         * @param handler The handler, should be a function that convertible to `void(winrt::Windows::ApplicationModel::Activation::ToastNotificationActivatedEventArgs)`
         * @see Documentation of `class ToastActivationHandler`
        */
        template<typename Handler>
        Action& Click(Handler&& handler)
        {
            m_handler = std::forward<Handler>(handler);
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            return internals::MakeElement(
                L"action",
                root,
                m_content,
                m_arguments,
                m_activationType,
                m_placement,
                m_imageUri,
                m_hintInputId,
                m_hintButtonStyle,
                m_hintToolTip
            );
        }

        ~Action()
        {
            ToastNotificationHandler::GetInstance().HandleAction(m_arguments.value->data(), std::move(m_handler));
        }
    };

    class Input : public IToastNode<Actions>
    {
        PropertyValue<std::wstring> m_id{ L"id" };
        PropertyValue<InputType> m_type{ L"type" };
        PropertyValue<std::wstring> m_placeHolderContent{ L"placeHolderContent" };
        PropertyValue<std::wstring> m_title{ L"title" };
    public:
        Input& Id(std::wstring id)
        {
            m_id = id;
            return *this;
        }

        Input& Type(InputType type)
        {
            m_type = type;
            return *this;
        }

        Input& PlaceHolderContent(std::wstring placeholderContent)
        {
            m_placeHolderContent = placeholderContent;
            return *this;
        }

        Input& Title(std::wstring title)
        {
            m_title = title;
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            return internals::MakeElement(L"input", root, m_id, m_type, m_placeHolderContent, m_title);
        }
    };

    class Selection : public IToastNode<Input>
    {
        PropertyValue<std::wstring> m_id{ L"id" };
        PropertyValue<std::wstring> m_content{ L"content" };
    public:
        Selection& Id(std::wstring id)
        {
            m_id = id;
            return *this;
        }

        Selection& Content(std::wstring content)
        {
            m_content = content;
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            return internals::MakeElement(L"selection", root, m_id, m_content);
        }
    };

    class Header : IToastNode<Toast>
    {
        PropertyValue<std::wstring> m_id;
        PropertyValue<std::wstring> m_title;
        PropertyValue<std::wstring> m_arguments;
        PropertyValue<ActivationType> m_activationType;
    public:
        Header& Id(std::wstring id)
        {
            m_id = id;
            return *this;
        }

        Header& Title(std::wstring title)
        {
            m_title = title;
            return *this;
        }

        Header& Arguments(std::wstring arguments)
        {
            m_arguments = arguments;
            return *this;
        }

        Header& ActivationType(ActivationType activationType)
        {
            m_activationType = activationType;
            return *this;
        }

        winrt::Windows::Data::Xml::Dom::XmlElement Get(winrt::Windows::Data::Xml::Dom::XmlDocument& root) override
        {
            return internals::MakeElement(L"header", root, m_id, m_title, m_arguments, m_activationType);
        }
    };
#pragma endregion
}