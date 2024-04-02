/**
 * \file allapotgep.cpp
 *
 * Ebben a fájlban kell megvalósítania az Allapotgep osztály
 * metódusait, valamint mindazon további osztályokat, melyek szükségesek
 * a feladat megvalósításához.
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include <iostream>
#include <fstream>

#include "allapotgep.h"
#include "memtrace.h"

void Allapotgep::konfigural(const char *fajlnev) {
    delete[] allapotok;
    for (size_t i = 0; i < allapotszam; i++) {
        delete atmenetek[i];
    }
    delete[] atmenetek;
    std::ifstream file(fajlnev);
    if (!file.is_open()) throw "CN12S0";
    file >> allapotszam;
    char c;
    allapotok = new State[allapotszam];
    std::string nev;
    for (size_t i = 0; i < allapotszam; i++) {
        State uj;
        file >> c >> nev;
        uj.set_elfogado(c);
        uj.set_nev(nev);
        allapotok[i] = uj;
    }
    aktualis = allapotok[0];
    aktual_index = 0;
    atmenetek = new std::string*[allapotszam];
    for (size_t i = 0; i < allapotszam; ++i) {
        atmenetek[i] = new std::string[allapotszam];
    }
    for (size_t i = 0; i < allapotszam; i++) {
        for (size_t j = 0; j < allapotszam; j++) {
            file >> atmenetek[i][j];
        }
    }
}

const char* Allapotgep::aktualisallapot() {
    return aktualis.get_nev();
}

bool Allapotgep::elfogad() {
    char elfogado = aktualis.get_elfogado();
    if (elfogado == 'I') return true;
    return false;
}

void Allapotgep::atmenet(Bazis b) {
    for (size_t i = 0; i < allapotszam; i++) {
        if (atmenetek[aktual_index][i] != "0") {
            for (size_t j = 0; j < atmenetek[aktual_index][i].size(); j++){
                if (atmenetek[aktual_index][i][j] == cast(b, true)){
                    aktual_index = i;
                    aktualis = allapotok[i];
                }
            }
        }
    }
}

bool Allapotgep::feldolgoz(const Bazis *b, int n) {
    for (int i = 0; i < n; i++) {
        atmenet(b[i]);
    }
    return elfogad();
}

void Allapotgep::alaphelyzet() {
    delete[] allapotok;
    for (size_t i = 0; i < allapotszam; i++) {
        delete atmenetek[i];
    }
    delete[] atmenetek;
    allapotszam = 0;
    aktual_index = 0;
    aktualis = State();
}

Allapotgep::~Allapotgep() {
    delete[] allapotok;

    for (size_t i = 0; i < allapotszam; i++) {
        delete atmenetek[i];
    }
    delete[] atmenetek;
}