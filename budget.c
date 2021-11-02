#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myFuncs.h"

#define YEAR 12  // one year
#define CATS 7   // budget categories
#define LEN 20   // category length

struct month_def
{
	// budget categories
	char cat[CATS][LEN];
	double data[CATS];
};
typedef struct month_def month;

void updateDB(char outFile[], month db[]);
void readBudget(FILE *ifp, month *budgetMaster);
void copyData(month budgetMaster, month db[]);
void zeroData(month db[]);
void readDB(FILE *ifp2, month db[]);
void mainMenu(month db[], month budgetMaster, char cal[YEAR][10], char outFile[]);
int mainOption();
int entryMenu();
void enterData(month db[], char cal[YEAR][10], month budgetMaster, char outFile[]);
double calcBudTotal(month budgetMaster);
void printBudget(month budgetMaster);
int selectMonth(char cal[YEAR][10]);
void printMonth(month db[], int monthVal, char cal[YEAR][10], month budgetMaster);
void yearReport(month budgetMaster, month db[]);
int selectCat(month db[]);
double recordVal();
void enterVal(double val, int cat, int cal, month db[], month budgetMaster);
double savingsBal (month db[]);
double spendTotal(month db[], int month);
void sortSpending(int cats, double arr[], month budgetMaster);
void printArr(int size, double arr[], int catArr[], month budgetMaster);

int main(int argc, char *argv[])
{
	// check for 3 command line arguments
	if (argc != 3)
	{
		printf("Syntax Error: please use ./<exec> <inFile> <inFile2> format\n");
		exit(1);
	}

	FILE *ifp = NULL;

	// open budget text file for reading
	ifp = fopen(argv[1], "r");

	// check that first input file opened correctly
	if (ifp == NULL)
	{
		printf("Error: could not open %s for reading\n", argv[1]);
		exit(1);
	}

	FILE *ifp2 = NULL;

	// open database text file for reading
	ifp2 = fopen(argv[2], "r");

	// check that second input file opened correctly
	if (ifp2 == NULL)
	{
		printf("Error: could not open %s for reading\n", argv[2]);
		exit(1);
	}

	month budgetMaster;  // budget data
	month db[YEAR];      // budget database

	month *B = NULL;
	B = &budgetMaster;

	// 2d array storing month names
	char cal[YEAR][10] = {
							{"January"},
							{"February"},
							{"March"},
							{"April"},
							{"May"},
							{"June"},
							{"July"},
							{"August"},
							{"September"},
							{"October"},
							{"November"},
							{"December"}
						};

	// scan in budget data from text file to budgetMaster
	readBudget(ifp, B);
	fclose(ifp);

	// copy budget categories to database
	copyData(budgetMaster, db);
	// zero out database
	zeroData(db);

	// scan in stored data from database text file to db
	readDB(ifp2, db);
	fclose(ifp2);

	printf("Welcome to BudgetC!\n");

	// display main menu, process user selection
	mainMenu(db, budgetMaster, cal, argv[2]);

	printf("\nGoodbye :)\n");

	return 0;
}
