#include "table.h"
#include "ui_table.h"
#include "mainwindow.h"
#include <mysql.h>
#include <QMessageBox>
#include <iostream>
#include <QHeaderView>
#include <QTableWidgetItem>

using namespace std;

Table::Table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Table)
{
    ui->setupUi(this);
    
    // 设置窗口标题
    setWindowTitle("用户数据表");
    
    // 设置按钮文本
    ui->btn_back->setText("返回登录");
    
    // 加载用户数据
    loadUserData();
    
    // 设置表格样式
    ui->table->horizontalHeader()->setStretchLastSection(true);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置为只读
}

Table::~Table()
{
    delete ui;
}

void Table::loadUserData()
{
    try {
        // 使用 MariaDB C API 进行连接
        MYSQL* mysql = mysql_init(nullptr);
        if (!mysql) {
            cerr << "MySQL 初始化失败" << endl;
            return;
        }

        cerr << "MySQL 初始化成功" << endl;

        // 设置插件目录
        const char *plugin_dir = "C:/Program Files/MariaDB/MariaDB Connector C 64-bit/lib/plugin";
        mysql_options(mysql, MYSQL_PLUGIN_DIR, plugin_dir);
        
        // 禁用服务器证书验证
        unsigned int option = 0; // 0表示禁用证书验证
        mysql_options(mysql, MYSQL_OPT_SSL_VERIFY_SERVER_CERT, &option);
        
        // 指定使用mysql_native_password认证插件
        const char *auth_plugin = "mysql_native_password";
        mysql_options(mysql, MYSQL_DEFAULT_AUTH, auth_plugin);
        
        // 添加连接选项，禁用某些功能
        int secure_auth = 0; // 允许老式认证
        mysql_options(mysql, MYSQL_SECURE_AUTH, &secure_auth);
        
        // 设置SSL参数全部为NULL，使用默认设置
        mysql_ssl_set(mysql, nullptr, nullptr, nullptr, nullptr, nullptr);

        // 连接到 MySQL 服务器
        if (!mysql_real_connect(mysql, "172.17.48.25", "windows", "sander2244", "for_demo", 3306, nullptr, 0)) {
            // 第一种连接方式失败，尝试不使用认证插件的方式
            cerr << "第一种连接方式失败: " << mysql_error(mysql) << endl;
            cerr << "尝试替代连接方式..." << endl;
            
            // 重新初始化连接
            mysql_close(mysql);
            mysql = mysql_init(nullptr);
            
            // 直接连接，不设置任何选项
            if (!mysql_real_connect(mysql, "172.17.48.25", "root", "sander2244", "for_demo", 3306, nullptr, 0)) {
                cerr << "替代连接方式也失败: " << mysql_error(mysql) << endl;
                mysql_close(mysql);
                return;
            }
        }
        
        // 执行查询
        if (mysql_query(mysql, "SELECT name, password FROM user")) {
            cerr << "查询失败: " << mysql_error(mysql) << endl;
            mysql_close(mysql);
            return;
        }
        
        // 获取查询结果
        MYSQL_RES* result = mysql_store_result(mysql);
        if (!result) {
            cerr << "获取结果失败: " << mysql_error(mysql) << endl;
            mysql_close(mysql);
            return;
        }
        
        // 清空表格并设置行数
        unsigned int numRows = mysql_num_rows(result);
        ui->table->setRowCount(numRows);
        
        // 添加数据到表格
        int row = 0;
        MYSQL_ROW mysqlRow;
        
        while ((mysqlRow = mysql_fetch_row(result))) {
            // 用户名
            QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromUtf8(mysqlRow[0]));
            ui->table->setItem(row, 0, nameItem);
            
            // 密码
            QTableWidgetItem *passwordItem = new QTableWidgetItem(QString::fromUtf8(mysqlRow[1]));
            ui->table->setItem(row, 1, passwordItem);
            
            row++;
        }
        
        // 释放结果和连接
        mysql_free_result(result);
        mysql_close(mysql);
    }
    catch (const exception& e) {
        cerr << "数据库错误: " << e.what() << endl;
    }
}

void Table::on_btn_back_clicked()
{
    // 隐藏表格窗口
    this->hide();
    
    // 设置表格窗口在关闭时自动销毁
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}
