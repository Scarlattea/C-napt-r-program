#include "konyvtar.h"

bool kereses_kiiras_cim_szerint(BEJEGYZES* eleje, char* keresett, FILE* talaltak)
{
    if (eleje == NULL)
    {
        return NULL;
    }

    BEJEGYZES* mozgo = eleje;
    int keresett_hossza = strlen(keresett);
    bool van_talalt = false;

    while (mozgo->kovetkezo != NULL)
    {
        char* osszehasonlit = strstr(mozgo->cim, keresett);
        if (osszehasonlit != NULL)
        {
            van_talalt = true;
            fprintf(talaltak, "%s\*%s\*%s\*%s\*\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
        }
        mozgo = mozgo->kovetkezo;
    }
    char* osszehasonlit = strstr(mozgo->cim, keresett);
    if (osszehasonlit != NULL)
    {
        van_talalt = true;
        fprintf(talaltak, "%s\*%s\*%s\*%s\*\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
    }
    if (!van_talalt)
    {
        printf("Nincs a keresesnek megfelelo elem.");
    }
    return van_talalt;
}

bool kereses_kiiras_hely_szerint(BEJEGYZES* eleje, char* keresett, FILE* talaltak)
{

    if (eleje == NULL)
    {
        return NULL;
    }

    BEJEGYZES* mozgo = eleje;
    int keresett_hossza = strlen(keresett);
    bool van_talalt = false;

    while (mozgo->kovetkezo != NULL)
    {
        char* osszehasonlit = strstr(mozgo->hely, keresett);
        if (osszehasonlit != NULL)
        {
            van_talalt = true;
            fprintf(talaltak, "%s\*%s\*%s\*%s\*\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
        }
        mozgo = mozgo->kovetkezo;
    }
    char* osszehasonlit = strstr(mozgo->hely, keresett);
    if (osszehasonlit != NULL)
    {
        van_talalt = true;
        fprintf(talaltak, "%s\*%s\*%s\*%s\*\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
    }
    if (!van_talalt)
    {
        printf("Nincs a keresesnek megfelelo elem.");
    }
    return van_talalt;
}

bool kereses_kiiras_megjegyzes_szerint(BEJEGYZES* eleje, char* keresett, FILE* talaltak)
{
    if (eleje == NULL)
    {
        return NULL;
    }

    BEJEGYZES* mozgo = eleje;
    int keresett_hossza = strlen(keresett);
    bool van_talalt = false;

    while (mozgo->kovetkezo != NULL)
    {
        char* osszehasonlit = strstr(mozgo->megjegyzes, keresett);
        if (osszehasonlit != NULL)
        {
            van_talalt = true;
            fprintf(talaltak, "%s\*%s\*%s\*%s\*\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
        }
        mozgo = mozgo->kovetkezo;
    }
    char* osszehasonlit = strstr(mozgo->megjegyzes, keresett);
    if (osszehasonlit != NULL)
    {
        van_talalt = true;
        fprintf(talaltak, "%s\*%s\*%s\*%s\*\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
    }
    if (!van_talalt)
    {
        printf("Nincs a keresesnek megfelelo elem.");
    }
    return van_talalt;
}

bool kereses_kiiras_ido_szerint(BEJEGYZES* eleje, char* keresett, FILE* talaltak)
{
     if (eleje == NULL)
    {
        return NULL;
    }

    BEJEGYZES* mozgo = eleje;
    int keresett_hossza = strlen(keresett);
    bool van_talalt = false;

    while (mozgo->kovetkezo != NULL)
    {
        char* osszehasonlit = strstr(mozgo->ido, keresett);
        if (osszehasonlit != NULL)
        {
            van_talalt = true;
            fprintf(talaltak, "%s\*%s\*%s\*%s\*\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
        }
        mozgo = mozgo->kovetkezo;
    }
    char* osszehasonlit = strstr(mozgo->ido, keresett);
    if (osszehasonlit != NULL)
    {
        van_talalt = true;
        fprintf(talaltak, "%s\*%s\*%s\*%s\*\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
    }
    if (!van_talalt)
    {
        printf("Nincs a keresesnek megfelelo elem.");
    }
    return van_talalt;
}

char* keresett_bejegyzesek_fajlbol_beolvasasa(int *hossz)
{
    FILE *bejegyzesek;
    bejegyzesek = fopen("kereses_eredmenyek.txt", "r+");

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

int kereses_eredmenyek_listaz_sorszammal(BEJEGYZES* eleje)
{
    int sorszam = 0;
    BEJEGYZES* mozgo = eleje;

    while (mozgo->kovetkezo !=NULL)
    {
        printf("(%d) \n", sorszam);
        printf("%s%s%s%s\n\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
        sorszam++;
        mozgo = mozgo->kovetkezo;
    }
    printf("(%d)\n", sorszam);
    printf("%s%s%s%s\n\n", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
    return sorszam;
}
BEJEGYZES* leptetes_kivalasztott_elemre(BEJEGYZES* eleje, int kivalasztott_sorszam)
{
     BEJEGYZES* mozgo = eleje;
    while (kivalasztott_sorszam != 0)
    {
        mozgo = mozgo->kovetkezo;
        kivalasztott_sorszam--;
    }
    return mozgo;
}
void torles_vagy_szerkesztes(BEJEGYZES* kivalasztott)
{
    printf("Valaszd ki, mit szeretnel tenni: \nA) Bejegyzes torlese\nB) Bejegyzes szerkesztese\n");

    char* valasz_torol_szerkeszt = (char*)malloc(1);
    valasz_torol_szerkeszt[0] = 'z';
    int valasz_t_sz;
    bool elso_eset = true;
    bool valasztast_befejez = false;

    while (!valasztast_befejez)
    {
        free(valasz_torol_szerkeszt);
        valasz_torol_szerkeszt = beolvas(&valasz_t_sz);
        // bejegyzes torlese
        if(valasz_torol_szerkeszt[0] == 'A'|valasz_torol_szerkeszt[0] == 'a' && valasz_t_sz < 2)
        {
            free(valasz_torol_szerkeszt);
            printf("Biztos torolni szeretned a bejegyzest?\nA) Tenyleg torolni szeretnem.\nB) Inkabb megse\n");

            char* biztos_e = (char*)malloc(1);
            biztos_e[0] = 'z';
            bool ciklus_elso = true;
            int hossz_biztos_e;
            bool kilep_e = false;

            while (!kilep_e)
            {
                //free(biztos_e);
                biztos_e = beolvas(&hossz_biztos_e);
                // bejegyzes torlese
                if(biztos_e[0] == 'a' | biztos_e[0] == 'A' && hossz_biztos_e <2)
                {
                    //printf("Hmmm");
                    free(biztos_e);
                    int szoveg_hossz;
                    char* szoveg = bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);
                    BEJEGYZES* eleje = make_structs_from_file_data(szoveg);
                    BEJEGYZES* mozgo = eleje;
                    bool elso = true;

                    //strcat(kivalasztott->cim, "\n");
                    //kivalasztott->cim[0] = 'x';

                    int i = 0;

                    if(kivalasztott->cim[0] == '\n')
                    {
                        while (kivalasztott->cim[i] != '\0')
                        {
                            kivalasztott->cim[i] = kivalasztott->cim[i+1];
                            i++;
                        }
                    }

                    while (mozgo->kovetkezo != NULL)
                    {
                        if (elso)
                        {
                            elso = false;
                            int cim = strcmp(mozgo->cim, kivalasztott->cim);
                            //printf("?%s%s?", mozgo->cim, kivalasztott->cim);
                            //printf("cim osszehasonlitas eredmenye: %d\n", cim);
                            int mozgo_cim_hossz = strlen(mozgo->cim);
                            int kivalasztott_cim_hossz = strlen(kivalasztott->cim);
                            //printf("egyik: %d masik: %d", mozgo_cim_hossz, kivalasztott_cim_hossz);

                            int hely = strcmp(mozgo->hely, kivalasztott->hely);
                            int megjegyzes = strcmp(mozgo->megjegyzes, kivalasztott->megjegyzes);
                            int ido = strcmp(mozgo->ido, kivalasztott->ido);

                            if( cim == 0 && hely ==0 && megjegyzes == 0 && ido == 0)
                            {
                                eleje = mozgo->kovetkezo;
                                free(mozgo);
                                maradek_mentese(eleje);
                                //printf("az if mukodik");
                                struct_elemeket_felszabadit(eleje);
                                return;
                            }
                        }
                        int cim = strcmp(mozgo->kovetkezo->cim, kivalasztott->cim);
                        int hely = strcmp(mozgo->kovetkezo->hely, kivalasztott->hely);
                        int megjegyzes = strcmp(mozgo->kovetkezo->megjegyzes, kivalasztott->megjegyzes);
                        int ido = strcmp(mozgo->kovetkezo->ido, kivalasztott->ido);

                        int mozgo_cim_hossz = strlen(mozgo->cim);
                        int kivalasztott_cim_hossz = strlen(kivalasztott->cim);
                        //printf("egyik: %d masik: %d\n", mozgo_cim_hossz, kivalasztott_cim_hossz);

                        if( cim == 0 && hely ==0 && megjegyzes == 0 && ido == 0)
                        {
                            BEJEGYZES* temp = mozgo->kovetkezo;
                            mozgo->kovetkezo = mozgo->kovetkezo->kovetkezo;
                            free(temp);
                            maradek_mentese(eleje);
                            struct_elemeket_felszabadit(eleje);
                            return;
                        }
                        else
                        {
                            mozgo = mozgo->kovetkezo;
                        }
                    }

                    int cim = strcmp(mozgo->kovetkezo->cim, kivalasztott->cim);
                    int hely = strcmp(mozgo->kovetkezo->hely, kivalasztott->hely);
                    int megjegyzes = strcmp(mozgo->kovetkezo->megjegyzes, kivalasztott->megjegyzes);
                    int ido = strcmp(mozgo->kovetkezo->ido, kivalasztott->ido);

                    int mozgo_cim_hossz = strlen(mozgo->cim);
                    int kivalasztott_cim_hossz = strlen(kivalasztott->cim);
                    //printf("egyik: %d masik: %d\n", mozgo_cim_hossz, kivalasztott_cim_hossz);

                    if( cim == 0 && hely ==0 && megjegyzes == 0 && ido == 0)
                    {
                        BEJEGYZES* temp = mozgo->kovetkezo;
                        mozgo->kovetkezo = mozgo->kovetkezo->kovetkezo;
                        free(temp);
                        maradek_mentese(eleje);
                        struct_elemeket_felszabadit(eleje);
                        printf("A bejegyzes torlese megtortent.\n\n");
                        return;
                    }

                    kilep_e = true;
                    valasztast_befejez = true;

                }
                else if(biztos_e[0] == 'B' | biztos_e[0] == 'b' && hossz_biztos_e <2 )
                {
                    printf("A bejegyzes nem kerult torlesre.\n");
                    free(biztos_e);
                    kilep_e = true;
                }
                else
                {   if(ciklus_elso)
                    {
                        ciklus_elso = false;
                    }
                    else
                    {
                        printf("Nem jo betut irtal, kerlek probalkozz ujra!");
                    }
                }
            }
            valasztast_befejez = true;
        }
        // bejegyzes szerkesztese:
        else if(valasz_torol_szerkeszt[0]== 'B' | valasz_torol_szerkeszt[0]== 'b' && valasz_t_sz<2)
        {
            free(valasz_torol_szerkeszt);

            int szoveg_hossz;
            char* szoveg = bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);
            BEJEGYZES* eleje = make_structs_from_file_data(szoveg);
            BEJEGYZES* mozgo = eleje;
            bool elso = true;

            int i = 0;

            if(kivalasztott->cim[0] == '\n')
            {
                while (kivalasztott->cim[i] != '\0')
                {
                    kivalasztott->cim[i] = kivalasztott->cim[i+1];
                    i++;
                }
            }

            while (mozgo != NULL)
            {

                while(mozgo->cim[0] == '\n')
                {
                    int j =0;
                    while (mozgo->cim[j] != '\0')
                    {
                        mozgo->cim[j] = mozgo->cim[j+1];
                        j++;
                    }
                }
                elso = false;
                int cim = strcmp(mozgo->cim, kivalasztott->cim);
                    //printf("?%s%s?", mozgo->cim, kivalasztott->cim);
                    //printf("cim osszehasonlitas eredmenye: %d\n", cim);
                int mozgo_cim_hossz = strlen(mozgo->cim);
                int kivalasztott_cim_hossz = strlen(kivalasztott->cim);
                //printf("egyik: %d masik: %d", mozgo_cim_hossz, kivalasztott_cim_hossz);

                int hely = strcmp(mozgo->hely, kivalasztott->hely);
                int megjegyzes = strcmp(mozgo->megjegyzes, kivalasztott->megjegyzes);
                int ido = strcmp(mozgo->ido, kivalasztott->ido);

                if( cim == 0 && hely ==0 && megjegyzes == 0 && ido == 0)
                {
                    printf("Mit szeretnel szerkeszteni?\nA)Cim\nB)Hely\nC)Megjegyzes\nD)Ido\n");
                    bool kerdes_befejez = false;
                    char* melyiket_szerkeszt = (char*)malloc(1);
                    melyiket_szerkeszt[0] ='z';
                    int melyiket_szerkeszt_hossz;

                    while (!kerdes_befejez)
                    {
                        free(melyiket_szerkeszt);
                        melyiket_szerkeszt = beolvas(&melyiket_szerkeszt_hossz);
                        // cim szerkesztese
                        if(melyiket_szerkeszt[0] == 'A' | melyiket_szerkeszt[0] == 'a')
                        {
                            free(melyiket_szerkeszt);
                            printf("Add meg az uj cimet!\n");
                            free(mozgo->cim);
                            int mozgo_cim_hossz_temp;

                            char* temp = beolvas(&mozgo_cim_hossz_temp);
                            mozgo->cim = (char*) malloc(sizeof(char)*(6+mozgo_cim_hossz_temp));
                            strcpy(mozgo->cim, "cim: ");
                            strcat(mozgo->cim, temp);

                            maradek_mentese(eleje);
                            struct_elemeket_felszabadit(eleje);
                            kerdes_befejez = true;
                        }
                        //hely szerkesztese
                        else if(melyiket_szerkeszt[0] == 'B' | melyiket_szerkeszt[0] == 'b' )
                        {
                            free(melyiket_szerkeszt);
                            printf("Add meg az uj helyet!\n");
                            free(mozgo->hely);
                            int mozgo_hely_hossz_temp;

                            char* temp = beolvas(&mozgo_hely_hossz_temp);
                            mozgo->hely = (char*) malloc(sizeof(char)*(7+mozgo_hely_hossz_temp));
                            strcpy(mozgo->hely, "hely: ");
                            strcat(mozgo->hely, temp);

                            //mozgo->hely = beolvas(&mozgo_hely_hossz_temp);
                            maradek_mentese(eleje);
                            struct_elemeket_felszabadit(eleje);
                            kerdes_befejez = true;
                        }
                        //megjegyzes szerkesztese
                        else if(melyiket_szerkeszt[0] == 'C' | melyiket_szerkeszt[0] == 'c' )
                        {
                            free(melyiket_szerkeszt);
                            printf("Add meg az uj megjegyzest!\n");
                            free(mozgo->megjegyzes);
                            int mozgo_megjegyzes_hossz_temp;

                            char* temp = beolvas(&mozgo_megjegyzes_hossz_temp);
                            mozgo->megjegyzes = (char*) malloc(sizeof(char)*(13+mozgo_megjegyzes_hossz_temp));
                            strcpy(mozgo->megjegyzes, "megjegyzes: ");
                            strcat(mozgo->megjegyzes, temp);

                            //mozgo->megjegyzes = beolvas(&mozgo_megjegyzes_hossz_temp);
                            maradek_mentese(eleje);
                            struct_elemeket_felszabadit(eleje);
                            kerdes_befejez = true;
                        }
                        //ido szerkesztese
                        else if(melyiket_szerkeszt[0] == 'D' | melyiket_szerkeszt[0] == 'd' )
                        {
                            free(melyiket_szerkeszt);
                            printf("Az ido szerkesztese kovetkezik. Kerlek valassz a menupontokbol! \n");

                            char* temp = teljes_ido_bekeres(mozgo->ido);
                            int temp_hossz = strlen(temp);
                            mozgo->ido = (char*)malloc(sizeof(char)* (temp_hossz+6));
                            strcpy(mozgo->ido, "ido: ");
                            strcat(mozgo->ido, temp);

                            maradek_mentese(eleje);
                            struct_elemeket_felszabadit(eleje);
                            kerdes_befejez = true;
                        }
                        else
                        {
                            printf("Nem jo betut irtal be menupontnak, kerlek probald ujra!");
                        }

                    }
                    return;
                }
                else
                {
                    mozgo = mozgo->kovetkezo;
                }
            }
            //kilep_e = true;
            valasztast_befejez = true;
        }
        else
        {
            if(elso_eset)
            {
                elso_eset = false;
            }
            else
            {
                printf("Nem jo betut irtal be, kerlek probalkozz ujra!\n");
            }
        }
    }
}
void maradek_mentese(BEJEGYZES* eleje)
{
    FILE* maradek;
    BEJEGYZES* mozgo = eleje;

    maradek = fopen("bejegyzesek.txt", "w");
    if (maradek==NULL)
    {
        perror("A fajl megnyitasa sikertelen volt");
    }
    else
    {
        while (mozgo->kovetkezo != NULL)
        {
            fprintf(maradek, "%s\*%s\*%s\*%s\*", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
            mozgo = mozgo->kovetkezo;
        }
        fprintf(maradek, "%s\*%s\*%s\*%s\*", mozgo->cim, mozgo->hely, mozgo->megjegyzes, mozgo->ido);
    }
    printf("Kesz van\n");
    fclose(maradek);
    //struct_elemeket_felszabadit(eleje);
}
