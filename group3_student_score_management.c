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
char* trimWhiteSpace(char* str);
int existStudent(const char *searchID);

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
    		char searchID[50];
    		printf("Nhap ma sinh vien: ");
    		scanf("%s", searchID);
    		searchStudents(searchID);
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
	//* Ko duoc them sinh vien khi qua gioi han 100
	if(line == 100) {
		printf("Da dat gioi han 100 sinh vien. Khong the them sinh vien.\n");
		return;
	}
	
	char id[50];
	char name[50];
	float score;

    //* Tranh loi khi dung scanf voi fgets
	getchar();	
	//* Nhap ma sv
	while(1) {
	printf("Nhap ma sinh vien: ");
	fgets(id, 50, stdin);
	if(validString(id) == 1){
		//* Bo cac dau space o dau va cuoi string:    hello   -> hello
		strcpy(id, trimWhiteSpace(id));
		//* Kiem tra xem sv da ton tai chua
		if(existStudent(id) == 1) {
			printf("Ma sinh vien da ton tai.\n");
			continue;
		}
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
		strcpy(name, trimWhiteSpace(name));
		break;	
	} else {
		printf("Ten sinh vien khong hop le.\n");
	}
	}
	
	//* Nhap diem sv
	while(1) {
	printf("Nhap diem sinh vien: ");
	int res = scanf("%f", &score);
	//* Kiem tra xem diem co phai la so thap phan ko.
	if(res > 0 && score >=0 && score <= 10){
		break;	
	} else {
		printf("Diem sinh vien khong hop le.\n");
		getchar();
	}
	}
	
	// Bo dau \n o cuoi string
	remove_newline_ch(id);
	remove_newline_ch(name);
	
	// luu vao mang
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
		// Len mang xem la biet %-10s nghia la j nha ;). Cho nay ko ghi vua
		printf("%-10s", studentIDs[i]);
		printf("%-40s", studentNames[i]);
		printf("%f", scores[i]);
		printf("\n");
	}
	printf("\n");
}

void searchStudents(const char *searchID) {
    int found = 0;
    int i;
    for (i = 0; i < line; i++) {
    	// ham strcmp kiem tra 2 string xem co giong nhau ko. Neu giong thi return 0.
        if (strcmp(studentIDs[i], searchID) == 0) {
            printf("Da tim thay sinh vien:\n");
            printf("Student ID: %s\nTen: %s\nDiem: %.2f\n", studentIDs[i], studentNames[i], scores[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Khong the tim thay sinh vien voi ID %s.\n", searchID);
    }
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
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Loi khi mo file.\n");
        return;
    }
    int i;
    for (i = 0; i < line; i++) {
        fprintf(file, "%s, %s, %f\n", studentIDs[i], studentNames[i], scores[i]);
    }
    fclose(file);
    printf("Tat ca sinh vien da duoc luu %s\n", FILENAME);
}




void sortStudents() {
    int i, j;
    float tempScore;
    char tempID[50];
    char tempName[50];

    // Bubble sort lmao
    for (i = 0; i < line - 1; i++) {
        for (j = i + 1; j < line; j++) {
            if (scores[i] < scores[j]) {
                // Swap scores
                tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                // Swap student IDs
                strcpy(tempID, studentIDs[i]);
                strcpy(studentIDs[i], studentIDs[j]);
                strcpy(studentIDs[j], tempID);

                // Swap student names
                strcpy(tempName, studentNames[i]);
                strcpy(studentNames[i], studentNames[j]);
                strcpy(studentNames[j], tempName);
            }
        }
    }
    printf("Sinh vien da duoc sap xep theo diem.\n");
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

// Load data tu file vao cac mang
int loadSavedStudents() {
	if(exists(FILENAME)) {
		FILE* f = fopen(FILENAME, "r");
		
		// %50 lay max 50 ky tu. [^,] bo dau "," khi scanf. %*c bo 1 ky tu cuoi la \n
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
	printf("5. Luu danh sach sinh vien vao file\n");
	printf("6. Sap xep danh sach sinh vien (giam dan theo diem)\n");
	printf("0. Thoat chuong trinh\n");
	printf("\n");
}


int existStudent(const char *searchID) {
    int found = 0;
    int i;
    for (i = 0; i < line; i++) {
        if (strcmp(studentIDs[i], searchID) == 0) {
            found = 1;
            break;
        }
    }
    
    return found;
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

// Kiem tra xem string co rong ko (toan dau space)
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

// Ghi 1 string vao 1 string khac
void copyNewStudentToData(char* from, char* des) {
	int i;
	for(i = 0; i < 50; i++) {
		if(from[i] == '\0' || from[i] == '\n') {
			break;
		}
		
		des[i] = from[i];
	}
	des[i] = '\0';
}
void remove_newline_ch(char *line) {
    int new_line = strlen(line) -1;
    if (line[new_line] == '\n')
        line[new_line] = '\0';
}

char* trimWhiteSpace(char* str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}
