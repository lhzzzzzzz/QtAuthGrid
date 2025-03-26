#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "success.h"  // 引入 Success 窗口类
#include "fail.h"     // 引入 Fail 对话框类

// 添加 MariaDB C 连接器头文件
#include <mysql.h>
#include <string.h>  // 为 strlen 函数添加头文件
#include <iostream>  // 为 cerr, endl 添加头文件

using namespace std;

bool login(string username, string password) {
    try {
        // 使用 MariaDB C API 进行连接
        MYSQL* mysql = mysql_init(nullptr);
        if (!mysql) {
            cerr << "MySQL fail" << endl;
            return false;
        }

        cerr << "MySQL success" << endl;

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

        // 禁用SSL连接的选项
        mysql_options(mysql, MYSQL_OPT_SSL_VERIFY_SERVER_CERT, &option);

        // 连接到 MySQL 服务器
        if (!mysql_real_connect(mysql, "172.17.48.25", "windows", "sander2244", "for_demo", 3306, nullptr, 0)) {
            // 第一种连接方式失败，尝试不使用认证插件的方式
            cerr << "First connection method failed: " << mysql_error(mysql) << endl;
            cerr << "Trying alternative connection method..." << endl;
            
            // 重新初始化连接
            mysql_close(mysql);
            mysql = mysql_init(nullptr);
            
            // 直接连接，不设置任何选项
            if (!mysql_real_connect(mysql, "172.17.48.25", "windows", "sander2244", "for_demo", 3306, nullptr, 0)) {
                cerr << "Alternative connection also failed: " << mysql_error(mysql) << endl;
                mysql_close(mysql);
                return false;
            }
        }

        cerr << "connect success" << endl;

        // 准备 SQL 查询
        // 使用预处理语句防止 SQL 注入
        MYSQL_STMT* stmt = mysql_stmt_init(mysql);
        if (!stmt) {
            cerr << "pre fail" << endl;
            mysql_close(mysql);
            return false;
        }

        cerr << "pre success" << endl;

        const char* query = "SELECT * FROM user WHERE name=? AND password=?";
        if (mysql_stmt_prepare(stmt, query, strlen(query))) {
            cerr << "pre fail 2: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            mysql_close(mysql);
            return false;
        }

        cerr << "pre success 2" << endl;

        // 绑定参数
        MYSQL_BIND bind[2];
        memset(bind, 0, sizeof(bind));

        // 保存字符串长度的变量
        unsigned long username_length = username.length();
        unsigned long password_length = password.length();

        // 为用户名和密码准备绑定数据
        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = (void*)username.c_str();
        bind[0].buffer_length = username_length;
        bind[0].is_null = 0;
        bind[0].length = &username_length;

        bind[1].buffer_type = MYSQL_TYPE_STRING;
        bind[1].buffer = (void*)password.c_str();
        bind[1].buffer_length = password_length;
        bind[1].is_null = 0;
        bind[1].length = &password_length;

        // 设置参数
        if (mysql_stmt_bind_param(stmt, bind)) {
            cerr << "参数绑定失败: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            mysql_close(mysql);
            return false;
        }

        cerr << "参数绑定成功" << endl;

        // 执行查询
        if (mysql_stmt_execute(stmt)) {
            cerr << "执行查询失败: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            mysql_close(mysql);
            return false;
        }

        cerr << "执行查询成功" << endl;

        // 获取结果
        if (mysql_stmt_store_result(stmt)) {
            cerr << "存储结果失败: " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            mysql_close(mysql);
            return false;
        }

        cerr << "存储结果成功" << endl;

        // 检查是否有匹配的记录
        bool isSuccess = (mysql_stmt_num_rows(stmt) > 0);

        // 清理资源
        mysql_stmt_close(stmt);
        mysql_close(mysql);

        return isSuccess;
    }
    catch (const exception& e) {
        cerr << "数据库错误: " << e.what() << endl;
        return false;
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

string userName, password;

void MainWindow::on_button_login_clicked()
{
    userName = ui->txt_name->text().toStdString();
    password = ui->txt_password->text().toStdString();
    
    // 输入验证
    if (userName.empty() || password.empty()) {
        Fail *failWindow = new Fail(this);
        failWindow->setErrorMessage("用户名和密码不能为空！");
        failWindow->exec();
        return;
    }
    
    if (login(userName, password)) {
        Success *successWindow = new Success(this);
        successWindow->setUsername(QString::fromStdString(userName));  // 传递用户名
        successWindow->exec();  // 显示成功对话框
        
        // 登录成功后可以清空输入框
        ui->txt_name->clear();
        ui->txt_password->clear();
    }
    else {
        Fail *failWindow = new Fail(this);
        // 可以使用默认错误消息，也可以设置自定义消息
        failWindow->setErrorMessage("用户名或密码错误，请重试！");
        failWindow->exec();  // 显示失败对话框
        
        // 登录失败后只清空密码框
        ui->txt_password->clear();
    }
}

