/*
 * "Reversi"
 * Program umozliwia gre w "Reversi"
 *
 * Tworzy początkową plansze do gry w "Reversi"
 * Pokazuje gracza ktory ma wykonac ruch, oraz legalne pola gdzie moze postawic pionek
 * Po wczytaniu ruchu gracza, program wykonuje ruch, a nastepnie zmienia plansze zgodnie z zasadami gry w "Reversi"
 * Gracz ma prawo pominac swoj ruch wprowadzajac do konsoli znak '-'
 * Gre konczy sie wprowadzajac do konsoli znak '='
 */

#include <stdio.h>
#include <stdbool.h>

//znak wskazujacy na gracza "czarny"
#define CZARNY 'C'
//znak wskazujacy na gracza "bialy"
#define BIALY 'B'
//stala uzywana do zmiany kolumny wejscia na indeks w tablicy
#define ASCII1 97
//stala uzywana do zmiany wiersza wejscia na indeks w tablicy
#define ASCII2 49
//ilosc wierszy w tablicy
#define SIZEW 8
//ilosc kolumn w tablicy
#define SIZEK 8
//oznaczenie bialego pionka na planszy
#define BP 1
//oznaczenie czarnego pionka na planszy
#define CP 2
//oznaczenie pustego miejsca na planszy
#define NP 0

//tworzy poczatkowe ustawienie planszy
void Start(int tablica[][SIZEK]);
//informuje ktory gracz teraz wykonuje ruch, oraz pokazuje jego legalne ruchy
void Prompt(char gracz, int tablica[][SIZEK]);
//zamienia indeksy wierszow i kolumn, na oznaczenie przyjete na planszy, oraz je drukuje
void printLegalne (int w, int k);
//sprawdza czy ruch w konkretnym kierunku jest legalny
bool Sprawdz(int kolor, int tablica[][SIZEK], int k1, int w1, int i, int j);
//wywoluje funkcje Sprawdz w kazdym z 8 mozliwych kierunkow
void Legalne (int kolor, int tablica[][SIZEK]);
//wczytuje ruch uzytkownika i zmienia oznaczenia przyjete na planszy na indeksy wierszow i kolumn, wywoluje funkcje Ruch
bool Input(char gracz, int tablica[][SIZEK]);
//jezeli ruch jest legalny to wykonuje go we wskazanym kierunku
void wykonajRuch(char gracz, int tablica[][SIZEK], int w, int k, int w2, int k2);
//wywoluje funkcje Ruch w kazdym z 8 mozliwych kierunkow
void Ruch(char gracz, int tablica[][SIZEK], int w, int k);
//wywoluje gre w petli
int main(void)
{
    int tab[SIZEW][SIZEK];
    Start(tab);

    int i = 1;
    char gracz;
    bool gra = true;
    while (gra == true)
    {
        if (i % 2 == 0) gracz = BIALY;
        else gracz = CZARNY;
        Prompt(gracz, tab);
        gra = Input(gracz, tab);
        getchar();
        i++;
    }
}

void Ruch(char gracz, int tablica[][SIZEK], int w, int k)
{
    //wywoluje funkcje w kierunku: ukos prawo - dol
    wykonajRuch(gracz, tablica, w, k, 1, 1);
    //wywoluje funkcje w kierunku: dol
    wykonajRuch(gracz, tablica, w, k, 1, 0);
    //wywoluje funkcje w kierunku: prawo
    wykonajRuch(gracz, tablica, w, k, 0, 1);
    //wywoluje funkcje w kierunku: ukos lewo - gora
    wykonajRuch(gracz, tablica, w, k, -1, -1);
    //wywoluje funckje w kierunku: ukos prawo - dol
    wykonajRuch(gracz, tablica, w, k, -1, 1);
    //wywoluje funkcje w kierunuku: ukos lewo - dol
    wykonajRuch(gracz, tablica, w, k, 1, -1);
    //wywoluje funkcje w kierunku: dol
    wykonajRuch(gracz, tablica, w, k, -1, 0);
    //wywoluje funkcje w kierunku: lewo
    wykonajRuch(gracz, tablica, w, k, 0, -1);
}

