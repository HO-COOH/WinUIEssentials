#pragma once
#include <string_view>
#include <winrt/Windows.Foundation.h>
#include <format>
#include <vector>
#if __has_include(<boost/algorithm/string.hpp>)
    #include <boost/algorithm/string.hpp>
#define WinUIEssential_UseBoost
#else
#include <numeric>
#endif

namespace BuiltInUris
{
    struct UriBase : private std::wstring_view
    {
        constexpr UriBase(std::wstring_view uri) : std::wstring_view{ uri }{}
        operator winrt::Windows::Foundation::Uri() const { return winrt::Windows::Foundation::Uri{ static_cast<std::wstring_view const&>(*this) }; }
    };


    //https://learn.microsoft.com/en-us/windows/uwp/launch-resume/launch-settings-app
    namespace Settings
    {
#pragma region Accounts
        struct Workplace : public UriBase
        {
            constexpr static inline UriBase Provisioning{ L"ms-settings:workplace-provisioning" };
            constexpr static inline UriBase RepairToken{ L"ms-settings:workplace-repairtoken" };
            constexpr Workplace(std::wstring_view uri) : UriBase{ uri } { }
        }; constexpr Workplace Workplace{ L"ms-settings:workplace" };
        constexpr UriBase EmailAndAccounts{ L"ms-settings:emailandaccounts" };
        constexpr UriBase OtherUsers{ L"ms-settings:otherusers" };
        constexpr UriBase AssignedAccess{ L"ms-settings:assignedaccess" };
        struct SignInOptions : public UriBase
        {
            constexpr static inline UriBase DynamicLock{ L"ms-settings:signinoptions-dynamic-lock" };
            constexpr static inline UriBase LaunchFaceEnrollment{ L"ms-settings:signinoptions-launchfaceencrollment" };
            constexpr static inline UriBase LaunchFingerprintEnrollment{ L"ms-settings:signinoptions-launchfingerprintenrollment" };
            constexpr static inline UriBase LaunchSecurityKeyEnrollment{ L"ms-settings:signinoptions-launchsecuritykeyenrollment" };
            constexpr SignInOptions(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr SignInOptions SignInOptions{ L"ms-settings:signinoptions" };
        constexpr UriBase Sync{ L"ms-settings:sync" };
        constexpr UriBase YourInfo{ L"ms-settings:yourinfo" };
#pragma endregion

#pragma region Apps
        struct DefaultApps : winrt::Windows::Foundation::Uri
        {
            struct RegisteredAppUser : std::wstring_view
            {
                using BaseType = std::wstring_view;
                constexpr RegisteredAppUser(std::wstring_view name) : std::wstring_view{ name }{}
            };
            struct RegisteredAppMachine : std::wstring_view
            {
                using BaseType = std::wstring_view;
                constexpr RegisteredAppMachine(std::wstring_view name) : std::wstring_view{ name }{}
            };
            struct RegisteredAUMID : std::wstring_view
            {
                using BaseType = std::wstring_view;
                constexpr RegisteredAUMID(std::wstring_view applicationUserModelId) : std::wstring_view{ applicationUserModelId }{}
            };

            DefaultApps(RegisteredAppUser registeredAppUser) :
                Uri{ std::format(L"ms-settings:defaultapps?registeredAppUser={}", winrt::Windows::Foundation::Uri::EscapeComponent(registeredAppUser)) }
            {
            }
            DefaultApps(RegisteredAppMachine registeredAppMachine) :
                Uri{ std::format(L"ms-settings:defaultapps?registeredAppMachine={}", winrt::Windows::Foundation::Uri::EscapeComponent(registeredAppMachine)) }
            {
            }
            DefaultApps(RegisteredAUMID registeredAUMID) :
                Uri{ std::format(L"ms-settings:defaultapps?registeredAUMID={}", static_cast<RegisteredAUMID::BaseType&>(registeredAUMID)) }
            {
            }
        };
        constexpr UriBase DefaultApps{ L"ms-settings:defaultapps" };
        struct AppsFeatures : UriBase
        {
            constexpr static inline UriBase App{ L"ms-settings:appsfeatures-app" };
            constexpr AppsFeatures(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr AppsFeatures AppsFeatures{ L"ms-settings:appsfeatures" };
        constexpr UriBase AppsForWebsites{ L"ms-settings:appsforwebsites" };
        constexpr UriBase DefaultBrowserSettings{ L"ms-settings:defaultbrowsersettings" };
        constexpr UriBase OptionalFeatures{ L"ms-settings:optionalfeatures" };
        struct Maps : UriBase
        {
            constexpr static inline UriBase DownloadMaps{ L"ms-settings:maps-downloadmaps" };
            constexpr Maps(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr Maps Maps{ L"ms-settings:maps" };
        constexpr UriBase StartupApps{ L"ms-settints:startupapps" };
        constexpr UriBase VideoPlayback{ L"ms-setttings:videoplayback" };
#pragma endregion

#pragma region ControlCenter
        constexpr UriBase ControlCenter{ L"ms-settings:controlcenter" };
#pragma endregion

#pragma region Cortana
        struct Cortana : UriBase
        {
            constexpr static inline UriBase Notifications{ L"ms-settings:cortana-notifications" };
            constexpr static inline UriBase MoreDetails{ L"ms-settings:cortana-moredetails" };
            constexpr static inline UriBase Permissions{ L"ms-settings:cortana-permissions" };
            constexpr static inline UriBase WindowsSearch{ L"ms-settings:cortana-windowssearch" };
            constexpr static inline UriBase Language{ L"ms-settings:cortana-language" };
            constexpr static inline UriBase TalkToCortana{ L"ms-settings:cortana-talktocortana" };
            constexpr Cortana(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr Cortana Cortana{ L"ms-settings:cortana" };
#pragma endregion

#pragma region Devices
        constexpr UriBase Autoplay{ L"ms-settings:autoplay" };
        constexpr UriBase Bluetooth{ L"ms-settings:bluetooth" };
        constexpr UriBase ConnectedDevices{ L"ms-settings:connecteddevices" };
        //constexpr UriBase Camera{ L"ms-settings:camera" };
        struct Camera : UriBase
        {
            //Camera(std::wstring_view cameraId) : Uri{ std::format(L"ms-settings:camera?cameraId=", Uri::EscapeComponent(cameraId)) } {}
            constexpr Camera(std::wstring_view uri) : UriBase{ uri } {}
            winrt::Windows::Foundation::Uri operator()(std::wstring_view cameraId) const
            {
                return winrt::Windows::Foundation::Uri{ std::format(L"ms-settings:camera?cameraId=", winrt::Windows::Foundation::Uri::EscapeComponent(cameraId)) };
            }
        }; constexpr Camera Camera{ L"ms-settings:camera" };
        constexpr UriBase MouseTouchpad{ L"ms-settings:mousetouchpad" };
        constexpr UriBase Pen{ L"ms-settings:pen" };
        constexpr UriBase Printers{ L"ms-settings:printers" };
        namespace Devices
        {
            constexpr UriBase Touch{ L"ms-settings:devices-touch" };
            constexpr UriBase Touchpad{ L"ms-settings:devices-touchpad" };
        }
        namespace DevicesTyping
        {
            constexpr UriBase HwkbTextSuggestions{ L"ms-settings:devicestyping-hwkbtextsuggestions" };
        }
        constexpr UriBase Typing{ L"ms-settings:typing" };
        constexpr UriBase USB{ L"ms-settings:usb" };
        constexpr UriBase Wheel{ L"ms-settings:wheel" };
#pragma endregion

#pragma region EaseOfAccess
        namespace EaseOfAccess
        {
            constexpr UriBase Audio{ L"ms-settings:easeofaccess-audio" };
            constexpr UriBase ClosedCaptioning{ L"ms-settings:easeofaccess-closedcaptioning" };
            struct ColorFilter : UriBase
            {
                constexpr ColorFilter(std::wstring_view uri) : UriBase{ uri } {}
                constexpr static inline UriBase AdaptiveColorLink{ L"ms-settings:easeofaccess-colorfilter-adaptivecolorlink" };
                constexpr static inline UriBase BlueLightLink{ L"ms-settings:easeofaccess-colorfilter-bluelightlink" };
            };  constexpr ColorFilter ColorFilter{ L"ms-settings:easeofaccess-colorfilter" };
            constexpr UriBase Display{ L"ms-settings:easeofaccess-display" };
            constexpr UriBase EyeControl{ L"ms-settings:easeofaccess-eyecontrol" };
            constexpr UriBase HighContrast{ L"ms-settings:easeofaccess-highcontrast" };
            constexpr UriBase Keryboard{ L"ms-settings:easeofaccess-keyboard" };
            constexpr UriBase Magnifier{ L"ms-settings:easeofaccess-magnifier" };
            constexpr UriBase Mouse{ L"ms-settings:easeofaccess-mouse" };
            constexpr UriBase MousePionter{ L"ms-settings:easeofaccess-mousepointer" };
            struct Narrator : UriBase
            {
                constexpr Narrator(std::wstring_view uri) : UriBase{ uri } { }
                constexpr static inline UriBase IsAutoStartEnabled{ L"ms-settings:easeofaccess-isautostartenabled" };
            }; constexpr UriBase Narrator{ L"ms-settings:easeofaccess-narrator" };
            constexpr UriBase SpeechRecognition{ L"ms-settings:easeofaccess-speechrecognition" };
            constexpr UriBase Cursor{ L"ms-settings:easeofaccess-cursor" };
            constexpr UriBase VisualEffects{ L"ms-settings:easeofaccess-visualeffects" };
        }
        constexpr UriBase Fonts{ L"ms-settings:fonts" };
#pragma endregion

#pragma region Extras
        constexpr UriBase Extras{ L"ms-settings:extras" };
#pragma endregion

#pragma region FamilyGroup
        namespace Family
        {
            constexpr UriBase Group{ L"ms-settings:family-group" };
        }
#pragma endregion

#pragma region Gaming
        namespace Gaming
        {
            constexpr UriBase GameBar{ L"ms-settings:gaming-gamebar" };
            constexpr UriBase GameDVR{ L"ms-settings:gaming-gamedvr" };
            constexpr UriBase TruePlay{ L"ms-settings:gaming-trueplay" };
            constexpr UriBase GameMode{ L"ms-settings:gaming-gamemode" };
        }
        constexpr UriBase QuietMomentsGame{ L"ms-settings:quietmomentsgame" };
#pragma endregion

#pragma region MixedReality
        namespace Holographic
        {
            constexpr UriBase Audio{ L"ms-settings:holographic-audio" };
            constexpr UriBase Headset{ L"ms-settings:holographic-headset" };
            constexpr UriBase Management{ L"ms-settings:holographic-management" };
            constexpr UriBase StartupAndDesktop{ L"ms-settings:holographic-startupanddesktop" };
        }
#pragma endregion

#pragma region NetworkAndInternet
        namespace Network
        {
            constexpr UriBase Status{ L"ms-settings:network-status" };
            constexpr UriBase AdvancedSettings{ L"ms-settings:network-advancedsettings" };
            constexpr UriBase AirplaneMode{ L"ms-settings:network-airplanemode" };
            constexpr UriBase Cellular{ L"ms-settings:network-cellular" };
            constexpr UriBase Dialup{ L"ms-settings:network-dialup" };
            constexpr UriBase DirectAccess{ L"ms-settings:network-directaccess" };
            constexpr UriBase Ethernet{ L"ms-settings:network-ethernet" };
            constexpr UriBase WifiSettings{ L"ms-settings:network-wifisettings" };
            constexpr UriBase MobileHotspot{ L"ms-settings:network-mobile-hotspot" };
            constexpr UriBase Proxy{ L"ms-settings:network-proxy" };
            constexpr UriBase VPN{ L"ms-settings:network-vpn" };
            constexpr UriBase Wifi{ L"ms-settings:network-wifi" };
        }
        constexpr UriBase Proximity{ L"ms-settings:proximity" };
        namespace Wifi
        {
            constexpr UriBase Provisioning{ L"ms-settings:wifi-provisioning" };
        }
#pragma endregion

#pragma region Personalization
        namespace
        {
            struct StartT : UriBase
            {
                constexpr StartT(std::wstring_view uri) : UriBase{ uri } {}
            };
        }
        struct Personalization : UriBase
        {
            constexpr static inline UriBase Background{ L"ms-settings:personalization-background" };
            struct Start
            {
                constexpr static inline UriBase Places{ L"ms-settings:personalization-start-places" };
            }; constexpr static inline StartT Start{ L"ms-settings:personalization-start" };;
            constexpr static inline UriBase Colors{ L"ms-settings:personalization-colors" };
            constexpr static inline UriBase Glance{ L"ms-settings:personalization-glance" };
            constexpr static inline UriBase NavBar{ L"ms-settings:personlization-navbar" };
            constexpr static inline UriBase TouchKeyboard{ L"ms-settings:personalization-touchkeyboard" };
            constexpr Personalization(std::wstring_view uri) : UriBase{ uri } {}
        };
        constexpr Personalization Personalization{ L"ms-settings:personalization" };
        constexpr UriBase Colors{ L"ms-settings:colors" };
        constexpr UriBase Lockscreen{ L"ms-settings:lockscreen" };
        constexpr UriBase Themes{ L"ms-settings:themes" };
#pragma endregion

#pragma region Phone
        namespace Mobile
        {
            namespace
            {
                struct AddPhoneT : UriBase
                {
                    constexpr AddPhoneT(std::wstring_view uri) : UriBase{ uri } {}
                };
            }
            struct Devices : public UriBase
            {
                struct AddPhone
                {
                    constexpr static inline UriBase Direct{ L"ms-settings:mobile-devices-addphone-direct" };
                };
                constexpr static inline AddPhoneT AddPhone{ L"ms-settings:mobile-devices-addphone" };
                constexpr Devices(std::wstring_view uri) : UriBase{ uri } {}
            };
            constexpr Devices Devices{ L"ms-settings:mobile-devices" };
        }
        constexpr UriBase DeviceUsage{ L"ms-settings:deviceusage" };
#pragma endregion

#pragma region Privacy
        struct Privacy : public UriBase
        {
            constexpr static inline UriBase AccessoryApps{ L"ms-settings:privacy-accessoryapps" };
            constexpr static inline UriBase AccountInfo{ L"ms-settings:privacy-accountinfo" };
            constexpr static inline UriBase ActivityHistory{ L"ms-settings:privacy-activityhistory" };
            constexpr static inline UriBase AdvertisingId{ L"ms-settings:privacy-advertisingid" };
            constexpr static inline UriBase AppDiagnostics{ L"ms-settings:privacy-appdiagnostics" };
            constexpr static inline UriBase AutomaticFileDownloads{ L"ms-settings:privacy-automaticfiledownloads" };
            constexpr static inline UriBase BackgroundApps{ L"ms-settings:privacy-backgroundapps" };
            constexpr static inline UriBase BackgroundSpatialPerception{ L"ms-settings:privacy-backgroundspatialperception" };
            constexpr static inline UriBase Calender{ L"ms-settings:privacy-calendar" };
            constexpr static inline UriBase CallHistory{ L"ms-settings:privacy-callhistory" };
            constexpr static inline UriBase WebCam{ L"ms-settings:privacy-webcam" };
            constexpr static inline UriBase Contacts{ L"ms-settings:privacy-contacts" };
            constexpr static inline UriBase Documents{ L"ms-settings:privacy-documents" };
            constexpr static inline UriBase DownloadsFolder{ L"ms-settings:privacy-downloadsfolder" };
            constexpr static inline UriBase Email{ L"ms-settings:privacy-email" };
            constexpr static inline UriBase EyeTracker{ L"ms-settings:privacy-eyetracker" };
            constexpr static inline UriBase Feedback{ L"ms-settings:privacy-feedback" };
            constexpr static inline UriBase BroadFilesystemAccess{ L"ms-settings:privacy-broadfilesystemaccess" };
            constexpr static inline UriBase General{ L"ms-settings:privacy-general" };
            constexpr static inline UriBase GraphicsCaptureProgrammatic{ L"ms-settings:privacy-graphicscaptureprogrammatic" };
            constexpr static inline UriBase GraphicsCaptureWithoutBorder{ L"ms-settings:privacy-graphicscapturewithoutborder" };
            constexpr static inline UriBase SpeechTyping{ L"ms-settings:privacy-speechtyping" };
            constexpr static inline UriBase Location{ L"ms-settings:privacy-location" };
            constexpr static inline UriBase Messaging{ L"ms-settings:privacy-messaging" };
            constexpr static inline UriBase Microphone{ L"ms-settings:privacy-microphone" };
            constexpr static inline UriBase Motion{ L"ms-settings:privacy-motion" };
            constexpr static inline UriBase MusicLibrary{ L"ms-settings:privacy-musiclibrary" };
            constexpr static inline UriBase Notifications{ L"ms-settings:privacy-notifications" };
            constexpr static inline UriBase CustomDevices{ L"ms-settings:privacy-customdevices" };
            constexpr static inline UriBase PhoneCalls{ L"ms-settings:privacy-phonecalls" };
            constexpr static inline UriBase Pictures{ L"ms-settings:privacy-pictures" };
            constexpr static inline UriBase Radios{ L"ms-settings:privacy-radios" };
            constexpr static inline UriBase Speech{ L"ms-settings:privacy-speech" };
            constexpr static inline UriBase Tasks{ L"ms-settings:privacy-tasks" };
            constexpr static inline UriBase Videos{ L"ms-settings:privacy-videos" };
            constexpr static inline UriBase VoiceActivation{ L"ms-settings:privacy-voiceactivation" };
            struct Holographic
            {
                constexpr static inline UriBase Environment{ L"ms-settings:privacy-holographic-environment" };
            };
            constexpr Privacy(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr Privacy Privacy{ L"ms-settings:privacy" };
#pragma endregion

#pragma region Search
        struct Search : public UriBase
        {
            constexpr static inline UriBase MoreDetails{ L"ms-settings:search-moredetails" };
            constexpr static inline UriBase Permissions{ L"ms-settings:permissions" };
            constexpr Search(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr Search Search{ L"ms-settings:search" };
#pragma endregion

#pragma region SurfaceHub
        namespace SurfaceHub
        {
            constexpr static inline UriBase Accounts{ L"ms-settings:surfacehub-accounts" };
            constexpr static inline UriBase SessionCleanup{ L"ms-settings:surfacehub-sessioncleanup" };
            constexpr static inline UriBase Calling{ L"ms-settings:surfacehub-calling" };
            constexpr static inline UriBase DeviceManagement{ L"ms-settings:surfacehub-devicemanagement" };
            constexpr static inline UriBase Welcome{ L"ms-settings:surfacehub-welcome" };
        }
#pragma endregion

#pragma region System
        constexpr UriBase About{ L"ms-settings:about" };
        namespace
        {
            struct DisplayT : public UriBase
            {
                constexpr DisplayT(std::wstring_view uri) : UriBase{ uri } {}
            };
        }
        struct Display : public UriBase
        {
            constexpr static inline UriBase Advanced{ L"ms-settings:display-advanced" };
            struct AdvancedGraphics
            {
                constexpr static inline UriBase Default{ L"ms-settings:display-advancedgraphics-default" };
            };
            constexpr static inline DisplayT AdvancedGraphics{ L"ms-settings:display-advancedgraphics" };
            constexpr Display(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr Display Display{ L"ms-settings:display" };
        namespace Apps
        {
            constexpr UriBase Volume{ L"ms-settings:apps-volume" };
        }
        struct BatterySaver : public UriBase
        {
            constexpr static inline UriBase Settings{ L"ms-settings:batterysaver-settings" };
            constexpr static inline UriBase UsageDetails{ L"ms-settings:batterysaver-usagedetails" };
            constexpr BatterySaver(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr BatterySaver BatterySaver{ L"ms-settings:batterysaver" };
        constexpr UriBase Clipboard{ L"ms-settings:clipboard" };
        constexpr UriBase SaveLocations{ L"ms-settings:savelocations" };
        constexpr UriBase ScreenRotation{ L"ms-settings:screenrotation" };
        constexpr UriBase QuietMomentsPresentation{ L"ms-settings:quietmomentspresentation" };
        constexpr UriBase QuietMomentsScheduled{ L"ms-settings:quietmomentsscheduled" };
        constexpr UriBase DeviceEncryption{ L"ms-settings:deviceencryption" };
        constexpr UriBase EnergyRecommendations{ L"ms-settings:energyrecommendations" };
        constexpr UriBase QuietHours{ L"ms-settings:quiethours" };
        struct MultiTasking : public UriBase
        {
            constexpr static inline UriBase SgUpdate{ L"ms-settings:multitasking-sgupdate" };
            constexpr MultiTasking(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr MultiTasking MultiTasking{ L"ms-settings:multitasking" };
        constexpr UriBase NightLight{ L"ms-settings:nightlight" };
        constexpr UriBase Project{ L"ms-settings:project" };
        constexpr UriBase CrossDevice{ L"ms-settings:crossdevice" };
        constexpr UriBase TabletMode{ L"ms-settings:tabletmode" };
        constexpr UriBase Taskbar{ L"ms-settings:taskbar" };
        constexpr UriBase Notifications{ L"ms-settings:notifications" };
        constexpr UriBase RemoteDesktop{ L"ms-settings:remotedesktop" };
        constexpr UriBase Phone{ L"ms-settings:phone" };
        constexpr UriBase PowerSleep{ L"ms-settings:powersleep" };
        constexpr UriBase Presence{ L"ms-settings:presence" };
        struct Sound : public UriBase
        {
            constexpr static inline UriBase Devices{ L"ms-settings:sound-devices" };
            constexpr Sound(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr Sound Sound{ L"ms-settings:sound" };
        constexpr UriBase StorageSense{ L"ms-settings:storagesense" };
        constexpr UriBase StoragePolicies{ L"ms-settings:storagepolicies" };
        constexpr UriBase StorageRecommendations{ L"ms-settings:storagerecommendations" };
        constexpr UriBase DisksAndVolumes{ L"ms-settings:diskandvolumes" };
#pragma endregion

#pragma region TimeAndLanguage
        constexpr UriBase DateAndTime{ L"ms-settings:dateandtime" };
        constexpr UriBase RegionFormatting{ L"ms-settings:regionformatting" };
        struct Keyboard : public UriBase
        {
            constexpr static inline UriBase Advanced{ L"ms-settings:keyboard-advanced" };
            constexpr Keyboard(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr Keyboard Keyboard{ L"ms-settings:keyboard" };
        namespace
        {
            struct PinyinT : public UriBase
            {
                constexpr PinyinT(std::wstring_view uri) : UriBase{ uri } {}
            };
        }
        struct RegionLanguage : public UriBase
        {
            constexpr static inline UriBase JpnIME{ L"ms-settings:regionlanguage-jpnime" };
            constexpr static inline UriBase BpmfIME{ L"ms-settings:regionlanguage-bpmfime" };
            constexpr static inline UriBase CangjieIME{ L"ms-settings:regionlanguage-cangjieime" };
            struct ChsIME
            {
                struct Wubi
                {
                    constexpr static inline UriBase Udp{ L"ms-settings:regionlanguage-chsime-wubi-udp" };
                };

                struct Pinyin
                {
                    constexpr static inline UriBase DomainLexicon{ L"ms-settings:regionlanguage-chsime-pinyin-domainlexicon" };
                    constexpr static inline UriBase KeyConfig{ L"ms-settings:regionlanguage-chsime-pinyin-keyconfig" };
                    constexpr static inline UriBase Udp{ L"ms-settings:regionlanguage-chsime-pinyin-udp" };
                }; constexpr static inline PinyinT Pinyin{ L"ms-settings:regionlanguage-chsime-pinyin" };
                constexpr static inline UriBase Wubi{ L"ms-settings:regionlanguage-chsime-wubi" };
            };

            constexpr static inline UriBase QuickIME{ L"ms-settings:regionlanguage-quickime" };
            constexpr static inline UriBase KorIME{ L"ms-settings:regionlanguage-korime" };
            constexpr static inline UriBase AddDisplayLanguage{ L"ms-settings:regionlanguage-adddisplaylanguage" };
            constexpr static inline UriBase LanguageOptions{ L"ms-settings:regionlangauge-languageoptions" };
            constexpr static inline UriBase SetDisplayLangauge{ L"ms-settings:regionlanguage-setdisplaylanguage" };
            constexpr RegionLanguage(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr RegionLanguage RegionLanguage{ L"ms-settings:regionlanguage" };
        constexpr UriBase Speech{ L"ms-settings:speech" };
#pragma endregion

#pragma region UpdateAndSecurity
        constexpr UriBase Activation{ L"ms-settings:activation" };
        constexpr UriBase Backup{ L"ms-settings:backup" };
        namespace Delivery
        {
            struct Optimization : public UriBase
            {
                constexpr static inline UriBase Activity{ L"ms-settings:delivery-optimization-activity" };
                constexpr static inline UriBase Advanced{ L"ms-settings:delivery-optimization-advanced" };
                constexpr Optimization(std::wstring_view uri) : UriBase{ uri } {}
            }; constexpr Optimization Optimization{ L"ms-settings:delivery-optimization" };
        }
        constexpr UriBase FindMyDevice{ L"ms-settings:findmydevice" };
        constexpr UriBase Developers{ L"ms-settings:developers" };
        constexpr UriBase Recovery{ L"ms-settings:recovery" };
        constexpr UriBase Troubleshoot{ L"ms-settings:troubleshoot" };
        constexpr UriBase WindowsDefender{ L"ms-settings:windowsdefender" };
        struct WindowsInsider : public UriBase
        {
            constexpr static inline UriBase Optin{ L"ms-settings:windowsinsider-optin" };
            constexpr WindowsInsider(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr WindowsInsider WindowsInsider{ L"ms-settings:windowsinsider" };
        struct WindowsUpdate : public UriBase
        {
            constexpr static inline UriBase Action{ L"ms-settings:windowsupdate-action" };
            constexpr static inline UriBase ActiveHours{ L"ms-settings:windowsupdate-activehours" };
            constexpr static inline UriBase Options{ L"ms-settings:windowsupdate-options" };
            constexpr static inline UriBase OptionalUpdates{ L"ms-settings:windowsupdate-optionalupdates" };
            constexpr static inline UriBase RestartOptions{ L"ms-settings:windowsupdate-restartoptions" };
            constexpr static inline UriBase SeekerOnDemand{ L"ms-settings:windowsupdate-seekderondemand" };
            constexpr static inline UriBase History{ L"ms-settings:windowsupdate-history" };
            constexpr WindowsUpdate(std::wstring_view uri) : UriBase{ uri } {}
        }; constexpr WindowsUpdate WindowsUpdate{ L"ms-settings:windowsupdate" };
#pragma endregion

#pragma region UserAccount
        constexpr UriBase Provisioning{ L"ms-settings:provisioning" };
        constexpr UriBase WindowsAnywhere{ L"ms-settings:windowsanywhere" };
#pragma endregion
    }

    namespace Store
    {
        constexpr UriBase Home{ L"ms-windows-store://home" };
        namespace NavigateToPage
        {
            constexpr UriBase Home{ L"ms-windows-store://navigatetopage/?Id=Home" };
            constexpr UriBase Gaming{ L"ms-windows-store://navigatetopage/?Id=Gaming" };
            constexpr UriBase Entertainment{ L"ms-windows-store://navigatetopage/?Id=entertainment" };
            constexpr UriBase Productivity{ L"ms-windows-store://navigatetopage/?Id=productivity" };
            constexpr UriBase LOB{ L"ms-windows-store://navigatetopage/?Id=lob" };
        }
        constexpr UriBase DownloadsAndUpdates{ L"ms-windows-store://downloadsandupdates" };
        constexpr UriBase Settings{ L"ms-windows-store://settings" };
        struct ProductId : std::wstring_view
        {
            using BaseType = std::wstring_view;
            explicit constexpr ProductId(std::wstring_view id) : std::wstring_view{ id }{}
        };
        struct PFN : std::wstring_view
        {
            using BaseType = std::wstring_view;
            explicit constexpr PFN(std::wstring_view packageFamilyName) : std::wstring_view{ packageFamilyName }{}
        };
        struct AppId : std::wstring_view
        {
            using BaseType = std::wstring_view;
            explicit constexpr AppId(std::wstring_view appId) : std::wstring_view{ appId }{}
        };
        struct ProductPage : public winrt::Windows::Foundation::Uri
        {
            ProductPage(std::wstring_view productId, bool mini = false) : Uri{ mini ?
                std::format(L"ms-windows-store://pdp/?ProductId={}&mode=mini", productId) :
                std::format(L"ms-windows-store://pdp/?ProductId={}", productId)
            }
            {}

            ProductPage(ProductId productId, bool mini = false) : Uri{ mini ?
                std::format(L"ms-windows-store://pdp/?ProductId={}&mode=mini", static_cast<ProductId::BaseType&>(productId)) :
                std::format(L"ms-windows-store://pdp/?ProductId={}", static_cast<ProductId::BaseType&>(productId))
            }
            {}

            ProductPage(AppId id, bool mini = false) : Uri{ mini ?
                std::format(LR"(ms-windows-store://pdp/?AppId={}&mode=mini)", static_cast<AppId::BaseType&>(id)) :
                std::format(LR"(ms-windows-store://pdp/?AppId={})", static_cast<AppId::BaseType&>(id))
            }
            {}

            ProductPage(PFN id, bool mini = false) : Uri{ mini ?
                std::format(LR"(ms-windows-store://pdp/?PFN={}&mode=mini)", static_cast<PFN::BaseType&>(id)) :
                std::format(LR"(ms-windows-store://pdp/?PFN={})", static_cast<PFN::BaseType&>(id))
            }
            {}
        };
        struct Review : public winrt::Windows::Foundation::Uri
        {
            Review(std::wstring_view productId) : Uri{ std::format(L"ms-windows-store://review/?ProductId={}", productId) } {}

            Review(ProductId productId) :
                Uri{ std::format(L"ms-windows-store://review/?ProductId={}", static_cast<ProductId::BaseType&>(productId)) }
            {}
            Review(AppId id) :
                Uri{ std::format(L"ms-windows-store://review/?AppId={}", static_cast<AppId::BaseType&>(id)) }
            {}
            Review(PFN id) :
                Uri{ std::format(L"ms-windows-store://review/?PFN={}", static_cast<PFN::BaseType&>(id)) }
            {}
        };
        struct Assoc : public winrt::Windows::Foundation::Uri
        {
            struct Tag : std::vector<std::wstring>
            {
                using BaseType = std::vector<std::wstring>;
                Tag(std::vector<std::wstring> tags) : std::vector<std::wstring>{ std::move(tags) } {}
            };
            struct FileExt : std::wstring_view
            {
                using BaseType = std::wstring_view;
                explicit constexpr FileExt(std::wstring_view fileExt) : std::wstring_view{ fileExt }{}
            };
            struct Protocol : std::wstring_view
            {
                using BaseType = std::wstring_view;
                explicit constexpr Protocol(std::wstring_view protocol) : std::wstring_view{ protocol }{}
            };

#ifndef WinUIEssential_UseBoost
            static std::wstring join(Tag::BaseType const& tags)
            {
                return std::accumulate(std::begin(tags), std::end(tags), std::wstring{},
                    [](std::wstring const& lhs, std::wstring const& rhs) { return lhs.empty() ? rhs : lhs + L' ' + rhs; });
            }
#endif // !WinUIEssential_UseBoost

        private:

        public:

            Assoc(Tag tag) :
#ifdef WinUIEssential_UseBoost
                Uri{ std::format(L"ms-windows-store://assoc/?Tags={}", boost::algorithm::join(static_cast<Tag::BaseType&>(tag), L",")) }
#else
                Uri{ std::format(L"ms-windows-store://assoc/?Tags={}", join(static_cast<Tag::BaseType&>(tag))) }
#endif
            {
            }
            Assoc(FileExt fileExt) : Uri{ std::format(L"ms-windows-store://assoc/?FileExt={}", static_cast<FileExt::BaseType&>(fileExt)) } {}
            Assoc(Protocol protocol) : Uri{ std::format(L"ms-windows-store://assoc/?Protocol={}", static_cast<Protocol::BaseType&>(protocol)) } {}
        };


        struct Search : public winrt::Windows::Foundation::Uri
        {
            Search(std::wstring_view query) : Uri{ std::format(L"ms-windows-store://search/?query={}", query) } {}
        };
        struct Publisher : public winrt::Windows::Foundation::Uri
        {
            Publisher(std::wstring_view name) : Uri{ std::format(L"ms-windows-store://publisher/?name={}", name) } {}
        };
    }
}