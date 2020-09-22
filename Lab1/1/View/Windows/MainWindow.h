#ifndef LAB1_1_MAINWINDOW_H
#define LAB1_1_MAINWINDOW_H

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

    const double analytic_Unique_ans = 0.504;
    const double analytic_Pair_ans = 0.432;
    const double analytic_DoublePair_ans = 0.027;
    const double analytic_Triplet_ans = 0.036;

  private slots:
    void on_CountButton_clicked();

  private:
    Ui::MainWindow* ui;
    const QString config_file_name = "conf.json";
};

#endif  // LAB1_1_MAINWINDOW_H
