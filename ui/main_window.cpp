#include "main_window.h"
#include "ui_main_window.h"
#include "../browser/browser.h"
#include <QtWidgets/QMessageBox>
#include <include/cef_app.h>
#include <include/cef_browser.h>

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

CefRefPtr<CefBrowser> MainWindow::getCurrentBrowser() {
  if (tabWidget_->count() > 0) {
    // Implementasikan logika untuk mendapatkan CefBrowser dari tab saat ini
    // Misalnya, simpan pointer CefBrowser di setiap tab
    // ...
  }
  return nullptr;
}
