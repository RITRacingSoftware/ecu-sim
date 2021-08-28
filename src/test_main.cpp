#include "DummyEcu.h"
#include "Simulation.h"

using namespace ecusim;

int main()
{
    Simulation sim;
    DummyEcu dummy0("dummy 0");
    DummyEcu dummy1("dummy 1");
    DummyEcu dummy2("dummy 2");

    sim.add_ecu(&dummy0);
    sim.add_ecu(&dummy1);
    sim.add_ecu(&dummy2);

    sim.run_ms(1);
    dummy0.set("CAN", 0);
    dummy0.set("CAN", 1);
    dummy1.set("CAN", 2);
    dummy2.set("CAN", 3);

    sim.run_ms(1);

    return 0; 
}
