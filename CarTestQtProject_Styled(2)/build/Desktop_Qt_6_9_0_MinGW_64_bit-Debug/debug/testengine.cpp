#include "testengine.h"
#include <QStringList>
#include <algorithm>
#include <random>
#include <ctime>

TestEngine::TestEngine() {
    // Пустой конструктор, можно ничего не писать
}

void TestEngine::init() {
    currentIndex = 0;
    scores.clear();

    questions = {
        {"1 из 20 - Как вы предпочитаете проводить свободное время?", {
                                                                {"Активно — спорт, походы, путешествия", EXPLORER_TYPE},
                                                                {"Спокойно — дома, в кругу близких", PRACTIC_TYPE},
                                                                {"В дороге — люблю быть в движении", DRIVER_TYPE},
                                                                {"В городе — встречи, кафе, тусовки", AESTHET_TYPE}
                                                            }},
        {"2 из 20 - Вы оказались в пробке на час. Что вы чувствуете?", {
                                                                {"Бешусь, время — деньги", DRIVER_TYPE},
                                                                {"Спокойно, включаю музыку или подкаст", PRACTIC_TYPE},
                                                                {"Строю альтернативные маршруты в голове", EXPLORER_TYPE},
                                                                {"Наслаждаюсь моментом", AESTHET_TYPE}
                                                            }},
        {"3 из 20 - Как вы относитесь к риску?", {
                                           {"Люблю рисковать", DRIVER_TYPE},
                                           {"Только если оправдан", PRACTIC_TYPE},
                                           {"Стараюсь избегать рисков", AESTHET_TYPE},
                                           {"Иногда риск — это шаг вперёд", EXPLORER_TYPE}
                                       }},
        {"4 из 20 - Что для вас важнее всего в автомобиле?", {
                                                        {"Скорость и мощность", DRIVER_TYPE},
                                                        {"Надежность и безопасность", PRACTIC_TYPE},
                                                        {"Комфорт и престиж", AESTHET_TYPE},
                                                        {"Экономичность и практичность", EXPLORER_TYPE}
                                                    }},
        {"5 из 20 - Представьте, вы едете ночью по трассе. Как вы себя чувствуете?", {
                                                                          {"Отлично, люблю ночные поездки", DRIVER_TYPE},
                                                                          {"Немного тревожно", PRACTIC_TYPE},
                                                                          {"Спокойно, дорога — мой элемент", EXPLORER_TYPE},
                                                                          {"Не люблю ночные поездки", AESTHET_TYPE}
                                                                      }},
        {"6 из 20 - Как вы относитесь к вниманию со стороны?", {
                                                         {"Люблю быть в центре", DRIVER_TYPE},
                                                         {"Пусть замечают, но не навязчиво", AESTHET_TYPE},
                                                         {"Предпочитаю оставаться в тени", PRACTIC_TYPE},
                                                         {"Всё зависит от настроения", EXPLORER_TYPE}
                                                     }},
        {"7 из 20 - Как бы вы описали свой характер?", {
                                                {"Импульсивный и энергичный", DRIVER_TYPE},
                                                {"Уравновешенный и логичный", PRACTIC_TYPE},
                                                {"Надежный и ответственный", AESTHET_TYPE},
                                                {"Спонтанный и креативный", EXPLORER_TYPE}
                                            }},
        {"8 из 20 - Какая музыка вам ближе?", {
                                         {"Рок или рэп", DRIVER_TYPE},
                                         {"Классика или джаз", AESTHET_TYPE},
                                         {"Поп, радио", PRACTIC_TYPE},
                                         {"Электронная или экспериментальная", EXPLORER_TYPE}
                                     }},
        {"9 из 20 - Вы едете по дороге, кто-то подрезал. Ваша реакция?", {
                                                                   {"Сигналю, догоняю", DRIVER_TYPE},
                                                                   {"Просто еду дальше", PRACTIC_TYPE},
                                                                   {"Думаю, как избежать таких ситуаций", AESTHET_TYPE},
                                                                   {"Чуть злюсь, но быстро отпускаю", EXPLORER_TYPE}
                                                               }},
        {"10 из 20 - Какая среда вам ближе?", {
                                        {"Большой город", AESTHET_TYPE},
                                        {"Пригород, частный дом", PRACTIC_TYPE},
                                        {"Деревня или природа", EXPLORER_TYPE},
                                        {"Постоянные поездки", DRIVER_TYPE}
                                    }},
        {"11 из 20 - Что вы выберете в сложной ситуации?", {
                                                    {"Быстрые действия", DRIVER_TYPE},
                                                    {"Анализ и план", PRACTIC_TYPE},
                                                    {"Совет с близкими", AESTHET_TYPE},
                                                    {"Следование интуиции", EXPLORER_TYPE}
                                                }},
        {"12 из 20 - Как вы решаете проблемы?", {
                                         {"Давлением, решительностью", DRIVER_TYPE},
                                         {"Рассудительностью", PRACTIC_TYPE},
                                         {"Терпением", AESTHET_TYPE},
                                         {"Креативными методами", EXPLORER_TYPE}
                                     }},
        {"13 из 20 - Вы больше экстраверт или интроверт?", {
                                                    {"Ярко выраженный экстраверт", DRIVER_TYPE},
                                                    {"Интроверт", AESTHET_TYPE},
                                                    {"Что-то между", PRACTIC_TYPE},
                                                    {"Зависят от ситуации", EXPLORER_TYPE}
                                                }},
        {"14 из 20 - Насколько для вас важен внешний вид машины?", {
                                                             {"Очень — чтобы все смотрели", AESTHET_TYPE},
                                                             {"Должен быть приятным, но не показным", PRACTIC_TYPE},
                                                             {"Главное — удобство", EXPLORER_TYPE},
                                                             {"Абсолютно не важно", DRIVER_TYPE}
                                                         }},
        {"15 из 20 - Сколько времени вы готовы тратить на уход за машиной?", {
                                                                     {"Как за любимым питомцем", AESTHET_TYPE},
                                                                     {"По необходимости", PRACTIC_TYPE},
                                                                     {"Минимум — мою редко", EXPLORER_TYPE},
                                                                     {"Лучше вообще не тратить", DRIVER_TYPE}
                                                                 }},
        {"16 из 20 - Какая фраза вам ближе?", {
                                     {"«Живи быстро»", DRIVER_TYPE},
                                     {"«Спокойствие — залог успеха»", PRACTIC_TYPE},
                                     {"«Движение — это жизнь»", EXPLORER_TYPE},
                                     {"«Главное — комфорт»", AESTHET_TYPE}
                                    }},
        {"17 из 20 - Как вы относитесь к новым технологиям в авто?", {
                                                              {"Обожаю — пусть всё будет 'умное'", AESTHET_TYPE},
                                                              {"Только если это реально полезно", PRACTIC_TYPE},
                                                              {"Старое — надежнее", EXPLORER_TYPE},
                                                              {"Главное — чтобы не мешало", DRIVER_TYPE}
                                                          }},
        {"18 из 20 - Вы любите планировать дальние поездки?", {
                                                       {"Да, готовлю маршрут заранее", PRACTIC_TYPE},
                                                       {"Только в общих чертах", AESTHET_TYPE},
                                                       {"Импровизирую по дороге", EXPLORER_TYPE},
                                                       {"Не люблю далеко ездить", DRIVER_TYPE}
                                                   }},
        {"19 из 20 - Если бы вы были машиной, то какой?", {
                                                  {"Мускул-кар", DRIVER_TYPE},
                                                  {"Немецкий седан", PRACTIC_TYPE},
                                                  {"Японский гибрид", AESTHET_TYPE},
                                                  {"Внедорожник", EXPLORER_TYPE}
                                              }},
        {"20 из 20 - Вы больше:", {
                           {"Ведущий — управляю ситуацией", DRIVER_TYPE},
                           {"Аналитик — всё просчитываю", PRACTIC_TYPE},
                           {"Миротворец — избегаю конфликтов", AESTHET_TYPE},
                           {"Искатель — всегда в поиске нового", EXPLORER_TYPE}
                       }}
    };
}

