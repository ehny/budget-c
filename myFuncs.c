#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myFuncs.h"

#define YEAR 12
#define CATS 7
#define LEN 20

struct month_def
{
	char cat[CATS][LEN];
	double data[CATS];
};
typedef struct month_def month;

// update database text file with any user entries
void updateDB(char outFile[], month db[])
{
	FILE *ofp = NULL;

	// open database text file for writing 
	ofp = fopen(outFile, "w");

	// check that output file opened correctly
	if (ofp == NULL)
	{
		printf("Error: could not open %s for writing\n", outFile);
		exit(1);
	}

	int j = 0;
	int k = 0;

	for  (j = 0; j < YEAR; j++)
	{
		for (k = 0; k < CATS; k++)
		{
			fprintf(ofp, "%lf\n", db[j].data[k]);
		}

	}

	fclose(ofp);

}

// print sorted values along with associated categories
void printArr(int size, double arr[], int catArr[], month budgetMaster)
{
	int l = 0;

	printf("\nExpense totals sorted from highest to lowest:\n\n");
	printf("%-20s %-11s\n", "Category", "Yearly Spend");
	printf("------------------------------------------------------\n");

	for (l = 0; l < size; l++)
	{
		printf("%-20s $%10.2f\n", budgetMaster.cat[catArr[l]], arr[l]);
	}
}

// sort yearly total spending values
void sortSpending(int cats, double arr[], month budgetMaster)
{

	int j = 0;
	int endPos = cats; // 5 category values to sort
	int swap = 0; // swap did not occur
	int catArr[] = {0, 1, 2, 3, 4}; // array storing int values corresponding to categories

	// repeat comparison sets (cats - 1) times
	for (j = 0; j < endPos - 1; j++)
	{
		int i = 0;
		double tmp = 0;
		int tmpCat = -1; // temp storage location for category value

		// repeat comparisons in each set (cats - 1) times
		for (i = 0; i < cats - 1; i++)
		{
			// swap values if value on left is smaller than on right
			// also swap corresponding category values in catArr
			if (arr[i] < arr[i+1])
			{
				tmp = arr[i];              // store value to be swapped
				tmpCat = catArr[i];        // store category of value to be swapped
				arr[i] = arr[i+1];         // swap value, part 1
				catArr[i] = catArr[i+1];   // swap category, part 1
				arr[i+1] = tmp;            // swap value, part 2
				catArr[i+1] = tmpCat;      // swap category, part 2
				swap = 1;                  // a swap occured
			}
		}
		// reduce index of last comparison by 1 after each full pass
		cats--;

		// exit function if no swap occured after full pass (sorting complete)
		if (swap == 0)
		{
			break;
		}
		swap = 0; // reset swap identifier
	}
	// print sorted values along with associated categories
	printArr(endPos, arr, catArr, budgetMaster);
}

// calculate total spending across categories
double spendTotal(month db[], int month)
{
	int i = 0; 
	double spend = 0;

	for (i = 0; i < 5; i++)
	{
		spend = spend + db[month].data[i];
	}
	
	return spend;
}

// calculate savings balance
double savingsBal(month db[])
{
	int i = 0; 
	double savings = 0;

	for (i = 0; i < YEAR; i++)
	{
		savings = savings + db[i].data[6];
	}
	
	return savings;
}

// store recorded value in database
void enterVal(double val, int cat, int cal, month db[], month budgetMaster)
{
	int adjustedMonth = cal - 1;
	// add recorded value to array, confim data entry, display budgeted value
	db[adjustedMonth].data[cat] = db[adjustedMonth].data[cat] + val;
	printf("Success! An entry for $%.2f has been recorded.\n", val);
	printf("---------------------------------------\n");
	printf("Your %s balance is now: $%.2f\n", db[adjustedMonth].cat[cat], db[adjustedMonth].data[cat]);
	printf("You budgeted $%.2f for %s\n", budgetMaster.data[cat], budgetMaster.cat[cat]);
}

// record a numeric value from user
double recordVal()
{
	double val = 0;
	char dump = 0;

	printf("Enter an amount: $");
	scanf("%lf%c", &val, &dump);

	return val;
}

