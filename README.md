# myChangesChrome

# TODO: Talk about why the isfirstrun function is called in the file it is.

# "Compilation steps can be selective, since not all APIs need to be included in all compilation steps. For instance, some APIs are implemented entirely in the renderer, and thus do not need to have strong types or function registration generated. See the JSON Schema Compiler for more information." https://chromium.googlesource.com/chromium/src/+/main/chrome/common/extensions/api/schemas.md#compilation

The above quote says that APIs implemented in the renxdered do not need to have function registration generated, but utilities is in the browser, and so it does need one.
