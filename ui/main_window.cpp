#include "main_window.h"
#include "ui_main_window.h"
#include "../browser/browser.h"
#include <QtWidgets/QMessageBox>
#include <include/cef_app.h>
#include <include/cef_browser.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QPixmap>
#include <QImage>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextEdit>
#include <QSettings>

MainWindow::MainWindow(const Settings &settings, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), settings_(settings) {
  ui->setupUi(this);
  tabWidget_ = ui->tabWidget;
  lineEditURL_ = ui->lineEditURL;

  connect(ui->actionNewTab, &QAction::triggered, this, &MainWindow::on_actionNewTab_triggered);
  connect(ui->actionCloseTab, &QAction::triggered, this, &MainWindow::on_actionCloseTab_triggered);
  connect(ui->actionExit, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);
  connect(lineEditURL_, &QLineEdit::returnPressed, this, &MainWindow::on_lineEditURL_returnPressed);
	 setupUI();
  on_actionNewTab_triggered(); // Buka tab awal
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setupUI() {
  tabWidget_ = ui->tabWidget;
  lineEditURL_ = ui->lineEditURL;

  fileMenu_ = menuBar()->addMenu("&File");
  fileMenu_->addAction(ui->actionNewTab);
  fileMenu_->addAction(ui->actionCloseTab);
  fileMenu_->addSeparator();
  fileMenu_->addAction(ui->actionExit);

  editMenu_ = menuBar()->addMenu("&Edit");
  // Tambahkan aksi edit

  viewMenu_ = menuBar()->addMenu("&View");
  // Tambahkan aksi view

  navigationToolbar_ = addToolBar("Navigation");
  navigationToolbar_->addAction(ui->actionBack);
  navigationToolbar_->addAction(ui->actionForward);
  navigationToolbar_->addAction(ui->actionReload);

  connect(ui->actionNewTab, &QAction::triggered, this, &MainWindow::on_actionNewTab_triggered);
  connect(ui->actionCloseTab, &QAction::triggered, this, &MainWindow::on_actionCloseTab_triggered);
  connect(ui->actionExit, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);
  connect(lineEditURL_, &QLineEdit::returnPressed, this, &MainWindow::on_lineEditURL_returnPressed);
  connect(ui->actionBack, &QAction::triggered, this, &MainWindow::on_actionBack_triggered);
  connect(ui->actionForward, &QAction::triggered, this, &MainWindow::on_actionForward_triggered);
  connect(ui->actionReload, &QAction::triggered, this, &MainWindow::on_actionReload_triggered);
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

void MainWindow::on_actionNewTab_triggered() {
  CefWindowInfo windowInfo;
  QWidget *tab = new QWidget();
  tabWidget_->addTab(tab, "New Tab");
  tabWidget_->setCurrentWidget(tab);
  windowInfo.SetAsChild(tab->winId(), {0, 0, tabWidget_->width(), tabWidget_->height()});

  CefBrowserSettings browserSettings;
  settings_.applyBrowserSettings(browserSettings);

  CefRequestContextSettings contextSettings;
  settings_.applyRequestContextSettings(contextSettings);
  CefRefPtr<CefRequestContext> requestContext =
      CefRequestContext::CreateContext(contextSettings, nullptr);

  CefRefPtr<Browser> browserClient = new Browser(settings_);
  CefBrowserHost::CreateBrowserSync(windowInfo, browserSettings, browserClient,
                                    "https://www.google.com", requestContext);

  browserMap_[tab] = browserClient->GetBrowser();
}

void MainWindow::on_actionCloseTab_triggered() {
  if (tabWidget_->count() > 1) {
    removeTab(tabWidget_->currentIndex());
  } else {
    QMessageBox::information(this, "Info", "Tidak dapat menutup tab terakhir.");
  }
}

void MainWindow::on_actionExit_triggered() { QApplication::quit(); }

void MainWindow::on_lineEditURL_returnPressed() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    browser->GetHost()->LoadURL(lineEditURL_->text().toStdString());
  }
}

