#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>

#include "base/macros.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/event_router.h"

namespace extensions {
namespace utilities {
// // Permission for accessing utilities namespace
// const char* const kUtilitiesPermission = "utilities";

std::string GetVersion();

bool IsFirstRun();

// // Event fired when clipboard content changes
// typedef base::Callback<void(const std::string&)> ClipboardContentChangedCallback;

// onClipboardContentChanged
// https://source.chromium.org/chromium/chromium/src/+/main:ui/base/clipboard/clipboard_monitor.h;drc=fe91e486972e3ce15459cea8765892913e487824;bpv=1;bpt=0;l=1
static void OnClipboardContentChanged();


}  // namespace utilities
}  // namespace extensions
#endif  // UTILITIES_H_
