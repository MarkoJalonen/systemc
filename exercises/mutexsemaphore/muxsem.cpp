#include <systemc.h>
#include <iostream>

// systemc offers mutexes and semaphores
// modelling software mutexes and semaphores

SC_MODULE(MuxSem){
    sc_mutex mutex;
    sc_semaphore semaphore;

    SC_CTOR(MuxSem) : semaphore(2)
    {
        SC_THREAD(thread1);
        SC_THREAD(thread2);
        SC_THREAD(thread3);
        SC_THREAD(thread4);
        SC_THREAD(thread5);
    }

    void thread1()
    {
        while (true)
        {
            if (mutex.trylock() == -1)
            {
                mutex.lock();
                std::cout << sc_time_stamp() << " : thread1 obtained mutex with lock()\n";
            }
            else 
            {
                std::cout << sc_time_stamp() << " : thread1 obtained mutex with trylock()\n";
            }
            // hold the mutex for one second
            wait(1, SC_SEC);
            mutex.unlock();
            std::cout << sc_time_stamp() << " : thread1 unlocked mutex\n";
            // time for other processes to lock the mutex
            wait(SC_ZERO_TIME);
        }
    }

    void thread2()
    {
        while (true)
        {
            if (mutex.trylock() == -1)
            {
                mutex.lock();
                std::cout << sc_time_stamp() << " : thread2 obtained mutex with lock()\n";
            }
            else 
            {
                std::cout << sc_time_stamp() << " : thread2 obtained mutex with trylock()\n";
            }
            // hold the mutex for one second
            wait(1, SC_SEC);

            mutex.unlock();
            std::cout << sc_time_stamp() << " : thread2 unlocked mutex\n";
            // time for other processes to lock the mutex
            wait(SC_ZERO_TIME);
        }
    }

    void thread3()
    {
        while (true)
        {
            // check if resource is available
            // if so obtain it
            if (semaphore.trywait() == -1)
            {
                // if not wait untill it is
                semaphore.wait();
            }
            std::cout << "\t" << sc_time_stamp() 
                << " : thread3 obtained a resource, value is now " 
                << semaphore.get_value() << std::endl;

            wait(1, SC_SEC);
            semaphore.post(); // free the resource
            std::cout << "\t" << sc_time_stamp() 
                << " : thread3 freed a resource, value is now " 
                << semaphore.get_value() << std::endl;   
            // give time for other processes to obtain the resource
            wait(SC_ZERO_TIME);
        }
    }

    void thread4()
    {
        while (true)
        {
            // check if resource is available
            // if so obtain it
            if (semaphore.trywait() == -1)
            {
                // if not wait untill it is
                semaphore.wait();
            }
            std::cout << "\t" << sc_time_stamp() 
                << " : thread4 obtained a resource, value is now " 
                << semaphore.get_value() << std::endl;

            wait(1, SC_SEC);
            semaphore.post(); // free the resource
            std::cout << "\t" << sc_time_stamp() 
                << " : thread4 freed a resource, value is now " 
                << semaphore.get_value() << std::endl;   
            // give time for other processes to obtain the resource
            wait(SC_ZERO_TIME);
        }
    }

    void thread5()
    {
        while (true)
        {
            // check if resource is available
            // if so obtain it
            if (semaphore.trywait() == -1)
            {
                // if not wait untill it is
                semaphore.wait();
            }
            std::cout << "\t" << sc_time_stamp() 
                << " : thread5 obtained a resource, value is now " 
                << semaphore.get_value() << std::endl;

            wait(1, SC_SEC);
            semaphore.post(); // free the resource
            std::cout << "\t" << sc_time_stamp() 
                << " : thread5 freed a resource, value is now " 
                << semaphore.get_value() << std::endl;   
            // give time for other processes to obtain the resource
            wait(SC_ZERO_TIME);
        }
    }
};

int sc_main(int argc, char** argv){
    MuxSem muxSem("muxSem");
    sc_start(10, SC_SEC);
    return 0;
}