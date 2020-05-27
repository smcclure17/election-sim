1.
Sean McClure
Date Tested: 5/6/2020

Summary:
Program to simulate a mail-in presidential election in the United States.
*Creates 51 "state" objects, each with a specified number of registered voters,
  electoral votes, and "political party percentage", which estimates how blue/red
  a each state is.
*The simulation outputs:
    *the number of elecotral votes each party earned
    *the popular vote
    *the winner of the Election
    *the duration in days that the election spanned
    *the total cost of the election in USD.
*The execution time of the simulation is also returned.

Comments:
Updates/changes to be made:
	*update initialization step to allow data read from csv, instead of manual entering of data.
	*update Base and Subclass constructors -- create parameterized subclass constructor to allow headquarter initialazation to be done in main

System Specs:
	Windows 10 Professional
	Processor: Intel(R) Core(TM) i5-7300HQ CPU @ 2.50GHz, 2501 Mhz, 4 Core(s), 4 Logical Processor(s)
	Installed Physical Memory (RAM)	8.00 GB
	Total Virtual Memory	17.0 GB
	Available Virtual Memory	6.77 GB
	Page File Space	9.14 GB

2. 
To run program on windows enviornment as tested in the report:
	election.cpp and class.cpp must be in same directory.
	required software/installations:
		*gcc/g++ compiler
		*mingw32
	compiling:
		*compile with g++ on windows cmd:
			*for sequential: > g++ election.cpp -O3
			*for parallel: 	 > g++ election.cpp -O3 -fopenmp
	execution:
		*in windows cmd: > election.exe
	



