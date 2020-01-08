#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <unordered_map>
#include <typeinfo>
using namespace std;


const double PENALIZARE = 5;

class Cont
{
protected:
    string detinator;
    string dataDeschidere;
    double sold;
    string istoric;
    static string banca;
public:
    Cont()
    {
        detinator = "Unknown";
        dataDeschidere = "01-Jan-2020";
        sold = 0;
        istoric = " ";
        banca = "ING";
    }
    Cont(const Cont &ob)
    {
        detinator = ob.detinator;
        dataDeschidere = ob.dataDeschidere;
        sold=ob.sold;
        istoric = ob.istoric;

    }
    string getDetinator() const
    {
        return detinator;
    }
    string getDataDeschidere() const
    {
        return dataDeschidere;
    }
    string getIstoric() const
    {
        return istoric;
    }
    double getSold() const
    {
        return sold;
    }

    void setDetinator(string s)
    {
        detinator = s;
    }
    void setDataDeschidere(string s)
    {
        dataDeschidere = s;
    }
    void setIstoric(string s)
    {
        istoric= s;
    }
    void setSold(double x)
    {
        sold=x;
    }

    virtual void retragere()
    {
        //istoric = istoric + to_string(sold);
    }
    virtual void depunere() {}
    virtual void citire()
    {
        cout<<"detinator: ";
        cin>>detinator;
        cout<<endl<<"dataDeschidere: ";
        cin>>dataDeschidere;
        cout<<endl<<"sold: ";
        cin>> sold;
        /*      cout<<endl<<"istoric: ";
              cin>>istoric;   */
    }
    virtual void afisare()
    {
        cout<<" "<<detinator;
        cout<<" "<<dataDeschidere;
        cout<<" "<<sold;
        cout<<istoric;
    }
    static string getBanca()
    {
        return banca;
    }
    virtual Cont operator =(const Cont &ob)
    {
        if (this!=&ob)
        {
            detinator = ob.detinator;
            dataDeschidere= ob.dataDeschidere;
            sold=ob.sold;
            istoric=ob.istoric;
        }
        return *this;
    }

    friend istream &operator >> (istream &in, Cont &ob );
};
string Cont::banca="ING";

istream &operator >> (istream &in, Cont &ob )
{
    cout<<"detinator: ";
    string a;
    double man;
    in>>a;
    ob.setDetinator(a);
    cout<<endl<<"dataDeschidere: ";
    in>>a;
    ob.setDataDeschidere(a);
    cout<<endl<<"sold: ";
    in>>man;
    ob.setSold(man);
    cout<<endl<<"istoric: ";
    in>>a;
    ob.setIstoric(a);
    return in;
}

class ContEconomii:public Cont
{
protected:
    int rataDobanda;
public:
    ContEconomii():Cont()
    {
        rataDobanda = 0;
    }
    ContEconomii(const ContEconomii &ob):Cont(ob)
    {
        rataDobanda = ob.rataDobanda;
    }
    void citire()
    {
        this->Cont::citire();
        cout<<endl<<"rataDobanda: ";
        cin>>rataDobanda;
    }
    void afisare()
    {
        this->Cont::afisare();
        cout<<" "<<rataDobanda;
    }

    ContEconomii operator =(const ContEconomii &ob)
    {
        if (this!=&ob)
        {
            this->Cont::operator=(ob);
            rataDobanda=ob.rataDobanda;
        }
        return *this;
    }


};
class ContCurrent:public Cont
{

protected:
    int nrTranzactiiGratuite;
public:
    ContCurrent():Cont()
    {
        nrTranzactiiGratuite = 10;
    }
    ContCurrent(const ContCurrent &ob):Cont(ob)
    {
        nrTranzactiiGratuite = ob.nrTranzactiiGratuite;

    }
    void retragere(double, string);
    void depunere(double, string);
    void citire()
    {
        this->Cont::citire();
        cout<<endl<<"nrTranzactiiGratuite: ";
        cin>>nrTranzactiiGratuite;
    }
    void afisare()
    {
        this->Cont::afisare();
        cout<<nrTranzactiiGratuite;
    }
    ContCurrent operator =(const ContCurrent &ob)
    {
        if (this!=&ob)
        {
            this->Cont::operator=(ob);
            nrTranzactiiGratuite=ob.nrTranzactiiGratuite;
        }
        return *this;
    }


};

void ContCurrent::retragere(double bani, string locatie)
{
    if (locatie==banca)
        if (nrTranzactiiGratuite > 0)
        {

            try
            {

                if (sold - bani < 0)
                    throw 'a';
                else
                {
                    sold-=bani;
                    nrTranzactiiGratuite --;
                }
            }

            catch(char x)
            {
                cout<<"Fonduri insuficiente"<<endl;
            }
        }
        else
        {

            try
            {

                if (sold - bani - PENALIZARE < 0)
                    throw 'a';
                else
                {
                    sold-=(bani+PENALIZARE);

                }
            }

            catch(char x)
            {
                cout<<"Fonduri insuficiente"<<endl;
            }
        }
    else
    {
        try
        {

            if (sold - bani - PENALIZARE < 0)
                throw 'a';
            else
            {
                sold-=(bani+PENALIZARE);

            }
        }

        catch(char x)
        {
            cout<<"Fonduri insuficiente"<<endl;
        }
    }

}

void ContCurrent:: depunere (double bani, string locatie)
{
    if (locatie == banca)
    {
        sold+=bani;

    }
    else
        sold = sold + bani - PENALIZARE;
    istoric = istoric + (to_string(sold));
}



template <class T>
class GestionareConturi
{

    vector <T*> vectorConturi;
    unordered_map<int, vector <string> > umap;
    static int index;
public:
    GestionareConturi() {};
    ~GestionareConturi();
    void addCont()
    {
        cout<<"\n 1 pt Cont curent, 2 pt ContEconomii:   ";
        int man;

        cin>>man;
        if (man==1)
        {
            index++;
            ContCurrent ob1;
            ob1.citire();
            vectorConturi.push_back(new ContCurrent(ob1));



        }
        if (man==2)
        {
            index++;
            ContEconomii ob2;
            ob2.citire();
            vectorConturi.push_back(new ContEconomii(ob2));

        }

    }

    void afisareConturi()
    {
        for (int i=0; i< index; i++)
        {
            vectorConturi[i]->afisare();
            cout<<endl;
        }


    }


};
template <class T> int GestionareConturi<T>::index=0;

template <> ContEconomii AfisareConturiDobandaAn(ContEconomii a)
{

}

int main()
{

    GestionareConturi<Cont> *Banca1 = new GestionareConturi<Cont>;
    Banca1->addCont();
     Banca1->addCont();
    Banca1->afisareConturi();


    return 0;
}
