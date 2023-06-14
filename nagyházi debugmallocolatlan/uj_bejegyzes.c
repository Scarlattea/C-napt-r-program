#include "konyvtar.h"

void bejegyzes_adatainak_beolvasasa(void)
{
    char *beolvasott_cim;
    char *beolvasott_hely;
    char *beolvasott_megjegyzes;
    char *beolvasott_ido;

    printf("Adj meg egy bejegyzescimet!: \n");
    int hossz_cim, hossz_hely, hossz_megjegyzes;
    beolvasott_cim = beolvas(&hossz_cim);
    if (hossz_cim == 0)
    {
        bool cim_enter = true;
        while(cim_enter)
        {
            printf("A cimet nem hagyhatod uresen! Kerlek adj meg egy cimet! \n");
            beolvasott_cim = beolvas(&hossz_cim);
            if (hossz_cim != 0)
            {
                cim_enter = false;
            }
        }
    }
    //printf("TEST: %s\n", beolvasott_cim);

    printf("Add meg az esemeny helyet! \n");
    beolvasott_hely = beolvas(&hossz_hely);
    //printf("%s \n", beolvasott_hely);

    printf("Adj meg megjegyzest!\n");
    beolvasott_megjegyzes = beolvas(&hossz_megjegyzes);
    //printf("%s \n", beolvasott_megjegyzes);

    beolvasott_ido = teljes_ido_bekeres(beolvasott_ido);

    kilepes_mentessel_vagy_nelkule(beolvasott_cim, beolvasott_hely, beolvasott_megjegyzes, beolvasott_ido);
}

char* napot_beolvas(char *beolvasott_ido)
{
    char napok[14][4] =
        {
            "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun","mon", "tue", "wed", "thu", "fri", "sat", "sun"
        };
        bool isGood=false;
        while(!isGood)
        {
            int nap_hossz;
            char* nap = beolvas(&nap_hossz);

            bool talalte = false;
            for(int i=0; i<14; i++)
            {
                int egyeznek_e= strcmp(nap, napok[i]);
                //printf("%d", egyeznek_e);
                if(egyeznek_e == 0)
                {
                    nap[0] = toupper(nap[0]);
                    beolvasott_ido = nap;
                    // ujraolvas = false;
                    //beolvasott_ido[3] ='\0';
                    talalte=true;
                }
            }
            if(!talalte)
            {
                printf("Helytelen megadas, kerlek probald ujra!");
            }
            else
            {
                isGood=true;
            }
        }

    return beolvasott_ido;
}

char* honapot_beolvas(char* beolvasott_ido)
{
    char honapok[24][4] =
    {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
        "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"
    };
    bool isGood = false;
    while(!isGood)
    {
        int honap_hossz;
        char* honap = beolvas(&honap_hossz);

        for (int i=0; i<24; i++)
        {
            int egyeznek_e = strcmp(honap, honapok[i]);
            //printf("%d", egyeznek_e);
            if (egyeznek_e == 0)
            {
                honap[0]= toupper(honap[0]);
                strcat(beolvasott_ido, " ");
                strcat(beolvasott_ido, honap);
                isGood=true;
            }
        }
        if(!isGood)
        {
            printf("Helytelen megadas, kerlek probald ujra!");
        }
    }
    return beolvasott_ido;
}

char* ev_beolvasas(bool *szokoev_e)
{
    bool isGood=false;
    int ev;
    while(!isGood)
    {
        if(scanf("%d", &ev) == 1)
        {
            if (ev<0)
            {
                printf("Az evszam nem lehet negativ, kerlek adj meg masik szamot!\n");
            }
            else
            {
                isGood=true;
            }
        }
        else
        {
                printf("Az evszam csak szam lehet, kerlek adj meg masik szamot!\n");
                int c;
                getchar();
        }
    }
    if (ev%4 == 0)
    {
        szokoev_e = true;
        //printf("oszthato neggyel");
    }
    else
    {
        szokoev_e = false;
    }

    int digits=1;
    int for_use = ev;
    while (for_use > 10)
    {
        for_use /=10;
        digits++;
    }

    char* beolvasott_ev = (char*)malloc(sizeof(char)*(digits+1));

    snprintf(beolvasott_ev, (digits+1), "%d", ev);

    printf("%s\n", beolvasott_ev);
    return beolvasott_ev;
}

