#include <QDebug>
#include <QString>
#include <QTimer>
#include <thread>
#include <chrono>
#include <QCoreApplication>
#include <QMutex>

extern void burnCPU();
extern void pureCPUBurn(int num_threads);

int main(int a, char **b)
{
    QCoreApplication app(a, b);

    QString option;
    if (app.arguments().size() > 1)
        option = app.arguments().at(1);

    if (option == "1-thread-burn") {
        pureCPUBurn(1);
    } else if (option == "2-thread-burn") {
        pureCPUBurn(2);
    } else if (option == "half-thread-burn") {
        burnCPU();
    } else if (option == "sleep") {
        qDebug() << "Sleeping";
        std::this_thread::sleep_for(std::chrono::seconds(3600));
    } if (option == "mutex") {
        QMutex m;
        qDebug() << "Locking...";
        m.lock();
        m.lock();
    } else {
        qDebug() << "Unknown option. Possible values: 1-thread-burn, 2-thread-burn, mutex, sleep, half-thread-burn";
        return 1;
    }

    return app.exec();
}