Question TestEngine::getCurrentQuestion() const {
    if (currentIndex >= 0 && currentIndex < questions.size()) {
        return questions[currentIndex];
    }
    return Question();
}

bool TestEngine::nextQuestion() {
    currentIndex++;
    return currentIndex < questions.size();
}

void TestEngine::addAnswer(PersonalityType type) {
    scores[type]++;
}

QVector<Car> TestEngine::getCarsForType(PersonalityType type) const {
    switch (type) {
    case DRIVER_TYPE:
        return {
            {"Subaru WRX STI", ":/images/images/wrxsti.jpg", 300, "Транспортный налог: ~45 000 ₽/год", "Годовые расходы: ~200 000–250 000 ₽"},
            {"BMW 5-й серии (530i)", ":/images/images/bmw5.jpg", 252, "Транспортный налог: ~37 800 ₽/год", "Годовые расходы: ~300 000 ₽"},
            {"Porsche Panamera (Turbo)", ":/images/images/panamera.jpg", 500, "Транспортный налог: ~75 000 ₽/год", "Годовые расходы: ~500 000–700 000 ₽"},
            {"Audi A5 (2.0 TFSI)", ":/images/images/a5.jpg", 190, "Транспортный налог: ~28 500 ₽/год", "Годовые расходы: ~250 000 ₽"}
        };

    case PRACTIC_TYPE:
        return {
            {"Toyota RAV4 (2.0, 149 л.с.)", ":/images/images/rav4.jpg", 149, "Транспортный налог: ~4 500 ₽/год", "Годовые расходы: ~130 000–150 000 ₽"},
            {"Skoda Octavia (1.4 TSI, 150 л.с.)", ":/images/images/octavia.jpg", 150, "Транспортный налог: ~4 500 ₽/год", "Годовые расходы: ~100 000–130 000 ₽"},
            {"Toyota Camry (2.5, 181 л.с.)", ":/images/images/camry.jpg", 181, "Транспортный налог: ~9 050 ₽/год", "Годовые расходы: ~300 000 ₽"},
            {"Volkswagen Tiguan (2.0 TSI, 180 л.с.)", ":/images/images/tiguan.jpg", 180, "Транспортный налог: ~27 000 ₽/год", "Годовые расходы: ~200 000–250 000 ₽"}
        };

    case AESTHET_TYPE:
        return {
            {"Tesla Model 3", ":/images/images/model3.jpg", 283, "Транспортный налог: ~42 450 ₽/год", "Годовые расходы: ~490 000 ₽"},
            {"Audi A6 (2.0 TFSI, 190 л.с.)", ":/images/images/a6.jpg", 190, "Транспортный налог: ~9 600 ₽/год", "Годовые расходы: ~189 225 ₽"},
            {"Mercedes-Benz C-Class (C200, 184 л.с.)", ":/images/images/cclass.jpg", 184, "Транспортный налог: ~27 600 ₽/год", "Годовые расходы: ~250 000–300 000 ₽"},
            {"Lexus ES (2.5, 200 л.с.)", ":/images/images/es.jpg", 200, "Транспортный налог: ~30 000 ₽/год", "Годовые расходы: ~250 000–300 000 ₽"}
        };

    case EXPLORER_TYPE:
        return {
            {"Jeep Wrangler (3.6, 285 л.с.)", ":/images/images/wrangler.jpg", 285, "Транспортный налог: ~42 750 ₽/год", "Годовые расходы: ~300 000–400 000 ₽"},
            {"Subaru Outback (2.5, 175 л.с.)", ":/images/images/outback.jpg", 175, "Транспортный налог: ~26 250 ₽/год", "Годовые расходы: ~200 000–250 000 ₽"},
            {"Toyota Land Cruiser Prado (2.7, 163 л.с.)", ":/images/images/prado.jpg", 163, "Транспортный налог: ~24 450 ₽/год", "Годовые расходы: ~127 646 ₽"},
            {"Ford Bronco (2.3 EcoBoost, 270 л.с.)", ":/images/images/bronco.jpg", 270, "Транспортный налог: ~40 500 ₽/год", "Годовые расходы: ~250 000–350 000 ₽"}
        };

    default:
        return {};
    }
}

