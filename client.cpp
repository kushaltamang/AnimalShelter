#include "client.h"

Client::Client(std::string name, std::string phone, std::string email)
 	: _name{name}, _phone{phone}, _email{email} { }

Client::Client(std::istream& ist)
{
	std::getline(ist, _name);
    std::getline(ist, _phone);
    std::getline(ist, _email);
    int animals;
    ist >> animals; ist.ignore(65535, '\n');
    while(animals--) adopted.push_back(Animal::make_animal(ist)); 
}

void Client::save(std::ostream& ost)
{
	ost << _name << '\n' << _phone << '\n' << _email << '\n';
    ost << adopted.size() << '\n';
    for (Animal* a : adopted) a->save(ost);
}

std::string Client::to_string() const
{
	return "("+ _name + ", " + " Phone: " + _phone + ", " + " Email: " + _email+")";
}

std::ostream& operator<<(std::ostream& ost,const Client& client)
{
	ost << client.to_string();
    return ost;
}

 void Client::adopt(Animal& animal)
 {
 	adopted.push_back(&animal);
 }

 int Client::num_adopted()
 {
 	return adopted.size();
 }

Animal& Client::animal(int index) const
 {
 	return *(adopted[index]);
 }

 std::string Client::name()
 {
 	return _name;
 }
 