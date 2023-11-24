#include <iostream> 
#include <vector>

using namespace std;

class Item {

    private:
            string name;
            float price;
            int quantity;
    public:

        // constructors for the item class
        Item(){
            name="test";
            price=2.00;
            quantity=1;
        };
        Item(string namE, float pricE, int quantitY){
            name=namE;
            price=pricE;
            quantity=quantitY;
        };

        string getName(){return name;};
        float getPrice(){return price;};
        int getQuantity(){return quantity;};

        void setName(string namE){name=namE;};
        void setPrice(float pricE){price=pricE;};
        void setQuantity(int quantitY){quantity=quantitY;};
    
};

class ShoppingCart{
    private:
        // vector<Item> cart;

    public:
        // constructors for the Shopping Cart class
        ShoppingCart(){
            vector<Item> cart;
        };
        ShoppingCart(vector<Item> carT){
            cart = carT;
        };
        vector<Item> cart;
};


class UserAccount {
    private:
        string name;
        ShoppingCart cart;
        bool isGuest;
        bool isAdmin;
        float total;

    public:

        UserAccount(){
            name = "Guest";
        }
        UserAccount(string name, bool isMain);
        UserAccount(string name, ShoppingCart cart, float total, bool isGuest);

        void setName(string namE){name=namE;};
        string getName(){return name;};
};

int homeScreen1(void);
UserAccount loginScreen(bool isGuest);
ShoppingCart adminScreen(ShoppingCart inventory);
int homeScreen2(void);
Item createItem(void);
UserAccount checkAccount(UserAccount useraccount);
void displayInventory(ShoppingCart inventory);
void printItem(Item item);


int main(){
    int choice;
    UserAccount current;
    ShoppingCart inventory;

    //this part works great
    choice = homeScreen1();
    if (choice ==1){current = loginScreen(1);}
    else if (choice==2){
        current = loginScreen(0);
        inventory = adminScreen(inventory);
    }


    choice = homeScreen2();
    if (choice==1){displayInventory(inventory);}

    

    return 1;
}


void printItem(Item item){
    cout << "\n"<< item.getName() << "\t" << item.getPrice() << "\t" << item.getQuantity();
}

void printHeader(void){
    cout << "\nItem\tPrice\tQuantity\n";
}

int homeScreen1(void){
    int choice;
    cout << "Welcome to CMart!\n\n(1) Continue as guest\n(2) Login/Make Account\n: ";
    cin >> choice;
    return choice;
}

ShoppingCart adminScreen(ShoppingCart inventory){
    int choice;
    cout << "What would you like to do?\n(1) Create Items\n: ";
    cin >> choice;

    while(choice==1){
        inventory.cart.push_back(createItem());
        cout << "\nCreate Another Item?(type 1 for yes)\n: ";
        cin >> choice;
    }
    return inventory;
}

int homeScreen2(void){
    int choice;
    cout << "\nWhat would you like to do?\n(1) View Items\n(2) Search Items\n(3) View Cart\n(4) Check out\n: ";
    cin >> choice;
    return choice;
}

void displayInventory(ShoppingCart inventory){
    
    printHeader();
    for (int i=0;i<inventory.cart.size();i++){
        printItem(inventory.cart[i]);
    }
}

UserAccount loginScreen(bool isGuest){
    UserAccount useraccount;

    if (isGuest){useraccount.setName("Guest");return useraccount;}

    else{useraccount = checkAccount(useraccount);return useraccount;}
    
}

UserAccount checkAccount(UserAccount useraccount){
    string name;
    int PIN, login=0;

    while (login ==0){
        cout << "\nUsername: ";
        cin >> name;        
        if (name=="Admin"){
            cout << "\nPIN: ";
            cin >> PIN;
            if (PIN == 1234){useraccount.setName(name); login=1;}
            else {cout << "\nIncorrect PIN\n";}
        }   
        else {useraccount.setName(name);login=1;}
    }
    return useraccount;
}

UserAccount editUser(UserAccount useraccount){
    useraccount = checkAccount(useraccount);
    return useraccount;
}

Item createItem(void){
    string name;
    float price;
    int quantity;

    cout << "\nItem Name: ";
    cin >> name;

    cout << "Unit Price: ";
    cin >> price;

    cout << "Quantity: ";
    cin >> quantity;

    Item newItem(name,price,quantity);
    return newItem;
}

Item editItem(Item item){
    string name;
    float price;
    int quantity;
    int choice=0;
    bool finished=false;
    
    
    while (finished==false){
        cout << "\nWhich value would you like to change?\n(1)name\n(2)price\n(3)quantity\n(4)Finished\n: ";
        cin >> choice;
        while ((choice<1)||(choice>4)){
            cout << "Please input a number between 1 and 4";
            cout << "\nWhich value would you like to change?\n(1)name\n(2)price\n(3)quantity\n(4)Finished\n: ";
            cin >> choice;
        }
        switch (choice){
            case 1:
                cout << "New name: ";
                cin >> name;
                item.setName(name);
                break;
            case 2:
                cout << "New price: ";
                cin >> price;
                item.setPrice(price);
                break;
            case 3:
                cout << "New quantity: ";
                cin >> quantity;
                item.setQuantity(quantity);
                break;
            case 4:
                finished=true;
                break;
            default:
                break;
        }
    }
    return item;
}
