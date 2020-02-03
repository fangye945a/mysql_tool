#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_comboBox_product_type_currentIndexChanged("所有产品");   //获取所有产品在线数量
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open_database()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("120.24.100.10");
    db.setPort(7306);
    db.setDatabaseName("mqtt_zbox_manage");
    db.setUserName("root");
    db.setPassword("zoom.157");
    bool ok = db.open();
    if (ok)
    {
        qDebug() << "连接数据库ok";
    }
    else
    {
        qDebug() << "连接数据库失败";
    }
}

void MainWindow::exec_mysql_cmd(QString cmd, int result_need, QStringList *result_list)
{
    if(!db.isOpen())
    {
       open_database();
    }

    if(db.isOpen())
    {
        QSqlQuery query;
        qDebug()<<"执行SQL语句:"<<cmd;
        bool ret = query.exec(cmd);            //执行此数据库语句
        if(ret)
            qDebug()<<"执行成功";
        else
            qDebug()<<"执行失败";

        if(result_need >= 0) //需要执行结果
        {
            while(query.next())//query指向下一条记录，每执行一次该函数，便指向相邻的下一条记录。
            {
                (*result_list)<<query.value(result_need).toString();
            }
        }
    }
    else
    {
        qDebug() << "打开数据库失败!";
    }
}

void MainWindow::on_comboBox_product_type_currentIndexChanged(const QString &arg1)  //选择产品类型
{
    QString device_num_cmd;
    QString device_num_online_cmd;

    if(arg1 == "所有产品")
    {
        device_num_cmd = "SELECT COUNT(*) FROM device_state_info;";
        device_num_online_cmd = "select COUNT(*) FROM device_state_info where online_time > offline_time;";
    }
    else if(arg1 == "建起塔机TSM")
    {
        device_num_cmd = "SELECT COUNT(product_id) FROM device_state_info WHERE product_id = 'KqSPWIMl3p';";
        device_num_online_cmd = "select COUNT(product_id) FROM device_state_info where online_time > offline_time AND product_id = 'KqSPWIMl3p';";
    }
    else if(arg1 == "建起塔机IOT")
    {
        device_num_cmd = "SELECT COUNT(product_id) FROM device_state_info WHERE product_id = 'z14NeBe47A';";
        device_num_online_cmd = "select COUNT(product_id) FROM device_state_info where online_time > offline_time AND product_id = 'z14NeBe47A';";
    }
    else if(arg1 == "土方小挖")
    {
        device_num_cmd = "SELECT COUNT(product_id) FROM device_state_info WHERE product_id = '1de29pmNvL';";
        device_num_online_cmd = "select COUNT(product_id) FROM device_state_info where online_time > offline_time AND product_id = '1de29pmNvL';";
    }
    else if(arg1 == "混凝土泵车")
    {
        device_num_cmd = "SELECT COUNT(product_id) FROM device_state_info WHERE product_id = 'IqmyGXSlPD';";
        device_num_online_cmd = "select COUNT(product_id) FROM device_state_info where online_time > offline_time AND product_id = 'IqmyGXSlPD';";
    }
    else if(arg1 == "基施旋挖钻")
    {
        device_num_cmd = "SELECT COUNT(product_id) FROM device_state_info WHERE product_id = '3qWnfgz6QL';";
        device_num_online_cmd = "select COUNT(product_id) FROM device_state_info where online_time > offline_time AND product_id = '3qWnfgz6QL';";
    }
    else if(arg1 == "工起轮胎吊")
    {
        device_num_cmd = "SELECT COUNT(product_id) FROM device_state_info WHERE product_id = '7qWnfgz9QL';";
        device_num_online_cmd = "select COUNT(product_id) FROM device_state_info where online_time > offline_time AND product_id = '7qWnfgz9QL';";
    }
    else if(arg1 == "工起履带吊")
    {
        device_num_cmd = "SELECT COUNT(product_id) FROM device_state_info WHERE product_id = '5qWnfgz7QL';";
        device_num_online_cmd = "select COUNT(product_id) FROM device_state_info where online_time > offline_time AND product_id = '5qWnfgz7QL';";
    }
    else if(arg1 == "其它")
    {
        device_num_cmd = "SELECT COUNT(product_id) FROM device_state_info WHERE product_id = 'unknow';";
        device_num_online_cmd = "select COUNT(product_id) FROM device_state_info where online_time > offline_time AND product_id = 'unknow';";
    }

    QStringList results;
    exec_mysql_cmd(device_num_cmd, 0, &results);
    ui->device_num->setText(QString(results.at(0)));

    results.clear();
    exec_mysql_cmd(device_num_online_cmd, 0, &results);
    ui->device_num_online->setText(QString(results.at(0)));
}
