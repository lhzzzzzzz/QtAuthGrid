#include "fail.h"
#include "ui_fail.h" // 包含由 Qt Designer 自动生成的 UI 头文件
#include <QString>

Fail::Fail(QWidget *parent) :
    QDialog(parent),  // 调用 QDialog 的构造函数
    ui(new Ui::Fail)  // 创建 UI 对象
{
    ui->setupUi(this);  // 初始化 UI
    
    // 设置窗口标题
    setWindowTitle("登录失败");
    
    // 设置失败信息
    ui->fail_message->setReadOnly(true); // 设置为只读
    ui->fail_message->setText("登录失败！\n用户名或密码错误。");
}

// 设置自定义错误信息
void Fail::setErrorMessage(const QString &message) {
    ui->fail_message->setText("登录失败！\n" + message);
}

Fail::~Fail()
{
    delete ui;  // 删除 UI 对象
}
