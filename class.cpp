#include <string>

class baba
{
    // private par défaut
public:
    std::string name;
    int age;
    void print();
// constructeur par défaut
    baba()
    {
        name ="jack";
        age=132
    }   
    // ou
    baba() = default;

    baba(std::string name,int age)
    {
        name =name;
        age=age;
    }
// constructeur par défault de copie (par ex en entrée de fonction)
    baba(const baba &other)
    {
        this->age =other.age;
        this->name=other.name;
    }
    // empêche les copies
   baba(baba &other) = delete;
// DESTRUCTOR
    ~baba()
    {
        std::cout<<this->name<<" DESTROYED"<<std::endl;

    }
// Methode qui ne modifie jamais les attributs
void woosh() const
{
    // wow
}
// argument const il FAUT méthode const

void anniversaire()
  {
    this->age += 1;
  }
void operator=(const baba &other)
  {
    this->age = other.age;
    this->name = other.name;
  }

  void operator=(std::tuple<std::string, int> data)
  {
    this->name = std::get<0>(data);
    this->age = std::get<1>(data);
  }
//   mieux:
baba &operator=(const baba &other)
  {
    this->age = other.age;
    this->name = other.name;

    return *this
  }

  baba &operator++(int)
  {
    this->anniversaire();
    return *this;}
    baba operator+(const baba &b) const
  {
    // nécessite d'autoriser la copie
    baba c(this->name + "-" + b.name, int((this->age + b.age) / 2));
    return c;
  }

void operator()(std::string msg)
  {
    std::cout << msg << " " << this->name << std::endl;
  }

  char operator[](int i)
  {
    return this->name[i];
  }
};







//  méthode def autre part
void baba::print()
{
std::cout<<this->name<<this->age<<std::endl;
// this-> est optionnel
}

int main()
{
baba m;
m.name ="bababoe";
m.age = 421;
baba b;

baba m;
baba b("Basile", 34);

  b.anniversaire();
  b++;

  auto data = std::make_tuple("Truc", 42);
  // m = data;
  baba c;
  m = c = data;
  // m = b;
  baba s(m+c);

}