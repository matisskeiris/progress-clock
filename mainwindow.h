#pragma once

#include "timed_progress_updater.hpp"

#include <QDateTime>
#include <QMainWindow>
#include <QResizeEvent>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTimer _timer;
    int _duration = 10 * 1000;
    QDateTime _startTime;

    QLayout* _centralWidgetLayout;
    QWidget* _currentWidget;

    TimedProgressUpdater _progressUpdater;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void setUpCentralWidget();
    void setProgressWidget();
    void setClockWidget();
};
