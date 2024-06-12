#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <iomanip>
using namespace std;

int topcart=0;//stack top for inv
int toptemp=0;//stack top for temp storage
int OrderID=0;//keep count for the ID

class Order{ //for shopping cart

	public:
	string brand,type,colour;
	double price;
		
	Order()
	{ //default constructor 
		price = 0.0;
		brand = "---";
		type = "---";
		colour = "---";
	}
};

class Receipt : public Order//for final order list
{
	public:	
	void Finalize(Order ShoppingCart[],Order Catalog[],Order Tempstore[]);//aka function to create nodes
	void ViewFinal();
	int intCheck(int input);
	void SepatuMenu(Order ShoppingCart[], Order Catalog[], Order TempStore[],Receipt head);
	void AddShoe(Order Catalog[],Order ShoppingCart[],Order TempStore[]);
	void DelShoe(Order ShoppingCart[],Order TempStore[],Order Catalog[]);
	void EditShoe(Order ShoppingCart[],Order TempStore[],Order Catalog[]);
	void AddOrder(Order ShoppingCart[], Order Catalog[], Order TempStore[]);
	void SummaryReport();	
		
	struct node
	{
		int ID;//id for current order
		int topcurrent;//number of shoes in the order	
		Order inventory[10];//actual array of classes @ the data
		node *next;
	};
		node *str_ptr = NULL;
};

int main(void){

	int m1;
	Order Catalog[5];
	Order ShoppingCart[10];
	Order TempStore[10];
	Receipt head;
	char confirm;
	
	for(int m1 = 0;m1 < 11;m1++)
	{ //initialize all elements/objects in the array with its constructor value
		ShoppingCart[m1];
	}
	
	//pre set data
	Catalog[0].brand = "Adidas";			Catalog[0].type = "Running";		Catalog[0].colour = "Red";			Catalog[0].price = 253.50;
	Catalog[1].brand = "Nike";				Catalog[1].type = "Badminton";		Catalog[1].colour = "Grey";			Catalog[1].price = 169.70;
	Catalog[2].brand = "Bata"; 				Catalog[2].type = "Training";		Catalog[2].colour = "Brown";		Catalog[2].price = 189.30;
	Catalog[3].brand = "Reebok";			Catalog[3].type = "Running";		Catalog[3].colour = "Gold";			Catalog[3].price = 275.00;
	Catalog[4].brand = "Puma";				Catalog[4].type = "Football";	    Catalog[4].colour = "Purple";	   	Catalog[4].price = 348.00;

	head.SepatuMenu(ShoppingCart,Catalog,TempStore,head);
	return 0;
}

int Receipt::intCheck(int input)//check input must be integer
{
	while(!cin)
	{	
		cin.clear();
		cin.ignore(100,'\n');
		cout << "Invalid Input Please try again"<< endl;
		cout << "=>> ";
		cin >>input;
	}
	return input;
}


void Receipt::SepatuMenu(Order ShoppingCart[], Order Catalog[], Order TempStore[],Receipt head)
{
	int i,Choice,menu;
	char confirm;
	node *temp;
	temp = str_ptr;
	
	while(Choice != 5)
	{
		
			for(i=0;i<=::topcart-1;i++)
			{	
				cout << ">> Cart " <<i+1;
				cout << " Brand:" <<ShoppingCart[i].brand;
				cout << "\t\t" << "Type:" <<ShoppingCart[i].type;
				cout << "\t\t" << "Colour:" <<ShoppingCart[i].colour;
				cout << "\t\t" << "Price:" <<ShoppingCart[i].price;
				cout << endl;
			}
	
		cout << endl;
		cout<<"*** Welcome To mySepatu Online Shop ***\n\n";
		
		menu:
		cout<<">> Please select an option below. <<"<<endl;
		cout<<"> 1 < Main Menu"<<endl;
		cout<<"> 2 < Add Order"<<endl;
		cout<<"> 3 < View an Order"<<endl;
		cout<<"> 4 < Summary Report"<<endl;	
		cout<<"> 5 < Exit"<<endl;
		cout << "=>> ";
		cin>>Choice;
		Choice = head.intCheck(Choice);
		
		switch(Choice)
			{
			
			case 1:
				{
					//system("CLS");
					
					break;
				}
			case 2:
				{
					head.AddOrder(ShoppingCart,Catalog,TempStore);
					break;	
				}
			case 3:
				{
					head.ViewFinal();
					break;
				}
			case 4:
				{
					//summary report
					head.SummaryReport();		
					break;
				}
			case 5:
				{
					cout << "Are you sure you want to exit? (1 for yes/2 for no): \n";
					cin>>menu;
					if (menu == 1){
						cout <<"\n*** Thank You ***\n\nPROGRAM TERMINATED\n";
						break;
					}
					else{
						goto menu;
					}
				}
				cout<<"\n*** Thank You ***\n\nPROGRAM TERMINATED";
			}
		
	}
}


