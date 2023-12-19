#include <iostream>
#include <cstring>
#include <string>
#include <random>

using namespace std;

class CustomException : public std::exception
{
public:

    const char* what()
    {
        return "Cosul este deja gol. Nu se pot sterge produse.\n";
    }
};

class Discount
{
    int procent;
    char categorie[50];

public:

    Discount(int procent = 0, char categorie[] = "_")
    {
        this->procent = procent;
        strcpy(this->categorie, categorie);
    }

    int getProcent()
    {
        return procent;
    }

    void getCategorie(char* output)
    {
        strcpy(output, categorie);
    }

    void setProcent(int input)
    {
        procent = input;
    }

    void setCategorie(char input[])
    {
        strcpy(categorie, input);
    }
};

class Adresa
{

    string strada, blocul, scara;
    int numar_strada, numar_locuinta;

public:

    Adresa()
    {
        strada = "_";
        blocul = "_";
        scara = "_";
        numar_strada = numar_locuinta = 0;
    }

    Adresa(string strada, int numar_strada,
           int numar_locuinta, string blocul = "_",
           string scara = "_")
    {
        this->strada = strada;
        this->blocul = blocul;
        this->scara = scara;
        this->numar_strada = numar_strada;
        this->numar_locuinta = numar_locuinta;
    }

    string getStrada()
    {
        return strada;
    }

    string getBlocul()
    {
        return blocul;
    }

    string getScara()
    {
        return scara;
    }

    int getNumar_Strada()
    {
        return numar_strada;
    }

    int getNumar_Locuinta()
    {
        return numar_locuinta;
    }

    void setStrada(string input)
    {
        strada = input;
    }

    void setBlocul(string input)
    {
        blocul = input;
    }

    void setScara(char input)
    {
        scara = input;
    }

    void setNumar_Strada(int input)
    {
        numar_strada = input;
    }

    void setNumar_Locuinta(int input)
    {
        numar_locuinta = input;
    }

    Adresa(const Adresa& adresa);
    Adresa& operator = (const Adresa& adresa);
    friend ostream & operator << ( ostream & out, const Adresa& adresa );

};

ostream & operator << ( ostream & out, const Adresa& adresa )
{
    out << "Strada: "<<adresa.strada<<", numarul: "<<adresa.numar_strada<<", ";

    if ( adresa.blocul != "_" )
        out<<"blocul: "<<adresa.blocul<<", scara: "<<adresa.scara<<", ";

    out<<"numar locuinta: "<<adresa.numar_locuinta<<endl;

    return out;
}

Adresa::Adresa(const Adresa& adresa)
{
    strada = adresa.strada;
    blocul =adresa.blocul;
    scara = adresa.scara;
    numar_strada = adresa.numar_strada;
    numar_locuinta = adresa.numar_locuinta;
}

Adresa& Adresa::operator = (const Adresa& adresa)
{

    if ( this != &adresa )
    {
        strada = adresa.strada;
        blocul =adresa.blocul;
        scara = adresa.scara;
        numar_strada = adresa.numar_strada;
        numar_locuinta = adresa.numar_locuinta;
    }

    return *this;
}

class Prod_baza
{
public:

    virtual float getPret() = 0;

    virtual float getReducere() = 0;

    virtual ~Prod_baza()
    {

    }

};

class Produs : public Prod_baza
{

    char nume[50], descriere[50], categorie[50];

protected:

    float pret;

public:
    Produs()
    {
        strcpy(nume, "_");
        strcpy(descriere, "_");
        strcpy(categorie, "_");
        pret = 0;
    }

    Produs(char nume[], char categorie[], float pret, char descriere[] = "_")
    {
        strcpy(this->nume, nume);
        strcpy(this->categorie, categorie);
        strcpy(this->descriere, descriere);
        this->pret = pret;
    }

    void getNume(char* output)
    {
        strcpy(output, nume);
    }

    void getDescriere(char* output)
    {
        strcpy(output, descriere);
    }

    void getCategorie(char* output)
    {
        strcpy(output, categorie);
    }

    float getPret()
    {
        return pret;
    }

    float getReducere()
    {
        return 0;
    }

