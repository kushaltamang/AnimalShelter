#ifndef __CLIENT_H
#define __CLIENT_H

#include "animal.h"
#include <vector>
#include <iostream>

class Client{
  public:
  	Client(std::string name, std::string phone, std::string email);
    Client(std::istream& ist);
  	std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& ost, const Client& client);
  	void adopt(Animal& animal);
  	int num_adopted();
  	Animal& animal(int index) const;
    std::string name();
    void save(std::ostream& ost);
  private:
  	std::string _name;
  	std::string _phone;
  	std::string _email;
    std::vector <Animal*> adopted;
};

#endif