#include <systemc>
#include <iostream>

// systemc provides a primitive channel with fifo behavior
// its fifo type inteface provides blocking and non blocking reads and writes
// channel also has events for read and write

SC_MODULE(Fifo)
{
    // create a fifo with int type slots
    sc_core::sc_fifo<int> fifo;
    SC_CTOR(Fifo) : fifo(2) // and give it two slots
    {
        SC_THREAD(writer1);
        SC_THREAD(reader1);
        SC_THREAD(reader2);
    }

    void writer1()
    {
        int value = 1;
        while (true)
        {
            fifo.write(value); // blocking
            std::cout << sc_core::sc_time_stamp()
                << " : writer1 wrote " << value++
                << " to the buffer\n";
            wait(3, sc_core::SC_SEC);
        }
    }

    void reader1() 
    {
        wait(sc_core::SC_ZERO_TIME);
        int value = 0;
        while (true)
        {
            fifo.read(value); // blocking, same as value = fifo.read();
            std::cout << sc_core::sc_time_stamp()
                << " : reader1 read " << value
                << " from the buffer\n";
            wait(2, sc_core::SC_SEC);
        }
    }

    void reader2()
    {
        wait(sc_core::SC_ZERO_TIME);
        int value = 0;
        while (true)
        {
            while (fifo.nb_read(value) == false) // non blocking
            {
                std::cout << sc_core::sc_time_stamp()
                    << " : reader2 tried reading an empty buffer\n";
                wait(fifo.data_written_event());
            }

            std::cout << sc_core::sc_time_stamp()
                << " : reader2 read " << value
                << " from the buffer\n";
            wait(3, sc_core::SC_SEC);
        }
    }
};

int sc_main(int argc, char** argv)
{
    Fifo fifo("fifo");
    sc_core::sc_start(10, sc_core::SC_SEC);
    return 0;
}