#include "browser.h"
#include <vector>
#include <cstdlib>

Browser::Browser(const Settings &settings) : settings_(settings), jsInjector_(settings) {}

CefLifeSpanHandler *Browser::GetLifeSpanHandler() { return this; }
CefLoadHandler *Browser::GetLoadHandler() { return this; }
CefRenderProcessHandler *Browser::GetRenderProcessHandler() { return this; }
CefResourceRequestHandler *Browser::GetResourceRequestHandler() { return this; }

void Browser::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
  CefBrowserSettings browserSettings;
  settings_.applyBrowserSettings(browserSettings);
  browser->GetHost()->SetBrowserSettings(browserSettings);

  CefRequestContextSettings contextSettings;
  settings_.applyRequestContextSettings(contextSettings);
  CefRefPtr<CefRequestContext> requestContext =
      CefRequestContext::CreateContext(contextSettings, nullptr);
  browser->GetHost()->SetRequestContext(requestContext);
}

void Browser::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                              CefRefPtr<CefV8Context> context) {
  jsInjector_.inject(frame);
}

CefRefPtr<CefResourceHandler> Browser::GetResourceHandler(
    CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
    CefRefPtr<CefRequest> request) {
  // Implementasikan penanganan sumber daya (misalnya, blokir permintaan)
  return nullptr;
}