// display expense category menu, scan in user choice
int selectCat(month db[])
{
	int cat = 0;
	char dump = 0;

	printf("Data Entry > Expense Category Menu\n");
	printf("Choose an expense category\n");
	printf("=======================================\n");
	printf("Enter 1 ... for %-20s\n", db[0].cat[0]);
	printf("Enter 2 ... for %-20s\n", db[0].cat[1]);
	printf("Enter 3 ... for %-20s\n", db[0].cat[2]);
	printf("Enter 4 ... for %-20s\n", db[0].cat[3]);
	printf("Enter 5 ... for %-20s\n", db[0].cat[4]);
	printf("=======================================\n");
	printf("Expense category: ");
	scanf("%d%c", &cat, &dump);

	// exit program for invalid entry
	if (cat < 1 || cat > 5)
	{
		printf("Invalid entry: quitting\n");
		exit(1);
	}

	// confirm user selection
	printf("%s successfully selected\n\n", db[0].cat[cat-1]);

	return cat - 1; // return adjusted category value
}

// display yearly report
void yearReport(month budgetMaster, month db[])
{
	// store yearly totals
	double cat0 = 0;
	double cat1 = 0;
	double cat2 = 0;
	double cat3 = 0;
	double cat4 = 0;
	double cat5 = 0; // total income
	double cat6 = 0; // total savings

	int i = 0;
	int sortCats = 5; // categories to sort (excluding income and savings)

	// array to store total yearly spending per category
	double yearCats[5] = {0};

	// add up total spending/earning for the year
	for(i = 0; i < YEAR; i++)
	{
		cat0 = cat0 + db[i].data[0];
		cat1 = cat1 + db[i].data[1];
		cat2 = cat2 + db[i].data[2];
		cat3 = cat3 + db[i].data[3];
		cat4 = cat4 + db[i].data[4];
		cat5 = cat5 + db[i].data[5];
		cat6 = cat6 + db[i].data[6];	
	}

	// assign total spend values to array for sorting
	yearCats[0] = cat0;
	yearCats[1] = cat1;
	yearCats[2] = cat2;
	yearCats[3] = cat3;
	yearCats[4] = cat4;

	// display yearly total spending/earning along with budgeted values
	printf("\nMain Menu > Yearly Report\n");
	printf("Here is your yearly report:\n\n");
	printf("%-20s %-11s    %-11s\n", "Category", "Budgeted", "Yearly Spend");
	printf("-------------------------------------------------------\n");
	printf("%-20s $%10.2f    $%10.2f\n", budgetMaster.cat[0], budgetMaster.data[0] * YEAR, cat0);
	printf("%-20s $%10.2f    $%10.2f\n", budgetMaster.cat[1], budgetMaster.data[1] * YEAR, cat1);
	printf("%-20s $%10.2f    $%10.2f\n", budgetMaster.cat[2], budgetMaster.data[2] * YEAR, cat2);
	printf("%-20s $%10.2f    $%10.2f\n", budgetMaster.cat[3], budgetMaster.data[3] * YEAR, cat3);
	printf("%-20s $%10.2f    $%10.2f\n", budgetMaster.cat[4], budgetMaster.data[4] * YEAR, cat4);
	printf("\n%-20s %-11s    %-11s\n", "Cash", "Estimated", "Actual");
	printf("-------------------------------------------------------\n");
	printf("%-20s $%10.2f    $%10.2f\n",  budgetMaster.cat[5], budgetMaster.data[5] * YEAR, cat5);
	printf("%-20s $%10.2f    $%10.2f\n",  budgetMaster.cat[6], budgetMaster.data[6] * YEAR, cat6);
	
	// sort and display spending from high to low
	sortSpending(sortCats, yearCats, budgetMaster);
}

