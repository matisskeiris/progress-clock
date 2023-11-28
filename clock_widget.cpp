#include "clock_widget.hpp"

#include <QDateTime>
#include <QLabel>
#include <QPainter>
#include <QTextCursor>
#include <QTimer>
#include <QVBoxLayout>

ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent) {
    auto currentDateTime = QDateTime::currentDateTime();

    _timer = new QTimer();
    _timer->setSingleShot(true);
    _timer->setInterval((60 - currentDateTime.time().second()) * 1000);

    connect(_timer, &QTimer::timeout, this, [=] {
        _timer->stop();
        repaint();

        delete _timer;
        _timer = new QTimer();
        _timer->setInterval(60 * 1000);

        connect(_timer, &QTimer::timeout, this, [=] { repaint(); });
        _timer->start();
    });

    _timer->start();
}

void ClockWidget::paintEvent(QPaintEvent *) {
    auto currentDateTime = QDateTime::currentDateTime();

    QPainter painter(this);

    QTextDocument clockTextDocument(this);
    QTextDocument dayOfTheWeekTextDocument(this);
    QTextDocument dateTextDocument(this);

    clockTextDocument.setDocumentMargin(0);
    dayOfTheWeekTextDocument.setDocumentMargin(0);
    dateTextDocument.setDocumentMargin(0);

    fillClockTextDocument(clockTextDocument, currentDateTime, _fontSize);
    fillDayOfTheWeekTextDocument(dayOfTheWeekTextDocument, currentDateTime, _fontSize * 0.4);
    fillDateTextDocument(dateTextDocument, currentDateTime, _fontSize * 0.4);

    int textHeight = clockTextDocument.size().height() + dayOfTheWeekTextDocument.size().height() + dateTextDocument.size().height();
    int topCornerX = (size().width() - clockTextDocument.idealWidth()) / 2;
    int topCornerY = (size().height() - textHeight) / 2;

    painter.translate(topCornerX, topCornerY);
    //painter.fillRect(QRectF(QPoint(0,0), clockTextDocument.size()), Qt::red);
    clockTextDocument.drawContents(&painter);

    painter.translate(0, clockTextDocument.size().height());
    dayOfTheWeekTextDocument.drawContents(&painter);

    painter.translate(0, dayOfTheWeekTextDocument.size().height());
    dateTextDocument.drawContents(&painter);
}

void ClockWidget::resizeEvent(QResizeEvent *event)
{
    auto width = std::min(size().width(), size().height());;
    int minSize = 1;
    int maxSize = width;

    do {
        _fontSize = minSize + (maxSize - minSize) / 2;
        QFont font;
        font.setWeight(QFont::Bold);
        font.setPointSize(_fontSize);
        QFontMetrics metrics(font);

        auto textWidth = metrics.horizontalAdvance("99:99");
        if (textWidth > width) {
            maxSize = _fontSize - 1;
        } else if (textWidth < width) {
            minSize = _fontSize + 1;
        } else {
            break;
        }
    } while (minSize + 1 < maxSize);
}

void ClockWidget::fillClockTextDocument(QTextDocument &textDocument, const QDateTime& dateTime, const int textSize) {
    QTextCursor cursor(&textDocument);

    QTextCharFormat format;
    format.setForeground(QColor(255, 255, 255));
    format.setFontWeight(QFont::Bold);
    format.setFontPointSize(textSize);

    cursor.insertText(dateTime.toString("hh") + ":", format);

    format.setFontWeight(QFont::Normal);
    cursor.insertText(dateTime.toString("mm"), format);
}

void ClockWidget::fillDayOfTheWeekTextDocument(QTextDocument &textDocument, const QDateTime& dateTime, const int textSize) {
    QTextCursor cursor(&textDocument);

    QTextCharFormat format;
    format.setForeground(QColor(255, 255, 255));
    format.setFontWeight(QFont::Bold);
    format.setFontPointSize(textSize);

    cursor.insertText(dateTime.toString("dddd"), format);
}

void ClockWidget::fillDateTextDocument(QTextDocument &textDocument, const QDateTime& dateTime, const int textSize) {
    QTextCursor cursor(&textDocument);

    QTextCharFormat format;
    format.setForeground(QColor(255, 255, 255));
    format.setFontPointSize(textSize);

    cursor.insertText(dateTime.toString("MMM d"), format);
}
