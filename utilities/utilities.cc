// #include "utilities.h"
// #include <string>
// #include <sstream>
// #include <vector>

// // GetVersion
// #include "base/version.h"  // Include base/version.h for version parsing

// // IsFirstRun
// #include "chrome/browser/browser_process.h"
// #include "chrome/browser/prefs/browser_prefs.h"
// #include "components/prefs/pref_service.h"
// #include "components/prefs/pref_registry_simple.h"

// // 

// namespace utilities {
// std::string GetVersion() {
//     std::string full_version = chrome::GetVersionString();

//     // Extract major version number
//     Version chromium_version(full_version);
//     int major_version = chromium_version.Major();

//     // Construct limited version string with major version only
//     std::stringstream limited_version;
//     limited_version << "Major Version: " << major_version;
//     return limited_version.str();
// }

// /////// Initializations for IsFirstRun ////////////

// const char kFirstLaunchKey[] = "first_launch";

// void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
//     // Register the preference with a default value of false
//     registry->RegisterBooleanPref(kFirstLaunchKey, false);
// }

// void CheckAndSetFirstLaunch(PrefService* local_state) {
//     // Check if the preference exists
//     if (!local_state->GetBoolean(kFirstLaunchKey)) {
//         // This is the first launch
//         local_state->SetBoolean(kFirstLaunchKey, true);
//         // Perform first launch actions
//         LOG(INFO) << "This is the first launch of the browser.";
//     } else {
//         // Not the first launch
//         LOG(INFO) << "This is not the first launch.";
//     }
// }

// void InitializeLocalState(PrefService* local_state) {
//     RegisterLocalStatePrefs(local_state);
//     CheckAndSetFirstLaunch(local_state);
// }

// bool IsFirstRun() {
//     // Ensure the preference is registered
//     RegisterLocalStatePrefs(local_state->registry());

//     bool isFirstLaunch = local_state->GetBoolean(kFirstLaunchKey);
//     if (isFirstLaunch) {
//         LOG(INFO) << "This is the first launch of the browser.";
//         return true;
//     }
    
//     LOG(INFO) << "This is not the first launch.";
//     return false;
// }

// /////// Initializations for onClipboardContentChanged ////////////

// void onClipboardContentChanged(const ClipboardContentChangedCallback& callback) {

// }
// }  // namespace utilities
