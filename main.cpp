#include <iostream> 
#include <vector>
#include <fstream>
#include <string>

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
        // ShoppingCart cart;
        vector<Item> cart;
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
        void setGuest(bool status){isGuest=status;};
        void setAdmin(bool status){isAdmin=status;};
        bool getAdmin(void){return isAdmin;};
        void add2Cart(Item item){cart.push_back(item);}
};

// continue as guest or login
int homeScreen(void);
// login to guest,user, or admin accounts
UserAccount login(bool isGuest);
// main screen for admin
bool adminScreen(void);
// main screen for other users
bool userScreen(UserAccount& current);
// creates an Item, adds to database
Item createItem(void);
// display items in items.txt in sets of 10
void displayItems(void);
// display a singular item
void printItem(Item item);
// print the item name, quantity, price header
void printHeader(void);
// write a user to the users.txt file
void writeUser(UserAccount user);
// write an item object to the inventory file
void writeItem(Item item);
// write the header to the inventory file and vector<Item> of all Items
void initInventory(void);
// write the header to the users file
void initUsers(void);
//search users.txt for name
bool searchUsers(string name);
// search items.txt for name, return quantity and price
int searchItems(string name);
// add items to shopping cart
void add2Cart(string name,int quantity, UserAccount& current);


int main(){
    int choice;
    bool done=0;
    UserAccount current;

    // initialize guest and admin accounts
    initUsers();
    while(!done){    
        // continue as guest or login
        choice = homeScreen();

        // login as guest
        if (choice ==1){current = login(1);done=userScreen(current);}
        
        // login as admin or user
        else if (choice==2){
            current = login(0);
            // if current account is admin, go to admin screen
            if(current.getAdmin()){done=adminScreen();}
            else{done=userScreen(current);}
        }
    }
    return 1;
}


void printItem(Item item){
    cout << "\n"<< item.getName() << "\t" << item.getPrice() << "\t" << item.getQuantity();
}

void printHeader(void){
    cout << "\nItem\t\tPrice\t\tQuantity\n";
}

int homeScreen(void){
    int choice;
    cout << "-----\nWelcome to CMart!\n-----\n\n(1) Continue as guest\n(2) Login/Make Account\n: ";
    cin >> choice;
    return choice;
}

bool adminScreen(void){
    int choice;
    bool done=0;

    while (done==0){
        cout << "What would you like to do?\n(1) Create Items\n(2) Clear Item Database\n(3) Display Items\n(4) Main Menu\n(6) Quit\n: ";
        cin >> choice;

        if(choice==1){
            bool another=1;
            while(another!=0){
                createItem();
                cout << "\nCreate Another Item?(type 0 for no/1 for yes)\n: ";
                cin >> another;
            }
        }
        else if(choice==2){
            initInventory();
        }
        else if(choice==3){displayItems();}
        else if(choice==4){return 0;}
        else if(choice==6){return 1;}
    }
    
}

bool userScreen(UserAccount& current1){
    int choice=0;

    while((choice!=6)&&(choice!=4)){
        string name="";
        int quantity=0;
        cout << "\nWhat would you like to do?\n(1) View Items\n(3) Add to Cart\n(4) Main Menu\n(6) Exit\n: ";
        cin >> choice;    
        switch(choice){
            case 1:
                displayItems();
                break;
            case 2:
                cout << "\nEnter the name of the item: ";
                cin >> name;
                searchItems(name);
                break;
            case 3:
                cout << "\nEnter the name of the item: ";
                cin >> name;
                cout << "\nEnter the quantity of the item: ";
                cin >> quantity;
                add2Cart(name,quantity,current1);
                break;
            case 4:
                return 0;
                //viewCart();
                // break;
            case 5:
                //checkOut();
                break;
            case 6:
                return 1;
            default:
                break;
        }
    }
}

