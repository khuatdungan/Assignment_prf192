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

int i, j;

void inputString(char* prompt, char* str, int size) { 
    do {
        printf("%s", prompt);
        fgets(str, size, stdin);
        str[strcspn(str, "\n")] = '\0';
        if (strlen(str) == 0) {
            printf("Khong duoc de trong. Vui long nhap lai.\n");
        }
    } while (strlen(str) == 0);
}


int simExists(SIM sims[], int count, char phoneNumber[]) {
    for (i = 0; i < count; i++) {
        if (strcmp(sims[i].phoneNumber, phoneNumber) == 0) {
            return 1;
        }
    }
    return 0;
}

void inputSIM(SIM *sim, SIM sims[], int count) {
    do {
        inputString("Nhap so dien thoai: ", sim->phoneNumber, 15);
        if (simExists(sims, count, sim->phoneNumber)) {
            printf("So dien thoai da ton tai. Vui long nhap lai.\n");
        }
    } while (simExists(sims, count, sim->phoneNumber));
    
    inputString("Nhap so CCCD: ", sim->cccd, 20);
    inputString("Nhap ho chu sim: ", sim->lastName, 50);
    inputString("Nhap ten chu sim: ", sim->firstName, 50);
    inputString("Nhap nha mang: ", sim->network, 50);
    printf("Nhap gia tien: ");
    scanf("%f", &sim->price);
    getchar();
}

void displaySIM(SIM sim) {
    printf("CCCD: %s\n", sim.cccd);
    printf("Ho: %s\n", sim.lastName);
    printf("Ten: %s\n", sim.firstName);
    printf("Nha mang: %s\n", sim.network);
    printf("So dien thoai: %s\n", sim.phoneNumber);
    printf("Gia tien: %.2f\n", sim.price);
}

void loadSIMsFromCSV(SIM sims[], int *count) {
    FILE *file = fopen("sim_database.csv", "r");
    if (file == NULL) {
        *count = 0;
        return;
    }
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%f\n", sims[*count].cccd, sims[*count].lastName, sims[*count].firstName, sims[*count].network, sims[*count].phoneNumber, &sims[*count].price) != EOF) {
        (*count)++;
    }
    fclose(file);
}

void saveSIMsToCSV(SIM sims[], int count) {
    FILE *file = fopen("sim_database.csv", "w");
    for (i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s,%s,%s,%.2f\n", sims[i].cccd, sims[i].lastName, sims[i].firstName, sims[i].network, sims[i].phoneNumber, sims[i].price);
    }
    fclose(file);
}

