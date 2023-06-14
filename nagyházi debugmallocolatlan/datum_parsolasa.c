#include "konyvtar.h"

void datum_parsolasa(BEJEGYZES* mozgo)
{
    int i =strlen(mozgo->ido);

    mozgo->raw_sort_number = (char*)malloc(i+1);
    int idx=0;

    //év
    for (int j = i-5; mozgo->ido[j] != '\0' && mozgo->ido[j] != '\n' ; j++)
    {
        if (mozgo->ido[j]== ' ')
        {
            idx = 0;
        }
        else
        {
            mozgo->raw_sort_number[idx]= mozgo->ido[j];
            idx++;
        }
    }
        //honap
        char* temp = (char*)malloc(sizeof(char)*(3+1));
        int idx_m = 0;
        for( int j = 10; j< 13; j++)
        {
            temp[idx_m] = mozgo->ido[j];
            idx_m++;
        }
        temp[idx_m] = '\0';

        char honapok_sorszama[24][4] =
        {
            "Jan", "01", "Feb", "02", "Mar", "03", "Apr", "04", "May", "05", "Jun", "06", "Jul", "07", "Aug", "08", "Sep", "09", "Oct", "10", "Nov", "11", "Dec", "12"
        };
        //honap
        for (int j= 0; j<24; j++)
        {
            int egyzenek_e = strcmp(temp, honapok_sorszama[j]);
            if (egyzenek_e == 0)
            {
                for (int k=0; k<2; k++)
                {
                    mozgo->raw_sort_number[idx]= honapok_sorszama[j+1][k];
                    idx++;
                }
            }
        }
        free(temp);

        //nap

        for (int j = 14; j<16; j++)
        {
            mozgo->raw_sort_number[idx] = mozgo->ido[j];
            idx++;
        }

        //ora perc masodperc
        for (int j = 17; j< i-4; j++)
        {   if (mozgo->ido[j]== ' ')
            {
                j = i-4;
            }
            else
            {
                if(mozgo->ido[j] != ':')
                {
                    mozgo->raw_sort_number[idx] = mozgo->ido[j];
                    idx++;
                }
            }
        }
        mozgo->raw_sort_number[idx] = '\0';

        //printf("%s\n", mozgo->raw_sort_number);
        char* ptr;

        mozgo->sort_number = strtoll(mozgo->raw_sort_number, &ptr, 10);
        //printf("%lld\n", mozgo->sort_number);
        //printf("itt vege\n");
}
