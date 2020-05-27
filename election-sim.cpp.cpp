/*
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
*/
#include <iostream>
#include <omp.h>
#include "class.cpp"
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include<chrono>
using namespace std::chrono;
using namespace std;


int main()
{

  /////// INITIALIZATION ////////////////////////////////////////////
  vector<State> states; //holds each state object
  float turnout = 0.9; //60% of registered voters vote
  //num of registered voters in each state
  int registered[] = {2526000,358000,3145000,1456000,16096000,2893000,1763000,487000,420000,9604000,4892000,530000,790000,6665000,3298000,1657000,1438000,2253000,2446000,830000,3114000,3660000,5434000,3055000,1725000,3333000,581000,1008000,1371000,763000,4165000,916000,9142000,5194000,424000,6128000,1861000,2147000,6909000,538000,2575000,437000,3251000,11724000,1398000,351000,4399000,3906000,913000,3323000,304000};
  //names of states
  string state_names[] = {"Alabama","Alaska","Arizona","Arkansas","California","Colorado","Connecticut","Deleware","Washington DC","Florida","Georgia","Hawaii","Idaho","Illinois","Indiana","Iowa","Kansas","Kentucky","Louisiana","Maine","Maryland","Massachusetts","Michigan","Minnesota","Mississippi","Missouri","Montana","Nebraska","Nevada","New Hampshire","New Jersey","New Mexico","New York","North Carolina","North Dakota","Ohio","Oklahoma","Oregon","Pennsylvania","Rhode Island","South Carolina","Sout Dakota","Tennessee","Texas","Utah","Vermont","Virginia","Washington","West Virginia","Wisconsin","Wyoming"};
  //postage zone of each state
  int zones[] = {4,7,6,4,6,5,2,1,1,4,4,7,6,3,3,3,5,1,4,2,1,2,3,3,4,3,6,5,6,2,2,5,2,1,5,3,5,6,1,2,1,5,1,5,6,2,1,6,1,3,6};
  //electoral votes for each state
  int electoral_votes[] = {9,3,11,6,55,9,7,3,3,29,16,4,4,20,11,6,6,8,8,4,10,11,16,6,10,10,3,5,6,4,14,5,29,15,3,18,7,7,20,4,9,3,11,38,6,3,13,12,5,10,3};
  //political party percentage:
  //  *probability of each indiviudal in respective state to vote for Blue Candidate.
  //  *data taken from results of 2016 general election
  double state_party[] = {0.3836,0.3655,0.4513,0.3365,0.6573,0.4816,0.5457,0.5309,0.9,0.4782,0.4564,0.6222,0.2749,0.5583,0.3791,0.4174,0.3605,0.3268,0.3845,0.4783,0.6033,0.6001,0.4727,0.4644,0.4011,0.3814,0.3575,0.337,0.4792,0.4698,0.5499,0.4826,0.5901,0.4617,0.2723,0.4356,0.2893,0.5007,0.4746,0.5441,0.4067,0.3174,0.3472,0.4324,0.2746,0.5668,0.4973,0.5254,0.2643,0.4645,0.2163};

  //start timing
  auto start = high_resolution_clock::now();

  //init each state with proper info
  Headquarters hq; //make ALABAMA the central location center
  for(int i = 1; i < 51; i++)
  {
    //replace state_party[i] with 0.5 for coinflip method
    states.push_back(State(state_names[i],registered[i],electoral_votes[i],zones[i],state_party[i],turnout));
  }

  //////////// SIMULATE ELECTION ///////////////////////////////////
  int * hold_vals;
  #pragma omp parallel for num_threads( 8 )
  for(int i = 0; i < 50; i++){
    hold_vals = states[i].send_delegates();
    hq.update_cost(states[i].get_zone(), states[i].get_voters());
    hq.update_votes(hold_vals[0], hold_vals[1], hold_vals[2], hold_vals[3]);
    hq.update_time(states[i].get_zone());
  }

  //make sure to include shipping state
  hold_vals = hq.send_delegates();
  hq.update_votes(hold_vals[0], hold_vals[1],hold_vals[2], hold_vals[3]);
  hq.update_cost(hq.get_zone(),hq.get_voters());
  hq.update_time(hq.get_zone());

  //stop timing
  auto stop = high_resolution_clock::now();

  /////////////OUTPUT///////////////////////////////////////////////
  cout << "Results:\n";
  hq.get_delegates();
  hq.get_popular_vote();
  cout << "\nAdditional Data:\n";
  hq.get_cost();
  cout << "Total election duration: " << hq.final_time() << " days" << endl;

  //report time
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "\nExecution time: " << duration.count() << " microseconds" << endl << endl;


  ////////////////////////////// TESTING /////////////////////

  //testing objects
cout << hq.get_name() << "," << hq.get_local_vote() << "%" << "," << 100 - hq.get_local_vote() << "%" << endl;
  cout << "state name" << "," << "% blue vote" << "," << "% red vote" << endl;
  for(int i = 0; i < 50; i++)//finish this
  {
     //cout << states[i].get_name() << "," << states[i].get_voters() << "," << states[i].get_delegates() << "," << states[i].get_zone() << endl;
    cout << states[i].get_name() << "," << states[i].get_local_vote() << "%" << "," << 100 - states[i].get_local_vote() << "%" << endl;

  }


return 0;
}
