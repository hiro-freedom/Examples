#include "workerthread.h"


WorkerThread *workerThread = new WorkerThread(this);
workerThread->SetCommands(m_commands);
connect(workerThread, &WorkerThread::finishedCommandNumber, this, &Cutter::on_command_finish);
workerThread->start();