    void setNume(char input[])
    {
        strcpy(nume, input);
    }

    void setDescriere(char input[])
    {
        strcpy(descriere, input);
    }

    void setCategorie(char input[])
    {
        strcpy(categorie, input);
    }

    void setPret(float input)
    {
        pret = input;
    }

    friend ostream & operator << ( ostream & out, const Produs& produs );

};

class ProdusPerisabil : virtual public Produs
{
protected:

    bool expira;

    float getReducere()
    {
        return expira * 0.1;
    }

public:

    ProdusPerisabil()
    {
        expira = 1;
    }

    ProdusPerisabil(char nume[], char categorie[], float pret, char descriere[] = "_"):Produs(nume, categorie, pret, descriere)
    {
        expira = 1;
    }

    void set_expira(bool val)
    {
        expira = val;
    }

    float getPret()
    {
        return (float)pret - pret * getReducere();
    }


};

class ProdusOnSale : virtual public Produs
{
protected:

    double reducere;

    float getReducere()
    {
        return (float)reducere / 100;
    }

public:

    ProdusOnSale()
    {
        reducere = 0;
    }

    ProdusOnSale(char nume[], char categorie[], float pret, double reducere, char descriere[] = "_"):Produs(nume, categorie, pret, descriere)
    {
        this->reducere = reducere;


    }

    void set_reducere(double val)
    {
        reducere = val;
    }

    float getPret()
    {
        return pret - getReducere() * pret;
    }
};

class ProdusPerisabilOnSale : public ProdusPerisabil, public ProdusOnSale
{
public:

    ProdusPerisabilOnSale()
    {

    }

    ProdusPerisabilOnSale(char nume[], char categorie[], float pret, char descriere[] = "_"):Produs(nume, categorie, pret, descriere)
    {

    }

    float getReducere()
    {
        return ProdusPerisabil :: getReducere() + ProdusOnSale :: getReducere();
    }

    float getPret()
    {
        return pret - getReducere() * pret;
    }
};

auto lambda = [](float& sum, int nr, vector<Produs*> p)
{
    sum = 0;

    for(int i = 0; i < nr; i++)
    {
        ProdusOnSale* pos = dynamic_cast<ProdusOnSale*>(p[i]);
        ProdusPerisabil* pp = dynamic_cast<ProdusPerisabil*>(p[i]);
        ProdusPerisabilOnSale* ppos = dynamic_cast<ProdusPerisabilOnSale*>(p[i]);

        float pret;

        if(pos)
            pret = pos->getPret();
        else
        if(pp)
            pret = pp->getPret();
        else
        if(ppos)
            pret = ppos->getPret();
        else
            pret = p[i]->getPret();

        sum += pret;
    }
};

ostream & operator << ( ostream & out, const Produs& produs )
{
    out<<"Nume produs: "<<produs.nume<<", ";

    if ( strcmp(produs.descriere, "_") != 0 )
        out<<"Descriere: "<<produs.descriere<<", ";

    out<<"Categorie: "<<produs.categorie<<", Pret: "<<produs.pret<<endl;

    return out;
}

class Inventar
{
    vector<Produs*> produse;
    vector<Produs*> produse_bonus;
    int numar_produse, numar_produse_bonus;
    static shared_ptr<Inventar> ref;

    Inventar()
    {
        numar_produse = numar_produse_bonus = 0;
    }

public:

    Inventar(const Inventar& clasa) = delete;
    void operator = (const Inventar* clasa) = delete;

    static shared_ptr<Inventar> getInstance()
    {
        if(ref == NULL)
        {
            ref.reset(new Inventar);

            return ref;
        }

        return ref;
    }

    void adauga_produs(Produs* p);
    void adauga_produs_bonus(Produs*p);
    void afiseaza_inventar();
    vector<Produs*>& get_produse()
    {
        return produse;
    }
    vector<Produs*>& get_produse_bonus()
    {
        return produse_bonus;
    }
    int getNumarProduse()
    {
        return numar_produse;
    }
    int getNumarProduseBonus()
    {
        return numar_produse_bonus;
    }

};

shared_ptr<Inventar> Inventar :: ref = NULL;

