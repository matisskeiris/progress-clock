#pragma once

#include "progress_updater.hpp"

#include <QDateTime>
#include <QTimer>


class TimedProgressUpdater : public ProgressUpdater {
    Q_OBJECT

    QTimer _timer;
    int _durationMs;
    QDateTime _startTime;

public:
    TimedProgressUpdater(int durationMs, int interval) : _durationMs(durationMs), _startTime(QDateTime::currentDateTime()) {
        _timer.setInterval(interval);
        connect(&_timer, &QTimer::timeout, this, &TimedProgressUpdater::onTimeout);
    }

    void start() override {
        _timer.start();
    }

private slots:
    void onTimeout() {
        auto elapsed = _startTime.msecsTo(QDateTime::currentDateTime());

        int progress = elapsed * 100 / _durationMs;

        emit progressUpdated(std::min(100, progress));
        if (elapsed >= _durationMs) {
            _timer.stop();
            emit finished();
        }
    }

};