CefRefPtr<CefBrowser> MainWindow::getCurrentBrowser() {
  QWidget *currentTab = tabWidget_->currentWidget();
  if (currentTab && browserMap_.contains(currentTab)) {
    return browserMap_[currentTab];
  }
  return nullptr;
}

void MainWindow::addTab(CefRefPtr<CefBrowser> browser, const QString &title) {
  QWidget *tab = new QWidget();
  QVBoxLayout *tabLayout = new QVBoxLayout(tab);
  tabLayout->setContentsMargins(0, 0, 0, 0);
  tabLayout->setSpacing(0);

  CefWindowInfo windowInfo;
  windowInfo.SetAsChild(tab->winId(), {0, 0, tabWidget_->width(), tabWidget_->height()});
  browser->GetHost()->SetWindowlessFrameRate(30);

  tabWidget_->addTab(tab, title);
  tabWidget_->setCurrentWidget(tab);
  browserMap_[tab] = browser;
}

void MainWindow::removeTab(int index) {
  QWidget *tab = tabWidget_->widget(index);
  tabWidget_->removeTab(index);
  browserMap_.remove(tab);
  delete tab;
}

// Implementasi pengambilan HTML (misalnya, menggunakan CefGetSourceVisitor)
class SourceVisitor : public CefStringVisitor {
public:
  SourceVisitor(QString *html) : html_(html) {}
  void Visit(const CefString &string) override {
    *html_ = QString::fromStdString(string.ToString());
  }
private:
  QString *html_;
};

QString MainWindow::getHTMLFromAPI() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    QString *html = new QString();
    browser->GetMainFrame()->GetSource(new SourceVisitor(html));
    return *html;
  }
  return QString();
}

// Implementasi pengambilan cookie (misalnya, menggunakan CefCookieVisitor)
class CookieVisitor : public CefCookieVisitor {
public:
  CookieVisitor(QString *cookies) : cookies_(cookies) {}
  bool Visit(const CefCookie &cookie, int count, int total, bool &deleteCookie) override {
    *cookies_ += QString::fromStdString(cookie.name.ToString()) + "=" + QString::fromStdString(cookie.value.ToString()) + "; ";
    return true;
  }
private:
  QString *cookies_;
};

QString MainWindow::getCookiesFromAPI() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    QString *cookies = new QString();
    CefCookieManager::GetGlobalManager()->VisitAllCookies(new CookieVisitor(cookies));
    return *cookies;
  }
  return QString();
}

void MainWindow::setProxyFromAPI(const QString &proxy) {
  settings_.setProxy(proxy.toStdString());
  CefRequestContextSettings contextSettings;
  settings_.applyRequestContextSettings(contextSettings);
  CefRefPtr<CefRequestContext> requestContext =
      CefRequestContext::CreateContext(contextSettings, nullptr);
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    browser->GetHost()->SetRequestContext(requestContext);
  }
}

void MainWindow::setSettingsFromAPI(const QString &settingsJSON) {
  QJsonDocument doc = QJsonDocument::fromJson(settingsJSON.toUtf8());
  if (!doc.isNull() && doc.isObject()) {
    QJsonObject obj = doc.object();
    if (obj.contains("canvasSpoofEnabled") && obj["canvasSpoofEnabled"].isBool()) {
      settings_.setCanvasSpoofEnabled(obj["canvasSpoofEnabled"].toBool());
    }
    if (obj.contains("webGlSpoofEnabled") && obj["webGlSpoofEnabled"].isBool()) {
      settings_.setWebGlSpoofEnabled(obj["webGlSpoofEnabled"].toBool());
    }
    if (obj.contains("userAgent") && obj["userAgent"].isString()) {
      settings_.setUserAgent(obj["userAgent"].toString().toStdString());
    }
    // ... Implementasikan pengaturan lainnya dari JSON
  }
}

void MainWindow::on_actionBack_triggered() {
  goBackFromAPI();
}

void MainWindow::on_actionForward_triggered() {
  goForwardFromAPI();
}

void MainWindow::on_actionReload_triggered() {
  reloadFromAPI();
}


