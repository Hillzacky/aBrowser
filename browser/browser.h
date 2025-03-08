#ifndef BROWSER_H
#define BROWSER_H

#include "../settings/settings.h"
#include "js_injector.h"
#include "res_handler.h"
#include <include/cef_app.h>
#include <include/cef_browser.h>

class Browser : public CefClient,
                public CefLifeSpanHandler,
                public CefLoadHandler,
                public CefRenderProcessHandler,
                public CefResourceRequestHandler {
public:
  Browser(const Settings &settings);

  CefLifeSpanHandler *GetLifeSpanHandler() override;
  CefLoadHandler *GetLoadHandler() override;
  CefRenderProcessHandler *GetRenderProcessHandler() override;
  CefResourceRequestHandler *GetResourceRequestHandler() override;

  void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
  void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                        CefRefPtr<CefV8Context> context) override;
  CefRefPtr<CefResourceHandler> GetResourceHandler(
      CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
      CefRefPtr<CefRequest> request) override;

private:
  Settings settings_;
  JSInjector jsInjector_;
};

#endif
