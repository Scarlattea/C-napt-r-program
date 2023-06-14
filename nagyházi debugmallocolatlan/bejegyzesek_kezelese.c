#include "konyvtar.h"

char* bejegyzesek_fajlbol_beolvasasa(int *hossz)
{
    FILE *bejegyzesek;
    bejegyzesek = fopen("bejegyzesek.txt", "r+");

    if (bejegyzesek != NULL)
    {
        char bekert;
        char *szoveg = (char*)malloc(0);
        int i=1;

        while ((fscanf(bejegyzesek, "%c", &bekert)==1) & (bekert != EOF))
        {
            szoveg = (char*)realloc(szoveg, i);
            szoveg[i-1]= bekert;
            i++;
        }
        szoveg = (char*)realloc(szoveg, i);
        szoveg[i-1]= '\0';
        *hossz = i-1;
        fclose(bejegyzesek);
        return szoveg;
    }
    else
    {
            printf("Nem sikerult a fajl beolvasasa, lehetseges, hogy meg nem letezik. \n");
            return NULL;
    }
}

BEJEGYZES* make_structs_from_file_data(char* szoveg)
{
     BEJEGYZES* elozo = NULL;
     BEJEGYZES* most;
     char *temp = (char*)malloc(0);
     int temp_meret=1;
     int elem_tipus=1; //1=cim; 2=hely; 3=megjegyzes; 4= ido;

     for (int i= 0; szoveg[i] != '\0' ; i++)
     {
        if(szoveg[i]!= '*') //amíg nincs csillag, addig olvasgatja be a betûket és berakja egy temp char*-ba
        {
            temp = (char*)realloc(temp, sizeof(char)*(temp_meret));
            temp[temp_meret-1]= szoveg[i];
            //printf("%c", temp[temp_meret-1]);
            temp_meret++;
        }
        if (szoveg[i]== '*') // ha elér egy csillaghoz, akkor az eddig begyûjtött betûket beteszi a soron következõ struct megfelelő elemébe
        {
            switch (elem_tipus)
            {
                case 1: most = (BEJEGYZES*)malloc(sizeof(BEJEGYZES));
                        most->kovetkezo = elozo; // balra haladva írom ki
                        most->cim = (char*)malloc(sizeof(char)*1);
                        for(int k=0; k<=(temp_meret-1); k++)
                        {   if(k<(temp_meret-1))
                            {
                                most->cim[k]= temp[k];
                                most->cim = (char*)realloc(most->cim, sizeof(char)*(k+2));
                            }
                            else
                            {
                                most->cim[k]= '\0';
                            }
                        }
                        //printf("%s\n", most->cim);
                        break;
                case 2: most->hely = (char*)malloc(sizeof(char)*1);
                        for(int k=0; k<=(temp_meret-1); k++)
                        {
                            if(k<(temp_meret-1))
                            {
                                most->hely[k]= temp[k];
                                most->hely = (char*)realloc(most->hely, sizeof(char)*(k+2));
                            }
                            else
                            {
                                most->hely[k]= '\0';
                            }
                        }
                        //printf("%s\n", most->hely);
                        break;
                case 3: most->megjegyzes = (char*)malloc(sizeof(char)*1);
                        for(int k=0; k<=(temp_meret-1); k++)
                        {
                            if(k<(temp_meret-1))
                            {
                                most->megjegyzes[k]= temp[k];
                                most->megjegyzes = (char*)realloc(most->megjegyzes, sizeof(char)*(k+2));
                            }
                            else
                            {
                                most->megjegyzes[k]= '\0';
                            }
                        }
                        //printf("%s\n", most->megjegyzes);
                        break;
                case 4: most->ido = (char*)malloc(sizeof(char)*1);
                        for(int k=0; k<=(temp_meret-1); k++)
                        {
                            if(k<(temp_meret-1))
                            {
                                most->ido[k]= temp[k];
                                most->ido = (char*)realloc(most->ido, sizeof(char)*(k+2));
                            }
                            else
                            {
                                most->ido[k]= '\0';
                            }
                        }
                        //printf("%s\n\n", most->ido);
                        elozo = most;
                        break;
                default:
                        break;
            }
            temp_meret = 1;

            if (elem_tipus==4)
            {
                elem_tipus = 1;
            }
            else
            {
                elem_tipus++;
            }
        }
    }
    free(szoveg);
    free(temp);
    // itt inkább átnevezem a pointert, amit eddig kezeltem, mert logikai szempontból a következő munkafolyamatokban jobb ha más a neve, itt viszont a "most" név segítette a logikus gondolkodást
    BEJEGYZES* eleje = most;
    return eleje;
}

