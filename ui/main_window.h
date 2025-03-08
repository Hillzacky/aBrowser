#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "../browser/browser.h"
#include "../settings/settings.h"
#include <QtWidgets/QMainWindow>
#include <include/cef_app.h>
#include <include/cef_browser.h>

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

private slots:
  void on_actionNewTab_triggered();
  // ... other slots

private:
  Ui::MainWindow *ui;
  Settings settings_;
  // ... tab management
};

#endif // MAIN_WINDOW_H
