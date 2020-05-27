#include <string>
#include<time.h>
#include<omp.h>
using namespace std;

////////////////////////////////////////////////////STATE BASE CLASS///////////////////////////////////////////
class State {
public:
  float turnout_rate;

  //CNSTRCTRs

  //THIS IS BAD PRACTICE - will be updated 
  State(){
    name = "Alabama";
    voters = 2526000;
    delegates = 9;
    zone = 4;
    pol_party = 0.3836;
    ballot = 0;
    turnout_rate = .9;
    blue_local_votes = 0;
    red_local_votes = 0;
  }

  State(string name1, int voters1, int delegates1, int zone1, float pol1, float turnout1){
    name = name1;
    voters = voters1;
    delegates = delegates1;
    zone = zone1;
    pol_party = pol1;
    ballot = 0;
    turnout_rate = turnout1;
    blue_local_votes = 0;
    red_local_votes = 0;
  }

  //getters
  int get_voters(){
    return this->voters;
  }

  string get_name(){
    return this->name;
  }

  int get_delegates(){
    return this->delegates;
  }

  int get_zone(){
    return this->zone;
  }

  float get_local_vote(){
    return 100 * (static_cast< float >(blue_local_votes / static_cast< float >(red_local_votes+blue_local_votes)));
  }

  //setters
  void set_voters(int x){
    this->voters = x;
  }

  void set_name(string x){
    name = x;
  }

  //send delegates
  //return array sizeof 4
  //return_vals[2] = BLUE VOTES
  //"..."      [3]  = RED VOTES
  int * send_delegates(){
    static int return_vals[4];
    return_vals[0] = this->vote_count(); //bool
    return_vals[1] = this->delegates;
    return_vals[2] = this->blue_local_votes;
    return_vals[3] = this->red_local_votes;
    return return_vals;
  }

protected:
  string name;
  int voters;
  int delegates;
  int zone;
  double pol_party; //percentage, eg .57 = 57% blue_electoral_votes
  bool ballot;
  int blue_local_votes;
  int red_local_votes;

  //counting
  // true = red majority
  //false = blue majority
  bool vote_count(){
    srand((unsigned)time(NULL));
    for(int i = 0; i < voters*turnout_rate; i++){
      if(((double)rand()/(double)RAND_MAX) < this->pol_party)
        this->blue_local_votes++;
      else
        this->red_local_votes++;
    }

    if(red_local_votes > blue_local_votes)
      return true;
    else
      return false;
  }

};

////////////////////////////////////////////////////Headquarters Subclass///////////////////////////////////////////
class Headquarters : public State {
protected:
    int red_electoral_votes; //total red electoral votes
    int blue_electoral_votes; //total blue electoral votes
    int blue_total_votes; //blue total popular vote
    int red_total_votes; //red total popular vote
    long long cost;
    int max_travel_time;

  public:
    Headquarters(){
      red_electoral_votes = 0;
      blue_electoral_votes = 0;
      cost = 0;
      max_travel_time = 0;
      blue_total_votes = 0;
      red_total_votes = 0;
    }

    //getters
    void get_delegates(){
      cout << "Red Electoral Votes: " << red_electoral_votes << endl;
      cout << "Blue Electoral Votes: " << blue_electoral_votes << endl;

      if(red_electoral_votes>blue_electoral_votes)
        cout <<"Red Candidate";
      else
        cout <<"Blue Candidate";

      cout <<" Wins the election" << endl;;
    }

    void get_cost(){
      cout << "Cost of Election:  " << "$" << cost <<endl;
    }

    void get_popular_vote(){
      float vote_percentage;
      if(blue_total_votes > red_total_votes){
        vote_percentage = 100 * (static_cast< float >(blue_total_votes / static_cast< float >(red_total_votes+blue_total_votes)));
        cout << "Blue won the majority of the popular vote with " << vote_percentage << "%" << endl;
      }
      else if (red_total_votes > blue_total_votes){
        vote_percentage = 100 * (static_cast< float >(red_total_votes / static_cast< float >(red_total_votes+blue_total_votes)));
        cout << "Red won the majority of the popular vote with " << vote_percentage << "%" << endl;
      }
      else
        cout << "we gotta problem with the pop vote" << endl;
    }

    //PUBLIC METHODS

    void update_votes(bool party, int local_elec_votes, int blue_votes, int red_votes){
      if (!party)
        this->blue_electoral_votes = this->blue_electoral_votes + local_elec_votes;
      else if (party)
        this->red_electoral_votes = this->red_electoral_votes + local_elec_votes;
      else
        cout << "error updating votes";

      //update popular vote
      this->blue_total_votes += blue_votes;
      this->red_total_votes += red_votes;
    }

    void update_cost(int recipient_zone, int recipient_voters){
      int zone_diff = abs(this->zone - recipient_zone);
      //send from center to each indiviudal in the state
      if(zone_diff == 0)
         cost+= (5*recipient_voters);
      else if(zone_diff == 1)
        cost+= (7 * recipient_voters);
      else if(zone_diff == 2)
        cost+= (10 * recipient_voters);
      else if(zone_diff == 3)
        cost += (12 * recipient_voters);
      else if(zone_diff == 4)
        cost += (15 * recipient_voters);
      else if(zone_diff == 5)
        cost += (20 * recipient_voters);
      else if(zone_diff >= 6)
        cost += (40 * recipient_voters);

      //send each filled out ballot to state gov by intrazone mail
      cost += (5*recipient_voters);
      //cout << "cost = " << cost << endl;
      //rest is done by email meaning no cost
    }

    void update_time(int recipient_zone){
      int zone_diff = abs(recipient_zone - this->zone);
      int local_time;

      if(zone_diff == 0)
         local_time = 3;
      else if(zone_diff == 1)
        local_time  = 4;
      else if(zone_diff == 2)
        local_time = 5;
      else if(zone_diff == 3)
        local_time  = 7;
      else if(zone_diff == 4)
        local_time  = 8;
      else if(zone_diff == 5)
        local_time  = 9;
      else if(zone_diff >= 6)
        local_time  = 10;

      if (local_time > max_travel_time){
        max_travel_time = local_time;
         // cout << "max travel time = " << this->zone << "-" << recipient_zone << " = " << max_travel_time <<endl;
      }
    }

    int final_time(){
      return max_travel_time + 3; //plus 3 for intrazone sending
    }

};
