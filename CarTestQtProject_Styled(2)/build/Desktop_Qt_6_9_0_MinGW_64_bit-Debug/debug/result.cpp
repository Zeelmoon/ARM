#include "result.h"
#include "ui_result.h"
#include <QDebug>
#include <QPixmap>

Result::Result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
    setWindowTitle("Результаты теста");

    // Убедимся, что лейблы видны
    ui->imageLabel1->setVisible(true);
    ui->imageLabel2->setVisible(true);
}

Result::~Result()
{
    emit windowClosed();
    delete ui;
}

void Result::setResultText(const QString &text)
{
    ui->label->setText(text);
}

void Result::closeEvent(QCloseEvent *event)
{
    qDebug() << "Result window closing...";
    emit windowClosed();
    QWidget::closeEvent(event);
}

void Result::setResultData(const QString& text, const QString& imagePath1, const QString& imagePath2)
{
    ui->label->setText(text);

    qDebug() << "Trying to load images from:" << imagePath1 << "and" << imagePath2;

    QPixmap pixmap1(imagePath1);
    if(pixmap1.isNull()) {
        qDebug() << "Failed to load image 1 from" << imagePath1;
    } else {
        ui->imageLabel1->setPixmap(pixmap1.scaled(200, 150, Qt::KeepAspectRatio));
    }

    QPixmap pixmap2(imagePath2);
    if(pixmap2.isNull()) {
        qDebug() << "Failed to load image 2 from" << imagePath2;
    } else {
        ui->imageLabel2->setPixmap(pixmap2.scaled(200, 150, Qt::KeepAspectRatio));
    }
}
