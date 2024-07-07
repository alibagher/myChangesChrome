// Located under "src/chrome/browser/extensions/api/utilities"

#include "utilities.h"
#include <string>
#include <sstream>
#include <vector>

// GetVersion
#include "base/version.h"  // Include base/version.h for version parsing

// IsFirstRun
#include "chrome/browser/browser_process.h"
#include "chrome/browser/prefs/browser_prefs.h"
#include "components/prefs/pref_service.h"
#include "components/prefs/pref_registry_simple.h"

// 
#include "chrome/browser/extensions/api/utilities/utilities_api.h"
#include "content/public/browser/clipboard_monitor.h"
#include "extensions/browser/event_router.h"

namespace extensions {

std::string GetVersion() {
    std::string full_version = chrome::GetVersionString();

    // Extract major version number
    Version chromium_version(full_version);
    int major_version = chromium_version.Major();

    // Construct limited version string with major version only
    std::stringstream limited_version;
    limited_version << "Major Version: " << major_version;
    return limited_version.str();
}

/////// Initializations for IsFirstRun ////////////

const char kFirstLaunchKey[] = "first_launch";

void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
    // Register the preference with a default value of false
    registry->RegisterBooleanPref(kFirstLaunchKey, false);
}

void CheckAndSetFirstLaunch(PrefService* local_state) {
    // Check if the preference exists
    if (!local_state->GetBoolean(kFirstLaunchKey)) {
        // This is the first launch
        local_state->SetBoolean(kFirstLaunchKey, true);
        // Perform first launch actions
        LOG(INFO) << "This is the first launch of the browser.";
    } else {
        // Not the first launch
        LOG(INFO) << "This is not the first launch.";
    }
}

void InitializeLocalState(PrefService* local_state) {
    RegisterLocalStatePrefs(local_state);
    CheckAndSetFirstLaunch(local_state);
}

bool IsFirstRun() {
    // Ensure the preference is registered
    RegisterLocalStatePrefs(local_state->registry());

    bool isFirstLaunch = local_state->GetBoolean(kFirstLaunchKey);
    if (isFirstLaunch) {
        LOG(INFO) << "This is the first launch of the browser.";
        return true;
    }
    
    LOG(INFO) << "This is not the first launch.";
    return false;
}

/////// Initializations for onClipboardContentChanged ////////////
https://source.chromium.org/chromium/chromium/src/+/main:extensions/browser/api/clipboard/clipboard_api.cc;l=15;bpv=1;bpt=0
https://source.chromium.org/chromium/chromium/src/+/main:ui/base/clipboard/clipboard_monitor.h;drc=fe91e486972e3ce15459cea8765892913e487824;bpv=1;bpt=0;l=1
void TabsEventRouter::DispatchTabUpdatedEvent(
    WebContents* contents,
    const std::set<std::string> changed_property_names) {
  DCHECK(!changed_property_names.empty());
  DCHECK(contents);

  Profile* profile = Profile::FromBrowserContext(contents->GetBrowserContext());

  auto event = std::make_unique<Event>(
      events::TABS_ON_UPDATED, api::tabs::OnUpdated::kEventName,
      // The event arguments depend on the extension's permission. They are set
      // in WillDispatchTabUpdatedEvent().
      base::Value::List(), profile);
  event->user_gesture = EventRouter::USER_GESTURE_NOT_ENABLED;
  event->will_dispatch_callback =
      base::BindRepeating(&WillDispatchTabUpdatedEvent, contents,
                          std::move(changed_property_names));
  EventRouter::Get(profile)->BroadcastEvent(std::move(event));
}



#include "chrome/browser/extensions/api/utilities/utilities_api.h"
#include "chrome/browser/profiles/profile.h"
#include "extensions/browser/event_router.h"
#include "extensions/browser/extensions_browser_client.h"
#include "chrome/browser/extensions/api/constants.h"

UtilitiesAPI::UtilitiesAPI() {
  ui::ClipboardMonitor::GetInstance()->AddObserver(this);
}

UtilitiesAPI::~UtilitiesAPI() {
  ui::ClipboardMonitor::GetInstance()->RemoveObserver(this);
}

void UtilitiesAPI::OnClipboardDataChanged() {
  // Call your custom method when the clipboard data changes
  OnClipboardContentChanged();
}

void UtilitiesAPI::OnClipboardContentChanged() {
  // Logic to fire the event to the JavaScript side
  Profile* profile = Profile::FromBrowserContext(
      ExtensionsBrowserClient::Get()->GetMainContext());
  EventRouter* event_router = EventRouter::Get(profile);
  if (event_router) {
    auto event = std::make_unique<Event>(
        events::kOnClipboardContentChanged, 
        "utilities.onClipboardContentChanged", 
        std::make_unique<base::ListValue>());
    event_router->BroadcastEvent(std::move(event));
  }
}




} // namespace extensions
