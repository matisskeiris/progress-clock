#pragma once

#include "progress_updater.hpp"

#include <QDateTime>
#include <QTextDocument>
#include <QTimer>
#include <QWidget>

class ProgressWidget : public QWidget {
    Q_OBJECT

    int _progress = 0;

public:
    ProgressWidget(QWidget* parent, ProgressUpdater* progressUpdater);
    void paintEvent(QPaintEvent*) override;

private slots:
    void setProgress(int progress) {
        _progress = progress;
        repaint();
    }

private:
    void fillPercentageTextDocument(QTextDocument& textDocument, int textSize);
    void fillInitializedTextDocument(QTextDocument& textDocument, int textSize);
    void paintProgressCircle(QPainter &painter, int circleDiameter);
    void paintProgressText(QPainter &painter, int circleDiameter);
};
