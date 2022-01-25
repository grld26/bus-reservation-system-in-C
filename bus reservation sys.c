#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>

void TicketDetails();
int GetOrder(char *pck);
void ReviewOrder();
void SaveTransaction();
void PrintReceipt();
void history();
void clearHistory();

//to temporary save the booking detail
struct order_detail
{
	char ticket_dest[35];
	char Premium;
	char Food;
	char Drink;
	float charge;
	
}ticket[6];

int counter=1;
int ticket_qty;
float S_Charge;
float T_Charge;
char confirm;
int end=1;

//GetOrder
int ticket_dest;
char seat_type;
char package,Food, Drink;
char addOn;

int main()
{	
	char *pck=&package;//assign a pointer for package
	
	start:				//for system to jump back to start
		
	system("cls");		//used to clear screen
	TicketDetails();	//call ticket detail function
	fflush(stdin);
	
	printf("Select [A] -> Adult Business, [B]-> Adult Economy, [C]-> Kid Business, [D]-> Kid Economy:");	//to filter user input before entering getBooking function
	scanf("%c",&package);
	printf("----------------------------------------------------------------\n");
	
	//To set the limit of ticket can be purchase according to package
	//To set the limit of ticket can be purchase according to category
	if(*pck=='A'||*pck=='a' || *pck=='B'||*pck=='b' || *pck=='C'||*pck=='c' || *pck=='D'||*pck=='d' )
	{	
		ticket_qty=1;
	}
	else if(*pck=='H'||*pck=='h')			// to open history
	{
		system("cls");
		history();
		goto start;
	}
	else if(*pck=='N'||*pck=='n')			//used to exit at main menu but not recomended
	{										//might cause saving empty receipt
		end=0;
		goto exit;
	}
	else 
	{
		printf("ERROR-Invalid Input\n");
		printf("SORRY, the system doesn't recognize the package entered\n");
		printf("Please try again\n");
		system("pause");
		goto start;
	}

counter=1;
S_Charge=0;
	
do{

	fflush(stdin);
	GetOrder(&package);
	S_Charge+=ticket[counter].charge;		//To calculate total or a single order
	T_Charge+=ticket[counter].charge;		//To calculate total of all orders
	counter++;	
	
}while(counter<=ticket_qty);

	system("pause");
	system("cls");
	ReviewOrder();
	
	//to double check the order
	confirm:
	fflush(stdin);
	printf("\t\t  ==  Press 'Y' to confirm your booking and press any other key to cancel  ==\n");
	scanf("%c",&confirm);
	if(confirm!='Y' && confirm!='y')
	{	
		fflush(stdin);
		printf("\t\t  Are you sure you want to cancel?(Y/N)\n");
		scanf("%c",&confirm );
		if(confirm =='Y'|| confirm=='y')
		{
			T_Charge-=S_Charge;
			system("cls");
			goto start;
		}
		else 
			goto confirm;
	}
	
	system("cls");
	SaveTransaction();
	PrintReceipt();
	fflush(stdin);
	
	//To exit the program and save the total into receipt.txt
	printf("\t\t\t\t\t\t== Press '0' to EXIT  ==\n");
	printf("\nEnter any key to continue...");
	scanf("%d",&end);
	
	exit:
		
	if(end==0)
	{
		FILE *fhistory;
		fhistory=fopen("history.txt","a");
	
		fprintf(fhistory," ______________________________________________________________________________________________________________________\n");
		fprintf(fhistory,"\t\t\t\t\t\t\t\t\t\t\t\t   Total= RM %5.2f\n\n\n",T_Charge);
		fprintf(fhistory,"\n\t\t\t\t  ======================================================\n");
		fprintf(fhistory,"\t\t\t\t\t\t       Booking History");
		fprintf(fhistory,"\n\t\t\t\t  ======================================================\n\n");
		fprintf(fhistory," ______________________________________________________________________________________________________________________\n");
		fprintf(fhistory,"\n   Ref. No.          Package                           Number of Ticket       Premium        Food      Drink   Amount(RM)\n");
	
		fclose(fhistory);
		return 0;
	}
	else
	{
		system("cls");
		goto start;
	}
	
return 0;	
}


