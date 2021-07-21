#ifndef __CAT_H
#define __CAT_H

#include <map>
#include <iostream>
#include <vector>
#include "animal.h"

enum class Cat_breed{bengal_cat, ragdoll, persian_cat, russian_blue, bobtail, himalayan_cat, pixie_bob, nebelung};

constexpr Cat_breed cat_breeds[] = {
    Cat_breed::bengal_cat,
    Cat_breed::ragdoll,
    Cat_breed::persian_cat,
    Cat_breed::russian_blue,
    Cat_breed::bobtail,
    Cat_breed::himalayan_cat,
    Cat_breed::pixie_bob, 
    Cat_breed::nebelung,
};

std::string to_string(const Cat_breed& breed);
std::ostream& operator<<(std::ostream& ost, const Cat_breed& breed);

class Cat: public Animal{
  public:
  	Cat(Cat_breed breed, std::string name, Gender gender, int age);
    Cat(std::istream& ist);
  	virtual ~Cat();
  	virtual std::string family() const override;
  	virtual std::string breed() const override;
    void save(std::ostream& ost)override;
  private:
  	Cat_breed _breed;
};

#endif