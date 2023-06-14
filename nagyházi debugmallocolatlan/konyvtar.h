#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "debugmalloc.h"

#ifndef KONYVTAR_H
#define KONYVTAR_H

typedef struct BEJEGYZES
{
    char *cim;
    char *hely;
    char *megjegyzes;
    char *ido;
    char* raw_sort_number;
    long long int sort_number;
    struct BEJEGYZES *kovetkezo;
}BEJEGYZES;

void fo_menupontok(bool *ujranyit);
char* beolvas(int *hossz);
void bejegyzes_adatainak_beolvasasa(void);
void kilepes_mentessel_vagy_nelkule (char* beolvasott_cim, char* beolvasott_hely, char* beolvasott_megjegyzes, char* beolvasott_ido);
void fajlba_mentes(char* beolvasott_cim, char* beolvasott_hely, char* beolvasott_megjegyzes, char* beolvasott_ido);
char* bejegyzesek_fajlbol_beolvasasa(int *hossz);
BEJEGYZES* make_structs_from_file_data(char *szoveg);
void bejegyzesek_kilistazasa(void);
void struct_elemeket_kiir(BEJEGYZES* eleje);
void struct_elemeket_felszabadit(BEJEGYZES *eleje);
char* napot_beolvas(char *beolvasott_ido);
char* honapot_beolvas(char* beolvasott_ido);
char* ev_beolvasas(bool* szokoev_e);
char* hanyadika_beolvas(bool szokoev_e, char* beolvasott_ido);
void datum_parsolasa(BEJEGYZES* mozgo);
void bubble_sort_sorrend(long long int sorszamok[], int sorban_hely[], int lancolt_lista_hossz);
BEJEGYZES* kereses_cim_szerint(BEJEGYZES* eleje, char* keresett);
BEJEGYZES* kereses_hely_szerint(BEJEGYZES* eleje, char* keresett);
BEJEGYZES* kereses_megjegyzes_szerint(BEJEGYZES* eleje, char* keresett);
void kereses_ido_szerint_sajat_kif(BEJEGYZES* eleje, char* keresett);
void kereses_het_napjai_szerint(void);
void kereses_honapban_hanyadika_szerint(void);
char* honapot_beolvas_nem_kiegeszito(char* beolvasott_honap);
void kereses_honap_szerint(void);
void kereses_ev_szerint(void);
char* egyszeru_ev_beolvasas(void);
bool kereses_kiiras_cim_szerint(BEJEGYZES* eleje, char* keresett, FILE* talaltak);
char* keresett_bejegyzesek_fajlbol_beolvasasa(int *hossz);
int kereses_eredmenyek_listaz_sorszammal(BEJEGYZES* eleje);
BEJEGYZES* leptetes_kivalasztott_elemre(BEJEGYZES* eleje, int kivalasztott_sorszam);
void torles_vagy_szerkesztes(BEJEGYZES* kivalasztott);
char* teljes_ido_bekeres(char* beolvasott_ido);
bool kereses_kiiras_hely_szerint(BEJEGYZES* eleje, char* keresett, FILE* talaltak);
bool kereses_kiiras_megjegyzes_szerint(BEJEGYZES* eleje, char* keresett, FILE* talaltak);
bool kereses_kiiras_ido_szerint(BEJEGYZES* eleje, char* keresett, FILE* talaltak);
void maradek_mentese(BEJEGYZES* eleje);
void kiir_reszlet(BEJEGYZES* mozgo);

#endif KONYVTAR_H
