#ifndef RESULT_H
#define RESULT_H

#include <QWidget>

namespace Ui {
class Result;
}

class Result : public QWidget
{
    Q_OBJECT
public:
    explicit Result(QWidget *parent = nullptr);
    ~Result();

    void setResultText(const QString &text);
    void setResultData(const QString& text, const QString& imagePath1, const QString& imagePath2);

signals:
    void windowClosed();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::Result *ui;
};

#endif // RESULT_H
