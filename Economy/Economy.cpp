#include <iostream>
#include <string>
#include <limits>
#include <vector>
void clear_screen() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}
std::string List = "1. Buy products\n2. Sell products\n3. Option\n4. Help\n5. Exit";
std::string Version = "V0.1 Economy Sim";
bool Devmode;
/*
Values needed to be found before doing the formula
    
    Bᵥ = D₀ / S₀


Formula for prices & How to run this

    P = (D / (S - Cₚ)) * (IBᵥ)

    { Demand Divided by Supply times by constant of 10 Equals the Price }

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
    static std::vector<Items*>& getAllItems() {
        static std::vector<Items*> allItems;
        return allItems;
    }
    Items(double Asupply, double Ademand, std::string Aname, int AitemID)
        : Name(Aname), Supply(Asupply), Demand(Ademand), ItemID(AitemID) {
        getAllItems().push_back(this);
    }
    int getItemID() const {
        return ItemID;
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

void Economy(int Option) {
    switch (Option) {
    case 1:
        // Add implementation for option 1
        break;
    case 2:
        // Add implementation for option 2
        break;
    case 3:
        // Add implementation for option 3
        break;
    case 4:
        // Add implementation for option 4
        break;
    default:
        std::cout << "You inputted an option that didn't exist" << std::endl;
        break;
    }
}

void initializeEconomy() {
    Items Item1(1.0, 1.0, "Planks", 1);
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

std::string EconomyHandler(int PlayerID, int ItemID, int Amount) {
    std::string Output;
    if (PlayerID == 0) {
        Devmode = true;
    }
    
     = Items::getAllItems();
    
    return Output;
}

void EconomyMain() {
    initializeEconomy();
    EconomyManager();
}

int main() {
    EconomyMain();
}