// print montly report
void printMonth(month db[], int monthVal, char cal[YEAR][10], month budgetMaster)
{
	int i = monthVal -1;         // adjust month value
	double savings = 0;          // savings balance
	double spend = 0;            // monthly spending
	double savContrib = 0;       // saving contribution
	double estimatedIncome = 0;  // estimated earnings
	double bal = 0;              // cash remaining after expenses and savings

	savings = savingsBal(db);                   // calculate savings balance
	spend = spendTotal(db, i);                  // calculate spending across categories
	savContrib = db[i].data[6];                 // savings contribution
	estimatedIncome = budgetMaster.data[5];     // estimated earnings 
	bal = estimatedIncome - savContrib - spend; // calculate cash remaining

	// display current spend, amount budgeted, amount remaining across categories
	printf("\nMain Menu > Monthly Report\n");
	printf("Here is your monthly report for %s:\n\n", cal[i]);
	printf("%-20s %-11s     %-11s     %-11s\n", "Category", "Budgeted", "Spent", "Remaining");
	printf("-------------------------------------------------------------------\n");
	printf("%-20s $%10.2f     $%10.2f     $%10.2f\n", db[i].cat[0], budgetMaster.data[0], db[i].data[0], budgetMaster.data[0] - db[i].data[0]);
	printf("%-20s $%10.2f     $%10.2f     $%10.2f\n", db[i].cat[1], budgetMaster.data[1], db[i].data[1], budgetMaster.data[1] - db[i].data[1]);
	printf("%-20s $%10.2f     $%10.2f     $%10.2f\n", db[i].cat[2], budgetMaster.data[2], db[i].data[2], budgetMaster.data[2] - db[i].data[2]);
	printf("%-20s $%10.2f     $%10.2f     $%10.2f\n", db[i].cat[3], budgetMaster.data[3], db[i].data[3], budgetMaster.data[3] - db[i].data[3]);
	printf("%-20s $%10.2f     $%10.2f     $%10.2f\n", db[i].cat[4], budgetMaster.data[4], db[i].data[4], budgetMaster.data[4] - db[i].data[4]);
	printf("\n%-20s %-11s     %-11s\n", "Cash", "Budgeted", "Current");
	printf("-------------------------------------------------------------------\n");
	printf("%-20s $%10.2f     $%10.2f\n", db[i].cat[5], budgetMaster.data[5], db[i].data[5]);
	printf("%-20s $%10.2f     $%10.2f\n", db[i].cat[6], budgetMaster.data[6], db[i].data[6]);
	printf("\nSavings Balance:\n");
	printf("-------------------------------------------------------------------\n");
	printf("Contributions to date: $%.2f\n", savings);
	printf("\nSpend Analysis:\n"); 
	printf("-------------------------------------------------------------------\n");
	printf("Monthly expenses:       $%10.2f\n", spend);
	printf("Savings contributions:  $%10.2f\n", db[i].data[6]);
	printf("Estimated income:       $%10.2f\n", budgetMaster.data[5]);
	printf("Remaining balance:      $%10.2f\n", bal);
	printf("\nAlerts:\n");
	printf("-------------------------------------------------------------------\n");
	
	int k = 0;
	int overspent = 0; // overspent set to false

	// check for overspending across 5 budget categories
	for (k = 0; k < 5; k++)
	{
		// display alert for overspent category
		if (db[i].data[k] > budgetMaster.data[k])
		{
			printf("Alert! Budget exceeded for %s\n", db[i].cat[k]);
			overspent = 1;
		}
	}

	// message for staying within budget
	if (overspent == 0)
	{
		printf("Nice job! Your spending is within budget.\n");
	}
	
}

