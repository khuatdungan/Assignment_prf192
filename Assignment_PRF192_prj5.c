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






int main()
{

	return 0;
}