void Inventar::adauga_produs(Produs* p)
{
    produse.push_back(p);
    numar_produse++;
}

void Inventar::adauga_produs_bonus(Produs* p)
{
    produse_bonus.push_back(p);
    numar_produse_bonus++;
}

void Inventar::afiseaza_inventar()
{
    cout<<"Produse standard:"<<endl;
    for(int i = 0; i < numar_produse; i++)
    {

        //unique_ptr<ProdusOnSale> pos(dynamic_cast<ProdusOnSale*>(produse[i]));
        ProdusOnSale* pos = dynamic_cast<ProdusOnSale*>(produse[i]);
        //unique_ptr<ProdusPerisabil> pp(dynamic_cast<ProdusPerisabil*>(produse[i]));

        ProdusPerisabil* pp = dynamic_cast<ProdusPerisabil*>(produse[i]);
        //unique_ptr<ProdusPerisabilOnSale> ppos(dynamic_cast<ProdusPerisabilOnSale*>(produse[i]));
        ProdusPerisabilOnSale* ppos = dynamic_cast<ProdusPerisabilOnSale*>(produse[i]);

        cout << i + 1 << ". Tip produs: ";

        if (ppos)
            cout << "Perisabil Redus, ";
        else
        if (pp)
            cout << "Perisabil, ";
        else
        if (pos)
            cout << "Redus, ";
        else
            cout << "Standard, ";

        cout << *produse[i];
    }

}

class Cos
{

    vector<Produs*> produse;
    Discount discount;
    int numar_produse;
    float suma_totala;

public:

    Cos()
    {
        numar_produse = suma_totala = 0;
    }

    Cos(const Cos& cos)
    {
        numar_produse = cos.numar_produse;
        suma_totala = cos.suma_totala;
        discount = cos.discount;

        for ( int i = 0; i < numar_produse; i++)
        {
            produse.push_back(cos.produse[i]);
        }
    }

    void adauga_produs(Produs* produs);
    void scoate_produs(int pozitie);
    void valoare_dupa_discount();
    void adaugare_discount(int procent, char categorie[]);
    void afisare_produse_cos();
    void reducere_mediu();
    void valoare_cos();
    template<typename Lambda>
    void valoare_produse(Lambda exp)
    {
        exp(suma_totala, numar_produse, produse);
    }

    template<>
    void valoare_produse<Discount>(Discount exp)
    {
        valoare_dupa_discount();
    }

    Cos& operator = (const Cos& cos);

    Cos(Cos&& cos)
    {
        produse = cos.produse;
        numar_produse = cos.numar_produse;
        discount = cos.discount;
        suma_totala = cos.suma_totala;

        while(cos.numar_produse)
        {
            cos.produse.pop_back();
            cos.numar_produse--;
        }

        cos.discount = NULL;
        cos.suma_totala = 0;
    }

    int getNumar_Produse()
    {
        return numar_produse;
    }

    float getSuma_Totala()
    {
        return suma_totala;
    }

};

void Cos::valoare_cos()
{
    if(discount.getProcent())
        valoare_produse(discount);
    else
        valoare_produse(lambda);

}

void Cos::reducere_mediu()
{
    if(all_of(produse.begin(), produse.end(), [](Produs* produs)
    {
        ProdusPerisabil* pp = dynamic_cast<ProdusPerisabil*>(produs);
        ProdusPerisabilOnSale* ppos = dynamic_cast<ProdusPerisabilOnSale*>(produs);

        if(pp)
            return 1;
        if(ppos)
            return 1;

        if(produs->getPret() == 0)
            return 1;

        return 0;
    }))
    {
        discount.setProcent(10);
        discount.setCategorie("toate");
    }
    else
    {
        discount.setProcent(0);
        discount.setCategorie("_");
    }
}

void Cos::adauga_produs(Produs* produs)
{
    produse.push_back(produs);
    numar_produse++;
    sort(produse.begin(), produse.end(), [](Produs* p1, Produs* p2)
    {
        return p1->getPret() > p2->getPret();
    });

    valoare_cos();

    if(suma_totala >= 150 && produse[numar_produse-1]->getPret() != 0)
    {

        shared_ptr<Inventar> ref = Inventar::getInstance();
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, ref->getNumarProduseBonus());
        adauga_produs(ref->get_produse_bonus()[distrib(gen)]);
    }

    reducere_mediu();

    valoare_cos();
}

