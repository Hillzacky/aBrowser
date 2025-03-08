#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "../browser/browser.h"
#include "../settings/settings.h"
#include <QtWidgets/QMainWindow>
#include <include/cef_app.h>
#include <include/cef_browser.h>
#include <QTabWidget>
#include <QLineEdit>
#include <QMap>
#include <QMenu>
#include <QToolBar>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(const Settings &settings, QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void loadURLFromAPI(const QString &url);
  void goBackFromAPI();
  void goForwardFromAPI();
  void reloadFromAPI();
  void executeJSFromAPI(const QString &code);
  QString getHTMLFromAPI();
  QString getURLFromAPI();
  QString getCookiesFromAPI();
  void setProxyFromAPI(const QString &proxy);
  void setSettingsFromAPI(const QString &settingsJSON);
  void takeScreenshotFromAPI(const QString &filePath);

private slots:
  void on_actionNewTab_triggered();
  void on_actionCloseTab_triggered();
  void on_actionExit_triggered();
  void on_lineEditURL_returnPressed();
  void on_actionBack_triggered();
  void on_actionForward_triggered();
  void on_actionReload_triggered();

private:
  Ui::MainWindow *ui;
  Settings settings_;
  QTabWidget *tabWidget_;
  QLineEdit *lineEditURL_;
  QMap<QWidget *, CefRefPtr<CefBrowser>> browserMap_;
  QMenu *fileMenu_;
  QMenu *editMenu_;
  QMenu *viewMenu_;
  QToolBar *navigationToolbar_;

  CefRefPtr<CefBrowser> getCurrentBrowser();
  void addTab(CefRefPtr<CefBrowser> browser, const QString &title);
  void removeTab(int index);
  void setupUI();
};

#endif
