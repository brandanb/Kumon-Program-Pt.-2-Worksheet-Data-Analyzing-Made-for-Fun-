#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QCoreApplication>
#include <QtCore>
#include <QFile>
#include <QDebug>
#include <sstream>
#include <QMessageBox>
#include "dialog.h"
#include "dialog2.h"

using namespace std;

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

QString MainWindow::deleteduplicates(QString a[22], int n)
{

int i, j, k;

    for(i=0;i<n;i++)
    {
       for(j=i+1;j<n;)
       {
          if(a[j]==a[i])
          {
             for(k=j;k<n;k++)
             {
                 a[k]=a[k+1];
             }
          n--;
          }
          else
             j++;
       }
    }

    qDebug() << " ";

    for(i=0;i<n;i++)
        qDebug() << i << ": " << a[i] << ", ";

    return a[i];

}

int MainWindow::sort(QString* a, int n, QString na)
{
    int yes = 1, i;
    int counter=0;
    for (i = 0; i < n; ++i)
    {
       if (a[i] == na)
       {
                counter++;
                qDebug() << "Found a duplicate of " << a[i];
                yes = 0;
       }
    }
    if (yes)
    {
    qDebug() << "No duplicates";
    }

    qDebug() << counter;
    return counter;
}

int MainWindow::sortsub(QString* a, int n, QString na, QString* subl, QString subb)
{
    int yes = 1, i;
    int counter=0;
    for (i = 0; i < n; ++i)
    {
       if (a[i] == na)
       {
                if (subl[i] == subb)
                {
                    counter++;
                    qDebug() << "Found a duplicate of " << subl[i];
                    yes = 0;
               }
       }
    }
    if (yes == 1)
    {
    qDebug() << "No duplicates";
    }

    qDebug() << counter;
    return counter;
}

void MainWindow::on_pushButton_clicked()
{
    QString line, name;
    double realaverage, rounded;
    double averagel = 0;
    QString *reallist;
    reallist =new QString[10000];
    QString *listof;
    QStringList listt;
    listof =new QString[10000];
    int x=0;

    name=ui->lineEdit->text();

    QFile file("C:/Program Files (x86)/BrandanApplications/Kumon Classwork Recording/KumonWrite.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        do
        {
        line = stream.readLine();
        listof[x] = line;
        // stream >> name >> month >> day >> year >> subject >> level >> apages >> total >> one >> two >> three >> four >> five >> six >> seven >> eight >> nine >> ten;
        // qDebug() << name << month << day << year << subject << level << apages << total << one << two << three << four << five << six << seven << eight << nine << ten;

        x++;
        } while(!line.isNull());
    }

    for (int q=x-2; q>=0; q--) //for (int q=x; q>=0; q--)
    {
        QString Parsing;
        Parsing = listof[q];
        qDebug() << "Hi" << Parsing;
        listt = Parsing.split(" ");

        qDebug() << "Here: " << listt[1] << endl; //"name" in string

        reallist[q] = listt[0];
        if (listt[0]==name)
        {
            averagel=averagel+listt[7].toInt();
            qDebug() << averagel;
        }

    }

    int Counter = sort(reallist,x,name);
    qDebug() << Counter;

    realaverage=averagel/Counter;
    qDebug() << realaverage;
    rounded = floor(100*realaverage + .05) / 100;
    QString averagestring = QString::number(rounded);

    QMessageBox::information(this,"Average Grade of Students Classwork","Average Grade of Students Classwork: " + averagestring);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString line, name;
    QString *reallist;
    reallist =new QString[10000];
    QString *listof;
    QStringList listt;
    listof =new QString[10000];
    int x=0;

    name=ui->lineEdit->text();

    QFile file("C:/Program Files (x86)/BrandanApplications/Kumon Classwork Recording/KumonWrite.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        do
        {
        line = stream.readLine();
        listof[x] = line;
        x++;
        } while(!line.isNull());
    }

    for (int q=x-2; q>=0; q--) //for (int q=x; q>=0; q--)
    {
        QString Parsing;
        Parsing = listof[q];
        listt = Parsing.split(" ");
        reallist[q] = listt[0];
    }

    int Counter = sort(reallist,x,name);

    QString CounterString = QString::number(Counter);

    qDebug() << Counter;
    QMessageBox::information(this,"Total Classworks Completed","Total Classwork Completed: " + CounterString);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString line, name, sub1, sub2;
    QString *reallist;
    QString *sublist;
    reallist =new QString[10000];
    sublist =new QString[10000];
    QString *listof;
    QStringList listt;
    listof =new QString[10000];
    int x=0;

    name=ui->lineEdit->text();


    QFile file("C:/Program Files (x86)/BrandanApplications/Kumon Classwork Recording/KumonWrite.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        do
        {
        line = stream.readLine();
        listof[x] = line;
        x++;
        } while(!line.isNull());
    }

    for (int q=x-2; q>=0; q--) //for (int q=x; q>=0; q--)
    {
        QString Parsing;
        Parsing = listof[q];
        listt = Parsing.split(" ");
        reallist[q] = listt[0];
        sublist[q] = listt[4];
    }
    sub1 = "Math";
    int Counter1 = sortsub(reallist,x,name,sublist,sub1); //add variable sub

    sub2 = "Reading";
    int Counter2 = sortsub(reallist,x,name,sublist,sub2);


    QString CounterString1 = QString::number(Counter1);
    QString CounterString2 = QString::number(Counter2);

    qDebug() << Counter1;
    qDebug() << Counter2;
    QMessageBox::information(this,"Total Classworks Completed Per Subject","Total Math Classwork: " + CounterString1 + "\n" + "Total Reading Classwork: " + CounterString2 + "\n");
}

