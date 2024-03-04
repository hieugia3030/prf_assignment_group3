#include <stdio.h>
#include <string.h>


#define FILENAME "students.txt"
/// maximum: 100 students
/// each students name has maximum 50 characters
char studentNames[100][50];

char studentIDs[100][50];

/// Scores must be >=0 and <=10
double scores[100];

/// Number of lines exist in the file. start from 0. (0 means there is 1 line)
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
				break;
			}
			
			case 3: {
				break;
			}
			
			case 4: {
				break;
			}
			
			case 5: {
				break;
			}
			
			case 6: {
				break;
			}
		}
	}
}
	
	return 0;
}

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
		
		while (fscanf(f, "%50[^,], %50[^,], %d%*c", &studentIDs[line], &studentNames[line], &scores[line]) == 3) {
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

void addStudent() {
	printf("\n");
	char id[50];
	char name[50];
	float score;
	
	getchar();
	printf("Nhap ma sinh vien: ");
	fgets(id, 50, stdin);
	printf("Nhap ten sinh vien: ");
	fgets(name, 50, stdin);
	printf("Nhap diem sinh vien: ");
	scanf("%f", &score);
	remove_newline_ch(id);
	remove_newline_ch(name);
	printf("Da them sinh vien: %s, %s, %f", id, name, score);
	printf("\n");
}

void remove_newline_ch(char *line) {
    int new_line = strlen(line) -1;
    if (line[new_line] == '\n')
        line[new_line] = '\0';
}
