#include <iostream>
#include <string.h>
using  namespace std;

class Book{
private:
    string title, author;
    float price;
    int stock;
public:
    void setData( Book*,int);
    void getData( Book*,int);
    void buy( Book*,int);
    bool search(int, Book*, char);
};

bool isNumberString(const string& s) {
    int len = s.length();
    for (int i = 0; i < len; i++) {
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

bool creditCard(){
    string card;
    enterCard:
    cout<<"Enter 0 if you want to cancel your transaction or,\n";
    cout<<"Enter your card number: ";
    getline(cin,card);
    if(card == "0"){
        return false;
    }
    else if ((!isNumberString(card)) || (card.length() != 16) || card[0]!='4') {
        cout << "Invalid Card\n\n";
        goto enterCard;
    }

    int size = card.length();
    int doubleEvenSum = 0;

    for( int i = size-2 ; i >=0 ; i-=2 ) {
        int sum = (card[i] - 48)*2;
        if(sum>9){
            sum = (sum/10) + (sum%10);
        }
        doubleEvenSum += sum;
    }

    for( int i=size-1 ; i >=0 ; i-=2 ) {
        doubleEvenSum += card[i]-48;
    }

    if(doubleEvenSum%10==0) {
        return true;
    }
    else{
        cout<<"Invalid Card\n\n";
        goto enterCard;
    }
}

void Book :: setData(Book b[],int j){//j is the index number of the object
    cout<<"Enter book title     : ";
    getline(cin,b[j].title);
    cout<<"Enter Author name    : ";
    getline(cin,b[j].author);
    cout<<"Enter no. of pieces  : ";
    cin>>b[j].stock;
    cout<<"Enter price : ";
    cin>>b[j].price;
    cin.ignore();//every time after entering an integer, have to ignore the ENTER
}
void Book :: getData(Book b[],int j){
    cout<<"Title  : "<<b[j].title<<endl;
    cout<<"Author : "<<b[j].author<<endl;
    cout<<"Price  : "<<b[j].price<<endl;
    cout<<"Piece  : "<<b[j].stock<<endl;
}
void Book :: buy(Book b[],int j){
    int piece;
    cout<<"Enter number of pieces       : ";
    cin>>piece;
    cin.ignore();
    if(b[j].stock >= piece){
        cout<<"Total price: "<<piece*b[j].price<<"\n";
        if(creditCard()){
            cout<<"Thanks for your purchase\n";
            b[j].stock-=piece;
        }
        cout<<"We wish you visit us again\n";
    }
    else{
        cout<<"Sorry, not enough in stock\n";
    }
}
bool Book :: search(int i,Book b[], char call){
    char bTitle[20], bAuth[30];
    cout<<"Enter the Title of the book  : ";
    cin.getline(bTitle,20);
    cout<<"Enter the Author of the book : ";
    cin.getline(bAuth,30);

    cout<<"Showing result for \""<<bTitle<<"\" by "<<bAuth<<endl;

    for( int j=0 ; j<i ; j++ ){
        if( b[j].author==bAuth && b[j].title==bTitle){
            if(call=='2'){
                buy(b,j);
                cout<<"Press ENTER to continue\n";
                cin.ignore();
            }
            else if(call=='3'){
                getData(b,j);
                cout<<"Press ENTER to continue\n";
                cin.ignore();
            }
            else if(call=='4'){
                setData(b,j);
                cout<<"Press ENTER to continue\n";
                cin.ignore();
            }
            return true;
        }
    }
    return false;
}

void menu(){
    cout<<"1. Enter a book to the stock\n";
    cout<<"2. Buy a book\n";
    cout<<"3. Search a book\n";
    cout<<"4. Edit book info\n";
    cout<<"5. Exit\n";
}
int main(){
    Book B[20];
    int i=0;
    char choice;
    do{
        menu();
        cout<<"Enter your choice: ";
        cin>>choice; cin.ignore();
        system("cls");

        if(choice=='1'){
            B[i].setData(B,i);
            cout<<"Press ENTER to continue\n";
            cin.ignore();
            i++;
            system("cls");
        }
        else if(choice=='2' || choice=='3' || choice=='4'){
            if(!(B[i].search(i,B,choice))){//if there is no book as given, the function will return false
                system("cls");
                cout<<"No such book found\n";
            // !false = true | since "Book not found" will be printed
            }
        }
        else if(choice!='5'){
            system("cls");
            cout<<"Enter a valid choice\n";
        }
    }while(choice!='5');    

    return 0;
}