void MainWindow::on_pushButton_4_clicked()
{
    double realmathavg, realreadingavg;
    double averagemath = 0;
    double averagereading = 0;
    QString line, name, sub1, sub2;
    QString *reallist;
    QString *sublist;
    reallist =new QString[10000];
    sublist =new QString[10000];
    QString *listof;
    QStringList listt;
    listof =new QString[10000];
    int x=0;

    name=ui->lineEdit->text();


    QFile file("C:/Program Files (x86)/BrandanApplications/Kumon Classwork Recording/KumonWrite.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        do
        {
        line = stream.readLine();
        listof[x] = line;
        x++;
        } while(!line.isNull());
    }

    for (int q=x-2; q>=0; q--) //for (int q=x; q>=0; q--)
    {
        QString Parsing;
        Parsing = listof[q];
        listt = Parsing.split(" ");
        reallist[q] = listt[0];
        sublist[q] = listt[4];
        if (listt[0]==name && listt[4]=="Math")
        {
            averagemath=averagemath+listt[7].toInt();
            qDebug() << "Math Avg: " << averagemath;
        }

        if (listt[0]==name && listt[4]=="Reading")
        {
            averagereading=averagereading+listt[7].toInt();
            qDebug() << "Read Avg: " << averagereading;
        }
    }


    sub1 = "Math";
    int Counter1 = sortsub(reallist,x,name,sublist,sub1); //add variable sub
    realmathavg = averagemath/Counter1;

    sub2 = "Reading";
    int Counter2 = sortsub(reallist,x,name,sublist,sub2);
    realreadingavg = averagereading/Counter2;

    double rounded1 = floor(100*realmathavg + .05) / 100;
    QString averagemathstring = QString::number(rounded1);
    qDebug() << "Counter1: " << Counter1;
    if (Counter1 == 0)
    {
        averagemathstring = "None Completed";
    }

    double rounded2 = floor(100*realreadingavg + .05) / 100;
    QString averagereadingstring = QString::number(rounded2);
    qDebug() << "Counter2: " << Counter2;
    if (Counter2 == 0)
    {
        averagereadingstring = "None Completed";
    }

    qDebug() << rounded1;
    qDebug() << rounded2;
    QMessageBox::information(this,"Subject Based Averages","Math Classwork Average: " + averagemathstring + "\n" + "Reading Classwork Average: " + averagereadingstring + "\n");
}

