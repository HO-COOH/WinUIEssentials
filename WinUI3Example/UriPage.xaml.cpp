#include "pch.h"
#include "UriPage.xaml.h"
#if __has_include("UriPage.g.cpp")
#include "UriPage.g.cpp"
#endif

#include <BuiltInUris.hpp>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> UriPage::Uris()
    {
        using namespace BuiltInUris;

        return winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>
        {
            WinUI3Example::UriGroup{ L"Accounts", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>
            {
                WinUI3Example::UriModel{L"Access work or school", Settings::Workplace},
                WinUI3Example::UriModel{L"Email & app accounts", Settings::EmailAndAccounts},
                WinUI3Example::UriModel{L"Family & other people", Settings::OtherUsers},
                WinUI3Example::UriModel{L"Set up a kiosk", Settings::AssignedAccess},
                WinUI3Example::UriModel{L"Sign-in options", Settings::SignInOptions},
                WinUI3Example::UriModel{L"Sign-in options", Settings::SignInOptions::DynamicLock},
                WinUI3Example::UriModel{L"Sync your settings", Settings::Sync},
                WinUI3Example::UriModel{L"Sync your settings", Settings::Backup},
                WinUI3Example::UriModel{L"Windows Hello setup", Settings::SignInOptions::LaunchFaceEnrollment},
                WinUI3Example::UriModel{L"Windows Hello setup", Settings::SignInOptions::LaunchFingerprintEnrollment},
                WinUI3Example::UriModel{L"Your info", Settings::YourInfo}
            }) },
                WinUI3Example::UriGroup{ L"Apps", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Apps & Features", Settings::AppsFeatures},
                    WinUI3Example::UriModel{L"App features", Settings::AppsFeatures::App},
                    WinUI3Example::UriModel{L"Apps for websites", Settings::AppsForWebsites},
                        //default apps,
                        WinUI3Example::UriModel{L"Default browser settings", Settings::DefaultBrowserSettings},
                        WinUI3Example::UriModel{L"Manage optional features", Settings::OptionalFeatures},
                        WinUI3Example::UriModel{L"Offline Maps", Settings::Maps},
                        WinUI3Example::UriModel{L"Offline Maps", Settings::Maps::DownloadMaps},
                        WinUI3Example::UriModel{L"Startup apps", Settings::StartupApps},
                        WinUI3Example::UriModel{L"Video playback", Settings::VideoPlayback}
                    }) },
                WinUI3Example::UriGroup{ L"Control Center", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Control center", Settings::ControlCenter}
                }) },
                WinUI3Example::UriGroup{ L"Cortana", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Cortana across my device", Settings::Cortana::Notifications},
                    WinUI3Example::UriModel{L"More details", Settings::Cortana::MoreDetails},
                    WinUI3Example::UriModel{L"Permissions & History", Settings::Cortana::Permissions},
                    WinUI3Example::UriModel{L"Searching Windows", Settings::Cortana::WindowsSearch},
                    WinUI3Example::UriModel{L"Talk to Cortana", Settings::Cortana::Language},
                    WinUI3Example::UriModel{L"Talk to Cortana", Settings::Cortana},
                    WinUI3Example::UriModel{L"Talk to Cortana", Settings::Cortana::TalkToCortana}
                }) },
                WinUI3Example::UriGroup{ L"Devices", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"AutoPlay", Settings::Autoplay},
                    WinUI3Example::UriModel{L"Bluetooth", Settings::Bluetooth},
                    WinUI3Example::UriModel{L"Connected Devices", Settings::ConnectedDevices},
                    WinUI3Example::UriModel{L"Default camera", Settings::Camera},
                    WinUI3Example::UriModel{L"Camera settings", Settings::Camera(L"2")},
                    WinUI3Example::UriModel{L"Mouse & touchpad", Settings::MouseTouchpad},
                    WinUI3Example::UriModel{L"Pen & Windows Ink", Settings::Pen},
                    WinUI3Example::UriModel{L"Printers & scanners", Settings::Printers},
                    WinUI3Example::UriModel{L"Touch", Settings::Devices::Touch},
                    WinUI3Example::UriModel{L"Touchpad", Settings::Devices::Touchpad},
                    WinUI3Example::UriModel{L"Text Suggestions", Settings::DevicesTyping::HwkbTextSuggestions},
                    WinUI3Example::UriModel{L"Typing", Settings::Typing},
                    WinUI3Example::UriModel{L"USB", Settings::USB},
                    WinUI3Example::UriModel{L"Wheel", Settings::Wheel},
                    WinUI3Example::UriModel{L"Your phone", Settings::Mobile::Devices}
                }) },
                WinUI3Example::UriGroup{ L"Ease of access", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Audio", Settings::EaseOfAccess::Audio},
                    WinUI3Example::UriModel{L"Closed captions", Settings::EaseOfAccess::ClosedCaptioning},
                    WinUI3Example::UriModel{L"Color filters", Settings::EaseOfAccess::ColorFilter},
                    WinUI3Example::UriModel{L"Color filters", Settings::EaseOfAccess::ColorFilter::AdaptiveColorLink},
                    WinUI3Example::UriModel{L"Color filters", Settings::EaseOfAccess::ColorFilter::BlueLightLink},
                    WinUI3Example::UriModel{L"Display", Settings::EaseOfAccess::Display},
                    WinUI3Example::UriModel{L"Eye control", Settings::EaseOfAccess::EyeControl},
                    WinUI3Example::UriModel{L"Fonts", Settings::Fonts},
                    WinUI3Example::UriModel{L"High contrast", Settings::EaseOfAccess::HighContrast},
                    WinUI3Example::UriModel{L"Keyboard", Settings::EaseOfAccess::Keryboard},
                    WinUI3Example::UriModel{L"Magnifier", Settings::EaseOfAccess::Magnifier},
                    WinUI3Example::UriModel{L"Mouse", Settings::EaseOfAccess::Mouse},
                    WinUI3Example::UriModel{L"Mouse pointer & touch", Settings::EaseOfAccess::MousePionter},
                    WinUI3Example::UriModel{L"Narrator", Settings::EaseOfAccess::Narrator},
                    WinUI3Example::UriModel{L"Narrator", Settings::EaseOfAccess::Narrator::IsAutoStartEnabled},
                    WinUI3Example::UriModel{L"Speech", Settings::EaseOfAccess::SpeechRecognition},
                    WinUI3Example::UriModel{L"Text cursor", Settings::EaseOfAccess::Cursor},
                    WinUI3Example::UriModel{L"Visual Effects", Settings::EaseOfAccess::VisualEffects}
                }) },
                WinUI3Example::UriGroup{ L"Extras", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Extras", Settings::Extras}
                }) },
                WinUI3Example::UriGroup{ L"Family Group", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Family Group", Settings::Family::Group}
                }) },
                WinUI3Example::UriGroup{ L"Gaming", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Game bar", Settings::Gaming::GameBar},
                    WinUI3Example::UriModel{L"Game DVR", Settings::Gaming::GameDVR},
                    WinUI3Example::UriModel{L"Game Mode", Settings::Gaming::GameMode},
                    WinUI3Example::UriModel{L"Playing a game full screen", Settings::QuietMomentsGame},
                    WinUI3Example::UriModel{L"TruePlay", Settings::Gaming::TruePlay}
                }) },
                WinUI3Example::UriGroup{ L"Mixed reality", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Audio and speech", Settings::Holographic::Audio},
                    WinUI3Example::UriModel{L"Environment", Settings::Privacy::Holographic::Environment},
                    WinUI3Example::UriModel{L"Headset display", Settings::Holographic::Headset},
                    WinUI3Example::UriModel{L"Uninstall", Settings::Holographic::Management},
                    WinUI3Example::UriModel{L"Startup and desktop", Settings::Holographic::StartupAndDesktop}
                }) },
                WinUI3Example::UriGroup{ L"Network and internet", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Network & internet", Settings::Network::Status},
                    WinUI3Example::UriModel{L"Advanced settings", Settings::Network::AdvancedSettings},
                    WinUI3Example::UriModel{L"Airplane mode", Settings::Network::AirplaneMode},
                    WinUI3Example::UriModel{L"Airplane mode", Settings::Proximity},
                    WinUI3Example::UriModel{L"Cellular & SIM", Settings::Network::Cellular},
                    WinUI3Example::UriModel{L"Dial-up", Settings::Network::Dialup},
                    WinUI3Example::UriModel{L"DirectAccess", Settings::Network::DirectAccess},
                    WinUI3Example::UriModel{L"Ethernet", Settings::Network::Ethernet},
                    WinUI3Example::UriModel{L"Manage known networks", Settings::Network::WifiSettings},
                    WinUI3Example::UriModel{L"Mobile hotspot", Settings::Network::MobileHotspot},

                }) },
                WinUI3Example::UriGroup{ L"Personalization", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Background", Settings::Personalization::Background},
                    WinUI3Example::UriModel{L"Choose which folders appear on Start", Settings::Personalization::Start::Places},
                    WinUI3Example::UriModel{L"Colors", Settings::Personalization::Colors},
                    WinUI3Example::UriModel{L"Colors", Settings::Colors},
                    WinUI3Example::UriModel{L"Glance", Settings::Personalization::Glance},
                    WinUI3Example::UriModel{L"Lock screen", Settings::Lockscreen},
                    WinUI3Example::UriModel{L"Navigation bar", Settings::Personalization::NavBar},
                    WinUI3Example::UriModel{L"Start", Settings::Personalization::Start},
                    WinUI3Example::UriModel{L"Taskbar", Settings::Taskbar},
                    WinUI3Example::UriModel{L"Touch keyboard", Settings::Personalization::TouchKeyboard},
                    WinUI3Example::UriModel{L"Themes", Settings::Themes}
                }) },
                WinUI3Example::UriGroup{ L"Phone", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Your phone", Settings::Mobile::Devices},
                    WinUI3Example::UriModel{L"Your phone", Settings::Mobile::Devices::AddPhone},
                    WinUI3Example::UriModel{L"Your phone", Settings::Mobile::Devices::AddPhone::Direct},
                    WinUI3Example::UriModel{L"Device Usage", Settings::DeviceUsage}
                }) },
                WinUI3Example::UriGroup{ L"Privacy", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Accessory apps", Settings::Privacy::AccessoryApps},
                    WinUI3Example::UriModel{L"Account info", Settings::Privacy::AccountInfo},
                    WinUI3Example::UriModel{L"Activity history", Settings::Privacy::ActivityHistory},
                    WinUI3Example::UriModel{L"Advertising ID", Settings::Privacy::AdvertisingId},
                    WinUI3Example::UriModel{L"App diagnostics", Settings::Privacy::AppDiagnostics},
                    WinUI3Example::UriModel{L"Automatic file downloads", Settings::Privacy::AutomaticFileDownloads},
                    WinUI3Example::UriModel{L"Background Apps", Settings::Privacy::BackgroundApps},
                    WinUI3Example::UriModel{L"Background Spatial Perception", Settings::Privacy::BackgroundSpatialPerception},
                    WinUI3Example::UriModel{L"Calendar", Settings::Privacy::Calender},
                    WinUI3Example::UriModel{L"Call history", Settings::Privacy::CallHistory},
                    WinUI3Example::UriModel{L"Camera", Settings::Privacy::WebCam},
                    WinUI3Example::UriModel{L"Contacts", Settings::Privacy::Contacts},
                    WinUI3Example::UriModel{L"Documents", Settings::Privacy::Documents},
                    WinUI3Example::UriModel{L"Downloads folder", Settings::Privacy::DownloadsFolder},
                    WinUI3Example::UriModel{L"Email", Settings::Privacy::Email},
                    WinUI3Example::UriModel{L"Eye tracker", Settings::Privacy::EyeTracker},
                    WinUI3Example::UriModel{L"Feedback & diagnostics", Settings::Privacy::Feedback},
                    WinUI3Example::UriModel{L"File system", Settings::Privacy::BroadFilesystemAccess},
                    WinUI3Example::UriModel{L"General", Settings::Privacy},
                    WinUI3Example::UriModel{L"General", Settings::Privacy::General},
                    WinUI3Example::UriModel{L"Graphics", Settings::Privacy::GraphicsCaptureProgrammatic},
                    WinUI3Example::UriModel{L"Graphics", Settings::Privacy::GraphicsCaptureWithoutBorder},
                    WinUI3Example::UriModel{L"Inking & typing", Settings::Privacy::SpeechTyping},
                    WinUI3Example::UriModel{L"Location", Settings::Privacy::Location},
                    WinUI3Example::UriModel{L"Messaging", Settings::Privacy::Messaging},
                    WinUI3Example::UriModel{L"Microphone", Settings::Privacy::Microphone},
                    WinUI3Example::UriModel{L"Motion", Settings::Privacy::Motion},
                    WinUI3Example::UriModel{L"Music Library", Settings::Privacy::MusicLibrary},
                    WinUI3Example::UriModel{L"Notifications", Settings::Privacy::Notifications},
                    WinUI3Example::UriModel{L"Other devices", Settings::Privacy::CustomDevices},
                    WinUI3Example::UriModel{L"Phone calls", Settings::Privacy::PhoneCalls},
                    WinUI3Example::UriModel{L"Pictures", Settings::Privacy::Pictures},
                    WinUI3Example::UriModel{L"Radios", Settings::Privacy::Radios},
                    WinUI3Example::UriModel{L"Speech", Settings::Privacy::Speech},
                    WinUI3Example::UriModel{L"Tasks", Settings::Privacy::Tasks},
                    WinUI3Example::UriModel{L"Videos", Settings::Privacy::Videos},
                    WinUI3Example::UriModel{L"Voice activation", Settings::Privacy::VoiceActivation}
                }) },
                WinUI3Example::UriGroup{ L"Search", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Search", Settings::Search},
                    WinUI3Example::UriModel{L"Search more details", Settings::Search::MoreDetails},
                    WinUI3Example::UriModel{L"Search Permissions", Settings::Search::Permissions},
                }) },
                WinUI3Example::UriGroup{ L"Surface Hub", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Accounts", Settings::SurfaceHub::Accounts},
                    WinUI3Example::UriModel{L"Session cleanup", Settings::SurfaceHub::SessionCleanup},
                    WinUI3Example::UriModel{L"Team conferencing", Settings::SurfaceHub::Calling},
                    WinUI3Example::UriModel{L"Team device management", Settings::SurfaceHub::DeviceManagement},
                    WinUI3Example::UriModel{L"Welcome screen", Settings::SurfaceHub::Welcome}
                }) },
                WinUI3Example::UriGroup{ L"System", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"About", Settings::About},
                    WinUI3Example::UriModel{L"Advanced display settings", Settings::Display::Advanced},
                    WinUI3Example::UriModel{L"App volume and device perference", Settings::Apps::Volume},
                    WinUI3Example::UriModel{L"Battery Saver", Settings::BatterySaver},
                    WinUI3Example::UriModel{L"Battery Saver settings", Settings::BatterySaver::Settings},
                    WinUI3Example::UriModel{L"Battery use", Settings::BatterySaver::UsageDetails},
                    WinUI3Example::UriModel{L"Clipboard", Settings::Clipboard},
                    WinUI3Example::UriModel{L"Display", Settings::Display},
                    WinUI3Example::UriModel{L"Default Save Locations", Settings::SaveLocations},
                    WinUI3Example::UriModel{L"Display", Settings::ScreenRotation},
                    WinUI3Example::UriModel{L"Duplicating my display", Settings::QuietMomentsPresentation},
                    WinUI3Example::UriModel{L"During these hours", Settings::QuietMomentsScheduled},
                    WinUI3Example::UriModel{L"Encryptions", Settings::DeviceEncryption},
                    WinUI3Example::UriModel{L"Energy recommendations", Settings::EnergyRecommendations},
                    WinUI3Example::UriModel{L"Focus assist", Settings::QuietHours},
                    WinUI3Example::UriModel{L"Graphics settings", Settings::Display::AdvancedGraphics},
                    WinUI3Example::UriModel{L"Graphics Default Settings", Settings::Display::AdvancedGraphics::Default},
                    WinUI3Example::UriModel{L"Multitasking", Settings::MultiTasking},
                    WinUI3Example::UriModel{L"Multitasking", Settings::MultiTasking::SgUpdate},
                    WinUI3Example::UriModel{L"Night light settings", Settings::NightLight},
                    WinUI3Example::UriModel{L"Projecting to this PC", Settings::Project},
                    WinUI3Example::UriModel{L"Shared experiences", Settings::CrossDevice},
                    WinUI3Example::UriModel{L"Tablet mode", Settings::TabletMode},
                    WinUI3Example::UriModel{L"Taskbar", Settings::Taskbar},
                    WinUI3Example::UriModel{L"Notifications & actions", Settings::Notifications},
                    WinUI3Example::UriModel{L"Remote Desktop", Settings::RemoteDesktop},
                    WinUI3Example::UriModel{L"Phone", Settings::Phone},
                    WinUI3Example::UriModel{L"Power & sleep", Settings::PowerSleep},
                    WinUI3Example::UriModel{L"Presence sensing", Settings::Presence},
                    WinUI3Example::UriModel{L"Sound", Settings::Sound},
                    WinUI3Example::UriModel{L"Sound devices",Settings::Sound::Devices},
                    WinUI3Example::UriModel{L"Storage", Settings::StorageSense},
                    WinUI3Example::UriModel{L"Storage Sense", Settings::StoragePolicies},
                    WinUI3Example::UriModel{L"Storage recommendations", Settings::StorageRecommendations},
                    WinUI3Example::UriModel{L"Disks & volumes", Settings::DisksAndVolumes}
                }) },
                WinUI3Example::UriGroup{ L"Time and language", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Date & time", Settings::DateAndTime},
                    WinUI3Example::UriModel{L"Japan IME settings", Settings::RegionLanguage::JpnIME},
                    WinUI3Example::UriModel{L"Region", Settings::RegionFormatting},
                    WinUI3Example::UriModel{L"Language", Settings::Keyboard},
                    WinUI3Example::UriModel{L"Language", Settings::Keyboard::Advanced},
                    WinUI3Example::UriModel{L"Language", Settings::RegionLanguage},
                    WinUI3Example::UriModel{L"Language", Settings::RegionLanguage::BpmfIME},
                    WinUI3Example::UriModel{L"Language", Settings::RegionLanguage::CangjieIME},
                    WinUI3Example::UriModel{L"Language", Settings::RegionLanguage::ChsIME::Wubi::Udp},
                    WinUI3Example::UriModel{L"Language", Settings::RegionLanguage::QuickIME},
                    WinUI3Example::UriModel{L"Language", Settings::RegionLanguage::KorIME},
                    WinUI3Example::UriModel{L"Pinyin IME settings", Settings::RegionLanguage::ChsIME::Pinyin},
                    WinUI3Example::UriModel{L"Pinyin IME settings", Settings::RegionLanguage::ChsIME::Pinyin::DomainLexicon},
                    WinUI3Example::UriModel{L"Pinyin IME settings", Settings::RegionLanguage::ChsIME::Pinyin::KeyConfig},
                    WinUI3Example::UriModel{L"Pinyin IME settings", Settings::RegionLanguage::ChsIME::Pinyin::Udp},
                    WinUI3Example::UriModel{L"Speech", Settings::Speech},
                    WinUI3Example::UriModel{L"Wubi IME settings", Settings::RegionLanguage::ChsIME::Wubi},
                    WinUI3Example::UriModel{L"Add display language", Settings::RegionLanguage::AddDisplayLanguage},
                    WinUI3Example::UriModel{L"Language options", Settings::RegionLanguage::LanguageOptions},
                    WinUI3Example::UriModel{L"Set display language", Settings::RegionLanguage::SetDisplayLangauge}
                }) },
                WinUI3Example::UriGroup{ L"Update and security", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Activation", Settings::Activation},
                    WinUI3Example::UriModel{L"Backup", Settings::Backup},
                    WinUI3Example::UriModel{L"Delivery Optimization", Settings::Delivery::Optimization},
                    WinUI3Example::UriModel{L"Delivery Optimization", Settings::Delivery::Optimization::Activity},
                    WinUI3Example::UriModel{L"Delivery Optimization", Settings::Delivery::Optimization::Advanced},
                    WinUI3Example::UriModel{L"Find My Device", Settings::FindMyDevice},
                    WinUI3Example::UriModel{L"For developers", Settings::Developers},
                    WinUI3Example::UriModel{L"Recovery", Settings::Recovery},
                    WinUI3Example::UriModel{L"Launch Security Key Enrollment", Settings::SignInOptions::LaunchSecurityKeyEnrollment},
                    WinUI3Example::UriModel{L"Troubleshoot", Settings::Troubleshoot},
                    WinUI3Example::UriModel{L"Windows Security", Settings::WindowsDefender},
                    WinUI3Example::UriModel{L"Windows Insider Program", Settings::WindowsInsider},
                    WinUI3Example::UriModel{L"Windows Insider Program", Settings::WindowsInsider::Optin},
                    WinUI3Example::UriModel{L"Windows Update", Settings::WindowsUpdate},
                    WinUI3Example::UriModel{L"Windows Update", Settings::WindowsUpdate::Action},
                    WinUI3Example::UriModel{L"Windows Update-Active hours", Settings::WindowsUpdate::ActiveHours},
                    WinUI3Example::UriModel{L"Windows Update-Advanced options", Settings::WindowsUpdate::Options},
                    WinUI3Example::UriModel{L"Windows Update-Optional updates", Settings::WindowsUpdate::OptionalUpdates},
                    WinUI3Example::UriModel{L"Windows Update-Restart options", Settings::WindowsUpdate::RestartOptions},
                    WinUI3Example::UriModel{L"Windows Update-Seeker on demand", Settings::WindowsUpdate::SeekerOnDemand},
                    WinUI3Example::UriModel{L"Windows Update-View update history", Settings::WindowsUpdate::History}
                }) },
                WinUI3Example::UriGroup{ L"User accounts", winrt::single_threaded_vector(std::vector<winrt::Windows::Foundation::IInspectable>{
                    WinUI3Example::UriModel{L"Provisioning", Settings::Workplace::Provisioning},
                    WinUI3Example::UriModel{L"Repair token", Settings::Workplace::RepairToken},
                    WinUI3Example::UriModel{L"Provisioning", Settings::Provisioning},
                    WinUI3Example::UriModel{L"Windows Anywhere", Settings::WindowsAnywhere}
                }) }
        });
    }
}
