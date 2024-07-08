#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>

// IsFirstRun
#include "chrome/browser/browser_process.h"
#include "chrome/browser/prefs/browser_prefs.h"
#include "components/prefs/pref_service.h"
#include "components/prefs/pref_registry_simple.h"


#include "base/macros.h"
#include "extensions/browser/extension_function.h"
#include "ui/base/clipboard/clipboard_monitor.h"
#include "ui/base/clipboard/clipboard_observer.h"
#include "extensions/browser/event_router.h"

namespace extensions {

class VersionSetup {
public:
  void InitializeLocalState(PrefService* local_state);
private:
  static const char kFirstLaunchKey[];

  void RegisterLocalStatePrefs(PrefRegistrySimple* registry); 
  void CheckAndSetFirstLaunch(PrefService* local_state);
}

class UtilitiesGetVersion: public ExtensionFunction{
  ~UtilitiesGetVersion() override {}
  ResponseAction Run() override;
  DECLARE_EXTENSION_FUNCTION("chrome.utilities.getVersion", CHROME_UTILITIES_GETVERSION)
};

class UtilitiesIsFirstRun: public ExtensionFunction{
  ~UtilitiesIsFirstRun() override {}
  ResponseAction Run() override;
  DECLARE_EXTENSION_FUNCTION("chrome.utilities.isFirstRun", CHROME_UTILITIES_ISFIRSTRUN)
};

class UtilitiesClipboardAPI: public ui::ClipboardObserver{
 public:
  UtilitiesClipboardAPI();
  ~UtilitiesClipboardAPI() override;

  static const char kEventName[];
  static const char event_name_[];

  void OnClipboardDataChanged() override;
};

} // namespace extensions

#endif // UTILITIES_H_
