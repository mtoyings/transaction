#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//
//classname
Transaction::Transaction(std::string ticker_symbol, unsigned int day_date, unsigned int month_date, unsigned int year_date, bool buy_sell_trans, unsigned int number_shares, double trans_amount)
{

  //the purpose of the parameter is
  acb = 0;
  acb_per_share = 0;
  share_balance = 0;
  cgl = 0;
  p_next = nullptr;
  this->symbol = ticker_symbol;
  this->day = day_date;
  this->month = month_date;
  this->year = year_date;
  if (buy_sell_trans == true)
  {
    this->trans_type = "Buy";
  }
  else
  {
    this->trans_type = "Sell";
  }
  this->shares = number_shares;
  this->amount = trans_amount;
  this->trans_id = assigned_trans_id;
  assigned_trans_id++;
}

// Destructor
// TASK 1
//

Transaction::~Transaction()
{
  //no memory to delete
}

// Overloaded < operator. 4.4
// TASK 2
//

bool Transaction::operator<(Transaction const &other)
{
  if (this->year < other.get_year())
  {
    return true;
  }
  if (this->year == other.get_year() && this->month < other.get_month())
  {
    return true;
  }
  if (this->year == other.get_year() && this->month == other.get_month() && this->day < other.get_day())
  {
    return true;
  }
  return false;

  //return false;
  // }
  // if(this -> year < other.get_year() && this->month < other.get_month() && this->day < other.get_day()){
  //   return true;
  // } else {
  //   return false;
  // }
}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true : false; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb(double acb_value) { acb = acb_value; }
void Transaction::set_acb_per_share(double acb_share_value) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance(unsigned int bal) { share_balance = bal; }
void Transaction::set_cgl(double value) { cgl = value; }
void Transaction::set_next(Transaction *p_new_next) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print()
{
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
            << std::setw(4) << get_symbol() << " "
            << std::setw(4) << get_day() << " "
            << std::setw(4) << get_month() << " "
            << std::setw(4) << get_year() << " ";

  if (get_trans_type())
  {
    std::cout << "  Buy  ";
  }
  else
  {
    std::cout << "  Sell ";
  }

  std::cout << std::setw(4) << get_shares() << " "
            << std::setw(10) << get_amount() << " "
            << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
            << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
            << std::setw(10) << std::setprecision(3) << get_cgl()
            << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 3
//

History::History() //submission 2
{
  this->p_head = nullptr;
}

// Destructor
// TASK 3
//

History::~History() //submission 2
{
  while (p_head != nullptr)
  {
    Transaction *p_jimmy{p_head};
    p_head = p_head->get_next();
    delete p_jimmy;
  }
  p_head = nullptr;
  //delete this;
}

// read_history(...): Read the transaction history from file.
// TASK 4
//

void History::read_history() //submission 2
{
  ece150::open_file();

  //int count{};

  while (ece150::next_trans_entry())
  {
    // Transaction( std::string ticker_symbol,  unsigned int day_date,
    //     unsigned int month_date,  unsigned year_date,
    //     bool buy_sell_trans,  unsigned int number_shares,
    //     double trans_amount );

    Transaction *t1 = new Transaction(ece150::get_trans_symbol(), ece150::get_trans_day(), ece150::get_trans_month(), ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), ece150::get_trans_amount());
    // std::cout << "day:" << t1->get_day();
    //std::cout << "day" << ece150::get_trans_day();
    //++count;
    insert(t1);
  }
  //std::cout << "count " << count << std::endl;

  ece150::close_file();
}

// insert(...): Insert transaction into linked list.
// TASK 5
//

void History::insert(Transaction *p_new_trans) //submission 2
{
  //Nov17 lab 11
  //
  //std::cout << "INSERT \n";
  if (p_head == nullptr)
  {
    this->p_head = p_new_trans; //change where p_head is pointing
  }
  else
  {

    Transaction *p_traverse{p_head};
    while (p_traverse->get_next() != nullptr)
    {
      // move through transaction until we get to the last transaction
      p_traverse = p_traverse->get_next();
    }

    //insert new transaction at the end of linked list

    p_traverse->set_next(p_new_trans);

    //
  }
  //std::cout << "INSERT END \n";
}

// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//

