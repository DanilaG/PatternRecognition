#include "MainWindow.h"

#include <QFile>
#include <QJsonObject>
#include <algorithm>
#include <iostream>

#include "Logic/Logic.h"
#include "ui_MainWindow.h"

template <class T>
static inline QVector<T> v2qv(const std::vector<T>& v) {
    QVector<T> ans(v.size());
    std::copy(v.begin(), v.end(), ans.begin());
    return ans;
}

static void draw_plot(const std::vector<double>& data,
                      QCustomPlot* plot,
                      const QColor& pen_color = Qt::blue) {
    QVector<double> x(data.size());
    QVector<double> y = v2qv(data);
    for (unsigned int i = 0; i < x.size(); i++) { x[i] = i; }

    plot->addGraph();
    plot->graph(plot->graphCount() - 1)->setPen(QPen(pen_color));
    plot->xAxis->setRange(0, x.size());
    plot->yAxis->setRange(0, *std::max_element(data.begin(), data.end()));
    plot->graph(plot->graphCount() - 1)->setData(x, y);
}

static void draw_plot(const Gist& data,
                      QCustomPlot* plot,
                      const QColor& pen_color = Qt::blue) {
    QVector<double> x(2 * (data.y.size() + 1));
    QVector<double> y(2 * (data.y.size() + 1));

    const double h = (data.end - data.start) / data.y.size();
    for (unsigned int i = 0; i <= data.y.size(); i++) {
        x[2 * i] = i * h + data.start;
        x[2 * i + 1] = i * h + data.start + 0.000001;
    }
    y.first() = y.last() = 0;
    for (unsigned int i = 0; i < data.y.size(); i++) {
        y[2 * i + 1] = data.y[i];
        y[2 * i + 2] = data.y[i];
    }

    plot->addGraph();
    plot->graph(plot->graphCount() - 1)->setPen(QPen(pen_color));
    plot->graph(plot->graphCount() - 1)
        ->setBrush(QBrush(
            QColor(pen_color.red(), pen_color.green(), pen_color.blue(), 20)));
    plot->xAxis->setRange(data.start, data.end);
    plot->yAxis->setRange(0, *std::max_element(data.y.begin(), data.y.end()));
    plot->graph(plot->graphCount() - 1)->setData(x, y);
}

MainWindow::MainWindow(Handler* init_handler, QWidget* parent)
    : QMainWindow(parent), handler(init_handler), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    auto distribution_series = handler->distribution_series();
    ui->DSTableWidget->setColumnCount(distribution_series.size());
    ui->DSTableWidget->horizontalHeader()->hide();
    for (unsigned int c = 0; c < distribution_series.size(); c++) {
        ui->DSTableWidget->setItem(0,
                                   c,
                                   new QTableWidgetItem(QString::number(c)));
        ui->DSTableWidget->setItem(
            1,
            c,
            new QTableWidgetItem(QString::number(distribution_series[c])));
    }
    ui->DSTableWidget->resizeColumnsToContents();

    draw_plot(distribution_series, ui->DPolygonPlot);
    ui->DPolygonPlot->replot();
    draw_plot(handler->distribution_function(), ui->DFunctionPlot);
    ui->DFunctionPlot->replot();

    ui->AverAnalyticLable->setNum(handler->count_analytic_average());
    ui->VarAnalyticLable->setNum(handler->count_analytic_variance());
    ui->AsymAnalyticLable->setNum(handler->count_analytic_asymmetry());
    ui->ExcAnalyticLable->setNum(handler->count_analytic_excess());

    load_config();
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::save_config() {
    QFile config(config_file_name);
    if (!config.open(QIODevice::WriteOnly)) {
        std::cerr << "Failed to save configs!" << std::endl;
        return false;
    }

    QJsonObject json({{"Rang1", ui->RangeSpinBox1->value()},
                      {"Rang2", ui->RangeSpinBox2->value()},
                      {"Mod", ui->ModelingSpinBox->value()},
                      {"NumberColum", ui->NumberColumsSpinBox->value()}});
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
    ui->RangeSpinBox1->setValue(json["Rang1"].toInt());
    ui->RangeSpinBox2->setValue(json["Rang2"].toInt());
    ui->ModelingSpinBox->setValue(json["Mod"].toInt());
    ui->NumberColumsSpinBox->setValue(json["NumberColum"].toInt());

    config.close();
    return true;
}

void MainWindow::on_ModelingButton_clicked() {
    std::string file_name =
        QFileDialog::getSaveFileName(this, tr("Save File.")).toStdString();

    unsigned int number_attempt = ui->ModelingSpinBox->value();

    if (!handler->generate_file(number_attempt, file_name)) {
        std::cerr << __func__ << ": Wrong file!" << std::endl;
    }

    save_config();
}

void MainWindow::on_LoadButton_clicked() {
    std::string file_name =
        QFileDialog::getOpenFileName(this, tr("Open File.")).toStdString();
    if (!handler->load_file(file_name)) {
        std::cerr << __func__ << ": Wrong file!" << std::endl;
    }

    ui->AverPracticalLable->setNum(handler->count_real_average());
    ui->AverMisclosureLable->setNum(handler->count_analytic_average() -
                                    handler->count_real_average());
    ui->VarPracticalLable->setNum(handler->count_real_variance());
    ui->VarMisclosureLable->setNum(handler->count_analytic_variance() -
                                   handler->count_real_variance());
    ui->AsymPracticalLable->setNum(handler->count_real_asymmetry());
    ui->AsymMisclosureLable->setNum(handler->count_analytic_asymmetry() -
                                    handler->count_real_asymmetry());
    ui->ExcPracticalLable->setNum(handler->count_real_excess());
    ui->ExcMisclosureLable->setNum(handler->count_analytic_excess() -
                                   handler->count_real_excess());

    ui->DPolygonPlot->clearGraphs();
    ui->DFunctionPlot->clearGraphs();
    draw_plot(handler->real_gist(ui->NumberColumsSpinBox->value()),
              ui->DPolygonPlot,
              Qt::green);
    draw_plot(handler->distribution_series(), ui->DPolygonPlot);
    draw_plot(handler->real_distribution_series(), ui->DPolygonPlot, Qt::red);
    draw_plot(handler->distribution_function(), ui->DFunctionPlot);
    draw_plot(handler->real_distribution_function(),
              ui->DFunctionPlot,
              Qt::red);
    ui->DPolygonPlot->replot();
    ui->DFunctionPlot->replot();

    save_config();
}

void MainWindow::on_RangeButton_clicked() {
    unsigned int val1 = ui->RangeSpinBox1->value();
    unsigned int val2 = ui->RangeSpinBox2->value();

    double probability =
        handler->in_area(std::min(val1, val2), std::max(val1, val2));

    ui->RangeAnsLabel->setNum(probability);

    save_config();
}