// display month menu, scan in user choice
int selectMonth(char cal[YEAR][10])
{
	int month = 0;
	char dump = 0;

	printf("\nMain Menu > Select Month Menu\n");
	printf("Select a month:\n");
	printf("=============================\n");
	printf("Enter  1 ... for %-10s\n", cal[0]);
	printf("Enter  2 ... for %-10s\n", cal[1]);
	printf("Enter  3 ... for %-10s\n", cal[2]);
	printf("Enter  4 ... for %-10s\n", cal[3]);
	printf("Enter  5 ... for %-10s\n", cal[4]);
	printf("Enter  6 ... for %-10s\n", cal[5]);
	printf("Enter  7 ... for %-10s\n", cal[6]);          
	printf("Enter  8 ... for %-10s\n", cal[7]);
	printf("Enter  9 ... for %-10s\n", cal[8]);
	printf("Enter 10 ... for %-10s\n", cal[9]);
	printf("Enter 11 ... for %-10s\n", cal[10]);
	printf("Enter 12 ... for %-10s\n", cal[11]);
	printf("=============================\n");
	printf("Month: ");
	scanf("%d%c", &month, &dump);

	// quit program for invalid entry
	if (month < 1 || month > 12)
	{
		printf("Invalid Entry: Quitting\n");
		exit(1);
	}

	// confirm user selection
	printf("%s successfully selected\n", cal[month-1]);
	
	return month;
}

// sum up expenses across categories 
double calcBudTotal(month budgetMaster)
{
	double total = 0;
	int i = 0;

	for (i = 0; i < 5; i++)
	{
		total = total + budgetMaster.data[i];
	}

	return total;
}

// prints monthly budget report
void printBudget(month budgetMaster)
{
	// display budget categories and amounts
	printf("\nMain Menu > Budget Summary\n");
	printf("Here is your budget summary:\n\n");
	printf("%-20s %-11s\n", "Category", "Amount");
	printf("--------------------------------------\n");
	printf("%-20s $%10.2f\n", budgetMaster.cat[0], budgetMaster.data[0]);
	printf("%-20s $%10.2f\n", budgetMaster.cat[1], budgetMaster.data[1]);
	printf("%-20s $%10.2f\n", budgetMaster.cat[2], budgetMaster.data[2]);
	printf("%-20s $%10.2f\n", budgetMaster.cat[3], budgetMaster.data[3]);
	printf("%-20s $%10.2f\n", budgetMaster.cat[4], budgetMaster.data[4]);
	printf("\nCash\n");
	printf("--------------------------------------\n");
	printf("%-20s $%10.2f\n", budgetMaster.cat[5], budgetMaster.data[5]);
	printf("%-20s $%10.2f\n", budgetMaster.cat[6], budgetMaster.data[6]);

	double expenTotal = 0;
	double budTotal = 0;
	
	// sum up expenses across categories
	expenTotal = calcBudTotal(budgetMaster);
	// add savings contribution
	budTotal = expenTotal + budgetMaster.data[6]; 

	// display expense totals and alerts
	printf("\nBudget Analysis:\n");
	printf("--------------------------------------\n");
	printf("Total expenses:      $%10.2f\n", expenTotal);
	printf("After savings:       $%10.2f\n", budTotal);
	printf("\nAlerts:\n");
	printf("--------------------------------------\n");
	
	// alert for balanced budget
	if (budgetMaster.data[5] > budTotal)
	{
		printf("Congratulations! Your budget is balanced.\n");
		printf("Cash remaining after all expenses: $%.2f\n", budgetMaster.data[5] - budTotal);
	}
	// alert for non balanced budget
	else
	{
		printf("Alert! Your budget is not balanced.\n");
		printf("You are $%.2f short\n", (budgetMaster.data[5] - budTotal) * -1);
	}
}

// display data entry menu, scan in user choice
int entryMenu()
{
	int option = -1;
	char dump = 0;

	printf("\n");
	printf("Main Menu > Data Entry Menu\n");
	printf("=============================================\n");
	printf("Enter 1 ... to record an expense\n");
	printf("Enter 2 ... to record a paycheck\n");
	printf("Enter 3 ... to record a savings contribution\n");
	printf("Enter 4 ... to return to the main menu\n");
	printf("=============================================\n");
	printf("Option: ");
	scanf("%d%c", &option, &dump);

	return option;

}

