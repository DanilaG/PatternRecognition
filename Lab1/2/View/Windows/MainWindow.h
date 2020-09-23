#ifndef LAB1_MAINWINDOW_H
#define LAB1_MAINWINDOW_H

#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  protected:
    bool save_config();
    bool load_config();

    const double analytic_ans = 1 - sqrt(3) / 2.0;

  private slots:
    void on_CountButton_clicked();

  private:
    Ui::MainWindow* ui;
    const QString config_file_name = "conf.json";
};

#endif  // LAB1_MAINWINDOW_H