void Receipt::AddShoe(Order Catalog[],Order ShoppingCart[],Order TempStore[])
{
	int C1,i;
	system ("CLS");
	for(i=0;i<5;i++)
	{ //show catalog
		cout<<i+1<<" Brand:"<<Catalog[i].brand<<"\t\t"
		<<"Type:"<<Catalog[i].type<<"\t\t"
		<<"Colour:"<<Catalog[i].colour<<"\t\t"
		<<"Price:"<<setprecision(2)<<fixed<<showpoint<<Catalog[i].price<<endl;
	}
	
		cout << "\nWhat do you want to add? 1-5"<< endl;
		cout << "=>> ";
		cin >>C1;
		C1 = intCheck(C1);//check input
	
	if(C1<=0||C1>=6)
	{ //outside the range
		cout <<">> Error value not available <<"<< endl;
	}
	else if(::topcart == 10)
	{ //Shopping cart full
		cout <<"\n>> Shopping Cart is full <<"<<endl;
	}

	else
	{ //within range, Cart not full and correct input
		ShoppingCart[::topcart].brand = Catalog[C1-1].brand;
		ShoppingCart[::topcart].type = Catalog[C1-1].type;
		ShoppingCart[::topcart].colour = Catalog[C1-1].colour;
		ShoppingCart[::topcart].price = Catalog[C1-1].price;
		::topcart++;//increase global variable so we know the number of items in the cart
		system ("CLS");

		cout << ">> Your order is succesfully added. <<" << endl;
		cout << ">> Go to 'Order List' to check. \n<<" << endl;
	}
	return;
}


void Receipt::DelShoe(Order ShoppingCart[],Order TempStore[],Order Catalog[])
{
	system ("CLS");
	int C2,i,j;

	if(::topcart == 0)
	{ //Shopping cart is empty
		cout <<"\n>> Shopping cart is empty <<"<<endl;
	}
	else
	{	
		for(i=0;i<=::topcart-1;i++)
		{
			cout<<">> Cart "<<i+1<<" Brand:"<<ShoppingCart[i].brand<<"\t\t"
			<<"Type:"<<ShoppingCart[i].type<<"\t\t"
			<<"Colour:"<<ShoppingCart[i].colour<<"\t\t"
			<<"Price:"<<setprecision(2)<<fixed<<showpoint<<ShoppingCart[i].price<<endl;
		}
	
		cout << "\nWhich do you want to delete? 1-"<<::topcart<<endl;
		cout << "=>> ";
		cin >>C2;
		C2 = intCheck(C2);//check input
		
		if(C2==::topcart)
		{ //popping 1 element/order from the top
			::topcart--;
		}
		else if(C2>::topcart||C2<1)
		{ //input is correct type but outside of range
			cout <<"\n>> Error value is not in the list <<"<<endl;
		}
		else if(1<=C2<topcart&&1<topcart)
		{ //choice is between 1 and top is greater than 1
			for(i = ::topcart,j = ::toptemp;i > C2;i--,j++)
			{ //place all items after choice into TempStore
				TempStore[j].brand = ShoppingCart[i-1].brand;
				TempStore[j].type = ShoppingCart[i-1].type;
				TempStore[j].colour = ShoppingCart[i-1].colour;
				TempStore[j].price = ShoppingCart[i-1].price;
				::toptemp++;
				::topcart--;//popping Shoppingcart top while pushing to TempStore until we reach the chosen element/class/order
			}
		
			::topcart--;//popping the element/class/order
			
			for(i = ::toptemp,j = ::topcart;i > 0;i--,j++)
			{ //pushing back from TempStore to Shopping cart	
				ShoppingCart[j].brand = TempStore[i-1].brand;
				ShoppingCart[j].type = TempStore[i-1].type;
				ShoppingCart[j].colour = TempStore[i-1].colour;
				ShoppingCart[j].price = TempStore[i-1].price;
				::topcart++;//updating the value of topcart for each push
				::toptemp--;//updating the value of toptemp for each pop
			}
		system ("CLS");
		}
		
		else
		{ //any unknown errors
			cout <<">> Error invalid input. <<"<<endl;
		}
	}
}


