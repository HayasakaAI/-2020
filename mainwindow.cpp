#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QTimeZone>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //ui->centralWidget->resize(800,600);

    //void status();
    //setFixedSize(this->width(), this->height());
    system_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::system_init(){




    //BINARY---INIT
    connect(ui->comboBox_binary_input_3, SIGNAL(currentIndexChanged(int)), this, SLOT( code_change()));
    connect(ui->comboBox_binary_output_3, SIGNAL(currentIndexChanged(int)), this, SLOT(code_change()));

    connect(ui->pushButton_binary,&QPushButton::released,
            [=]()
    {
        ui->lineEdit_binary_output_3->setText(resu);

    }
    );


    //初始化输入框，仅支持整数及double类型输入
    QIntValidator* aIntValidator = new QIntValidator;
    QDoubleValidator* aDoubleValidator = new QDoubleValidator;
    ui->lineEdit_binary_input_3 ->setValidator(aIntValidator);
    ui->lineEdit_binary_output_3 ->setValidator(aIntValidator);
    ui->lineEdit_length_ENG->setValidator(aDoubleValidator);
    ui->lineEdit_length_GONG ->setValidator(aDoubleValidator);
    ui->lineEdit_area_ENG ->setValidator(aDoubleValidator);
    ui->lineEdit_area_GONG ->setValidator(aDoubleValidator);
    ui->lineEdit_volume_ENG ->setValidator(aDoubleValidator);
    ui->lineEdit_volume_GONG ->setValidator(aDoubleValidator);
    ui->lineEdit_weight_ENG ->setValidator(aDoubleValidator);
    ui->lineEdit_weight_GONG ->setValidator(aDoubleValidator);
    ui->lineEdit_temp_Celsius ->setValidator(aDoubleValidator);
    ui->lineEdit_temp_Farenheit ->setValidator(aDoubleValidator);
    ui->lineEdit_money_CNY ->setValidator(aDoubleValidator);
    ui->lineEdit_money_USD ->setValidator(aDoubleValidator);



    //-----------------------长度转换初始化-------------------------
    //  input_length.addButton(ui->comboBox_length_ENG);
    //  output_length.addButton(ui->comboBox_length_output);
   //connect(ui->pushButton_length_GtE,ui->pushButton_length_GtE::pressed,this,slot(code_test_lengthENG()));
    connect(ui->pushButton_length_GtE,SIGNAL(pressed()),this,SLOT(code_test_lengthGONG()));//公制转英制
    connect(ui->pushButton_length_EtG,SIGNAL(pressed()),this,SLOT(code_test_lengthENG())); //英制转公制

    //-----------------------面积转换初始化-----------------------
    connect(ui->pushButton_area_GtE,SIGNAL(pressed()),this,SLOT(code_test_areaGONG()));
    connect(ui->pushButton_area_EtG,SIGNAL(pressed()),this,SLOT(code_test_areaENG()));
    //-----------------------体积转换初始化-----------------------
    connect(ui->pushButton_volume_GtE,SIGNAL(pressed()),this,SLOT(code_test_volGONG()));
    connect(ui->pushButton_volume_EtG,SIGNAL(pressed()),this,SLOT(code_test_volENG()));
    //-----------------------重量转换初始化-----------------------
    connect(ui->pushButton_weight_GtE,SIGNAL(pressed()),this,SLOT(code_test_weiGONG()));
    connect(ui->pushButton_weight_EtG,SIGNAL(pressed()),this,SLOT(code_test_weiENG()));
    //-----------------------温度转换初始化-----------------------
    connect(ui->pushButton_temp_FtC,SIGNAL(pressed()),this,SLOT(code_test_tempFah()));
    connect(ui->pushButton_temp_CtF,SIGNAL(pressed()),this,SLOT(code_test_tempCel()));
    //-----------------------货币转换初始化-----------------------
    connect(ui->pushButton_money_CNYtoUSD,SIGNAL(pressed()),this,SLOT(code_test_moneyCNY()));
    connect(ui->pushButton_money_USDtoCNY,SIGNAL(pressed()),this,SLOT(code_test_moneyUSD()));
    //-----------------------时区转换初始化-----------------------
    connect(ui->pushButton_curtime_read,SIGNAL(pressed()),this,SLOT(code_test_timeread()));
    connect(ui->pushButton_time_trans,SIGNAL(pressed()),this,SLOT(on_btnGetTime_clicked()));
}

void MainWindow::input_error_show()
{
    QMessageBox qm;
    qm.about(this,"提示","输入数值有误，请重新输入！");
//    qm.setStyleSheet(
//            "QPushButton {"
//                            "background-color:#89AFDE;"
//                            " border-style: outset;"
//                            " border-width: 2px;"
//                            " border-radius: 10px;"
//                            " border-color: beige;"
//                            " font: bold 24px;"
//                            " min-width: 10em;"
//                            " min-height: 5em;"
//                            "}"
//            "QLabel { min-width: 10em;min-height:5em;font:24px;background-color:#f0f0f0;}"
//        );
//    qm.exec();

}