void MainWindow::on_pushButton_6_clicked()
{
    int element1=0;
    int element2=0;
    int element3=0;
    int element4=0;
    int element5=0;
    int element6=0;
    int element7=0;
    int element8=0;
    int element9=0;
    int element10=0;
    int element11=0;
    int element12=0;
    int element13=0;
    int element14=0;
    int element15=0;
    int element16=0;
    int element17=0;
    int element18=0;
    int element19=0;
    int element20=0;
    int element21=0;
    int element22=0;

    int element1b=0;
    int element2b=0;
    int element3b=0;
    int element4b=0;
    int element5b=0;
    int element6b=0;
    int element7b=0;
    int element8b=0;
    int element9b=0;
    int element10b=0;
    int element11b=0;
    int element12b=0;
    int element13b=0;
    int element14b=0;
    int element15b=0;
    int element16b=0;
    int element17b=0;
    int element18b=0;
    int element19b=0;
    int element20b=0;
    int element21b=0;
    int element22b=0;
    int element23b=0;
    int element24b=0;

        QString line, name;
        QString *reallist;

        QString levellist[10000];
        QString levellist2[10000];
\
        reallist =new QString[10000];

        QString *listof;
        QStringList listt;
        listof =new QString[10000];
        int x=0;
        int i=0;
        int b=0;

        name=ui->lineEdit->text();


        QFile file("C:/Program Files (x86)/BrandanApplications/Kumon Classwork Recording/KumonWrite.txt");

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);

            do
            {
            line = stream.readLine();
            listof[x] = line;
            x++;
            } while(!line.isNull());
        }



        for (int q=x-2; q>=0; q--) //for (int q=x; q>=0; q--)
        {
            QString Parsing;
            Parsing = listof[q];
            listt = Parsing.split(" ");
            reallist[q] = listt[0];



            if (listt[0]==name && listt[4]=="Math")
            {
                    if (listt[5] != "")
                    {
                    levellist[i] = listt[5];
                    qDebug() << levellist[i] << ", ";
                    }

                    if(listt[5]=="7A")
                    {
                        element1++;
                    }
                    if(listt[5]=="6A")
                    {
                        element2++;
                    }
                    if(listt[5]=="5A")
                    {
                        element3++;
                    }
                    if(listt[5]=="4A")
                    {
                        element4++;
                    }
                    if(listt[5]=="3A")
                    {
                        element5++;
                    }
                    if(listt[5]=="2A")
                    {
                        element6++;
                    }
                    if(listt[5]=="A")
                    {
                        element7++;
                    }
                    if(listt[5]=="B")
                    {
                        element8++;
                    }
                    if(listt[5]=="C")
                    {
                        element9++;
                    }
                    if(listt[5]=="D")
                    {
                        element10++;
                    }
                    if(listt[5]=="E")
                    {
                        element11++;
                    }
                    if(listt[5]=="F")
                    {
                        element12++;
                    }
                    if(listt[5]=="G")
                    {
                        element13++;
                    }
                    if(listt[5]=="H")
                    {
                        element14++;
                    }
                    if(listt[5]=="I")
                    {
                        element15++;
                    }
                    if(listt[5]=="J")
                    {
                        element16++;
                    }
                    if(listt[5]=="K")
                    {
                        element17++;
                    }
                    if(listt[5]=="L")
                    {
                        element18++;
                    }
                    if(listt[5]=="M")
                    {
                        element19++;
                    }
                    if(listt[5]=="N")
                    {
                        element20++;
                    }
                    if(listt[5]=="O")
                    {
                        element21++;
                    }
                    if(listt[5]=="X")
                    {
                        element22++;
                    }

                    i++;
            }

            if(listt[0]==name && listt[4]=="Reading")
            {
                if (listt[5] != "")
                {
                    levellist2[i] = listt[5];
                }

                if(listt[5]=="7A")
                {
                    element1b++;
                }
                if(listt[5]=="6A")
                {
                    element2b++;
                }
                if(listt[5]=="5A")
                {
                    element3b++;
                }
                if(listt[5]=="4A")
                {
                    element4b++;
                }
                if(listt[5]=="3A")
                {
                    element5b++;
                }
                if(listt[5]=="2A")
                {
                    element6b++;
                }
                if(listt[5]=="AI")
                {
                    element7b++;
                }
                if(listt[5]=="AII")
                {
                    element8b++;
                }
                if(listt[5]=="BI")
                {
                    element9b++;
                }
                if(listt[5]=="BII")
                {
                    element10b++;
                }
                if(listt[5]=="CI")
                {
                    element11b++;
                }
                if(listt[5]=="CII")
                {
                    element12b++;
                }
                if(listt[5]=="DI")
                {
                    element13b++;
                }
                if(listt[5]=="DII")
                {
                    element14b++;
                }
                if(listt[5]=="EI")
                {
                    element15b++;
                }
                if(listt[5]=="EII")
                {
                    element16b++;
                }
                if(listt[5]=="FI")
                {
                    element17b++;
                }
                if(listt[5]=="FII")
                {
                    element18b++;
                }
                if(listt[5]=="G")
                {
                    element19b++;
                }
                if(listt[5]=="H")
                {
                    element20b++;
                }
                if(listt[5]=="I")
                {
                    element21b++;
                }
                if(listt[5]=="J")
                {
                    element22b++;
                }
                if(listt[5]=="K")
                {
                    element23b++;
                }
                if(listt[5]=="L")
                {
                    element24b++;
                }


                b++;
            }

        }

      deleteduplicates(levellist, i);
      qDebug() << "\n";



       QString one = QString::number(element1);
       QString two = QString::number(element2);
       QString three = QString::number(element3);
       QString four = QString::number(element4);
       QString five = QString::number(element5);
       QString six = QString::number(element6);
       QString seven = QString::number(element7);
       QString eight = QString::number(element8);
       QString nine = QString::number(element9);
       QString ten = QString::number(element10);
       QString eleven = QString::number(element11);
       QString twelve = QString::number(element12);
       QString thirteen = QString::number(element13);
       QString fourteen = QString::number(element14);
       QString fifteen = QString::number(element15);
       QString sixteen = QString::number(element16);
       QString seventeen = QString::number(element17);
       QString eighteen = QString::number(element18);
       QString nineteen = QString::number(element19);
       QString twenty = QString::number(element20);
       QString twentyone = QString::number(element21);
       QString twentytwo = QString::number(element22);



      deleteduplicates(levellist2,b);


      QString oneb = QString::number(element1b);
      QString twob = QString::number(element2b);
      QString threeb = QString::number(element3b);
      QString fourb = QString::number(element4b);
      QString fiveb = QString::number(element5b);
      QString sixb = QString::number(element6b);
      QString sevenb = QString::number(element7b);
      QString eightb = QString::number(element8b);
      QString nineb = QString::number(element9b);
      QString tenb = QString::number(element10b);
      QString elevenb = QString::number(element11b);
      QString twelveb = QString::number(element12b);
      QString thirteenb = QString::number(element13b);
      QString fourteenb = QString::number(element14b);
      QString fifteenb = QString::number(element15b);
      QString sixteenb = QString::number(element16b);
      QString seventeenb = QString::number(element17b);
      QString eighteenb = QString::number(element18b);
      QString nineteenb = QString::number(element19b);
      QString twentyb = QString::number(element20b);
      QString twentyoneb = QString::number(element21b);
      QString twentytwob = QString::number(element22b);
      QString twentythreeb = QString::number(element23b);
      QString twentyfourb = QString::number(element24b);


     Dialog object;
     object.setModal(true);
     object.SetLabelText("7A : " + one + "\n"
                         + "6A : " + two + "\n"
                         + "5A : " + three + "\n"
                         + "4A : " + four + "\n"
                         + "3A : " + five + "\n"
                         + "2A : " + six + "\n"
                         + "A : " + seven + "\n"
                         + "B : " + eight + "\n"
                         + "C : " + nine + "\n"
                         + "D : " + ten + "\n"
                         + "E : " + eleven + "\n"
                         + "F : " + twelve + "\n"
                         + "G : " + thirteen + "\n"
                         + "H : " + fourteen + "\n"
                         + "I : " + fifteen + "\n"
                         + "J : " + sixteen + "\n"
                         + "K : " + seventeen + "\n"
                         + "L : " + eighteen + "\n"
                         + "M : " + nineteen + "\n"
                         + "N : " + twenty + "\n"
                         + "O : " + twentyone + "\n"
                         + "X : " + twentytwo + "\n",

                         "7A : " + oneb + "\n"
                         + "6A : " + twob + "\n"
                         + "5A : " + threeb + "\n"
                         + "4A : " + fourb + "\n"
                         + "3A : " + fiveb + "\n"
                         + "2A : " + sixb + "\n"
                         + "AI : " + sevenb + "\n"
                         + "AII : " + eightb + "\n"
                         + "BI : " + nineb + "\n"
                         + "BII : " + tenb + "\n"
                         + "CI : " + elevenb + "\n"
                         + "CII : " + twelveb + "\n"
                         + "DI : " + thirteenb + "\n"
                         + "DII : " + fourteenb + "\n"
                         + "EI : " + fifteenb + "\n"
                         + "EII : " + sixteenb + "\n"
                         + "FI : " + seventeenb + "\n"
                         + "FII : " + eighteenb + "\n"
                         + "G : " + nineteenb + "\n"
                         + "H : " + twentyb + "\n"
                         + "I : " + twentyoneb + "\n"
                         + "J : " + twentytwob + "\n"
                         + "K : " + twentythreeb + "\n"
                         + "L : " + twentyfourb + "\n"
                     );

     object.exec();

}


