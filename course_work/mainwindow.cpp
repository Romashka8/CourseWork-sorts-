#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "sorts_algs.h"
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <cmath>


const int n_end = 10000;
int n_values[11] = {100, 500, 700, 800, 900, 1000, 2000, 3000, 5000, 7000, 10000};
double res[5][11] = {{0.0}};
time_t start, end;


void gather_stat(double *res, int *arr, int head, int sort_num, int index)
{
    if(sort_num == 0)
    {
        auto begin = std::chrono::high_resolution_clock::now();
        insert_sort(arr, head);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> seconds = end - begin;
        res[index] = (seconds.count() * 1000);
        return;
    }
    if(sort_num == 1)
    {
        auto begin = std::chrono::high_resolution_clock::now();
        bubble_sort(arr, head);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> seconds = end - begin;
        res[index] = (seconds.count() * 1000);
        return;
    }
    if(sort_num == 2)
    {
        auto begin = std::chrono::high_resolution_clock::now();
        quick_sort(arr, head);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> seconds = end - begin;
        res[index] = (seconds.count() * 1000);
        return;
    }
    if(sort_num == 3)
    {
        auto begin = std::chrono::high_resolution_clock::now();
        selection_sort(arr, head);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> seconds = end - begin;
        res[index] = (seconds.count() * 1000);
        return;
    }
    if(sort_num == 4)
    {
        auto begin = std::chrono::high_resolution_clock::now();
        heap_sort(arr, head);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> seconds = end - begin;
        res[index] = (seconds.count() * 1000);
        return;
    }
}


void calculate(int* n_values, double *res, int sort_num)
{
    int arr_origin[n_end]; // начальный неупорядоченный массив.
    int arr[n_end]; // сортируемые массивы(длина меняется по ходу программы).
    init_arr(arr_origin, n_end);
    for (int index = 0; index <= 11; index++)
    {
        std::copy_n(arr_origin, n_values[index], arr);
        gather_stat(res, arr, n_values[index], sort_num, index);
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_b_calc_clicked()
{
    if(ui->cb_is->isChecked()) calculate(n_values, res[0], 0);
    else make_zeros(res[0], 11);
    if(ui->cb_bs->isChecked()) calculate(n_values, res[1], 1);
    else make_zeros(res[1], 11);
    if(ui->cb_qs->isChecked()) calculate(n_values, res[2], 2);
    else make_zeros(res[2], 11);
    if(ui->cb_ss->isChecked()) calculate(n_values, res[3], 3);
    else make_zeros(res[3], 11);
    if(ui->cb_hs->isChecked()) calculate(n_values, res[4], 4);
    else make_zeros(res[4], 11);
}


void MainWindow::on_b_save_clicked()
{
    system("rm res.txt");
    std::ofstream out("res.txt");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            out << res[i][j] << " ";
        }
        out << "\n";
     }
     out.close();
}


void MainWindow::on_b_load_clicked()
{
    double num;
    std::fstream in("res.txt");
    if (in)
    {
        for (int i = 0; i < 5; i++)
        {
            for(int j = 0; j < 11; j++)
            {
                in >> num;
                res[i][j] = num;
            }
         }
    }
    in.close();
}


void MainWindow::on_b_show_clicked()
{
    ui->tb_res->clearContents();
    if(ui->cb_is->isChecked())
    {
        for(int index = 0; index < 11; index++)
        {
            ui->tb_res->setItem(index, 0, new QTableWidgetItem(QString::number(res[0][index])));
        }
    }
    if(ui->cb_bs->isChecked())
    {
        for(int index = 0; index < 11; index++)
        {
            ui->tb_res->setItem(index, 1, new QTableWidgetItem(QString::number(res[1][index])));
        }
    }
    if(ui->cb_qs->isChecked())
    {
        for(int index = 0; index < 11; index++)
        {
            ui->tb_res->setItem(index, 2, new QTableWidgetItem(QString::number(res[2][index])));
        }
    }
    if(ui->cb_ss->isChecked())
    {
        for(int index = 0; index < 11; index++)
        {
            ui->tb_res->setItem(index, 3, new QTableWidgetItem(QString::number(res[3][index])));
        }
    }
    if(ui->cb_hs->isChecked())
    {
        for(int index = 0; index < 11; index++)
        {
            ui->tb_res->setItem(index, 4, new QTableWidgetItem(QString::number(res[4][index])));
        }
    }
}


void MainWindow::on_b_plots_clicked()
{
    std::string run = "python3 graphics.py";
    if (ui->cb_is->isChecked()) run.append(" 1");
    else run.append(" 0");
    if (ui->cb_bs->isChecked()) run.append(" 1");
    else run.append(" 0");
    if (ui->cb_qs->isChecked()) run.append(" 1");
    else run.append(" 0");
    if (ui->cb_ss->isChecked()) run.append(" 1");
    else run.append(" 0");
    if (ui->cb_hs->isChecked()) run.append(" 1");
    else run.append(" 0");
    std::cout << run << "\n";
    system("rm fig.png");
    system(run.c_str());
    Dialog win;
    win.setModal(true);
    win.exec();
}
