#include <stdio.h>
#include <string.h>


#define FILENAME "students.txt"
/// maximum: 100 students
/// each students name has maximum 50 characters
char studentNames[100][50];

char studentIDs[100][50];

/// Scores must be >=0 and <=10
float scores[100];

/// Number of lines exist in the file.
int line = 0;

/// Features
void addStudent();
void displayStudents();
void searchStudents();
void averageScore();
void save();
void sortStudents();

/// Program only
int exist();
void displayTitle();
int loadSavedStudents();
void input(int* choice);
void remove_newline_ch(char* line);
int validString(char* s);
void copyNewStudentToData(char* from, char* des);

int main() {
	int res = loadSavedStudents();
	if(res == 1) {
		displayTitle();
		
		while(1) {
		int choice;
		input(&choice);
		if(choice == 0) break;
		switch(choice) {
			case 1: {
				addStudent();
				break;
			}
			
			case 2: {
				displayStudents();
				break;
			}
			
			case 3: {
				searchStudents();
				break;
			}
			
			case 4: {
				averageScore();
				break;
			}
			
			case 5: {
				save();
				break;
			}
			
			case 6: {
				sortStudents();
				break;
			}
		}
	}
}
	
	return 0;
}

void addStudent() {
	printf("\n");
	if(line == 100) {
		printf("Da dat gioi han 100 sinh vien. Khong the them sinh vien.\n");
		return;
	}
	
	char id[50];
	char name[50];
	float score;

	getchar();	
	//* Nhap ma sv
	while(1) {
	printf("Nhap ma sinh vien: ");
	fgets(id, 50, stdin);
	if(validString(id) == 1){
		break;	
	} else {
		printf("Ma sinh vien khong hop le.\n");
	}
	}
	
	//* Nhap ten sv
	while(1) {
	printf("Nhap ten sinh vien: ");
	fgets(name, 50, stdin);
	if(validString(name) == 1){
		break;	
	} else {
		printf("Ten sinh vien khong hop le.\n");
	}
	}
	
	//* Nhap diem sv
	while(1) {
	printf("Nhap diem sinh vien: ");
	int res = scanf("%f", &score);
	if(res > 0 && score >=0 && score <= 10){
		break;	
	} else {
		printf("Diem sinh vien khong hop le.\n");
		getchar();
	}
	}
	
	remove_newline_ch(id);
	remove_newline_ch(name);
	
	//* Assign new value to data 
	copyNewStudentToData(id, studentIDs[line]);
	copyNewStudentToData(name, studentNames[line]);
	scores[line] = score;
	line++;
	
	printf("Da them sinh vien: %s, %s, %.2f\n", id, name, score);
	printf("\n");
}

void displayStudents() {
	printf("\n");
	printf("Ma SV     Ten SV                                  Diem\n");
	int i;
	for(i = 0; i< line; i++) {
		printf("%-10s", studentIDs[i]);
		printf("%-40s", studentNames[i]);
		printf("%f", scores[i]);
		printf("\n");
	}
	printf("\n");
}

void searchStudents() {
	//* Implement this
}

void averageScore() {
	printf("\n");
	int i;
	float sum = 0;
	for(i = 0; i < line; i++) {
		sum += scores[i];
	}
	
	printf("Diem trung binh cua cac sinh vien: %.2f", sum/line);
	printf("\n");
}

void save() {
	//* Implement this
}

void sortStudents() {
	//* Implement this
}

//* Implemetation of program function. Not related to Function 1, 2, 3, 4, 5, 6

int exists(char* name) {
	FILE* f = fopen(name, "r");
	if(f != NULL) {
		fclose(f);
		return 1;
	}
	return 0;
}

int loadSavedStudents() {
	if(exists(FILENAME)) {
		FILE* f = fopen(FILENAME, "r");
		
		while (fscanf(f, "%50[^,], %50[^,], %f%*c", &studentIDs[line], &studentNames[line], &scores[line]) == 3) {
			line++;
		}	
		
		fclose(f);
		printf("Danh sach sinh vien da duoc tai tu file %s \n", FILENAME);
		return 1;
	} else {
		printf("Loi khi mo file %s. Vui long kiem tra lai vi tri file hoac ten file.\n", FILENAME);
		return 0;
	}
}

void displayTitle() {
	printf("MENU:\n");
	printf("1. Them sinh vien moi\n");
	printf("2. Hien thi danh sach sinh vien\n");
	printf("3. Tim sinh vien theo ma so\n");
	printf("4. Tinh diem trung binh\n");
	printf("5. Sap xep danh sach sinh vien (giam dan theo diem)\n");
	printf("6. Luu danh sach sinh vien vao file\n");
	printf("0. Thoat chuong trinh\n");
	printf("\n");
}


void input(int* choice) {
	while (1) 
	{
		printf("Nhap lua chon cua ban: ");
		scanf("%d", choice);		
		if(*choice >=0 && *choice <= 6) {
			break;
		} else {
			printf("\nLua chon khong hop le\n");
		}
	}
}

int validString(char* s) {
	int char_count = 0;
	int i= 0;
	while(s[i] != '\0' && s[i] != '\n') {
		if(s[i] != ' ') {
			char_count ++;
		}
		i++;
	}
	
	if(char_count == 0) return 0;
	else return 1;
}

void copyNewStudentToData(char* from, char* des) {
	int i;
	for(i = 0; i < 50; i++) {
		if(from[i] == '\0' || from[i] == '\n') {
			break;
		}
		
		des[i] = from[i];
	}
}
void remove_newline_ch(char *line) {
    int new_line = strlen(line) -1;
    if (line[new_line] == '\n')
        line[new_line] = '\0';
}
