#include "js_injector.h"

JSInjector::JSInjector(const Settings &settings) : settings_(settings) {}

void JSInjector::inject(CefRefPtr<CefFrame> frame) {
  if (settings_.isCanvasSpoofEnabled()) {
    frame->ExecuteJavaScript(
        "(function() { /* Canvas spoofing code */ })();", "", 0);
  }
  if (settings_.isWebGlSpoofEnabled()) {
    frame->ExecuteJavaScript(
        "(function() { /* WebGL spoofing code */ })();", "", 0);
  }
  // ... other injections
}