void kiir_reszlet(BEJEGYZES* mozgo)
{

    int cim = strlen(mozgo->cim);
    int hely = strlen(mozgo->hely);
    int megjegyzes = strlen(mozgo->megjegyzes);
    int ido = strlen(mozgo->ido);
    if(mozgo->cim[cim] != '\n' | mozgo->hely[0] != '\n')
    {
        printf("%s\n", mozgo->cim);
    }
    else
    {
        printf("%s", mozgo->cim);
    }

    //printf("%s", mozgo->cim);

    if(mozgo->hely[hely] != '\n' | mozgo->megjegyzes[0] != '\n')
    {
        printf("%s\n", mozgo->hely);
    }
    else
    {
        printf("%s", mozgo->hely);
    }

    if(mozgo->megjegyzes[megjegyzes] != '\n' | mozgo->ido[0] != '\n')
    {
        printf("%s\n", mozgo->megjegyzes);
    }
    else
    {
        printf("%s", mozgo->megjegyzes);
    }

    /*if(mozgo->ido[0] != '\n')
    {
        printf("%s\n", mozgo->ido);
    }
    else
    {
        printf("%s", mozgo->ido);
    }*/
    printf("%s", mozgo->ido);
    printf("\n\n");
}

void struct_elemeket_kiir(BEJEGYZES* eleje)
{
    BEJEGYZES* mozgo = eleje;

    while (mozgo->kovetkezo !=NULL)
    {
        kiir_reszlet(mozgo);
        mozgo = mozgo->kovetkezo;
    }
    kiir_reszlet(mozgo);
}

void struct_elemeket_felszabadit(BEJEGYZES *eleje)
{
    BEJEGYZES *mozgo = eleje;

    while (mozgo->kovetkezo != NULL)
    {
        mozgo = mozgo->kovetkezo;
        if(eleje->cim != NULL)
        {
            free(eleje->cim);
        }
        if(eleje->hely != NULL)
        {
            free(eleje->hely);
        }
        if(eleje->megjegyzes != NULL)
        {
            free(eleje->megjegyzes);
        }
        if(eleje->ido != NULL)
        {
            free(eleje->ido);
        }
        free(eleje);
        eleje = mozgo;
    }
    free(mozgo);
}

// ez a függvény végül használaton kívül került
/*void bejegyzesek_kilistazasa(void)
{
    FILE *bejegyzesek;
    bejegyzesek = fopen("bejegyzesek.txt", "r+");

    char c;

    while((c = getc(bejegyzesek)) != EOF)
    {
        if (c != '*')
        {
            putchar(c);
        }
    }
   fclose(bejegyzesek);
}*/

BEJEGYZES* kereses_cim_szerint(BEJEGYZES* eleje, char* keresett)
{
    if (eleje == NULL)
    {
        return NULL;
    }

    BEJEGYZES* mozgo = eleje;
    int keresett_hossza = strlen(keresett);

    while (mozgo->kovetkezo != NULL)
    {
        char* osszehasonlit = strstr(mozgo->cim, keresett);
        if (osszehasonlit != NULL)
        {
            return mozgo;
        }
        mozgo = mozgo->kovetkezo;
    }
    char* osszehasonlit = strstr(mozgo->cim, keresett);
    if (osszehasonlit != NULL)
    {
        return mozgo;
    }
    else
    {
        return NULL;
    }
}

BEJEGYZES* kereses_hely_szerint(BEJEGYZES* eleje, char* keresett)
{
    if (eleje == NULL)
    {
        return NULL;
    }

    BEJEGYZES* mozgo = eleje;
    int keresett_hossza = strlen(keresett);

    while (mozgo->kovetkezo != NULL)
    {
        char* osszehasonlit = strstr(mozgo->hely, keresett);
        if (osszehasonlit != NULL)
        {
            return mozgo;
        }
        mozgo = mozgo->kovetkezo;
    }
    char* osszehasonlit = strstr(mozgo->hely, keresett);
    if (osszehasonlit != NULL)
    {
        return mozgo;
    }
    else
    {
        return NULL;
    }
}

