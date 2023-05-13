#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <map>
#include <unordered_map>
void clear_screen() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}
void wait_for_enter() {
#ifdef _WIN32
    system("pause");
#else
    system("clear");
#endif
}
std::string List = "1. Buy products\n2. Sell products\n3. Option\n4. Help\n5. Exit";
std::string Version = "V0.1 Economy Sim";
bool Devmode;


// Map PlayerID to their money
std::map<int, double> playerMoney;

// Map PlayerID to their inventory, which is another map of ItemID to the amount of that item they own
std::map<int, std::unordered_map<int, int>> playerInventory;

/*
Values needed to be found before doing the formula
    
    Bᵥ = D₀ / S₀


Formula for prices & How to run this

    P = (D / (S - Cₚ)) * (IBᵥ)

    { Supply minus Production cost which is than the demand gets divided by the new supply before multiplying, Inflation Times Base Value which than, we multiple the two numbers founded which equals the price }

    IF no Supply than
    - Product is unavailable
    IF Someone buys than
    - Demand Increases
    - Supply Decreases a little
    IF someone sells than
    - Demand Stays same
    - Supply Increases
    IF no one buys or sells than
    - Demand goes back to normal
    - Supply goes back to normal
*/

class Items {
public:
    std::string Name;
    double Supply;
    double Demand;
    int ItemID;
    double Price;
    double Bv;  // Initial base value
    double ProductionCost;  // The cost to produce the item
    double Inflation;  // The rate of inflation

    static std::vector<Items*>& getAllItems() {
        static std::vector<Items*> allItems;
        return allItems;
    }
    int getItemID() const {
        return ItemID;
    }

    Items(double Asupply, double Ademand, std::string Aname, int AitemID, double AproductionCost, double Ainflation)
        : Name(Aname), Supply(Asupply), Demand(Ademand), ItemID(AitemID), ProductionCost(AproductionCost), Inflation(Ainflation) {
        Bv = Demand / Supply;  // Calculate the initial base value
        Price = calculatePrice();
        getAllItems().push_back(this);
    }

    void setSupply(double newSupply) {
        Supply = newSupply;
        valueChanged();
    }

    void setDemand(double newDemand) {
        Demand = newDemand;
        valueChanged();
    }

private:
    void valueChanged() {
        Price = calculatePrice();
    }

    double calculatePrice() {
        double adjustedSupply = Supply - ProductionCost;
        double demandOverSupply = Demand / adjustedSupply;
        return demandOverSupply * (Inflation * Bv);
    }
};

std::vector<Items> itemList;

void FindItem(int ItemID) {
    std::vector<Items*>& allItems = Items::getAllItems();
    for (auto& item : allItems) {
        if (item->ItemID == ItemID) {
            // Do something with the found item...
            break;
        }
    }
}

bool Buy(int ItemID) {
    return false;
}

bool Sell(int ItemID) {
    return false;
}
std::string EconomyHandler(int PlayerID, int ItemID, int Amount, std::string Action) {
    std::string Output;
    if (PlayerID == 0) {
        Devmode = true;
    }

    std::vector<Items*>& allItems = Items::getAllItems();
    for (auto& item : allItems) {
        if (item->ItemID == ItemID) {
            if (Action == "Buy") {
                if (item->Supply < Amount) {
                    Output = "Insufficient supply to buy.";
                    wait_for_enter();
                }
                else {
                    double cost = item->Price * Amount;
                    if (playerMoney[PlayerID] < cost) {
                        Output = "Insufficient funds to buy.";
                        wait_for_enter();
                    }
                    else {
                        playerMoney[PlayerID] -= cost;
                        item->setSupply(item->Supply - Amount);
                        playerInventory[PlayerID][ItemID] += Amount;
                        Output = "Successfully bought " + std::to_string(Amount) + " " + item->Name;
                        wait_for_enter();
                    }
                }
            }
            else if (Action == "Sell") {
                if (playerInventory[PlayerID][ItemID] < Amount) {
                    Output = "Insufficient items to sell.";
                    wait_for_enter();
                }
                else {
                    playerMoney[PlayerID] += item->Price * Amount;
                    item->setSupply(item->Supply + Amount);
                    playerInventory[PlayerID][ItemID] -= Amount;
                    Output = "Successfully sold " + std::to_string(Amount) + " " + item->Name;
                    wait_for_enter();
                }
            }
            else {
                Output = "Invalid action.";
                wait_for_enter();
            }
            break;
        }
    }

    return Output;
}

void Economy(int Option) {
    int ItemID, Amount;
    std::string Action;
    switch (Option) {
    case 1:
        std::cout << "Enter the ID of the item you want to buy: ";
        std::cin >> ItemID;
        std::cout << "Enter the amount you want to buy: ";
        std::cin >> Amount;
        Action = "Buy";
        std::cout << EconomyHandler(0, ItemID, Amount, Action) << std::endl;
        break;
    case 2:
        std::cout << "Enter the ID of the item you want to sell: ";
        std::cin >> ItemID;
        std::cout << "Enter the amount you want to sell: ";
        std::cin >> Amount;
        Action = "Sell";
        std::cout << EconomyHandler(0, ItemID, Amount, Action) << std::endl;
        break;
    case 3:

        break;
    case 4:

        break;
    default:
        std::cout << "You inputted an option that didn't exist" << std::endl;
        break;
    }
}


void initializeEconomy() {
    Items Item1(1.0, 1.0, "Planks", 1, 0.5, 1);
}

void displayMenu() {
    std::cout << "Hello User!" << std::endl;
    std::cout << "I am " << Version << "." << std::endl;
    std::cout << "I am able to do trades for you!" << std::endl;
    std::cout << "If you want, you can very well create products to sell!" << std::endl;
    std::cout << "Need support? Make sure you read the Help option and you will be able to do anything you want with this program!" << std::endl;
    std::cout << std::endl;
    std::cout << "Please select an option:" << std::endl;
    std::cout << List << std::endl;
}

int getInput() {
    int input;
    std::cin >> input;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        input = -1;
    }

    return input;
}

void EconomyManager() {
    bool done;

    do {
        clear_screen();
        displayMenu();
        int input = getInput();
        done = true;

        switch (input) {
        case 1:
            std::cout << "Buy" << std::endl;
            Economy(1);
            break;
        case 2:
            std::cout << "Sell" << std::endl;
            Economy(2);
            break;

        case 3:
            std::cout << "Option" << std::endl;
            break;
        case 4:
            std::cout << "Help" << std::endl;
            break;
        case 5:
            std::cout << "Exiting..." << std::endl;
            exit(EXIT_SUCCESS);
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            done = false;
            break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line

    } while (!done || done);
}




void EconomyMain() {
    initializeEconomy();
    EconomyManager();
}

int main() {
    EconomyMain();
}
