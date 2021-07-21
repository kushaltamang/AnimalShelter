#include "rabbit.h"

std::map<Rabbit_breed, std::string> breedsofrabbit = {
	{Rabbit_breed::lionhead, "Lionhead"},
	{Rabbit_breed::flemish_giant, "Flemish Giant"},
	{Rabbit_breed::holland_lop, "Holland Lop"},
	{Rabbit_breed::continental_giant, "Continental Giant"},
	{Rabbit_breed::netherland_dwarf, "Netherland Dwarf"},
	{Rabbit_breed::dutch_rabbit, "Dutch Rabbit"},
	{Rabbit_breed::english_lop, "English Lop"},
	{Rabbit_breed::french_lop, "French Lop"}
};

Rabbit::Rabbit(Rabbit_breed breed, std::string name, Gender gender, int age) 
: Animal(name, gender, age), _breed{breed} { }

Rabbit::Rabbit(std::istream& ist) : Animal(ist)
{
	std::string s;
    getline(ist, s);
    for(auto& [breed, breed_name] : breedsofrabbit) 
        if(s == ::to_string(breed)) {_breed = breed; break;}
}

void Rabbit::save(std::ostream& ost)
{
	ost << "Rabbit\n";
    Animal::save(ost);
    ost << breed() << '\n';
}


Rabbit::~Rabbit() {}

std::string Rabbit::family() const 
{
	return "rabbit";
}

std::string Rabbit::breed() const
{
 	return ::to_string(_breed);
}

std::string to_string(const Rabbit_breed& breed)
{
	return breedsofrabbit[breed]; 
}

std::ostream& operator<<(std::ostream& ost, const Rabbit_breed& breed) 
{
    ost << ::to_string(breed);
    return ost;
}