void wykonajRuch(char gracz, int tablica[][SIZEK], int w, int k, int w2, int k2) {
    /*funckja zmienia pola w okreslonym kierunku, jezeli okaze sie ze ruch byl nielegalny,
     *to przywraca plansze do stanu sprzed zmian
     */

    int kolor;
    int kolor2;
    if (gracz == CZARNY) {
        kolor = CP;
        kolor2 = BP;
    } else {
        kolor = BP;
        kolor2 = CP;
    }
    int w1 = w;
    int k1 = k;
    int ruchy = 0;
    tablica[w][k] = kolor;
    while (w1 + w2 >= 0 && w1 + w2 < SIZEW && k1 + k2 >= 0 && k1 + k2 < SIZEK && tablica[w1 + w2][k1 + k2] == kolor2)
    {
        tablica[w1 + w2][k1 + k2] = kolor;
        w1 += w2;
        k1 += k2;
        ruchy++;
    }
    if (w1 + w2 < 0 || k1 + k2 < 0 || k1 + k2 > SIZEK - 1 || w1 + w2 > SIZEK - 1 || tablica[w1 + w2][k1 + k2] != kolor)
    {
        w1 = w;
        k1 = k;
        for (int i = 0; i < ruchy; i++) {
            tablica[w1 + w2][k1 + k2] = kolor2;
            w1 += w2;
            k1 += k2;
        }
    }
}

void Start(int tablica[][SIZEK])
{
    for (int i = 0; i < SIZEW; i++)
    {
        for (int j = 0; j < SIZEK; j++)
        {
            if ((i == 3 && j == 3) || (i == 4 && j == 4))
            {
                tablica[i][j] = BP;
            }
            else if ((i == 4 && j == 3) || (i == 3 && j == 4))
            {
                tablica[i][j] = CP;
            }
            else
            {
                tablica[i][j] = NP;
            }
        }
    }
}

void Prompt(char gracz, int tablica[][SIZEK])
{
    printf("%c", gracz);
    if (gracz == CZARNY)
    {
        Legalne(CP, tablica);
    }
    else
    {
        Legalne(BP, tablica);
    }
    printf("\n");
}

bool Input(char gracz, int tablica[][SIZEK])
{
    int wiersz;
    int kolumna;
    int w;
    int k;
    kolumna = getchar();
    if (kolumna == '=')
    {
        return false;
    }
    if (kolumna == '-')
    {
        return true;
    }
    else
    {
        wiersz = getchar();
    }
    k = kolumna - ASCII1;
    w = wiersz - ASCII2;
    Ruch(gracz, tablica, w, k);
    return true;
}

void printLegalne (int w, int k)
{
    char k1 = (char) k + 'a';
    char w1 = (char) w + '1';
    printf(" %c%c", k1, w1);
}

void Legalne (int kolor, int tablica[][SIZEK])
{
    //zmienna checekd zapewnia, ze jedno pole nie zostanie wypisane dwa razy
    bool checked = false;
    for (int j = 0; j < SIZEK; j++)
    {
        for (int i = 0; i < SIZEW; i++)
        {
            checked = false;
            if (tablica[i][j] == NP)
            {
                //wywoluje funkcje w kierunku: ukos prawo - dol
                checked = Sprawdz(kolor, tablica, 1, 1, i, j);
                //wywoluje funkcje w kierunku: ukos lewo - gora
                if (checked == false) checked = Sprawdz(kolor, tablica, -1, -1, i, j);
                //wywoluje funkcje w kierunku: ukos prawo - gora
                if (checked == false) checked = Sprawdz(kolor, tablica, 1, -1, i, j);
                //wywoluje funkcje w kierunku: ukos lewo - dol
                if (checked == false) checked = Sprawdz(kolor, tablica, -1, 1, i, j);
                //wywoluje funkcje w kierunku: prawo
                if (checked == false) checked = Sprawdz(kolor, tablica, 1, 0, i, j);
                //wywoluje funkcje w kierunku: dol
                if (checked == false) checked = Sprawdz(kolor, tablica, 0, 1, i, j);
                //wywoluje funkcje w kierunku: lewo
                if (checked == false) checked = Sprawdz(kolor, tablica, -1, 0, i, j);
                //wywoluje funkcje w kierunku: gora
                if (checked == false) checked = Sprawdz(kolor, tablica, 0, -1, i, j);
            }
        }
    }
}

bool Sprawdz (int kolor, int tablica[][SIZEK], int k1, int w1, int i, int j)
{
    int kolor2;
    if (kolor == BP) kolor2 = CP;
    if (kolor == CP) kolor2 = BP;
    int k;
    int w;
    if (j + k1 >= 0 && j + k1 <= SIZEW - 1 && i + w1 >= 0 && i + w1 <= SIZEK - 1)
    {
        if (tablica[i + w1][j + k1] == kolor2)
        {
            k = j + k1;
            w = i + w1;
            while (k >= 0 && k <= (SIZEK - 1) && w >= 0 && w <= (SIZEW - 1))
            {
                if (tablica[w][k] == kolor)
                {
                    printLegalne(i, j);
                    return true;
                }
                else if (tablica[w][k] == NP)
                {
                    return false;
                }
                k += k1;
                w += w1;
            }
        }
    }
    return false;
}