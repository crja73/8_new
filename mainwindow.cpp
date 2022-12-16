#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

bool ok1 = false;
int row = 0;
bool crask = false;
bool founder = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clear()
{

    ui->label_min->setVisible(0);
    ui->label_max->setVisible(0);
    ui->label_avg->setVisible(0);
}

void MainWindow::on_pushButton_all_clear_clicked()
{
    clear();
    ui->tableWidget->setRowCount(0);
    ui->spinBox->setValue(0);
    ui->lineEdit_found->setText("");
}

void MainWindow::on_pushButton_rundom_clicked()
{
    for(qint64 i = 0; i < row; i++)
    {
    ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(QRandomGenerator::global()->bounded(1, 100000))));
    clear();
    }
}

void MainWindow::problems(int *mas)
{
    if (ui->spinBox->value() == 0)
    {
        QMessageBox::warning(this, "ОШИБКА", "массив должен быть заполнен!", QMessageBox::Ok);
        ok1 = false;
        //clear();
    }
    else
    {
        for (int i = 0; i < row; i++)
        {
            if (ui->tableWidget->item(i, 0) == nullptr)
            {
                //clear();
                ui->tableWidget->setItem(i, 0, new QTableWidgetItem(""));
                ok1 = false;
                QMessageBox::warning(this, "ОШИБКА", "заполни ВСЕ ячейки");

                break;
            }
            int box = ui->tableWidget->item(i, 0)->text().toInt(&ok1);
            if (!ok1)
            {
                //clear();
                QMessageBox::warning(this, "ОШИБКА", "неприятное значение.. меняй");
                break;
            }
            else
            {
                ok1 = true;
                if (mas != NULL)
                {
                    mas[i] = box;
                }
            }
        }
    }
}

void MainWindow::sinch(int *mas)
{
    for (int i = 0; i < row; i++)
    {
        QString numberText = QString::number(mas[i]);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(numberText));
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    //QString text = item -> text();
    row = arg1;
    ui->tableWidget->setRowCount(row);
    if (crask)
    {

        ui->tableWidget->setItem(row-1, 0, new QTableWidgetItem(""));
        //item -> setBackground(Qt:: red);
        ui->tableWidget->setRowCount(row-1);
        ui->tableWidget->setRowCount(row);
    }
    if (row > 200)
    {
        QMessageBox::warning(this, "ОШИБКА", "слишком много");
    }
}

void MainWindow::quickSort(int left, int right, int *mas)
{
    int pivot;
    int l_hold = left;
    int r_hold = right;
    pivot = mas[left];
    while (left < right) // пока границы не сомкнутся
    {
      while ((mas[right] >= pivot) && (left < right))
        right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
      if (left != right) // если границы не сомкнулись
      {
        mas[left] = mas[right]; // перемещаем элемент [right] на место разрешающего
        left++; // сдвигаем левую границу вправо
      }
      while ((mas[left] <= pivot) && (left < right))
        left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
      if (left != right) // если границы не сомкнулись
      {
        mas[right] = mas[left]; // перемещаем элемент [left] на место [right]
        right--; // сдвигаем правую границу влево
      }
    }
    mas[left] = pivot; // ставим разрешающий элемент на место
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
      quickSort(left, pivot - 1, mas);
    if (right > pivot)
        quickSort(pivot + 1, right, mas);
}

void MainWindow::izmen()
{
    if(crask)
    {
    ui->lineEdit_2->setText("");
    ui->lable_searchCount->setText("");
    for(int i = 0; i <row; i++)
    {
        ui->tableWidget->item(i,0)->setBackground(Qt::white);
    }
    crask = false;

    }
}

bool MainWindow::correct(int size, int *mas)
{
    bool ok7 = false;
    for(int i = 0; i < size - 1; i++)
    {
        if (mas[i] > mas[i+1])
        {
            ok7 = true;
            break;
        }
    }
    if(ok7)
        return true;
    else
        return false;
}

void MainWindow::shuffle(int size, int *mas)
{
    for (int i = 0; i < size; i++)
    {
        int a = mas[i];
        int ran = QRandomGenerator::global()->bounded(0, size-1);
        int b = mas[ran];
        mas[i] = b;
        mas[ran] = a;
    }
}


void MainWindow::on_pushButton_monkey_clicked()
{
    ui->label_min->setVisible(1);
    ui->label_max->setVisible(1);
    ui->label_avg->setVisible(1);
    if(row > 10)
    {
        //clear();

        QMessageBox::warning(this,"Внимание!", " до 10", QMessageBox::Ok);
    }
    else
    {
        int* mas_number = new int[row];
        problems(mas_number);
        if(ok1)
        {
        while (correct(row, mas_number))
                shuffle(row, mas_number);
        sinch(mas_number);
        }
        delete [] mas_number;
        mas_number = NULL;
    }



}


