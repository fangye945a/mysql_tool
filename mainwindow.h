#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void open_database();
    void exec_mysql_cmd(QString cmd, int result_need = -1, QStringList *result_list = NULL);

private slots:
    void on_comboBox_product_type_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;    //数据库
};

#endif // MAINWINDOW_H
