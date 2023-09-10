#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
          Hasta takip sistemi
? Hasta no, adý, yaþý ve hastalýk bilgisini tutacak
bir struct oluþtur
? Belli sayýda hasta giriþi yap.              (hasta girisi icin dosya acýp icine yazmak gerekiyo yani fseek ,fwrite)
? Dosya içerisinde hasta no’ya göre arama yap.
? Hasta kaydý sil
? Hasta kaydý düzenle.
? Dosyadan hastalarý listele
*/
struct hastakayit{
    int no;
    char ad[20];
    int yas;
    char hastalik[50];
};

typedef struct hastakayit hastabilgi;

int secimgir()
{
    int menusecim;
    printf("1- Belli sayida hasta girisi yap. \n"
           "2-Dosya icerisinde hasta no ya gore arama yap.\n"
           "3-Hasta kaydi sil\n"
           "4-Hasta kaydi duzenle.\n"
           "5-Dosyadan hastalari listele\n");
           printf("\n\nbir secim yapiniz(cikis icin 6)");
    scanf("%d",&menusecim);
    return menusecim;

}


void hastagiriskayidi(FILE *dosya)
{
    hastabilgi hastabilgiii={0,"",0,""};
    printf("1-100 arasi hasta yerlestirmek istenen no gir(bitirmek icin 0 gir): ");
    scanf("%d",&hastabilgiii.no);
    while(hastabilgiii.no!=0)
    {
        printf("hasta ad yas ve hastalik bilgisini giriniz: ");
        fscanf(stdin,"%s%d%s",hastabilgiii.ad,&hastabilgiii.yas,hastabilgiii.hastalik);
        fseek(dosya,(hastabilgiii.no-1)*sizeof(hastabilgi),SEEK_SET);
        fwrite(&hastabilgiii,sizeof(hastabilgi),1,dosya);
        printf("hasta no girin: \n?");
        scanf("%d",&hastabilgiii.no);
    }

}

void hastanoyagoreara(FILE *dosya)
{
    int arananno;
    hastabilgi hastabilgiii={0,"",0,""};
    printf("aradiginiz no yu girin:  ");
    scanf("%d",&arananno);

    printf("%s   %s   %s    %s\n","no","ad","yas","hastalik");
    while(fread(&hastabilgiii,sizeof(hastabilgi),1,dosya)==1)
    {
        if(hastabilgiii.no==arananno)
        {

        printf("%d-   %s    %d    %s\n",hastabilgiii.no,hastabilgiii.ad,hastabilgiii.yas,hastabilgiii.hastalik);
        break;

        }
        else
        {
            printf("boyle bi hasta bulunamadi...");
        }
    }
}

void kayitsil(FILE *dosya)
{
    int hesapnosu;
    hastabilgi hastasil,boskayit={0,"",0,""};
    printf("silinecek hesabi girin:  ");
    scanf("%d",&hesapnosu);
    fseek(dosya,(hastasil.no-1)*sizeof(hastabilgi),SEEK_SET);
    fread(&hastasil,sizeof(hastabilgi),1,dosya);
    if(hastasil.no==0)
    {
        printf("silinecek hasta kayidi yokk\n");
    }
    else
    {
        fseek(dosya,(hastasil.no-1)*sizeof(hastabilgi),SEEK_SET);
        fwrite(&boskayit,sizeof(hastabilgi),1,dosya);
    }

}

void kayitduzenle(FILE *dosya)
{
    int hastanosu;
    printf("duzenlenecek hasta kaydi girin:  ");
    scanf("%d",&hastanosu);
    hastabilgi hastalar;
    while(fread(&hastalar,sizeof(hastalar),1,dosya)==1)
    {
        if(hastalar.no==hastanosu)
        {
            fseek(dosya,sizeof(hastalar),SEEK_SET);
            printf("hastanin adi: ");
            scanf("%s",hastalar.ad);
            printf("hastanin yasi: ");
            scanf("%d",&hastalar.yas);
            printf("hastanin rahatsizligi: ");
            printf("%s",hastalar.hastalik);

            fwrite(&hastalar,sizeof(hastabilgi),1,dosya);
            printf("hasta basariyla guncellendi\n");
            break;
        }
    }

}

void listele(FILE *dosya)
{
    hastabilgi hastalist={0,"",0,""};
    while(!feof(dosya))
    {
        fread(&hastalist,sizeof(hastabilgi),1,dosya);
        printf("%d %s %d %s\n",hastalist.no,hastalist.ad,hastalist.yas,hastalist.hastalik);
    }
}

int main() {

    int secim;

    FILE *dosya;
    dosya=fopen("hastabilgileri.txt","r+");
    if(dosya==NULL)
    {
        printf("dosya acilamadi...");
    }
    else
    {
        while((secim=secimgir())!=6)
        {
            switch(secim)
            {
                case 1: hastagiriskayidi(dosya); break;
                case 2: hastanoyagoreara(dosya); break;
                case 3: kayitsil(dosya); break;
                case 4: kayitduzenle(dosya); break;
                case 5: listele(dosya); break;

            }
        }
        fclose(dosya);
    }


    return 0;
}

