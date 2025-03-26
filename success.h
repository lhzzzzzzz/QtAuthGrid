#ifndef SUCCESS_H
#define SUCCESS_H

#include <QDialog>
#include <QString>

// 前向声明
class Table;

namespace Ui {
class Success;
}

class Success : public QDialog
{
    Q_OBJECT

public:
    explicit Success(QWidget *parent = nullptr);
    ~Success();
    
    void setUsername(const QString &username);
    
private slots:
    // 处理确定按钮点击事件
    void on_buttonBox_accepted();
    
private:
    Ui::Success *ui;
    QString m_username; // 保存用户名
};


#endif // SUCCESS_H
