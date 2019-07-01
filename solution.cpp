#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST_ */



class CThing {
  public:
    CThing(const int weight) : weight(weight) {}
    
    virtual ~CThing(){}

    virtual ostream& print(ostream& os) const {
        return os << "Thing";
    }

    int Weight() const {
        return weight;
    }

    virtual bool operator== (const CThing& other) const {
        return weight == other.weight;
    }

  protected:
    int weight;
};



class CKnife : public CThing
{
  public:
    CKnife(int bladeLength) : CThing(100), blade(bladeLength) {}
    
    virtual ~CKnife(){}
    
    int Blade() const {
        return blade;
    }

    virtual ostream& print(ostream& os) const {
        return os << "Knife, blade: " << blade << " cm";
    }

    bool operator== (const CKnife& other) const {
        return blade == other.blade;
    }

  protected:
    int blade;
};



class CClothes : public CThing
{
  public:
    CClothes(string desc) : CThing(500), desc(desc) {}

    virtual ~CClothes(){}

    virtual ostream& print(ostream& os) const {
        return os << "Clothes (" << desc << ")";
    }

    bool operator== (const CClothes& other) const {
        return desc == other.desc;
    }

  protected:
    string desc;
};



class CShoes : public CThing
{
  public:
    CShoes() : CThing(750) {}

    virtual ~CShoes(){}

    virtual ostream& print(ostream& os) const {
        return os << "Shoes";
    }

    bool operator== (const CShoes& other) const {
        return true;
    }
};



class CMobile : public CThing
{
  public:
    CMobile(string manufacturer, string model) : CThing(150), manufacturer(manufacturer), model(model) {}
    
    virtual ~CMobile(){}

    string Type() const {
        return manufacturer+" "+model;
    }

    virtual ostream& print(ostream& os) const {
        return os << "Mobile " << model << " by: " << manufacturer;
    }

    bool operator== (const CMobile& other) const {
        return manufacturer == other.manufacturer && model == other.model;
    }

  protected:
    string manufacturer, model;
};



ostream& operator << (ostream& os, const CThing& thing) {
    return thing.print(os);
}



class CLuggage {
  public:
    CLuggage(int weight): weight(weight), danger(false) {}

    bool IdenticalContents(const CLuggage& other) const {
        if (this == &other) {
          return true;
        }
        if (this->content.size() != other.content.size()) {
          return false;
        }

        for (unsigned int i = 0; i < content.size(); ++i) {
            unsigned int j;
            for (j = 0; j < other.content.size(); ++j) {
                if (*(content[i]) == *(other.content[j])) {
                  break;
                }
            }
            if (j == other.content.size()) {
              return false;
            }
        }

        return true;
    }

    int   Weight() const {
        return weight;
    }

    int   Count() const {
        return content.size();
    }

    bool  Danger() const {
        return danger;
    }

    CLuggage& Add(const CThing& thing) {

        if (const CClothes* clothes = dynamic_cast<const CClothes*>(&thing)) {
            content.push_back(make_shared<CClothes>(CClothes(*clothes)));
        } else if (const CShoes* shoes = dynamic_cast<const CShoes*>(&thing)) {
            content.push_back(make_shared<CShoes>(CShoes(*shoes)));
        } else if (const CMobile* mobile = dynamic_cast<const CMobile*>(&thing)) {
            content.push_back(make_shared<CMobile>(CMobile(*mobile)));
            if (mobile->Type() == "Samsung Galaxy Note S7") {
              danger = true;
            }
        } else if (const CKnife* knife = dynamic_cast<const CKnife*>(&thing)) {
            content.push_back(make_shared<CKnife>(CKnife(*knife)));
            if (knife->Blade() > 7) {
              danger = true;
            }
        }

        weight += thing.Weight();
        return *this;
    }

    virtual ostream& print(ostream& os) const {
        os << "Luggage\n";
        for(unsigned int i = 0; i < content.size(); ++i)
            os << "+-" << *(content[i]) << "\n";
        return os;
    }

  protected:
    int weight;
    bool danger;
    vector<shared_ptr<CThing> > content;
};



class CSuitcase : public CLuggage
{
  public:
    CSuitcase(int w, int h, int d): CLuggage(2000), width(w), height(h), depth(d) {}

    virtual ostream& print(ostream& os) const {
        os << "Suitcase " << width << "x" << height << "x" << depth << "\n";
        
        for (unsigned int i = 0; i < content.size(); ++i) {
          if (i == content.size() - 1) {
            os << "\\-" << *(content[i]) << "\n";
          } else {
            os << "+-" << *(content[i]) << "\n";
          }
        }

        return os;
    }

  protected:
    int width, height, depth;
};



