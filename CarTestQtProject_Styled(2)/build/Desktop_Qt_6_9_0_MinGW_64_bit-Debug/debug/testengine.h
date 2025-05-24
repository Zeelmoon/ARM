#ifndef TESTENGINE_H
#define TESTENGINE_H

#include <QString>
#include <QMap>
#include <QVector>

// Унифицированное перечисление для типов
enum PersonalityType {
    DRIVER_TYPE,
    PRACTIC_TYPE,
    AESTHET_TYPE,
    EXPLORER_TYPE
};

struct AnswerOption {
    QString text;
    PersonalityType type;
};

struct Question {
    QString text;
    QVector<AnswerOption> options;
};

struct Car {
    QString name;
    QString imagePath;
    int horsepower;
    QString taxText;
    QString annualCostText;
};

class TestEngine
{
public:
    TestEngine();

    void init();
    void addAnswer(PersonalityType type);
    bool nextQuestion();
    Question getCurrentQuestion() const;
    QString getResultText() const;
    QPair<PersonalityType, PersonalityType> getTopTwoResultTypes() const;
    QVector<Car> getCarsForType(PersonalityType type) const;
    QString getTypeDescription(PersonalityType type) const;

private:
    QVector<Question> questions;
    int currentIndex = 0;
    QMap<PersonalityType, int> scores;
};

#endif // TESTENGINE_H
