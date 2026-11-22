#include "mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);
    this->setStyleSheet(R"(
        QWidget#MainPage {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                        stop:0 #2b192e, stop:0.5 #1b1e32, stop:1 #152b3c);
            color: #ffffff;
            font-family: 'Segoe UI', sans-serif;
            font-size: 15px;
        }

        QFrame#centerLine {
            border: none;
            min-width: 3px;
            max-width: 3px;
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                        stop:0 #ff6ec7, stop:1 #4facfe);
            border-radius: 1px;
        }

        QLabel {
            background: transparent;
            font-size: 19px;
            font-weight: bold;
            color: #ff9ce3;
            padding: 8px;
        }

        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                        stop:0 rgba(255, 110, 199, 0.25),
                                        stop:1 rgba(79, 172, 254, 0.25));
            border: 1px solid #ff6ec7;
            border-radius: 10px;
            padding: 10px 16px;
            color: #ffffff;
            font-weight: bold;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                        stop:0 #ff6ec7, stop:1 #4facfe);
            color: #11111b;
            border: 1px solid #4facfe;
        }
        QPushButton:pressed {
            background-color: #4facfe;
            color: #11111b;
        }
        QPushButton:disabled {
            background: rgba(255, 255, 255, 0.05);
            border: 1px solid rgba(255, 255, 255, 0.1);
            color: rgba(255, 255, 255, 0.3);
        }

        QListWidget {
            background-color: rgba(17, 17, 27, 0.65);
            border: 2px solid #4facfe;
            border-radius: 12px;
            padding: 8px;
            font-size: 16px;
        }
        QListWidget::item {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                        stop:0 rgba(255, 110, 199, 0.2),
                                        stop:1 rgba(79, 172, 254, 0.2));
            border-left: 4px solid #ff6ec7;
            border-radius: 6px;
            padding: 10px;
            margin-bottom: 6px;
            color: #ffffff;
        }
        QListWidget::item:selected {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                        stop:0 #ff6ec7, stop:1 #4facfe);
            color: #11111b;
            font-weight: bold;
        }
    )");

    updateScreen();
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::on_open1_clicked() { visitPage("Google"); }
void MainPage::on_open2_clicked() { visitPage("YouTube"); }
void MainPage::on_open3_clicked() { visitPage("GitHub"); }

void MainPage::updateScreen()
{
    ui->label->setText("Now opened: " + currentPage);
    ui->listBack->clear();
    for (int i = backStack.size() - 1; i >= 0; --i) {
        ui->listBack->addItem(backStack[i]);
    }
    ui->listForward->clear();
    for (int i = forwardStack.size() - 1; i >= 0; --i) {
        ui->listForward->addItem(forwardStack[i]);
    }
    ui->back->setEnabled(!backStack.isEmpty());
    ui->foward->setEnabled(!forwardStack.isEmpty());
}


void MainPage::on_back_clicked()
{
    if (backStack.isEmpty()) return;
    forwardStack.push(currentPage);
    currentPage = backStack.pop();
    updateScreen();
}


void MainPage::on_foward_clicked()
{
    if (forwardStack.isEmpty()) return;
    backStack.push(currentPage);
    currentPage = forwardStack.pop();
    updateScreen();
}

void MainPage::visitPage(const QString &url)
{
    backStack.push(currentPage);
    forwardStack.clear();
    currentPage = url;
    updateScreen();
}

void MainPage::on_pushButton_clicked()
{
    QString url = ui->urlInput->text().trimmed();
    if (!url.isEmpty() && url != currentPage) {
        visitPage(url);
        ui->urlInput->clear();
    }
}

void MainPage::on_clearBtn_clicked()
{
    backStack.clear();
    forwardStack.clear();
    currentPage = "Home page";
    updateScreen();
}

