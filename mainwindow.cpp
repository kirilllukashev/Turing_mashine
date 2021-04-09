#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QColor>
#include <QTimer>
#include <QTableWidgetItem>
#include <cmath>
#include <string>
QString symb;
QStringList lst_symb;

int ind = 499;
int quantity = 1e3;

QTimer *timer;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->insertRow(0);
    ui->tableWidget->setColumnCount(quantity);
    for (int i = 0; i < quantity; ++i) {
        QTableWidgetItem *curr = new QTableWidgetItem("-");
        ui->tableWidget->setItem(0, i, curr);

    }
    ui->tableWidget->scrollToItem(ui->tableWidget->item(0, quantity / 2));
    ui->tableWidget->item(0, ind)->setBackgroundColor("#00FF00");

    ui->tableWidget_2->insertRow(0);
    QTableWidgetItem *tables = new QTableWidgetItem();
    tables->setText("q0");
    ui->tableWidget_2->setVerticalHeaderItem(0, tables);
    ui->tableWidget_2->insertColumn(0);
    QTableWidgetItem *tables_2 = new QTableWidgetItem("-");
    lst_symb.append("-");
    ui->tableWidget_2->setHorizontalHeaderItem(0, tables_2);
}

MainWindow::~MainWindow()
{
    delete ui;
    ui->setupUi(this);
}

void MainWindow::on_pushButton_3_clicked()
{
    symb = ui->lineEdit->text();
    QTableWidgetItem *curr = new QTableWidgetItem();
    curr->setText(symb);
    lst_symb.append(symb);
    ui->tableWidget_2->insertColumn(ui->tableWidget_2->columnCount());
    ui->tableWidget_2->setHorizontalHeaderItem(ui->tableWidget_2->columnCount() - 1, curr);
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    symb = ui->lineEdit_2->text();
    QTableWidgetItem *curr = new QTableWidgetItem();
    curr->setText(symb);
    ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
    ui->tableWidget_2->setVerticalHeaderItem(ui->tableWidget_2->rowCount() - 1, curr);
    ui->lineEdit_2->clear();
}

int64_t to_int(std::string str_numb) {
  int64_t number = 0;
  int64_t strlength = str_numb.size();
  for (int i = 0; i < strlength; ++i) {
    number += (str_numb[i] - '0') * std::pow(10, strlength - i - 1);
  }
  return number;
}

int con_numb = 0;

//"#00FF00"
void MainWindow::scroll() {
      bool fl = 0;
      bool fl1 = 0;
      for (int j = 0; j < lst_symb.size(); ++j) {
        if (ui->tableWidget->item(0, ind)->text() == lst_symb[j]) {
          QString curr1 = ui->tableWidget_2->item(con_numb, j)->text();
          int64_t len_curr = curr1.size();
          int k = 0;
          while (k < len_curr){
            if (curr1[k] == '!') {
                fl1 = 1;
                fl = 1;
                timer->stop();
                break;
            }
            if (k != len_curr - 1) {
              if (curr1[k] == '-' and curr1[k + 1] == '>') {
                ++ind;
                k += 2;
                ui->tableWidget->item(0, ind - 1)->setBackgroundColor(Qt::white);
                ui->tableWidget->item(0, ind + 1)->setBackgroundColor(Qt::white);
                ui->tableWidget->item(0, ind)->setBackgroundColor("#00FF00");
                if (k == len_curr) {
                    fl = 1;

                    break;
                }
              }
              if (curr1[k] == '<' and curr1[k + 1] == '-') {
                --ind;
                k += 2;
                ui->tableWidget->item(0, ind - 1)->setBackgroundColor(Qt::white);
                ui->tableWidget->item(0, ind + 1)->setBackgroundColor(Qt::white);
                ui->tableWidget->item(0, ind)->setBackgroundColor("#00FF00");
                if (k == len_curr) {
                    fl = 1;
                    break;
                }
              }
            }
            if (curr1[k] == 'q') {
              con_numb = to_int(curr1.toStdString().substr(k + 1, len_curr - k));
              fl = 1;
              break;
            }
            QString tmp(curr1[k]);
            ui->tableWidget->item(0, ind)->setBackgroundColor("#00FF00");
            ui->tableWidget->item(0, ind - 1)->setBackgroundColor(Qt::white);
            ui->tableWidget->item(0, ind + 1)->setBackgroundColor(Qt::white);
            ui->tableWidget->item(0, ind)->setText(tmp);
            ui->tableWidget->repaint();
            ++k;
          }
          if (fl) break;
        }
        if (fl) break;
      }
      if (fl1) return;
}

void MainWindow::on_pushButton_clicked()
{
    timer = new QTimer();
    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(scroll()));
    timer->start(1000);
}

void MainWindow::on_pushButton_2_clicked()
{
     timer->stop();
}
