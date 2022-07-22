#include<bits/stdc++.h>
using namespace std;
class Restaurant
{
public:
    int food_item_codes[12];
    string food_item_names[12];
    int food_item_prices[12];
    float total_tax;
    Restaurant(int n,int food_item_codes[],string food_item_names[],int food_item_prices[])
    {
        this->total_tax = 0;
        for(int i=0; i<n; i++)
        {
            this->food_item_codes[i] = food_item_codes[i];
            this->food_item_names[i] = food_item_names[i];
            this->food_item_prices[i] = food_item_prices[i];
        }

    }
};

class Order
{
public:
    int tax;
    int table_number;
    int items;
    int items_code[12];
    int items_quantity[12];
    Order(int table_number,int items,int items_code[],int items_quantity[])
    {
        this->tax = 0;
        this->table_number = table_number;
        for(int i=0; i<items; i++)
        {
            this->items_code[i] = items_code[i];
            this->items_quantity[i] = items_quantity[i];
        }
    }

};
class Details
{

public:
    int table_no;
    float tax_count;
    int sum;
    float total_expence;
    int items_code[12];
    string items_name[12];
    int price[12];
    int quantity[12];
    int total_price[12];

    Details(int n,int item,Order *take_order,Restaurant *myRestaurant)
    {
        this->table_no = take_order->table_number;
        this->sum = 0;
        for(int i=0; i<item; i++)
        {
            this->items_code[i] = take_order->items_code[i];
            this->quantity[i] = take_order->items_quantity[i];
            for(int j=0; j<n; j++)
            {
                if(take_order->items_code[i] == myRestaurant->food_item_codes[j])
                {
                    this->items_name[i] = myRestaurant->food_item_names[j];
                    this->price[i] = myRestaurant->food_item_prices[j];
                }
            }
        }
        for(int i=0; i<item; i++)
        {

            this->total_price[i] = this->price[i]*this->quantity[i];
            this->sum += total_price[i];

        }
        this->tax_count = this->sum * 0.05;
        this->total_expence = this->sum + this->tax_count;
        myRestaurant->total_tax += this->tax_count;
    }


};

Restaurant *createRestaurant(int n)
{
    int code[n];
    int price[n];
    string name[n];
    for(int i=0; i<n; i++)
    {

        cin>>code[i];
        cin.ignore();
        getline(cin, name[i]);
        cin>>price[i];

    }

    Restaurant *myRestaurant = new Restaurant(n,code,name,price);
    return myRestaurant;
}

void createMenu(Restaurant *myRestaurant,int n)
{

    cout<<"\t\t\t\tMENU CARD"<<endl;
    cout<<"\t\t\t________________________"<<endl;
    cout<<"Item Code\t\tItem Name\t\t\t\tItem Price"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<myRestaurant->food_item_codes[i]<<"\t\t\t"<<myRestaurant->food_item_names[i]<<"\t\t\t"<<myRestaurant->food_item_prices[i]<<endl;
    }

}
void print_details(Details *details, int n)
{
    cout<<"\t\t\t\t\t\tBILL SUMMARY"<<endl;
    cout<<"\t\t\t\t\t___________________________"<<endl;
    cout<<"Table no : "<<details->table_no<<endl;
    cout<<"Item Code\t\t\tItem Name\t\t\tItem Price\t\tItem Quantity\t\tTotal Price"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<details->items_code[i]<<"\t\t\t\t"<<details->items_name[i]<<"\t\t"<<details->price[i]<<"\t\t\t"<<details->quantity[i]<<"\t\t\t"<<details->total_price[i]<<endl;
    }
    cout<<"TEX\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<details->tax_count<<endl;
    cout<<"________________________________________________________________________________________________________________________"<<endl;
    cout<<"NET TOTAL\t\t\t\t\t\t\t\t\t\t\t\t\t"<<details->total_expence<<" TAKA"<<endl;


}

void make_order(int n,Restaurant *myRestaurant)
{
    int table_no;
    int items;
    cout<<"Enter Table Number : ";
    cin>>table_no;
    cout<<"Enter Number of Items : ";
    cin>>items;

    int food_code[items];
    int quantity[items];




    for(int i=0; i<items; i++){
int code;
        bool isValid = false;
Go:
        cout<<"Enter Item "<<i+1<<" Code : ";
        cin>>code;
        for(int j=0; j<n; j++)
        {
            if(code == myRestaurant->food_item_codes[j])
            {
                isValid = true;
                break;
            }
        }
        if(isValid)
        {
            food_code[i] = code;
        }
        else
        {
            cout<<"This item is not available..."<<endl;
            goto Go;
        }

        cout<<"Enter Item "<<i+1<<" Quantity : ";
        cin>>quantity[i];

    }

    Order *take_order = new Order(table_no,items,food_code,quantity);
    Details *order_details = new Details(n,items,take_order,myRestaurant);
    print_details(order_details,items);

}

int main()
{
    int n;
    cin>>n;
    Restaurant *myRestaurant = createRestaurant(n);

    while(true)
    {
        createMenu(myRestaurant,n);
        make_order(n,myRestaurant);
    }




    return 0;
}
