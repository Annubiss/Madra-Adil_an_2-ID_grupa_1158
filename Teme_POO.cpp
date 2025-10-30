#include <iostream>
#include <cstring>
using namespace std;

//===================== CLASA Masina =====================
class Masina {
private:
    int anFabricatie;
    float km;
    const int idMasina;
    static int totalMasini;
    char* model;

public:
    Masina() : anFabricatie(2000), km(0.0f), idMasina(++totalMasini) {
        model = new char[4]; strcpy(model, "NA");
    }
    Masina(const char* _model) : anFabricatie(2010), km(0.0f), idMasina(++totalMasini) {
        model = new char[strlen(_model)+1]; strcpy(model, _model);
    }
    Masina(const char* _model, int _an, float _km)
        : anFabricatie(_an), km(_km), idMasina(++totalMasini) {
        model = new char[strlen(_model)+1]; strcpy(model, _model);
    }
    Masina(const Masina& other)
        : anFabricatie(other.anFabricatie), km(other.km), idMasina(++totalMasini) {
        model = new char[strlen(other.model)+1]; strcpy(model, other.model);
    }
    ~Masina(){ delete[] model; }

    // --- get/set
    int getAnFabricatie() const { return anFabricatie; }
    float getKm() const { return km; }
    int getIdMasina() const { return idMasina; }
    const char* getModel() const { return model; }
    void setAnFabricatie(int v){ anFabricatie=v; }
    void setKm(float v){ km=v; }
    void setModel(const char* m){
        delete[] model; model = new char[strlen(m)+1]; strcpy(model,m);
    }

    // --- statice
    static bool necesitaRevizie(float v){ return v >= 10000.0f; }
    static int  getTotalMasini(){ return totalMasini; }

    // ====== Faza 3: operatori ======
    // copy-assignment (deep copy; ID-ul ramane acelasi)
    Masina& operator=(const Masina& o){
        if(this != &o){
            anFabricatie = o.anFabricatie;
            km = o.km;
            setModel(o.model); // deep copy
            // idMasina este const -> nu se reasigneaza
        }
        return *this;
    }
    // += adauga kilometri
    Masina& operator+=(float plusKm){ km += plusKm; return *this; }
    // comparatie dupa kilometri
    bool operator<(const Masina& o) const { return km < o.km; }
    // afisare prietena
    friend ostream& operator<<(ostream& os, const Masina& m){
        os << "Masina#" << m.idMasina << " [" << m.model
           << ", an " << m.anFabricatie << ", km " << m.km << "]";
        return os;
    }

    // prietene din fazele anterioare
    friend float cost_revizie(const Masina&, float, float);
    friend void  adauga_km(Masina&, float);
};
int Masina::totalMasini = 0;


//===================== CLASA Mecanic =====================
class Mecanic {
private:
    int   vechimeAni;
    float tarifOra;
    const int idMecanic;
    static int totalMecanici;
    char* nume;

public:
    Mecanic() : vechimeAni(0), tarifOra(50.0f), idMecanic(++totalMecanici){
        nume = new char[8]; strcpy(nume,"Anonim");
    }
    Mecanic(const char* _nume) : vechimeAni(1), tarifOra(60.0f), idMecanic(++totalMecanici){
        nume = new char[strlen(_nume)+1]; strcpy(nume,_nume);
    }
    Mecanic(const char* _nume, int v, float t)
        : vechimeAni(v), tarifOra(t), idMecanic(++totalMecanici){
        nume = new char[strlen(_nume)+1]; strcpy(nume,_nume);
    }
    Mecanic(const Mecanic& o)
        : vechimeAni(o.vechimeAni), tarifOra(o.tarifOra), idMecanic(++totalMecanici){
        nume = new char[strlen(o.nume)+1]; strcpy(nume,o.nume);
    }
    ~Mecanic(){ delete[] nume; }

    int getVechimeAni() const { return vechimeAni; }
    float getTarifOra() const { return tarifOra; }
    int getIdMecanic() const { return idMecanic; }
    const char* getNume() const { return nume; }
    void setVechimeAni(int v){ vechimeAni=v; }
    void setTarifOra(float t){ tarifOra=t; }
    void setNume(const char* n){ delete[] nume; nume = new char[strlen(n)+1]; strcpy(nume,n); }

    static float estimeazaCost(float tarif, float ore){ return tarif*ore; }
    static int   getTotalMecanici(){ return totalMecanici; }

    // ====== Faza 3: operatori ======
    Mecanic& operator=(const Mecanic& o){
        if(this != &o){
            vechimeAni = o.vechimeAni;
            tarifOra   = o.tarifOra;
            setNume(o.nume);
        }
        return *this;
    }
    // ++ prefix (creste vechimea)
    Mecanic& operator++(){ ++vechimeAni; return *this; }
    // comparatie dupa tarif
    bool operator<(const Mecanic& o) const { return tarifOra < o.tarifOra; }
    // afisare
    friend ostream& operator<<(ostream& os, const Mecanic& c){
        os << "Mecanic#" << c.idMecanic << " [" << c.nume
           << ", vechime " << c.vechimeAni << " ani, tarif " << c.tarifOra << "/h]";
        return os;
    }