void Cos::scoate_produs(int pozitie)
{
    try
    {
        if ( numar_produse != 0)
        {
            try
            {
                if ( pozitie <=numar_produse && pozitie >= 0)
                {
                    produse.erase(produse.begin() + pozitie - 1);
                    numar_produse--;
                    reducere_mediu();
                    valoare_cos();
                }
                else
                    throw pozitie;
            }
            catch(int poz)
            {
                cout<<"Nu exista un element pe pozitia "<<poz<<endl;

                throw;
            }
        }
        else
            throw CustomException();
    }
    catch(CustomException ce)
    {
        cout<<ce.what();
    }

}

void Cos::valoare_dupa_discount()
{
    if (discount.getProcent() != 0)
    {
        suma_totala = 0;

        for(int  i = 0; i < numar_produse; i++)
        {
            char cat_prod[50], cat_discount[50];
            produse[i]->getCategorie(cat_prod);
            discount.getCategorie(cat_discount);

            if (strcmp(cat_prod, cat_discount) == 0 || strcmp(cat_discount, "toate") == 0)
            {
                suma_totala += ( produse[i]->getPret() - (float)produse[i]->getPret() * discount.getProcent() / 100 );
            }
            else
            {
                suma_totala += produse[i]->getPret();
            }
        }
    }
    else
    {
        valoare_cos();
    }
}

void Cos::adaugare_discount(int procent, char categorie[])
{
    discount.setProcent(procent);
    discount.setCategorie(categorie);
}

Cos& Cos::operator = (const Cos& cos)
{
    if ( this != &cos )
    {
        if ( numar_produse != 0)
            produse.clear();

        discount = cos.discount;
        numar_produse = cos.numar_produse;
        suma_totala = cos.suma_totala;

        for ( int i = 0; i < numar_produse; i++)
        {
            produse[i] = cos.produse[i];
        }
    }

    return *this;
}

void Cos::afisare_produse_cos()
{
    if ( numar_produse != 0 )
    {
        for ( int i = 0; i < numar_produse; i++ )
        {
            ProdusOnSale* pos = dynamic_cast<ProdusOnSale*>(produse[i]);
            ProdusPerisabil* pp = dynamic_cast<ProdusPerisabil*>(produse[i]);
            ProdusPerisabilOnSale* ppos = dynamic_cast<ProdusPerisabilOnSale*>(produse[i]);

            cout<<i+1<<". Tip produs: ";

            if(ppos)
                cout<<"Perisabil Redus, ";
            else
            if(pp)
                cout<<"Perisabil, ";
            else
            if(pos)
                cout<<"Redus, ";
            else
                cout<<"Standard, ";

            cout<<*produse[i];
        }
    }
    else
    {
        cout<<"Momentan nu exista produse in cos"<<endl<<endl;
    }
}

class Utilizator
{

    char nume[50], prenume[50], username[50], parola[50], email[50];
    Cos cos;
    Adresa* adrese;
    int numar_adrese;

public:

    Utilizator()
    {
        adrese = NULL;
        numar_adrese = 0;
        strcpy(nume, "_");
        strcpy(prenume, "_");
        strcpy(username, "_");
        strcpy(parola, "_");
        strcpy(email, "_");
    }

    Utilizator(char username[], char parola[], char email[] = "_", char nume[] = "_", char prenume[] = "_")
    {
        adrese = NULL;
        numar_adrese = 0;
        strcpy(this->nume, nume);
        strcpy(this->prenume, prenume);
        strcpy(this->username, username);
        strcpy(this->parola, parola);
        strcpy(this->email, email);

    }

    ~Utilizator()
    {
        if ( adrese != NULL )
            delete[] adrese;
    }

    void getNume(char* output)
    {
        strcpy(output, nume);
    }

    void getPrenume(char* output)
    {
        strcpy(output, prenume);
    }

    void getUsername(char* output)
    {
        strcpy(output, username);
    }

    void getParola(char* output)
    {
        strcpy(output, parola);
    }

