    #include "konyvtar.h"

    void fo_menupontok(bool *ujranyit)
    {
        printf("\n\nValaszd ki az alabbiak kozul, hogy mit szeretnel tenni:\n\n");
        printf("A): Uj bejegyzes \n");
        printf("B): Meglevo bejegyzesek kezelese\n");
        printf("C): Kilepes\nValasztas: ");

        //ennek már itt kell helyet foglalnia a memóriában, mert a while feltételében már az elemeit vizsgáljuk
        //értéket is kell adni annak az elemnek,amit vizsgálunk, nehogy pont olyan memóriaszemétbe fussunk bele, ami elrontja a programot
        char *valasz= (char*)malloc(1);
        valasz[0]= 'z';
        int beolvasott_hossz;
        bool elso_while = true;

        while (valasz[0] != 'A' |valasz[0] != 'a' |valasz[0] != 'B' | valasz[0] != 'b'|valasz[0] != 'c' | valasz[0] != 'C')
        {
            elso_while = false;
            //ide kell egy free, mert ha csak valamelyik válasz esetén használjuk a free-t, akkor az elsõ foglalás benne marad a memóriában (20.sor, 21. sor)
            free(valasz);
            valasz = beolvas(&beolvasott_hossz);

            // uj bejegyzes
            if((valasz[0] == 'A' | valasz[0] == 'a')& beolvasott_hossz<2 )
            {
                //char*valasz itt már ellátta feladatát, fel lehet szabadítani. késõbbiekben is hasonlóan helyeztem el a döntéseket jelzõ char*-ok felszabadításait
                free(valasz);

                // innentõl kezdve a program az uj_bejegyzes.c-ben dolgozik tovább egy ideig
                bejegyzes_adatainak_beolvasasa();
                return;
            }

            // meglevo bejegyzesek kezelese
            else if ((valasz[0] == 'B' | valasz[0] == 'b')& beolvasott_hossz<2 )
            {
                elso_while = false;
                free(valasz);
                printf("Mit szeretnel tenni?\n");
                printf("A) Bejegyzesek kilistazasa\n");
                printf("B) Bejegyzes keresese (csak olvasas)\n");
                printf("C) Bejegyzes keresese torlesre vagy szerkesztesre\n");

                char *valasz_bejegyzest_kezel= (char*)malloc(1);
                valasz_bejegyzest_kezel[0]= 'z';
                int meret_bejegyzest_kezel;

                while (valasz_bejegyzest_kezel[0]!='A'|valasz_bejegyzest_kezel[0]!='a'|valasz_bejegyzest_kezel[0]!='B'| valasz_bejegyzest_kezel[0]!='b' |valasz_bejegyzest_kezel[0]!='C'| valasz_bejegyzest_kezel[0]!='c')
                {
                    free(valasz_bejegyzest_kezel);
                    valasz_bejegyzest_kezel= beolvas(&meret_bejegyzest_kezel);

                    //bejegyzesek kilistazasa
                    if(valasz_bejegyzest_kezel[0]== 'A' | valasz_bejegyzest_kezel[0]=='a' & meret_bejegyzest_kezel<2)
                    {
                        free(valasz_bejegyzest_kezel);
                        int kilistaz_hossz;
                        char* kilistaz = bejegyzesek_fajlbol_beolvasasa(&kilistaz_hossz);
                        if( kilistaz != NULL)
                        {
                            BEJEGYZES *kilistazo_lanc = make_structs_from_file_data(kilistaz);
                            struct_elemeket_kiir(kilistazo_lanc);
                        }

                        return;
                    }
                    //Bejegyzes keresese (csak olvasas)
                    else if(valasz_bejegyzest_kezel[0]== 'B' | valasz_bejegyzest_kezel[0]=='b' & meret_bejegyzest_kezel<2)
                    {
                        //printf("Ez mukodik");
                        free(valasz_bejegyzest_kezel);
                        int hossz;

                        char* szoveg = bejegyzesek_fajlbol_beolvasasa(&hossz);

                        if( szoveg != NULL)
                        {
                            BEJEGYZES* eleje = make_structs_from_file_data(szoveg);

                            printf("Mi alapjan keressunk?\nA) Cim\nB) Hely\nC) Megjegyzes\nD) Ido\n");
                            char* miben_keress = (char*)malloc(sizeof(char)*1);
                            miben_keress[0]= 'z';
                            int meret_miben_keress;

                            while (miben_keress[0]!='A'&& miben_keress[0]!='a'&& miben_keress[0]!='B'&& miben_keress[0]!='b' && miben_keress[0]!='C'&& miben_keress[0]!='c' && miben_keress[0]!='D' && miben_keress[0]!='d')
                            {

                                free(miben_keress);
                                miben_keress = beolvas(&meret_miben_keress);

                                if(miben_keress[0]== 'A' | miben_keress[0]== 'a' && meret_miben_keress <2)
                                {
                                    //kereses cim szerint
                                    free(miben_keress);
                                    printf("Mi legyen a keresett cim?\n");
                                    int keresett_cim_hossza;
                                    char* keresett_cim = beolvas(&keresett_cim_hossza);
                                    BEJEGYZES* talalt = kereses_cim_szerint(eleje, keresett_cim);
                                    if(talalt == NULL)
                                    {
                                        printf("Nincs  a keresesnek megfelelo elem\n");
                                        free(keresett_cim);
                                        struct_elemeket_felszabadit(eleje);
                                        //free(talalt);
                                        return;
                                    }
                                    printf("A kereses eredmenye:\n");
                                    // ez nem vizsgálja az utolsó elemet
                                    while (talalt->kovetkezo != NULL)
                                    {
                                        printf("%s %s %s %s \n\n", talalt->cim, talalt->hely, talalt->megjegyzes, talalt->ido);
                                        talalt = kereses_cim_szerint(talalt->kovetkezo, keresett_cim);
                                        if (talalt == NULL)
                                        {
                                            free(keresett_cim);
                                            struct_elemeket_felszabadit(eleje);
                                            //free(talalt);
                                            return;
                                        }
                                    }
                                    //ez végzi az utolso elem elemzését
                                    if (talalt->kovetkezo == NULL)
                                    {
                                        talalt = kereses_cim_szerint(talalt, keresett_cim);
                                        if(talalt != NULL)
                                        {
                                            printf("%s %s %s %s\n\n", talalt->cim, talalt->hely, talalt->megjegyzes, talalt->ido);
                                        }
                                    }

                                    free(keresett_cim);
                                    struct_elemeket_felszabadit(eleje);
                                    //free(talalt);
                                    return;
                                }
                                //kereses hely szerint
                                else if (miben_keress[0] =='B' | miben_keress[0] == 'b' && meret_miben_keress < 3)
                                {
                                    free(miben_keress);
                                    printf("Mi legyen a keresett hely?\n");
                                    int keresett_hely_hossza;
                                    char* keresett_hely = beolvas(&keresett_hely_hossza);
                                    BEJEGYZES* talalt = kereses_hely_szerint(eleje, keresett_hely);
                                    if(talalt == NULL)
                                    {
                                        printf("Nincs  a keresesnek megfelelo elem\n");
                                        free(keresett_hely);
                                        free(eleje);
                                        free(talalt);
                                        return;
                                    }
                                    printf("A kereses eredmenye:\n");
                                    // ez nem vizsgálja az utolsó elemet
                                    while (talalt->kovetkezo != NULL)
                                    {
                                        printf("%s %s %s %s", talalt->cim, talalt->hely, talalt->megjegyzes, talalt->ido);
                                        talalt = kereses_hely_szerint(talalt->kovetkezo, keresett_hely);
                                        if (talalt == NULL)
                                        {
                                            free(keresett_hely);
                                            free(eleje);
                                            free(talalt);
                                            return;
                                        }
                                    }
                                    //ez végzi az utolso elem elemzését
                                    if (talalt->kovetkezo == NULL)
                                    {
                                        talalt = kereses_hely_szerint(talalt, keresett_hely);
                                        if(talalt != NULL)
                                        {
                                            printf("%s %s %s %s", talalt->cim, talalt->hely, talalt->megjegyzes, talalt->ido);
                                        }
                                    }

                                    free(keresett_hely);
                                    free(eleje);
                                    free(talalt);
                                    return;
                                }
                                //kereses megjegyzes szerint:
                                else if (miben_keress[0] =='C' | miben_keress[0] == 'c' && meret_miben_keress < 2)
                                {
                                    free(miben_keress);
                                    printf("Mi legyen a keresett megjegyzes?\n");
                                    int keresett_megjegyzes_hossza;
                                    char* keresett_megjegyzes = beolvas(&keresett_megjegyzes_hossza);
                                    BEJEGYZES* talalt = kereses_megjegyzes_szerint(eleje, keresett_megjegyzes);
                                    if(talalt == NULL)
                                    {
                                        printf("Nincs  a keresesnek megfelelo elem\n");
                                        free(keresett_megjegyzes);
                                        free(eleje);
                                        free(talalt);
                                        return;
                                    }
                                    printf("A kereses eredmenye:\n");
                                    // ez nem vizsgálja az utolsó elemet
                                    while (talalt->kovetkezo != NULL)
                                    {
                                        printf("%s %s %s %s", talalt->cim, talalt->hely, talalt->megjegyzes, talalt->ido);
                                        talalt = kereses_megjegyzes_szerint(talalt->kovetkezo, keresett_megjegyzes);
                                        if (talalt == NULL)
                                        {
                                            free(keresett_megjegyzes);
                                            free(eleje);
                                            free(talalt);
                                            return;
                                        }
                                    }
                                    //ez végzi az utolso elem elemzését
                                    if (talalt->kovetkezo == NULL)
                                    {
                                        talalt = kereses_megjegyzes_szerint(talalt, keresett_megjegyzes);
                                        if(talalt != NULL)
                                        {
                                            printf("%s %s %s %s", talalt->cim, talalt->hely, talalt->megjegyzes, talalt->ido);
                                        }
                                    }

                                    free(keresett_megjegyzes);
                                    free(eleje);
                                    free(talalt);
                                    return;
                                }
                                //kereses ido szerint
                                else if (miben_keress[0] =='D' | miben_keress[0] == 'd' && meret_miben_keress < 2)
                                {
                                    //printf("Ez is mukodik.");
                                    printf("Milyen idonagysagrendben szeretnel keresni? \nA) Het napjai(Mon\\Tue\\Wed\\Thu\\Fri\\Sat\\Sun)\nB) Honapban hanyadik nap\nC) Honap szerint (Jan\\Feb\\Mar\\Apr\\May\\Jun\\Jul\\Aug\\Sep\\Oct\\Nov\\Dec)\nD) Ev szerint\nE) Egyedi kifejezes\n");

                                    char* ido_kereses = (char*)malloc(1);
                                    ido_kereses[0]= 'z';

                                    while (ido_kereses[0]!= 'A' && ido_kereses[0]!= 'a'&& ido_kereses[0]!= 'b'&& ido_kereses[0]!= 'B'&& ido_kereses[0]!= 'c'&& ido_kereses[0]!= 'C'&& ido_kereses[0]!= 'D'&& ido_kereses[0]!= 'd'&& ido_kereses[0]!= 'E'&& ido_kereses[0]!= 'e')
                                    {
                                        free(ido_kereses);
                                        int ido_kereses_hossz;
                                        ido_kereses = beolvas(&ido_kereses_hossz);

                                        //kereses a het napjai szerint
                                       if(ido_kereses[0]== 'A'|ido_kereses[0]== 'a')
                                       {
                                            free(ido_kereses);
                                            kereses_het_napjai_szerint();
                                            return;
                                       }
                                       //kereses->honapban hanyadik nap
                                       else if(ido_kereses[0]== 'B'|ido_kereses[0]== 'b')
                                       {
                                            free(ido_kereses);
                                            kereses_honapban_hanyadika_szerint();
                                            return;
                                       }
                                       //honap szerint
                                       else if(ido_kereses[0]== 'C'|ido_kereses[0]== 'c')
                                       {
                                            free(ido_kereses);
                                            kereses_honap_szerint();
                                            return;
                                       }
                                       //ev szerint
                                       else if(ido_kereses[0]== 'D'|ido_kereses[0]== 'd')
                                       {
                                            free(ido_kereses);
                                            kereses_ev_szerint();
                                            return;

                                       }
                                       //sajat kifejezes
                                       else if(ido_kereses[0]== 'E'|ido_kereses[0]== 'e')
                                       {
                                            free(ido_kereses);
                                            int szoveg_hossz;
                                            char* szoveg = bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);
                                            BEJEGYZES* eleje = make_structs_from_file_data(szoveg);
                                            int keresett_hossza;
                                            printf("Add meg a keresett kifejezest! \nKerlek vedd figyelembe, hogy ennel a funkcional tartanod kell a datumozas eredeti formatumat!\n (Www Mmm dd hh:mm:ss Yyyy)\n");
                                            printf("Ha nem teljes datumot keresel, akkor azon a szakaszon tartsd a formatumot amit beirsz, pl. Www Mmm\n\n");
                                            char* keresett = beolvas(&keresett_hossza);
                                            kereses_ido_szerint_sajat_kif(eleje, keresett);
                                            return;
                                       }
                                       else
                                       {
                                           printf("Nem jo betut nyomtal, probalkozz ujra !");
                                       }
                                    }
                                }
                                else
                                {
                                    printf("Nem jo betut adtal meg, probald ujra!");
                                }
                            }
                        }
                        //struct_elemeket_kiir(eleje);
                        return;
                    }
                    //Bejegyzes keresese torlesre vagy szerkesztesre
                    else if(valasz_bejegyzest_kezel[0]== 'C' | valasz_bejegyzest_kezel[0]=='c' & meret_bejegyzest_kezel<2)
                    {
                        //printf("Ez mukodik");
                        free(valasz_bejegyzest_kezel);


                        printf("Eloszor meg kell hatarozni, hogy melyik bejegyzest szeretned kezelni. Mi alapjan keressem?\n");
                        printf("A) Cim\nB) Hely\nC) Megjegyzes\nD) Ido\n");

                        char* miben_keress = (char*)malloc(sizeof(char)*1);
                        miben_keress[0]= 'z';
                        int meret_miben_keress;

                        while (miben_keress[0]!= 'A' && miben_keress[0]!= 'a' && miben_keress[0]!= 'b' && miben_keress[0]!= 'B' && miben_keress[0]!= 'c' && miben_keress[0]!= 'C' && miben_keress[0]!= 'D' && miben_keress[0]!= 'd')
                        {
                            free(miben_keress);
                            miben_keress = beolvas(&meret_miben_keress);
                            //kereses cim szerint
                            if(miben_keress[0] == 'a' | miben_keress[0] == 'A' && meret_miben_keress <2 )
                            {
                                int szoveg_hossz;
                                char* szoveg = bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);

                                if(szoveg != NULL)
                                {
                                    BEJEGYZES* eleje = make_structs_from_file_data(szoveg);
                                    int keresett_hossz;
                                    printf("Ird be a keresett cimet!\n");
                                    char* keresett = beolvas(&keresett_hossz);
                                    printf("\n");
                                    FILE* talaltak;
                                    talaltak = fopen("kereses_eredmenyek.txt", "w");
                                    bool tovabb = kereses_kiiras_cim_szerint(eleje, keresett, talaltak);
                                    struct_elemeket_felszabadit(eleje);
                                    fclose(talaltak);
                                    //free(szoveg);

                                    if (tovabb)
                                    {
                                        szoveg = keresett_bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);
                                        eleje = make_structs_from_file_data(szoveg);
                                        int max_sorszam = kereses_eredmenyek_listaz_sorszammal(eleje);
                                        printf("Ird be, hogy hanyadik elemet valasztod ki!");
                                        int kivalasztott_sorszam;
                                        bool ujra = true;

                                        while (ujra)
                                        {
                                            scanf("%d", &kivalasztott_sorszam);
                                            if (kivalasztott_sorszam > max_sorszam | kivalasztott_sorszam < 0)
                                            {
                                                printf("A kivalasztott sorszam nagyobb, mint ahany bejegyzes van, vagy negativ. \nKerlek adj meg egy megfelelo sorszamot!");
                                            }
                                            else
                                            {
                                                ujra = false;
                                            }
                                        }
                                        BEJEGYZES* kivalasztott = leptetes_kivalasztott_elemre(eleje, kivalasztott_sorszam);
                                        printf("A kivalasztott elem: \n%s%s%s%s\n", kivalasztott->cim, kivalasztott->hely, kivalasztott->megjegyzes, kivalasztott->ido);
                                        torles_vagy_szerkesztes(kivalasztott);
                                    }
                                }
                                return;
                            }
                            //kereses hely szerint
                            else if(miben_keress[0] == 'B' | miben_keress[0] == 'b' && meret_miben_keress <2)
                            {
                                int szoveg_hossz;
                                char* szoveg = bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);
                                if (szoveg != NULL)
                                {
                                    BEJEGYZES* eleje = make_structs_from_file_data(szoveg);
                                    int keresett_hossz;
                                    printf("Ird be a keresett helyet!\n");
                                    char* keresett = beolvas(&keresett_hossz);
                                    printf("\n");
                                    FILE* talaltak;
                                    talaltak = fopen("kereses_eredmenyek.txt", "w");
                                    bool tovabb = kereses_kiiras_hely_szerint(eleje, keresett, talaltak);
                                    struct_elemeket_felszabadit(eleje);
                                    fclose(talaltak);
                                    //free(szoveg);

                                    if (tovabb)
                                    {
                                        szoveg = keresett_bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);
                                        eleje = make_structs_from_file_data(szoveg);
                                        int max_sorszam = kereses_eredmenyek_listaz_sorszammal(eleje);
                                        printf("Ird be, hogy hanyadik elemet valasztod ki!");
                                        int kivalasztott_sorszam;
                                        bool ujra = true;

                                        while (ujra)
                                        {
                                            scanf("%d", &kivalasztott_sorszam);
                                            if (kivalasztott_sorszam > max_sorszam | kivalasztott_sorszam < 0)
                                            {
                                                printf("A kivalasztott sorszam nagyobb, mint ahany bejegyzes van, vagy negativ. \nKerlek adj meg egy megfelelo sorszamot!");
                                            }
                                            else
                                            {
                                                ujra = false;
                                            }
                                        }
                                        BEJEGYZES* kivalasztott = leptetes_kivalasztott_elemre(eleje, kivalasztott_sorszam);
                                        printf("A kivalasztott elem: \n%s%s%s%s\n", kivalasztott->cim, kivalasztott->hely, kivalasztott->megjegyzes, kivalasztott->ido);
                                        torles_vagy_szerkesztes(kivalasztott);
                                    }
                                }
                                return;
                            }
                            // kereses megjegyzes szerint
                            else if(miben_keress[0] == 'C' | miben_keress[0] == 'c' && meret_miben_keress <2)
                            {
                                int szoveg_hossz;
                                char* szoveg = bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);

                                if(szoveg != NULL)
                                {

                                    BEJEGYZES* eleje = make_structs_from_file_data(szoveg);
                                    int keresett_hossz;
                                    printf("Ird be a keresett megjegyzest!\n");
                                    char* keresett = beolvas(&keresett_hossz);
                                    printf("\n");
                                    FILE* talaltak;
                                    talaltak = fopen("kereses_eredmenyek.txt", "w");
                                    bool tovabb = kereses_kiiras_megjegyzes_szerint(eleje, keresett, talaltak);
                                    struct_elemeket_felszabadit(eleje);
                                    fclose(talaltak);
                                    //free(szoveg);

                                    if (tovabb)
                                    {
                                        szoveg = keresett_bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);
                                        eleje = make_structs_from_file_data(szoveg);
                                        int max_sorszam = kereses_eredmenyek_listaz_sorszammal(eleje);
                                        printf("Ird be, hogy hanyadik elemet valasztod ki!");
                                        int kivalasztott_sorszam;
                                        bool ujra = true;

                                        while (ujra)
                                        {
                                            scanf("%d", &kivalasztott_sorszam);
                                            if (kivalasztott_sorszam > max_sorszam | kivalasztott_sorszam < 0)
                                            {
                                                printf("A kivalasztott sorszam nagyobb, mint ahany bejegyzes van, vagy negativ. \nKerlek adj meg egy megfelelo sorszamot!");
                                            }
                                            else
                                            {
                                                ujra = false;
                                            }
                                        }
                                        BEJEGYZES* kivalasztott = leptetes_kivalasztott_elemre(eleje, kivalasztott_sorszam);
                                        printf("A kivalasztott elem: \n%s%s%s%s\n", kivalasztott->cim, kivalasztott->hely, kivalasztott->megjegyzes, kivalasztott->ido);
                                        torles_vagy_szerkesztes(kivalasztott);
                                    }
                                }
                                return;
                            }
                            // kereses ido szerint
                            else if(miben_keress[0] == 'd' | miben_keress[0] == 'D' && meret_miben_keress <2)
                            {
                                int szoveg_hossz;
                                char* szoveg = bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);
                                if (szoveg != NULL)
                                {
                                    BEJEGYZES* eleje = make_structs_from_file_data(szoveg);
                                    int keresett_hossz;
                                    printf("Ird be a keresett idot!\n");
                                    char* keresett = teljes_ido_bekeres(keresett);
                                    printf("\n");
                                    FILE* talaltak;
                                    talaltak = fopen("kereses_eredmenyek.txt", "w");
                                    bool tovabb = kereses_kiiras_ido_szerint(eleje, keresett, talaltak);
                                    struct_elemeket_felszabadit(eleje);
                                    fclose(talaltak);
                                    //free(szoveg);

                                    if (tovabb)
                                    {
                                        szoveg = keresett_bejegyzesek_fajlbol_beolvasasa(&szoveg_hossz);
                                        eleje = make_structs_from_file_data(szoveg);
                                        int max_sorszam = kereses_eredmenyek_listaz_sorszammal(eleje);
                                        printf("Ird be, hogy hanyadik elemet valasztod ki!");
                                        int kivalasztott_sorszam;
                                        bool ujra = true;

                                        while (ujra)
                                        {
                                            scanf("%d", &kivalasztott_sorszam);
                                            if (kivalasztott_sorszam > max_sorszam | kivalasztott_sorszam < 0)
                                            {
                                                printf("A kivalasztott sorszam nagyobb, mint ahany bejegyzes van, vagy negativ. \nKerlek adj meg egy megfelelo sorszamot!");
                                            }
                                            else
                                            {
                                                ujra = false;
                                            }
                                        }
                                        BEJEGYZES* kivalasztott = leptetes_kivalasztott_elemre(eleje, kivalasztott_sorszam);
                                        printf("A kivalasztott elem: \n%s%s%s%s\n", kivalasztott->cim, kivalasztott->hely, kivalasztott->megjegyzes, kivalasztott->ido);
                                        torles_vagy_szerkesztes(kivalasztott);
                                    }
                                }

                                return;
                            }
                            else
                            {
                                printf("Nem a megadott valaszthato betukbol irtal. Probald ujra!\n");
                            }
                        }
                        return;
                    }
                    else
                    {
                        printf("Nem menupontot irtal be. Probalkozz ujra!");
                    }
                }
            }

            //kilepes
            else if(valasz[0] == 'C' | valasz[0] == 'c' & beolvasott_hossz<2)
            {
                printf("Viszlat kesobb!");
                free(valasz);
                *ujranyit = false;
                return;
            }
            else
            {
                if (elso_while)
                {
                    elso_while = false;
                }
                else
                {
                    printf("Nem menupontot irtal be.\n");
                }
            }
        }
    }
