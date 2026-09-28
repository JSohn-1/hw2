#include <string>
#include "util.h"

#include "book.h"


Book::Book(const std::string name, double price, int qty, const std::string isbn, const std::string author) : Product("book", name, price, qty) {
    this->isbn = isbn;
    this->author = author;
};

std::set<std::string> Book::keywords() const
{
    std::set<std::string> words;

    words = parseStringToWords(this->name_);

    std::set<std::string> authorWords = parseStringToWords(this->author);
    words.insert(authorWords.begin(), authorWords.end());

    words.insert(this->isbn);

    return words;
}

std::string Book::displayString() const
{
    std::string output;

    output += this->name_ + "\n";
    output += "Author: " + this->author + " ISBN: " + this->isbn + "\n";
    output += std::to_string(this->price_) + " " +
              std::to_string(this->qty_) + " left.\n";

    return output;
}

void Book::dump(std::ostream& os) const
{
    os << "book" << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << isbn << std::endl;
    os << author << std::endl;
    os << category_ << std::endl;
}