void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    izmen();
    QString text = item -> text();

    bool ok;
    text.toInt(&ok);
    for (int i = 0; i < row; i++)
    {
        if(!ok)
        {
            item -> setBackground(Qt:: red);
            clear();
        }
        else
        {
            if(!founder)
                item -> setBackground(Qt:: white);
                clear();
        }
    }
}

void MainWindow::on_pushButton_result_clicked()
{
    int* mas_number = new int[row];
    problems(mas_number);
    if(ok1)
    {
        int minNumber = 1e9;
        int maxNumber = -1;
        int avrNumber = 0;

        for(int i = 0; i < row; i ++)
        {
            if(mas_number[i] < minNumber)
            {
                minNumber = mas_number[i];
            }
            if(mas_number[i] > maxNumber)
            {
                maxNumber = mas_number[i];
            }
        avrNumber += mas_number[i];

        }

        ui->label_min->show();
        ui->label_max->show();
        ui->label_avg->show();
    }
    delete [] mas_number;
    mas_number = NULL;
}

void MainWindow::on_pushButton_rashectka_clicked()
{
    ui->label_min->setVisible(1);
    ui->label_max->setVisible(1);
    ui->label_avg->setVisible(1);
    int* mas_number = new int[row];
    problems(mas_number);
    if(ok1)
    {
        if(row >= 400000)
        {
            QMessageBox::information(this, "внимание", "3-5 секунд");
        }
        int shag = row;
        bool flagUA = true;
        int vrem;
        while(shag > 1 or flagUA)
        {
            if(shag > 1)
            {
                shag = floor(shag / 1.247);
            }
                flagUA = false;
                int i = 0;
                while(i + shag < row)
                {
                    if(mas_number[i] > mas_number[i+shag])
                    {
                        vrem = mas_number[i];
                        mas_number[i] = mas_number[i+shag];
                        mas_number[i+shag] = vrem;
                        flagUA = true;
                    }
                    i++;
                }
            }
       sinch(mas_number);
    }


    delete [] mas_number;
    mas_number = NULL;
}



void MainWindow::on_pushButton_gnom_clicked()
{
    ui->label_min->setVisible(1);
    ui->label_max->setVisible(1);
    ui->label_avg->setVisible(1);
    int* mas_number = new int[row];
    if(row > 100000)
    {
        QMessageBox::warning(this,"ошибка", "большое число");
    }
    else
    {
    problems(mas_number);
    if(ok1)
    {
        if(row > 50000)
        {
            QMessageBox::information(this, "внимание", "3-5 секунд");
        }
        int i = 0;
        int j = 0;
        int vrem;
        int vernis = 0;
        bool na_meste = true;
        while (i < row)
        {
            if(i==0 or mas_number[i-1] <= mas_number[i])
            {
                if(!na_meste)
                {
                    na_meste = true;
                    i = vernis;
                }

                i++;

            }

            else
            {
                if(na_meste)
                {
                    vernis = i;
                }
                na_meste = false;
                j = i - 1;
                vrem = mas_number[i];
                mas_number[i] = mas_number[j];
                mas_number[j] = vrem;
                i = j;

            }
        }
        sinch(mas_number);


    }

    }

    delete [] mas_number;
    mas_number = NULL;


}


void MainWindow::on_pushButton_bubble_clicked()
{
    int* mas_number = new int[row];
    if(row > 50000)
    {
        QMessageBox::warning(this,"ошибка", "большие числа");
    }
    else
    {
    if(row > 25000)
    {
        QMessageBox::information(this, "внимание", " 5-7 секунд");
    }
    problems(mas_number);
    if(ok1)
    {
        int i = 0;
        int j;
        int vrem;
        while(i < row-1)
        {
            j = i+1;
            while(j < row)
            {
                if(mas_number[i] > mas_number[j])
                {
                    vrem = mas_number[i];
                    mas_number[i] = mas_number[j];
                    mas_number[j] = vrem;
                }
            j = j+1;
            }
        i = i+1;
        }
        sinch(mas_number);
    }
    }

    delete [] mas_number;
    mas_number = NULL;


}


void MainWindow::on_pushButton_quick_clicked()
{
    ui->label_min->setVisible(1);
    ui->label_max->setVisible(1);
    ui->label_avg->setVisible(1);
    int* mas_number = new int[row];
    problems(mas_number);

    if(ok1)
    {
        if(row >= 400000)
        {
            QMessageBox::information(this, "внимание", " 3-5 секунд");
        }
        quickSort(0, row-1, mas_number);
        sinch(mas_number);
    }

    delete [] mas_number;
    mas_number = NULL;
}


