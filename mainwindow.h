#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <qstring.h>
#include <QString>

namespace Ui {
class MainWindow;
}

class database :public QMainWindow
{
    QString data_input;
    QString data_output;
    int code_input;
    int code_resu;
    int start;
    QString resu;

};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


void input_error_show();

    //----------------------------------------------进制转换部分
public:
    QButtonGroup input;
    QButtonGroup output;
    QString data_input;
    QString data_output;
    int code_input;
    int code_resu;
    int start;
    QString resu;
public slots:
    //进制转换信号槽
       void on_lineEdit_input_textChanged(const QString &arg1);
       void print_resu();
        void code_change();

    //-----------------------------------------------长度转换部分
public:
    QButtonGroup input_length;
    QButtonGroup output_length;
    int code_length_input;
    int code_length_resu;
    double length_mid_input;
    double length_mid_output;
    QString resu_length_ENGtoGONG;
    QString resu_length_GONGtoENG;
public slots:
    void code_test_lengthENG();
    void code_test_lengthGONG();
    void trans_length_ENGtoGong(const QString &arg2);
    void trans_length_GongtoENG(const QString &arg3);
    //------------------------------------------------面积转换部分
public:
    int code_area_input;
    int code_area_resu;
    double area_mid_input;
    double area_mid_output;
    QString resu_area_ENGtoGONG;
    QString resu_area_GONGtoENG;
public slots:
    void code_test_areaENG();
    void code_test_areaGONG();
    void trans_area_ENGtoGong(const QString &arg2);
    void trans_area_GongtoENG(const QString &arg3);
    //------------------------------------------------体积转换部分
public:

    int code_vol_input;
    int code_vol_resu;
    double vol_mid_input;
    double vol_mid_output;
    QString resu_vol_ENGtoGONG;
    QString resu_vol_GONGtoENG;
public slots:
    void code_test_volENG();
    void code_test_volGONG();
    void trans_vol_ENGtoGong(const QString &arg2);
    void trans_vol_GongtoENG(const QString &arg3);
    //------------------------------------------------重量转换部分
public:
    int code_wei_input;
    int code_wei_resu;
    double weight_mid_input;
    double weight_mid_output;
    QString resu_wei_ENGtoGONG;
    QString resu_wei_GONGtoENG;
public slots:
    void code_test_weiENG();
    void code_test_weiGONG();
    void trans_wei_ENGtoGong(const QString &arg2);
    void trans_wei_GongtoENG(const QString &arg3);
    //------------------------------------------------温度转换部分
public:
    int code_temp_input;
    int code_temp_resu;
   // double weight_mid_input;
    //double weight_mid_output;
    QString resu_temp_CtoF;
    QString resu_temp_FtoC;
public slots:
    void code_test_tempCel();
    void code_test_tempFah();
    void trans_temp_CtoF(const QString &arg2);
    void trans_temp_FtoC(const QString &arg3);
    //------------------------------------------------货币转换部分
public:
    double exange_rate_USDtoCNY=6.6933;
    double exange_rate_CNYtoUSD=0.1494;
    int code_money_input;
    int code_money_resu;
   // double weight_mid_input;
    //double weight_mid_output;
    QString resu_money_USDtoCNY;
    QString resu_money_CNYtoUSD;
public slots:
    void code_test_moneyUSD();
    void code_test_moneyCNY();
    void trans_money_USDtoCNY(const QString &arg2);
    void trans_money_CNYtoUSD(const QString &arg3);
    //------------------------------------------------时区转换部分
public:

public slots:
    void on_btnGetTime_clicked();
    void code_test_timeread();


private:
    Ui::MainWindow *ui;
    void system_init();
};

#endif // MAINWINDOW_H