void MainWindow::on_pushButton_5_clicked()
{


    QString line, name;
    QString *reallist;

    QString levellist[10000];
    QString levellist2[10000];
\
    reallist =new QString[10000];

    QString *listof;
    QStringList listt;
    listof =new QString[10000];
    int x=0;
    int i=0;
    int b=0;

    int element1=0;
    int element2=0;
    int element3=0;
    int element4=0;
    int element5=0;
    int element6=0;
    int element7=0;
    int element8=0;
    int element9=0;
    int element10=0;
    int element11=0;
    int element12=0;
    int element13=0;
    int element14=0;
    int element15=0;
    int element16=0;
    int element17=0;
    int element18=0;
    int element19=0;
    int element20=0;
    int element21=0;
    int element22=0;

    int element1b=0;
    int element2b=0;
    int element3b=0;
    int element4b=0;
    int element5b=0;
    int element6b=0;
    int element7b=0;
    int element8b=0;
    int element9b=0;
    int element10b=0;
    int element11b=0;
    int element12b=0;
    int element13b=0;
    int element14b=0;
    int element15b=0;
    int element16b=0;
    int element17b=0;
    int element18b=0;
    int element19b=0;
    int element20b=0;
    int element21b=0;
    int element22b=0;
    int element23b=0;
    int element24b=0;


    name=ui->lineEdit->text();


    QFile file("C:/Program Files (x86)/BrandanApplications/Kumon Classwork Recording/KumonWrite.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        do
        {
        line = stream.readLine();
        listof[x] = line;
        x++;
        } while(!line.isNull());
    }

    int o=x;



    for (int q=x-2; q>=0; q--) //for (int q=x; q>=0; q--)
    {
        QString Parsing;
        Parsing = listof[q];
        listt = Parsing.split(" ");
        reallist[q] = listt[0];



        if (listt[0]==name && listt[4]=="Math")
        {
                if (listt[5] != "")
                {
                levellist[i] = listt[5];
                qDebug() << levellist[i] << ", ";
                }

                if(listt[5]=="7A")
                {
                    element1++;
                }
                if(listt[5]=="6A")
                {
                    element2++;
                }
                if(listt[5]=="5A")
                {
                    element3++;
                }
                if(listt[5]=="4A")
                {
                    element4++;
                }
                if(listt[5]=="3A")
                {
                    element5++;
                }
                if(listt[5]=="2A")
                {
                    element6++;
                }
                if(listt[5]=="A")
                {
                    element7++;
                }
                if(listt[5]=="B")
                {
                    element8++;
                }
                if(listt[5]=="C")
                {
                    element9++;
                }
                if(listt[5]=="D")
                {
                    element10++;
                }
                if(listt[5]=="E")
                {
                    element11++;
                }
                if(listt[5]=="F")
                {
                    element12++;
                }
                if(listt[5]=="G")
                {
                    element13++;
                }
                if(listt[5]=="H")
                {
                    element14++;
                }
                if(listt[5]=="I")
                {
                    element15++;
                }
                if(listt[5]=="J")
                {
                    element16++;
                }
                if(listt[5]=="K")
                {
                    element17++;
                }
                if(listt[5]=="L")
                {
                    element18++;
                }
                if(listt[5]=="M")
                {
                    element19++;
                }
                if(listt[5]=="N")
                {
                    element20++;
                }
                if(listt[5]=="O")
                {
                    element21++;
                }
                if(listt[5]=="X")
                {
                    element22++;
                }

                i++;
        }

        if(listt[0]==name && listt[4]=="Reading")
        {
            if (listt[5] != "")
            {
                levellist2[i] = listt[5];
            }

            if(listt[5]=="7A")
            {
                element1b++;
            }
            if(listt[5]=="6A")
            {
                element2b++;
            }
            if(listt[5]=="5A")
            {
                element3b++;
            }
            if(listt[5]=="4A")
            {
                element4b++;
            }
            if(listt[5]=="3A")
            {
                element5b++;
            }
            if(listt[5]=="2A")
            {
                element6b++;
            }
            if(listt[5]=="AI")
            {
                element7b++;
            }
            if(listt[5]=="AII")
            {
                element8b++;
            }
            if(listt[5]=="BI")
            {
                element9b++;
            }
            if(listt[5]=="BII")
            {
                element10b++;
            }
            if(listt[5]=="CI")
            {
                element11b++;
            }
            if(listt[5]=="CII")
            {
                element12b++;
            }
            if(listt[5]=="DI")
            {
                element13b++;
            }
            if(listt[5]=="DII")
            {
                element14b++;
            }
            if(listt[5]=="EI")
            {
                element15b++;
            }
            if(listt[5]=="EII")
            {
                element16b++;
            }
            if(listt[5]=="FI")
            {
                element17b++;
            }
            if(listt[5]=="FII")
            {
                element18b++;
            }
            if(listt[5]=="G")
            {
                element19b++;
            }
            if(listt[5]=="H")
            {
                element20b++;
            }
            if(listt[5]=="I")
            {
                element21b++;
            }
            if(listt[5]=="J")
            {
                element22b++;
            }
            if(listt[5]=="K")
            {
                element23b++;
            }
            if(listt[5]=="L")
            {
                element24b++;
            }

            b++;
        }

    }

  deleteduplicates(levellist, i);
  qDebug() << "\n";


   QString one = QString::number(element1);
   QString two = QString::number(element2);
   QString three = QString::number(element3);
   QString four = QString::number(element4);
   QString five = QString::number(element5);
   QString six = QString::number(element6);
   QString seven = QString::number(element7);
   QString eight = QString::number(element8);
   QString nine = QString::number(element9);
   QString ten = QString::number(element10);
   QString eleven = QString::number(element11);
   QString twelve = QString::number(element12);
   QString thirteen = QString::number(element13);
   QString fourteen = QString::number(element14);
   QString fifteen = QString::number(element15);
   QString sixteen = QString::number(element16);
   QString seventeen = QString::number(element17);
   QString eighteen = QString::number(element18);
   QString nineteen = QString::number(element19);
   QString twenty = QString::number(element20);
   QString twentyone = QString::number(element21);
   QString twentytwo = QString::number(element22);


  deleteduplicates(levellist2,b);

  QString oneb = QString::number(element1b);
  QString twob = QString::number(element2b);
  QString threeb = QString::number(element3b);
  QString fourb = QString::number(element4b);
  QString fiveb = QString::number(element5b);
  QString sixb = QString::number(element6b);
  QString sevenb = QString::number(element7b);
  QString eightb = QString::number(element8b);
  QString nineb = QString::number(element9b);
  QString tenb = QString::number(element10b);
  QString elevenb = QString::number(element11b);
  QString twelveb = QString::number(element12b);
  QString thirteenb = QString::number(element13b);
  QString fourteenb = QString::number(element14b);
  QString fifteenb = QString::number(element15b);
  QString sixteenb = QString::number(element16b);
  QString seventeenb = QString::number(element17b);
  QString eighteenb = QString::number(element18b);
  QString nineteenb = QString::number(element19b);
  QString twentyb = QString::number(element20b);
  QString twentyoneb = QString::number(element21b);
  QString twentytwob = QString::number(element22b);
  QString twentythreeb = QString::number(element23b);
  QString twentyfourb = QString::number(element24b);



 x=o;
 i=0;
 b=0;


 int avgm1=0;
 int avgm2=0;
 int avgm3=0;
 int avgm4=0;
 int avgm5=0;
 int avgm6=0;
 int avgm7=0;
 int avgm8=0;
 int avgm9=0;
 int avgm10=0;
 int avgm11=0;
 int avgm12=0;
 int avgm13=0;
 int avgm14=0;
 int avgm15=0;
 int avgm16=0;
 int avgm17=0;
 int avgm18=0;
 int avgm19=0;
 int avgm20=0;
 int avgm21=0;
 int avgm22=0;

 int avgr1=0;
 int avgr2=0;
 int avgr3=0;
 int avgr4=0;
 int avgr5=0;
 int avgr6=0;
 int avgr7=0;
 int avgr8=0;
 int avgr9=0;
 int avgr10=0;
 int avgr11=0;
 int avgr12=0;
 int avgr13=0;
 int avgr14=0;
 int avgr15=0;
 int avgr16=0;
 int avgr17=0;
 int avgr18=0;
 int avgr19=0;
 int avgr20=0;
 int avgr21=0;
 int avgr22=0;
 int avgr23=0;
 int avgr24=0;





 for (int q=x-2; q>=0; q--) //for (int q=x; q>=0; q--)
 {
     QString Parsing;
     Parsing = listof[q];
     listt = Parsing.split(" ");
     reallist[q] = listt[0];


 qDebug() << "hi";
     if (listt[0]==name && listt[4]=="Math")
     {

             if (listt[5] == "7A")
             {
                 avgm1=avgm1+listt[7].toInt();
                 qDebug() << "avgm1= " << avgm1;
             }

             if (listt[5] == "6A")
             {
                 avgm2=avgm2+listt[7].toInt();
             }

             if (listt[5] == "5A")
             {
                 avgm3=avgm3+listt[7].toInt();
             }

             if (listt[5] == "4A")
             {
                 avgm4=avgm4+listt[7].toInt();
             }

             if (listt[5] == "3A")
             {
                 avgm5=avgm5+listt[7].toInt();
             }

             if (listt[5] == "2A")
             {
                 avgm6=avgm6+listt[7].toInt();
             }

             if (listt[5] == "A")
             {
                 avgm7=avgm7+listt[7].toInt();
             }

             if (listt[5] == "B")
             {
                 avgm8=avgm8+listt[7].toInt();
             }

             if (listt[5] == "C")
             {
                 avgm9=avgm9+listt[7].toInt();
             }

             if (listt[5] == "D")
             {
                 avgm10=avgm10+listt[7].toInt();
             }

             if (listt[5] == "E")
             {
                 avgm11=avgm11+listt[7].toInt();
             }

             if (listt[5] == "F")
             {
                 avgm12=avgm12+listt[7].toInt();
             }

             if (listt[5] == "G")
             {
                 avgm13=avgm13+listt[7].toInt();
             }

             if (listt[5] == "H")
             {
                 avgm14=avgm14+listt[7].toInt();
             }

             if (listt[5] == "I")
             {
                 avgm15=avgm15+listt[7].toInt();
             }

             if (listt[5] == "J")
             {
                 avgm16=avgm16+listt[7].toInt();
             }

             if (listt[5] == "K")
             {
                 avgm17=avgm17+listt[7].toInt();
             }

             if (listt[5] == "L")
             {
                 avgm18=avgm18+listt[7].toInt();
             }

             if (listt[5] == "M")
             {
                 avgm19=avgm19+listt[7].toInt();
             }

             if (listt[5] == "N")
             {
                 avgm20=avgm20+listt[7].toInt();
             }

             if (listt[5] == "O")
             {
                 avgm21=avgm21+listt[7].toInt();
             }

             if (listt[5] == "X")
             {
                 avgm22=avgm22+listt[7].toInt();
             }

     }

     if(listt[0]==name && listt[4]=="Reading")
     {
         if (listt[5] == "7A")
         {
             avgr1=avgr1+listt[7].toInt();
         }

         if (listt[5] == "6A")
         {
             avgr2=avgr2+listt[7].toInt();
         }

         if (listt[5] == "5A")
         {
             avgr3=avgr3+listt[7].toInt();
         }

         if (listt[5] == "4A")
         {
             avgr4=avgr4+listt[7].toInt();
         }

         if (listt[5] == "3A")
         {
             avgr5=avgr5+listt[7].toInt();
         }

         if (listt[5] == "2A")
         {
             avgr6=avgr6+listt[7].toInt();
         }

         if (listt[5] == "AI")
         {
             avgr7=avgr7+listt[7].toInt();
         }

         if (listt[5] == "AII")
         {
             avgr8=avgr8+listt[7].toInt();
         }

         if (listt[5] == "BI")
         {
             avgr9=avgr9+listt[7].toInt();
         }

         if (listt[5] == "BII")
         {
             avgr10=avgr10+listt[7].toInt();
         }

         if (listt[5] == "CI")
         {
             avgr11=avgr11+listt[7].toInt();
         }

         if (listt[5] == "CII")
         {
             avgr12=avgr12+listt[7].toInt();
         }

         if (listt[5] == "DI")
         {
             avgr13=avgr13+listt[7].toInt();
         }

         if (listt[5] == "DII")
         {
             avgr14=avgr14+listt[7].toInt();
         }

         if (listt[5] == "EI")
         {
             avgr15=avgr15+listt[7].toInt();
         }

         if (listt[5] == "EII")
         {
             avgr16=avgr16+listt[7].toInt();
         }

         if (listt[5] == "FI")
         {
             avgr17=avgr17+listt[7].toInt();
         }

         if (listt[5] == "FII")
         {
             avgr18=avgr18+listt[7].toInt();
         }

         if (listt[5] == "G")
         {
             avgr19=avgr19+listt[7].toInt();
         }

         if (listt[5] == "H")
         {
             avgr20=avgr20+listt[7].toInt();
         }

         if (listt[5] == "I")
         {
             avgr21=avgr21+listt[7].toInt();
         }

         if (listt[5] == "J")
         {
             avgr22=avgr22+listt[7].toInt();
         }

         if (listt[5] == "K")
         {
             avgr23=avgr23+listt[7].toInt();
         }

         if(listt[5] == "L")
         {
            avgr24=avgr24+listt[7].toInt();
         }
     }

 }

 double m1 = element1;
 double m2 = element2;
 double m3 = element3;
 double m4 = element4;
 double m5 = element5;
 double m6 = element6;
 double m7 = element7;
 double m8 = element8;
 double m9 = element9;
 double m10 = element10;
 double m11 = element11;
 double m12 = element12;
 double m13 = element13;
 double m14 = element14;
 double m15 = element15;
 double m16 = element16;
 double m17 = element17;
 double m18 = element18;
 double m19 = element19;
 double m20 = element20;
 double m21 = element21;
 double m22 = element22;

 double r1 = element1b;
 double r2 = element2b;
 double r3 = element3b;
 double r4 = element4b;
 double r5 = element5b;
 double r6 = element6b;
 double r7 = element7b;
 double r8 = element8b;
 double r9 = element9b;
 double r10 = element10b;
 double r11 = element11b;
 double r12 = element12b;
 double r13 = element13b;
 double r14 = element14b;
 double r15 = element15b;
 double r16 = element16b;
 double r17 = element17b;
 double r18 = element18b;
 double r19 = element19b;
 double r20 = element20b;
 double r21 = element21b;
 double r22 = element22b;
 double r23 = element23b;
 double r24 = element24b;

 double mm1 = avgm1;
 double mm2 = avgm2;
 double mm3 = avgm3;
 double mm4 = avgm4;
 double mm5 = avgm5;
 double mm6 = avgm6;
 double mm7 = avgm7;
 double mm8 = avgm8;
 double mm9 = avgm9;
 double mm10 = avgm10;
 double mm11 = avgm11;
 double mm12 = avgm12;
 double mm13 = avgm13;
 double mm14 = avgm14;
 double mm15 = avgm15;
 double mm16 = avgm16;
 double mm17 = avgm17;
 double mm18 = avgm18;
 double mm19 = avgm19;
 double mm20 = avgm20;
 double mm21 = avgm21;
 double mm22 = avgm22;

 double rr1 = avgr1;
 qDebug() << "rr1: " << rr1;
 double rr2 = avgr2;
 double rr3 = avgr3;
 double rr4 = avgr4;
 double rr5 = avgr5;
 double rr6 = avgr6;
 double rr7 = avgr7;
 double rr8 = avgr8;
 double rr9 = avgr9;
 double rr10 = avgr10;
 double rr11 = avgr11;
 double rr12 = avgr12;
 double rr13 = avgr13;
 double rr14 = avgr14;
 double rr15 = avgr15;
 double rr16 = avgr16;
 double rr17 = avgr17;
 double rr18 = avgr18;
 double rr19 = avgr19;
 double rr20 = avgr20;
 double rr21 = avgr21;
 double rr22 = avgr22;
 double rr23 = avgr23;
 double rr24 = avgr24;

 double realaveragem1=mm1/m1;
 double realaveragem2=mm2/m2;
 double realaveragem3=mm3/m3;
 double realaveragem4=mm4/m4;
 double realaveragem5=mm5/m5;
 double realaveragem6=mm6/m6;
 double realaveragem7=mm7/m7;
 double realaveragem8=mm8/m8;
 double realaveragem9=mm9/m9;
 double realaveragem10=mm10/m10;
 double realaveragem11=mm11/m11;
 double realaveragem12=mm12/m12;
 double realaveragem13=mm13/m13;
 double realaveragem14=mm14/m14;
 double realaveragem15=mm15/m15;
 double realaveragem16=mm16/m16;
 double realaveragem17=mm17/m17;
 double realaveragem18=mm18/m18;
 double realaveragem19=mm19/m19;
 double realaveragem20=mm20/m20;
 double realaveragem21=mm21/m21;
 double realaveragem22=mm22/m22;
 qDebug() << "mm22= " << mm22;
 qDebug() << "m22= " << m22;
 qDebug() << "realaveragem22= " << realaveragem22;

 double realaverager1=rr1/r1;
 double realaverager2=rr2/r2;
 double realaverager3=rr3/r3;
 double realaverager4=rr4/r4;
 double realaverager5=rr5/r5;
 double realaverager6=rr6/r6;
 double realaverager7=rr7/r7;
 double realaverager8=rr8/r8;
 double realaverager9=rr9/r9;
 double realaverager10=rr10/r10;
 double realaverager11=rr11/r11;
 double realaverager12=rr12/r12;
 double realaverager13=rr13/r13;
 double realaverager14=rr14/r14;
 double realaverager15=rr15/r15;
 double realaverager16=rr16/r16;
 double realaverager17=rr17/r17;
 double realaverager18=rr18/r18;
 double realaverager19=rr19/r19;
 double realaverager20=rr20/r20;
 double realaverager21=rr21/r21;
 double realaverager22=rr22/r22;
 double realaverager23=rr23/r23;
 double realaverager24=rr24/r24;




 double roundedm1 = floor(100*realaveragem1 + .05) / 100;
 qDebug() << "Hi: " << roundedm1;
 double roundedm2 = floor(100*realaveragem2 + .05) / 100;
 double roundedm3 = floor(100*realaveragem3 + .05) / 100;
 double roundedm4 = floor(100*realaveragem4 + .05) / 100;
 double roundedm5 = floor(100*realaveragem5 + .05) / 100;
 double roundedm6 = floor(100*realaveragem6 + .05) / 100;
 double roundedm7 = floor(100*realaveragem7 + .05) / 100;
 double roundedm8 = floor(100*realaveragem8 + .05) / 100;
 double roundedm9 = floor(100*realaveragem9 + .05) / 100;
 double roundedm10 = floor(100*realaveragem10 + .05) / 100;
 double roundedm11 = floor(100*realaveragem11 + .05) / 100;
 double roundedm12 = floor(100*realaveragem12 + .05) / 100;
 double roundedm13 = floor(100*realaveragem13 + .05) / 100;
 double roundedm14 = floor(100*realaveragem14 + .05) / 100;
 double roundedm15 = floor(100*realaveragem15 + .05) / 100;
 double roundedm16 = floor(100*realaveragem16 + .05) / 100;
 double roundedm17 = floor(100*realaveragem17 + .05) / 100;
 double roundedm18 = floor(100*realaveragem18 + .05) / 100;
 double roundedm19 = floor(100*realaveragem19 + .05) / 100;
 double roundedm20 = floor(100*realaveragem20 + .05) / 100;
 double roundedm21 = floor(100*realaveragem21 + .05) / 100;
 double roundedm22 = floor(100*realaveragem22 + .05) / 100;

 double roundedr1 = floor(100*realaverager1 + .05) / 100;
 double roundedr2 = floor(100*realaverager2 + .05) / 100;
 double roundedr3 = floor(100*realaverager3 + .05) / 100;
 double roundedr4 = floor(100*realaverager4 + .05) / 100;
 double roundedr5 = floor(100*realaverager5 + .05) / 100;
 double roundedr6 = floor(100*realaverager6 + .05) / 100;
 double roundedr7 = floor(100*realaverager7 + .05) / 100;
 double roundedr8 = floor(100*realaverager8 + .05) / 100;
 double roundedr9 = floor(100*realaverager9 + .05) / 100;
 double roundedr10 = floor(100*realaverager10 + .05) / 100;
 double roundedr11 = floor(100*realaverager11 + .05) / 100;
 double roundedr12 = floor(100*realaverager12 + .05) / 100;
 double roundedr13 = floor(100*realaverager13 + .05) / 100;
 double roundedr14 = floor(100*realaverager14 + .05) / 100;
 double roundedr15 = floor(100*realaverager15 + .05) / 100;
 double roundedr16 = floor(100*realaverager16 + .05) / 100;
 double roundedr17 = floor(100*realaverager17 + .05) / 100;
 double roundedr18 = floor(100*realaverager18 + .05) / 100;
 double roundedr19 = floor(100*realaverager19 + .05) / 100;
 double roundedr20 = floor(100*realaverager20 + .05) / 100;
 double roundedr21 = floor(100*realaverager21 + .05) / 100;
 double roundedr22 = floor(100*realaverager22 + .05) / 100;
 double roundedr23 = floor(100*realaverager23 + .05) / 100;
 double roundedr24 = floor(100*realaverager24 + .05) / 100;

 QString onem = QString::number(roundedm1);
 QString twom = QString::number(roundedm2);
 QString threem = QString::number(roundedm3);
 QString fourm = QString::number(roundedm4);
 QString fivem = QString::number(roundedm5);
 QString sixm = QString::number(roundedm6);
 QString sevenm = QString::number(roundedm7);
 QString eightm = QString::number(roundedm8);
 QString ninem = QString::number(roundedm9);
 QString tenm = QString::number(roundedm10);
 QString elevenm = QString::number(roundedm11);
 QString twelvem = QString::number(roundedm12);
 QString thirteenm = QString::number(roundedm13);
 QString fourteenm = QString::number(roundedm14);
 QString fifteenm = QString::number(roundedm15);
 QString sixteenm = QString::number(roundedm16);
 QString seventeenm = QString::number(roundedm17);
 QString eighteenm = QString::number(roundedm18);
 QString nineteenm = QString::number(roundedm19);
 QString twentym = QString::number(roundedm20);
 QString twentyonem = QString::number(roundedm21);
 QString twentytwom = QString::number(roundedm22);

 QString oner = QString::number(roundedr1);
 QString twor = QString::number(roundedr2);
 QString threer = QString::number(roundedr3);
 QString fourr = QString::number(roundedr4);
 QString fiver = QString::number(roundedr5);
 QString sixr = QString::number(roundedr6);
 QString sevenr = QString::number(roundedr7);
 QString eightr = QString::number(roundedr8);
 QString niner = QString::number(roundedr9);
 QString tenr = QString::number(roundedr10);
 QString elevenr = QString::number(roundedr11);
 QString twelver = QString::number(roundedr12);
 QString thirteenr = QString::number(roundedr13);
 QString fourteenr = QString::number(roundedr14);
 QString fifteenr = QString::number(roundedr15);
 QString sixteenr = QString::number(roundedr16);
 QString seventeenr = QString::number(roundedr17);
 QString eighteenr = QString::number(roundedr18);
 QString nineteenr = QString::number(roundedr19);
 QString twentyr = QString::number(roundedr20);
 QString twentyoner = QString::number(roundedr21);
 QString twentytwor = QString::number(roundedr22);
 QString twentythreer = QString::number(roundedr23);
 QString twentyfourr = QString::number(roundedr24);

 Dialog2 object1;
 object1.setModal(true);
 object1.SetLabelText("7A : " + onem + "\n"
                     + "6A : " + twom + "\n"
                     + "5A : " + threem + "\n"
                     + "4A : " + fourm + "\n"
                     + "3A : " + fivem + "\n"
                     + "2A : " + sixm + "\n"
                     + "A : " + sevenm + "\n"
                     + "B : " + eightm + "\n"
                     + "C : " + ninem + "\n"
                     + "D : " + tenm + "\n"
                     + "E : " + elevenm + "\n"
                     + "F : " + twelvem + "\n"
                     + "G : " + thirteenm + "\n"
                     + "H : " + fourteenm + "\n"
                     + "I : " + fifteenm + "\n"
                     + "J : " + sixteenm + "\n"
                     + "K : " + seventeenm + "\n"
                     + "L : " + eighteenm + "\n"
                     + "M : " + nineteenm + "\n"
                     + "N : " + twentym + "\n"
                     + "O : " + twentyonem + "\n"
                     + "X : " + twentytwom + "\n",

                     "7A : " + oner + "\n"
                     + "6A : " + twor + "\n"
                     + "5A : " + threer + "\n"
                     + "4A : " + fourr + "\n"
                     + "3A : " + fiver + "\n"
                     + "2A : " + sixr + "\n"
                     + "AI : " + sevenr + "\n"
                     + "AII : " + eightr + "\n"
                     + "BI : " + niner + "\n"
                     + "BII : " + tenr + "\n"
                     + "CI : " + elevenr + "\n"
                     + "CII : " + twelver + "\n"
                     + "DI : " + thirteenr + "\n"
                     + "DII : " + fourteenr + "\n"
                     + "EI : " + fifteenr + "\n"
                     + "EII : " + sixteenr + "\n"
                     + "FI : " + seventeenr + "\n"
                     + "FII : " + eighteenr + "\n"
                     + "G : " + nineteenr + "\n"
                     + "H : " + twentyr + "\n"
                     + "I : " + twentyoner + "\n"
                     + "J : " + twentytwor + "\n"
                     + "K : " + twentythreer + "\n"
                     + "L : " + twentyfourr + "\n"
                 );
  object1.exec();
}
