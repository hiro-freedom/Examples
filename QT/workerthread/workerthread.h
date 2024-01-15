#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QProcess>
#include <QThread>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent = nullptr);

    void SetCommands(QStringList commands);

protected:
    void run() override;

signals:
    void outputAvailable(QString output);
    void errorAvailable(QString output);
    void finishedCommandNumber(int number);

private:
    QProcess *m_process;
    QStringList m_commands;
};

#endif // WORKERTHREAD_H
