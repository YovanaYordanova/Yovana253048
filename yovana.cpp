#include <iostream>
#include <string>

using namespace std;

// Дефиниране на абстрактен базов клас
class LegalEntity {
protected:
    // Използване на спецификатор за достъп protected
    string Ime;
    int GodinaNaPostupvane;

public:
    // Инициализиране на данните чрез конструктори с параметри
    LegalEntity(string Ime, int Godina) : Ime(Ime), GodinaNaPostupvane(Godina) {}

    // Осигуряване на виртуален деструктор в базовия клас
    virtual ~LegalEntity() {}

    // Деклариране на чисто виртуални функции
    virtual void Godishnina() const = 0;
    virtual void printInfo() const = 0;
    virtual void provejdaneDelo() = 0;

    // Препокриване (Overriding) на виртуални методи (базова дефиниция)
    virtual void infoSpecializaciq() {}
};

// Реализиране на йерархия от класове с поне три нива на наследяване (Ниво 1)
class Judge : public LegalEntity {
protected:
    string Sud;
    int BroiResheniq;

public:
    Judge(string Ime, int Godina, string Sud, int BroiResheniq)
        : LegalEntity(Ime, Godina), Sud(Sud), BroiResheniq(BroiResheniq) {
    }

    // Препокриване (Overriding) на виртуални методи
    void Godishnina() const override {
        cout << Ime << " // " << (2026 - GodinaNaPostupvane) << " godini staj v sudebnata sistema" << endl;
    }
};

// Реализиране на йерархия от класове (Ниво 2 - Разклонение 1)
class CriminalJudge : public Judge {
private:
    string rang;
    int tejkiDela;
    string dopulnitelenTekst;

public:
    CriminalJudge(string Ime, int Godina, string Sud, int BroiResheniq, string rang, int tejkiDela, string tekst)
        : Judge(Ime, Godina, Sud, BroiResheniq), rang(rang), tejkiDela(tejkiDela), dopulnitelenTekst(tekst) {
    }

    void printInfo() const override {
        cout << Ime << ", Sud: " << Sud << ", Resheniq: " << BroiResheniq << endl;
        cout << "Kvalifikaciq: " << rang << ", Tejki nakazatelni dela: " << tejkiDela << endl;
    }

    void provejdaneDelo() override {
        cout << dopulnitelenTekst << endl;
    }
};

// Реализиране на йерархия от класове (Ниво 1 - Разклонение 2)
class Lawyer : public LegalEntity {
protected:
    string oblast;

public:
    Lawyer(string Ime, int Godina, string oblast)
        : LegalEntity(Ime, Godina), oblast(oblast) {
    }

    void Godishnina() const override {
        cout << Ime << " // " << (2026 - GodinaNaPostupvane) << " godini chlen na Advokatskata kolegiq" << endl;
    }
};

// Реализиране на йерархия от класове (Ниво 2)
class DefenseAttorney : public Lawyer {
protected:
    string Kliant;
    string Postijenie;
    string finalenTekst;

public:
    DefenseAttorney(string Ime, int Godina, string oblast, string Kliant, string Postijenie, string fTekst)
        : Lawyer(Ime, Godina, oblast), Kliant(Kliant), Postijenie(Postijenie), finalenTekst(fTekst) {
    }

    void printInfo() const override {
        cout << Ime << ", Oblast: " << oblast << endl;
        cout << "Klient: " << Kliant << ", Uspeh: " << Postijenie << endl;
    }

    void provejdaneDelo() override {
        cout << finalenTekst << endl;
    }

    void infoSpecializaciq() override {
        cout << Ime << " e specializiran advokat po " << oblast << ", s uspeh: " << Postijenie << endl;
    }
};

int main() {
    // Полиморфична обработка на обекти чрез масив от указатели към базовия клас
    LegalEntity* entities[] = {
        // Динамично управление на паметта (създ. с new)
        new CriminalJudge("Ivan Ivanov", 1998, "Okrujen Sud", 450, "Vurhoven Sudbiq", 120,
            "Sudiq Ivanov vodi deloto s izkluchitelna preciznost i po sigurni pravila."),

        new DefenseAttorney("Elena Petrova", 2010, "Nakazatelno pravo", "Darina Georgieva",
            "Osporena osuditelna prisuda", "Advokat Petrova uspq da dokaje nevinnostta na svoq klient."),

        new CriminalJudge("Georgi Stoqnov", 2005, "Raionen Sud", 300, "Starshi Sudiq", 45,
            "Sudiq Stoqnov e izvesten sus svoqta obektivnost pri razglejdaneto na dela."),

        new DefenseAttorney("Stefan Kolev", 2015, "Turgovsko pravo", "Bulgarian-Trade OOD",
            "Specheleno arbitrajno delo", "Misiqta na advokata e da zashtiti interesite na firmata.")
    };

    // Полиморфична обработка чрез обхождане на масива
    for (int i = 0; i < 4; ++i) {
        cout << (i + 1) << ")" << endl;

        // Полиморфично извикване на препокрити виртуални методи
        entities[i]->printInfo();
        entities[i]->Godishnina();
        entities[i]->infoSpecializaciq();

        cout << endl;
        entities[i]->provejdaneDelo();
        cout << endl;
    }

    // Динамично управление на паметта (освобождаване с delete)
    for (int i = 0; i < 4; ++i) {
        delete entities[i];
    }

    return 0;
}