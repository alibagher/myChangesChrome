# Task: Chromium Extension APIs
Task for RedBrick (Shift) Lead Software Developer (Chromium).

# isFirstRun
The official documentation (https://www.chromium.org/developers/how-tos/getting-around-the-chrome-source-code/#application-startup ) clearly indicates that on startup of the browser, the BrowserMain function in `chrome/browser/browser_main.cc` does common browser initialization. This is a good location to place the initialization of `isFirstRun`, which is to write to local file a boolean indicating first run or no.

isFirstRun is initialized in the 'utilities/chrome/browser/chrome_browser_main.cc' changes are including the utilities header file and 
the following on line 1003:

```
  // Initialize utilities local storage
  VersionSetup version_setup;
  version_setup.InitializeLocalState(browser_process_->local_state());
```


"Compilation steps can be selective, since not all APIs need to be included in all compilation steps. For instance, some APIs are implemented entirely in the renderer, and thus do not need to have strong types or function registration generated. See the JSON Schema Compiler for more information." https://chromium.googlesource.com/chromium/src/+/main/chrome/common/extensions/api/schemas.md#compilation

The above quote says that APIs implemented in the renxdered do not need to have function registration generated, but utilities is in the browser, and so it does need one.


# BUILD DEPS
Only need to add dependency to 'chrome/browser/extensions/BUILD.gn' because higher deps depend on this file, so utilities will be included. 
