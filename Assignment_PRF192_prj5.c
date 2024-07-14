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
char* lTrim (char s[]){
	int i=0;
	while (s[i]==' ') i++;
	if(i>0) strcpy(&s[0], &s[i]);//     khuat dung an
	return s;
}
char* rTrim (char s[]){
	int i=strlen(s)-1;
	while (s[i]==' ') i--;// khuat dung an       .
	s[i+1]='\0';
	return s;
}
char* trim (char s[]){
	rTrim(lTrim(s));
	char *ptr = strstr(s,"  ");
	while (ptr!=NULL) {
		strcpy(ptr,ptr+1);
		
		ptr = strstr(s,"  ");
	}
	return s;  // khuat      dung     an 
}
char* nameStr(char s[]){
	trim(s);
	strlwr(s);
	int L = strlen(s);
	int i;
	for (i=0;i<L;i++){
		if (i==0 || (i>0 && s[i-1]==' ')){ // Khuat Dung An
			s[i] = toupper (s[i]);
		}
	
	}
	return s;
}
void inputSIM(SIM *sim) {
    printf("Nhap so CCCD: ");
    scanf("%s", sim->cccd);
    printf("Nhap ho chu sim: ");
    scanf("%s", sim->lastName);
    //trim(sim.lastName);
    printf("Nhap ten chu sim: ");
    scanf("%s", sim->firstName);
    //trim(sim.firstName);
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
    FILE *file = fopen("sim_database.csv", "w");
    int i;
	for (i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s,%s,%s,%.2f\n", sims[i].cccd, sims[i].lastName, sims[i].firstName, sims[i].network, sims[i].phoneNumber, sims[i].price);
    }
    fclose(file);
}
void saveSIMsToCSV(SIM sims[], int count) {
    FILE *file = fopen("sim_database.csv", "w");
    int i;
    for ( i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s,%s,%s,%.2f\n", sims[i].cccd, sims[i].lastName, sims[i].firstName, sims[i].network, sims[i].phoneNumber, sims[i].price);
    }
    fclose(file);
}


void updatePrice(SIM sims[], int count, char phoneNumber[], float newPrice) {
    int i;
	for ( i = 0; i < count; i++) {
        if (strcmp(sims[i].phoneNumber, phoneNumber) == 0) {
            sims[i].price = newPrice;
            printf("Cap nhat gia tien thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay so dien thoai.\n");
}

void updateOwner(SIM sims[], int count, char phoneNumber[], char newLastName[], char newFirstName[]) {
    int i;
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
    int i,j;
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
	for (i = 0; i < count - 1; i++) {
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

    int i;
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

    // Load data from file at the beginning
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
        printf("||      7. Xuat toan bo danh sach                                                            ||\n");
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

        switch (choice) {
            case 1:
                inputSIM(&sims[count]);
                count++;
                break;
            case 2: {
                char phoneNumber[15];
                float newPrice;
                printf("Nhap so dien thoai: ");
                scanf("%s", phoneNumber);
                printf("Nhap gia tien moi: ");
                scanf("%f", &newPrice);
                updatePrice(sims, count, phoneNumber, newPrice);
                break;
            }
            case 3: {
                char phoneNumber[15];
                char newLastName[50];
                char newFirstName[50];
                printf("Nhap so dien thoai: ");
                scanf("%s", phoneNumber);
				printf("Nhap ho moi: ");
                scanf("%s", newLastName);
                printf("Nhap ten moi: ");
                scanf("%s", newFirstName);
                updateOwner(sims, count, phoneNumber, newLastName, newFirstName);
                break;
            }
            case 4: {
                char phoneNumber[15];
                printf("Nhap so dien thoai: ");
                scanf("%s", phoneNumber);
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
                printf("Nhap so dien thoai: ");
                scanf("%s", phoneNumber);
                displaySIMsByPhoneNumber(sims, count, phoneNumber);
                break;
            }
            case 9: {
                float minPrice, maxPrice;
                printf("Nhap gia tien thap nhat: ");
                scanf("%f", &minPrice);
                printf("Nhap gia tien cao nhat: ");
                scanf("%f", &maxPrice);
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

        // Save data to file after every change
        saveSIMsToCSV(sims, count);

    } while (choice != 0);

    return 0;
}


