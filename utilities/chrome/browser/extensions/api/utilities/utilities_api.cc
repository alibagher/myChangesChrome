// Located under "src/chrome/browser/extensions/api/utilities"

#include "utilities.h"
#include <string>
#include <vector>

// GetVersion
#include "base/version.h"  // Include base/version.h for version parsing

// 
#include "chrome/browser/extensions/api/utilities/utilities_api.h"
#include "content/public/browser/clipboard_monitor.h"
#include "extensions/browser/event_router.h"

#include "chrome/browser/extensions/api/utilities/utilities_api.h"
#include "chrome/browser/profiles/profile.h"
#include "extensions/browser/event_router.h"
#include "extensions/browser/extensions_browser_client.h"
#include "chrome/browser/extensions/api/constants.h"

namespace extensions {

ExtensionFunction::ResponseAction UtilitiesGetVersion::Run() {
    std::string full_version = chrome::GetVersionString();

    // Extract major version number
    Version chromium_version(full_version);
    int major_version = chromium_version.Major();
    std::string s = std::to_string(major_version);
    
    return RespondNow(WithArguments(std::move(s)));
}

/////// Initializations for IsFirstRun ////////////

const char VersionSetup::kFirstLaunchKey[] = "first_launch";

// TODO: put the initializations into its own class and call from startup. 

void VersionSetup::RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
    // Register the preference with a default value of false
    registry->RegisterBooleanPref(kFirstLaunchKey, false);
}

void VersionSetup::CheckAndSetFirstLaunch(PrefService* local_state) {
    // Check if the preference exists
    if (!local_state->GetBoolean(kFirstLaunchKey)) {
        local_state->SetBoolean(kFirstLaunchKey, true);
        // Perform first launch actions
        LOG(INFO) << "This is the first launch of the browser.";
    } else {
        // Not the first launch
        LOG(INFO) << "This is not the first launch.";
    }
}

void VersionSetup::InitializeLocalState(PrefService* local_state) {
    RegisterLocalStatePrefs(local_state);
    CheckAndSetFirstLaunch(local_state);
}

ExtensionFunction::ResponseAction UtilitiesIsFirstRun::Run() {
    RegisterLocalStatePrefs(local_state->registry());

    bool isFirstLaunch = local_state->GetBoolean(kFirstLaunchKey);
    if (isFirstLaunch) {
        LOG(INFO) << "This is the first launch of the browser.";
        return RespondNow(WithArguments(true));
    }
    
    LOG(INFO) << "This is not the first launch.";
    
    return RespondNow(WithArguments(false));
}


/////// onClipboardContentChanged ////////////
const char ClipboardContentChangedEvent::kEventName[] = "onClipboardContentChanged";
const char ClipboardContentChangedEvent::event_name_[] = "chrome.utilities.onClipboardContentChanged";

UtilitiesClipboardAPI::UtilitiesClipboardAPI() {
  ui::ClipboardMonitor::GetInstance()->AddObserver(this);
}

UtilitiesClipboardAPI::~UtilitiesClipboardAPI() {
  ui::ClipboardMonitor::GetInstance()->RemoveObserver(this);
}

void UtilitiesClipboardAPI::OnClipboardDataChanged() {
      Profile* profile = Profile::FromBrowserContext(web_contents()->GetBrowserContext());
    
    auto event = std::make_unique<Event>(
      ClipboardContentChangedEvent::kEventName,
      ClipboardContentChangedEvent::event_name_,
      base::Value::List(), profile);
    event->user_gesture = EventRouter::USER_GESTURE_NOT_ENABLED;
    
    EventRouter::Get(profile)->BroadcastEvent(std::move(event));
}

} // namespace extensions