void MainWindow::on_actionFindInPage_triggered() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    QString searchText = QInputDialog::getText(this, "Find in Page", "Enter text to find:");
    if (!searchText.isEmpty()) {
      browser->GetHost()->Find(1, CefString(searchText.toStdString()), true, false, false);
    }
  }
}

void MainWindow::on_actionStopFind_triggered() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    browser->GetHost()->StopFinding(true);
  }
}

void MainWindow::on_actionPrint_triggered() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    browser->GetHost()->Print();
  }
}

void MainWindow::on_actionSavePageAs_triggered() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    QString filePath = QFileDialog::getSaveFileName(this, "Save Page As", "", "HTML (*.html);;MHTML (*.mhtml)");
    if (!filePath.isEmpty()) {
      browser->GetHost()->SavePage(filePath.toStdString(), true, CefURLParts());
    }
  }
}

void MainWindow::on_actionViewSource_triggered() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    // Implementasikan dialog atau tab baru untuk menampilkan sumber halaman
  }
}

void MainWindow::on_actionInspectElement_triggered() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    // Implementasikan dialog atau tab baru untuk menampilkan elemen yang diinspeksi
  }
}


void MainWindow::on_actionViewSource_triggered() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    QString html = getHTMLFromAPI();
    QTextEdit *textEdit = new QTextEdit();
    textEdit->setPlainText(html);
    textEdit->setReadOnly(true);
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);
    layout->addWidget(textEdit);
    tabWidget_->addTab(tab, "Source");
    tabWidget_->setCurrentWidget(tab);
  }
}

void MainWindow::on_actionInspectElement_triggered() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    browser->GetHost()->ShowDevTools(CefWindowInfo(), new Browser(settings_), CefBrowserSettings(), nullptr);
  }
}

void MainWindow::on_actionClearCache_triggered() {
  CefRequestContext::GetGlobalContext()->ClearHttpCache();
  QMessageBox::information(this, "Clear Cache", "Cache cleared successfully.");
}

void MainWindow::on_actionClearCookies_triggered() {
  CefCookieManager::GetGlobalManager()->DeleteCookies("", "", nullptr);
  QMessageBox::information(this, "Clear Cookies", "Cookies cleared successfully.");
}

void MainWindow::on_actionClearHistory_triggered() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    browser->GetHost()->ClearHistory();
    QMessageBox::information(this, "Clear History", "History cleared successfully.");
  }
}

void MainWindow::on_actionAbout_triggered() {
  QMessageBox::about(this, "About AntiDetectionBrowser", "AntiDetectionBrowser v1.0\nCreated by [Your Name]");
}


void MainWindow::on_actionSettings_triggered() {
  QSettings settings("AntiDetectionBrowser", "Settings");
  // Implementasikan dialog pengaturan menggunakan QSettings
  // Misalnya, tampilkan dialog dengan opsi untuk mengubah pengaturan
}

void MainWindow::on_actionFullscreen_triggered() {
  if (isFullScreen()) {
    showNormal();
  } else {
    showFullScreen();
  }
}

void MainWindow::on_actionIncognitoMode_triggered() {
  // Implementasikan mode incognito dengan membuat profil browser baru
  // Misalnya, buat direktori cache baru dan gunakan profil browser sementara
}

void MainWindow::on_actionAddBookmark_triggered() {
  if (CefRefPtr<CefBrowser> browser = getCurrentBrowser()) {
    QString url = QString::fromStdString(browser->GetMainFrame()->GetURL());
    QString title = QString::fromStdString(browser->GetMainFrame()->GetTitle());
    // Implementasikan dialog atau mekanisme untuk menambahkan bookmark
    // Misalnya, simpan URL dan judul ke file konfigurasi
  }
}

void MainWindow::on_actionManageBookmarks_triggered() {
  // Implementasikan dialog atau tab baru untuk mengelola bookmark
}

void MainWindow::on_actionDownloadManager_triggered() {
  // Implementasikan dialog atau tab baru untuk mengelola unduhan
}

void MainWindow::on_actionExtensions_triggered() {
  // Implementasikan dialog atau tab baru untuk mengelola ekstensi
}
