#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ***** dinh nghia bien SIM *****
typedef struct {
    char cccd[20];
    char lastName[50];
    char firstName[50];
    char network[50];
    char phoneNumber[15];
    float price;
} SIM;

void inputSIM(SIM *sim) {
    printf("Nhap so CCCD: ");
    scanf("%s", sim->cccd);
    printf("Nhap ho chu sim: ");
    scanf("%s", sim->lastName);
    printf("Nhap ten chu sim: ");
    scanf("%s", sim->firstName);
    printf("Nhap nha mang: ");
    scanf("%s", sim->network);
    printf("Nhap so dien thoai: ");
    scanf("%s", sim->phoneNumber);
    printf("Nhap gia tien: ");
    scanf("%f", &sim->price);
}

void displaySIM(SIM sim) {
    printf("CCCD: %s\n", sim.cccd);
    printf("Ho: %s\n", sim.lastName);
    printf("Ten: %s\n", sim.firstName);
    printf("Nha mang: %s\n", sim.network);
    printf("So dien thoai: %s\n", sim.phoneNumber);
    printf("Gia tien: %.2f\n", sim.price);
}

void loadSIMsFromFile(SIM sims[], int *count) {
    FILE *file = fopen("sim_database.txt", "r");
    if (file == NULL) {
        *count = 0;
        return;
    }
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%f\n", sims[*count].cccd, sims[*count].lastName, sims[*count].firstName, sims[*count].network, sims[*count].phoneNumber, &sims[*count].price) != EOF) {
        (*count)++;
    }
    fclose(file);
}

void saveSIMsToFile(SIM sims[], int count) {
    FILE *file = fopen("sim_database.txt", "w");
    int i;
    for ( i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s,%s,%s,%.2f\n", sims[i].cccd, sims[i].lastName, sims[i].firstName, sims[i].network, sims[i].phoneNumber, sims[i].price);
    }
    fclose(file);
}



void sortSIMByPhoneNumber(SIM sims[], int count, int ascending) {
	int i,j;
    for (i = 0; i < count - 1; i++) {
        for ( j = i + 1; j < count; j++) {
            if ((ascending && strcmp(sims[i].phoneNumber, sims[j].phoneNumber) > 0) ||
                (!ascending && strcmp(sims[i].phoneNumber, sims[j].phoneNumber) < 0)) {
                SIM temp = sims[i];
                sims[i] = sims[j];
                sims[j] = temp;
            }
        }
    }
}

void sortSIMByPrice(SIM sims[], int count, int ascending) {
	int i,j;
    for ( i = 0; i < count - 1; i++) {
        for ( j = i + 1; j < count; j++) {
            if ((ascending && sims[i].price > sims[j].price) ||
                (!ascending && sims[i].price < sims[j].price)) {
                SIM temp = sims[i];
                sims[i] = sims[j];
                sims[j] = temp;
            }
        }
    }
}




int main()
{

	return 0;
}
