#include <iostream>
#include <cstring>
using namespace std;

// ===================== CLASA Masina =====================
class Masina {
public:
    int anFabricatie;
    float km;
    const int idMasina;
    static int totalMasini;
    char* model;

    Masina() : anFabricatie(2000), km(0.0f), idMasina(++totalMasini) {
        model = new char[6]; strcpy(model, "N/A");
    }

    Masina(const char* _model) : anFabricatie(2010), km(0.0f), idMasina(++totalMasini) {
        model = new char[strlen(_model)+1]; strcpy(model, _model);
    }
   
    Masina(const char* _model, int _an, float _km)
        : anFabricatie(_an), km(_km), idMasina(++totalMasini) {
        model = new char[strlen(_model)+1]; strcpy(model, _model);
    }

    
    static bool necesitaRevizie(float km) { return km >= 10000.0f; }

    
    void print() const {
        cout << "Masina#" << idMasina << " [" << model << ", an " << anFabricatie
             << ", km " << km << "]\n";
    }
};
int Masina::totalMasini = 0;


// ===================== CLASA Mecanic =====================
class Mecanic {
public:
    
    int vechimeAni;
    float tarifOra;
    const int idMecanic;
    static int totalMecanici;
    char* nume;

    Mecanic() : vechimeAni(0), tarifOra(50.0f), idMecanic(++totalMecanici) {
        nume = new char[9]; strcpy(nume, "Anonim");
    }
   
    Mecanic(const char* _nume) : vechimeAni(1), tarifOra(60.0f), idMecanic(++totalMecanici) {
        nume = new char[strlen(_nume)+1]; strcpy(nume, _nume);
    }
   
    Mecanic(const char* _nume, int _vechime, float _tarif)
        : vechimeAni(_vechime), tarifOra(_tarif), idMecanic(++totalMecanici) {
        nume = new char[strlen(_nume)+1]; strcpy(nume, _nume);
    }

   
    static float estimeazaCost(float tarifOra, float ore) { return tarifOra * ore; }

    void print() const {
        cout << "Mecanic#" << idMecanic << " [" << nume
             << ", vechime " << vechimeAni << " ani, tarif " << tarifOra << "/h]\n";
    }
};
int Mecanic::totalMecanici = 0;


// ===================== CLASA Piesa =====================
class Piesa {
public:
    
    float pret;
    int stoc;
    const int codPiesa;
    static int totalPiese;
    char* denumire;

    Piesa() : pret(0.0f), stoc(0), codPiesa(++totalPiese) {
        denumire = new char[6]; strcpy(denumire, "Generic");
    }

    Piesa(const char* _den, float _pret) : pret(_pret), stoc(10), codPiesa(++totalPiese) {
        denumire = new char[strlen(_den)+1]; strcpy(denumire, _den);
    }
    
    Piesa(const char* _den, float _pret, int _stoc)
        : pret(_pret), stoc(_stoc), codPiesa(++totalPiese) {
        denumire = new char[strlen(_den)+1]; strcpy(denumire, _den);
    }

    static float aplicaDiscount(float pret, float procent) { return pret * (1.0f - procent/100.0f); }

    void print() const {
        cout << "Piesa#" << codPiesa << " [" << denumire
             << ", pret " << pret << ", stoc " << stoc << "]\n";
    }
};
int Piesa::totalPiese = 0;


// ===================== MAIN – testam toti constructorii =====================
int main() {
    cout << "--- Test Masina ---\n";
    Masina m1;
    Masina m2("Logan");
    Masina m3("Octavia", 2018, 45800);
    m1.print(); m2.print(); m3.print();
    cout << "Revizie m3? " << (Masina::necesitaRevizie(m3.km) ? "DA" : "NU") << "\n\n";

    cout << "--- Test Mecanic ---\n";
    Mecanic c1;
    Mecanic c2("Ionescu");
    Mecanic c3("Popa", 7, 95.0f);
    c1.print(); c2.print(); c3.print();
    cout << "Cost estimat 3h cu c3: " << Mecanic::estimeazaCost(c3.tarifOra, 3.0f) << "\n\n";

    cout << "--- Test Piesa ---\n";
    Piesa p1;
    Piesa p2("FiltruUlei", 45.0f);
    Piesa p3("PlacuteFrana", 120.0f, 24); 
    p1.print(); p2.print(); p3.print();
    cout << "Pret p3 dupa discount 15%: " << Piesa::aplicaDiscount(p3.pret, 15.0f) << "\n\n";

    cout << "--- Statistici ---\n";
    cout << "Total masini: " << Masina::totalMasini << "\n";
    cout << "Total mecanici: " << Mecanic::totalMecanici << "\n";
    cout << "Total piese: " << Piesa::totalPiese << "\n";
    return 0;
}
