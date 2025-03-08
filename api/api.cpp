#include "api.h"
#include "../ui/main_window.h" // Perlu akses ke MainWindow
#include <QApplication>
#include <QMetaObject>
#include <QJsonDocument>
#include <QJsonObject>

void BrowserAPI::loadURL(const std::string &url) {
  QMetaObject::invokeMethod(QApplication::instance()->topLevelWidgets().at(0),
                            "loadURLFromAPI", Q_ARG(QString, QString::fromStdString(url)));
}

void BrowserAPI::goBack() {
  QMetaObject::invokeMethod(QApplication::instance()->topLevelWidgets().at(0),
                            "goBackFromAPI");
}

void BrowserAPI::goForward() {
  QMetaObject::invokeMethod(QApplication::instance()->topLevelWidgets().at(0),
                            "goForwardFromAPI");
}

void BrowserAPI::reload() {
  QMetaObject::invokeMethod(QApplication::instance()->topLevelWidgets().at(0),
                            "reloadFromAPI");
}

void BrowserAPI::executeJavaScript(const std::string &code) {
  QMetaObject::invokeMethod(QApplication::instance()->topLevelWidgets().at(0),
                            "executeJSFromAPI", Q_ARG(QString, QString::fromStdString(code)));
}

std::string BrowserAPI::getHTML() {
  QString html;
  QMetaObject::invokeMethod(QApplication::instance()->topLevelWidgets().at(0),
                            "getHTMLFromAPI", Q_RETURN_ARG(QString, html));
  return html.toStdString();
}

std::string BrowserAPI::getURL() {
  QString url;
  QMetaObject::invokeMethod(QApplication::instance()->topLevelWidgets().at(0),
                            "getURLFromAPI", Q_RETURN_ARG(QString, url));
  return url.toStdString();
}

std::string BrowserAPI::getCookies() {
  QString cookies;
  QMetaObject::invokeMethod(QApplication::instance()->topLevelWidgets().at(0),
                            "getCookiesFromAPI", Q_RETURN_ARG(QString, cookies));
  return cookies.toStdString();
}

void BrowserAPI::setProxy(const std::string &proxy) {
  QMetaObject::invokeMethod(QApplication::instance()->topLevelWidgets().at(0),
                            "setProxyFromAPI", Q_ARG(QString, QString::fromStdString(proxy)));
}

void BrowserAPI::setSettings(const std::string &settingsJSON) {
  QMetaObject::invokeMethod(QApplication::instance()->topLevelWidgets().at(0),
                            "setSettingsFromAPI", Q_ARG(QString, QString::fromStdString(settingsJSON)));
}
