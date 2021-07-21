#include "cat.h"

std::map<Cat_breed, std::string> breedsofcat = {
	{Cat_breed::bengal_cat, "Bengal cat"},
	{Cat_breed::ragdoll, "Ragdoll"},
	{Cat_breed::persian_cat, "Persian Cat"},
	{Cat_breed::russian_blue, "Russian Blue"},
	{Cat_breed::bobtail, "Bobtail"},
	{Cat_breed::himalayan_cat, "Himalayan Cat"},
	{Cat_breed::pixie_bob, "Pixie Bob"},
	{Cat_breed::nebelung, "Nebelung"}
};

Cat::Cat(Cat_breed breed, std::string name, Gender gender, int age) 
: Animal(name, gender, age), _breed{breed} { }

Cat::Cat(std::istream& ist) : Animal(ist) 
{
	std::string s;
    getline(ist, s);
    for(auto& [_breed, breed_name] : breedsofcat)
        if(s == breed_name) break;
}

void Cat::save(std::ostream& ost){
	ost << "Cat\n";
    Animal::save(ost);
    ost << breed() << '\n';
}

Cat::~Cat() {}

std::string Cat::family() const 
{
	return "cat";
}

std::string Cat::breed() const
{
 	return ::to_string(_breed);
}

std::string to_string(const Cat_breed& breed)
{
	return breedsofcat[breed]; 
}

std::ostream& operator<<(std::ostream& ost, const Cat_breed& breed) 
{
    ost << ::to_string(breed);
    return ost;
}