#ifdef MYFUNCS_h
#define MYFUNCS_h

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

#endif
