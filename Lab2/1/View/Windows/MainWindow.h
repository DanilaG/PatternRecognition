#ifndef LAB1_1_MAINWINDOW_H
#define LAB1_1_MAINWINDOW_H

#include <QtWidgets>
#include <vector>

#include "Handler/Handler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(Handler* init_handler, QWidget* parent = nullptr);
    ~MainWindow();

  protected:
    bool save_config();
    bool load_config();

  private slots:
    void on_ModelingButton_clicked();
    void on_LoadButton_clicked();
    void on_RangeButton_clicked();

  private:
    Handler* handler;
    Ui::MainWindow* ui;
    const QString config_file_name = "conf.json";
};

#endif  // LAB1_1_MAINWINDOW_H
