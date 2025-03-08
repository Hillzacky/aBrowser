#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <include/cef_app.h>

class Settings {
public:
  // ... getters and setters for settings
  void applyBrowserSettings(CefBrowserSettings &settings) const;
  void applyRequestContextSettings(CefRequestContextSettings &settings) const;
  bool isCanvasSpoofEnabled() const;
  bool isWebGlSpoofEnabled() const;

private:
  // ... settings variables
};

#endif
