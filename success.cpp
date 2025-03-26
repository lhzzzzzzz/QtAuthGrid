#include "success.h"
#include "ui_success.h" // 包含由 Qt Designer 自动生成的 UI 头文件
#include "table.h"
#include <QString>

Success::Success(QWidget *parent) :
    QDialog(parent),  // 调用基类构造函数
    ui(new Ui::Success) // 创建 UI 对象
{
    ui->setupUi(this);  // 初始化 UI，关联成功界面和 UI 文件
    
    // 设置窗口标题
    setWindowTitle("登录成功");
    
    // 设置欢迎文本
    ui->textEdit->setReadOnly(true); // 设置为只读
    ui->textEdit->setText("登录成功！\n欢迎使用本系统。");
}

// 设置用户名显示
void Success::setUsername(const QString &username) {
    m_username = username; // 保存用户名
    ui->textEdit->setText("登录成功！\n欢迎您，" + username + "！");
}

// 当用户点击"确定"按钮时跳转到表格界面
void Success::on_buttonBox_accepted()
{
    // 隐藏成功对话框
    this->hide();
    
    // 创建表格窗口并显示
    Table *tableWindow = new Table();
    tableWindow->show();
    
    // 关闭并销毁当前窗口
    this->accept();
}

Success::~Success()
{
    delete ui;  // 销毁 UI 对象
}