//----------------------------进制转换-----------------------------------
void MainWindow::code_change(){
    QString ss=ui->lineEdit_binary_input_3->text();
    //qDebug()<<"sss"<<ui->comboBox_binary_input_3->checkedId();
    qDebug()<<"sss"<<ui->comboBox_binary_input_3->currentIndex();

    on_lineEdit_input_textChanged(ss);
}
void MainWindow::on_lineEdit_input_textChanged(const QString &arg1)
{
    bool ok;
    qDebug()<<arg1;
    code_input=ui->comboBox_binary_input_3->currentIndex();
    code_resu=ui->comboBox_binary_output_3->currentIndex();
    switch (code_input) {
    case 1:   //2
        start=arg1.toInt(&ok,2);
        break;
    case 2:   //8
        start=arg1.toInt(&ok,8);
        break;
    case 3:  //10
        start=arg1.toInt(&ok,10);
        break;
    case 4:   //16
        start=arg1.toInt(&ok,16);
        break;
    }
    print_resu();
}
//进制转换---输出
void MainWindow::print_resu(){
    switch (code_resu) {
    case 1:   //2
        resu=QString::number(start,2);
        break;
    case 2:   //8
        resu=QString::number(start,8);
        break;
    case 3:   //10
       resu=QString::number(start,10);
        break;
    case 4:   //16
        resu=QString::number(start,16);
        break;
    }
    //ui->lineEdit_binary_output_3->setText(resu);
}