void Receipt::EditShoe(Order ShoppingCart[],Order TempStore[],Order Catalog[])
{
	/*
	Edit is similar to Delete in that it moves all objects to the temp array, edits the specified object ,then moves the objects back,
	This is to satisfy the stack model in that only the top can be be pushed, popped and edited.
	*/
	system ("CLS");
	int C3,i,j,newcolour;//add empty set option

	if(::topcart == 0)
	{ //Shopping cart is empty
		cout <<"\n>> Shopping cart is empty <<"<<endl;
	}
	else
	{	
		for(i=0;i<=::topcart-1;i++)
		{
			cout<<">> Cart "<<i+1<<" Brand:"<<ShoppingCart[i].brand<<"\t\t"
			<<"Type:"<<ShoppingCart[i].type<<"\t\t"
			<<"Colour:"<<ShoppingCart[i].colour<<"\t\t"
			<<setprecision(2)<<fixed<<showpoint<<"Price:"<<ShoppingCart[i].price<<endl;
		}
	
			cout << "\nWhich do you want to edit? 1-"<<::topcart<<endl;
			cout << "=>> ";
			cin >>C3;
			C3 = intCheck(C3);//check input
			
		if(C3==::topcart)
		{ //edit the top value
			cout<<"\nPlease choose the colour you wish\n1.Red\n2.Grey\n3.Brown\n4.Gold\n5.Purple\n"<<endl;
			cin>>newcolour;
			newcolour = intCheck(newcolour);

			switch(newcolour)
				{
			case 1:
				{
					ShoppingCart[C3-1].colour = "Red";
					break;
				}
			case 2:
				{
					ShoppingCart[C3-1].colour = "Grey";
					break;	
				}
			case 3:
				{
					ShoppingCart[C3-1].colour = "Brown";
				}
				break;
			case 4:
				{
					ShoppingCart[C3-1].colour = "Gold";
					break;
				}
			case 5:
				{
					ShoppingCart[C3-1].colour = "Purple";
					break;
				}
			default:
				{
					cout<<"Error invalid input"<<endl;
					break;
				}
				}
		}
		else if(C3>::topcart||C3<1)
		{ //input is correct but outside of range
			cout <<"\n>> Error value is not in the list <<"<<endl;
		}
		else if(1<=C3<topcart&&1<topcart)
		{ //since value is in between bottom and top of stack we have to move the objects first then edit the object
			for(i = ::topcart,j = ::toptemp;i > C3;i--,j++)
			{ //place all items after choice into TempStore
				TempStore[j].brand = ShoppingCart[i-1].brand;
				TempStore[j].type = ShoppingCart[i-1].type;
				TempStore[j].colour = ShoppingCart[i-1].colour;
				TempStore[j].price = ShoppingCart[i-1].price;
				::toptemp++;
				::topcart--;//popping Shopping cart top while pushing to TempStore until we reach the chosen element/class/order
				cout<<::topcart<<endl;
			}
		
			cout<<"\nPlease choose the colour you wish\n1.Red\n2.Grey\n3.Brown\n4.Gold\n5.Purple\n"<<endl;
			cin>>newcolour;
			newcolour = intCheck(newcolour);
			
			switch(newcolour)
				{
			case 1:
				{
					ShoppingCart[C3-1].colour = "Red";
					break;
				}
			case 2:
				{
					ShoppingCart[C3-1].colour = "Grey";
					break;	
				}
			case 3:
				{
					ShoppingCart[C3-1].colour = "Brown";
				}
				break;
			case 4:
				{
					ShoppingCart[C3-1].colour = "Gold";
					break;
				}
			case 5:
				{
					ShoppingCart[C3-1].colour = "Purple";
					break;
				}
			default:
				{
					cout<<"Error invalid input"<<endl;
					break;
				}
				}
			
			for(i = ::toptemp,j = ::topcart;i > 0;i--,j++)
			{ //pushing back from TempStore to Shopping cart	
				ShoppingCart[j].brand = TempStore[i-1].brand;
				ShoppingCart[j].type = TempStore[i-1].type;
				ShoppingCart[j].colour = TempStore[i-1].colour;
				ShoppingCart[j].price = TempStore[i-1].price;
				::topcart++;//updating the value of topcart for each push
				::toptemp--;//updating the value of toptemp for each pop
			}
		system ("CLS");
		}
		
		else
		{ //any unknown errors
			cout <<">> Error invalid input. <<"<<endl;
		}
	}
}


