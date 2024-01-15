#include "workerthread.h"

WorkerThread::WorkerThread(QObject *parent) : QThread(parent)
{
    m_process = new QProcess(this);
    connect(m_process, &QProcess::readyReadStandardOutput, this, [this]() {
        QString output = m_process->readAllStandardOutput();
        emit outputAvailable(output);
    });

    connect(m_process, &QProcess::readyReadStandardError, this, [this]() {
        QString output = m_process->readAllStandardError();
        emit errorAvailable(output);
    });

    m_commands.clear();
}

void WorkerThread::SetCommands(QStringList commands)
{
    m_commands.clear();
    m_commands = commands;
}

void WorkerThread::run()
{
    if (m_commands.count() == 0)
    {
        return;
    }

    // Execute QProcess here
    for (int i = 0; i < m_commands.count(); ++i) {
        m_process->start(m_commands[i]);
        m_process->waitForFinished(-1);

        emit finishedCommandNumber((i+1));
    }
}
