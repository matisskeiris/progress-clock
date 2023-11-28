#pragma once

#include <QTextDocument>
#include <QTimer>
#include <QWidget>

class ClockWidget : public QWidget {
    Q_OBJECT

    int _fontSize;

    QTimer* _timer;

public:
    ClockWidget(QWidget* parent);
    void paintEvent(QPaintEvent*) override;

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    static void fillClockTextDocument(QTextDocument& textDocument, const QDateTime& dateTime, const int textSize);
    static void fillDayOfTheWeekTextDocument(QTextDocument& textDocument, const QDateTime& dateTime, const int textSize);
    static void fillDateTextDocument(QTextDocument& textDocument, const QDateTime& dateTime, const int textSize);

};