char* hanyadika_beolvas(bool szokoev_e, char* beolvasott_ido)
{
    int hanyadika;
    bool isGood = false;

    while(!isGood)
    {
        isGood=true;
        if(scanf("%d", &hanyadika)== 1)
        {
            if(hanyadika<1 | hanyadika > 31)
            {
                printf("A honap legalabb 1 es legfeljebb 31 napos. Adj meg egy uj szamot, ami a megadott tartomanyba esik!\n");
                isGood=false;
            }

            if (hanyadika ==29)
            {
                char* feb_e = strstr(beolvasott_ido, "Feb");
                if (feb_e != NULL)
                {
                    if(!szokoev_e)
                    {
                        printf("A korabban megadott ev nem szokoev, igy nincs ebben az evben feb 29. Kerlek adj meg masik szamot!\n");
                        isGood=false;
                    }
                }
            }
            if (hanyadika == 31)
            {
                char* feb_e = strstr(beolvasott_ido, "Feb");
                if (feb_e != NULL)
                {
                    printf("A korabban megadott honap (Feb) nem lehet 31 napos. Kerlek probalkozz egy kisebb szammal!\n");
                    isGood=false;
                }

                char honapok[7][4] =
                {
                    "Jan","Mar","May", "Jul", "Aug", "Oct", "Dec"
                };

                bool megtalalta_e= false;

                char* harmincegy_napos_e;

                for (int i=0; i<7 && !megtalalta_e; i++)
                {
                    harmincegy_napos_e = strstr(beolvasott_ido, honapok[i]);
                    //printf("A beolvasott ido: %s\n", beolvasott_ido);
                    //printf("harmincegy_napos_e : s\n", harmincegy_napos_e);
                    if(harmincegy_napos_e != NULL)
                    {
                        megtalalta_e = true;
                    }
                }

                if(harmincegy_napos_e == NULL)
                {
                    printf("A korabban megadott honap nem 31 napos, kerlek adj meg kisebb szamot!\n");
                    isGood=false;
                }
            }
            if (hanyadika ==30)
            {
                char* feb_e = strstr(beolvasott_ido, "Feb");
                if (feb_e != NULL)
                {
                    printf("A korabban megadott honap (Feb) nem lehet 30 napos. Kerlek probalkozz egy kisebb szammal!\n");
                    isGood=false;
                }
            }
            if(isGood)
            {
                int digits= 1;
                int for_use = hanyadika;

                while( for_use > 10)
                {
                    for_use /=10;
                    digits++;
                }

                char* beolvasott_hanyadika = (char*)malloc(sizeof(char)*(digits+1));

                snprintf(beolvasott_hanyadika, (digits+1), "%d", hanyadika);

                if(digits <2)
                {
                    for (int j = digits+2; j>0; j--)
                    {
                        beolvasott_hanyadika[j] = beolvasott_hanyadika[j-1];
                    }
                    beolvasott_hanyadika[0] = '0';
                }

                printf("%s\n", beolvasott_hanyadika);
                return beolvasott_hanyadika;
            }
        }
        else
        {
            printf("Nem sikerult a beolvasas\n");
            fflush(stdin);
            //getch(hanyadika);
            isGood=false;
        }
    }
}

char* beolvas(int *hossz)
{
    int i=1;
    char bekert;
    char *szoveg = (char*)malloc(0);

    while ((scanf("%c", &bekert)==1) & (bekert != '\n'))
    {
        szoveg = (char*)realloc(szoveg, i);
        szoveg[i-1]= bekert;
        i++;
    }
    szoveg = (char*)realloc(szoveg, i);
    szoveg[i-1]= '\0';
    *hossz = i-1;
    //printf("TEST2: %s\n", szoveg);
    return szoveg;
}

