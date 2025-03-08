#include "settings.h"
#include <QDir>
#include <QStandardPaths>

Settings::Settings()
    : canvasSpoofEnabled_(false),
      webGlSpoofEnabled_(false),
      userAgent_(""),
      proxy_(""),
      javaScriptEnabled_(true),
      pluginsEnabled_(false),
      settingsFile_(QSettings::IniFormat, QSettings::UserScope, "AntiDetectionBrowser", "Settings") {
  cachePath_ = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/AntiDetectionBrowser";
  loadSettings();
}

bool Settings::isCanvasSpoofEnabled() const {
  return canvasSpoofEnabled_;
}

bool Settings::isWebGlSpoofEnabled() const {
  return webGlSpoofEnabled_;
}

std::string Settings::getUserAgent() const {
  return userAgent_;
}

std::string Settings::getProxy() const {
  return proxy_;
}

std::string Settings::getCachePath() const {
  return cachePath_;
}

bool Settings::isJavaScriptEnabled() const {
  return javaScriptEnabled_;
}

bool Settings::isPluginsEnabled() const {
  return pluginsEnabled_;
}

void Settings::setCanvasSpoofEnabled(bool enabled) {
  canvasSpoofEnabled_ = enabled;
}

void Settings::setWebGlSpoofEnabled(bool enabled) {
  webGlSpoofEnabled_ = enabled;
}

void Settings::setUserAgent(const std::string &userAgent) {
  userAgent_ = userAgent;
}

void Settings::setProxy(const std::string &proxy) {
  proxy_ = proxy;
}

void Settings::setCachePath(const std::string &cachePath) {
  cachePath_ = cachePath;
}

void Settings::setJavaScriptEnabled(bool enabled) {
  javaScriptEnabled_ = enabled;
}

void Settings::setPluginsEnabled(bool enabled) {
  pluginsEnabled_ = enabled;
}

void Settings::applyBrowserSettings(CefBrowserSettings &settings) const {
  settings.web_security = STATE_DISABLED;
  settings.javascript = javaScriptEnabled_ ? STATE_ENABLED : STATE_DISABLED;
  settings.plugins = pluginsEnabled_ ? STATE_ENABLED : STATE_DISABLED;
  settings.remote_fonts = STATE_DISABLED;
  settings.default_encoding = "UTF-8";
  if (!userAgent_.empty()) {
    settings.user_agent = userAgent_;
  }
}

void Settings::applyRequestContextSettings(CefRequestContextSettings &settings) const {
  if (!proxy_.empty()) {
    settings.proxy_type = PROXY_TYPE_HTTP;
    settings.proxy_uri = proxy_;
  } else {
    settings.proxy_type = PROXY_TYPE_NONE;
  }
}

void Settings::saveSettings() {
  settingsFile_.setValue("canvasSpoofEnabled", canvasSpoofEnabled_);
  settingsFile_.setValue("webGlSpoofEnabled", webGlSpoofEnabled_);
  settingsFile_.setValue("userAgent", QString::fromStdString(userAgent_));
  settingsFile_.setValue("proxy", QString::fromStdString(proxy_));
  settingsFile_.setValue("cachePath", QString::fromStdString(cachePath_));
  settingsFile_.setValue("javaScriptEnabled", javaScriptEnabled_);
  settingsFile_.setValue("pluginsEnabled", pluginsEnabled_);
}

void Settings::loadSettings() {
  canvasSpoofEnabled_ = settingsFile_.value("canvasSpoofEnabled", false).toBool();
  webGlSpoofEnabled_ = settingsFile_.value("webGlSpoofEnabled", false).toBool();
  userAgent_ = settingsFile_.value("userAgent", "").toString().toStdString();
  proxy_ = settingsFile_.value("proxy", "").toString().toStdString();
  cachePath_ = settingsFile_.value("cachePath", QString::fromStdString(cachePath_)).toString().toStdString();
  javaScriptEnabled_ = settingsFile_.value("javaScriptEnabled", true).toBool();
  pluginsEnabled_ = settingsFile_.value("pluginsEnabled", false).toBool();
}
