/* RABIN-KARP ALGORITAM */
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

// d definisemo kao globalnu varijablu bez mogucnosti izmjene vrijednosti iste. d nam predstavlja
// broj karaktera u alfabetu.
#define d 256

/* Radi lakseg pisanja koda uvedimo sljedece skracenice
    p -> sablon
    txt -> orginalni tekst
    q -> prost broj
    h -> hash
*/

void search(char P[], char txt[], int q)
{
    int m = strlen(P); // Sa m i n cemo definisati duzinu stringova, u biti sa m duzinu teksta koji trazimo, a sa n duzinu orginalnog teksta
    int n = strlen(txt);
    int i, j; //Incijalizacija i,j
    int p = 0; // Sa p i t cemo incijalizirati hash vrijednosti sablona i orginalnog teksta, tj sa p sablona i sa t orginala
    int t = 0;
    int h = 1; // h postavimo na 1 posto cemo h dobiti kao proizvod i on nam predstavlja vrijednost hasha

    // Nakon postavljanja h na 1, h treba da bude "pow(d, m-1)%q"
    for (i = 0; i < m-1; i++)
        h = (h*d)%q;

    /* Za slucaj da se nas sablon u orginalnom tekstu nalazi negdje na pocetku teksta, treba da izracunamo hash vrijednosti sablona i prvog
    uslovno receno prozora u tekstu. Prozor nam je potreban da bi "klizali" po orginalnom tekstu i racunali hash vrijednost tog prozora.
    Sam prozor je duzine m. */
    for (i = 0; i < m; i++)
    {
        p = (d*p + P[i])%q;
        t = (d*t + txt[i])%q;
    }

    // Ovom for petljom sa sablonom tj patternom se "klizemo" po tekstu prolazeci poziciju po pozciju
    for (i = 0; i <= n-m; i++){

        /* Ukoliko su hash vrijednost od sablona i prozora iste onda cemo provjeravati za svaki od karaktera da li se podudara sa sablonom,
        tj provjeravamo da li je tekst u prozoru jedank trazenom tekstu. */

        if ( p == t ){

            /* Provjeravaj karakter po karakter, ali karakter po karakter prozora kojim klizemo kroz tekst.
               Zato i uzimamo da idemo do duzine patterna jer su nam te duzine prozori kojima prolazimo kroz
               orginalan tekst. */

            for (j = 0; j < m; j++){
                if (txt[i+j] != P[j]) // Provjerava karakter po karakter
                    break; // Nemaju iste karaktere stani, jer je dovoljno da se jedno slovo ne podudara.
            }

            // Ako nam je hash uzorka i orginalnog teksta isti, te ako im se karakteri podudarju sablon postoji
            // Podudaranja podrazumijeva da je p[0,1,...,m-1]=txt[i,i+1,...,i+m-1]
            if (j == m)
                cout<<"POSTOJI I NALAZI SE NA POZICIJI "<<i<<endl;
        }

        // Ukoliko ne dodje do podudaranja racunamo hash vrijednost za sljedeci prozor teksta
        if ( i < n-m )
        {
            t = (d*(t - txt[i]*h) + txt[i+m])%q; // Formula za rehesiranje

            if (t < 0) // Za slucaj da je hash vrijednost teksta negativan broj to nam ne odgovara, pa ga onda prebacujemo u pozitivan
            t = (t + q);
        }
    }
}
//BERNSTEIN HASH FUNKCIJA ZA POREDJENJE
unsigned bernstein_hash ( void *key, int len )
{
    unsigned char *p = key;
    unsigned h = 0;
    int i;

    for ( i = 0; i < len; i++ )
        h = 33 * h + p[i];

    return h;
}

//POlinomna hash funkcija
unsigned hash(const char* s, unsigned salt)
{
    unsigned h = salt;
    while (*s)
        h = h * 101 + (unsigned) *s++;
    return h;
}

int hashLookup[256];

// Hash funkcija za 6 karakterne stringove
int hash(const char *str)
{
    int ret = 0, mult = 1;
    for (const char *p = str; *p; *p++, mult *= 32) {
        assert(*p >= 0 && *p < 256);
        ret += mult * hashLookup[*p];
    }

    return ret;
}

int main()
{
    char txt[] = "Bijah šetao gadom";
    char pat[] = "dom";
    int q = 101;
    search(pat, txt, q);
    return 0;
}
