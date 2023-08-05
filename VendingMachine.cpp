#include <string>
#include <random>
#include "Appliance.h"

class PopMachine : public Appliance {

  //What makes pop machine unique from other appliances?
  //What does a pop machine need to do that a coin op 
  //dryer does not need to do?
  public:

  virtual void currency_processor(float amount) override {
    amount_paid += amount;
    std::cout<<"Amount paid: " << amount_paid << std::endl;
  }
  
  //needs to:
      //allow user to select soda
      //dispense soda
      //take user input

  void hold_temperature(float temp_to_hold) {
    //in practice, a PID loop would go here
    //to hold the temperature
  }


  void cancel_transaction(float amt_paid) {
    if(amt_paid > 0.0) {
     Appliance::currency_refunder(amt_paid); 
    }
    abort();
  }

  public:
    float amount_paid = 0.0;
};

class myPopMachine : public PopMachine {
//my unique pop machine with some special features:
    //It contains whatever sodas I want
    //I choose the price per soda
    //I set the temperature
    //takes the user input and dispenses soda at 
    //that location
public:

    void config() {  

    //method for owner of pop machine to configure settings 
    
      set_temp = 31.2; //temp to hold sodas at (F)
      hold_temperature(set_temp);
      
      std::string sodas[3] = {"Sprite", "Coke", "Fanta"};
      available_sodas[0] = sodas[0];
      available_sodas[1] = sodas[1];
      available_sodas[2] = sodas[2];

      //initialize global private list so sodas
      //are visible to the rest of the class
      
      set_soda_price(1.75);
    }

  void operation_mode() {

    config();
    
    PopMachine* pm = new PopMachine(); //Q about this
    float user_payment = 0;
    do {
      
      std::cout << "Insert Payment: " << std::endl;
      std::cin >> user_payment;
      if(user_payment == 0.0) {
        std::cout<< "Transaction canceled" << std::endl;
        pm->cancel_transaction(pm->amount_paid);
      }
      pm->currency_processor(user_payment);
      
    } while(pm->amount_paid < soda_price);
    
    //if we have exited do-while loop it is because
    //user entered enough money to receive a soda
    //or if the transaction was cancelled, which
    //stops the execution
    
    float amt_to_refund = pm->amount_paid - soda_price;
    Appliance::currency_refunder(amt_to_refund); //Q about this
    std::string soda_to_dispense = get_soda();
    std::cout << "Please take your " << soda_to_dispense << std::endl;
    
  }

  std::string get_soda() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0,2);

    int random_integer = distribution(gen);
    std::string soda_to_dispense = available_sodas[random_integer]; 

    return soda_to_dispense;
  }

  private:

    void set_soda_price(float owner_soda_cost) { //Q; is this the best way to approach this
      soda_price = owner_soda_cost;
      /*
      this private method exists so owner
      //of pop machine can set price of soda 
      //in public config method, but method 
      //exists privately so price per soda 
      can't be changed outside this class
      */

    }

    float set_temp; //temp to hold machine at (F)
    std::string available_sodas[3];
    float soda_price;

};

int main() { 
  myPopMachine* mpm = new myPopMachine();
  std::cout <<"Welcome to the random soda dispenser!" << std::endl;
  std::cout << "Insert $1.75 to receive a soda" << std::endl;
  mpm->operation_mode();
}
