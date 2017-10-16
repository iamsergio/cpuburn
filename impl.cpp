#include <mutex>
#include <thread>
#include <vector>
#include <atomic>

#include <QDebug>

using namespace std;

static mutex s_mutex;
static bool s_continue = true;

#define IDLE_TIME 1
#define BURN_TIME 1

void burn1Core()
{
    while (1) {}
}


void pureCPUBurn(int num_threads)
{
    std::vector<thread> threads;
    for (int i = 0; i < num_threads; ++i)
    {
        thread t(burn1Core);
        threads.push_back(move(t));
    }
    threads[0].join();
}
std::atomic<bool> s_lock = ATOMIC_FLAG_INIT;
void burnCPUThread()
{
    while (s_lock) { }
}

void burnCPU()
{
    while (true)
    {
        s_lock.store(true);
        thread t(burnCPUThread);

        {
            this_thread::sleep_for(std::chrono::seconds(BURN_TIME));
            s_lock.store(false);
        }

        t.join();
        qDebug() << "Sleeping";
        std::this_thread::sleep_for(std::chrono::seconds(IDLE_TIME));
        qDebug() << "Starting";
    }
}