    friend float cost_revizie(const Masina&, float, float);
};
int Mecanic::totalMecanici = 0;


//===================== CLASA Piesa =====================
class Piesa {
private:
    float pret;
    int   stoc;
    const int codPiesa;
    static int totalPiese;
    char* denumire;

public:
    Piesa() : pret(0.f), stoc(0), codPiesa(++totalPiese){
        denumire = new char[8]; strcpy(denumire,"Generic");
    }
    Piesa(const char* d, float p) : pret(p), stoc(10), codPiesa(++totalPiese){
        denumire = new char[strlen(d)+1]; strcpy(denumire,d);
    }
    Piesa(const char* d, float p, int s) : pret(p), stoc(s), codPiesa(++totalPiese){
        denumire = new char[strlen(d)+1]; strcpy(denumire,d);
    }
    Piesa(const Piesa& o) : pret(o.pret), stoc(o.stoc), codPiesa(++totalPiese){
        denumire = new char[strlen(o.denumire)+1]; strcpy(denumire,o.denumire);
    }
    ~Piesa(){ delete[] denumire; }

    float getPret() const { return pret; }
    int   getStoc() const { return stoc; }
    int   getCodPiesa() const { return codPiesa; }
    const char* getDenumire() const { return denumire; }
    void setPret(float p){ pret=p; }
    void setStoc(int s){ stoc=s; }
    void setDenumire(const char* d){ delete[] denumire; denumire=new char[strlen(d)+1]; strcpy(denumire,d); }

    static float aplicaDiscount(float pret, float proc){ return pret*(1.0f-proc/100.f); }
    static int   getTotalPiese(){ return totalPiese; }

    // ====== Faza 3: operatori ======
    Piesa& operator=(const Piesa& o){
        if(this != &o){
            pret = o.pret; stoc = o.stoc; setDenumire(o.denumire);
        }
        return *this;
    }
    // scade stocul
    Piesa& operator-=(int buc){ stoc = (buc>stoc)? 0 : stoc-buc; return *this; }
    // scaleaza pretul (ex. 0.9 => -10%)
    Piesa operator*(float factor) const {
        Piesa tmp(*this); tmp.pret *= factor; return tmp;
    }
    // afisare
    friend ostream& operator<<(ostream& os, const Piesa& p){
        os << "Piesa#" << p.codPiesa << " [" << p.denumire
           << ", pret " << p.pret << ", stoc " << p.stoc << "]";
        return os;
    }

    friend void aplica_discount_si_scade_stoc(Piesa&, float, int);
};
int Piesa::totalPiese = 0;


//===================== FUNCTII PRIETENE (existente) =====================
float cost_revizie(const Masina& m, float coefPeKm, float tarifOraMecanic){
    return m.km * coefPeKm + tarifOraMecanic * 2.0f;
}
void aplica_discount_si_scade_stoc(Piesa& p, float disc, int buc){
    if(buc>p.stoc) buc = p.stoc;
    p.pret = Piesa::aplicaDiscount(p.pret, disc);
    p.stoc -= buc;
}
void adauga_km(Masina& m, float plusKm){ m.km += plusKm; }


//===================== MAIN: apelam functia prietena + 12 operatori =====================
int main(){
    cout << "--- Masina ---\n";
    Masina m1("Logan", 2018, 45000), m2("Octavia", 2020, 30000);
    cout << m1 << "\n" << m2 << "\n";                 // << (1,2)
    m1 += 500;                                        // += (3)
    cout << "m1 < m2 ? " << (m1 < m2 ? "DA" : "NU") << "\n"; // < (4)
    Masina m3("Temp"); m3 = m1;                       // = (5)
    cout << "m3 dupa = : " << m3 << "\n";

    cout << "\n--- Mecanic ---\n";
    Mecanic c1("Ionescu", 7, 95), c2("Popa", 3, 70);
    cout << c1 << "\n" << c2 << "\n";                 // << (6,7)
    ++c2;                                             // ++ (8)
    cout << "c2 dupa ++ : " << c2 << "\n";
    cout << "c2 < c1 ? " << (c2 < c1 ? "DA" : "NU") << "\n"; // < (9)
    Mecanic c3; c3 = c2;                              // = (10)
    cout << "c3 dupa = : " << c3 << "\n";

    cout << "\n--- Piesa ---\n";
    Piesa p1("Placute", 120, 24), p2("Filtru", 45, 10);
    cout << p1 << "\n" << p2 << "\n";                 // << (11,12)
    p1 -= 5;                                          // -= (13)
    cout << "p1 dupa -=5 : " << p1 << "\n";
    Piesa p3 = p2 * 0.9f;                             // * (14)
    cout << "p3 = p2 * 0.9 : " << p3 << "\n";
    Piesa p4; p4 = p3;                                // = (15)
    cout << "p4 dupa = : " << p4 << "\n";

    cout << "\n--- Functie prietena ---\n";
    float cost = cost_revizie(m2, 0.05f, c1.getTarifOra());
    cout << "Cost revizie m2 cu " << c1.getNume() << ": " << cost << " lei\n";

    return 0;
}