void History::sort_by_date() //FINAL SUBMISSION
{

  Transaction *p_sorted{nullptr}; //record sorted linked list
  Transaction *p_temp{nullptr};   //store a value temporary for sorting

  while (p_head != nullptr)
  {

    p_temp = p_head;             //store the first one
    p_head = p_head->get_next(); //remove the first one
    p_temp->set_next(nullptr);   //set the next one to null ptr

    //INSERTION
    //case 1: beginning case

    if (p_sorted == nullptr)
    {
      p_sorted = p_temp;
      p_temp = nullptr;
      //std::cout << "JIMMY" << std::endl;
    }
    else if (*p_temp < *p_sorted)
    { //
      p_temp->set_next(p_sorted);
      p_sorted = p_temp;
      p_temp = nullptr;
      //std::cout << "WORKED" << std::endl;
    }
    else
    {
      Transaction *p_runthrough{p_sorted};
      //std::cout << "WORK" << std::endl;

      while ((p_runthrough->get_next() != nullptr) && (*(p_runthrough->get_next()) < *p_temp))
      {
        p_runthrough = p_runthrough->get_next();
        //std::cout << p_runthrough << std::endl;
      }
      //std::cout << "yea" << std::endl;
      //Inserting
      p_temp->set_next(p_runthrough->get_next());
      p_runthrough->set_next(p_temp);
      p_temp = nullptr;
      p_runthrough = nullptr;
    }
  }
  p_head = p_sorted;
}

// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//

void History::update_acb_cgl() //FINAL SUBMISSION
{
  double acb{};
  double acb_per_share{};
  unsigned int share_balance{};
  double cgl{};

  Transaction *p_runthrough{p_head};
  while (p_runthrough != nullptr)
  {
    // if (p_runthrough->get_next() != nullptr)
    // {
    if (p_runthrough->get_trans_type() == true)
    {                                              //Buy
      acb += p_runthrough->get_amount();           //total amount paid for the purchases
      share_balance += p_runthrough->get_shares(); //add share balance from teh previous trans with new trans
      acb_per_share = acb / share_balance;
      // std::cout << "BUY \n";
      // std::cout << "ACB = " << acb << std::endl;
      // std::cout << "Share Balance = " << share_balance << std::endl;
      // std::cout << "acb_per_share = " << acb_per_share << std::endl;
      // std::cout << "cgl = "
      //           << "0.000" << std::endl;
      p_runthrough->set_acb(acb);
      p_runthrough->set_acb_per_share(acb_per_share);
      p_runthrough->set_share_balance(share_balance);
      p_runthrough->set_cgl(0);
    }
    else if (p_runthrough->get_trans_type() == false)
    { //Sell
      acb = acb - ((p_runthrough->get_shares()) * acb_per_share);
      share_balance = share_balance - p_runthrough->get_shares();
      cgl = p_runthrough->get_amount() - ((p_runthrough->get_shares()) * acb_per_share);
      p_runthrough->set_acb(acb);
      p_runthrough->set_acb_per_share(acb_per_share);
      p_runthrough->set_share_balance(share_balance);
      p_runthrough->set_cgl(cgl);
      //   std::cout << "SELL \n";
      //   std::cout << "ACB = " << acb << std::endl;
      //   std::cout << "Share Balance = " << share_balance << std::endl;
      //   std::cout << "acb_per_share = " << acb_per_share << std::endl;
      //   std::cout << "cgl = " << cgl << std::endl;
      // }
    }
    // }
    p_runthrough = p_runthrough->get_next();
  }
}

// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8

double History::compute_cgl(unsigned int year) //FINAL SUBMISSION
{
  double cgl{};
  Transaction *p_runthrough{p_head};
  while (p_runthrough != nullptr)
  {

    if (p_runthrough->get_year() == year)
    {
      cgl += p_runthrough->get_cgl();
    }
    p_runthrough = p_runthrough->get_next();
  }

  return cgl;
}

// print() Print the transaction history.
//TASK 9
//

void History::print() //submission 2
{
  if (p_head != nullptr)
  {
    std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;
    Transaction *p_traverse{p_head};
    while (p_traverse != nullptr)
    {
      //std::cout << "p_traverse" << p_traverse << std::endl;
      //std::cout << "p_traverse next" << p_traverse->get_next() << std::endl;
      p_traverse->print();
      // move through transaction until we get to the last transaction
      p_traverse = p_traverse->get_next();
    }
    std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;
  }
  else
  {
    std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;
    std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;
  }
}

// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
