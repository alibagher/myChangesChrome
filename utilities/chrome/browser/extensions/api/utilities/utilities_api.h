#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>

#include "base/macros.h"
#include "extensions/browser/extension_function.h"
#include "ui/base/clipboard/clipboard_monitor.h"
#include "ui/base/clipboard/clipboard_observer.h"
#include "extensions/browser/event_router.h"

namespace extensions {

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
