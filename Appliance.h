#include <iostream>

// Appliance interface, contains pure virtual methods
// that I promise to implement in a subclass somewhere
// Contains methods any appliance would have
// Examples include:
//     coin op washer, food vending machine
//     soda vending machine, coin op dryer

class IAppliance {
public:
  virtual float currency_receiver(float amount) = 0;
  virtual void currency_refunder(float amount) = 0;
  virtual void maint_mode() = 0;
};

//Abstract class, implement methods from interface and
//methods unique to pop machines, but not unique to a 
//specific pop machine

class Appliance: public IAppliance {
  public:

    virtual void currency_processor(float amount) = 0;
    
    virtual float currency_receiver(float amount_received) override {
      return amount_received;
    }
    
    virtual void currency_refunder(float refund_amount) override {
      std::cout << "Please take change: " << refund_amount << std::endl;
    }

    void maint_mode() override {
      //need a clean way to implement a maintinence mode 
      //that stops all operations on appliance
      abort();
      //whenever this funciton is called, execution of
      //the program will be stopped so no user input
      //will be taken
    }
};
