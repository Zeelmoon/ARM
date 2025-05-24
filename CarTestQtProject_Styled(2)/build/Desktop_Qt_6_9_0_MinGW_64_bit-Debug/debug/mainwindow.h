#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QButtonGroup>
#include "testengine.h"
#include "result.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartButtonClicked();
    void onAnswerSelected(QAbstractButton *button);
    void onAnswerSelected(int id);

private:
    Ui::MainWindow *ui;
    TestEngine engine;
    QButtonGroup* buttonGroup;
    void loadQuestion();

    Result *result;
    void showTestResult();
};

#endif // MAINWINDOW_H
