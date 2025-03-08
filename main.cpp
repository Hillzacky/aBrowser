#ifndef API_H
#define API_H
#include "ui/main_window.h"
#include "settings/settings.h"
#include <QtWidgets/QApplication>
#include <include/cef_app.h>
#include <string>

class BrowserAPI {
public:
  static void loadURL(const std::string &url);
  static void goBack();
  static void goForward();
  static void reload();
  static void executeJavaScript(const std::string &code);
  static std::string getHTML();
  static std::string getURL();
  static std::string getCookies();
  static void setProxy(const std::string &proxy);
};

#endif

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Settings settings;
  CefMainArgs mainArgs(argc, argv);
  CefSettings cefSettings;
  CefInitialize(mainArgs, cefSettings, nullptr, nullptr);
  MainWindow mainWindow(settings);
  mainWindow.show();
  int result = app.exec();
  CefShutdown();
  return result;
}
