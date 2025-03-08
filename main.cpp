#include "ui/main_window.h"
#include "settings/settings.h"
#include <QtWidgets/QApplication>
#include <include/cef_app.h>
#include <QDir>
#include <QStandardPaths>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Settings settings;

  // Atur direktori cache CEF
  CefSettings cefSettings;
  QString cachePath = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/AntiDetectionBrowser";
  QDir dir(cachePath);
  if (!dir.exists()) {
    dir.mkpath(".");
  }
  CefString(&cefSettings.cache_path) = cachePath.toStdString();

  CefMainArgs mainArgs(argc, argv);
  CefInitialize(mainArgs, cefSettings, nullptr, nullptr);

  MainWindow mainWindow(settings);
  mainWindow.show();

  int result = app.exec();

  CefShutdown();
  return result;
}
