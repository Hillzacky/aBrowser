#ifndef JS_INJECTOR_H
#define JS_INJECTOR_H

#include "../settings/settings.h"
#include <include/cef_app.h>
#include <include/cef_browser.h>

class JSInjector {
public:
  JSInjector(const Settings &settings);
  void inject(CefRefPtr<CefFrame> frame);

private:
  Settings settings_;
};

#endif
