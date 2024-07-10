#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char cccd[20];
    char lastName[50];
    char firstName[50];
    char network[50];
    char phoneNumber[15];
    float price;
} SIM;

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

void deleteSIM(SIM sims[], int count, char phoneNumber[]) {
	int i,j;
    for (i = 0; i < count; i++) {
        if (strcmp(sims[i].phoneNumber, phoneNumber) == 0) {
            for (j = i; j < count - 1; j++) {
                sims[j] = sims[j + 1];
            }
            count--;
            printf("Xoa thong tin sim thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay so dien thoai.\n");
}

void displayAllSIMs(SIM sims[], int count) {
	int i;
    for (i = 0; i < count; i++) {
        displaySIM(sims[i]);
        printf("\n");
    }
}

void displaySIMsByPhoneNumber(SIM sims[], int count, char phoneNumber[]) {
	int i;
    for (i = 0; i < count; i++) {
        if (strcmp(sims[i].phoneNumber, phoneNumber) == 0) {
            displaySIM(sims[i]);
            return;
        }
    }
    printf("Khong tim thay so dien thoai.\n");
}

void displaySIMsByPriceRange(SIM sims[], int count, float minPrice, float maxPrice) {
	int i;
    for ( i = 0; i < count; i++) {
        if (sims[i].price >= minPrice && sims[i].price <= maxPrice) {
            displaySIM(sims[i]);
            printf("\n");
        }
    }
}

void displayPriceStats(SIM sims[], int count) {
    if (count == 0) {
        printf("Khong co thong tin sim nao.\n");
        return;
    }

    float totalPrice = 0;
    float maxPrice = sims[0].price;
    float minPrice = sims[0].price;
    int i;
    for ( i = 0; i < count; i++) {
        totalPrice += sims[i].price;
        if (sims[i].price > maxPrice) {
            maxPrice = sims[i].price;
        }
        if (sims[i].price < minPrice) {
            minPrice = sims[i].price;
        }
    }

    float averagePrice = totalPrice / count;
    printf("Gia tien trung binh: %.2f\n", averagePrice);
    printf("Gia tien cao nhat: %.2f\n", maxPrice);
    printf("Gia tien thap nhat: %.2f\n", minPrice);
}

int main() {
    SIM sims[100];
    int count = 0;
    int choice;

    // Load data from file at the beginning
    loadSIMsFromFile(sims, &count);
    
    displaySIM(sims[0]);
	displayAllSIMs(sims, count);
	displaySIMsByPhoneNumber(sims, count, "0928393839");
	displaySIMsByPriceRange(sims, count, 0, 1000000);
	displayPriceStats(sims, count);
	deleteSIM(sims, count, "0992833983");
    return 0;
}


