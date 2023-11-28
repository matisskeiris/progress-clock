#include "clock_widget.hpp"
#include "mainwindow.h"
#include "progress_widget.hpp"

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    _startTime(QDateTime::currentDateTime()),
    _progressUpdater(10 * 1000, 1000 / 24)
{
    setUpCentralWidget();
    setProgressWidget();
}

MainWindow::~MainWindow() {}

void MainWindow::setProgressWidget() {
    auto progressWidget = new ProgressWidget(this, &_progressUpdater);
    _centralWidgetLayout->addWidget(progressWidget);
    _currentWidget = progressWidget;

    connect(&_progressUpdater, &TimedProgressUpdater::finished, this, &MainWindow::setClockWidget);
    _progressUpdater.start();
}

void MainWindow::setClockWidget() {
    auto eff = new QGraphicsOpacityEffect(this);
    _currentWidget->setGraphicsEffect(eff);

    auto animation = new QPropertyAnimation(eff,"opacity");
    animation->setDuration(500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
    connect(animation, &QPropertyAnimation::finished, this, [=] {
        auto clockWidget = new ClockWidget(this);

        _centralWidgetLayout->replaceWidget(_currentWidget, clockWidget);

        auto eff = new QGraphicsOpacityEffect(this);
        clockWidget->setGraphicsEffect(eff);
        auto animation = new QPropertyAnimation(eff,"opacity");
        animation->setDuration(500);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->setEasingCurve(QEasingCurve::InOutQuad);

        animation->start(QPropertyAnimation::DeleteWhenStopped);

        delete _currentWidget;
        _currentWidget = clockWidget;
    });
}

void MainWindow::setUpCentralWidget()
{
    auto widget = new QWidget(this);
    setCentralWidget(widget);
    _centralWidgetLayout = new QVBoxLayout(this);
    widget->setLayout(_centralWidgetLayout);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    auto marginLeft = event->size().width() * 0.2;
    auto marginTop = event->size().height() * 0.2;
    setContentsMargins(marginLeft, marginTop, marginLeft, marginTop);

    QMainWindow::resizeEvent(event);
}