void MainWindow::on_pushButton_clicked()
{
    izmen();
    int* mas_number = new int[row];
    problems(mas_number);
    if(ok1)
    {
    bool ok89;
    int kolvo = 0;
    bool sovpad = true;
    int found = ui->lineEdit_found->text().toInt(&ok89);
    founder = true;
    QString otvet ="";
    int index[200];
    for(int i = 0; i < row-1; i++)
    {
        if(mas_number[i] > mas_number[i+1])
        {
            sovpad = false;
            break;
        }
    }
    if(sovpad) //бинарный поиск
    {
        if(ok89)
        {
            bool da = false;
            int count = 0;
            int del = floor(row/2);
            int kray = del;
            while(!da)
            {
                if(mas_number[del] == found)
                {
                    da = true;
                    for(int i = del; i >-1; i--)
                    {
                        if(mas_number[i] == found)
                        {
                            kray = i;
                        }
                        else
                        {
                            break;
                        }
                    }
                    for(int i = kray; i < del; i++)
                    {
                        index[kolvo] = i+1;
                        kolvo++;
                        ui->tableWidget->item(i,0)->setBackground(Qt::green);
                    }

                    for(int i = del; i < row; i++)
                    {
                        if(mas_number[i] == found)
                        {
                            index[kolvo] = i+1;
                            kolvo++;
                            ui->tableWidget->item(i,0)->setBackground(Qt::green);
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                else if(mas_number[del] > found)
                {
                    del = floor(del/2);
                }
                else if(mas_number[del] < found)
                {
                    if(count < 2)
                    {
                        del ++;
                    }
                    else
                    {
                        del += floor((row-del)/2);
                        count++;
                    }
                }
            }
        }
        else
        {
            QMessageBox::warning(this, "ошибка", "только  цифры");
            founder = false;
        }
    }
    else
    {
        if(ok89)
        {
            for(int i = 0; i < row; i++)
            {
                if(mas_number[i] == found)
                {
                    index[kolvo] = i+1;
                    kolvo++;
                    ui->tableWidget->item(i,0)->setBackground(Qt::green);
                }
            }
        }
        else
        {
            QMessageBox::warning(this, "ошибка", "вводите в поиск только цифры");
            founder = false;
        }
     }
    if(ok89)
    {
    if(kolvo > 0)
    {
        crask = true;
        for(int i = 0; i < kolvo; i ++)
        {
            otvet += QString::number(index[i]) + " ";
            ui->lable_searchCount->setNum(kolvo);
            ui->lineEdit_2->setText(otvet);
        }
    }
    else
    {
        clear();
        QMessageBox::warning(this, "", "Такого числа нет");
    }
    }
    founder = false;
    }

    delete [] mas_number;
    mas_number = NULL;
}


void MainWindow::on_pushButton_deleteDublikat_clicked()
{
    int* mas_number = new int[row];
    problems(mas_number);
    if(ok1)
    {
    bool sovpad = true;
    for(int i = 0; i < row-1; i++)
    {
        if(mas_number[i] > mas_number[i+1])
        {
            sovpad = false;
            break;
        }
    }
    if(sovpad)
    {
        int rows = 1;
        int point = mas_number[0];
        mas_number[0] = point;
        for(int i = 1; i < row; i++)
        {
            if(point == mas_number[i])
                continue;
            else
            {
                point = mas_number[i];
                mas_number[rows] = point;
                rows++;
            }
        }
        ui->spinBox->setValue(rows);
        for (int i = 0; i < rows; i++)
        {
            QString numberText = QString::number(mas_number[i]);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(numberText));
        }
    }
    else
    {
        QMessageBox::warning(this, "ошибка", "отсортируйте массив");
    }

    }

    delete [] mas_number;
    mas_number = NULL;
}


void MainWindow::on_pushButton_avg_clicked()
{
    int* mas_number = new int[row];
    problems(mas_number);
    if(ok1)
    {
        int minNumber = 1e9;
        int maxNumber = -1;
        qint64 avrNumber = 0;

        for(int i = 0; i < row; i ++)
        {
            if(mas_number[i] < minNumber)
            {
                minNumber = mas_number[i];
            }
            if(mas_number[i] > maxNumber)
            {
                maxNumber = mas_number[i];
            }
        avrNumber += mas_number[i];

        }

        ui->label_min->show();
        ui->label_max->show();
        ui->label_avg->show();

        QString srAvg = QString::number(avrNumber/row);

            ui->label_avg->setText(srAvg);
            ui->label_max->setNum(maxNumber);
            ui->label_min->setNum(minNumber);
    }
    ui->label_min->setVisible(1);
    ui->label_max->setVisible(1);
    ui->label_avg->setVisible(1);

    delete [] mas_number;
    mas_number = NULL;
}

