#ifndef FAIL_H
#define FAIL_H

#include <QDialog>
#include <QString>

namespace Ui {
class Fail;
}

class Fail : public QDialog
{
    Q_OBJECT

public:
    explicit Fail(QWidget *parent = nullptr);
    ~Fail();
    
    // 添加设置错误信息的方法
    void setErrorMessage(const QString &message);

private:
    Ui::Fail *ui;
};



#endif // FAIL_H