    void getEmail(char* output)
    {
        strcpy(output, email);
    }

    void setNume(char input[])
    {
        strcpy(nume, input);
    }

    void setPrenume(char input[])
    {
        strcpy(prenume, input);
    }

    void setUsername(char input[])
    {
        strcpy(username, input);
    }

    void setParola(char input[])
    {
        strcpy(parola, input);
    }

    void setEmail(char input[])
    {
        strcpy(email, input);
    }

    Cos& getCos()
    {
        return cos;
    }

    void adauga_adresa(const reference_wrapper<Adresa> adresa);
    void sterge_adresa(int pozitie);
    void afisare_adrese();
    void adauga_produs(Produs* produs);
    void valoare_cos();
    void scoate_produs(int pozitie);
    int getSuma_Totala();

};

int Utilizator::getSuma_Totala()
{
    return cos.getSuma_Totala();
}

void Utilizator::scoate_produs(int pozitie)
{
    try
    {
        cos.scoate_produs(pozitie);
    }
    catch(int x)
    {
        throw;
    }
}

void Utilizator::valoare_cos()
{
    cos.valoare_cos();
}

void Utilizator::adauga_produs(Produs* produs)
{
    cos.adauga_produs(produs);
}

void Utilizator::adauga_adresa(const reference_wrapper<Adresa> adresa)
{
    if ( adrese == NULL )
    {
        numar_adrese = 1;
        adrese = new Adresa[numar_adrese];

        adrese[0] = adresa;
    }
    else
    {
        Adresa* aux = new Adresa[numar_adrese + 1];

        for ( int i = 0; i < numar_adrese; i++)
        {
            aux[i] = adrese[i];
        }

        aux[numar_adrese] = adresa;
        numar_adrese++;
        delete[] adrese;
        adrese = aux;
    }
}

void Utilizator::sterge_adresa(int pozitie)
{
    if ( adrese != NULL )
    {
        if ( pozitie <= numar_adrese )
        {
            Adresa* aux = new Adresa[numar_adrese - 1];

            for ( int i = 0; i < numar_adrese; i++ )
            {
                if ( i != ( pozitie - 1 ) )
                {
                    aux[i] = adrese[i];
                }
            }

            numar_adrese--;
            delete[] adrese;
            adrese = aux;
        }
        else
        {
            cout<<"Nu exista o adresa pe pozitia "<<pozitie<<".\n";
        }
    }
    else
    {
        cout<<"Nu exista nicio adresa care poate fi stearsa";
    }
}

void Utilizator::afisare_adrese()
{
    if ( numar_adrese != 0 )
    {
        for ( int i = 0; i < numar_adrese; i++ )
        {
            cout<<adrese[i];
        }
    }
    else
    {
        cout<<"Momentan nicio adresa nu a fost adaugata."<<endl;
    }


}