void TicketDetails()
{
	printf("\n\t\t\t  ======================================================\n");
	printf("\t\t\t\t\tBus Reservation Details\n");
	printf("\t\t\t  ======================================================\n");
	printf("  _______________________________________________________________________________________________________________________\n");
	printf(" |           Package                      |     Normal(RM)    |    Premium Seat(RM)   |        Food (RM)    |  Drink(RM) |\n");
	printf(" |________________________________________|___________________|_______________________|_____________________|____________|\n");
	printf(" | (A)Adult Business  |      Kuching      |  12.50 per person |    15.50 per person   |     5.00 per pax    |2.00 per pax|\n");
	printf(" |                    |___________________|___________________|_______________________|                     |            |\n");
	printf(" |                    |      Serian       |  20.00 per person |    25.00 per person   |                     |            |\n");
	printf(" |                    |___________________|___________________|_______________________|                     |            |\n");
	printf(" |                    |   Kota Samarahan  |  18.00 per person |    20.00 per person   |                     |            |\n");
	printf(" |____________________|___________________|___________________|_______________________|_____________________|____________|\n");
	printf(" | (B)Adult Economy   |      Kuching      |  10.50 per person |    12.50 per person   |     4.00 per pax    |1.50 per pax|\n");
	printf(" |                    |___________________|___________________|_______________________|                     |            |\n");
	printf(" |                    |      Serian       |  18.00 per person |    20.00 per person   |                     |            |\n");
	printf(" |                    |___________________|___________________|_______________________|                     |            |\n");
	printf(" |                    |   Kota Samarahan  |  15.70 per person |    17.00 per person   |                     |            |\n");
	printf(" |____________________|___________________|___________________|_______________________|_____________________|____________|\n");
	printf(" | (C)Kid Business    |      Kuching      |   6.25 per person |     7.75 per person   |     3.50 per pax    |1.20 per pax|\n");
	printf(" |                    |___________________|___________________|_______________________|                     |            |\n");
	printf(" |                    |      Serian       |  12.00 per person |    15.00 per person   |                     |            |\n");
	printf(" |                    |___________________|___________________|_______________________|                     |            |\n");
	printf(" |                    |   Kota Samarahan  |   9.00 per person |    10.00 per person   |                     |            |\n");
	printf(" |____________________|___________________|___________________|_______________________|_____________________|____________|\n");
	printf(" | (D)Kid Economy     |      Kuching      |   5.25 per person |     6.25 per person   |     5.00 per pax    |2.00 per pax|\n");
	printf(" |                    |___________________|___________________|_______________________|                     |            |\n");
	printf(" |                    |      Serian       |   9.00 per person |    12.00 per person   |                     |            |\n");
	printf(" |                    |___________________|___________________|_______________________|                     |            |\n");
	printf(" |                    |   Kota Samarahan  |   7.85 per person |     8.50 per person   |                     |            |\n");
	printf(" |____________________|___________________|___________________|_______________________|_____________________|____________|\n");
	
	printf("\n\t\t\t\t==  Press 'H' to open HISTORY / 'N'to EXIT  ==\n");
	printf("\n *********************************************************************************************************\n\n");
	return;
}

