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
    public:
        // constructors for the Shopping Cart class
        ShoppingCart(){
            vector<Item> cart;
        };
        ShoppingCart(vector<Item> carT){
            vector<Item> cart;
            cart = carT;
        };

    private:
        vector<Item> carT;
};


class UserAccount {
    private:
        string name;
        ShoppingCart cart;
        bool isGuest;
        float total;

    public:

        UserAccount(){
            name = "Guest";

        }
        UserAccount(string name, bool isMain);
        UserAccount(string name, ShoppingCart cart, float total, bool isGuest);

};

Item createItem(void);
Item editItem(Item item);
void printHeader(void);
void printItem(Item item);

int main(){

    Item Potato;
    Potato = editItem(Potato);
    printHeader();
    printItem(Potato);
    printHeader();
    return 1;
}


void printItem(Item item){
    cout << item.getName() << "\t" << item.getPrice() << "\t" << item.getQuantity();
}

void printHeader(void){
    cout << "\nItem\tPrice\tQuantity\n";
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
