#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRadioButton>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QtGlobal>
#include <testengine.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    buttonGroup(new QButtonGroup(this)),
    result(new Result(this))
{
    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);


    buttonGroup->addButton(ui->answerButton1, 0);
    buttonGroup->addButton(ui->answerButton2, 1);
    buttonGroup->addButton(ui->answerButton3, 2);
    buttonGroup->addButton(ui->answerButton4, 3);

    connect(buttonGroup, SIGNAL(idClicked(int)), this, SLOT(onAnswerSelected(int)));
    engine.init(); // initialize questions
    loadQuestion();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAnswerSelected(QAbstractButton *button)
{
    Q_UNUSED(button);
    int id = buttonGroup->checkedId();
    onAnswerSelected(id); // Делегируем обработку
}

// Реализация для int
void MainWindow::onAnswerSelected(int id)
{
    qDebug() << "Selected answer ID:" << id;

    if (id < 0 || id >= 4) return;

    auto question = engine.getCurrentQuestion();
    if (id >= question.options.size()) return;

    engine.addAnswer(question.options[id].type);

    if (engine.nextQuestion()) {
        loadQuestion();
    } else {
        showTestResult();
    }
}

void MainWindow::loadQuestion()
{
    auto q = engine.getCurrentQuestion();
    ui->questionLabel->setText(q.text);

    ui->answerButton1->setText(q.options[0].text);
    ui->answerButton2->setText(q.options[1].text);
    ui->answerButton3->setText(q.options[2].text);
    ui->answerButton4->setText(q.options[3].text);

    buttonGroup->setExclusive(false);
    for (auto button : buttonGroup->buttons()) {
        button->setChecked(false);
    }
    buttonGroup->setExclusive(true);
}



void MainWindow::onStartButtonClicked()
{
    ui->startButton->hide();
    ui->startPage->hide();
    ui->testPage->show();

    ui->questionLabel->show();
    ui->answerButton1->show();
    ui->answerButton2->show();
    ui->answerButton3->show();
    ui->answerButton4->show();


    engine.init();
    loadQuestion();
}

#include <QTime>
#include <QtGlobal>
#include "testengine.h"
void MainWindow::showTestResult()
{
    if (!result) {
        result = new Result(this);
    }

    result->setWindowFlags(Qt::Window);
    result->setWindowModality(Qt::ApplicationModal);
    result->setAttribute(Qt::WA_DeleteOnClose, false);

    auto resultTypes = engine.getTopTwoResultTypes();
    auto cars1 = engine.getCarsForType(resultTypes.first);
    auto cars2 = engine.getCarsForType(resultTypes.second);

    if (!cars1.isEmpty() && !cars2.isEmpty()) {
        // Генерация случайных машин
        srand(static_cast<unsigned>(QTime::currentTime().msec()));
        Car randomCar1 = cars1[rand() % cars1.size()];
        Car randomCar2 = cars2[rand() % cars2.size()];

        // Описание типов личности
        QString desc1 = engine.getTypeDescription(resultTypes.first);
        QString desc2 = engine.getTypeDescription(resultTypes.second);

        // Описание машин
        QString carInfo1 = QString("%1\nМощность: %2 л.с.\n%3\n%4")
                               .arg(randomCar1.name)
                               .arg(randomCar1.horsepower)
                               .arg(randomCar1.taxText)
                               .arg(randomCar1.annualCostText);

        QString carInfo2 = QString("%1\nМощность: %2 л.с.\n%3\n%4")
                               .arg(randomCar2.name)
                               .arg(randomCar2.horsepower)
                               .arg(randomCar2.taxText)
                               .arg(randomCar2.annualCostText);

        // Финальный текст
        QString resultText = QString("Ваши типы:\n\n%1\n\n%2\n\nРекомендуемые автомобили:\n\n%3\n\n%4")
                                 .arg(desc1)
                                 .arg(desc2)
                                 .arg(carInfo1)
                                 .arg(carInfo2);

        result->setResultData(resultText, randomCar1.imagePath, randomCar2.imagePath);
    } else {
        result->setResultText("Тест завершён. Результат недоступен.");
    }

    result->show();
    this->hide();

    connect(result, &Result::windowClosed, this, &MainWindow::show);
}
