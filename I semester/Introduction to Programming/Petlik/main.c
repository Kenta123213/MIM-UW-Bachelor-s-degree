/*
Program petlik wykonuje polecenia wypisania wartosci zmiennej, program oparty jest na autorskim systemie
liczbowym, ktorego podstawa jest liczba 1000000000000000000
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//stala definiujaca o ile miejsc zwiekszamy tablice przechowujaca input gdy zabraknie w jej miejsca
#define CharTab 10
//stala definiujaca ilosc zmiennych
#define varTab 26
//stala definiujaca maksymalna ilosc zer poprzedzajacych liczbe zapisana jako unsigned long long
#define MaxLength 17
//stala definiujaca maksymalna wartosc unsigned long long w autorskim systemie liczbowym
#define Max 999999999999999999
//stala definiujaca podstawe autorskiego system liczbowego
#define Base 1000000000000000000

void wykonaj (char tab[], int dl, unsigned long long **PointerTab, int *length, int start);

void prostaPetla (char tab[], unsigned long long **PointerTab, int *lengthTab, int start, int end);

void zlozonaPetla (char tab[], unsigned long long **PointerTab, int *lengthTab, int start, int end);

bool czyZero (unsigned long long **PointerTab, int *length);

void wypisz (unsigned long long **PointerTab, int *length);

void add1 (unsigned long long **PointerTab, int *length);

void minus1 (unsigned long long **PointerTab, int *length);

void zeruj (unsigned long long **PointerTab, int *length);

int intMin (int a, int b);

int intMax (int a, int b);

void dodajBdoA (unsigned long long **A, int *lengthA, unsigned long long *B, int lengthB);

void input (unsigned long long **PointerTab, int *lengthTab);

int zbadajPetle (char tab[], unsigned long long **PointerTab, int *lengthTab, int i);

//funkcja wypisujaca liczbe w autorskim systemie liczbowym
void wypisz (unsigned long long **PointerTab, int *length)
{
    printf("%llu", (*PointerTab)[*length - 1]);
    for (int i = *length - 2; i >= 0; i--)
    {
        unsigned long long temp = (*PointerTab)[i];
        int dl = 0;
        while (temp / 10 >= 1)
        {
            temp = temp / 10;
            dl++;
        }
        for (int j = 0; j < MaxLength - dl; j++)
        {
            printf("0");
        }
        printf("%llu", (*PointerTab)[i]);
    }
    printf("\n");
}

//funkcja dodajaca 1 do zmiennej w autorskim systemie liczbowym
void add1 (unsigned long long **PointerTab, int *length)
{
    int i = 0;
    while ((*PointerTab)[i] == Max)
    {
        (*PointerTab)[i] = 0;
        i++;
        if (i == *length)
        {
            *PointerTab = (unsigned long long *) realloc(*PointerTab, (unsigned int) (*length + 1) * sizeof(unsigned long long));
            (*PointerTab)[i] = 0;
            (*length)++;
        }
    }
    (*PointerTab)[i]++;
}

//funkcja odejmujaca 1 od zmiennej w autorskim systemie liczbowym
void minus1 (unsigned long long **PointerTab, int *length)
{
    if (czyZero(PointerTab, length) == false)
    {
        int i = 0;
        while ((*PointerTab)[i] == 0)
        {
            (*PointerTab)[i] = Max;
            i++;
        }
        if ((*PointerTab)[i] == 1 && i == *length - 1 && *length > 1)
        {
            *PointerTab = (unsigned long long *) realloc(*PointerTab, (unsigned int) (*length - 1) * sizeof(unsigned long long));
            (*length)--;
        }
        else
        {
            (*PointerTab)[i]--;
        }
    }
}

//funkcja okreslajaca czy liczba zapisana w autoryskim systemie liczbowym jest rowna zero
bool czyZero (unsigned long long **PointerTab, int *length)
{
    if (*length == 1 && (*PointerTab)[0] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//funkcja ustawiajaca wartosc liczby zapisanej w autorskim systemie liczbowym na 0
void zeruj (unsigned long long **PointerTab, int *length)
{
    *PointerTab = (unsigned long long *) realloc(*PointerTab, sizeof(unsigned long long));
    (*PointerTab)[0] = 0;
    *length = 1;
}

//funkcja zwraca mniejsza z dwoch liczb
int intMin (int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

//funkcja zwraca wieksza z dwoch liczb
int intMax (int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

//funkcja dodaje do siebie dwie liczby zapisane w autorskim systemie liczbowym
void dodajBdoA (unsigned long long **A, int *lengthA, unsigned long long *B, int lengthB)
{
    unsigned long long temp = 0;
    bool dluzszeA = true;
    if (intMin(*lengthA, lengthB) == *lengthA) dluzszeA = false;

    for (int i = 0; i < intMax(*lengthA, lengthB); i++)
    {
        unsigned long long x;
        unsigned long long y;
        if (dluzszeA)
        {
            if (i >= lengthB)
            {
                x = 0;
                y = (*A)[i];
            }
            else
            {
                x = B[i];
                y = (*A)[i];
            }
        }
        else
        {
            if (i >= *lengthA)
            {
                x = B[i];
                y = 0;
                *A = (unsigned long long *) realloc(*A, (unsigned int) (*lengthA + 1) * sizeof(unsigned long long));
                (*lengthA)++;
            }
            else
            {
                x = B[i];
                y = (*A)[i];
            }
        }
        bool wykracza = false;
        if (Base - y <= x + temp) wykracza = true;
        else wykracza = false;
        if (wykracza)
        {
            y = y - (Base - x) + temp;
        }
        else
        {
            y = y + x + temp;
        }
        if (wykracza) temp = 1;
        else temp = 0;
        (*A)[i] = y;
    }
    if (temp == 1)
    {
        *A = (unsigned long long *) realloc(*A, (unsigned int) (*lengthA + 1) * sizeof(unsigned long long));
        (*lengthA)++;
        (*A)[(*lengthA) - 1] = 1;
    }
}

//funkcja wczytujaca znaki wierszu wejscia i zapisujaca je w tablicy
void input (unsigned long long **PointerTab, int *lengthTab)
{
    char znak = (char) getchar();
    char *tab = (char *) calloc(CharTab, sizeof(char));
    int i = 0;
    int dl = CharTab;
    while (znak != '\n')
    {
        if (i >= dl)
        {
            tab = (char *) realloc(tab, (unsigned int) (dl + CharTab) * sizeof(char));
            dl += CharTab;
            for (int j = i; j < dl; j++)
            {
                tab[j] = 0;
            }
        }
        tab[i] = znak;
        znak = (char) getchar();
        i++;
    }
    wykonaj(tab, dl, PointerTab, lengthTab, 0);
    free(tab);
}

//funkcja okresla czy petla jest prosta czy zlozona
int zbadajPetle (char tab[], unsigned long long **PointerTab, int *lengthTab, int i)
{
    i++;
    int start = i;
    int lNawias = 1;
    int pNawias = 0;
    while (lNawias != pNawias)
    {
        if (tab[i] == '(') lNawias++;
        if (tab[i] == ')') pNawias++;
        i++;
    }
    if (lNawias == 1)
    {
        prostaPetla(tab, PointerTab, lengthTab, start, i - 1);
    }
    else
    {
        zlozonaPetla(tab, PointerTab, lengthTab, start, i - 1);
    }
    return i - 1;
}

//funkcja wykonujaca prosta petle
void prostaPetla (char tab[], unsigned long long **PointerTab, int *lengthTab, int start, int end)
{
    int i = start;
    char B = tab[i];
    i++;
    if (tab[i] >= 'a' && tab[i] <= 'z') {
        while (i < end)
        {
            dodajBdoA(&PointerTab[tab[i] - 'a'], &lengthTab[tab[i] - 'a'], PointerTab[B - 'a'], lengthTab[B - 'a']);
            i++;
        }
    }
    zeruj(&PointerTab[B - 'a'], &lengthTab[B - 'a']);
}

//funkcja wykonujaca zlozona petle
void zlozonaPetla (char tab[], unsigned long long **PointerTab, int *lengthTab, int start, int end)
{
    int i = start;
    char B = tab[i];
    i++;
    while (czyZero(&PointerTab[B - 'a'], &lengthTab[B - 'a']) == false)
    {
        i = start + 1;
        minus1(&PointerTab[B - 'a'], &lengthTab[B - 'a']);
        while (i < end)
        {
            if (tab[i] >= 'a' && tab[i] <= 'z')
            {
                dodajBdoA(&PointerTab[tab[i] - 'a'], &lengthTab[tab[i] - 'a'], PointerTab[B - 'a'], lengthTab[B - 'a']);
            }
            else if (tab[i] == '(')
            {
                i = zbadajPetle(tab, PointerTab, lengthTab, i);
            }
            i++;
        }
    }
}

//funkcja wykonujaca polecenia programu
void wykonaj (char tab[], int dl, unsigned long long **PointerTab, int *lengthTab, int start)
{
    int i = start;
    while (i < dl && tab[i] != 0)
    {
        char temp = 0;
        if (tab[i] == '=')
        {
            i++;
            temp = tab[i];
            wypisz(&PointerTab[temp - 'a'], &lengthTab[temp - 'a']);
        }
        else if (tab[i] >= 'a' && tab[i] <= 'z')
        {
            temp = tab[i];
            add1(&PointerTab[temp - 'a'], &lengthTab[temp - 'a']);
        }
        else if (tab[i] == '(')
        {
            i = zbadajPetle(tab, PointerTab, lengthTab, i);
        }
        i++;
    }
}

int main() {
    //definicja tablicy przechowujacej zmienna od 'a' do 'z'
    unsigned long long **PointerTab;
    PointerTab = calloc(varTab,sizeof(unsigned long long*));

    //definicja tablicy przechowujacej dlugosci poszczegolnych zmiennych
    int lengthTab[varTab];
    for (int i = 0; i < varTab; i++)
    {
        lengthTab[i] = 1;
        lengthTab[i] = 1;
        PointerTab[i] = (unsigned long long *) calloc(1, sizeof(unsigned long long));
    }

    //inicjowanie funkcji input dla kazdego wierszu wejscia
    char znak = (char) getchar();
    while (znak != EOF)
    {
        ungetc(znak, stdin);
        input(PointerTab, lengthTab);
        znak = (char) getchar();
    }

    //czyszczenie pamięci
    for (int i = 0; i < varTab; i++)
    {
        if (lengthTab[i] != -1)
        {
            free(PointerTab[i]);
        }
    }
    free(PointerTab);

    return 0;
}