#define _CRT_SECURE_NO_WARNINGS

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


class StudentList {
private:
	Student* arr = nullptr;
	int size = 0;
	int cnt = 0;

	void swap(Student& s1, Student& s2) {
		Student tmp = s1;
		s1 = s2;
		s2 = tmp;
	}

	bool cmp(const Student& s1, const Student& s2) {
		return strcmp(s1.name, s2.name) > 0;
	}

	void bubbleSort() {
		for (int i = 0; i < cnt - 1; i++) {
			for (int j = i; j < cnt - 1 - i; j++) {
				if (cmp(arr[j], arr[j+1])) {
					swap(arr[j], arr[j+1]);
				}
			}
		}
	}

	void print(const Student& s) {
		printf("%s %c %s %s %.2f %d %d\n",
			s.name,
			s.gender,
			s.location,
			s.department,
			s.gpa,
			s.height,
			s.weight);
	}

	int linearSearch(const char* name) {
		for (int i = 0; i < cnt; i++) {
			if (strcmp(arr[i].name, name) == 0) {
				return i;
			}
		}
		return -1;
	}


public:
	void create() {
		size = MAX_STUDENTS;
		arr = new Student[size];
		cnt = 0;
	}

	void load(const char fileName[]) {
		FILE* fp = fopen(fileName, "r");
		if (fp == NULL) {
			printf("Failed to open file %s.\n", fileName);
			return;
		}
		while (feof(fp) == 0) {
			fscanf(fp, "%s %c %s %s %f %d %d",
				arr[cnt].name,
				&arr[cnt].gender,
				arr[cnt].location,
				arr[cnt].department,
				&arr[cnt].gpa,
				&arr[cnt].height,
				&arr[cnt].weight);
			cnt++;
		}
		fclose(fp);
		bubbleSort();
	}

	void print() {
		for (int i = 0; i < cnt; i++) {
			print(arr[i]);
		}
	}

	void insert(
		const char* name,
		const char* gender,
		const char* location,
		const char* department,
		const char* gpa,
		const char* height,
		const char* weight
	) {
		if (cnt >= size) {
			printf("Cannot add student, the list is full.\n");
			return;
		}
		Student newStudent;
		strcpy(newStudent.name, name);
		newStudent.gender = gender[0];
		strcpy(newStudent.location, location);
		strcpy(newStudent.department, department);
		newStudent.gpa = atof(gpa);
		newStudent.height = atoi(height);
		newStudent.weight = atoi(weight);
		// »ðÀÔ À§Ä¡ °áÁ¤
		int insertBefore = 0;
		while (insertBefore < cnt) {
			if (!cmp(newStudent, arr[insertBefore])) {
				break;
			}
			insertBefore++;
		}
		// »ðÀÔ °ø°£ È®º¸
		for (int i = cnt; i > insertBefore; i--) {
			swap(arr[i - 1], arr[i]);
		}
		// »ðÀÔ
		arr[insertBefore] = newStudent;
		cnt++;
	}

	void remove(const char* name) {
		int index = linearSearch(name);
		if (index == -1) {
			printf("Student with name %s is not found.\n", name);
			return;
		}
		for (int i = index; i < cnt; i++) {
			swap(arr[i], arr[i + 1]);
		}
		cnt--;
	}

	void search(const char* name) {
		int index = linearSearch(name);
		if (index == -1) {
			printf("Student with name %s is not found.\n", name);
			return;
		}
		print(arr[index]);
	}
};


int main() {
	FILE* inputFile = fopen("input.txt", "r");
	StudentList list;

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
			list.create();
		}
		else if (strcmp(cmd, CMD_LOAD) == 0) {
			list.load(param[0]);
		}
		else if (strcmp(cmd, CMD_PRINT) == 0) {
			list.print();
		}
		else if (strcmp(cmd, CMD_INSERT) == 0) {
			list.insert(param[0], param[1], param[2], param[3], param[4], param[5], param[6]);
		}
		else if (strcmp(cmd, CMD_DELETE) == 0) {
			list.remove(param[0]);
		}
		else if (strcmp(cmd, CMD_SEARCH) == 0) {
			list.search(param[0]);
		}
		else {
			printf("%s is not a keyword.\n", cmd);
			continue;
		}
		printf("%s done ========================================\n\n", cmd);
	}
	fclose(inputFile);
	return 0;
}