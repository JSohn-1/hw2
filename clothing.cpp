#include <string>
#include "util.h"
#include "clothing.h"

Clothing::Clothing(
                   const std::string name,
                   double price,
                   int qty,
                   const std::string size,
                   const std::string brand)
    : Product("clothing", name, price, qty)
{
    this->size = size;
    this->brand = brand;
}

std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> words;

    words = parseStringToWords(this->name_);

    std::set<std::string> brandWords = parseStringToWords(this->brand);
    words.insert(brandWords.begin(), brandWords.end());

    words.insert(this->size);

    return words;
}

std::string Clothing::displayString() const
{
    std::string output;

    output += this->name_ + "\n";
    output += this->size + " " + this->brand + "\n";
    output += std::to_string(this->price_) + " " +
              std::to_string(this->qty_) + " left.\n";

    return output;
}

void Clothing::dump(std::ostream& os) const
{
    os << "clothing" << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << size << std::endl;
    os << brand << std::endl;
    os << category_ << std::endl;
}