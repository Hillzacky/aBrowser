#include "main_window.h"
#include "ui_main_window.h"
#include "../browser/browser.h"
#include <QtWidgets/QMessageBox>
#include <include/cef_app.h>
#include <include/cef_browser.h>
#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(const Settings &settings, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), settings_(settings) {
  ui->setupUi(this);
  tabWidget_ = ui->tabWidget;

  connect(ui->actionNewTab, &QAction::triggered, this, &MainWindow::on_actionNewTab_triggered);
  connect(ui->actionCloseTab, &QAction::triggered, this, &MainWindow::on_actionCloseTab_triggered);
  connect(ui->actionExit, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);
  connect(ui->lineEditURL, &QLineEdit::returnPressed, this, &MainWindow::on_lineEditURL_returnPressed);

  on_actionNewTab_triggered(); // Buka tab awal
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionNewTab_triggered() {
  CefWindowInfo windowInfo;
  windowInfo.SetAsChild(tabWidget_->currentWidget()->winId(), {0, 0, 800, 600});

  CefBrowserSettings browserSettings;
  settings_.applyBrowserSettings(browserSettings);

  CefRequestContextSettings contextSettings;
  settings_.applyRequestContextSettings(contextSettings);
  CefRefPtr<CefRequestContext> requestContext =
      CefRequestContext::CreateContext(contextSettings, nullptr);

  CefRefPtr<Browser> browserClient = new Browser(settings_);
  CefBrowserHost::CreateBrowserSync(windowInfo, browserSettings, browserClient,
                                    "https://www.google.com", requestContext);

  tabWidget_->addTab(tabWidget_->currentWidget(), "New Tab");
}

void MainWindow::on_actionCloseTab_triggered() {
  if (tabWidget_->count() > 1) {
    tabWidget_->removeTab(tabWidget_->currentIndex());
  } else {
    QMessageBox::information(this, "Info", "Tidak dapat menutup tab terakhir.");
  }
}

void MainWindow::on_actionExit_triggered() { QApplication::quit(); }

void MainWindow::on_lineEditURL_returnPressed() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    browser->GetHost()->LoadURL(ui->lineEditURL->text().toStdString());
  }
}

void MainWindow::loadURLFromAPI(const QString &url) {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    browser->GetHost()->LoadURL(url.toStdString());
  }
}

void MainWindow::goBackFromAPI() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    browser->GetHost()->GoBack();
  }
}

void MainWindow::goForwardFromAPI() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    browser->GetHost()->GoForward();
  }
}

void MainWindow::reloadFromAPI() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    browser->GetHost()->Reload();
  }
}

void MainWindow::executeJSFromAPI(const QString &code) {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    browser->GetMainFrame()->ExecuteJavaScript(code.toStdString(), "", 0);
  }
}

QString MainWindow::getHTMLFromAPI() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    // Implementasikan pengambilan HTML (misalnya, menggunakan CefGetSourceVisitor)
    return QString(); // Placeholder
  }
  return QString();
}

QString MainWindow::getURLFromAPI() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    return QString::fromStdString(browser->GetMainFrame()->GetURL());
  }
  return QString();
}

QString MainWindow::getCookiesFromAPI() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    // Implementasikan pengambilan cookie (misalnya, menggunakan CefCookieVisitor)
    return QString(); // Placeholder
  }
  return QString();
}

void MainWindow::setProxyFromAPI(const QString &proxy) {
  // Implementasikan pengaturan proxy
}

void MainWindow::setSettingsFromAPI(const QString &settingsJSON) {
  QJsonDocument doc = QJsonDocument::fromJson(settingsJSON.toUtf8());
  if (!doc.isNull()) {
    QJsonObject obj = doc.object();
    // Implementasikan pengaturan dari JSON
  }
}

CefRefPtr<CefBrowser> MainWindow::getCurrentBrowser() {
  if (tabWidget_->count() > 0) {
    QWidget *currentTab = tabWidget_->currentWidget();
    // Implementasikan pencarian CefBrowser dari QWidget tab
    // Misalnya, simpan pointer CefBrowser di QWidget tab
    return nullptr; // Placeholder
  }
  return nullptr;
}