class CBackpack : public CLuggage
{
  public:
    CBackpack() : CLuggage(1000) {}

    virtual ostream& print(ostream& os) const {
        os << "Backpack\n";

        for (unsigned int i = 0; i < content.size(); ++i)
          if (i == content.size() - 1) {
            os << "\\-" << *(content[i]) << "\n";
          } else { 
            os << "+-" << *(content[i]) << "\n";
          }
        return os;
    }

};



ostream& operator << (ostream& os, const CLuggage& lug){
    return lug.print(os);
}



#ifndef __PROGTEST__
int main (void)
{
  CSuitcase x (1,2,3);
  CBackpack y;
  ostringstream os;

  x.Add(CKnife(7));
  x.Add(CClothes("red T-shirt"));
  x.Add(CClothes("black hat"));
  x.Add(CShoes());
  x.Add(CClothes("green pants") );
  x.Add(CClothes("blue jeans"));
  x.Add(CMobile("Samsung", "J3"));
  x.Add(CMobile("Tamtung", "Galaxy Note S7"));

  os.str("");
  os << x;
  assert(os.str() == "Suitcase 1x2x3\n"
                     "+-Knife, blade: 7 cm\n"
                     "+-Clothes (red T-shirt)\n"
                     "+-Clothes (black hat)\n"
                     "+-Shoes\n"
                     "+-Clothes (green pants)\n"
                     "+-Clothes (blue jeans)\n"
                     "+-Mobile J3 by: Samsung\n"
                     "\\-Mobile Galaxy Note S7 by: Tamtung\n");

  assert( x.Count() == 8);
  assert( x.Weight() == 5150);
  assert(!x.Danger());
  x.Add(CKnife(8));
  
  os.str("");
  os << x;
  assert(os.str() ==  "Suitcase 1x2x3\n"
                      "+-Knife, blade: 7 cm\n"
                      "+-Clothes (red T-shirt)\n"
                      "+-Clothes (black hat)\n"
                      "+-Shoes\n"
                      "+-Clothes (green pants)\n"
                      "+-Clothes (blue jeans)\n"
                      "+-Mobile J3 by: Samsung\n"
                      "+-Mobile Galaxy Note S7 by: Tamtung\n"
                      "\\-Knife, blade: 8 cm\n" );
  assert (x.Count() == 9);
  assert (x.Weight() == 5250);
  assert (x.Danger());


  y.Add(CKnife(7))
   .Add(CClothes("red T-shirt"))
   .Add(CShoes());
  y.Add(CMobile("Samsung", "Galaxy Note S7"));
  y.Add(CShoes());
  y.Add(CClothes("blue jeans"));
  y.Add(CClothes("black hat"));
  y.Add(CClothes("green pants"));

  os.str ("");
  os << y;
  assert(os.str() == "Backpack\n"
           "+-Knife, blade: 7 cm\n"
           "+-Clothes (red T-shirt)\n"
           "+-Shoes\n"
           "+-Mobile Galaxy Note S7 by: Samsung\n"
           "+-Shoes\n"
           "+-Clothes (blue jeans)\n"
           "+-Clothes (black hat)\n"
           "\\-Clothes (green pants)\n");

  assert (y.Count() == 8);
  assert (y.Weight() == 4750);
  assert (y.Danger());

  y.Add(CMobile("Samsung", "J3"));
  y.Add(CMobile("Tamtung", "Galaxy Note S7"));
  y.Add(CKnife(8));
  
  os.str("");
  os << y;
  assert(os.str() ==  "Backpack\n"
                      "+-Knife, blade: 7 cm\n"
                      "+-Clothes (red T-shirt)\n"
                      "+-Shoes\n"
                      "+-Mobile Galaxy Note S7 by: Samsung\n"
                      "+-Shoes\n"
                      "+-Clothes (blue jeans)\n"
                      "+-Clothes (black hat)\n"
                      "+-Clothes (green pants)\n"
                      "+-Mobile J3 by: Samsung\n"
                      "+-Mobile Galaxy Note S7 by: Tamtung\n"
                      "\\-Knife, blade: 8 cm\n");

  assert (y.Count() == 11);
  assert (y.Weight() == 5150);
  assert (y.Danger());


  assert (!x.IdenticalContents(y));
  assert (!y.IdenticalContents(x));
  x.Add(CMobile("Samsung", "Galaxy Note S7"));
  assert (!x.IdenticalContents(y));
  assert (!y.IdenticalContents(x));
  x.Add(CShoes());
  assert (x.IdenticalContents(y));
  assert (y.IdenticalContents(x));
  assert (y.IdenticalContents(y));
  assert (x.IdenticalContents(x));

  return 0;
}
#endif /* __PROGTEST__ */
