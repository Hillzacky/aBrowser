#ifndef API_H
#define API_H

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
  static void setSettings(const std::string &settingsJSON);
};

#endif
