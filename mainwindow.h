#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTableWidgetItem>
#include <QMessageBox>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void readMassive(double *mas, int *size, bool *error); //функция для считывания массива
    void writeMassive(double *mas, int size);

private slots:
    void clear();

    void problems(int *mas);

    void sinch(int *mas);

    void quickSort(int left, int right, int *mas);

    void izmen();

    bool correct(int size, int *mas);

    void shuffle(int size, int *mas);

    void on_pushButton_all_clear_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_rundom_clicked();

    void on_pushButton_monkey_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_pushButton_result_clicked();

    void on_pushButton_rashectka_clicked();

    void on_pushButton_gnom_clicked();

    void on_pushButton_bubble_clicked();

    void on_pushButton_quick_clicked();

    void on_pushButton_clicked();

    void on_pushButton_deleteDublikat_clicked();

    void on_pushButton_avg_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