//-------------------------------------------------进制转换结束------------------------------------------
// ------------------------------------------------长度部分---------------------------------------------
void MainWindow::code_test_lengthENG()
{
    qDebug()<<"英制转公制"<<endl;
    QString mid_length1=ui->lineEdit_length_ENG->text();
    trans_length_ENGtoGong(mid_length1);
}
void MainWindow::code_test_lengthGONG(){
    qDebug()<<"公制转英制"<<endl;
    QString mid_length2=ui->lineEdit_length_GONG->text();
    trans_length_GongtoENG(mid_length2);
    //ulong mid_length2=ui->lineEdit_length_GONG->text();
    //trans_length_GongtoYing(mid_length2);
}
void MainWindow::trans_length_ENGtoGong(const QString &arg2)
{
    bool ok;
    double weishu=arg2.toDouble();
    if(weishu<0)
    {
        //resu_length_ENGtoGONG="error";
        input_error_show();
    }
    else {
    QString str1= QString::number(weishu,'f',6);//设置数据保留小数点后6位
    qDebug()<<arg2<<"---"<<str1;
    code_length_input=ui->comboBox_length_ENG->currentIndex();
    code_length_resu=ui->comboBox_length_GONG->currentIndex();

    switch(code_length_input){
    case 1:
        length_mid_input=0.0254*weishu;
        qDebug()<<"test--"<<length_mid_input;
        break;
    case 2://英尺转换到米
        length_mid_input=0.3048*weishu;
        qDebug()<<"test--"<<length_mid_input;
        break;
    case 3://码转换到米
        length_mid_input=0.9144*weishu;
        qDebug()<<"test--"<<length_mid_input;
        break;
    case 4://英里转换到米
        length_mid_input=1609.344*weishu;
        qDebug()<<"test--"<<length_mid_input;
        break;
    }
    switch(code_length_resu){
    case 1:
        resu_length_ENGtoGONG=QString::number( length_mid_input,'f',6);
        break;
    case 2:
        resu_length_ENGtoGONG=QString::number( 10*length_mid_input,'f',6);
        break;
    case 3:
        resu_length_ENGtoGONG=QString::number(100*length_mid_input,'f',6);
        break;
    case 4:
        resu_length_ENGtoGONG=QString::number(1000* length_mid_input,'f',6);
        break;
    case 5:
        resu_length_ENGtoGONG=QString::number( 10000*length_mid_input,'f',6);
        break;
    case 6:
        resu_length_ENGtoGONG=QString::number( 100000*length_mid_input,'f',6);
        break;
    }}
    ui->lineEdit_length_GONG->setText(resu_length_ENGtoGONG);


}
void MainWindow::trans_length_GongtoENG(const QString &arg3)
{
    bool ok;
    double weishu=arg3.toDouble();
    if(weishu<0)
    {
        //resu_length_GONGtoENG="error";
        input_error_show();

    }
    else {
    QString str2= QString::number(weishu,'f',6);//设置数据保留小数点后6位
    qDebug()<<arg3<<"---"<<str2;
    code_length_input=ui->comboBox_length_GONG->currentIndex();
    code_length_resu=ui->comboBox_length_ENG->currentIndex();

    switch(code_length_input){
    case 1:
        length_mid_input=weishu;
        qDebug()<<"test--"<<length_mid_input;
        break;
    case 2://英尺转换到米
        length_mid_input=0.1*weishu;
        qDebug()<<"test--"<<length_mid_input;
        break;
    case 3://码转换到米
        length_mid_input=0.01*weishu;
        qDebug()<<"test--"<<length_mid_input;
        break;
    case 4://英里转换到米
        length_mid_input=0.001*weishu;
        qDebug()<<"test--"<<length_mid_input;
        break;
    case 5://英里转换到米
        length_mid_input=0.0001*weishu;
        qDebug()<<"test--"<<length_mid_input;
        break;
    case 6://英里转换到米
        length_mid_input=0.00001*weishu;
        qDebug()<<"test--"<<length_mid_input;
        break;
    }
    switch(code_length_resu){
    case 1: //英寸
        resu_length_GONGtoENG=QString::number(39.3700787*length_mid_input,'f',6);
        break;
    case 2:  //英尺
        resu_length_GONGtoENG=QString::number( 3.2808399*length_mid_input,'f',6);
        break;
    case 3: //码
        resu_length_GONGtoENG=QString::number( 1.0936133*length_mid_input,'f',6);
        break;
    case 4://英里
        resu_length_GONGtoENG=QString::number( 0.0006214*length_mid_input,'f',6);
        break;

    }
    }

    ui->lineEdit_length_ENG->setText(resu_length_GONGtoENG);
}
// ------------------------------------------------长度部分结束-------------------------------
// ------------------------------------------------面积部分-----------------------------------
void MainWindow::code_test_areaENG(){
    qDebug()<<"面积--英制转公制"<<endl;
    QString mid_area1 = ui->lineEdit_area_ENG->text();
    //trans_area_ (mid_area1);
    trans_area_ENGtoGong(mid_area1);
}
void MainWindow::code_test_areaGONG(){
    qDebug()<<"面积--公制转英制"<<endl;
    QString mid_area2=ui->lineEdit_area_GONG->text();
    trans_area_GongtoENG(mid_area2);

}
void MainWindow::trans_area_ENGtoGong(const QString &arg2)
{
    bool ok;
    double weishu_area=arg2.toDouble();
    if(weishu_area<0)
    {
        //resu_length_ENGtoGONG="ERROR INPUT";
        input_error_show();

    }
    else {
    QString str1_area= QString::number(weishu_area,'f',6);//设置数据保留小数点后6位
    qDebug()<<arg2<<"---"<<str1_area;
    code_area_input=ui->comboBox_area_ENG->currentIndex();
    code_area_resu=ui->comboBox_area_GONG->currentIndex();
    //----------------------------------------------------------非公制转换为国际单位平方米
    switch(code_area_input){
    case 1://英亩
        area_mid_input=4046.8564224*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 2://平方英里
        area_mid_input=2589988.110336*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 3://平方码
        area_mid_input=0.8361274*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 4://平方英尺
        area_mid_input=0.092903*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 5://平方英寸
        area_mid_input=0.0006452*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 6://平方竿
        area_mid_input=25.2928526*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 7://顷
        area_mid_input=66666.6666667*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 8://亩
        area_mid_input=666.6666667*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 9://分
        area_mid_input=66.6666667*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 10://平方尺
        area_mid_input=0.1111111*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 11://平方寸
        area_mid_input=0.0011111*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    }//-----------------------------国际单位重新转换
    switch(code_area_resu){
    case 1://平方千米
        resu_area_ENGtoGONG=QString::number( (1e-6)*area_mid_input,'f',6);
        break;
    case 2://公顷
        resu_area_ENGtoGONG=QString::number( 0.0001*area_mid_input,'f',6);
        break;
    case 3://公亩
        resu_area_ENGtoGONG=QString::number( 0.01*area_mid_input,'f',6);
        break;
    case 4://平方米
        resu_area_ENGtoGONG=QString::number( area_mid_input,'f',6);
        break;
    case 5://平方分米
        resu_area_ENGtoGONG=QString::number( 100*area_mid_input,'f',6);
        break;
    case 6://平方厘米
        resu_area_ENGtoGONG=QString::number( 10000*area_mid_input,'f',6);
        break;
    case 7://平方毫米
        resu_area_ENGtoGONG=QString::number( 1000000*area_mid_input,'f',6);
        break;

    }}
    //test
    qDebug()<<resu_area_ENGtoGONG<<endl;
    ui->lineEdit_area_GONG->setText(resu_area_ENGtoGONG);


}
void MainWindow::trans_area_GongtoENG(const QString &arg3)
{
    bool ok;
    double weishu_area=arg3.toDouble();
    if(weishu_area<0)
    {
        //resu_area_GONGtoENG="ERROR INPUT";
        input_error_show();

    }
    else {
    QString str2_area= QString::number(weishu_area,'f',6);//设置数据保留小数点后6位
    qDebug()<<arg3<<"---"<<str2_area;
    code_area_input=ui->comboBox_area_GONG->currentIndex();
    code_area_resu=ui->comboBox_area_ENG->currentIndex();
//-------------其他公制转换为国际单位
    switch(code_area_input){
    case 1:  //平方千米->平方米
        area_mid_input=1000000*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 2://公顷转换到平方米
        area_mid_input=10000*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 3://公亩转换到平方米
        area_mid_input=100*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 4://平方米转换到平方米
        area_mid_input=weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 5://平方分米转换到平方米
        area_mid_input=0.01*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 6://平方厘米转换到平方米
        area_mid_input=0.0001*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    case 7://平方毫米转换到平方米
        area_mid_input=(1e-6)*weishu_area;
        qDebug()<<"test--"<<area_mid_input;
        break;
    }
    switch(code_area_resu){
    case 1://英亩
        resu_area_GONGtoENG=QString::number(0.0002471*area_mid_input,'f',6);
        break;
    case 2://平方英里
        resu_area_GONGtoENG=QString::number((3.8610e-7)*area_mid_input,'f',6);
        break;
    case 3://平方码
        resu_area_GONGtoENG=QString::number((1.19599)*area_mid_input,'f',6);
        break;
    case 4://平方英尺
        resu_area_GONGtoENG=QString::number((10.7639104)*area_mid_input,'f',6);
        break;
    case 5://平方英寸
        resu_area_GONGtoENG=QString::number((1550.0031)*area_mid_input,'f',6);
        break;
        break;
    case 6://平方竿
        resu_area_GONGtoENG=QString::number((0.0395369)*area_mid_input,'f',6);
        break;
    case 7://顷
        resu_area_GONGtoENG=QString::number((0.000015)*area_mid_input,'f',6);
        break;
    case 8://亩
        resu_area_GONGtoENG=QString::number((0.0015 )*area_mid_input,'f',6);
        break;
    case 9://分
        resu_area_GONGtoENG=QString::number((0.015)*area_mid_input,'f',6);
        break;
    case 10://平方尺
        resu_area_GONGtoENG=QString::number((9)*area_mid_input,'f',6);
        break;
    case 11://平方寸
        resu_area_GONGtoENG=QString::number((900)*area_mid_input,'f',6);
        break;

    }
    }
//test
    qDebug()<<"resu_area is: "<<resu_area_GONGtoENG<<endl;
    ui->lineEdit_area_ENG->setText(resu_area_GONGtoENG);
}
//-------------------------------------------------面积部分结束-----------------------------------
//-------------------------------------------------体积部分---------------------------------------
void MainWindow::code_test_volENG(){
    qDebug()<<"体积--其他转公制"<<endl;
    QString mid_vol1 = ui->lineEdit_volume_ENG->text();
    //trans_area_ (mid_area1);
    trans_vol_ENGtoGong(mid_vol1);
}
void MainWindow::code_test_volGONG(){
    qDebug()<<"体积--公制转其他"<<endl;
    QString mid_vol2=ui->lineEdit_volume_GONG->text();
    trans_vol_GongtoENG(mid_vol2);

}
void MainWindow::trans_vol_ENGtoGong(const QString &arg2)
{
    bool ok;
    double weishu_vol=arg2.toDouble();
    if(weishu_vol<0)
    {
        //resu_vol_ENGtoGONG="ERROR INPUT";
        input_error_show();

    }
    else {
    QString str1_vol= QString::number(weishu_vol,'f',6);//设置数据保留小数点后6位
    qDebug()<<arg2<<"---"<<str1_vol;
    code_vol_input=ui->comboBox_volume_ENG->currentIndex();
    code_vol_resu=ui->comboBox_volume_GONG->currentIndex();
    //----------------------------------------------------------非公制转换为国际单位立方米
    switch(code_vol_input){
    case 1://立方英尺
        vol_mid_input=(0.0283168)*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 2://立方英寸
        vol_mid_input=(0.0000164)*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 3://立方码
        vol_mid_input=(0.7645536)*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 4://亩英尺
        vol_mid_input=(1233.4818375)*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 5://英制加仑
        vol_mid_input=(0.0045461)*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 6://美制加仑
        vol_mid_input=(0.0037854)*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 7://英制液体盎司
        vol_mid_input=(0.0000284)*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 8://美制液体盎司
        vol_mid_input=(0.0000296 )*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;

    }//-----------------------------国际单位重新转换
    switch(code_vol_resu){
    case 1://立方千米
        resu_vol_ENGtoGONG=QString::number( (1e-9 )*vol_mid_input,'f',6);
        break;
    case 2://立方米
        resu_vol_ENGtoGONG=QString::number( vol_mid_input,'f',6);
        break;
    case 3://立方分米
        resu_vol_ENGtoGONG=QString::number( (1000)*vol_mid_input,'f',6);
        break;
    case 4://立方厘米
        resu_vol_ENGtoGONG=QString::number( (1000000 )*vol_mid_input,'f',6);
        break;
    case 5://立方毫米
        resu_vol_ENGtoGONG=QString::number( (1000000000 )*vol_mid_input,'f',6);
        break;
    case 6://升
        resu_vol_ENGtoGONG=QString::number( (1000  )*vol_mid_input,'f',6);
        break;
    case 7://分升
        resu_vol_ENGtoGONG=QString::number( (10000  )*vol_mid_input,'f',6);
        break;
    case 8://毫升
        resu_vol_ENGtoGONG=QString::number( (1000000  )*vol_mid_input,'f',6);
        break;
    case 9://公石
        resu_vol_ENGtoGONG=QString::number( (10  )*vol_mid_input,'f',6);
        break;
    case 10://微升
        resu_vol_ENGtoGONG=QString::number( (1000000000 )*vol_mid_input,'f',6);
        break;
    }}
    //test
    qDebug()<<resu_vol_ENGtoGONG<<endl;
    ui->lineEdit_volume_GONG->setText(resu_vol_ENGtoGONG);


}
void MainWindow::trans_vol_GongtoENG(const QString &arg3)
{
    bool ok;
    double weishu_vol=arg3.toDouble();
    if(weishu_vol<0)
    {
        //resu_vol_GONGtoENG="ERROR INPUT";
        input_error_show();

    }
    else {
    QString str2_vol= QString::number(weishu_vol,'f',6);//设置数据保留小数点后6位
    qDebug()<<arg3<<"---"<<str2_vol;
    code_vol_input=ui->comboBox_volume_GONG->currentIndex();
    code_vol_resu=ui->comboBox_volume_ENG->currentIndex();
//-------------其他公制转换为国际单位
    switch(code_vol_input){
    case 1:  //立方千米->立方米
        vol_mid_input=(1000000000 )*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 2://立方米到立方米
        vol_mid_input=weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 3://立方分米到立方米
        vol_mid_input=(0.001 )*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 4://立方厘米转换到立方米
        vol_mid_input=(1e-6  )*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 5://立方毫米转换到立方米
        vol_mid_input=(1e-9  )*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 6://升转换到平方米
        vol_mid_input=(0.001 )*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 7://分升转换到平方米
        vol_mid_input=(0.0001 )*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 8://毫升转换到平方米
        vol_mid_input=(1e-6 )*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 9://公石转换到平方米
        vol_mid_input=(0.1 )*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;
    case 10://微升转换到平方米
        vol_mid_input=(1e-9 )*weishu_vol;
        qDebug()<<"test--"<<vol_mid_input;
        break;

    }
    switch(code_vol_resu){
    case 1://立方英尺
        resu_vol_GONGtoENG=QString::number((35.3147248)*vol_mid_input,'f',6);
        break;
    case 2://立方英寸
        resu_vol_GONGtoENG=QString::number((61023.8445022)*vol_mid_input,'f',6);
        break;
    case 3://立方码
        //vol_mid_input=(1.3079528)*weishu_vol;
        resu_vol_GONGtoENG=QString::number((1.3079528)*vol_mid_input,'f',6);
        break;
    case 4://亩英尺
        //vol_mid_input=(0.0008107)*weishu_vol;
        resu_vol_GONGtoENG=QString::number((0.0008107)*vol_mid_input,'f',6);
        break;
    case 5://英制加仑
        //vol_mid_input=(219.9691573)*weishu_vol;
        resu_vol_GONGtoENG=QString::number((219.9691573)*vol_mid_input,'f',6);
        break;
    case 6://美制加仑
        //vol_mid_input=(264.1720524)*weishu_vol;
        resu_vol_GONGtoENG=QString::number((264.1720524)*vol_mid_input,'f',6);
        break;
    case 7://英制液体盎司
        //vol_mid_input=(35198.873636)*weishu_vol;
        resu_vol_GONGtoENG=QString::number((35198.873636)*vol_mid_input,'f',6);
        break;
    case 8://美制液体盎司
        //vol_mid_input=(33818.0588434 )*weishu_vol;
        resu_vol_GONGtoENG=QString::number((33818.0588434)*vol_mid_input,'f',6);
        break;

    }
    }

//test
    qDebug()<<"resu_vol is: "<<resu_vol_GONGtoENG<<endl;
    ui->lineEdit_volume_ENG->setText(resu_vol_GONGtoENG);
}
    //---------------------------------------------体积部分结束------------------------------------
    //---------------------------------------------重量部分---------------------------------------
    void MainWindow::code_test_weiENG(){
        qDebug()<<"重量--其他转公制"<<endl;
        QString mid_wei1 = ui->lineEdit_weight_ENG->text();
        //trans_area_ (mid_area1);
        trans_wei_ENGtoGong(mid_wei1);
    }
    void MainWindow::code_test_weiGONG(){
        qDebug()<<"重量--公制转其他"<<endl;
        QString mid_wei2=ui->lineEdit_weight_GONG->text();
        trans_wei_GongtoENG(mid_wei2);

    }
    void MainWindow::trans_wei_ENGtoGong(const QString &arg2)
    {
        bool ok;
        double weishu_wei=arg2.toDouble();
        if(weishu_wei<0)
        {
            //resu_wei_ENGtoGONG="ERROR INPUT";
            input_error_show();

        }
        else {
        QString str1_wei= QString::number(weishu_wei,'f',6);//设置数据保留小数点后6位
        qDebug()<<arg2<<"---"<<str1_wei;
        code_wei_input=ui->comboBox_weight_ENG->currentIndex();
        code_wei_resu=ui->comboBox_weight_GONG->currentIndex();
        //----------------------------------------------------------非公制转换为国际单位千克
        switch(code_wei_input){
        case 1://磅
            weight_mid_input=(0.4535924)*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 2://盎司
            weight_mid_input=(0.0283495 )*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 3://克拉
            weight_mid_input=(0.0002 )*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 4://格灵
            weight_mid_input=(0.0000648 )*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 5://长吨
            weight_mid_input=(1016.0469088  )*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 6://短吨
            weight_mid_input=(907.18474 )*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 7://英担
            weight_mid_input=(50.8023454 )*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 8://美担
            weight_mid_input=(45.359237 )*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 9://英石
            weight_mid_input=(6.3502932 )*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 10://打兰
            weight_mid_input=(0.0017718 )*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;

        }//-----------------------------国际单位重新转换
        switch(code_wei_resu){
        case 1://千克
            resu_wei_ENGtoGONG=QString::number( weight_mid_input,'f',6);
            break;
        case 2://克
            resu_wei_ENGtoGONG=QString::number((1000)* weight_mid_input,'f',6);
            break;
        case 3://毫克
            resu_wei_ENGtoGONG=QString::number( (1000000)*weight_mid_input,'f',6);
            break;
        case 4://微克
            resu_wei_ENGtoGONG=QString::number((1000000000)* weight_mid_input,'f',6);
            break;
        case 5://吨
            resu_wei_ENGtoGONG=QString::number((0.001)* weight_mid_input,'f',6);
            break;
        case 6://公担
            resu_wei_ENGtoGONG=QString::number((0.01)* weight_mid_input,'f',6);
            break;
        case 7://克拉
            resu_wei_ENGtoGONG=QString::number( (5000 )*weight_mid_input,'f',6);
            break;
        case 8://分
            resu_wei_ENGtoGONG=QString::number( (500000)*weight_mid_input,'f',6);
            break;
        }}
        //test
        qDebug()<<resu_wei_ENGtoGONG<<endl;
        ui->lineEdit_weight_GONG->setText(resu_wei_ENGtoGONG);


    }
    void MainWindow::trans_wei_GongtoENG(const QString &arg3)
    {
        bool ok;
        double weishu_wei=arg3.toDouble();
        if(weishu_wei<0)
        {
            //resu_wei_GONGtoENG="ERROR INPUT";
            input_error_show();

        }
        else {
        QString str2_wei= QString::number(weishu_wei,'f',6);//设置数据保留小数点后6位
        qDebug()<<arg3<<"---"<<str2_wei;
        code_wei_input=ui->comboBox_weight_GONG->currentIndex();
        code_wei_resu=ui->comboBox_weight_ENG->currentIndex();
    //-------------其他公制转换为国际单位
        switch(code_wei_input){
        case 1:  //千克转换到千克
            weight_mid_input=(1)*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 2://克转换到千克
            weight_mid_input=(0.001 )*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 3://毫克转换到千克
            weight_mid_input=(1e-6)*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 4://微克转换到千克
            weight_mid_input=(1e-9)*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 5://吨转换到千克
            weight_mid_input=(1000 )*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 6://公担转换到千克
            weight_mid_input=(100)*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 7://克拉转换到千克
            weight_mid_input=(0.0002)*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        case 8://分转换到千克
            weight_mid_input=(2e-6)*weishu_wei;
            qDebug()<<"test--"<<weight_mid_input;
            break;
        }
        switch(code_wei_resu){
        case 1://磅
            resu_wei_GONGtoENG=QString::number((2.2046226 )*weight_mid_input,'f',6);
            break;
        case 2://盎司
            resu_wei_GONGtoENG=QString::number((35.2739619 )*weight_mid_input,'f',6);
            break;
        case 3://克拉
            resu_wei_GONGtoENG=QString::number((5000 )*weight_mid_input,'f',6);
            break;
        case 4://格令
            resu_wei_GONGtoENG=QString::number((15432.3583529 )*weight_mid_input,'f',6);
            break;
        case 5://长吨
            resu_wei_GONGtoENG=QString::number((0.0009842 )*weight_mid_input,'f',6);
            break;
        case 6://短吨
            resu_wei_GONGtoENG=QString::number((0.0011023 )*weight_mid_input,'f',6);
            break;
        case 7://英担
            resu_wei_GONGtoENG=QString::number((0.0196841 )*weight_mid_input,'f',6);
            break;
        case 8://美担
            resu_wei_GONGtoENG=QString::number((0.0220462  )*weight_mid_input,'f',6);
            break;
        case 9://英石
            resu_wei_GONGtoENG=QString::number((0.157473  )*weight_mid_input,'f',6);
            break;
        case 10://打兰
            resu_wei_GONGtoENG=QString::number((564.3833912  )*weight_mid_input,'f',6);
            break;
        }
        }
    //test
        qDebug()<<"resu_wei is: "<<resu_wei_GONGtoENG<<endl;
        ui->lineEdit_weight_ENG->setText(resu_wei_GONGtoENG);
    }

    //---------------------------------------------重量部分结束------------------------------------
    //---------------------------------------------温度部分---------------------------------------
    void MainWindow::code_test_tempCel(){
        qDebug()<<"温度--摄氏转华氏-------------"<<endl;
        QString mid_temp1 = ui->lineEdit_temp_Celsius->text();
        //trans_area_ (mid_area1);
        trans_temp_CtoF(mid_temp1);
    }
    void MainWindow::code_test_tempFah(){
        qDebug()<<"温度--华氏转摄氏--------------"<<endl;
        QString mid_temp2=ui->lineEdit_temp_Farenheit->text();
        trans_temp_FtoC(mid_temp2);

    }
    void MainWindow::trans_temp_CtoF(const QString &arg2)
    {
        bool ok;
        double weishu_temp=arg2.toDouble();
        if(weishu_temp+273.0<0.000)
        {
            //resu_temp_CtoF="ERROR INPUT";
            input_error_show();

        }
        else {
        QString str1_temp= QString::number(weishu_temp,'f',6);//设置数据保留小数点后6位
        qDebug()<<arg2<<"---"<<str1_temp;
        code_temp_input=ui->comboBox_temp_Celsius->currentIndex();
        code_temp_resu=ui->comboBox_temp_Farenheit->currentIndex();
        qDebug()<<code_temp_input<<endl; //test
        //----------------------------------------------------------f=9/5 *C +32
        switch(code_temp_input){
        case 0://摄氏度
            resu_temp_CtoF =QString::number( (1.8)*weishu_temp+32 ,'f',6);
            //weight_mid_input=(0.4535924)*weishu_wei;
            //qDebug()<<"test--"<<weight_mid_input;
            break;
        }

        }//test
        qDebug()<<resu_temp_CtoF <<endl;
        ui->lineEdit_temp_Farenheit ->setText(resu_temp_CtoF);
    }
    void MainWindow::trans_temp_FtoC( const QString &arg3)
    {
        bool ok;
        double weishu_temp=arg3.toDouble();
        if(0)
        {
            //resu_temp_FtoC ="ERROR INPUT";
            input_error_show();
        }
        else {
        QString str2_temp= QString::number(weishu_temp,'f',6);//设置数据保留小数点后6位
        qDebug()<<arg3<<"---"<<str2_temp;
        code_temp_input=ui->comboBox_temp_Farenheit ->currentIndex();
        code_temp_resu=ui->comboBox_temp_Celsius->currentIndex();
        qDebug()<<code_temp_input<<endl;  //test
    //-----------------------------------------------------c= (f-32)/1.8
        switch(code_temp_input){
        case 0:  //
            resu_temp_FtoC =QString::number( (weishu_temp-32)/(1.8) ,'f',6);
        }
        }//test
        qDebug()<<"resu_temp is: "<<resu_temp_FtoC <<endl;
        ui->lineEdit_temp_Celsius ->setText(resu_temp_FtoC );
    }
    //---------------------------------------------温度部分结束--------------------------------------

    //---------------------------------------------货币部分---------------------------------------
    void MainWindow::code_test_moneyUSD(){
        qDebug()<<"货币--美元转人民币-------------"<<endl;
        QString mid_money1 = ui->lineEdit_money_USD->text();
        //trans_area_ (mid_area1);
        trans_money_USDtoCNY(mid_money1);
    }
    void MainWindow::code_test_moneyCNY(){
        qDebug()<<"温度--人民币转美元--------------"<<endl;
        QString mid_money2=ui->lineEdit_money_CNY->text();
        trans_money_CNYtoUSD(mid_money2);

    }
    void MainWindow::trans_money_USDtoCNY(const QString &arg2)
    {
        bool ok;
        double weishu_money=arg2.toDouble();
        if(weishu_money<0.000)
        {
            //resu_temp_CtoF="ERROR INPUT";
            input_error_show();

        }
        else {
        QString str1_money= QString::number(weishu_money,'f',6);//设置数据保留小数点后6位
        qDebug()<<arg2<<"---"<<str1_money;
        code_money_input=ui->comboBox_money_USD->currentIndex();
        code_money_resu=ui->comboBox_money_CNY->currentIndex();
        qDebug()<<code_money_input<<endl; //test
        //----------------------------------------------------------美元汇率:6.7898
        switch(code_money_input){
        case 0://美元
            resu_money_USDtoCNY =QString::number( (exange_rate_USDtoCNY)*weishu_money ,'f',6);
            break;
        }
        }//test
        qDebug()<<resu_money_USDtoCNY <<endl;
        ui->lineEdit_money_CNY->setText(resu_money_USDtoCNY);
    }
    void MainWindow::trans_money_CNYtoUSD(const QString &arg3)
    {
        bool ok;
        double weishu_money=arg3.toDouble();
        if(weishu_money<0)
        {
            //resu_temp_FtoC ="ERROR INPUT";
            input_error_show();
        }
        else {
        QString str2_money= QString::number(weishu_money,'f',6);//设置数据保留小数点后6位
        qDebug()<<arg3<<"---"<<str2_money;
        code_money_input=ui->comboBox_money_CNY->currentIndex();
        code_money_resu=ui->comboBox_money_USD ->currentIndex();
        qDebug()<<code_money_input<<endl;  //test
    //-----------------------------------------------------人民币汇率
        switch(code_money_input){
        case 0:  //
            resu_money_CNYtoUSD =QString::number( (exange_rate_CNYtoUSD)*weishu_money ,'f',6);
        }
        }//test
        qDebug()<<"resu_money is: "<<resu_money_CNYtoUSD <<endl;
        ui->lineEdit_money_USD ->setText(resu_money_CNYtoUSD);
    }
    //---------------------------------------------时间部分---------------------------------------

    void MainWindow::code_test_timeread()
    {
        //获取当前日期时间
        //QDateTime curDateTime=QDateTime::currentDateTime();
        ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    }
    void MainWindow::on_btnGetTime_clicked()
    {

         QTimeZone newZone_Tokyo("Asia/Tokyo");
         QTimeZone newZone_London("Europe/London");
         QTimeZone newZone_Berlin("Europe/Berlin");
         QTimeZone newZone_Vancouver("America/Vancouver");
         QTimeZone newZone_Moscow("Europe/Moscow");
         QTimeZone newZone_Los_Angeles("America/Los_Angeles");
         QTimeZone newZone_Chicago("America/Chicago");
         QTimeZone newZone_NewYork("America/New_York");
         //QTimeZone newZone_Brasilia("America/Argentina/Rio_Gallegos"); //判定无效
         QTimeZone newZone_Paris("Europe/Paris");
         QTimeZone newZone_Tehran("Asia/Tehran");
        // QTimeZone newZone_New_Delhi("Asia/New_Delhi"); //system不支持
         QTimeZone newZone_Bangkok("Asia/Bangkok");
         QTimeZone newZone_Sydney("Australia/Sydney");

         //----------------读取左侧输入栏日期
         //QDateTime curDateTime=QDateTime::currentDateTime();//写入当前系统时间
         QDateTime curDateTime=ui->dateTimeEdit->dateTime();


         //ui->dateTimeEdit->setDateTime(curDateTime);

        //QDateTime nowDate = QDateTime::currentDateTimeUtc();
        //qDebug()<< nowDate<<"----------"<<nowDate.toTimeZone(newZone);
        switch(ui->comboBox_time_output->currentIndex()){

        case 0://北京
            qDebug()<<"转换到北京时间："<<curDateTime<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime);
            break;
        case 1://东京
            qDebug()<<"转换到东京时间："<<curDateTime.toTimeZone(newZone_Tokyo)<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime.toTimeZone(newZone_Tokyo));
            break;
        case 2://伦敦
            qDebug()<<"转换到伦敦时间："<<curDateTime.toTimeZone(newZone_London)<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime.toTimeZone(newZone_London));
            break;
        case 3://柏林
            qDebug()<<"转换到柏林时间："<<curDateTime.toTimeZone(newZone_Berlin)<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime.toTimeZone(newZone_Berlin));
            break;
        case 4://温哥华
            qDebug()<<"转换到温哥华时间："<<curDateTime.toTimeZone(newZone_Vancouver)<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime.toTimeZone(newZone_Vancouver));
            break;
        case 5://莫斯科
            qDebug()<<"转换到莫斯科时间："<<curDateTime.toTimeZone(newZone_Moscow)<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime.toTimeZone(newZone_Moscow));
            break;
        case 6://洛杉矶
            qDebug()<<"转换到洛杉矶时间："<<curDateTime.toTimeZone(newZone_Los_Angeles)<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime.toTimeZone(newZone_Los_Angeles));
            break;
        case 7://芝加哥
            qDebug()<<"转换到芝加哥时间："<<curDateTime.toTimeZone(newZone_Chicago)<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime.toTimeZone(newZone_Chicago));
            break;
        case 8://纽约
            qDebug()<<"转换到纽约时间："<<curDateTime.toTimeZone(newZone_NewYork)<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime.toTimeZone(newZone_NewYork));
            break;
        case 9://巴黎
            qDebug()<<"转换到巴黎时间："<<curDateTime.toTimeZone(newZone_Paris)<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime.toTimeZone(newZone_Paris));
            break;
        case 10://德黑兰
            qDebug()<<"转换到德黑兰时间："<<curDateTime.toTimeZone(newZone_Tehran)<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime.toTimeZone(newZone_Tehran));
            break;
        case 11://曼谷
            qDebug()<<"转换到曼谷时间："<<curDateTime.toTimeZone(newZone_Bangkok)<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime.toTimeZone(newZone_Bangkok));
            break;
        case 12://悉尼
            qDebug()<<"转换到悉尼时间："<<curDateTime.toTimeZone(newZone_Sydney)<<endl;
            ui->dateTimeEdit_output->setDateTime(curDateTime.toTimeZone(newZone_Sydney));
            break;
        }
    }
    //---------------------------------------------时间部分结束---------------------------------------
