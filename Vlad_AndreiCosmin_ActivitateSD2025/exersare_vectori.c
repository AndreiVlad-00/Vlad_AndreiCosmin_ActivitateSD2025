#include<malloc.h> //alocare memorie
#include<stdio.h>
#include<string.h>

//vector pe structura
typedef struct student {
	int id;
	char* nume;
}student;

student initializareStudent(int id, const char* nume) {
	student s;
	s.id = id;
	s.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy_s(s.nume, (sizeof(char) * strlen(nume) + 1) ,nume);
	return s;
}

//functie separata de afisare

void main() {

	int v[5] = { 4,2,7,3,9 };
	printf("%p \n", v);
	printf("%d \n", *v);
	printf("%d \n", *(v + 1));
	printf("%p \n", (v + 1));


	for (int i = 0; i < 5; i++) {
		printf("%d \n", v[i]);
	}

	int* p;
	p = v; //pointam catre inceputul vectorului
	printf(" % d \n", *p);
	*p = 13; //4 se tranforma in 13
	printf("%d \n", *p);
	p++;
	printf("%d \n", *p);
	printf("%p \n", p);

	*p = 12; // 2 devine 12
	printf("%d \n", *p);
	p = &v[2];
	printf("%d \n", v[2]); // indexare - imi arata valoarea de la o anumita pozitie

	//p=v[2] nu este ok pt ca in stanga avem pointer si in dreapta avem adresa

	*p = 17;
	printf("%p \n", p);
	printf("%d \n", *p);

	p = v + 3;
	*p = 22;
	printf("%d \n", *p);

	p = v;
	p--;
	printf("%d \n", *p);
	//*p = 88; nu merge pt ca e in afara vectorului nostru / nu am alocat memorie
	*(v + 4) = 33;

	for (int i = 0; i < 5; i++) {
		printf("\n\n%d \n", v[i]);
	}

	int dim = 4;
	int* vd = (int*)malloc(sizeof(int) * dim);

	float a = 1.77;
	printf("%5.2f \n", a);
	printf("%d \n", (int)a); // cast prin pierdere

	int dim1 = 5; //dimensiunea mereu este int
	float* vdf = (float*)malloc(sizeof(float) * dim);

	char* name = (char*)malloc(sizeof(char) * strlen("Andrei") + 1);//nu exista nicio litera in vector
	strcpy_s(name, (sizeof(char) * strlen("Andrei") + 1), "Andrei");
	char buffer[50];//vector static de caractere, se elibereaza singur
	printf("%s \n", name);
	student s1 = initializareStudent(10, "Andrei");
	student s2 = initializareStudent(11, "Ioana");
	student s3 = initializareStudent(12, "Ana");
	printf("Studentul este:%s si are id:%d \n", s1.nume, s1.id);

	//vector de studenti

	int nrStudenti = 3;
	student* vector = (student*)malloc(sizeof(student) * nrStudenti);
	//adaugare studenti in vector
	vector[0] = s1;
	vector[1] = s2;
	vector[2] = s3;

	for (int i = 0; i < nrStudenti; i++) {
		printf("Studentul este:%s si are id:%d \n", vector[i].nume, vector[i].id);
	}

	//data viitoare lista simpla

}
