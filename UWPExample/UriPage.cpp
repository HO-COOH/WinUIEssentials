#include "pch.h"
#include "UriPage.h"
#if __has_include("UriPage.g.cpp")
#include "UriPage.g.cpp"
#endif
#include <winrt/Windows.System.h>
#include <BuiltInUris.hpp>

using namespace winrt;
using namespace Windows::UI::Xaml;



//class ScreenClip
//{
//    template<typename Value = std::wstring_view>
//    struct QueryBase
//    {
//        std::wstring_view name;
//        Value value;
//    };
//    struct TypeImpl : QueryBase<std::wstring_view>
//    {
//        constexpr TypeImpl(std::wstring_view type) : QueryBase{ L"type", type } {}
//    };
//public:
//    struct Source : QueryBase<>
//    {
//        constexpr Source(std::wstring_view source) : QueryBase{ L"source", source } {}
//    };
//    struct Type
//    {
//        constexpr static inline TypeImpl Snapshot{ L"snapshot" };
//        constexpr static inline TypeImpl Recording{ L"recording" };
//    };
//    struct DelayInSeconds : QueryBase<int>
//    {
//        constexpr DelayInSeconds(int seconds) : QueryBase{ L"delayInSeconds", seconds } {}
//    };
//};

namespace winrt::UWPExample::implementation
{