// process data entry menu
void enterData(month db[], char cal[YEAR][10], month budgetMaster, char outFile[])
{
	int month = 0;
	int cat = 0;
	double data = 0;
	int option = -1;

	// display month menu and scan in user choice
	month = selectMonth(cal);

	do {
		// display data entry menu and scan in user choice
		option = entryMenu();

		switch (option)
		{
			case 1: // record expense data
				printf("Record an expense selected\n\n");
				cat = selectCat(db); // display budget categories, scan in user choice
				data = recordVal(); // prompt for, scan in value
				enterVal(data, cat, month, db, budgetMaster); // store value in db
				updateDB(outFile, db); // write data to db.txt for storage
				break;
			case 2: // record income
				printf("Record income selected\n\n");
				cat = 5; // income stored at data[5]
				data = recordVal(); // prompt for, scan in value
				enterVal(data, cat, month, db, budgetMaster); // store value in db
				updateDB(outFile, db); // write data to db.txt for storage
				break;
			case 3:	// record savings contribution
				printf("Record savings selected\n\n"); 	
				cat = 6; // savings stored at data[6]
				data = recordVal(); // prompt for, scan in value
				enterVal(data, cat, month, db, budgetMaster); // store value in db
				updateDB(outFile, db); // write data to db.txt for storage
				break;
			case 4: // return to main menu
				printf("Returning to main menu...\n");
				break;
			default: // return to main menu for any invalid entry
				printf("Invalid entry: returning to main menu...\n");
				break;
		}
	// repeatedly prompt user while entry is valid
	} while (option == 1 || option == 2 || option == 3);

}

// display main menu, scan in user choice
int mainOption()
{
	int option = -1;
	char dump = 0;
	
	printf("\nBudgetC > Main Menu\n");
	printf("========================================\n");
	printf("Enter 1 ... to record data\n");
	printf("Enter 2 ... to print your budget\n");
	printf("Enter 3 ... to print a monthly report\n");
	printf("Enter 4 ... to print a yearly report\n");
	printf("Enter 0 ... to quit BudgetC\n");
	printf("========================================\n");
	printf("Option: ");
	scanf("%d%c", &option, &dump);

	return option;
}

// process user main menu selection
void mainMenu(month db[], month budgetMaster, char cal[YEAR][10], char outFile[])
{
	int month = -1;
	int option = -1;

	do {
		// display main menu and read in user choice
		option = mainOption();
	
		switch (option)
		{
			case 1: // record data
				enterData(db, cal, budgetMaster, outFile);
				break;
			case 2: // print budget
				printBudget(budgetMaster);
				break;
			case 3:	// select month, print montly report
				month = selectMonth(cal);
				printMonth(db, month, cal, budgetMaster);			
				break;
			case 4: // print yearly report
				yearReport(budgetMaster, db);
				break;
			case 0: // exit program
				printf("Exiting\n");
				break;
			default: // quit for any invalid entry
				printf("Invalid entry: quitting\n");
				break;
	
		}
	// repeatedly prompt user while entry is valid
	} while (option == 1 || option == 2 || option == 3 || option == 4);

}

// scan in stored data from database text file to db
void readDB(FILE *ifp2, month db[])
{

	int j = 0;
	int k = 0;

	for  (j = 0; j < YEAR; j++)
	{
		for (k = 0; k < CATS; k++)
		{
			fscanf(ifp2, "%lf", &db[j].data[k]);
		}

	}
}

// zero out all numeric values in db
void zeroData(month db[])
{

	int j = 0;
	int k = 0;

	for  (j = 0; j < YEAR; j++)
	{
		for (k = 0; k < CATS; k++)
		{
			db[j].data[k] = 0;
		}

	}
}

// copy budgetMaster to db array of structures
void copyData(month budgetMaster, month db[])
{
	int i = 0;

	for (i = 0; i < YEAR; i++)
	{
		db[i] = budgetMaster;
	}
}

// scan in budget data from text file to budgetMaster structure
void readBudget(FILE *ifp, month *budgetMaster)
{
	int i = 0;
	int j = 0;

	// scan in categories into 2d array
	for (i = 0; i < CATS; i++)
	{
		fscanf(ifp, "%s", budgetMaster->cat[i]);
	}

	// scan in values into array
	for (j = 0; j < CATS; j++)
	{
		fscanf(ifp, "%lf", &budgetMaster->data[j]);
	}

}
