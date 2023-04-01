#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#define MAX_STR_LEN 36
#define MAX_CMD_LEN 512
#define MAX_STUDENTS 100

#define CMD_CREATE "CREATE"
#define CMD_LOAD "LOAD"
#define CMD_PRINT "PRINT"
#define CMD_INSERT "INSERT"
#define CMD_DELETE "DELETE"
#define CMD_SEARCH "SEARCH"


class Student {
public:
	char name[MAX_STR_LEN];
	char gender;
	char location[MAX_STR_LEN];
	char department[MAX_STR_LEN];
	float gpa;
	int height;
	int weight;
};

Student* studentList;
int studentCount;

void createStudents() {
	studentList = new Student[MAX_STUDENTS];
	studentCount = 0;
}

void loadStudents(const char fileName[]) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Failed to open file %s.\n", fileName);
		return;
	}
	while (feof(fp) == 0) {
		fscanf(fp, "%s %c %s %s %f %d %d",
			studentList[studentCount].name,
			&studentList[studentCount].gender,
			studentList[studentCount].location,
			studentList[studentCount].department,
			&studentList[studentCount].gpa,
			&studentList[studentCount].height,
			&studentList[studentCount].weight);
		studentCount++;
	}
	fclose(fp);
	return;
}

void printStudents() {
	for (int i = 0; i < studentCount; i++) {
		printf("%s %c %s %s %.2f %d %d\n",
			studentList[i].name,
			studentList[i].gender,
			studentList[i].location,
			studentList[i].department,
			studentList[i].gpa,
			studentList[i].height,
			studentList[i].weight);
	}
}

void insertStudent(
	const char* name,
	const char* gender,
	const char* location,
	const char* department,
	const char* gpa,
	const char* height,
	const char* weight
) {
	strcpy(studentList[studentCount].name, name);
	studentList[studentCount].gender = gender[0];
	strcpy(studentList[studentCount].location, location);
	strcpy(studentList[studentCount].department, department);
	studentList[studentCount].gpa = atof(gpa);
	studentList[studentCount].height = atoi(height);
	studentList[studentCount].weight = atoi(weight);
	studentCount++;
}

void deleteStudent(const char* name) {

}

int main() {
	FILE* inputFile = fopen("input.txt", "r");

	char input[MAX_CMD_LEN];
	char cmd[MAX_STR_LEN];
	char param[7][MAX_STR_LEN];

	while (fgets(input, MAX_CMD_LEN, inputFile) != NULL) {
		sscanf(input, "%s%s%s%s%s%s%s%s",
			cmd,
			param[0],
			param[1],
			param[2],
			param[3],
			param[4],
			param[5],
			param[6]);
		if (strcmp(cmd, CMD_CREATE) == 0) {
			createStudents();
		}
		else if (strcmp(cmd, CMD_LOAD) == 0) {
			loadStudents(param[0]);
		}
		else if (strcmp(cmd, CMD_PRINT) == 0) {
			printStudents();
		}
		else if (strcmp(cmd, CMD_INSERT) == 0) {
			insertStudent(param[0], param[1], param[2], param[3], param[4], param[5], param[6]);
		}
		else if (strcmp(cmd, CMD_DELETE) == 0) {
			
		}
		else if (strcmp(cmd, CMD_SEARCH) == 0) {

		}
		else {
			printf("%s is not a keyword.\n", cmd);
			continue;
		}
		printf("%s done ========================================\n\n", cmd);
	}


	int studentCount = countStudents(listFile);
	Student* studentList = new Student[studentCount + MAX_CREATE_STUDENTS];

	loadStudents(listFile, studentCount, studentList);


	fclose(listFile);
	fclose(inputFile);
}