void kilepes_mentessel_vagy_nelkule (char* beolvasott_cim, char* beolvasott_hely, char* beolvasott_megjegyzes,char* beolvasott_ido)
{
    printf("Mit szeretnel tenni?\nA) Mentes es visszalepes menube \nB) Visszalepes mentes nelkul\n");

    char *valasz_mentes_e= (char*)malloc(1);
    valasz_mentes_e[0]= 'z';
    int meret_mentes_e;
    bool elso_while_e = true;

    while (valasz_mentes_e[0]!='A' && valasz_mentes_e[0]!='a' && valasz_mentes_e[0]!='B'&& valasz_mentes_e[0]!='b')
    {
        elso_while_e = false;
        free(valasz_mentes_e);
        valasz_mentes_e= beolvas(&meret_mentes_e);

        if(valasz_mentes_e[0]== 'A' | valasz_mentes_e[0]=='a' & meret_mentes_e<2)
        {
            fajlba_mentes(beolvasott_cim, beolvasott_hely, beolvasott_megjegyzes, beolvasott_ido);

            printf("%s \n%s\n%s\n%s\n",  beolvasott_cim, beolvasott_hely, beolvasott_megjegyzes, beolvasott_ido);

            free(beolvasott_cim);
            free(beolvasott_hely);
            free(beolvasott_megjegyzes);
            free(valasz_mentes_e);

            printf("A bejegyzes mentese megtortent\n");
            //iiigen, tulajdonképpen a fo_menupontok rekurzívan visszatér magába, viszont egy ilyen egyszerűen müködő programnál valószínűleg ez még nem okoz gondokat
            //fo_menupontok();
            return;
        }
        else if(valasz_mentes_e[0]=='B' | valasz_mentes_e[0]== 'b' & meret_mentes_e<2)
        {
            elso_while_e = false;
            printf("Biztos nem akarod menteni?\nA) Tenyleg nem akarom menteni\nB) Mentsd el megis!\n");

            char *megerosites= (char*)malloc(1);
            megerosites[0]='z';
            int megerosites_meret;

            while(megerosites[0]!='A'|megerosites[0]!='a'| megerosites[0]!='B'|megerosites[0]!='b')
            {
                free(megerosites);
                megerosites= beolvas(&megerosites_meret);

                if(megerosites[0]== 'B' | megerosites[0]== 'b' & megerosites_meret <2)
                {
                    //fájlba mentés!
                    time_t most;
                    time(&most);
                    char *beolvasott_ido = ctime(&most);

                    fajlba_mentes(beolvasott_cim, beolvasott_hely, beolvasott_megjegyzes, beolvasott_ido);

                    printf("%s \n%s\n%s\n%s\n",  beolvasott_cim, beolvasott_hely, beolvasott_megjegyzes, beolvasott_ido);

                    free(beolvasott_cim);
                    free(beolvasott_hely);
                    free(beolvasott_megjegyzes);
                    free(valasz_mentes_e);
                    free(megerosites);

                    printf("A bejegyzes fajlba mentese megtortent\n");
                    //fo_menupontok();
                    return;

                }
                else if(megerosites[0]== 'A' | megerosites[0]== 'a' & megerosites_meret<2)
                {
                    printf("Visszateres a menube mentes nelkul\n");

                    free(beolvasott_cim);
                    free(beolvasott_hely);
                    free(beolvasott_megjegyzes);
                    free(valasz_mentes_e);
                    free(megerosites);

                    //fo_menupontok();
                    return;
                }
                else
                {
                    printf("Ugy tunik nem jo betut nyomtal\n");
                }
            }
        }
        else
        {
            if(elso_while_e)
            {
                elso_while_e = false;
            }
            else
            {
                printf("Rossz betut irtal\n");
            }
        }
    }
}


