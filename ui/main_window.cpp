#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(const Settings &settings, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), settings_(settings) {
  ui->setupUi(this);
  // ... initialize tab widget
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow
