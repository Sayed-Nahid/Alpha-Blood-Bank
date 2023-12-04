 /*****************************************************

* @authors  :  Mohammad Ullah (202-15-3833)     *

*          	   Sayed Nahid (202-15-3849)      	*

*          	  Radiful Islam (202-15-3837)      	*

*          	Mehedi Hasan Rudro (202-15-3845)  	*

*         Rashik Shahriar Akash (202-15-3825)  	*

*                                                	*

* @file 	:  main.c                            	*

* @modified :  Monday Nov 28, 2022 19:14:33 +06  	*

*****************************************************/


#include <math.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>


struct donor {

	int id;

	char name[50];

	int group;

	char rh;

	char address[200];

	long long int contact;

	int lastDonation;

	struct donor *prev;

	struct donor *next;

};


struct donor *head = NULL;

int didglobal = 202;


void savedb() {


	FILE *db;

	db = fopen("db.txt", "w");


	struct donor *temp = head;


	while (temp != NULL) {

       fprintf(db, "%d", temp->id);

       fprintf(db, "\n");

       fprintf(db, "%s", temp->name);

       fprintf(db, "\n");

       fprintf(db, "%d", temp->group);

       fprintf(db, "\n");

       fprintf(db, "%c", temp->rh);

       fprintf(db, "\n");

       fprintf(db, "%s", temp->address);

       fprintf(db, "\n");

       fprintf(db, "%lld", temp->contact);

       fprintf(db, "\n");

       fprintf(db, "%d", temp->lastDonation);

       fprintf(db, "\n");


       temp = temp->next;

	}

	fclose(db);

}


void loaddb() {

	int id;

	char name[50];

	int group;

	char rh;

	char address[200];

	long long int contact;

	int lastDonation;


	FILE *db;

	db = fopen("db.txt", "r");


	if (db == NULL) {

       return;

	}


	int i = 0;


	while (fscanf(db, "%d\n", &id) != EOF) {

       struct donor *temp = (struct donor *)malloc(sizeof(struct donor));

       temp->id = id;

       didglobal = id;

       didglobal++;

       fgets(name, 50, db);

       name[strlen(name) - 1] = '\0';

       strcpy(temp->name, name);

       fscanf(db, "%d\n", &group);

       temp->group = group;

       fscanf(db, "%c\n", &rh);

       temp->rh = rh;

       fgets(address, 200, db);

       address[strlen(address) - 1] = '\0';

       strcpy(temp->address, address);

       fscanf(db, "%lld\n", &contact);

       temp->contact = contact;

       fscanf(db, "%d\n", &lastDonation);

       temp->lastDonation = lastDonation;

       temp->next = NULL;

       if (head == NULL) {

     	  head = temp;

     	  head->prev = NULL;

       } else {

     	  struct donor *temp2 = head;

     	  while (temp2->next != NULL) {

     		  temp2 = temp2->next;

     	  }

     	  temp->prev = temp2;

     	  temp2->next = temp;

       }

       printf("%d\n", i);

       i++;

	}

	fclose(db);

}


void bloodGroup(int group, char rh) {

	switch (group) {

       case 1:

     	  printf("A");

     	  break;


       case 2:

     	  printf("B");

     	  break;


       case 3:

     	  printf("AB");

     	  break;


       case 4:

     	  printf("O");

     	  break;


       default:

     	  break;

	}


	if (rh == '+')

       printf("+(ve)");

	else

       printf("-(ve)");

}


int defaultPrompt() {

	int c;


	printf("\e[1;1H\e[2J");

	printf("\n\n");

	printf("\t/---------------------------------------------------------------\\\n");

	printf("\t|                                                      		 |\n");

	printf("\t|     Alpha Blood Bank Blood Donation Portal (v1.0 stable) 	 |\n");

	printf("\t|                                                      		 |\n");

	printf("\t|---------------------------------------------------------------|\n");

	printf("\t| Available Commands:                                  		 |\n");

	printf("\t|---------------------------------------------------------------|\n");

	printf("\t|                                                      		 |\n");

	printf("\t| 1. Find Blood                                        		 |\n");

	printf("\t| 2. Add new Donor to Database                         		 |\n");

	printf("\t| 3. Remove Donor from Database                        		 |\n");

	printf("\t| 4. List all Donors                                   		 |\n");

	printf("\t| 5. Update Donor Info                                 		 |\n");

	printf("\t| 6. Exit the program                                  		 |\n");

	printf("\t|                                                      		 |\n");

	printf("\t|---------------------------------------------------------------|\n");

	printf("\t| Example: Enter 6 to exit the program.                		 |\n");

	printf("\t\\---------------------------------------------------------------/\n\n");


	printf(" --> Enter a command: ");

	scanf("%d", &c);


	return c; // <-- Pass the command to the main program

}


void findBlood() {

	int found = 0;

	int group = 0;

	char rh;

	int bg = 0;

	printf("\n");

	printf("Blood Group: 1. A+(ve)    2. B+(ve)    3. AB+(ve)    4. O+(ve)\n    		 5. A-(ve)    6. B-(ve)    7. AB-(ve)    8. O-(ve)\n");

	printf("  		 : ");

	scanf("%d", &bg);

	switch (bg) {

       case 1:

     	  group = 1;

     	  rh = '+';

     	  break;


       case 2:

     	  group = 2;

     	  rh = '+';

     	  break;


       case 3:

     	  group = 3;

     	  rh = '+';

     	  break;


       case 4:

     	  group = 4;

     	  rh = '+';

     	  break;


       case 5:

     	  group = 1;

     	  rh = '-';

     	  break;


       case 6:

     	  group = 2;

     	  rh = '-';

     	  break;


       case 7:

     	  group = 3;

     	  rh = '-';

     	  break;


       case 8:

     	  group = 4;

     	  rh = '-';

     	  break;


       default:

     	  break;

	}


	struct donor *list = head;


	while (list != NULL) {

       if (list->group == group && ((list->rh) == rh)) {

     	  printf("\n");

     	  if ((list->lastDonation) > 90)

     		  printf("[More than 90 days since last donation]");

     	  else

     		  printf("[Less that 90 days since last donation]");

     	  printf("\n");

     	  printf("Donor ID: %d", list->id);

     	  printf("\n");

     	  printf("Donor Name: %s", list->name);

     	  printf("\n");

     	  printf("Blood Group: ");

     	  bloodGroup(list->group, list->rh);

     	  printf("\n");

     	  printf("Donor Address: %s", list->address);

     	  printf("\n");

     	  printf("Contact Number: %lld", list->contact);

     	  printf("\n");

     	  printf("Days Since Last Donation: %d days", list->lastDonation);

     	  printf("\n");

     	  printf("\n");

     	  found++;

       }


       list = list->next;

	}


	printf("\n");

	if (found == 0)

       printf("No Donors Found!\n");

	printf("Press ENTER to go back: ");

	getchar();

	getchar();

}


void listDonors(int p) {

	printf("\e[1;1H\e[2J");

	struct donor *temp = head;


	printf("\n");

	printf("\n");


	while (temp != NULL) {

       printf("\tDonor ID: %d", temp->id);

       printf("\n");

       printf("\tDonor Name: %s", temp->name);

       printf("\n");

       printf("\tBlood Group: ");

       bloodGroup(temp->group, temp->rh);

       printf("\n");

       printf("\tDonor Address: %s", temp->address);

       printf("\n");

       printf("\tContact Number: %lld", temp->contact);

       printf("\n");

       printf("\tDays Since Last Donation: %d days", temp->lastDonation);

       printf("\n");

       printf("\n");


       temp = temp->next;

	}


	if (p) {

       printf("Press ENTER to go back: ");

       getchar();

       getchar();

	}

}


void addDonor() {

	struct donor *temp = (struct donor *)malloc(sizeof(struct donor));

	printf("\e[1;1H\e[2J");

	printf("\n\n\t\t     >--> Adding New Donor to the Database <--< \n");

	printf("\n");

	printf("\n");

	printf("Name of the Donor: ");

	getchar();

	gets(temp->name);

	temp->id = didglobal;

	didglobal++;

	printf("\n");

	printf("Address of Donor: ");

	gets(temp->address);

	int bg;

	printf("\n");

	printf("Blood Group: 1. A+(ve)    2. B+(ve)    3. AB+(ve)    4. O+(ve)\n    		 5. A-(ve)    6. B-(ve)    7. AB-(ve)    8. O-(ve)\n");

	printf("  		 : ");

	scanf("%d", &bg);

	switch (bg) {

       case 1:

     	  temp->group = 1;

     	  temp->rh = '+';

     	  break;


       case 2:

     	  temp->group = 2;

     	  temp->rh = '+';

     	  break;


       case 3:

     	  temp->group = 3;

     	  temp->rh = '+';

     	  break;


       case 4:

     	  temp->group = 4;

     	  temp->rh = '+';

     	  break;


       case 5:

     	  temp->group = 1;

     	  temp->rh = '-';

     	  break;


       case 6:

     	  temp->group = 2;

     	  temp->rh = '-';

     	  break;


       case 7:

     	  temp->group = 3;

     	  temp->rh = '-';

     	  break;


       case 8:

     	  temp->group = 4;

     	  temp->rh = '-';

     	  break;


       default:

     	  break;

	}


	printf("\n");

	printf("Contact Number: ");

	scanf("%lld", &temp->contact);

	printf("\n");

	printf("Days Since Last Donation: ");

	scanf("%d", &temp->lastDonation);


	temp->next = NULL;


	if (head == NULL) {

       head = temp;

       head->prev = NULL;

	} else {

       struct donor *temp2 = head;

       while (temp2->next != NULL) {

     	  temp2 = temp2->next;

       }

       temp->prev = temp2;

       temp2->next = temp;

	}


	printf("\n");

	printf("--> Added Entry for %s with ID %d", temp->name, temp->id);

	printf("\n");

	printf("\n\t\t  		 >--> Press ENTER to go back <--< ");

	getchar();

	getchar();

}


void removeDonor() {

	char name[50];

	int id;

	listDonors(0);

	printf("Enter the ID of Donor to be removed: ");

	scanf("%d", &id);


	struct donor *temp = head;


	while (temp != NULL) {

       if (temp->id == id) {

     	  strcpy(name, temp->name);

     	  if (temp->prev == NULL && temp->next == NULL) {

     		  temp = NULL;

     		  free(temp);

     	  }


     	  else if (temp->prev != NULL && temp->next == NULL) {

     		  (temp->prev)->next = NULL;

     		  free(temp);

     	  }


     	  else if (temp->prev == NULL && temp->next != NULL) {

     		  (temp->next)->prev = NULL;

     		  head = temp->next;

     		  free(temp);

     	  }


     	  else {

     		  (temp->prev)->next = temp->next;

     		  (temp->next)->prev = temp->prev;

     		  free(temp);

     	  }


     	  printf("Deleted Entry for %s with ID %d\n", name, id);

     	  printf("Press ENTER to go back: ");

     	  getchar();

     	  getchar();


     	  break;

       }

       temp = temp->next;

	}

}


void updateDonor() {

	char name[50];

	int id;

	listDonors(0);

	printf("Enter the ID of Donor to be Updated: ");

	scanf("%d", &id);


	struct donor *temp = head;


	while (temp != NULL) {

       if (temp->id == id) {

     	  strcpy(name, temp->name);


     	  printf("Press 1 to Update Address or 2 to Update Contact. Press 0 to go back.\n");


     	  int l;

     	  char la[200];

     	  long long int lc;

     	  scanf("%d", &l);


     	  switch (l) {

     		  case 1: {

     			  printf(" --> Previous Address: %s\n", temp->address);

     			  printf(" --> New Address: ");

     			  getchar();

     			  gets(la);

     			  strcpy(temp->address, la);

     			  break;

     		  }


     		  case 2: {

     			  printf(" --> Previous Contact: %d\n", temp->contact);

     			  printf(" --> New Contact: ");

     			  scanf("%lld", &lc);

     			  temp->contact = lc;

     		  }


     		  case 0:

     			  break;


     		  default:

     			  break;

     	  }


     	  printf("Updated Entry for %s with ID %d\n", name, id);

     	  printf("Press ENTER to go back: ");

     	  getchar();

     	  getchar();


     	  break;

       }

       temp = temp->next;

	}

}


int main() {


	loaddb();

	while (1) {

       int c = 0;

       c = defaultPrompt();

       switch (c) {

     	  case 1:

     		  findBlood();

     		  break;


     	  case 2:

     		  addDonor();

     		  break;


     	  case 3:

     		  removeDonor();

     		  break;


     	  case 4:

     		  listDonors(1);

     		  break;


     	  case 5:

     		  updateDonor();

     		  break;


     	  case 6:

     		  return 0;


     	  default:

     		  c = 0;

     		  printf("Invalid Command!");

       }

       savedb();

	}

	return 0;

}
