//DACA DORITI SA RULATI, LUATI FUNCTIA SI APELUL SI LE ADAUGATI IN PROIECTUL Seminar02.c . AICI ESTE DOAR EXERCITIUL REZOLVAT SI EXEMPLU DE APEL.

struct Masina getMasiniDupaModel(struct Masina* vector, int nrElemente, const char* conditie) {
	for (int i = 0; i < nrElemente; i++)
	{
		if (strcmp(conditie, vector[i].model) == 0)
		{
			return vector[i];
		}
	}
	return initializare(-1, 0, NULL, 0, '-');
}

int main() {

	printf("Prima masina: \n");
	struct Masina masinaDupaModel = getPrimaMasinaDupaSofer(vector, nrElemente, "Audi");
	afisare(masinaDupaModel);

	dezalocare(&vector, &nrElemente);
}