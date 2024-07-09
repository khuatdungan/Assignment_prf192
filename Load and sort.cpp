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
