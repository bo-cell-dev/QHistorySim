#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QStack>
#include <QString>

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

private slots:
    void on_open1_clicked();
    void on_open2_clicked();
    void on_open3_clicked();

    void on_back_clicked();

    void on_foward_clicked();

    void on_pushButton_clicked();
    void on_clearBtn_clicked();

private:
    Ui::MainPage *ui;

    QString currentPage = "Home page";
    QStack<QString> backStack;
    QStack<QString> forwardStack;

    void updateScreen();
    void visitPage(const QString &url);
};

#endif