void displayItems(void){
    ifstream file;
    string next;
    bool done=0;
    int count=0;
    char response;
    file.open("items.txt");

    printHeader();
    // skip heading in items.txt
    getline(file,next);
    getline(file,next);
    while(!done){
        if(file.eof()){
            cout << next <<"\nThat's all the items!";
            cin.get(response);
            cin.get(response);
            done=1;
            }
        else if(count<10){
            cout << next <<"\n";
            getline(file,next);
            count++;
        }
        else{
            cout << "\nType m for more or press enter: ";
            cin.get(response);
            cin.get(response);
            if(response=='m'){
                count=0;
            }
            else{done=1;}
        }
    }    
}

UserAccount login(bool isGuest){
    UserAccount useraccount;

    // set current account as guest
    if (isGuest){
        useraccount.setName("Guest");
        useraccount.setGuest(1);
        useraccount.setAdmin(0);
        return useraccount;
    }

    // go to login screen
    else{
        string name;
        int PIN, login=0;

        while (login==0){
            cout << "\nUsername: ";
            cin >> name;        
            if (name=="Admin"){
                cout << "\nPIN: ";
                cin >> PIN;
                // login as admin
                if (PIN == 1234){
                    useraccount.setName(name); 
                    useraccount.setGuest(0);
                    useraccount.setAdmin(1);
                    login=1;
                }
                else {cout << "\nIncorrect PIN\n";}
            }
            // login as another user   
            else {
                // search users.txt for name
                if (searchUsers(name)){
                    useraccount.setName(name);
                    useraccount.setGuest(0);
                    useraccount.setAdmin(0);
                    login=1;
                }
                else {
                    cout << "\nThat account does not exist, would you like to create it as a new account?(y/n)\n: ";
                    char response;
                    cin.get(response);
                    cin.get(response);
                    if (response=='y'){
                        // create user account w/ name
                        useraccount.setName(name);
                        useraccount.setGuest(0);
                        useraccount.setAdmin(0); 
                        writeUser(useraccount);   
                        login=1;
                    }
                    else{
                        // go back to login
                    }
                }
                
            }
        }
        return useraccount;
    }
    
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
    writeItem(newItem);
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

void writeUser(UserAccount user){
    ofstream file;
    file.open("users.txt",ios::app);
    file << "\n" << user.getName();
}

void writeItem(Item item){
    ofstream file;

    file.open("items.txt",ios::app);
    file << "\n" << item.getName() << "\t\t" << item.getPrice() << "\t\t" << item.getQuantity();
    file.close();   
}

void initInventory(void){
    ofstream file;
    file.open("items.txt");

    file << "Item\t\tPrice\t\tQuantity\n";
    file.close();
}

void initUsers(void){
    ofstream file;
    file.open("users.txt");

    file << "Name\n\nAdmin\nGuest";
    file.close();
}

bool searchUsers(string name){
    ifstream file;
    string query;
    bool isThere=0;
    bool done=0;
    file.open("users.txt");

    getline(file,query);
    while(!done){
        if (query==name){
            isThere=1;
        }
        if(file.eof()){
                done=1;
        }
        getline(file,query);
    }
    return isThere;

}

int searchItems(string name){
    ifstream file;
    string query;
    string queryn="";
    bool isThere=0;
    bool done=0;
    int quantity=0;
    file.open("items.txt");

    getline(file,query);
    while(!done){
        for(int i=0; i<size(query);i++){
            // write all alphanum into queryn
            if(!isalnum(query[i])){
                break;
            }
            else {
                queryn[i]=query[i];
                }
        }

        if (queryn==name){
            cout << query;
            isThere=1;
            done=1;
        }
        if(file.eof()){
                done=1;
        }
        getline(file,query);
        queryn="\0\0\0\0\0\0\0\0\0\0\0\0\0";
    }
    return quantity;
}

void add2Cart(string name,int quantity, UserAccount& current){
    Item item;
    item.setName(name);
    item.setQuantity(quantity);
    current.add2Cart(item);
}

// void testFunc(ofstream& file){
//     file << "Test";
// }