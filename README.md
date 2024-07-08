# Task: Chromium Extension APIs
Task for RedBrick (Shift) Lead Software Developer (Chromium).

# BUILD DEPS
Only need to add dependency to 'chrome/browser/extensions/BUILD.gn' because higher deps depend on this file, so utilities will be included.

# Chromium version
62.0.3202.66

# platform
MacOS


# isFirstRun
The official documentation (https://www.chromium.org/developers/how-tos/getting-around-the-chrome-source-code/#application-startup ) clearly indicates that on startup of the browser, the BrowserMain function in `chrome/browser/browser_main.cc` does common browser initialization. This is a good location to place the initialization of `isFirstRun`, which is to write to local file a boolean indicating first run or no.

isFirstRun is initialized in the 'utilities/chrome/browser/chrome_browser_main.cc' changes are including the utilities header file and 
the following on line 1003:

```
  // Initialize utilities local storage
  VersionSetup version_setup;
  version_setup.InitializeLocalState(browser_process_->local_state());
```


# onClipboardContentChanged
I used the ui::ClipboardObserver class and overrided the OnClipboardDataChanged method which fires when clipboard data is changed. This then broadcasts the event (chrome.utilities.onClipboardContentChanged).
