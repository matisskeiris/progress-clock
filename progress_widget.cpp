#include "progress_widget.hpp"

#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTextCursor>
#include <QTextItem>
#include <QVBoxLayout>

ProgressWidget::ProgressWidget(QWidget *parent, ProgressUpdater* progressUpdater)
    : QWidget(parent) {
    connect(progressUpdater, &ProgressUpdater::progressUpdated, this, &ProgressWidget::setProgress);
}

void ProgressWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    auto circleDiameter = std::min(size().width(), size().height());

    paintProgressCircle(painter, circleDiameter);
    paintProgressText(painter, circleDiameter);
}

inline void ProgressWidget::paintProgressCircle(QPainter& painter, int circleDiameter) {
    // Progress bar pen should be 10% of with and be divisible by 2
    int brushWidth = circleDiameter / 10;
    brushWidth -= brushWidth % 2;
    // Take in account brush width
    circleDiameter -= brushWidth;

    QPainterPath path;
    path.moveTo(size().width()/2, (size().height() - circleDiameter) / 2);
    path.arcTo(
        QRectF(
            QPointF(
                (size().width() - circleDiameter)/2,
                (size().height() - circleDiameter)/2),
            QSize(circleDiameter, circleDiameter)),
        90,
        -360 * _progress / 100);

    QPen pen;
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);
    pen.setColor(QColor(0, 0, 0xbf));
    pen.setWidth(brushWidth);

    painter.strokePath(path, pen);
}

inline void ProgressWidget::paintProgressText(QPainter& painter, int circleDiameter) {
    int percentageTextSize = circleDiameter * 0.15;

    QTextDocument percentageTextDocument(this);
    QTextDocument initializingTextDocument(this);

    fillPercentageTextDocument(percentageTextDocument, percentageTextSize);
    fillInitializedTextDocument(initializingTextDocument, percentageTextSize * 0.4);

    int textHeight = percentageTextDocument.size().height() + initializingTextDocument.size().height();

    painter.translate(
        (size().width() - percentageTextDocument.idealWidth()) / 2,
        (size().height() - textHeight) / 2);
    percentageTextDocument.drawContents(&painter);

    painter.resetTransform();
    painter.translate(
        (size().width() - initializingTextDocument.idealWidth()) / 2,
        ((size().height() - textHeight) / 2) + percentageTextDocument.size().height());
    initializingTextDocument.drawContents(&painter);
}

inline void ProgressWidget::fillPercentageTextDocument(QTextDocument &textDocument, int textSize) {
    QTextCursor cursor(&textDocument);

    QTextCharFormat format;
    format.setForeground(QColor(255, 255, 255));
    format.setFontWeight(QFont::Bold);
    format.setFontPointSize(textSize);

    cursor.insertText(QString::number(_progress), format);

    format.setFontWeight(QFont::Normal);
    format.setFontPointSize(textSize * 0.6);
    cursor.insertText("%", format);
}

inline void ProgressWidget::fillInitializedTextDocument(QTextDocument &textDocument, int textSize) {
    QTextCursor cursor(&textDocument);

    QTextCharFormat format;
    format.setForeground(QColor(255, 255, 255));
    format.setFontPointSize(textSize);

    cursor.insertText("INITIALIZING", format);
}