//Get orders from customer
//Calculate the booking charges
int GetOrder(char *pck)
{
	char *Stype=&seat_type;
	char *fOOd=&Food;
	char *dRink=&Drink;
	
	switch(*pck)
	{
		Adult_Business:
		//Adult_Business	
		case'A':case'a':
			printf("\n\t\t== Adult_Business #%d ==\n\n",counter);
			printf("Enter ticket destination(1-Kuching; 2-Serian; 3-Kota Samarahan):");
			scanf("%d",&ticket_dest);
			
		switch(ticket_dest)
		{	
		//Kuching
		case 1:
		strcpy(ticket[counter].ticket_dest, "Adult_Business-Kuching");	
		seat_type1:
			fflush(stdin);
			printf("Enter type of seat\t\t\t(1-Normal;2-Premium):");
			scanf("%c",&seat_type);
			
			if(*Stype=='1')
			{
				ticket[counter].charge=12.5;
				ticket[counter].Premium='-';
			}
			else if(*Stype=='2')
			{	
				ticket[counter].charge=15.5;
				ticket[counter].Premium='1';
			}
			else
			{
				printf("ERROR-Invalid Input\n");
				goto seat_type1;
			}
			
		Food1:
			fflush(stdin);
			printf("Do you need food? \t\t\t\t    (Y/N):");
			scanf("%c",&Food);
			
			if(*fOOd=='Y'||*fOOd=='y')
			{
				ticket[counter].Food='1';
				ticket[counter].charge+=5;
			}
			else if(*fOOd=='N'||*fOOd=='n')
			{
				ticket[counter].Food='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Food1;
			}
			
			Drink1:
			fflush(stdin);
			printf("Do you need drinks? \t\t\t\t    (Y/N):");
			scanf("%c",&Drink);
			
			if(*dRink=='Y'||*dRink=='y')
			{
				ticket[counter].Drink='1';
				ticket[counter].charge+=2;
			}
			else if(*fOOd=='N'||*dRink=='n')
			{
				ticket[counter].Drink='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Drink1;
			}
			
			//addOn	
			fflush(stdin);
			printf("\nPress 'Y' to add-on 1 more ticket & press any other key to proceed to payment\n");
			scanf("%c",&addOn);
			if(addOn=='Y'||addOn=='y')
			{
				ticket_qty+=1;
				package='A';
			}
			printf("\n----------------------------------------------------------------\n");
			break;
			
		//Serian
		case 2:
		strcpy(ticket[counter].ticket_dest, "Adult_Business-Serian");	
		seat_type2:
			
			fflush(stdin);
			printf("Enter type of seat \t\t\t(1-Normal;2-Premium):"),counter;
			scanf("%c",&seat_type);
			
			if(*Stype=='1')
			{
				ticket[counter].charge=20;
				ticket[counter].Premium='-';
			}
			else if(*Stype=='2')
			{
				ticket[counter].Premium='1';
				ticket[counter].charge=25;
			}
			else
			{
				printf("ERROR-Invalid Input\n");
				goto seat_type2;
			}
			
		Food2:			
			fflush(stdin);
			printf("Do you need food? \t\t\t\t    (Y/N):");
			scanf("%c",&Food);
			
			if(*fOOd=='Y'||*fOOd=='y')
			{
				ticket[counter].Food='1';
				ticket[counter].charge+=5;	
			}
			else if(*fOOd=='N'||*fOOd=='n')
			{
				ticket[counter].Food='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Food2;
			}
			
			Drink2:
					
			fflush(stdin);
			printf("Do you need drinks? \t\t\t\t    (Y/N):");
			scanf("%c",&Drink);
			
			if(*dRink=='Y'||*dRink=='y')
			{
				ticket[counter].Drink='1';
				ticket[counter].charge+=2;	
			}
			else if(*dRink=='N'||*dRink=='n')
			{
				ticket[counter].Drink='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Drink2;
			}
			
			//addOn	
			fflush(stdin);
			printf("\nPress 'Y' to add-on 1 more ticket & press any other key to proceed to payment\n");
			scanf("%c",&addOn);
			if(addOn=='Y'||addOn=='y')
			{
				ticket_qty+=1;
				package='A';
			}
			printf("\n----------------------------------------------------------------\n");
			break;
			
			
		//Kota Samarahan
		case 3:
		strcpy(ticket[counter].ticket_dest, "Adult_Business-Kota Samarahan");
		seat_type3:
			
			fflush(stdin);
			printf("Enter type of seat \t\t\t(1-Normal;2-Premium):"),counter;
			scanf("%c",&seat_type);
			
			if(*Stype=='1')
			{
				ticket[counter].charge=18;
				ticket[counter].Premium='-';
			}
			else if(*Stype=='2')
			{
				ticket[counter].Premium='1';
				ticket[counter].charge=20;
			}
			else
			{
				printf("ERROR-Invalid Input\n");
				goto seat_type3;
			}
				
			Food3:	
			fflush(stdin);
			printf("Do you need food? \t\t\t    (Y/N):");
			scanf("%c",&Food);
			
			if(*fOOd=='Y'||*fOOd=='y')
			{
				ticket[counter].Food='1';
				ticket[counter].charge+=5;	
			}
			else if(*fOOd=='N'||*fOOd=='n')
			{
				ticket[counter].Food='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Food3;
			}
			
			Drink3:	
			fflush(stdin);
			printf("Do you need drinks? \t\t\t    (Y/N):");
			scanf("%c",&Drink);
			
			if(*dRink=='Y'||*dRink=='y')
			{
				ticket[counter].Drink='1';
				ticket[counter].charge+=2;	
			}
			else if(*dRink=='N'||*dRink=='n')
			{
				ticket[counter].Drink='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Drink3;
			}
	 	
			//addOn	
			fflush(stdin);
			printf("\nPress 'Y' to add-on 1 more ticket & press any other key to proceed to payment\n");
			scanf("%c",&addOn);
			if(addOn=='Y'||addOn=='y')
			{
				ticket_qty+=1;
				package='A';
			}
			break;
			
			default:
			printf("ERROR-Invalid Input\n");
			printf("SORRY, the system doesn't recognize the category entered\n");
			printf("Please try again\n");
			goto Adult_Business;	
		}
			printf("\n----------------------------------------------------------------\n");
			break;
		
	Adult_Economy:
		//Adult_Economy	
		case'B':case'b':
			printf("\n\t\t== Adult_Economy #%d ==\n\n",counter);
			printf("Enter ticket destination(1-Kuching; 2-Serian; 3-Kota Samarahan):");
			scanf("%d",&ticket_dest);
			
			switch(ticket_dest)
		{
			
		//Kuching
		case 1:
		strcpy(ticket[counter].ticket_dest, "Adult_Economy-Kuching");	
		seat_type4:
			fflush(stdin);
			printf("Enter type of seat\t\t\t(1-Normal;2-Premium):");
			scanf("%c",&seat_type);
			
			if(*Stype=='1')
			{
				ticket[counter].charge=10.5;
				ticket[counter].Premium='-';
			}
			else if(*Stype=='2')
			{	
				ticket[counter].charge=12.5;
				ticket[counter].Premium='1';
			}
			else
			{
				printf("ERROR-Invalid Input\n");
				goto seat_type4;
			}
			
		Food4:
			fflush(stdin);
			printf("Do you need food? \t\t\t\t    (Y/N):");
			scanf("%c",&Food);
			
			if(*fOOd=='Y'||*fOOd=='y')
			{
				ticket[counter].Food='1';
				ticket[counter].charge+=4;
			}
			else if(*fOOd=='N'||*fOOd=='n')
			{
				ticket[counter].Food='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Food4;
			}
			
			Drink4:
			fflush(stdin);
			printf("Do you need drinks? \t\t\t\t    (Y/N):");
			scanf("%c",&Drink);
			
			if(*dRink=='Y'||*dRink=='y')
			{
				ticket[counter].Drink='1';
				ticket[counter].charge+=1.5;
			}
			else if(*fOOd=='N'||*dRink=='n')
			{
				ticket[counter].Drink='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Drink4;
			}
			
			//addOn	
			fflush(stdin);
			printf("\nPress 'Y' to add-on 1 more ticket & press any other key to proceed to payment\n");
			scanf("%c",&addOn);
			if(addOn=='Y'||addOn=='y')
			{
				ticket_qty+=1;
				package='B';
			}
			printf("\n----------------------------------------------------------------\n");
			break;
			
		//Serian
		case 2:
		strcpy(ticket[counter].ticket_dest, "Adult_Economy-Serian");	
		seat_type5:
			
			fflush(stdin);
			printf("Enter type of seat \t\t\t(1-Normal;2-Premium):"),counter;
			scanf("%c",&seat_type);
			
			if(*Stype=='1')
			{
				ticket[counter].charge=18;
				ticket[counter].Premium='-';
			}
			else if(*Stype=='2')
			{
				ticket[counter].Premium='1';
				ticket[counter].charge=20;
			}
			else
			{
				printf("ERROR-Invalid Input\n");
				goto seat_type5;
			}
			
		Food5:
					
			fflush(stdin);
			printf("Do you need food? \t\t\t\t    (Y/N):");
			scanf("%c",&Food);
			
			if(*fOOd=='Y'||*fOOd=='y')
			{
				ticket[counter].Food='1';
				ticket[counter].charge+=4;	
			}
			else if(*fOOd=='N'||*fOOd=='n')
			{
				ticket[counter].Food='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Food5;
			}
			
			Drink5:
					
			fflush(stdin);
			printf("Do you need drinks? \t\t\t\t    (Y/N):");
			scanf("%c",&Drink);
			
			if(*dRink=='Y'||*dRink=='y')
			{
				ticket[counter].Drink='1';
				ticket[counter].charge+=1.5;	
			}
			else if(*dRink=='N'||*dRink=='n')
			{
				ticket[counter].Drink='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Drink5;
			}
			
			//addOn	
			fflush(stdin);
			printf("\nPress 'Y' to add-on 1 more ticket & press any other key to proceed to payment\n");
			scanf("%c",&addOn);
			if(addOn=='Y'||addOn=='y')
			{
				ticket_qty+=1;
				package='B';
			}
		
			printf("\n----------------------------------------------------------------\n");
			break;
			
			
		//Kota Samarahan
		case 3:
		strcpy(ticket[counter].ticket_dest, "Adult_Economy-Kota Samarahan");
		seat_type6:
			
			fflush(stdin);
			printf("Enter type of seat \t\t\t(1-Normal;2-Premium):"),counter;
			scanf("%c",&seat_type);
			
			if(*Stype=='1')
			{
				ticket[counter].charge=15.7;
				ticket[counter].Premium='-';
			}
			else if(*Stype=='2')
			{
				ticket[counter].Premium='1';
				ticket[counter].charge=17;
			}
			else
			{
				printf("ERROR-Invalid Input\n");
				goto seat_type6;
			}
				
			Food6:	
			fflush(stdin);
			printf("Do you need food? \t\t\t    (Y/N):");
			scanf("%c",&Food);
			
			if(*fOOd=='Y'||*fOOd=='y')
			{
				ticket[counter].Food='1';
				ticket[counter].charge+=3.5;	
			}
			else if(*fOOd=='N'||*fOOd=='n')
			{
				ticket[counter].Food='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Food6;
			}
			
			Drink6:	
			fflush(stdin);
			printf("Do you need drinks? \t\t\t    (Y/N):");
			scanf("%c",&Drink);
			
			if(*dRink=='Y'||*dRink=='y')
			{
				ticket[counter].Drink='1';
				ticket[counter].charge+=1.2;	
			}
			else if(*dRink=='N'||*dRink=='n')
			{
				ticket[counter].Drink='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Drink6;
			}
		
			//addOn	
			fflush(stdin);
			printf("\nPress 'Y' to add-on 1 more ticket & press any other key to proceed to payment\n");
			scanf("%c",&addOn);
			if(addOn=='Y'||addOn=='y')
			{
				ticket_qty+=1;
				package='B';
			}
			break;
		}
			printf("\n----------------------------------------------------------------\n");
			break;
		
	Kid_Business:
		//Kid_Business	
		case'C':case'c':
			printf("\n\t\t== Kid_Business #%d ==\n\n",counter);
			printf("Enter ticket destination(1-Kuching; 2-Serian; 3-Kota Samarahan):");
			scanf("%d",&ticket_dest);
			
			switch(ticket_dest)
		{
			
		//Kuching
		case 1:
		strcpy(ticket[counter].ticket_dest, "Kid_Business-Kuching");	
		seat_type7:
			fflush(stdin);
			printf("Enter type of seat\t\t\t(1-Normal;2-Premium):");
			scanf("%c",&seat_type);
			
			if(*Stype=='1')
			{
				ticket[counter].charge=6.25;
				ticket[counter].Premium='-';
			}
			else if(*Stype=='2')
			{	
				ticket[counter].charge=7.75;
				ticket[counter].Premium='1';
			}
			else
			{
				printf("ERROR-Invalid Input\n");
				goto seat_type7;
			}
			
		Food7:
			fflush(stdin);
			printf("Do you need food? \t\t\t\t    (Y/N):");
			scanf("%c",&Food);
			
			if(*fOOd=='Y'||*fOOd=='y')
			{
				ticket[counter].Food='1';
				ticket[counter].charge+=3.5;
			}
			else if(*fOOd=='N'||*fOOd=='n')
			{
				ticket[counter].Food='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Food7;
			}
			
			Drink7:
			fflush(stdin);
			printf("Do you need drinks? \t\t\t\t    (Y/N):");
			scanf("%c",&Drink);
			
			if(*dRink=='Y'||*dRink=='y')
			{
				ticket[counter].Drink='1';
				ticket[counter].charge+=1.2;
			}
			else if(*fOOd=='N'||*dRink=='n')
			{
				ticket[counter].Drink='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Drink7;
			}
			
			//addOn	
			fflush(stdin);
			printf("\nPress 'Y' to add-on 1 more ticket & press any other key to proceed to payment\n");
			scanf("%c",&addOn);
			if(addOn=='Y'||addOn=='y')
			{
				ticket_qty+=1;
				package='C';
			}
			printf("\n----------------------------------------------------------------\n");
			break;
			
		//Serian
		case 2:
		strcpy(ticket[counter].ticket_dest, "Kid_Business-Serian");	
		seat_type8:
			
			fflush(stdin);
			printf("Enter type of seat \t\t\t(1-Normal;2-Premium):"),counter;
			scanf("%c",&seat_type);
			
			if(*Stype=='1')
			{
				ticket[counter].charge=12;
				ticket[counter].Premium='-';
			}
			else if(*Stype=='2')
			{
				ticket[counter].Premium='1';
				ticket[counter].charge=15;
			}
			else
			{
				printf("ERROR-Invalid Input\n");
				goto seat_type8;
			}
			
		Food8:
					
			fflush(stdin);
			printf("Do you need food? \t\t\t\t    (Y/N):");
			scanf("%c",&Food);
			
			if(*fOOd=='Y'||*fOOd=='y')
			{
				ticket[counter].Food='1';
				ticket[counter].charge+=3.5;	
			}
			else if(*fOOd=='N'||*fOOd=='n')
			{
				ticket[counter].Food='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Food8;
			}
			
			Drink8:
					
			fflush(stdin);
			printf("Do you need drinks? \t\t\t\t    (Y/N):");
			scanf("%c",&Drink);
			
			if(*dRink=='Y'||*dRink=='y')
			{
				ticket[counter].Drink='1';
				ticket[counter].charge+=1.2;	
			}
			else if(*dRink=='N'||*dRink=='n')
			{
				ticket[counter].Drink='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Drink8;
			}
			
			//addOn	
			fflush(stdin);
			printf("\nPress 'Y' to add-on 1 more ticket & press any other key to proceed to payment\n");
			scanf("%c",&addOn);
			if(addOn=='Y'||addOn=='y')
			{
				ticket_qty+=1;
				package='C';
			}
		
			printf("\n----------------------------------------------------------------\n");
			break;
			
			
		//Kota Samarahan
		case 3:
		strcpy(ticket[counter].ticket_dest, "Kid_Business-Kota Samarahan");
		seat_type9:
			
			fflush(stdin);
			printf("Enter type of seat \t\t\t(1-Normal;2-Premium):"),counter;
			scanf("%c",&seat_type);
			
			if(*Stype=='1')
			{
				ticket[counter].charge=9;
				ticket[counter].Premium='-';
			}
			else if(*Stype=='2')
			{
				ticket[counter].Premium='1';
				ticket[counter].charge=10;
			}
			else
			{
				printf("ERROR-Invalid Input\n");
				goto seat_type9;
			}
				
			Food9:	
			fflush(stdin);
			printf("Do you need food? \t\t\t    (Y/N):");
			scanf("%c",&Food);
			
			if(*fOOd=='Y'||*fOOd=='y')
			{
				ticket[counter].Food='1';
				ticket[counter].charge+=3.5;	
			}
			else if(*fOOd=='N'||*fOOd=='n')
			{
				ticket[counter].Food='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Food9;
			}
			
			Drink9:	
			fflush(stdin);
			printf("Do you need drinks? \t\t\t    (Y/N):");
			scanf("%c",&Drink);
			
			if(*dRink=='Y'||*dRink=='y')
			{
				ticket[counter].Drink='1';
				ticket[counter].charge+=1.2;	
			}
			else if(*dRink=='N'||*dRink=='n')
			{
				ticket[counter].Drink='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Drink9;
			}
			
			//addOn	
			fflush(stdin);
			printf("\nPress 'Y' to add-on 1 more ticket & press any other key to proceed to payment\n");
			scanf("%c",&addOn);
			if(addOn=='Y'||addOn=='y')
			{
				ticket_qty+=1;
				package='C';
			}
			break;
		}	
			printf("\n----------------------------------------------------------------\n");
			break;
		
	Kid_Economy:
		//Kid_Economy	
		case'D':case'd':
			printf("\n\t\t== Kid_Economy #%d ==\n\n",counter);
			printf("Enter ticket destination(1-Kuching; 2-Serian; 3-Kota Samarahan):");
			scanf("%d",&ticket_dest);
			
			switch(ticket_dest)
		{
			
		//Kuching
		case 1:
		strcpy(ticket[counter].ticket_dest, "Kid_Economy-Kuching");	
		seat_type10:
			fflush(stdin);
			printf("Enter type of seat\t\t\t(1-Normal;2-Premium):");
			scanf("%c",&seat_type);
			
			if(*Stype=='1')
			{
				ticket[counter].charge=5.25;
				ticket[counter].Premium='-';
			}
			else if(*Stype=='2')
			{	
				ticket[counter].charge=6.25;
				ticket[counter].Premium='1';
			}
			else
			{
				printf("ERROR-Invalid Input\n");
				goto seat_type10;
			}
			
		Food10:
			fflush(stdin);
			printf("Do you need food? \t\t\t\t    (Y/N):");
			scanf("%c",&Food);
			
			if(*fOOd=='Y'||*fOOd=='y')
			{
				ticket[counter].Food='1';
				ticket[counter].charge+=3;
			}
			else if(*fOOd=='N'||*fOOd=='n')
			{
				ticket[counter].Food='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Food10;
			}
			
			Drink10:
			fflush(stdin);
			printf("Do you need drinks? \t\t\t\t    (Y/N):");
			scanf("%c",&Drink);
			
			if(*dRink=='Y'||*dRink=='y')
			{
				ticket[counter].Drink='1';
				ticket[counter].charge+=1;
			}
			else if(*fOOd=='N'||*dRink=='n')
			{
				ticket[counter].Drink='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Drink10;
			}
			
			//addOn	
			fflush(stdin);
			printf("\nPress 'Y' to add-on 1 more ticket & press any other key to proceed to payment\n");
			scanf("%c",&addOn);
			if(addOn=='Y'||addOn=='y')
			{
				ticket_qty+=1;
				package='D';
			}
			printf("\n----------------------------------------------------------------\n");
			break;
			
		//Serian
		case 2:
		strcpy(ticket[counter].ticket_dest, "Kid_Economy-Serian");	
		seat_type11:
			
			fflush(stdin);
			printf("Enter type of seat \t\t\t(1-Normal;2-Premium):"),counter;
			scanf("%c",&seat_type);
			
			if(*Stype=='1')
			{
				ticket[counter].charge=9;
				ticket[counter].Premium='-';
			}
			else if(*Stype=='2')
			{
				ticket[counter].Premium='1';
				ticket[counter].charge=12;
			}
			else
			{
				printf("ERROR-Invalid Input\n");
				goto seat_type11;
			}
			
		Food11:
					
			fflush(stdin);
			printf("Do you need food? \t\t\t\t    (Y/N):");
			scanf("%c",&Food);
			
			if(*fOOd=='Y'||*fOOd=='y')
			{
				ticket[counter].Food='1';
				ticket[counter].charge+=3;	
			}
			else if(*fOOd=='N'||*fOOd=='n')
			{
				ticket[counter].Food='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Food11;
			}
			
			Drink11:
					
			fflush(stdin);
			printf("Do you need drinks? \t\t\t\t    (Y/N):");
			scanf("%c",&Drink);
			
			if(*dRink=='Y'||*dRink=='y')
			{
				ticket[counter].Drink='1';
				ticket[counter].charge+=1;	
			}
			else if(*dRink=='N'||*dRink=='n')
			{
				ticket[counter].Drink='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Drink11;
			}
			
			//addOn	
			fflush(stdin);
			printf("\nPress 'Y' to add-on 1 more ticket & press any other key to proceed to payment\n");
			scanf("%c",&addOn);
			if(addOn=='Y'||addOn=='y')
			{
				ticket_qty+=1;
				package='D';
			}
			printf("\n----------------------------------------------------------------\n");
			break;
			
			
		//Kota Samarahan
		case 3:
		strcpy(ticket[counter].ticket_dest, "Kid_Economy-Kota Samarahan");
		seat_type12:
			
			fflush(stdin);
			printf("Enter type of seat \t\t\t(1-Normal;2-Premium):"),counter;
			scanf("%c",&seat_type);
			
			if(*Stype=='1')
			{
				ticket[counter].charge=7.85;
				ticket[counter].Premium='-';
			}
			else if(*Stype=='2')
			{
				ticket[counter].Premium='1';
				ticket[counter].charge=8.5;
			}
			else
			{
				printf("ERROR-Invalid Input\n");
				goto seat_type12;
			}
				
			Food12:	
			fflush(stdin);
			printf("Do you need food? \t\t\t    (Y/N):");
			scanf("%c",&Food);
			
			if(*fOOd=='Y'||*fOOd=='y')
			{
				ticket[counter].Food='1';
				ticket[counter].charge+=3;	
			}
			else if(*fOOd=='N'||*fOOd=='n')
			{
				ticket[counter].Food='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Food12;
			}
			
			Drink12:	
			fflush(stdin);
			printf("Do you need drinks? \t\t\t    (Y/N):");
			scanf("%c",&Drink);
			
			if(*dRink=='Y'||*dRink=='y')
			{
				ticket[counter].Drink='1';
				ticket[counter].charge+=1;	
			}
			else if(*dRink=='N'||*dRink=='n')
			{
				ticket[counter].Drink='-';
				ticket[counter].charge+=0;
			}
			else
			{
				printf("ERROR-Input Unclear\n");
				printf("Please try again\n");
				goto Drink12;
			}
			
			//addOn	
			fflush(stdin);
			printf("\nPress 'Y' to add-on 1 more ticket & press any other key to proceed to payment\n");
			scanf("%c",&addOn);
			if(addOn=='Y'||addOn=='y')
			{
				ticket_qty+=1;
				package='D';
			}
			break;
			
			default:
			printf("ERROR-Invalid Input\n");
			printf("SORRY, the system doesn't recognize the category entered\n");
			printf("Please try again\n");
			goto Adult_Business;
		}
			printf("\n----------------------------------------------------------------\n");
			break;
	};
 
}


