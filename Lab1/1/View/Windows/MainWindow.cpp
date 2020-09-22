#include "MainWindow.h"

#include <QFile>
#include <QJsonObject>
#include <iostream>

#include "Logic/ProbabilityCounter.h"
#include "ui_MainWindow.h"

#define COUNT_RESULT(TYPE, NUMBER, CAPACITY, PROB, COUNT)                    \
    {                                                                        \
        unsigned int count = ui->Attempt##NUMBER##SpinBox->value();          \
        double prob = TYPE##ProbabilityCounter(CAPACITY).count(count);       \
        COUNT += count;                                                      \
        PROB += prob * count;                                                \
        ui->TYPE##Ans##NUMBER##Label->setNum(prob);                          \
        ui->TYPE##Misc##NUMBER##Label->setNum(analytic_##TYPE##_ans - prob); \
    }

#define SET_RESULT(TYPE, CAPACITY)                                \
    {                                                             \
        double prop = 0;                                          \
        long int counter = 0;                                     \
        COUNT_RESULT(TYPE, 1, CAPACITY, prop, counter);           \
        COUNT_RESULT(TYPE, 2, CAPACITY, prop, counter);           \
        COUNT_RESULT(TYPE, 3, CAPACITY, prop, counter);           \
        double ans = prop / counter;                              \
        ui->TYPE##AnsLabel->setNum(ans);                          \
        ui->TYPE##MiscLabel->setNum(analytic_##TYPE##_ans - ans); \
    }

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->UniqueAnalyticAnsLabel->setNum(analytic_Unique_ans);
    ui->PairAnalyticAnsLabel->setNum(analytic_Pair_ans);
    ui->DoublePairAnalyticAnsLabel->setNum(analytic_DoublePair_ans);
    ui->TripletAnalyticAnsLabel->setNum(analytic_Triplet_ans);

    load_config();
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::save_config() {
    QFile config(config_file_name);
    if (!config.open(QIODevice::WriteOnly)) {
        std::cerr << "Failed to save configs!" << std::endl;
        return false;
    }

    QJsonObject json({{"Attempt1", ui->Attempt1SpinBox->value()},
                      {"Attempt2", ui->Attempt2SpinBox->value()},
                      {"Attempt3", ui->Attempt3SpinBox->value()}});
    config.write(QJsonDocument(json).toJson(QJsonDocument::Indented));

    config.close();
    return true;
}

bool MainWindow::load_config() {
    QFile config(config_file_name);
    if (!config.open(QIODevice::ReadOnly)) {
        std::cerr << "Failed to load configs!" << std::endl;
        return false;
    }

    QJsonObject json = QJsonDocument::fromJson(config.readAll()).object();
    ui->Attempt1SpinBox->setValue(json["Attempt1"].toInt());
    ui->Attempt2SpinBox->setValue(json["Attempt2"].toInt());
    ui->Attempt3SpinBox->setValue(json["Attempt3"].toInt());

    config.close();
    return true;
}

void MainWindow::on_CountButton_clicked() {
    const unsigned int digit_capacity = 4;
    const unsigned int number_attempts = ui->Attempt1SpinBox->value();

    SET_RESULT(Unique, digit_capacity);
    SET_RESULT(Pair, digit_capacity);
    SET_RESULT(DoublePair, digit_capacity);
    SET_RESULT(Triplet, digit_capacity);

    save_config();
}
