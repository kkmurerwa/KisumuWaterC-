#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

/// Method declarations
int int_input_validator(int final_limit);
void choose_client();
void metered();
void un_metered();
void industry();
int raw_bill_calculator(int units_consumed);
int above_100_units_discount(int units_consumed);
void payment(int total_bill_payable);


int main(){
    choose_client();
    return 0;
}

int int_input_validator(int final_limit){
    /// Variable declaration
    string raw_input;
    int integer_input;
    bool not_int = false;

    /// Take use input
    cin>>raw_input;

    /// Check if input is integer
    for(int i = 0; i<raw_input.length(); i++){
        if (isdigit(raw_input[i]) == false){
            not_int = true;
            continue;
        }
    }

    /// Return value if input is not integer
    if (not_int){
        cout<<"Enter a valid input"<<endl;
        return 0;
    }

    /// Perform more tests if input is integer
    else{
        /// Use stingstream convert string input to int
        stringstream ss(raw_input);
        ss >> integer_input;

        /// Check if input is between 1 and 3 and return 0 if not
        if (integer_input > final_limit || integer_input < 1){
            cout<<"Enter a valid input"<<endl;
            return 0;
        }

        /// Return the input if value is in range
        else return integer_input;
    }
}

void choose_client(){
    /// Request user input
    cout<<"Select your client type"<<endl;
    cout<<"1. Metered\n2. Un-metered\n3. Industry"<<endl;

    /// Pass it through input validator first then save it to var choice
    int choice = int_input_validator(3);

    /// Perform actions based on the returned value
    switch (choice){
        case 0:
            choose_client();
            break;
        case 1:
            metered();
            break;
        case 2:
            un_metered();
            break;
        case 3:
            industry();
            break;
        default:
             cout<<"Unexpected error!!!"<<endl;
             exit(0);
             break;
    }
}

/// Bill calculations for metered clients
void metered(){
    int monthly_fee = 500;
    cout<<"Enter units consumed"<<endl;

    /// Pass input through validator
    int units_consumed = int_input_validator(100000);


    /// Check if input is invalid and perform some actions
    if (units_consumed == 0){
        metered();
    }

    /// The code below is run if input is valid
    int raw_bill = raw_bill_calculator(units_consumed);

    /// Calculate discounts
    int metered_discount = raw_bill * 0.1;
    int additional_discount = above_100_units_discount(units_consumed-100);
    int total_discount = metered_discount + additional_discount;

    /// Calculate total bill after discounts
    int total_bill_owed = raw_bill + monthly_fee - total_discount;

    /// Go to payments method
    payment(total_bill_owed);
}

/// Bill calculations for un-metered clients
void un_metered(){
    cout<<"Enter units consumed"<<endl;

    /// Pass input through validator
    int units_consumed = int_input_validator(100000);


    /// Check if input is invalid and perform some actions
    if (units_consumed == 0){
        metered();
    }

    /// The code below is run if input is valid
    int raw_bill = raw_bill_calculator(units_consumed);

    /// Calculate discounts
    int additional_discount = above_100_units_discount(units_consumed-100);

    /// Calculate total bill after discounts
    int total_bill_owed = raw_bill - additional_discount;

    /// Go to payments method
    payment(total_bill_owed);
}

/// Bill calculations for industry clients
void industry(){
    int units_consumed = 2500;
    int meter_fee = 500;

    /// Calculate raw bill
    int raw_bill = raw_bill_calculator(units_consumed);

    /// Calculate discounts
    int industry_discount = 0.9 * raw_bill;
    int additional_discount = above_100_units_discount(units_consumed-100);
    int total_discount = industry_discount + additional_discount;

    /// Calculate total bill after discounts
    int total_bill_owed = raw_bill + meter_fee - industry_discount;

    /// Go to payments method
    payment(total_bill_owed);
}

int raw_bill_calculator(int units_consumed){
    if (units_consumed > 150){
        return units_consumed*33;
    }
    else {
        return 150*33 + (units_consumed-149)*30;
    }
}

int above_100_units_discount(int units_consumed){
    return units_consumed * 0.92;
}

void payment(int total_bill_payable){
    cout<<"You are owed "<<total_bill_payable<<"."<<endl;
    cout<<"How do you want to pay the bill? (There is a 5% discount if you pay electronically)"<<endl;
    cout<<"1. Electronically(Visa)\n2. Cash"<<endl;
    int choice = int_input_validator(2);
    if (choice == 0){
        payment(total_bill_payable);
    }
    else {
        cout<<"Your total bill is: "<<total_bill_payable * 0.95<<endl;
        cout<<"Do you want to continue?\n1. Yes\n2. No"<<endl;
        int decision = int_input_validator(2);
        if (decision == 0){
            cout<<"You're dumb. System will now exit!!"<<endl;
            exit(0);
        }
        else if (decision == 1){
            choose_client();
        }
        else{
            exit(0);
        }
    }

}