BEJEGYZES* kereses_megjegyzes_szerint(BEJEGYZES* eleje, char* keresett)
{
    if (eleje == NULL)
    {
        return NULL;
    }

    BEJEGYZES* mozgo = eleje;
    int keresett_hossza = strlen(keresett);

    while (mozgo->kovetkezo != NULL)
    {
        char* osszehasonlit = strstr(mozgo->megjegyzes, keresett);
        if (osszehasonlit != NULL)
        {
            return mozgo;
        }
        mozgo = mozgo->kovetkezo;
    }
    char* osszehasonlit = strstr(mozgo->megjegyzes, keresett);
    if (osszehasonlit != NULL)
    {
        return mozgo;
    }
    else
    {
        return NULL;
    }
}

void kereses_ido_szerint_sajat_kif(BEJEGYZES* eleje, char* keresett)
{
    if (eleje == NULL)
    {
        return NULL;
    }

    BEJEGYZES* mozgo = eleje;
    bool van_talalt = false;

    while (mozgo->kovetkezo != NULL)
    {
        char* osszehasonlit = strstr(mozgo->ido, keresett);
        if (osszehasonlit != NULL)
        {
            van_talalt = true;
            printf("%s%s%s%s\n\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
        }
        mozgo = mozgo->kovetkezo;
    }
    char* osszehasonlit = strstr(mozgo->ido, keresett);
    if (osszehasonlit != NULL)
    {
        van_talalt = true;
        printf("%s%s%s%s\n\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
    }
    if (!van_talalt)
    {
        printf("Nincs a keresesnek megfelelo elem.\n");
    }
}
void kereses_het_napjai_szerint(void)
{
    printf("Kerlek add meg a keresett napot! (Mon\\Tue\\Wed\\Thu\\Fri\\Sat\\Sun)\n");
    char* beolvasott_nap = napot_beolvas(beolvasott_nap);
    printf("\n\n");
    int szoveg_hossz;
    char* szoveg = bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);
    BEJEGYZES* eleje = make_structs_from_file_data(szoveg);
    BEJEGYZES* mozgo = eleje;
    while(mozgo->kovetkezo != NULL)
    {
        char* talalt_e = strstr(mozgo->ido, beolvasott_nap);
        if (talalt_e != NULL)
        {
            printf("%s%s%s%s\n\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
        }
        mozgo = mozgo->kovetkezo;
    }
    char* talalt_e = strstr(mozgo->ido, beolvasott_nap);
    if (talalt_e != NULL)
    {
        printf("%s%s%s%s\n\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
    }
    //free(beolvasott_nap);
    struct_elemeket_felszabadit(eleje);
}
void kereses_honapban_hanyadika_szerint(void)
{
    printf("Kerlek add meg a keresett napot! (Hanyadika)");
    bool beolvasas_sikertelen = true;
    int beolvasott_hanyadika;
    while (beolvasas_sikertelen)
    {
        if(scanf("%d", &beolvasott_hanyadika)==1)
        {
            if(beolvasott_hanyadika>0 && beolvasott_hanyadika<32)
            {
                beolvasas_sikertelen = false;
                printf("A beolvasott nap (hanyadika) :%d \n", beolvasott_hanyadika);
            }
            else
            {
                    printf("A beirt szamnak 1 es 31 kozott kell lennie, kerlek adj meg egy masik szamot!\n");
            }
        }
        else
        {
            printf("A beolvasas sikertelen volt, probalkozz ujra!");
        }
    }
    int szoveg_hossz;
    char* szoveg = bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);
    BEJEGYZES* eleje = make_structs_from_file_data(szoveg);
    BEJEGYZES* mozgo = eleje;
    bool van_talalat = false;
    int idx = 0;

    while (mozgo->kovetkezo != NULL)
    {
        mozgo->raw_sort_number = (char*)malloc(sizeof(char)*(2+1));
        idx = 0;

        for (int j = 14; j<16; j++)
        {
            mozgo->raw_sort_number[idx] = mozgo->ido[j];
            idx++;
        }
        mozgo->raw_sort_number[idx] = '\0';
        char *ptr;
        mozgo->sort_number = strtoll(mozgo->raw_sort_number, &ptr, 10);
        if (mozgo->sort_number == beolvasott_hanyadika)
        {
            van_talalat = true;
            printf("%s%s%s%s\n\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
        }
        mozgo = mozgo->kovetkezo;
    }
    mozgo->raw_sort_number = (char*)malloc(sizeof(char)*(2+1));
    for (int j = 14; j<16; j++)
    {
        mozgo->raw_sort_number[idx] = mozgo->ido[j];
        idx++;
    }
    mozgo->raw_sort_number[idx] = '\0';
    char *ptr;
    mozgo->sort_number = strtoll(mozgo->raw_sort_number, &ptr, 10);
    if (mozgo->sort_number == beolvasott_hanyadika)
    {
        van_talalat = true;
        printf("%s%s%s%s\n\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
    }
    if (!van_talalat)
    {
        printf("Nincs a keresesnek megfelelo talalat\n");
    }
    struct_elemeket_felszabadit(eleje);
}
void kereses_honap_szerint(void)
{
    printf("Kerlek add meg, melyik honap bejegyzeseit keresed!\n");
    char* beolvasott_honap = honapot_beolvas_nem_kiegeszito(beolvasott_honap);
    printf("A keresett honap: %s \n", beolvasott_honap);

    int szoveg_hossz;
    char* szoveg = bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);
    BEJEGYZES* eleje = make_structs_from_file_data(szoveg);
    BEJEGYZES* mozgo = eleje;
    char* talalt;
    bool van_talalat = false;

    while (mozgo->kovetkezo != NULL)
    {
        talalt = strstr(mozgo->ido, beolvasott_honap);
        if(talalt != NULL)
        {
            van_talalat = true;
            printf("%s%s%s%s\n\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
        }
        mozgo= mozgo->kovetkezo;
    }
    talalt = strstr(mozgo->ido, beolvasott_honap);
    if(talalt != NULL)
    {
        van_talalat = true;
        printf("%s%s%s%s\n\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
    }
    if(!van_talalat)
    {
        printf("Nincs a keresesnek megfelelo elem.\n");
    }
    struct_elemeket_felszabadit(eleje);
}

char* honapot_beolvas_nem_kiegeszito(char* beolvasott_honap)
{
     char honapok[24][4] =
    {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
        "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"
    };
    int honap_hossz;
    char* honap = beolvas(&honap_hossz);

    for (int i=0; i<24; i++)
    {
        int egyeznek_e = strcmp(honap, honapok[i]);
        //printf("%d", egyeznek_e);
        if (egyeznek_e == 0)
        {
            honap[0]= toupper(honap[0]);
            beolvasott_honap = honap;
            return beolvasott_honap;
        }
    }
    printf("Helytelen megadas, kerlek probald ujra!");
    return honapot_beolvas_nem_kiegeszito(beolvasott_honap);
}
void kereses_ev_szerint(void)
{
    printf("Kerlek add meg a keresett evszamot!\n");
    char* beolvasott_ev = egyszeru_ev_beolvasas();
    int szoveg_hossza;
    char* szoveg = bejegyzesek_fajlbol_beolvasasa(&szoveg_hossza);
    BEJEGYZES* eleje = make_structs_from_file_data(szoveg);
    BEJEGYZES* mozgo = eleje;
    bool van_talalat = false;

    while (mozgo->kovetkezo != NULL)
    {
        char* talalt = strstr(mozgo->ido, beolvasott_ev);
        if (talalt != NULL)
        {
          van_talalat =true;
          printf("%s%s%s%s\n\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
        }
        mozgo = mozgo->kovetkezo;
    }
    char* talalt = strstr(mozgo->ido, beolvasott_ev);
    if (talalt != NULL)
    {
        van_talalat =true;
        printf("%s%s%s%s\n\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
    }
    if(!van_talalat)
    {
        printf("Nincs talalat az adott keresesre. ");
    }
    struct_elemeket_felszabadit(eleje);
}

char* egyszeru_ev_beolvasas(void)
{
    int ev;
    if(scanf("%d", &ev) == 1)
    {
       if (ev<0)
        {
            printf("Az evszam nem lehet negativ, kerlek adj meg masik szamot!\n");
            return egyszeru_ev_beolvasas();
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
    else
    {
        printf("Az ev beolvasasa sikertelen volt. Probalkozz ujra!");
        return egyszeru_ev_beolvasas();
    }
}
