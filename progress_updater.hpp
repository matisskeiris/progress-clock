#pragma once

#include <QObject>

class ProgressUpdater : public QObject {
    Q_OBJECT

signals:
    void progressUpdated(int progress);
    void finished();

public:
    virtual void start() = 0;
};