void testare()
{
    shared_ptr<Inventar> ref_inv = Inventar::getInstance();

    Cos c;
    c.adauga_produs(ref_inv->get_produse()[6]);
    c.adauga_produs(ref_inv->get_produse()[5]);
    c.valoare_cos();
    c.afisare_produse_cos();
    c.valoare_cos();
    cout<<c.getSuma_Totala();

//    ProdusPerisabil* prod = new ProdusPerisabil("MacBook", "Tech", 2000);
//    afisare_pret(prod);

//     Cos cos, cos2;
//
//     char nume[50], categorie[50], descriere[50];
//
//     cos.adauga_produs(new Produs("Aspirator", "Casnic", 250));
//     cos.valoare_cos();
//     cout<<cos.getSuma_Totala()<<endl;
//
//     cos.adauga_produs(new Produs("Periuta", "Igiena", 100));
//     cos.valoare_cos();
//     cout<<cos.getSuma_Totala()<<endl;
//
//     cos.adaugare_discount(20, "Igiena");
//     cos.valoare_dupa_discount();
//     cout<<cos.getSuma_Totala()<<endl;
//
//     cos2.adauga_produs(new Produs("Laptop", "Tech", 4000));
//     cos2.adauga_produs(new Produs("iPhone", "Tech", 3500));
//
//     cout<<1<<endl;
//     cos2.valoare_cos();
//
//     cout<<cos2.getSuma_Totala()<<endl;
//     cos2.adaugare_discount(50, "Tech");
//     cos2.valoare_dupa_discount();
//     cout<<2<<endl;
//     cout<<cos2.getSuma_Totala()<<endl;
//
//     cos.scoate_produs(2);
//     cos.valoare_dupa_discount();
//     cout<<cos.getSuma_Totala()<<endl;
//
//     Utilizator Marcel;
//     Adresa adresa("Victoriei", 10, 20);
//     Adresa adresa2("Plevnei", 15, 3);
//     Marcel.adauga_adresa(adresa);
//     Marcel.adauga_adresa(adresa2);
//     Marcel.afisare_adrese();
//
//     cout<<endl<<"TEST MOVE"<<endl;
//
//
//     Cos cos3;
//
//     cos3.adauga_produs(new Produs("Shaorma", "Mancare", 20));
//
//     cos3.valoare_cos();
//     cos3.getSuma_Totala();
//
//
//     Utilizator m;
//     m.adauga_produs(new ProdusPerisabilOnSale("MacBook", "Tech", 2000));
//     m.adauga_produs(new ProdusOnSale("iPhone", "IT", 3500, 20));
//     m.adauga_produs(new Produs("Tricou", "Haine", 50));
//     m.valoare_cos();
//     m.getCos().afisare_produse_cos();
//     cout<<m.getSuma_Totala()<<endl;
//     m.getCos().afisare_produse_cos();
//
//     ProdusPerisabilOnSale test("Scaun", "Mobilier", 500);
//     test.set_expira(1);
//     test.set_reducere(40);
//     cout<<test.get_price();
//
//    Inventar* ref_inv = Inventar::getInstance();
//
//
//
//    Utilizator u;
//
//    u.adauga_produs(ref_inv->get_produse()[0]);
//    u.getCos().afisare_produse_cos();
//    u.valoare_cos();
//   cout<< u.getSuma_Totala()<<endl;
//
//    cout<<endl<<endl;

//    Cos c;
//    c.adauga_produs(new ProdusOnSale("iPhone", "IT", 3500, 20));
////    c.test();
//    c.valoare_cos();
//    c.valoare_dupa_discount();
//
//    cout<<c.getSuma_Totala()<<endl;
}