void fajlba_mentes(char* beolvasott_cim, char* beolvasott_hely, char* beolvasott_megjegyzes, char* beolvasott_ido)
{

    // új bejegyzés mentése a fájl végére
    FILE *bejegyzes_tarolo;

    bejegyzes_tarolo = fopen("bejegyzesek.txt", "a");
    if (bejegyzes_tarolo==NULL)
        {
            perror("A fajl megnyitasa sikertelen volt");
        }
    else
        {
            fprintf(bejegyzes_tarolo, "cim: %s\*\nhely: %s\*\nmegjegyzes: %s\*\nido: %s\*\n", beolvasott_cim, beolvasott_hely , beolvasott_megjegyzes, beolvasott_ido);
            fprintf(bejegyzes_tarolo, "\n");
        }
    fclose(bejegyzes_tarolo);

    //innentől lesz a bejegyzés megfelelő helyre rakása:
    int fajl_hossza;
    char* szoveg = bejegyzesek_fajlbol_beolvasasa(&fajl_hossza);
    BEJEGYZES* eleje = make_structs_from_file_data(szoveg);

    BEJEGYZES* mozgo = eleje;

    while (mozgo->kovetkezo != NULL)
    {
        datum_parsolasa(mozgo);
        mozgo = mozgo->kovetkezo;
    }
    datum_parsolasa(mozgo);

    mozgo = eleje;
    int lancolt_lista_hossz= 0;
    while(mozgo->kovetkezo != NULL)
    {
        lancolt_lista_hossz++;
        mozgo = mozgo->kovetkezo;
    }
    lancolt_lista_hossz++;

    long long int sorszamok[lancolt_lista_hossz];
    int sorban_hely[lancolt_lista_hossz];
    mozgo = eleje;

    for(int k = 0; k<lancolt_lista_hossz; k++)
    {
        sorszamok[k]= mozgo->sort_number;
        //printf("%lld ", sorszamok[k]);
        sorban_hely[k] = k;
        //printf("%d\n", sorban_hely[k]);
        mozgo = mozgo->kovetkezo;
    }

    bubble_sort_sorrend(sorszamok, sorban_hely, lancolt_lista_hossz);

    /*for(int i= 0; i< lancolt_lista_hossz; i++)
    {
        printf("%lld %d \n", sorszamok[i], sorban_hely[i] );
    }*/

    //sorbarendezett bejegyzesek mentese
    bejegyzes_tarolo = fopen("bejegyzesek.txt", "w");
    if (bejegyzes_tarolo==NULL)
    {
        perror("A fajl megnyitasa sikertelen volt");
    }
    else
    {
        for(int k = 0; k< lancolt_lista_hossz; k++)
        {
            mozgo = eleje;
            for (int j = 0; j<sorban_hely[k]; j++)
            {
                mozgo = mozgo->kovetkezo;
            }

            fprintf(bejegyzes_tarolo, "%s\*%s\*%s\*%s\*", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
        }
    }
    fclose(bejegyzes_tarolo);
    struct_elemeket_felszabadit(eleje);
}

void bubble_sort_sorrend( long long int sorszamok[], int sorban_hely[], int lancolt_lista_hossz)
{
    for (int i =  lancolt_lista_hossz-1; i>0; i--)
    {
        for(int j= 0; j<i; j++)
        {
            if( sorszamok[j]> sorszamok[j+1])
            {
                long long int temp  = sorszamok[j];
                sorszamok[j] = sorszamok[j+1];
                sorszamok[j+1] = temp;

                long long int temp2 = sorban_hely[j];
                sorban_hely[j]= sorban_hely[j+1];
                sorban_hely[j+ 1] = temp2;
            }
        }
    }
}
char* teljes_ido_bekeres(char* beolvasott_ido)
{
    printf("Automatikus idomeghatarozas vagy sajat idopont megadasa?\n");
    printf("A) Automatikus ido\nB) Sajat ido megadasa");

    char *milyen_ido= (char*)malloc(1);
    milyen_ido[0]= 'z';
    int meret_milyen_ido;

    while(milyen_ido[0]!='A' && milyen_ido[0]!='a' && milyen_ido[0]!='B' && milyen_ido[0]!='b' )
    {
        //free(milyen_ido);
        milyen_ido = beolvas(&meret_milyen_ido);

        if (milyen_ido[0] == 'A' | milyen_ido[0]=='a' && meret_milyen_ido <2 )
        {
            printf("Automatikus ido kivalasztva\n");
            time_t most;
            time(&most);
            beolvasott_ido = ctime(&most);
        }
        else if (milyen_ido[0] == 'B' | milyen_ido[0]=='b' && meret_milyen_ido <2 )
        {
            printf("Ird be a napot! (Mon/Tue/Wed/Thu/Fri/Sat/Sun)\n");

            beolvasott_ido = napot_beolvas(beolvasott_ido);
            printf("A kapott nap: %s\n", beolvasott_ido);

            printf("Ird be a honapot! (Jan/Feb/Mar/Apr/May/Jun/Jul/Aug/Sep/Oct/Nov/Dec)\n");
            beolvasott_ido = honapot_beolvas(beolvasott_ido);
            printf("A kapott ido: %s \n", beolvasott_ido);

            printf("Ird be az evet!");
            bool szokoev_e = false;
            char* beolvasott_ev = ev_beolvasas(&szokoev_e);
            printf("Ird be, hogy hanyadika legyen!");
            char* beolvasott_nap =hanyadika_beolvas(szokoev_e, beolvasott_ido);

            strcat(beolvasott_ido, " ");
            strcat(beolvasott_ido, beolvasott_nap);
            strcat(beolvasott_ido, " ");
            strcat(beolvasott_ido, "00:00:00");
            strcat(beolvasott_ido, " ");
            strcat(beolvasott_ido, beolvasott_ev);
        }
        else
        {
            printf("Nem jo betut nyomtal, adj meg masikat!");
        }
    }
    return beolvasott_ido;
}

