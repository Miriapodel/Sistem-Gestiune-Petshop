#include <iostream>
#include <cstring>

using namespace std;

class CustomException : public std::exception
{
    public:

        char* what()
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

    char strada[50], blocul[20], scara[20];
    int numar_strada, numar_locuinta;

    public:

        Adresa()
        {
            strcpy(strada, "_");
            strcpy(blocul, "_");
            strcpy(scara, "_");
            numar_strada = numar_locuinta = 0;
        }

        Adresa(char strada[], int numar_strada,
        int numar_locuinta, char blocul[20] = "_",
        char scara[20] = "_")
        {
            strcpy(this->strada, strada);
            strcpy(this->blocul, blocul);
            strcpy(this->scara, scara);
            this->numar_strada = numar_strada;
            this->numar_locuinta = numar_locuinta;
        }

        void getStrada(char* output)
        {
            strcpy(output, strada);
        }

        void getBlocul(char* output)
        {
            strcpy(output, blocul);
        }

        void getScara(char* output)
        {
            strcpy(output, scara);
        }

        int getNumar_Strada()
        {
            return numar_strada;
        }

        int getNumar_Locuinta()
        {
            return numar_locuinta;
        }

        void setStrada(char input[])
        {
            strcpy(strada, input);
        }

        void setBlocul(char input[])
        {
            strcpy(blocul, input);
        }