//review booking before saving it into history.txt and receipt.txt
void ReviewOrder()
{	
	printf("\n\t\t\t\t  ======================================================\n");
	printf("\t\t\t\t\t\t      Booking Details");
	printf("\n\t\t\t\t  ======================================================\n\n");
	printf("   Ref. No.          Package                           Number of Ticket       Premium        Food      Drink   Amount(RM)");
	printf("\n ______________________________________________________________________________________________________________________\n");
	for(counter=1;counter<=ticket_qty;counter++)
	{
		
		printf("	D%.2d     %-35s                                         1       %c       %c       %c       %5.2f\n"
		,counter,ticket[counter].ticket_dest,ticket[counter].Premium,ticket[counter].Food,ticket[counter].Drink,ticket[counter].charge);
	}
		printf("\n ______________________________________________________________________________________________________________________\n");
		printf("\t\t\t\t\t\t\t\t\t\t\t\t\tTotal=RM %5.2f\n",S_Charge);
		
	printf("\n **********************************************************************************************************************\n\n");

}

//used to save all transaction
void SaveTransaction()
{	
	//random ref no generator for easier referencing
	srand(time(NULL));
	int Ref_No=rand()%99999;
	
	//To save data into receipt.txt
	FILE *fhistory;
	char* filename = "history.txt";
	fhistory=fopen(filename,"a");
	
	fprintf(fhistory," ______________________________________________________________________________________________________________________\n\n");
	fprintf(fhistory,"  #%.5d\n",Ref_No);
		
	for(counter=1;counter<=ticket_qty;counter++)
	{
		fprintf(fhistory,"	D%.2d     %-35s                                         1       %c       %c       %c       %5.2f\n"
		,counter,ticket[counter].ticket_dest,ticket[counter].Premium,ticket[counter].Food,ticket[counter].Drink,ticket[counter].charge);	
	}
		fprintf(fhistory,"\n ----------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fhistory,"\t\t\t\t\t\t\t\t\t\t\t\tSub Total= RM %5.2f\n",S_Charge);
	
	fclose(fhistory);
	
	printf("\n  Ref.No.: #%.5d\n",Ref_No);
	printf("\n\t\t\t\t  ======================================================\n");
	printf("\t\t\t\t\t\t      Booking Confirmed");
	printf("\n\t\t\t\t  ======================================================\n\n");
	printf("   Ref. No.          Package                           Number of Ticket       Premium        Food      Drink   Amount(RM)");
	printf("\n ______________________________________________________________________________________________________________________\n");
	for(counter=1;counter<=ticket_qty;counter++)
	{	
		printf("	D%.2d     %-35s                                         1       %c       %c       %c       %5.2f\n"
		,counter,ticket[counter].ticket_dest,ticket[counter].Premium,ticket[counter].Food,ticket[counter].Drink,ticket[counter].charge);	
	}
		printf("\n ______________________________________________________________________________________________________________________\n");
		printf("\t\t\t\t\t\t\t\t\t\t\t\t\tTotal=RM %5.2f\n",S_Charge);
		
	printf("\n **********************************************************************************************************************\n");
	printf(" **Please proceed the payment at the counter to get your ticket(s)\n");
	printf("\n\t\t\t\t  ======================================================\n");
	printf("\t\t\t\t\t\t\tThank you");
	printf("\n\t\t\t\t  ======================================================\n\n\n");

}


// used to print out the receipt of single transaction into a .txt file
void PrintReceipt()
{
	//random ref no generator for easier referencing
	srand(time(NULL));
	int Ref_No=rand()%99999;
	
	
	FILE *fReceipt;
	char* filename = "receipt.txt";
	fReceipt=fopen(filename,"w");
	
	fprintf(fReceipt," ______________________________________________________________________________________________________________________\n\n");
	fprintf(fReceipt,"  #%.5d\n",Ref_No);
	fprintf(fReceipt,"\n\t\t\t\t  ======================================================\n");
	fprintf(fReceipt,"\t\t\t\t\t\t       Booking History");
	fprintf(fReceipt,"\n\t\t\t\t  ======================================================\n\n");
	fprintf(fReceipt," ______________________________________________________________________________________________________________________\n");
	fprintf(fReceipt,"\n   Ref. No.          Package                           Number of Ticket       Premium        Food      Drink   Amount(RM)\n");
			
	for(counter=1;counter<=ticket_qty;counter++)
	{
		fprintf(fReceipt,"	D%.2d     %-35s                                         1       %c       %c       %c       %5.2f\n"
		,counter,ticket[counter].ticket_dest,ticket[counter].Premium,ticket[counter].Food,ticket[counter].Drink,ticket[counter].charge);	
	}
		fprintf(fReceipt,"\n ----------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fReceipt,"\t\t\t\t\t\t\t\t\t\t\t\tSub Total= RM %5.2f\n",S_Charge);
		fprintf(fReceipt,"\n **********************************************************************************************************************\n");
		fprintf(fReceipt," **Please proceed the payment at the counter to get your ticket(s)\n");
		fprintf(fReceipt,"\n\t\t\t\t  ======================================================\n");
		fprintf(fReceipt,"\t\t\t\t\t\t\tThank you");
		fprintf(fReceipt,"\n\t\t\t\t  ======================================================\n\n\n");
	
	fclose(fReceipt);
	
}


//used to view history
void history()
{
	int clrH;
	fflush(stdin);
	printf("\n\t\t\t\t  ======================================================\n");
	printf("\t\t\t\t\t\t       Booking History");
	printf("\n\t\t\t\t  ======================================================\n\n");
	printf(" ______________________________________________________________________________________________________________________\n\n");
	printf("   Ref. No.          Package                           Number of Ticket       Premium        Food      Drink   Amount(RM)\n");
	
    FILE *fhistory;
    char history[99999];
    char* filename = "history.txt";
 
 	//Open History
    fhistory = fopen(filename, "r");
    if (fhistory == NULL)
	{
        printf("Could not open file %s\n",filename);
    }
    while (fgets(history,99999, fhistory) != NULL)
        printf("%s", history);
    fclose(fhistory);
    
    printf("\n ______________________________________________________________________________________________________________________\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t  Total = RM %5.2f\n",T_Charge);
    
    printf("\n\t\t\t\t\t     ==  Press 'X' to CLEAR HISTORY  ==\n");
    printf("\nPress any key to continue...");
	scanf("%c",&clrH);
	if(clrH=='X'||clrH=='x')
	{
		printf("Press '1' to confirm CLEAR HISTORY\n");
		scanf("%d",&clrH);
		if (clrH==1)
		{
			T_Charge=0;
			clearHistory();
		}
	}
}

//used to clear history
void clearHistory()
{
	FILE *fhistory;
	
    char* filename = "history.txt";
 	
 	//Overwrite the history to clear it
    fhistory = fopen(filename, "w");
    
    	fprintf(fhistory,"");
    
    fclose(fhistory);
}
