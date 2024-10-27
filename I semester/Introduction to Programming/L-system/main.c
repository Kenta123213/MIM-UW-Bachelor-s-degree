#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

//stala okreslajaca maksymalna dlugosc wejscia
#define MAX_INPUT 101

//funkcja pobierajaca wiersz znakow
void input(char tab[]);
//funkcja wypelniajaca tablice dwu wymiarowe, tablica na indeksie oznaczonym zadanym symbolem zawiera ciag znakow na jaki ma byc ten symbol zamieniony
void tablica2d_input(char tab[][MAX_INPUT], bool chars[]);
//funkcja wczytujaca prolog i epilog oraz wywolujaca ich drukowanie
void prolog_epilog();
//funkcja zwracajaca dlugosc zadanego ciagu znakow
int dlugosc(char tablica[]);
//funkcja drukujaca zadany ciag znakow
void drukuj(char tablica[]);
//funkcja rekurencyjna odpowiadajaca za przeksztalcanie aksjomatu, wywoluje rowniez funkcje tworzenie_slow
void wyprowadzenie(int n, char zastap[][MAX_INPUT], char aksjomat[], char slowa[][MAX_INPUT], bool zastap_chars[], bool slowa_chars[]);
//funkcja przeksztalcajaca symobl na slowo
void tworzenie_slow(char x, char tab[][MAX_INPUT], bool chars[]);

int main(void)
{
    int n;
    char aksjomat[MAX_INPUT + 1];
    char zastap[CHAR_MAX + 1][MAX_INPUT];
    char slowa[CHAR_MAX + 1][MAX_INPUT];
    //tablica okreslajaca dla jakich symboli mamy okreslone reguly zastepowania
    bool defined_chars_zastap[CHAR_MAX + 1];
    //tablica okreslajaca dla jakich symboli mamy okreslona interpretacje slow
    bool defined_chars_slowa[CHAR_MAX + 1];
    //zerowanie tablicy przechowujacej aksjomat
    for (int i = 0; i < MAX_INPUT; i++) aksjomat[i] = (char) 10;
    //zerowanie tablic defined_chars_slowa i defined_chars_zastap
    for (int i = 0; i < CHAR_MAX + 1; i++) {defined_chars_slowa[i] = 0; defined_chars_zastap[i] = 0;}
    //zerowanie tablicy zastap
    for (int i = 0; i < CHAR_MAX + 1; i++)
    {
        for (int j = 0; j < MAX_INPUT; j++)
        {
            zastap[i][j] = (char) 10;
        }
    }
    //zerowanie tablicy slowa
    for (int i = 0; i < CHAR_MAX + 1; i++)
    {
        for (int j = 0; j < MAX_INPUT; j++)
        {
            slowa[i][j] = (char) 10;
        }
    }

    scanf("%d", &n);
    getchar();
    input(aksjomat);
    tablica2d_input(zastap, defined_chars_zastap);
    prolog_epilog();
    tablica2d_input(slowa, defined_chars_slowa);
    wyprowadzenie(n, zastap, aksjomat, slowa,defined_chars_zastap, defined_chars_slowa);
    prolog_epilog();


    return 0;
}

void input(char tab[])
{
    int temp = getchar();
    int i = 0;
    while (temp != 10)
    {
        ungetc(temp, stdin);
        tab[i] = (char) getchar();
        temp = getchar();
        i++;
    }
}

void tablica2d_input(char tab[][MAX_INPUT], bool chars[])
{
    int temp = getchar();
    while (temp != 10)
    {
        chars[temp] = 1;
        input(tab[temp]);
        temp = getchar();
    }
}

void prolog_epilog()
{
    int temp1 = getchar();
    int temp2;
    char tab [MAX_INPUT + 1];
    for (int j = 0; j < MAX_INPUT; j++)
    {
        tab[j] = (char) 10;
    }
    while (temp1 != 10 && temp1 >= 0)
    {
        ungetc(temp1, stdin);
        temp2 = getchar();
        int i = 0;
        while (temp2 != 10)
        {
            ungetc(temp2, stdin);
            tab[i] = (char) getchar();
            temp2 = getchar();
            i++;
        }
        drukuj(tab);
        printf("\n");
        for (int j = 0; j < MAX_INPUT; j++)
        {
            tab[j] = (char) 10;
        }
        temp1 = getchar();
    }
}

int dlugosc(char tablica[])
{
    int i = 0;
    while ((int) tablica[i] != 10)
    {
        i++;
    }
    return i;
}

void drukuj(char tablica[]) {
    for (int i = 0; i < dlugosc(tablica); i++)
    {
        putchar(tablica[i]);
    }
}

void wyprowadzenie(int n, char zastap[][MAX_INPUT], char aksjomat[], char slowa[][MAX_INPUT], bool zastap_chars[], bool slowa_chars[])
{
    if (n == 0)
    {
        for (int i = 0; i < dlugosc(aksjomat); i++)
        {
            tworzenie_slow(aksjomat[i], slowa, slowa_chars);
        }
    }
    else
    {
        for (int i = 0; i < dlugosc(aksjomat); i++)
        {
            if (zastap_chars[(int) aksjomat[i]])
            {
                if (zastap[(int) aksjomat[i]][0] != (char) 10)
                {
                    wyprowadzenie(n - 1, zastap, zastap[(int) aksjomat[i]], slowa, zastap_chars, slowa_chars);
                }
            }

            else
            {
                char temp[2] = {aksjomat[i], '\n'};
                wyprowadzenie(0, zastap, temp, slowa, zastap_chars, slowa_chars);
            }

        }
    }
}

void tworzenie_slow(char x, char tab[][MAX_INPUT], bool chars[])
{
    if(chars[(int) x])
    {
        drukuj(tab[(int) x]);
        printf("\n");
    }
}