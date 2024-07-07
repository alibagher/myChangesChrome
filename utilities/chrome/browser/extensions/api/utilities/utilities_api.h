#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>

#include "base/macros.h"
#include "extensions/browser/extension_function.h"
#include "ui/base/clipboard/clipboard_monitor.h"
#include "ui/base/clipboard/clipboard_observer.h"
#include "extensions/browser/event_router.h"

namespace chrome {
namespace utilities {

class UtilitiesAPI: public ui::ClipboardObserver{
 public:
  UtilitiesAPI();
  ~UtilitiesAPI() override;

  std::string GetVersion();

  bool IsFirstRun();

  void OnClipboardDataChanged() override;
  void OnClipboardContentChanged();
};

}  // namespace utilities
}  // namespace chrome
#endif  // UTILITIES_H_