void Receipt::AddOrder(Order ShoppingCart[], Order Catalog[], Order TempStore[])
{
	int i,Choice;
	system("CLS");

	while(Choice != 5)
	{
		
			for(i=0;i<=::topcart-1;i++)
			{	
				cout << ">> Inv " <<i+1;
				cout << " Brand:" <<ShoppingCart[i].brand;
				cout << "\t\t" << "Type:" <<ShoppingCart[i].type;
				cout << "\t\t" << "Colour:" <<ShoppingCart[i].colour;
				cout << "\t\t" << "Price:" <<ShoppingCart[i].price;
				cout << endl;
			}
	
		cout << endl;

		cout<<">> Please select an option below. <<"<<endl;
		cout<<"> 1 < Add Shoe"<<endl;
		cout<<"> 2 < Delete Shoe"<<endl;
		cout<<"> 3 < Edit Shoe"<<endl;
		cout<<"> 4 < Finalize/Exit"<<endl;	
		cout << "=>> ";
		cin>>Choice;
		Choice = intCheck(Choice);
		
		switch(Choice)
			{
			
			case 1:
				{
					AddShoe(Catalog,ShoppingCart,TempStore);
					break;
				}
			case 2:
				{
					DelShoe(ShoppingCart,TempStore,Catalog);
					break;	
				}
			case 3:
				{
					EditShoe(ShoppingCart,TempStore,Catalog);
					break;
				}
			case 4:
				{
					Finalize(ShoppingCart,Catalog,TempStore);
					::topcart = 0;//reset topcart for next order
					Choice = 5;
					break;
				}
			}
		
	}
}


void Receipt::Finalize(Order ShoppingCart[],Order Catalog[],Order TempStore[])
{
	node *temp, *temp2;//pointers
	int i;
	
	if(::topcart == 0)
	{
		cout<<"\n>> Shopping Cart is empty. <<" << endl;
		cout<<">> Make sure confirmed your order <<"<<endl;
	}
	
	else
	{

		temp = new node;//new node
		::OrderID++;//keep track of the orders
	
		for(i=0;i<topcart;i++)
		{	
			temp->inventory[i].price = ShoppingCart[i].price;//deep copy
			temp->inventory[i].brand = ShoppingCart[i].brand;
			temp->inventory[i].type = ShoppingCart[i].type;
			temp->inventory[i].colour = ShoppingCart[i].colour;	
			//assigning/copying the shopping cart data to the new node inventory
		}
		temp->ID = ::OrderID;		
		temp->topcurrent = ::topcart;//assigning the number of shoes with the topcart value
		temp->next = NULL; 
		
		if (str_ptr == NULL)
		{  //node not linked so becomes first node
		 	str_ptr = temp;
		}
	
		else
		{	
			temp2 = str_ptr; // use temp 2 to traverse until the end
			while (temp2->next != NULL)
			{
				temp2 = temp2->next; // Move to next node
			}
			temp2->next = temp; //connect the last node (temp2) in the list with the new node(temp)
		}
	
		system ("CLS");
		cout << ">> Your order had been confirmed. <<" << endl;
 	}
}


