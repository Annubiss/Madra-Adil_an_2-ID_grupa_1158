// Proiect POO – Faza 1 (Atelier Mecanic: Masina, Mecanic, Piesa)
// Toate clasele în același fișier, atribute în public (cum cere Faza 1)

#include <iostream>
#include <cstring>
using namespace std;

// ===================== CLASA Masina =====================
class Masina {
public:
    // atribute normale
    int anFabricatie;
    float km;
    // atribut constant (se setează în lista de inițializare)
    const int idMasina;
    // atribut static (contor de obiecte)
    static int totalMasini;
    // pointer alocat pe heap (nume model)
    char* model;

    // ctor 1: default
    Masina() : anFabricatie(2000), km(0.0f), idMasina(++totalMasini) {
        model = new char[6]; strcpy(model, "N/A");
    }
    // ctor 2: parțial
    Masina(const char* _model) : anFabricatie(2010), km(0.0f), idMasina(++totalMasini) {
        model = new char[strlen(_model)+1]; strcpy(model, _model);
    }
    // ctor 3: complet
    Masina(const char* _model, int _an, float _km)
        : anFabricatie(_an), km(_km), idMasina(++totalMasini) {
        model = new char[strlen(_model)+1]; strcpy(model, _model);
    }

    // funcție statică: conversie km → “revizie necesară?”
    static bool necesitaRevizie(float km) { return km >= 10000.0f; }

    // utilitar mic pentru afișare
    void print() const {
        cout << "Masina#" << idMasina << " [" << model << ", an " << anFabricatie
             << ", km " << km << "]\n";
    }
};
int Masina::totalMasini = 0;


// ===================== CLASA Mecanic =====================
class Mecanic {
public:
    // atribute normale
    int vechimeAni;
    float tarifOra;
    // atribut constant
    const int idMecanic;
    // static
    static int totalMecanici;
    // pointer heap (nume)
    char* nume;

    // ctor 1: default
    Mecanic() : vechimeAni(0), tarifOra(50.0f), idMecanic(++totalMecanici) {
        nume = new char[9]; strcpy(nume, "Anonim");
    }
    // ctor 2
    Mecanic(const char* _nume) : vechimeAni(1), tarifOra(60.0f), idMecanic(++totalMecanici) {
        nume = new char[strlen(_nume)+1]; strcpy(nume, _nume);
    }
    // ctor 3
    Mecanic(const char* _nume, int _vechime, float _tarif)
        : vechimeAni(_vechime), tarifOra(_tarif), idMecanic(++totalMecanici) {
        nume = new char[strlen(_nume)+1]; strcpy(nume, _nume);
    }

    // funcție statică: cost estimat pentru n ore
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
    // atribute normale
    float pret;
    int stoc;
    // constant
    const int codPiesa;
    // static
    static int totalPiese;
    // pointer heap (denumire)
    char* denumire;

    // ctor 1: default
    Piesa() : pret(0.0f), stoc(0), codPiesa(++totalPiese) {
        denumire = new char[6]; strcpy(denumire, "Generic");
    }
    // ctor 2
    Piesa(const char* _den, float _pret) : pret(_pret), stoc(10), codPiesa(++totalPiese) {
        denumire = new char[strlen(_den)+1]; strcpy(denumire, _den);
    }
    // ctor 3
    Piesa(const char* _den, float _pret, int _stoc)
        : pret(_pret), stoc(_stoc), codPiesa(++totalPiese) {
        denumire = new char[strlen(_den)+1]; strcpy(denumire, _den);
    }

    // funcție statică: aplică un discount (%) și întoarce prețul nou
    static float aplicaDiscount(float pret, float procent) { return pret * (1.0f - procent/100.0f); }

    void print() const {
        cout << "Piesa#" << codPiesa << " [" << denumire
             << ", pret " << pret << ", stoc " << stoc << "]\n";
    }
};
int Piesa::totalPiese = 0;


// ===================== MAIN – testăm toți constructorii =====================
int main() {
    cout << "--- Test Masina ---\n";
    Masina m1;                        // ctor default
    Masina m2("Logan");               // ctor parțial
    Masina m3("Octavia", 2018, 45800);// ctor complet
    m1.print(); m2.print(); m3.print();
    cout << "Revizie m3? " << (Masina::necesitaRevizie(m3.km) ? "DA" : "NU") << "\n\n";

    cout << "--- Test Mecanic ---\n";
    Mecanic c1;                          // default
    Mecanic c2("Ionescu");               // parțial
    Mecanic c3("Popa", 7, 95.0f);        // complet
    c1.print(); c2.print(); c3.print();
    cout << "Cost estimat 3h cu c3: " << Mecanic::estimeazaCost(c3.tarifOra, 3.0f) << "\n\n";

    cout << "--- Test Piesa ---\n";
    Piesa p1;                             // default
    Piesa p2("FiltruUlei", 45.0f);        // parțial
    Piesa p3("PlacuteFrana", 120.0f, 24); // complet
    p1.print(); p2.print(); p3.print();
    cout << "Pret p3 dupa discount 15%: " << Piesa::aplicaDiscount(p3.pret, 15.0f) << "\n\n";

    cout << "--- Statistici ---\n";
    cout << "Total masini: " << Masina::totalMasini << "\n";
    cout << "Total mecanici: " << Mecanic::totalMecanici << "\n";
    cout << "Total piese: " << Piesa::totalPiese << "\n";
    return 0;
}
