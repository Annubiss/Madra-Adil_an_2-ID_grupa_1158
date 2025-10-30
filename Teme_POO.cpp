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
    Masina()
        : anFabricatie(2000), km(0.0f), idMasina(++totalMasini) {
        model = new char[4]; strcpy(model, "NA");
    }
    Masina(const char* _model)
        : anFabricatie(2010), km(0.0f), idMasina(++totalMasini) {
        model = new char[strlen(_model)+1]; strcpy(model, _model);
    }
    Masina(const char* _model, int _an, float _km)
        : anFabricatie(_an), km(_km), idMasina(++totalMasini) {
        model = new char[strlen(_model)+1]; strcpy(model, _model);
    }
    Masina(const Masina& other)
        : anFabricatie(other.anFabricatie),
          km(other.km),
          idMasina(++totalMasini) { 
        model = new char[strlen(other.model)+1];
        strcpy(model, other.model);
    }
    ~Masina() { delete[] model; }

    int        getAnFabricatie() const { return anFabricatie; }
    float      getKm()           const { return km; }
    int        getIdMasina()     const { return idMasina; }
    const char*getModel()        const { return model; }

    void setAnFabricatie(int v) { anFabricatie = v; }
    void setKm(float v)         { km = v; }
    void setModel(const char* m){
        delete[] model;
        model = new char[strlen(m)+1];
        strcpy(model, m);
    }

    static bool necesitaRevizie(float km) { return km >= 10000.0f; }
    static int  getTotalMasini() { return totalMasini; }


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
    Mecanic()
        : vechimeAni(0), tarifOra(50.0f), idMecanic(++totalMecanici) {
        nume = new char[8]; strcpy(nume, "Anonim");
    }
    Mecanic(const char* _nume)
        : vechimeAni(1), tarifOra(60.0f), idMecanic(++totalMecanici) {
        nume = new char[strlen(_nume)+1]; strcpy(nume, _nume);
    }
    Mecanic(const char* _nume, int _v, float _tarif)
        : vechimeAni(_v), tarifOra(_tarif), idMecanic(++totalMecanici) {
        nume = new char[strlen(_nume)+1]; strcpy(nume, _nume);
    }

    Mecanic(const Mecanic& o)
        : vechimeAni(o.vechimeAni), tarifOra(o.tarifOra), idMecanic(++totalMecanici) {
        nume = new char[strlen(o.nume)+1]; strcpy(nume, o.nume);
    }

    ~Mecanic(){ delete[] nume; }


    int getVechimeAni() const { return vechimeAni; }
    float getTarifOra() const { return tarifOra; }
    int getIdMecanic() const { return idMecanic; }
    const char* getNume() const { return nume; }

    void setVechimeAni(int v){ vechimeAni = v; }
    void setTarifOra(float t){ tarifOra = t; }
    void setNume(const char* n){
        delete[] nume; nume = new char[strlen(n)+1]; strcpy(nume,n);
    }


    static float estimeazaCost(float tarif, float ore){ return tarif*ore; }
    static int   getTotalMecanici(){ return totalMecanici; }


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
    Piesa() : pret(0.0f), stoc(0), codPiesa(++totalPiese) {
        denumire = new char[8]; strcpy(denumire, "Generic");
    }
    Piesa(const char* d, float p) : pret(p), stoc(10), codPiesa(++totalPiese) {
        denumire = new char[strlen(d)+1]; strcpy(denumire,d);
    }
    Piesa(const char* d, float p, int s) : pret(p), stoc(s), codPiesa(++totalPiese) {
        denumire = new char[strlen(d)+1]; strcpy(denumire,d);
    }

    Piesa(const Piesa& o) : pret(o.pret), stoc(o.stoc), codPiesa(++totalPiese) {
        denumire = new char[strlen(o.denumire)+1]; strcpy(denumire,o.denumire);
    }

    ~Piesa(){ delete[] denumire; }

    float getPret() const { return pret; }
    int   getStoc() const { return stoc; }
    int   getCodPiesa() const { return codPiesa; }
    const char* getDenumire() const { return denumire; }

    void setPret(float p){ pret = p; }
    void setStoc(int s){ stoc = s; }
    void setDenumire(const char* d){
        delete[] denumire; denumire = new char[strlen(d)+1]; strcpy(denumire,d);
    }


    static float aplicaDiscount(float pret, float proc){ return pret*(1.0f-proc/100.f); }
    static int   getTotalPiese(){ return totalPiese; }


    friend void  aplica_discount_si_scade_stoc(Piesa&, float, int);
};
int Piesa::totalPiese = 0;


//===================== FUNCTII GLOBALE PRIETENE =====================

float cost_revizie(const Masina& m, float coefPeKm, float tarifOraMecanic) {

    return m.km * coefPeKm + tarifOraMecanic * 2.0f;
}


void aplica_discount_si_scade_stoc(Piesa& p, float discountProc, int bucati) {
    if (bucati > p.stoc) bucati = p.stoc;
    p.pret = Piesa::aplicaDiscount(p.pret, discountProc);
    p.stoc -= bucati;
}


void adauga_km(Masina& m, float plusKm){ m.km += plusKm; }


//===================== MAIN – test complet cerinta Faza 2 =====================
int main(){
    cout << "--- Test Masina (get/set + copy + friend) ---\n";
    Masina m1("Logan", 2018, 45800);
    Masina m2 = m1;
    adauga_km(m2, 2200);
    cout << "m1: " << m1.getModel() << " id=" << m1.getIdMasina()
         << " an=" << m1.getAnFabricatie() << " km=" << m1.getKm()
         << " revizie? " << (Masina::necesitaRevizie(m1.getKm())?"DA":"NU") << "\n";
    cout << "m2(copie): " << m2.getModel() << " id=" << m2.getIdMasina()
         << " an=" << m2.getAnFabricatie() << " km=" << m2.getKm() << "\n";
    cout << "Total masini: " << Masina::getTotalMasini() << "\n\n";

    cout << "--- Test Mecanic (get/set + copy) ---\n";
    Mecanic c1("Ionescu", 7, 95.0f);
    Mecanic c2 = c1;
    cout << c1.getNume() << " id=" << c1.getIdMecanic()
         << " vechime=" << c1.getVechimeAni()
         << " tarif=" << c1.getTarifOra()
         << " cost 3h=" << Mecanic::estimeazaCost(c1.getTarifOra(), 3) << "\n";
    cout << c2.getNume() << " id=" << c2.getIdMecanic()
         << " (copie)\n";
    cout << "Total mecanici: " << Mecanic::getTotalMecanici() << "\n\n";

    cout << "--- Test Piesa (get/set + copy + friend) ---\n";
    Piesa p1("PlacuteFrana", 120.0f, 24);
    Piesa p2 = p1;
    aplica_discount_si_scade_stoc(p1, 15.0f, 3);
    cout << p1.getDenumire() << " cod=" << p1.getCodPiesa()
         << " pret=" << p1.getPret() << " stoc=" << p1.getStoc() << "\n";
    cout << p2.getDenumire() << " cod=" << p2.getCodPiesa()
         << " pret=" << p2.getPret() << " stoc=" << p2.getStoc() << " (copie)\n";
    cout << "Total piese: " << Piesa::getTotalPiese() << "\n\n";

   
    float cost = cost_revizie(m2, 0.05f, c1.getTarifOra());
    cout << "Cost revizie pentru m2 cu " << c1.getNume() << ": " << cost << " lei\n";

    return 0;
}
