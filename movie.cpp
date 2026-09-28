#include <string>
#include "util.h"
#include "movie.h"

Movie::Movie(
             const std::string name,
             double price,
             int qty,
             const std::string genre,
             const std::string rating)
    : Product("movie", name, price, qty)
{
    this->genre = genre;
    this->rating = rating;
}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> words;

    words = parseStringToWords(this->name_);

    std::set<std::string> genreWords = parseStringToWords(this->genre);
    words.insert(genreWords.begin(), genreWords.end());

    words.insert(this->rating);

    return words;
}

std::string Movie::displayString() const
{
    std::string output;

    output += this->name_ + "\n";
    output += this->genre + " " + this->rating + "\n";
    output += std::to_string(this->price_) + " " +
              std::to_string(this->qty_) + " left.\n";

    return output;
}

void Movie::dump(std::ostream& os) const
{
    os << "movie" << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << genre << std::endl;
    os << rating << std::endl;
    os << category_ << std::endl;
}