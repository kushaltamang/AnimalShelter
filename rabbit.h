#ifndef __RABBIT_H
#define __RABBIT_H

#include <map>
#include <iostream>
#include <vector>
#include "animal.h"

enum class Rabbit_breed{
	lionhead,
	flemish_giant,
	holland_lop,
	continental_giant,
	netherland_dwarf,
	dutch_rabbit,
	english_lop,
	french_lop
};

constexpr Rabbit_breed rabbit_breeds[] = {
    Rabbit_breed::lionhead,
	Rabbit_breed::flemish_giant,
	Rabbit_breed::holland_lop,
	Rabbit_breed::continental_giant,
	Rabbit_breed::netherland_dwarf,
	Rabbit_breed::dutch_rabbit,
	Rabbit_breed::english_lop,
	Rabbit_breed::french_lop
};

std::string to_string(const Rabbit_breed& breed);
std::ostream& operator<<(std::ostream& ost, const Rabbit_breed& breed);

class Rabbit: public Animal{	
  public:
  	Rabbit(Rabbit_breed breed, std::string name, Gender gender, int age);
  	Rabbit(std::istream& ist);
  	virtual ~Rabbit();
  	virtual std::string family() const override;
  	virtual std::string breed() const override;
  	void save(std::ostream& ost) override;
  private:
  	Rabbit_breed _breed;

};

#endif