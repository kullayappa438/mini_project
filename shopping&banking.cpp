#include<iostream>
#include<cstring>
#include<limits>
using namespace std;
class Bank;
class Shopping
{
        static int cnt;
        struct Product
        {
                string name;
                float price;
                int quantity;
        };
        int totalItems;
        float totalAmount;
        public:
        void billing(Bank &,Product *ptr);
        void Itembilling(Bank &);
        bool verifyPassword(Bank &);
        void addToCart(Product *ptr);
        void viewCart(Product *ptr);
        void deleteItem(Product *ptr);
        friend class Bank;
};
int Shopping::cnt=0;
class Bank
{
        int accountno;
        float balance;
        string name,password,email;
        struct address
        {
                int houseNo,pincode;
                string street,city,state;
        };
        address addr;
        private:
        //bool verifyPassword();
        friend bool Shopping::verifyPassword(Bank &);
        public:
        friend void Shopping::Itembilling(Bank &);
        Bank();
bool verifyPassword();
        void menu();
        friend void Shopping::billing(Bank &,Product *ptr);
        void AccDetails();
        void Deposit();
        void Withdraw();
         ~Bank();
        void BalEnq();
};
void Shopping::Itembilling(Bank &bobj)
{
        Product product[20];
        char choice;
        cout<<"----Shopping Menu----"<<endl;
        cout<<"1.Add to Cart"<<endl;
        cout<<"2.View Cart"<<endl;
        cout<<"3.Delete Item"<<endl;
        cout<<"4.Billing"<<endl;
        while(1)
        {
                cout<<"Enter the choice:";
                cin>>choice;
                switch(choice)
                {
                case'1':addToCart(product);
                        break;
                case'2':viewCart(product);
                        break;
                case'3':deleteItem(product);
                        break;
                case'4':billing(bobj,product);
                        break;
                case'5':
               default:exit(0);
                }
        }
}
void Shopping::addToCart(Product *ptr)
{
        float amt=0;
 if(cnt==21)
        {
                cout<<"Cart is full"<<endl;
        }
        else
        {
                cout<<"Enter the product:"<<endl;
                cin>>ptr[cnt].name;
                cout<<"Enter the price:"<<endl;
                cin>>ptr[cnt].price;
                cout<<"No.of products:"<<endl;
                cin>>ptr[cnt].quantity;
                cout<<"Added Item:"<<ptr[cnt].name<<","<<"Price:"<<ptr[cnt].price<<","<<"Quantity:"<<ptr[cnt].quantity<<endl;
                cout<<"Item added successfully"<<endl;
                cnt++;
        }
}
void Shopping::viewCart(Product *ptr)
{
        float total=0;
        totalAmount=0;
        if(cnt==0)
        {
                cout<<"cart is empty"<<endl;
        }
        else
        {
                for(int i=0;i<cnt;i++)
                {
                        total=(ptr[i].price)*(ptr[i].quantity);
                        cout<<i+1<<"."<<ptr[i].name<<"|"<<"Price:"<<ptr[i].price<<"|"<<"Quantity:"<<ptr[i].quantity<<"|"<<"TotalAmount:"<<total<<endl;
                        totalAmount+=total;
                }
        cout<<"Total Amount:"<<totalAmount<<endl;
}
}
void Shopping::deleteItem(Product *ptr)
{
        int productNo;
        cout<<"Enter the Item No:";
        cin>>productNo;
 if(cnt<productNo)
        {
                cout<<"Insufficient products"<<endl;
        }
        else
        {
        memmove(ptr+productNo-1,ptr+(productNo-1)+1,(cnt-(productNo-1)-1)*sizeof(Product));
        cnt--;
        }
}
void Shopping::billing(Bank &obj,Product *ptr)
{
        if(totalAmount>obj.balance)
        {
                cout<<"Insufficient balance"<<endl;
                cout<<"Remove any Item"<<endl;
                cout<<"Remaining Balance:"<<obj.balance<<endl;
        }
        else if(verifyPassword(obj)==1)
        {
                obj.balance-=totalAmount;
                cout<<"Billing Successful!Amount deducted:"<<totalAmount<<endl;
                cout<<"Remaining Balance:"<<obj.balance<<endl;
        while(cnt>0)
        {
        memmove(ptr,ptr+1,(cnt-1)*sizeof(Product));
        cnt--;
        }
        cout<<"Cart is now Empty."<<endl;
        exit(0);
        }
        else
                cout<<"Retry the correct password"<<endl;
}
bool Shopping::verifyPassword(Bank &obj)
{
        string pass;
        cout<<"Enter the password for verification:"<<endl;
        cin>>pass;
        if(pass==obj.password)
                return 1;
        else
 return 0;
}
Bank::Bank()
{

        cout<<"Welcome to the Bank&Shopping System"<<endl;
        cout<<"Enter the accountno:"<<endl;
        cin>>accountno;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"Enter the name:"<<endl;
        getline(cin,name);
        cout<<"Enter the emailId:"<<endl;
        getline(cin,email);
        cout<<"Enter the address:"<<endl;
        cout<<"houseNo:"<<endl;
        cin>>addr.houseNo;
        cout<<"street:"<<endl;
        cin>>addr.street;
        cout<<"city:"<<endl;
        cin>>addr.city;
        cout<<"state:"<<endl;
        cin>>addr.state;
        cout<<"pincode:"<<endl;
        cin>>addr.pincode;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"Enter the password:"<<endl;
        getline(cin,password);
}
void Bank::AccDetails()
{
        cout<<"AccountNo:"<<accountno<<endl;
        cout<<"Name:"<<name<<endl;
        cout<<"EmailId:"<<email<<endl;
        cout<<"HouseNo:"<<addr.houseNo<<endl;
        cout<<"Street:"<<addr.street<<endl;
        cout<<"City:"<<addr.city<<endl;
        cout<<"State:"<<addr.state<<endl;
        cout<<"pincode:"<<addr.pincode<<endl;
}
bool Bank::verifyPassword()
{
 string pass;
        cout<<"Enter the password:"<<endl;
        cin>>pass;
        if(pass==password)
                return 1;
        else
                return 0;
}
Bank::~Bank()
{

        cout<<"Bank Destructor"<<endl;
}
void Bank::menu()
{
        cout<<"1.Deposit"<<endl;
        cout<<"2.Withdraw"<<endl;
        cout<<"3.Balance Enquiry"<<endl;
        cout<<"4.Proceed to Shopping"<<endl;
}
void Bank::Deposit()
{
        float amt;
        cout<<"Enter the ammount:"<<endl;
        cin>>amt;
        balance+=amt;
}
void Bank::Withdraw()
{
        float amt;
        cout<<"Enter the required amount:"<<endl;
        cin>>amt;
        if(amt>balance)
        {
                cout<<"Insuffient amount:"<<endl;
                exit(0);
        }
        else
        {
        balance-=amt;
        }
}
void Bank::BalEnq()
{
        cout<<"Available Balance:"<<balance<<endl;
}
int main()
{
        char choice;
        Bank bobj;
        Shopping sobj;
        bobj.AccDetails();
        bobj.menu();
        while(1)
        {
        cout<<"Enter the choice:";
        cin>>choice;
        switch(choice)
        {
                case'1':if(bobj.verifyPassword());
                        bobj.Deposit();
                        break;
                case'2':if(bobj.verifyPassword());
                        bobj.Withdraw();
                        break;
                case'3':if(bobj.verifyPassword());
                        bobj.BalEnq();
                        break;
                case'4':sobj.Itembilling(bobj);
                        break;
                default:exit(0);
        }
        }

}
