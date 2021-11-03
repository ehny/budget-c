# BudgetC

BudgetC is a budgeting program designed to track a user's monthly budget for one calendar year. Specifically, it tracks expenditures in five user-defined categories, along with income and savings contributions. 

The [accompanying wiki](https://github.com/ehny/budget-c/wiki#about) has additional details about the program's structure and capabilities.

## About

BudgetC was submitted as a final project for Computer Science II, [CSC 250](https://catalog.dsu.edu/preview_course.php?catoid=29&coid=18532), at [Dakota State University](https://dsu.edu) during the Spring 2020 semester. The course instructor was [Joel Wohnoutka](https://dsu.edu/directory/wohnoutka-joel.html).

BudgetC implements the following topics discussed in the course:
- 2D Arrays
- Command Line Arguments
- File I/O
- Header Files
- Sorting
- Structures 

## Installation

### Program Files

This repository contains the following files:
|File|Description|
|:--|:--|
|`LICENSE`| The BudgetC license.|
|`bud.txt`| This file stores the user's budget.|
|`budget.c`| This is the main program file.|
|`db.txt`| This file stores the user's data.|
|`myFuncs.c`| This file contains the program's functions.|
|`myFuncs.h`| This is an included header file.|
|`README.md`| The program documentation.

### Launching BudgetC

Compile and launch BudgetC with the following  commands:
```
$ gcc budget.c myFuncs.c
$ ./a.out bud.txt db.txt
```
## Usage

### Using BudgetC

Please see [the repository Wiki](https://github.com/ehny/budget-c/wiki) for detailed program documentation. 😉

#### Main Menu
```
BudgetC > Main Menu
========================================
Enter 1 ... to record data
Enter 2 ... to print your budget
Enter 3 ... to print a monthly report
Enter 4 ... to print a yearly report
Enter 0 ... to quit BudgetC
========================================
Option: 
```

***

#### Sample Monthly Report

```
Main Menu > Monthly Report
Here is your monthly report for January:

Category             Budgeted        Spent           Remaining  
-------------------------------------------------------------------
Housing              $    200.00     $    200.00     $      0.00
Food                 $    200.00     $    100.00     $    100.00
Transport            $    200.00     $    100.00     $    100.00
Bills                $    200.00     $     50.00     $    150.00
Fun                  $    200.00     $     50.00     $    150.00

Cash                 Budgeted        Current    
-------------------------------------------------------------------
Income               $   2000.00     $   1000.00
Savings              $    100.00     $    100.00

Savings Balance:
-------------------------------------------------------------------
Contributions to date: $100.00

Spend Analysis:
-------------------------------------------------------------------
Monthly expenses:       $    500.00
Savings contributions:  $    100.00
Estimated income:       $   2000.00
Remaining balance:      $   1400.00

Alerts:
-------------------------------------------------------------------
Nice job! Your spending is within budget.
```

***

#### Sample Yearly Report

```
Main Menu > Yearly Report
Here is your yearly report:

Category             Budgeted       Yearly Spend
-------------------------------------------------------
Housing              $   2400.00    $    400.00
Food                 $   2400.00    $    200.00
Transport            $   2400.00    $    200.00
Bills                $   2400.00    $    100.00
Fun                  $   2400.00    $    100.00

Cash                 Estimated      Actual     
-------------------------------------------------------
Income               $  24000.00    $   4000.00
Savings              $   1200.00    $    200.00

Expense totals sorted from highest to lowest:

Category             Yearly Spend
------------------------------------------------------
Housing              $    400.00
Food                 $    200.00
Transport            $    200.00
Bills                $    100.00
Fun                  $    100.00
```
## Acknowledgement 

The author expresses his gratitude to [Joel Wohnoutka](https://dsu.edu/directory/wohnoutka-joel.html), the course instructor, an outstanding teacher who inspires his students to write clear, well-commented, and neatly formatted code. 

## License 

BudgetC is released under [MIT license](https://github.com/ehny/budget-c/blob/main/LICENSE). 