void updatePrice(SIM sims[], int count, char phoneNumber[], float newPrice) {
    for (i = 0; i < count; i++) {
        if (strcmp(sims[i].phoneNumber, phoneNumber) == 0) {
            sims[i].price = newPrice;
            printf("Cap nhat gia tien thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay so dien thoai.\n");
}

void updateOwner(SIM sims[], int count, char phoneNumber[], char newLastName[], char newFirstName[]) {
    for (i = 0; i < count; i++) {
        if (strcmp(sims[i].phoneNumber, phoneNumber) == 0) {
            strcpy(sims[i].lastName, newLastName);
            strcpy(sims[i].firstName, newFirstName);
            printf("Cap nhat thong tin chu sim thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay so dien thoai.\n");
}

void deleteSIM(SIM sims[], int *count, char phoneNumber[]) {
    for (i = 0; i < *count; i++) {
        if (strcmp(sims[i].phoneNumber, phoneNumber) == 0) {
            for (j = i; j < *count - 1; j++) {
                sims[j] = sims[j + 1];
            }
            (*count)--;
            printf("Xoa thong tin sim thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay so dien thoai.\n");
}

void sortSIMByPhoneNumber(SIM sims[], int count, int ascending) {
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
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
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if ((ascending && sims[i].price > sims[j].price) ||
                (!ascending && sims[i].price < sims[j].price)) {
                SIM temp = sims[i];
                sims[i] = sims[j];
                sims[j] = temp;
            }
        }
    }
}

void displayAllSIMs(SIM sims[], int count) {
    for (i = 0; i < count; i++) {
        displaySIM(sims[i]);
        printf("\n");
    }
}

void displaySIMsByPhoneNumber(SIM sims[], int count, char phoneNumber[]) {
    for (i = 0; i < count; i++) {
        if (strcmp(sims[i].phoneNumber, phoneNumber) == 0) {
            displaySIM(sims[i]);
            return;
        }
    }
    printf("Khong tim thay so dien thoai.\n");
}

void displaySIMsByPriceRange(SIM sims[], int count, float minPrice, float maxPrice) {
    for (i = 0; i < count; i++) {
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

    for (i = 0; i < count; i++) {
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

    loadSIMsFromCSV(sims, &count);

    do {
        printf("==========================================   MENU:   ==========================================\n");
        printf("||      1. Nhap thong tin Sim                                                                ||\n");
        printf("||-------------------------------------------------------------------------------------------||\n");
        printf("||      2. Sua thong tin Gia tien cua sim (tim theo So dien thoai)                           ||\n");
        printf("||-------------------------------------------------------------------------------------------||\n");
        printf("||      3. Sua thong tin Ho va Ten chu sim (tim theo So dien thoai)                          ||\n");
        printf("||-------------------------------------------------------------------------------------------||\n");
        printf("||      4. Xoa thong tin (tim theo So dien thoai)                                            ||\n");
        printf("||-------------------------------------------------------------------------------------------||\n");
        printf("||      5. Sap xep danh sach giam dan theo So dien thoai                                     ||\n");
        printf("||-------------------------------------------------------------------------------------------||\n");
        printf("||      6. Sap xep danh sach tang dan theo Gia tien                                          ||\n");
        printf("||-------------------------------------------------------------------------------------------||\n");
        printf("||       7. Xuat toan bo danh sach                                                           ||\n");
        printf("||-------------------------------------------------------------------------------------------||\n");
        printf("||      8. Xuat danh sach theo So dien thoai                                                 ||\n");
        printf("||-------------------------------------------------------------------------------------------||\n");
        printf("||      9. Xuat danh sach theo Gia tien trong khoang nao do                                  ||\n");
        printf("||-------------------------------------------------------------------------------------------||\n");
        printf("||      10. Xuat Gia tien trung binh, Gia tien cao nhat, Gia tien thap nhat                  ||\n");
        printf("||-------------------------------------------------------------------------------------------||\n");
        printf("||      0. Thoat                                                                             ||\n");
        printf("===============================================================================================\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                inputSIM(&sims[count], sims, count);
                count++;
                break;
            case 2: {
                char phoneNumber[15];
                float newPrice;
                inputString("Nhap so dien thoai: ", phoneNumber, 15);
                printf("Nhap gia tien moi: ");
                scanf("%f", &newPrice);
                getchar();
                updatePrice(sims, count, phoneNumber, newPrice);
                break;
            }
            case 3: {
                char phoneNumber[15];
                char newLastName[50], newFirstName[50];
                inputString("Nhap so dien thoai: ", phoneNumber, 15);
                inputString("Nhap ho moi: ", newLastName, 50);
                inputString("Nhap ten moi: ", newFirstName, 50);
                updateOwner(sims, count, phoneNumber, newLastName, newFirstName);
                break;
            }
            case 4: {
                char phoneNumber[15];
                inputString("Nhap so dien thoai: ", phoneNumber, 15);
                deleteSIM(sims, &count, phoneNumber);
                break;
            }
            case 5:
                sortSIMByPhoneNumber(sims, count, 0);
                printf("Sap xep danh sach giam dan theo So dien thoai thanh cong.\n");
                break;
            case 6:
                sortSIMByPrice(sims, count, 1);
                printf("Sap xep danh sach tang dan theo Gia tien thanh cong.\n");
                break;
            case 7:
                displayAllSIMs(sims, count);
                break;
            case 8: {
                char phoneNumber[15];
                inputString("Nhap so dien thoai: ", phoneNumber, 15);
                displaySIMsByPhoneNumber(sims, count, phoneNumber);
                break;
            }
            case 9: {
                float minPrice, maxPrice;
                printf("Nhap gia tien thap nhat: ");
                scanf("%f", &minPrice);
                printf("Nhap gia tien cao nhat: ");
                scanf("%f", &maxPrice);
                getchar();
                displaySIMsByPriceRange(sims, count, minPrice, maxPrice);
                break;
            }
            case 10:
                displayPriceStats(sims, count);
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }

        saveSIMsToCSV(sims, count);

    } while (choice != 0);

    return 0;
}