QString TestEngine::getTypeDescription(PersonalityType type) const {
    switch (type) {
    case DRIVER_TYPE:
        return "Гонщик:\nЛюбит скорость, мощь, внимание\nЭнергичен, импульсивен, активен\nПредпочитает спорткары, купе, мощные хэтчбеки";
    case PRACTIC_TYPE:
        return "Практик:\nЦенит надёжность и безопасность\nСпокойный, рассудительный\nВыбирает седаны, кроссоверы, универсалы";
    case AESTHET_TYPE:
        return "Эстет:\nЛюбит комфорт и стиль\nОриентирован на престиж\nПредпочитает премиум-седаны, гибриды";
    case EXPLORER_TYPE:
        return "Исследователь:\nЛюбит приключения и поездки\nКреативный, гибкий, любит природу\nВыбирает внедорожники, кроссоверы, универсалы";
    default:
        return "Неизвестный тип";
    }
}

QString TestEngine::getResultText() const {
    auto types = getTopTwoResultTypes();
    auto cars1 = getCarsForType(types.first);
    auto cars2 = getCarsForType(types.second);

    auto typeName = [](PersonalityType type) {
        switch(type) {
        case DRIVER_TYPE: return "Гонщик";
        case PRACTIC_TYPE: return "Практик";
        case AESTHET_TYPE: return "Эстет";
        case EXPLORER_TYPE: return "Исследователь";
        default: return "Неизвестно";
        }
    };

    QString result = QString("Ваши типы: %1 и %2\n")
                         .arg(typeName(types.first))
                         .arg(typeName(types.second));

    if (!cars1.isEmpty() && !cars2.isEmpty()) {
        result += QString("Рекомендуемые автомобили: %1 и %2")
                      .arg(cars1.first().name)
                      .arg(cars2.first().name);
    }

    return result;
}

QPair<PersonalityType, PersonalityType> TestEngine::getTopTwoResultTypes() const {
    QVector<QPair<PersonalityType, int>> sortedScores;
    for (auto it = scores.begin(); it != scores.end(); ++it) {
        sortedScores.append(qMakePair(it.key(), it.value()));
    }

    std::sort(sortedScores.begin(), sortedScores.end(), [](auto a, auto b) {
        return a.second > b.second;
    });

    if (sortedScores.size() == 0) {
        return qMakePair(DRIVER_TYPE, DRIVER_TYPE);
    } else if (sortedScores.size() == 1) {
        return qMakePair(sortedScores[0].first, sortedScores[0].first);
    } else {
        return qMakePair(sortedScores[0].first, sortedScores[1].first);
    }
}