    static winrt::Windows::Foundation::IAsyncOperation<bool> Launch()
    {
        //Settings::A;
        //return winrt::Windows::System::Launcher::LaunchUriAsync(BuiltInUris::Settings::MobileDevices);
        co_return true;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> UriPage::Uris()
    {
        using namespace BuiltInUris;

        return winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>
        {
            UWPExample::UriGroup{ L"Accounts", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>
            {
                UWPExample::UriModel{L"Access work or school", Settings::Workplace},
                UWPExample::UriModel{L"Email & app accounts", Settings::EmailAndAccounts},
                UWPExample::UriModel{L"Family & other people", Settings::OtherUsers},
                UWPExample::UriModel{L"Set up a kiosk", Settings::AssignedAccess},
                UWPExample::UriModel{L"Sign-in options", Settings::SignInOptions},
                UWPExample::UriModel{L"Sign-in options", Settings::SignInOptions::DynamicLock},
                UWPExample::UriModel{L"Sync your settings", Settings::Sync},
                UWPExample::UriModel{L"Sync your settings", Settings::Backup},
                UWPExample::UriModel{L"Windows Hello setup", Settings::SignInOptions::LaunchFaceEnrollment},
                UWPExample::UriModel{L"Windows Hello setup", Settings::SignInOptions::LaunchFingerprintEnrollment},
                UWPExample::UriModel{L"Your info", Settings::YourInfo}
            }) },
            UWPExample::UriGroup{ L"Apps", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Apps & Features", Settings::AppsFeatures},
                UWPExample::UriModel{L"App features", Settings::AppsFeatures::App},
                UWPExample::UriModel{L"Apps for websites", Settings::AppsForWebsites},
                //default apps,
                UWPExample::UriModel{L"Default browser settings", Settings::DefaultBrowserSettings},
                UWPExample::UriModel{L"Manage optional features", Settings::OptionalFeatures},
                UWPExample::UriModel{L"Offline Maps", Settings::Maps},
                UWPExample::UriModel{L"Offline Maps", Settings::Maps::DownloadMaps},
                UWPExample::UriModel{L"Startup apps", Settings::StartupApps},
                UWPExample::UriModel{L"Video playback", Settings::VideoPlayback}
            }) },
            UWPExample::UriGroup{ L"Control Center", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Control center", Settings::ControlCenter}
            }) },
            UWPExample::UriGroup{ L"Cortana", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Cortana across my device", Settings::Cortana::Notifications},
                UWPExample::UriModel{L"More details", Settings::Cortana::MoreDetails},
                UWPExample::UriModel{L"Permissions & History", Settings::Cortana::Permissions},
                UWPExample::UriModel{L"Searching Windows", Settings::Cortana::WindowsSearch},
                UWPExample::UriModel{L"Talk to Cortana", Settings::Cortana::Language},
                UWPExample::UriModel{L"Talk to Cortana", Settings::Cortana},
                UWPExample::UriModel{L"Talk to Cortana", Settings::Cortana::TalkToCortana}
            })},
            UWPExample::UriGroup{ L"Devices", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"AutoPlay", Settings::Autoplay},
                UWPExample::UriModel{L"Bluetooth", Settings::Bluetooth},
                UWPExample::UriModel{L"Connected Devices", Settings::ConnectedDevices},
                UWPExample::UriModel{L"Default camera", Settings::Camera},
                UWPExample::UriModel{L"Camera settings", Settings::Camera(L"2")},
                UWPExample::UriModel{L"Mouse & touchpad", Settings::MouseTouchpad},
                UWPExample::UriModel{L"Pen & Windows Ink", Settings::Pen},
                UWPExample::UriModel{L"Printers & scanners", Settings::Printers},
                UWPExample::UriModel{L"Touch", Settings::Devices::Touch},
                UWPExample::UriModel{L"Touchpad", Settings::Devices::Touchpad},
                UWPExample::UriModel{L"Text Suggestions", Settings::DevicesTyping::HwkbTextSuggestions},
                UWPExample::UriModel{L"Typing", Settings::Typing},
                UWPExample::UriModel{L"USB", Settings::USB},
                UWPExample::UriModel{L"Wheel", Settings::Wheel},
                UWPExample::UriModel{L"Your phone", Settings::Mobile::Devices}
            })},
            UWPExample::UriGroup{ L"Ease of access", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Audio", Settings::EaseOfAccess::Audio},
                UWPExample::UriModel{L"Closed captions", Settings::EaseOfAccess::ClosedCaptioning},
                UWPExample::UriModel{L"Color filters", Settings::EaseOfAccess::ColorFilter},
                UWPExample::UriModel{L"Color filters", Settings::EaseOfAccess::ColorFilter::AdaptiveColorLink},
                UWPExample::UriModel{L"Color filters", Settings::EaseOfAccess::ColorFilter::BlueLightLink},
                UWPExample::UriModel{L"Display", Settings::EaseOfAccess::Display},
                UWPExample::UriModel{L"Eye control", Settings::EaseOfAccess::EyeControl},
                UWPExample::UriModel{L"Fonts", Settings::Fonts},
                UWPExample::UriModel{L"High contrast", Settings::EaseOfAccess::HighContrast},
                UWPExample::UriModel{L"Keyboard", Settings::EaseOfAccess::Keryboard},
                UWPExample::UriModel{L"Magnifier", Settings::EaseOfAccess::Magnifier},
                UWPExample::UriModel{L"Mouse", Settings::EaseOfAccess::Mouse},
                UWPExample::UriModel{L"Mouse pointer & touch", Settings::EaseOfAccess::MousePionter},
                UWPExample::UriModel{L"Narrator", Settings::EaseOfAccess::Narrator},
                UWPExample::UriModel{L"Narrator", Settings::EaseOfAccess::Narrator::IsAutoStartEnabled},
                UWPExample::UriModel{L"Speech", Settings::EaseOfAccess::SpeechRecognition},
                UWPExample::UriModel{L"Text cursor", Settings::EaseOfAccess::Cursor},
                UWPExample::UriModel{L"Visual Effects", Settings::EaseOfAccess::VisualEffects}
            })},
            UWPExample::UriGroup{ L"Extras", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Extras", Settings::Extras}
            })},
            UWPExample::UriGroup{ L"Family Group", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Family Group", Settings::Family::Group}
            })},
            UWPExample::UriGroup{ L"Gaming", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Game bar", Settings::Gaming::GameBar},
                UWPExample::UriModel{L"Game DVR", Settings::Gaming::GameDVR},
                UWPExample::UriModel{L"Game Mode", Settings::Gaming::GameMode},
                UWPExample::UriModel{L"Playing a game full screen", Settings::QuietMomentsGame},
                UWPExample::UriModel{L"TruePlay", Settings::Gaming::TruePlay}
            })},
            UWPExample::UriGroup{ L"Mixed reality", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Audio and speech", Settings::Holographic::Audio},
                UWPExample::UriModel{L"Environment", Settings::Privacy::Holographic::Environment},
                UWPExample::UriModel{L"Headset display", Settings::Holographic::Headset},
                UWPExample::UriModel{L"Uninstall", Settings::Holographic::Management},
                UWPExample::UriModel{L"Startup and desktop", Settings::Holographic::StartupAndDesktop}
            })},
            UWPExample::UriGroup{ L"Network and internet", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Network & internet", Settings::Network::Status},
                UWPExample::UriModel{L"Advanced settings", Settings::Network::AdvancedSettings},
                UWPExample::UriModel{L"Airplane mode", Settings::Network::AirplaneMode},
                UWPExample::UriModel{L"Airplane mode", Settings::Proximity},
                UWPExample::UriModel{L"Cellular & SIM", Settings::Network::Cellular},
                UWPExample::UriModel{L"Dial-up", Settings::Network::Dialup},
                UWPExample::UriModel{L"DirectAccess", Settings::Network::DirectAccess},
                UWPExample::UriModel{L"Ethernet", Settings::Network::Ethernet},
                UWPExample::UriModel{L"Manage known networks", Settings::Network::WifiSettings},
                UWPExample::UriModel{L"Mobile hotspot", Settings::Network::MobileHotspot},

            })},
            UWPExample::UriGroup{ L"Personalization", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Background", Settings::Personalization::Background},
                UWPExample::UriModel{L"Choose which folders appear on Start", Settings::Personalization::Start::Places},
                UWPExample::UriModel{L"Colors", Settings::Personalization::Colors},
                UWPExample::UriModel{L"Colors", Settings::Colors},
                UWPExample::UriModel{L"Glance", Settings::Personalization::Glance},
                UWPExample::UriModel{L"Lock screen", Settings::Lockscreen},
                UWPExample::UriModel{L"Navigation bar", Settings::Personalization::NavBar},
                UWPExample::UriModel{L"Start", Settings::Personalization::Start},
                UWPExample::UriModel{L"Taskbar", Settings::Taskbar},
                UWPExample::UriModel{L"Touch keyboard", Settings::Personalization::TouchKeyboard},
                UWPExample::UriModel{L"Themes", Settings::Themes}
            })},
            UWPExample::UriGroup{ L"Phone", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Your phone", Settings::Mobile::Devices},
                UWPExample::UriModel{L"Your phone", Settings::Mobile::Devices::AddPhone},
                UWPExample::UriModel{L"Your phone", Settings::Mobile::Devices::AddPhone::Direct},
                UWPExample::UriModel{L"Device Usage", Settings::DeviceUsage}
            })},
            UWPExample::UriGroup{ L"Privacy", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Accessory apps", Settings::Privacy::AccessoryApps},
                UWPExample::UriModel{L"Account info", Settings::Privacy::AccountInfo},
                UWPExample::UriModel{L"Activity history", Settings::Privacy::ActivityHistory},
                UWPExample::UriModel{L"Advertising ID", Settings::Privacy::AdvertisingId},
                UWPExample::UriModel{L"App diagnostics", Settings::Privacy::AppDiagnostics},
                UWPExample::UriModel{L"Automatic file downloads", Settings::Privacy::AutomaticFileDownloads},
                UWPExample::UriModel{L"Background Apps", Settings::Privacy::BackgroundApps},
                UWPExample::UriModel{L"Background Spatial Perception", Settings::Privacy::BackgroundSpatialPerception},
                UWPExample::UriModel{L"Calendar", Settings::Privacy::Calender},
                UWPExample::UriModel{L"Call history", Settings::Privacy::CallHistory},
                UWPExample::UriModel{L"Camera", Settings::Privacy::WebCam},
                UWPExample::UriModel{L"Contacts", Settings::Privacy::Contacts},
                UWPExample::UriModel{L"Documents", Settings::Privacy::Documents},
                UWPExample::UriModel{L"Downloads folder", Settings::Privacy::DownloadsFolder},
                UWPExample::UriModel{L"Email", Settings::Privacy::Email},
                UWPExample::UriModel{L"Eye tracker", Settings::Privacy::EyeTracker},
                UWPExample::UriModel{L"Feedback & diagnostics", Settings::Privacy::Feedback},
                UWPExample::UriModel{L"File system", Settings::Privacy::BroadFilesystemAccess},
                UWPExample::UriModel{L"General", Settings::Privacy},
                UWPExample::UriModel{L"General", Settings::Privacy::General},
                UWPExample::UriModel{L"Graphics", Settings::Privacy::GraphicsCaptureProgrammatic},
                UWPExample::UriModel{L"Graphics", Settings::Privacy::GraphicsCaptureWithoutBorder},
                UWPExample::UriModel{L"Inking & typing", Settings::Privacy::SpeechTyping},
                UWPExample::UriModel{L"Location", Settings::Privacy::Location},
                UWPExample::UriModel{L"Messaging", Settings::Privacy::Messaging},
                UWPExample::UriModel{L"Microphone", Settings::Privacy::Microphone},
                UWPExample::UriModel{L"Motion", Settings::Privacy::Motion},
                UWPExample::UriModel{L"Music Library", Settings::Privacy::MusicLibrary},
                UWPExample::UriModel{L"Notifications", Settings::Privacy::Notifications},
                UWPExample::UriModel{L"Other devices", Settings::Privacy::CustomDevices},
                UWPExample::UriModel{L"Phone calls", Settings::Privacy::PhoneCalls},
                UWPExample::UriModel{L"Pictures", Settings::Privacy::Pictures},
                UWPExample::UriModel{L"Radios", Settings::Privacy::Radios},
                UWPExample::UriModel{L"Speech", Settings::Privacy::Speech},
                UWPExample::UriModel{L"Tasks", Settings::Privacy::Tasks},
                UWPExample::UriModel{L"Videos", Settings::Privacy::Videos},
                UWPExample::UriModel{L"Voice activation", Settings::Privacy::VoiceActivation}
            })},
            UWPExample::UriGroup{ L"Search", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Search", Settings::Search},
                UWPExample::UriModel{L"Search more details", Settings::Search::MoreDetails},
                UWPExample::UriModel{L"Search Permissions", Settings::Search::Permissions},
            })},
            UWPExample::UriGroup{ L"Surface Hub", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Accounts", Settings::SurfaceHub::Accounts},
                UWPExample::UriModel{L"Session cleanup", Settings::SurfaceHub::SessionCleanup},
                UWPExample::UriModel{L"Team conferencing", Settings::SurfaceHub::Calling},
                UWPExample::UriModel{L"Team device management", Settings::SurfaceHub::DeviceManagement},
                UWPExample::UriModel{L"Welcome screen", Settings::SurfaceHub::Welcome}
            })},
            UWPExample::UriGroup{ L"System", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"About", Settings::About},
                UWPExample::UriModel{L"Advanced display settings", Settings::Display::Advanced},
                UWPExample::UriModel{L"App volume and device perference", Settings::Apps::Volume},
                UWPExample::UriModel{L"Battery Saver", Settings::BatterySaver},
                UWPExample::UriModel{L"Battery Saver settings", Settings::BatterySaver::Settings},
                UWPExample::UriModel{L"Battery use", Settings::BatterySaver::UsageDetails},
                UWPExample::UriModel{L"Clipboard", Settings::Clipboard},
                UWPExample::UriModel{L"Display", Settings::Display},
                UWPExample::UriModel{L"Default Save Locations", Settings::SaveLocations},
                UWPExample::UriModel{L"Display", Settings::ScreenRotation},
                UWPExample::UriModel{L"Duplicating my display", Settings::QuietMomentsPresentation},
                UWPExample::UriModel{L"During these hours", Settings::QuietMomentsScheduled},
                UWPExample::UriModel{L"Encryptions", Settings::DeviceEncryption},
                UWPExample::UriModel{L"Energy recommendations", Settings::EnergyRecommendations},
                UWPExample::UriModel{L"Focus assist", Settings::QuietHours},
                UWPExample::UriModel{L"Graphics settings", Settings::Display::AdvancedGraphics},
                UWPExample::UriModel{L"Graphics Default Settings", Settings::Display::AdvancedGraphics::Default},
                UWPExample::UriModel{L"Multitasking", Settings::MultiTasking},
                UWPExample::UriModel{L"Multitasking", Settings::MultiTasking::SgUpdate},
                UWPExample::UriModel{L"Night light settings", Settings::NightLight},
                UWPExample::UriModel{L"Projecting to this PC", Settings::Project},
                UWPExample::UriModel{L"Shared experiences", Settings::CrossDevice},
                UWPExample::UriModel{L"Tablet mode", Settings::TabletMode},
                UWPExample::UriModel{L"Taskbar", Settings::Taskbar},
                UWPExample::UriModel{L"Notifications & actions", Settings::Notifications},
                UWPExample::UriModel{L"Remote Desktop", Settings::RemoteDesktop},
                UWPExample::UriModel{L"Phone", Settings::Phone},
                UWPExample::UriModel{L"Power & sleep", Settings::PowerSleep},
                UWPExample::UriModel{L"Presence sensing", Settings::Presence},
                UWPExample::UriModel{L"Sound", Settings::Sound},
                UWPExample::UriModel{L"Sound devices",Settings::Sound::Devices},
                UWPExample::UriModel{L"Storage", Settings::StorageSense},
                UWPExample::UriModel{L"Storage Sense", Settings::StoragePolicies},
                UWPExample::UriModel{L"Storage recommendations", Settings::StorageRecommendations},
                UWPExample::UriModel{L"Disks & volumes", Settings::DisksAndVolumes}
            })},
            UWPExample::UriGroup{ L"Time and language", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Date & time", Settings::DateAndTime},
                UWPExample::UriModel{L"Japan IME settings", Settings::RegionLanguage::JpnIME},
                UWPExample::UriModel{L"Region", Settings::RegionFormatting},
                UWPExample::UriModel{L"Language", Settings::Keyboard},
                UWPExample::UriModel{L"Language", Settings::Keyboard::Advanced},
                UWPExample::UriModel{L"Language", Settings::RegionLanguage},
                UWPExample::UriModel{L"Language", Settings::RegionLanguage::BpmfIME},
                UWPExample::UriModel{L"Language", Settings::RegionLanguage::CangjieIME},
                UWPExample::UriModel{L"Language", Settings::RegionLanguage::ChsIME::Wubi::Udp},
                UWPExample::UriModel{L"Language", Settings::RegionLanguage::QuickIME},
                UWPExample::UriModel{L"Language", Settings::RegionLanguage::KorIME},
                UWPExample::UriModel{L"Pinyin IME settings", Settings::RegionLanguage::ChsIME::Pinyin},
                UWPExample::UriModel{L"Pinyin IME settings", Settings::RegionLanguage::ChsIME::Pinyin::DomainLexicon},
                UWPExample::UriModel{L"Pinyin IME settings", Settings::RegionLanguage::ChsIME::Pinyin::KeyConfig},
                UWPExample::UriModel{L"Pinyin IME settings", Settings::RegionLanguage::ChsIME::Pinyin::Udp},
                UWPExample::UriModel{L"Speech", Settings::Speech},
                UWPExample::UriModel{L"Wubi IME settings", Settings::RegionLanguage::ChsIME::Wubi},
                UWPExample::UriModel{L"Add display language", Settings::RegionLanguage::AddDisplayLanguage},
                UWPExample::UriModel{L"Language options", Settings::RegionLanguage::LanguageOptions},
                UWPExample::UriModel{L"Set display language", Settings::RegionLanguage::SetDisplayLangauge}
            })},
            UWPExample::UriGroup{ L"Update and security", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Activation", Settings::Activation},
                UWPExample::UriModel{L"Backup", Settings::Backup},
                UWPExample::UriModel{L"Delivery Optimization", Settings::Delivery::Optimization},
                UWPExample::UriModel{L"Delivery Optimization", Settings::Delivery::Optimization::Activity},
                UWPExample::UriModel{L"Delivery Optimization", Settings::Delivery::Optimization::Advanced},
                UWPExample::UriModel{L"Find My Device", Settings::FindMyDevice},
                UWPExample::UriModel{L"For developers", Settings::Developers},
                UWPExample::UriModel{L"Recovery", Settings::Recovery},
                UWPExample::UriModel{L"Launch Security Key Enrollment", Settings::SignInOptions::LaunchSecurityKeyEnrollment},
                UWPExample::UriModel{L"Troubleshoot", Settings::Troubleshoot},
                UWPExample::UriModel{L"Windows Security", Settings::WindowsDefender},
                UWPExample::UriModel{L"Windows Insider Program", Settings::WindowsInsider},
                UWPExample::UriModel{L"Windows Insider Program", Settings::WindowsInsider::Optin},
                UWPExample::UriModel{L"Windows Update", Settings::WindowsUpdate},
                UWPExample::UriModel{L"Windows Update", Settings::WindowsUpdate::Action},
                UWPExample::UriModel{L"Windows Update-Active hours", Settings::WindowsUpdate::ActiveHours},
                UWPExample::UriModel{L"Windows Update-Advanced options", Settings::WindowsUpdate::Options},
                UWPExample::UriModel{L"Windows Update-Optional updates", Settings::WindowsUpdate::OptionalUpdates},
                UWPExample::UriModel{L"Windows Update-Restart options", Settings::WindowsUpdate::RestartOptions},
                UWPExample::UriModel{L"Windows Update-Seeker on demand", Settings::WindowsUpdate::SeekerOnDemand},
                UWPExample::UriModel{L"Windows Update-View update history", Settings::WindowsUpdate::History}
            })},
            UWPExample::UriGroup{ L"User accounts", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                UWPExample::UriModel{L"Provisioning", Settings::Workplace::Provisioning},
                UWPExample::UriModel{L"Repair token", Settings::Workplace::RepairToken},
                UWPExample::UriModel{L"Provisioning", Settings::Provisioning},
                UWPExample::UriModel{L"Windows Anywhere", Settings::WindowsAnywhere}
            })}
        });
    }
}
