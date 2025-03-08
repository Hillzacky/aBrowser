#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <include/cef_app.h>
#include <QSettings>

class Settings {
public:
  Settings();

  // Getters
  bool isCanvasSpoofEnabled() const;
  bool isWebGlSpoofEnabled() const;
  std::string getUserAgent() const;
  std::string getProxy() const;
  std::string getCachePath() const;
  bool isJavaScriptEnabled() const;
  bool isPluginsEnabled() const;

  // Setters
  void setCanvasSpoofEnabled(bool enabled);
  void setWebGlSpoofEnabled(bool enabled);
  void setUserAgent(const std::string &userAgent);
  void setProxy(const std::string &proxy);
  void setCachePath(const std::string &cachePath);
  void setJavaScriptEnabled(bool enabled);
  void setPluginsEnabled(bool enabled);

  void applyBrowserSettings(CefBrowserSettings &settings) const;
  void applyRequestContextSettings(CefRequestContextSettings &settings) const;
  void saveSettings();
  void loadSettings();

private:
  bool canvasSpoofEnabled_;
  bool webGlSpoofEnabled_;
  std::string userAgent_;
  std::string proxy_;
  std::string cachePath_;
  bool javaScriptEnabled_;
  bool pluginsEnabled_;
  QSettings settingsFile_;
};

#endif // SETTINGS_H
