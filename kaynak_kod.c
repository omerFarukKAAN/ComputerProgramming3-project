#include <stdio.h>
#include <string.h> //Aduzelt() fonksiyonunda strcmp() fonksiyonunu kullanmak için eklendi
#define n 5

typedef struct{
	int year;
	char singer[30];
	char albumName[30];
} Record;

int cumleKarsilastir(char *s1, char *s2){	//benzerBul() metodunda string kutuphanesi kullanmadan string karsilastirmak icin metod
	int i = 0;
	while( s1[i] != '\0' && s2[i] != '\0' ){
		if( s1[i] != s2[i] ){
			return 0;
	}
		i++;	
	}return 1;
}

void Kaydet_R(FILE *records){
	int i;
	records = fopen("Records.txt", "a");
	for(i = 0; i < n; i++){
		Record r;
		puts("Enter record year : ");
		scanf("%d", &r.year);
		puts("Enter singer : ");
		scanf("%s", &r.singer);
		puts("Enter album name : ");
		scanf("%s", &r.albumName);
		puts("");
		fprintf(records, "%d %s %s\n", r.year, r.singer, r.albumName);
	}
	fclose(records);
	puts("Records.txt dosyasina belirtilen Record'lar kaydedildi !");
}

void Kaydet_n(FILE *newRecords){
	int i;
	newRecords = fopen("newRecords.txt", "a");
	for(i = 0; i < n; i++){
		Record r;
		puts("Enter record year : ");
		scanf("%d", &r.year);
		puts("Enter singer : ");
		scanf("%s", &r.singer);
		puts("Enter album name : ");
		scanf("%s", &r.albumName);
		puts("");
		fprintf(newRecords, "%d %s %s\n", r.year, r.singer, r.albumName);
	}
	fclose(newRecords);
	puts("newRecords.txt dosyasina belirtilen Record'lar kaydedildi !");
}

void Ylistele(FILE *records, int year){
	records = fopen("Records.txt", "r");
	FILE *yaz = fopen("yaz.txt", "w");
	Record okunan;
	int c;
	do {
      c = fscanf(records,"%d %s %s",&okunan.year, okunan.singer, okunan.albumName);
      if (c != EOF && okunan.year > year)
         fprintf(yaz, "%d %s %s", okunan.year, okunan.singer, okunan.albumName);
   } while (c != EOF);
   
   	fclose(yaz);
	fclose(records);

	puts("Belirtilen yildan sonraki yillara sahip Record'lar yaz.txt dosyasina basari ile yazildi !");
}

void Aduzelt(char albumName[30], FILE *records){
	records = fopen("Records.txt", "r");
	FILE *yeni = fopen("Records1.txt","w");	//Dosya icerigini degistirmek icin yeni dosya ac
	Record okunan, yeniKayit;
	
	int c;
	
	while( !feof(records) ){
		c = fscanf(records,"%d %s %s",&okunan.year, okunan.singer, okunan.albumName);
		if( c != EOF){
			if ( strcmp(albumName, okunan.albumName) == 0 ){	//Okunan icerik degismesi istenen icerikle ayni ise onun yerine degistirilmis olan yeni icerigi yaz
      			char newSinger[30];
				puts("Yeni sarkici girin :");
				scanf("%s", &newSinger);
				strcpy(yeniKayit.singer, newSinger);
				strcpy(yeniKayit.albumName, okunan.albumName);
				yeniKayit.year = okunan.year;
				fprintf(yeni, "%d %s %s\n", yeniKayit.year, yeniKayit.singer, yeniKayit.albumName);
			}else fprintf(yeni, "%d %s %s\n", okunan.year, okunan.singer, okunan.albumName);	//Okunan icerik degismesi istenen icerikle ayni degil ise aynen yaz
		}
	}
	
	fclose(records);
	fclose(yeni);
	
	remove("Records.txt");		//Eski dosyayi sil
	rename("Records1.txt", "Records.txt");	//Yeni dosyanin adini eski dosyanin adi ile degistir. Boylece eski dosya uzerinde degisiklik yapmis gibi olsun
	
	puts("Verilen parametredeki albumName ile ayni degere sahip olan Record'larin singer degiskenleri kullanicidan alinan veri ile degistirildi !");
}

void searchRecord(FILE *records, FILE *newRecords){
	records = fopen("Records.txt", "r");
	newRecords = fopen("newRecords.txt", "r");
	
	int c;
	Record okunan, newOkunan;
	
	while( !feof(records) ){
		c = fscanf(records, "%d %s %s", &okunan.year, okunan.singer, okunan.albumName);
		if( c != EOF ){
			rewind(newRecords); //Her dönüste newRecords.txt adli dosyayi basa dondur
			while( !feof(newRecords) ){
				c = fscanf(newRecords, "%d %s %s", &newOkunan.year, newOkunan.singer, newOkunan.albumName);
				if( c != EOF ){
					if(okunan.year == newOkunan.year){
						printf("Year : %d Singer : %s Album Name : %s\n", okunan.year, okunan.singer, okunan.albumName);
						printf("Year : %d Singer : %s Album Name : %s\n", newOkunan.year, newOkunan.singer, newOkunan.albumName);
						puts("----------------------------------------------------------------------------------------------");
					}
				}
			}
		}
	}
   
   fclose(records);
   fclose(newRecords);
}

void benzerBul(FILE *records, FILE *newRecords, FILE *benzerRecords){
	records = fopen("Records.txt", "r");
	newRecords = fopen("newRecords.txt", "r");
	benzerRecords = fopen("benzerRecords.txt", "w");
	
	Record okunan, newOkunan;
	int c;
	int count = 0;	//Ayni eleman sayisi
	
	while( !feof(records) ){
		c = fscanf(records, "%d %s %s", &okunan.year, okunan.singer, okunan.albumName);
		if( c != EOF ){
			rewind(newRecords);	//Her dönüste newRecords.txt adli dosyayi basa dondur
			while( !feof(newRecords) ){
				c = fscanf(newRecords, "%d %s %s", &newOkunan.year, newOkunan.singer, newOkunan.albumName);
				if( c != EOF ){
					if( okunan.year == newOkunan.year){
						count++;
					}
					if( cumleKarsilastir(okunan.singer, newOkunan.singer) == 1){
						count++;
					}
						
					if( cumleKarsilastir(okunan.albumName, newOkunan.albumName) == 1){
						count++;
					}
				}
				if(count >= 2){	//Okunan iceriklerden en az 2 tane ayni olan varsa ekrana yazdir
					fprintf(benzerRecords, "%d %s %s\n", okunan.year, okunan.singer, okunan.albumName);
					fprintf(benzerRecords, "%d %s %s\n", newOkunan.year, newOkunan.singer, newOkunan.albumName);
					fputs("---------------\n", benzerRecords);
				}
				count = 0; //Sonraki Record'a gecerken ayni eleman sayisini sifirla
			}
		}
	}
	puts("'Records.txt' ve 'newRecords.txt' dosyalarindaki benzer Record lar 'benzerRecords.txt' adli dosyaya yazildi !");
}

int main (void){
	FILE *fp, *fp1, *fp2;
	
	Kaydet_R(fp);
	//Kaydet_n(fp1);
	//Ylistele(fp1, 2000);
	Aduzelt("omer", fp);
	//searchRecord(fp, fp1);
	//benzerBul(fp, fp1, fp2);

}