void Receipt::ViewFinal() 
{
	node *temp,*temp2;
	temp  = str_ptr;
	temp2 = str_ptr;//both pointers start at the beginning 
	int i,IDC;//i = counter, IDC used to find the ID chosen 
	double totalPrice;//used to calculate the total
	bool found = false;

	system ("CLS");
	
	if(str_ptr == NULL)
	{
		cout<<"Final order list is empty"<<endl;
	}
	else 
	{
		cout<<"\nWhich one do you want to view?\n" << endl;
	
		while(temp)
			{ //first temp travels to list the ID available
				cout <<"Order ID: "<<temp->ID<<endl;
				temp = temp->next;
			}
	
		cout << "=>> ";
		cin>>IDC;
		IDC = intCheck(IDC);
	
		while(temp2)//second temp travels to find the chosen ID
			{ 

				if(temp2->ID == IDC)//if it is found print the order
				{
					cout<<"__________________________________________________________________________"<<endl;
					cout<<"|Order ID: "<<IDC;
					cout<<"    |                       |                   |            |"<<endl;
					cout << "|_______________|_______________________|___________________|____________|" << endl;
					cout << "|  Brand\t"<<"|\t  Type\t\t"<<"|\tColour      "<<"|\tPrice\t |"<<endl;
		
				for(i=0; i<temp2->topcurrent; i++)
					{ //print the order
					
					cout << "|_______________|_______________________|___________________|____________|" << endl;
					cout << "|" << temp2->inventory[i].brand << "\t\t|"
					<< temp2->inventory[i].type << "\t\t"<<"|" 
					<< temp2->inventory[i].colour << "\t\t    |RM "
					<<setprecision(2)<<fixed<<showpoint<<temp2->inventory[i].price<< "   |"<<endl;	
			
					totalPrice = totalPrice + temp2->inventory[i].price; //sum up the total price
					}
					cout<<"|_______________|_______________________|___________________|____________|"<<endl;
					cout<<"|               |                       |Total              |RM " << totalPrice;
					cout<<"\t |" <<endl; 
					cout<<"|_______________|_______________________|___________________|____________|"<<endl;
					
					found = true;
					break;
				}
				temp2 = temp2->next;

			}
	}
	if(found == false)
	{
		cout<<"Order not found"<<endl;
	}
}

void Receipt::SummaryReport()
{
	node *temp,*temp2;
	temp  = str_ptr;
	temp2 = str_ptr;//both pointers start at the beginning 
	int i;
	double totalPrice;
	
	system ("CLS");
	
	if(str_ptr == NULL)
	{
		cout<<"No purchasing for today."<<endl;
	}
	else 
	{
		cout << endl << endl;
		cout<<"__________________________________________________________________________"<<endl;
		cout << "|  Brand\t"<<"|\t  Type\t\t"<<"|\tColour      "<<"|\tPrice\t |"<<endl;
		while(temp2!=NULL)
		{
		for(i=0; i<temp2->topcurrent; i++)
		{ //print the order
					
			cout << "|_______________|_______________________|___________________|____________|" << endl;
			cout << "|" << temp2->inventory[i].brand << "\t\t|"
			<< temp2->inventory[i].type << "\t\t"<<"|" 
			<< temp2->inventory[i].colour << "\t\t    |RM "
			<<setprecision(2)<<fixed<<showpoint<<temp2->inventory[i].price<< "   |"<<endl;	
			
			totalPrice = totalPrice + temp2->inventory[i].price; //sum up the total price
		}
		temp2 = temp2->next;
		}
		cout<<"|_______________|_______________________|___________________|____________|"<<endl;
		cout<<"|               |                       |Total              |RM " << totalPrice;
		cout<<"\t |" <<endl; 
		cout<<"|_______________|_______________________|___________________|____________|"<<endl;

	}				
}
