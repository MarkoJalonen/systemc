#include <systemc.h>
#include <iostream>

// three stages of systemc simulation:
// elaboration: data structs and connections, 
// execution: processes identified and placed into runnable set (or waiting), 
// and then the simulation is run: first evaluation of all processes one by one
// until wait() or return() then the time is advanced and evaluation repeated
// cleanup: when either max time, sc_stop(), or all processes have exited
// destroy objects, release memory and close opened files etc

// there are different callback functions called during these stages (explained below)