        void setScara(char input[])
        {
            strcpy(scara, input);
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

    if ( strcmp(adresa.blocul, "_") != 0 )
        out<<"blocul: "<<adresa.blocul<<", scara: "<<adresa.scara<<", ";

    out<<"numar locuinta: "<<adresa.numar_locuinta<<endl;

    return out;
}

Adresa::Adresa(const Adresa& adresa)
        {
            strcpy(strada, adresa.strada);
            strcpy(blocul, adresa.blocul);
            strcpy(scara, adresa.scara);
            numar_strada = adresa.numar_strada;
            numar_locuinta = adresa.numar_locuinta;
        }

Adresa& Adresa::operator = (const Adresa& adresa)
{

    if ( this != &adresa )
    {
        strcpy(strada, adresa.strada);
            strcpy(blocul, adresa.blocul);
            strcpy(scara, adresa.scara);
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

auto lambda = [](float& sum, int nr, Produs* p)
{
    sum = 0;

    for(int i = 0; i < nr; i++)
    {
        sum += p[i].getPret();
    }
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
            expira = 0;
        }

        ProdusPerisabil(char nume[], char categorie[], float pret, char descriere[] = "_"):Produs(nume, categorie, pret, descriere)
        {

        }

        void set_expira(bool val)
        {
            expira = val;
        }

        float get_price()
        {
            return pret - pret * getReducere();
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

        ProdusOnSale(char nume[], char categorie[], float pret, char descriere[] = "_"):Produs(nume, categorie, pret, descriere)
        {
            
        }

        void set_reducere(double val)
        {
            reducere = val;
        }

        float get_price()
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

        float get_price()
        {
            return pret - getReducere() * pret;
        } 
};

ostream & operator << ( ostream & out, const Produs& produs )
{
    out<<"Nume produs: "<<produs.nume<<", ";

    if ( strcmp(produs.descriere, "_") != 0 )
        out<<"descriere: "<<produs.descriere<<", ";

    out<<"categorie: "<<produs.categorie<<", pret: "<<produs.pret<<endl;

    return out;
}

class Inventar
{
    vector<Produs*> produse;
    int numar_produse;
    static Inventar* ref;

    Inventar()
    {
        numar_produse = 0;
    }

    public:

        Inventar(const Inventar& clasa) = delete;
        void operator = (const Inventar* clasa) = delete;

        static Inventar* getInstance()
        {
            if(ref == NULL)
            {
                ref = new Inventar;

                return ref;
            }

            return ref;
        }

        void adauga_produs(Produs* p);
        void afiseaza_inventar();

};


void Inventar::adauga_produs(Produs* p)
{
    produse.push_back(p);
}

void Inventar::afiseaza_inventar()
{
    for(int i = 0; i < numar_produse; i++)
        cout<<produse[i];
}

class Cos
{

    Produs* produse;
    Discount discount;
    int numar_produse;
    float suma_totala;

    public:

        Cos()
        {
            numar_produse = suma_totala = 0;
            produse = NULL;
        }

        ~Cos()
        {
            if ( produse != NULL )
                delete[] produse;
        }

        Cos(const Cos& cos)
        {
            numar_produse = cos.numar_produse;
            suma_totala = cos.suma_totala;
            discount = cos.discount;
            produse = new Produs[numar_produse];

            for ( int i = 0; i < numar_produse; i++)
            {
                produse[i] = cos.produse[i];
            }
        }

        void adauga_produs(const Produs& produs);
        void scoate_produs(int pozitie);
        template<typename Lambda>
        void valoare_produse(Lambda exp)
        {
            exp(suma_totala, numar_produse, produse);
        }
        void valoare_dupa_discount();
        void adaugare_discount(int procent, char categorie[]);
        void afisare_produse_cos();

        Cos& operator = (const Cos& cos);
        Cos& operator = (Cos&& cos);

        Cos(Cos&& cos)
        {
            produse = cos.produse;
            numar_produse = cos.numar_produse;
            discount = cos.discount;
            suma_totala = cos.suma_totala;

            cos.produse = NULL;
            cos.discount = NULL;
            cos.numar_produse = 0;
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

Cos& Cos::operator = (Cos&& cos)
{
    if ( this != &cos )
    {
        if ( produse != NULL )
        {
            delete[] produse;
        }

        produse = cos.produse;
        numar_produse = cos.numar_produse;
        discount = cos.discount;
        suma_totala = cos.suma_totala;

        cos.produse = NULL;
        cos.discount = NULL;
        cos.numar_produse = 0;
        cos.suma_totala = 0;

        return *this;
    }

    return *this;
}

void Cos::adauga_produs(const Produs& produs)
{
    if ( produse == NULL )
            {
                numar_produse++;
                produse = new Produs[numar_produse];
                produse[0] = produs;
            }
            else
            {
                Produs* aux = new Produs[numar_produse + 1];

                for( int i = 0; i < numar_produse; i++)
                {
                    aux[i] = produse[i];
                }

                aux[numar_produse] = produs;
                numar_produse++;
                delete[]produse;
                produse = aux;
            }
}

void Cos::scoate_produs(int pozitie)
{
    try
    {
        if ( produse != NULL)
        {
            try
            {
                if ( pozitie <= numar_produse && pozitie >= 0)
                {
                    Produs* aux = new Produs[numar_produse - 1];

                    for ( int i = 0; i < numar_produse; i++ )
                        if ( i != ( pozitie - 1 ) )
                            aux[i] = produse[i];

                    numar_produse--;
                    delete[] produse;
                    produse = aux;
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
            produse[i].getCategorie(cat_prod);
            discount.getCategorie(cat_discount);

            if (strcmp(cat_prod, cat_discount) == 0 || strcmp(cat_discount, "toate") == 0)
            {
                suma_totala += ( produse[i].getPret() - produse[i].getPret() * discount.getProcent() / 100 );
            }
            else
            {
                suma_totala += produse[i].getPret();
            }
        }
    }
    else
    {
        valoare_produse(lambda);
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
        discount = cos.discount;
        numar_produse = cos.numar_produse;
        suma_totala = cos.suma_totala;

        if ( produse != NULL)
            delete[] produse;

        produse = new Produs[numar_produse];

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
            cout<<produse[i];

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

        Cos getCos()
        {
            return this->cos;
        }

        void adauga_adresa(const Adresa& adresa);
        void sterge_adresa(int pozitie);
        void afisare_adrese();
        void adauga_produs(const Produs& produs);
        void valoare_produse();
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

void Utilizator::valoare_produse()
{
    cos.valoare_produse(lambda);
}

void Utilizator::adauga_produs(const Produs& produs)
{
    cos.adauga_produs(produs);
}

void Utilizator::adauga_adresa(const Adresa& adresa)
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
        cout<<endl<<"Momentan nicio adresa nu a fost adaugata."<<endl;
    }

    
}

void testare()
{
//     Cos cos, cos2;

//     Produs produs("Aspirator", "Casnic", 250);
//     Produs prod("Periuta", "Igiena", 100);
//     Produs prod2("Laptop", "Tech", 4000);
//     Produs prod3("iPhone", "Tech", 3500);

//     char nume[50], categorie[50], descriere[50];

//     produs.getNume(nume);
//     produs.getCategorie(categorie);
//     produs.getDescriere(descriere);

//     cos.adauga_produs(produs);
//     cos.valoare_produse(lambda);
//     cout<<cos.getSuma_Totala()<<endl;

//     cos.adauga_produs(prod);
//     cos.valoare_produse(lambda);
//     cout<<cos.getSuma_Totala()<<endl;
    
//     cos.adaugare_discount(20, "Igiena");
//     cos.valoare_dupa_discount();
//     cout<<cos.getSuma_Totala()<<endl;

//     cos2.adauga_produs(prod2);
//     cos2.adauga_produs(prod3);

//     cout<<endl;

//     cos = cos2;
//     cos.valoare_produse(lambda);
//     cout<<cos.getSuma_Totala()<<endl;

//     cos.adaugare_discount(50, "Tech");
//     cos.valoare_dupa_discount();
//     cout<<cos.getSuma_Totala()<<endl;

//     cos.scoate_produs(2);
//     cos.valoare_dupa_discount();
//     cout<<cos.getSuma_Totala()<<endl;

//     Utilizator Marcel;
//     Adresa adresa("Victoriei", 10, 20);
//     Adresa adresa2("Plevnei", 15, 3);
//     Marcel.adauga_adresa(adresa);
//     Marcel.adauga_adresa(adresa2);
//     Marcel.afisare_adrese();

//     cout<<prod2;

//     cout<<endl<<"TEST MOVE"<<endl;

//     Produs p("Shaorma", "Mancare", 20);

//     Cos cos3;

//     cos3.adauga_produs(p);

//     cos3.valoare_produse(lambda);
//     cos3.getSuma_Totala();

//     Cos cos4(move(cos3));

//     cout<<cos3.getSuma_Totala()<<endl;

//     cos4.afisare_produse_cos();
//     cos3.afisare_produse_cos();

//     cos4.valoare_produse(lambda);
//     cout<<cos4.getSuma_Totala()<<endl;

    // ProdusPerisabilOnSale ppos("MacBook", "Tech", 2000);
    // cout<<ppos.getReducere()<<endl;
    // ppos.set_reducere(10);
    // cout<<ppos.getReducere()<<endl;
    // ppos.set_expira(1);
    // cout<<ppos.getReducere()<<endl;
    // ppos.setPret(3000);
    // cout<<ppos.get_price()<<endl;

    // ProdusOnSale prod("iPhone", "IT", 3500);
    // Produs p("Tricou", "Haine", 50);
    // Utilizator m;
    // m.adauga_produs(ppos);
    // m.adauga_produs(prod);
    // m.adauga_produs(p);
    // m.valoare_produse();
    // m.getCos().afisare_produse_cos();
    // cout<<m.getSuma_Totala()<<endl;
    // m.getCos().afisare_produse_cos();

    // ProdusPerisabilOnSale test("Scaun", "Mobilier", 500);
    // test.set_expira(1);
    // test.set_reducere(40);
    // cout<<test.get_price();

    Inventar* ref_inv = Inventar::getInstance();

    ref_inv->adauga_produs(new ProdusOnSale);
    ref_inv->afiseaza_inventar();

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

        switch ( optiune )
        {
            case 1:
            {

                int tip;

                cout<<"Alegeti tipul de produs pe care vreti sa il adaugati: "<<endl;
                cout<<"1. Produs"<<endl;
                cout<<"2. Produs Perisabil"<<endl;
                cout<<"3. Produs Redus"<<endl;
                cout<<"4. Produs Perisabil Redus"<<endl;

                cin>>tip;

                switch(tip)
                {
                    case 1:
                    {
                        char nume[50], descriere[50], categorie[50];
                        int pret;

                        cin.ignore();
                        cout<<"Introdu numele produsului: ";
                        cin.get(nume, 50);
                        cin.ignore();
                        cout<<"Introdu descrierea produsului ( tasteaza _ daca nu doresti sa completezi ): ";
                        cin.get(descriere, 50);
                        cin.ignore();
                        cout<<"Introdu categoria din care face parte produsul: ";
                        cin.get(categorie, 50);
                        cin.ignore();
                        cout<<"Introdu pretul produsului: ";
                        cin>>pret;

                        Produs p(nume, categorie, pret, descriere);

                        utilizator.adauga_produs(p);
            
                        cout<<endl<<"Produsul a fost adaugat cu succes!"<<endl<<endl;

                        break;
                    }
                    case 2:
                    {
                        char nume[50], descriere[50], categorie[50];
                        int pret;

                        cin.ignore();
                        cout<<"Introdu numele produsului: ";
                        cin.get(nume, 50);
                        cin.ignore();
                        cout<<"Introdu descrierea produsului ( tasteaza _ daca nu doresti sa completezi ): ";
                        cin.get(descriere, 50);
                        cin.ignore();
                        cout<<"Introdu categoria din care face parte produsul: ";
                        cin.get(categorie, 50);
                        cin.ignore();
                        cout<<"Introdu pretul produsului: ";
                        cin>>pret;

                        ProdusPerisabil p(nume, categorie, pret, descriere);

                        utilizator.adauga_produs(p);
            
                        cout<<endl<<"Produsul a fost adaugat cu succes!"<<endl<<endl;

                        break;
                    }
                    case 3:
                    {
                        char nume[50], descriere[50], categorie[50];
                        int pret;

                        cin.ignore();
                        cout<<"Introdu numele produsului: ";
                        cin.get(nume, 50);
                        cin.ignore();
                        cout<<"Introdu descrierea produsului ( tasteaza _ daca nu doresti sa completezi ): ";
                        cin.get(descriere, 50);
                        cin.ignore();
                        cout<<"Introdu categoria din care face parte produsul: ";
                        cin.get(categorie, 50);
                        cin.ignore();
                        cout<<"Introdu pretul produsului: ";
                        cin>>pret;

                        ProdusOnSale p(nume, categorie, pret, descriere);

                        utilizator.adauga_produs(p);
            
                        cout<<endl<<"Produsul a fost adaugat cu succes!"<<endl<<endl;

                        break;
                    }
                    case 4:
                    {
                        char nume[50], descriere[50], categorie[50];
                        int pret;

                        cin.ignore();
                        cout<<"Introdu numele produsului: ";
                        cin.get(nume, 50);
                        cin.ignore();
                        cout<<"Introdu descrierea produsului ( tasteaza _ daca nu doresti sa completezi ): ";
                        cin.get(descriere, 50);
                        cin.ignore();
                        cout<<"Introdu categoria din care face parte produsul: ";
                        cin.get(categorie, 50);
                        cin.ignore();
                        cout<<"Introdu pretul produsului: ";
                        cin>>pret;

                        ProdusPerisabilOnSale p(nume, categorie, pret, descriere);

                        utilizator.adauga_produs(p);
            
                        cout<<endl<<"Produsul a fost adaugat cu succes!"<<endl<<endl;

                        break;
                    }
                    default:
                        break;
                }

                break;
            }
            case 2:
            {
                char strada[50], blocul[50], scara[50];
                int numar_strada, numar_locuinta;

                cout<<"Introdu numele strazii: ";
                cin.ignore();
                cin.get(strada, 50);
                cin.ignore();
                cout<<"Introdu numarul strazii: ";
             
                cin>>numar_strada;
                cin.ignore();
                cout<<"Introdu blocul ( tasteaza _ daca nu este cazul ): ";
                
                cin.get(blocul, 50);
                cin.ignore();
                cout<<"Introdu scara ( tasteaza _ daca nu este cazul ): ";
                
                cin.get(scara, 50);
                cin.ignore();
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
                cout<<"Username: "<<username<<endl;

                break;
            }
            case 4:
            {
               utilizator.getCos().afisare_produse_cos();

               break;
            }
            case 5:
            {
                utilizator.afisare_adrese();

                break;
            }
            case 6:
            {
                utilizator.valoare_produse();
                cout<<"Valoarea produselor din cos este de "<<utilizator.getSuma_Totala()<<" lei."<<endl<<endl;
                break;
            }
            case 7:
            {
                int pozitie;

                cout<<"Introduceti pozitia elementului pe care vreti sa il stergeti: ";
                cin>>pozitie;

                try
                {
                    utilizator.scoate_produs(pozitie);
                }
                catch(int x)
                {
                    cout<<"Indicele trebuie sa fie un numar pozitiv"<<endl;
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

    meniu_interactiv();
    //testare();

    return 0;
}

