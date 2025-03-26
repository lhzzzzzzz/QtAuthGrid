#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class Table;
}

class Table : public QWidget
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = nullptr);
    ~Table();
    
    // 加载用户数据到表格
    void loadUserData();

private slots:
    // 返回登录界面的按钮点击事件
    void on_btn_back_clicked();

private:
    Ui::Table *ui;
};

#endif // TABLE_H