void meniu_interactiv()
{
    char nume[50], prenume[50], email[50], username[50], parola[50];

    cout<<"Creeaza un utilizator nou!"<<endl;
    cout<<"Nume: ( tasteaza _ daca nu doresti sa completezi ) ";
    cin.get(nume, 50);
    cin.ignore();
    cout<<"Prenume: ( tasteaza _ daca nu doresti sa completezi ) ";
    cin.get(prenume, 50);
    cin.ignore();
    cout<<"Email: ( tasteaza _ daca nu doresti sa completezi ) ";
    cin.get(email, 50);
    cin.ignore();
    cout<<"Username: ";
    cin.get(username, 50);
    cin.ignore();
    cout<<"Parola: ";
    cin.get(parola, 50);
    cin.ignore();
    cout<<endl;

    Utilizator utilizator(username, parola, email, nume, prenume);

    bool meniu = 1;
    int optiune;



    while ( meniu != 0 )
    {
        cout<<"1. Adauga un produs in cos"<<endl;
        cout<<"2. Adauga o adresa de livrare"<<endl;
        cout<<"3. Afiseaza datele utilizatorului"<<endl;
        cout<<"4. Afiseaza produsele din cos"<<endl;
        cout<<"5. Afiseaza adresele de livrare ale utilizatorului"<<endl;
        cout<<"6. Afiseaza suma totala a produselor din cos"<<endl;
        cout<<"7. Stergeti un produs din cos"<<endl;
        cout<<"8. Inchide"<<endl;
        cout<<endl<<" Tasteza numarul optiunii pe care vrei sa o alegi! "<<endl;


        cin>>optiune;
        cout<<endl;

        switch ( optiune )
        {
            case 1:
            {
                shared_ptr<Inventar> ref_inv = Inventar::getInstance();
                int numar_produs;

                cout<<"Produsele disponibile sunt: "<<endl;
                ref_inv->afiseaza_inventar();

                cout<<"Alege numarul produsului pe care vrei sa il adaugi in cos: ";
                cin>>numar_produs;
                cout<<endl;

                if(numar_produs <= ref_inv->getNumarProduse())
                    utilizator.adauga_produs(ref_inv->get_produse()[numar_produs - 1]);
                else
                    cout<<"Nu exista niciun produs cu numarul introdus!\n\n";


                break;
            }
            case 2:
            {
                string strada, blocul, scara;
                int numar_strada, numar_locuinta;

                cout<<"Introdu numele strazii: ";
                cin>>strada;
                cout<<"Introdu numarul strazii: ";

                cin>>numar_strada;
                cout<<"Introdu blocul ( tasteaza _ daca nu este cazul ): ";

                cin>>blocul;
                cout<<"Introdu scara ( tasteaza _ daca nu este cazul ): ";

                cin>>scara;
                cout<<"Introdu numarul locuintei: ";

                cin>>numar_locuinta;

                Adresa adresa(strada, numar_strada, numar_locuinta, blocul, scara);

                utilizator.adauga_adresa(adresa);

                cout<<endl<<"Adresa a fost adaugata cu succes!"<<endl;

                break;
            }
            case 3:
            {
                char nume[50], prenume[50], email[50], username[50], parola[50];

                utilizator.getNume(nume);
                utilizator.getPrenume(prenume);
                utilizator.getEmail(email);
                utilizator.getUsername(username);
                utilizator.getParola(parola);

                cout<<"Nume: "<<nume<<endl;
                cout<<"Prenume: "<<prenume<<endl;
                cout<<"Email: "<<email<<endl;
                cout<<"Username: "<<username<<endl<<endl;

                break;
            }
            case 4:
            {
                utilizator.getCos().afisare_produse_cos();
                cout<<endl;

                break;
            }
            case 5:
            {
                utilizator.afisare_adrese();
                cout<<endl;

                break;
            }
            case 6:
            {
                cout<<"Valoarea produselor din cos este de "<<utilizator.getSuma_Totala()<<" lei."<<endl<<endl;
                break;
            }
            case 7:
            {
                int pozitie;
                cout<<"Produsele pe care le aveti in cos sunt:\n";
                utilizator.getCos().afisare_produse_cos();

                if(utilizator.getCos().getNumar_Produse())
                {
                    cout<<"Introduceti pozitia elementului pe care vreti sa il stergeti: ";
                    cin>>pozitie;
                    cout<<endl;
                    try
                    {
                        utilizator.scoate_produs(pozitie);
                    }
                    catch(int x)
                    {
                        cout<<"Indicele trebuie sa fie un numar pozitiv"<<endl;
                    }
                }


                break;
            }
            case 8:
            {
                cout<<"Aplicatia a fost inchisa !"<<endl;

                meniu = 0;
            }
            default:
            {
                break;
            }
        }
    }
}

int main()
{
    shared_ptr<Inventar> ref_inv = Inventar::getInstance();

    ref_inv->adauga_produs(new ProdusOnSale("iPhone", "Telefoane", 3500, 20));
    ref_inv->adauga_produs(new Produs("MacBook Air", "Laptopuri", 8000));
    ref_inv->adauga_produs(new Produs("MacBook Pro", "Laptopuri", 10000));
    ref_inv->adauga_produs(new Produs("PS5", "Console", 3500));
    ref_inv->adauga_produs(new ProdusPerisabilOnSale("Branza", "Branzeturi", 10));
    ref_inv->adauga_produs(new ProdusPerisabilOnSale("Cascaval", "Branzeturi", 15));
    ref_inv->adauga_produs(new ProdusPerisabil("Iaurt", "Branzeturi", 5));
    ref_inv->adauga_produs_bonus(new Produs("Lesa", "Ingrijire", 0));
    ref_inv->adauga_produs_bonus(new Produs("Baton Iepuri", "Hrana", 0));
    ref_inv->adauga_produs_bonus(new Produs("Snack rozatoare", "Hrana", 0));
    ref_inv->afiseaza_inventar();

    meniu_interactiv();
    //testare();

    return 0;
}
