#include "mydatastore.h"

#include "util.h"

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
  for (std::set<Product*>::iterator it = products_.begin();
       it != products_.end(); ++it) {
    delete *it;
  }

  for (std::set<User*>::iterator it = users_.begin(); it != users_.end();
       ++it) {
    delete *it;
  }
}

void MyDataStore::addProduct(Product* p) {
  products_.insert(p);

  std::set<std::string> keywords = p->keywords();

  for (std::set<std::string>::iterator it = keywords.begin();
       it != keywords.end(); ++it) {
    productKeywords_[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u) { users_.insert(u); }

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms,
                                          int type) {
  std::vector<Product*> results;

  if (terms.empty()) {
    return results;
  }

  std::set<Product*> resultSet;

  if (type == 0) {
    resultSet = productKeywords_[terms[0]];

    for (size_t i = 1; i < terms.size(); ++i) {
      resultSet = setIntersection(resultSet, productKeywords_[terms[i]]);
    }
  } else if (type == 1) {
    resultSet = productKeywords_[terms[0]];

    for (size_t i = 1; i < terms.size(); ++i) {
      resultSet = setUnion(resultSet, productKeywords_[terms[i]]);
    }
  }

  for (std::set<Product*>::iterator it = resultSet.begin();
       it != resultSet.end(); ++it) {
    results.push_back(*it);
  }

  return results;
}

void MyDataStore::dump(std::ostream& ofile) {
  ofile << "<products>" << std::endl;

  for (std::set<Product*>::iterator it = products_.begin();
       it != products_.end(); ++it) {
    (*it)->dump(ofile);
  }

  ofile << "</products>" << std::endl;

  ofile << "<users>" << std::endl;

  for (std::set<User*>::iterator it = users_.begin(); it != users_.end();
       ++it) {
    (*it)->dump(ofile);
  }

  ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(std::string username, Product* p) {
  carts_[username].push_back(p);
}

void MyDataStore::viewCart(std::string username) {
  if (carts_.find(username) == carts_.end()) {
    return;
  }

  std::vector<Product*>& cart = carts_[username];

  for (size_t i = 0; i < cart.size(); ++i) {
    std::cout << "Item " << i + 1 << std::endl;
    std::cout << cart[i]->displayString() << std::endl;
  }
}

void MyDataStore::buyCart(std::string username)
{
    User* user = NULL;

    for (std::set<User*>::iterator it = users_.begin();
         it != users_.end();
         ++it) {

        if ((*it)->getName() == username) {
            user = *it;
            break;
        }
    }

    if (user == NULL) {
        return;
    }

    if (carts_.find(username) == carts_.end()) {
        return;
    }

    std::vector<Product*>& cart = carts_[username];
    std::vector<Product*> remaining;

    for (size_t i = 0; i < cart.size(); ++i) {
        Product* p = cart[i];

        if (p->getQty() > 0 &&
            user->getBalance() >= p->getPrice()) {

            user->deductAmount(p->getPrice());
            p->subtractQty(1);
        }
        else {
            remaining.push_back(p);
        }
    }

    cart = remaining;
}