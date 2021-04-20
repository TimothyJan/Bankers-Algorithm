//
//  bankexample.h
//  bankers
//
//  Created by William McCarthy on 1011//20.
//

#ifndef bankexample_h
#define bankexample_h

#include "customer.h"


class BankExample {
public:
  BankExample() = default;
  BankExample(const ext_vector<int>& available) : avail(available), customers() { }
  
  ext_vector<int> get_avail() const { return avail; }
  bool is_avail(const ext_vector<int>& req) const { return req < avail; }
  
  bool is_safe(int id, const ext_vector<int>& req) { return true; }
  bool req_approved(int id, const ext_vector<int>& req) { return true; }
  
  void add_customer(CustomerExample* c) { customers.push_back(c); }
  
  void withdraw_resources(const ext_vector<int>& req) {
    if (!is_avail(req)) {
      pthread_mutex_lock(&mutex_);
      std::cerr << "WARNING: req: " << req << " is not available for withdrawing\n";
      pthread_mutex_unlock(&mutex_);
      return;
    }
    if (is_avail(req)) { avail -= req; }
  }
  void deposit_resources(const ext_vector<int>& req) { avail += req; }


  ext_vector<CustomerExample*> get_customers() const { return customers; }
  
  void show() const {
    pthread_mutex_lock(&mutex_);
    std::cout << "avail: [" << avail << "]\n";
    pthread_mutex_unlock(&mutex_);
    
    for (CustomerExample* c : customers) {
      c->show();
    }
    std::cout << "\n";
  }
  
  friend std::ostream& operator<<(std::ostream& os, const BankExample& be) {
    be.show();
    return os;
  }

private:
  ext_vector<int> avail;
  ext_vector<CustomerExample*> customers;
};

#endif /* bankexample_h */
