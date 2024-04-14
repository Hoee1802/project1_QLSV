#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

//dinh nghia kieu du lieu student co cau truc
struct student {
	string id;// ma so sinh vie
	string name;// ho va ten cua sinh vien
	string birthday;// ngay sinh
	string address;// dia chi cua sinh vien
	string sex;// gioi tinh
	string class_name;//ten lop cua sinh vien
	struct mark* mark; //1 student co 1 mark
};

// dinh nghia kieu du lieu mark (diem mon hoc) co cau truc
struct mark {
	float project1 ;
	float database;
	float oop;
	float gpa;
};


//ham doc du lie
vector<student> readFile(const string& tenFile) {
	vector<student> listOfStudents;//khai bao vector de luu danh sach sinh vien
	ifstream inFile(tenFile);//mo file de doc

	//kiem tra xem co mo file thanh cong khong
	if (!inFile.is_open()) {
		cerr << "Can't open file" << endl;
		// tra ve vector rong neu khong mo duoc file
		return listOfStudents;
	}
	string line;

	//doc tung dong trong file
	while (getline(inFile, line)) {//inFile.eof() tra ve true neu den cuoi file và tra ve false neu chua den cuoi file
		student students;
		//doc thong tin sinh vien

		students.mark = new mark;

		stringstream ss(line);//chia nho dong thanh cac truong thong tin
		getline(ss, students.id, ',');
		getline(ss, students.name, ',');
		getline(ss, students.sex, ',');
		getline(ss, students.birthday, ',');
		getline(ss, students.address, ',');
		getline(ss, students.class_name, ',');

		ss >> students.mark->project1;
		ss.ignore();

		ss >> students.mark->database;
		ss.ignore();

		ss >> students.mark->oop;
		ss.ignore();

		ss >> students.mark->gpa;
		ss.ignore();
		if (inFile.good()) {
			listOfStudents.push_back(students);
		}
		else {
			delete students.mark;
			break;
		}
	}
	inFile.close();
	return listOfStudents;
}



//ham in tieu de cot
void printHeaderColumn() {
	const int columnWidth = 10;

	// in tieu de cot
	cout << "  |---------------------------------------------------------------------------------------------------------------------------------------|\n";
	cout << "  " << setw(12) << left << "|ID"
		<< setw(25) << left << "|NAME"
		<< setw(8) << left << "|SEX"
		<< setw(15) << left << "|BIRTHDAY"
		<< setw(15) << left << "|ADDRESS"
		<< setw(25) << left << "|CLASS"
		<< setw(columnWidth) << left << "|PROJECT1"
		<< setw(columnWidth) << left << "|DATABASE"
		<< setw(columnWidth) << left << "|OOP"
		<< setw(5) << left << "|GPA  |\n";
	cout << "  |---------------------------------------------------------------------------------------------------------------------------------------|\n";

}

//ham in ra danh sach sinh vien da nhap
void printResult(struct student* students, int numberOfStudents) {
	//thiet lap chieu rong cot
	const int columnWidth = 10;

	// in tieu de cot
	printHeaderColumn();
	//in du lieu
	for (int i = 0; i < numberOfStudents; i++) {
		struct student* currentStudent = students + i;
		cout << "  |" << setw(12) << left << currentStudent->id
			<< setw(25) << left << currentStudent->name
			<< setw(8) << left << currentStudent->sex
			<< setw(15) << left << currentStudent->birthday
			<< setw(15) << left << currentStudent->address
			<< setw(25) << left << currentStudent->class_name
			<< setw(columnWidth) << left << currentStudent->mark->project1
			<< setw(columnWidth) << left << currentStudent->mark->database
			<< setw(columnWidth) << left << currentStudent->mark->oop
			<< fixed << setw(5) << left << setprecision(2) << currentStudent->mark->gpa << "|" << endl;
	}
	cout << "  |---------------------------------------------------------------------------------------------------------------------------------------|\n";


}

//ghi thong tin sinh vien vao file
void saveStudents(struct student* students, int numberOfStudents) {
	ofstream outFile("C://Users//admin//OneDrive//Desktop//SINHVIEN.txt",ios::app);//mo file de ghi tiep
	for (int i = 0; i < numberOfStudents; i++) {
		struct student* currentStudent = students + i;
		//ghi thong tin sinh vien i vao file
		outFile << currentStudent->id << ","
			<< currentStudent->name << ","
			<< currentStudent->sex << ","
			<< currentStudent->birthday << ","
			<< currentStudent->address << ","
			<< currentStudent->class_name << ","
			<< currentStudent->mark->project1 << ","
			<< currentStudent->mark->database << ","
			<< currentStudent->mark->oop << ","
			<< fixed << setprecision(2) << currentStudent->mark->gpa << endl;
	}
	outFile.close();//dong file
}

//ham kiem tra xem mssv co bi trung khi nhap hay khong
bool checkID(const string& studentID) {
	vector<student> listOfStudents = readFile("C://Users//admin//OneDrive//Desktop//SINHVIEN.txt");
	for (const auto& student : listOfStudents) {
		if (studentID == student.id) {
			cout << "\t\tID: " << studentID << " is already on the list!" << endl;
			return true;
		}
	}
	return false;
}

//ham nhap vao thong tin sinh vien
void input(struct student* students, int numberOfStudents) {
	for (int i = 0; i < numberOfStudents; i++) {//mang danh sach cac student
		struct student* currentStudent = students + i; // con tro currentStudent tro den student thu i
		cout << "\tEnter student " << i + 1 << endl;
		do {
			cout << "\t\tMSSV: ";
			cin >> currentStudent->id;//nhap mssv cua studen thu i
		} while (checkID(currentStudent->id));
		cin.ignore();
		cout << "\t\tName: ";
		getline(cin, currentStudent->name);//nhap ten cua student thu i

		cout << "\t\tSex: ";
		getline(cin, currentStudent->sex);// nhap gioi tinh 

		cout << "\t\tBirthday: ";
		getline(cin, currentStudent->birthday);//nhap ngay sinh
	
		cout << "\t\tAddress: ";
		getline(cin, currentStudent->address);//nhap dia chi
	
		cout << "\t\tClass: ";
		getline(cin, currentStudent->class_name);// nhap ten lop
		cout << endl;

		// nhap diem cua student
		currentStudent->mark = new mark;//cap phat bo nho cho mark cua student
		if (currentStudent->mark == nullptr) {
			cout << "Error allocating memory for mark." << endl;
			exit(EXIT_FAILURE);
		}

		//nhap diem project1 
		do {
			cout << "\t\tProject1's mark: ";
			cin >> currentStudent->mark->project1;
			if (currentStudent->mark->project1 > 10 || currentStudent->mark->project1 < 0) {
				cout << "\t\t\tIncorrectly entered data!\n";
			}
		} while (currentStudent->mark->project1 > 10 || currentStudent->mark->project1 < 0);// neu sai thi nhap lai

		//nhap diem database
		do {
			cout << "\t\tDatabase's mark: ";
			cin >> currentStudent->mark->database;
			if (currentStudent->mark->database > 10 || currentStudent->mark->database < 0) {
				cout << "\t\t\tIncorrectly entered data!\n";
			}
		} while (currentStudent->mark->database > 10 || currentStudent->mark->database < 0);//neu sai thi nhap lai

		//nhap diem oop
		do {
			cout << "\t\tOop's mark: ";
			cin >> currentStudent->mark->oop;
			if (currentStudent->mark->oop > 10 || currentStudent->mark->oop < 0) {
				cout << "\t\t\tIncorrectly entered data!\n";
			}
		} while (currentStudent->mark->oop > 10 || currentStudent->mark->oop < 0);//neu sai thi nhap lai

		//tinh diem trung binh
		currentStudent->mark->gpa = (currentStudent->mark->project1 + currentStudent->mark->database + currentStudent->mark->oop) / 3;
	}
	printResult(students, numberOfStudents);// in ra danh sach da nhap
}

//ham in danh sach sinh vien hien co
void showListOfStudents(vector<student> list = readFile("C://Users//admin//OneDrive//Desktop//SINHVIEN.txt")) {
	//thiet lap chieu rong cot
	const int columnWidth = 10;

	// in tieu de cot
	printHeaderColumn();

	for (const auto& students : list) {
		cout << "  |" << setw(12) << left << students.id
			<< setw(25) << left << students.name
			<< setw(8) << left << students.sex
			<< setw(15) << left << students.birthday
			<< setw(15) << left << students.address
			<< setw(25) << left << students.class_name
			<< setw(columnWidth) << left << students.mark->project1
			<< setw(columnWidth) << left << students.mark->database
			<< setw(columnWidth) << left << students.mark->oop
			<< fixed << setw(5) << left << setprecision(2) << students.mark->gpa << "|" << endl;
	}
	cout << "  |---------------------------------------------------------------------------------------------------------------------------------------|\n";

}

//ham sua thong tin sinh vien theo id
void editStudent(vector<student>& listOfStudents, const string& studentID) {
	//tim sinh vien can sua trong danh sach
	for (auto& currentStudent : listOfStudents) {
		if (currentStudent.id == studentID) {
			//hien thi thong tin hien tai
			cout << endl;
			cout << "\tCurrent information" << endl;
			cout << endl;
			const int columnWidth = 10;

			// in tieu de cot
			printHeaderColumn();

			cout << "  |" << setw(12) << left << currentStudent.id
				<< setw(25) << left << currentStudent.name
				<< setw(8) << left << currentStudent.sex
				<< setw(15) << left << currentStudent.birthday
				<< setw(15) << left << currentStudent.address
				<< setw(25) << left << currentStudent.class_name
				<< setw(columnWidth) << left << currentStudent.mark->project1
				<< setw(columnWidth) << left << currentStudent.mark->database
				<< setw(columnWidth) << left << currentStudent.mark->oop
				<< fixed << setw(5) << left << setprecision(2) << currentStudent.mark->gpa << "|" << endl;

			//nhap thong tin moi 
			cout << endl;
			cout << "\tEnter new information" << endl;
			cout << "\t\tMSSV: ";
			cin >> currentStudent.id;

			cin.ignore();
			cout << "\t\tName: ";
			getline(cin, currentStudent.name);

			cout << "\t\tSex: ";
			getline(cin, currentStudent.sex);

			cout << "\t\tBirthday: ";
			getline(cin, currentStudent.birthday);

			cout << "\t\tAddress: ";
			getline(cin, currentStudent.address);

			cout << "\t\tClass: ";
			getline(cin, currentStudent.class_name);

			cout << endl;

			currentStudent.mark = new mark;
			if (currentStudent.mark == nullptr) {
				cout << "\tError allocating memory for mark." << endl;
				exit(EXIT_FAILURE);
			}

			do {
				cout << "\t\tProject1's mark: ";
				cin >> currentStudent.mark->project1;
				if (currentStudent.mark->project1 > 10 || currentStudent.mark->project1 < 0) {
					cout << "\t\t\tIncorrectly entered data!\n";
				}
			} while (currentStudent.mark->project1 > 10 || currentStudent.mark->project1 < 0);

			do {
				cout << "\t\tDatabase's mark: ";
				cin >> currentStudent.mark->database;
				if (currentStudent.mark->database > 10 || currentStudent.mark->database < 0) {
					cout << "\t\t\tIncorrectly entered data!\n";
				}
			} while (currentStudent.mark->database > 10 || currentStudent.mark->database < 0);

			do {
				cout << "\t\tOop's mark: ";
				cin >> currentStudent.mark->oop;
				if (currentStudent.mark->oop > 10 || currentStudent.mark->oop < 0) {
					cout << "\t\t\tIncorrectly entered data!\n";
				}
			} while (currentStudent.mark->oop > 10 || currentStudent.mark->oop < 0);
			
			currentStudent.mark->gpa = (currentStudent.mark->project1 + currentStudent.mark->database + currentStudent.mark->oop) / 3;


			//luu lai thong tin da cap nhat
			ofstream outFile("C://Users//admin//OneDrive//Desktop//SINHVIEN.txt", ios::trunc); // mo file đe luu va xoa thong tin hien tai 
			if (!outFile.is_open()) {
				cerr << "\tError opening record file!";
				return;
			}

			for (const auto& updateStudent : listOfStudents) {
				outFile << updateStudent.id << ","
					<< updateStudent.name << ","
					<< updateStudent.sex << ","
					<< updateStudent.birthday << ","
					<< updateStudent.address << ","
					<< updateStudent.class_name << ","
					<< updateStudent.mark->project1 << ","
					<< updateStudent.mark->database << ","
					<< updateStudent.mark->oop << ","
					<< fixed << setprecision(2) << updateStudent.mark->gpa << endl;
			}

			outFile.close();
			cout << endl;
			cout << "\tEdit information successfully!" << endl;
			return;
		}
	}
	cout << "\tStudent with ID: " << studentID << " not found!" << endl;

}

//ham xoa sinh vien theo id
void removeStudent(vector<student>& listOfStudents, const string& studentID) {
	//duyet qua danh sach sinh vien
	for (auto it = listOfStudents.begin(); it != listOfStudents.end(); ++it) {
		//kiem tra xem sinh vien hien tai có ID trung khop
		if (it->id == studentID) {
			//neu trung khop thi xoa sinh vien
			listOfStudents.erase(it);

			//cap nhat lai file sau khi xoa
			ofstream outFile("C://Users//admin//OneDrive//Desktop//SINHVIEN.txt", ios::trunc);
			if (!outFile.is_open()) {
				cerr << "\tError opening record file!" << endl;
				return;
			}

			//ghi lai toan bo danh sach sinh vien vao file
			for (const auto& updateStudent : listOfStudents) {
				outFile << updateStudent.id << ","
					<< updateStudent.name << ","
					<< updateStudent.sex << ","
					<< updateStudent.birthday << ","
					<< updateStudent.address << ","
					<< updateStudent.class_name << ","
					<< updateStudent.mark->project1 << ","
					<< updateStudent.mark->database << ","
					<< updateStudent.mark->oop << ","
					<< fixed << setprecision(2) << updateStudent.mark->gpa << endl;
			}
			outFile.close();

			cout << "\tStudent with ID: " << studentID << " has been removed successfully!" << endl;
			return;
		}
	}

	//neu khong tim thay sinh vien co id trung thi bao sinh vien khong duoc tim thay
	cout << "\tStudent with ID: " << studentID << " not found!" << endl;
}

//ham tim kiem sinh vien co phan id nhap tu ban phim
void searchStudentByID(const vector<student>& listOfStudents, const string& studentID) {
	vector<const student*> foundStudents;
	//tim nhung sinh vien co id chua phan id da nhap
	for (const auto &currentStudent : listOfStudents) {
		//kiem tra xem mssv cua sinh vien nao chua phan studentID khong, tra ve string::npos neu ko co
		if (currentStudent.id.find(studentID) != string::npos) {
			//neu co, them con tro den sinh vien vao vector foundStudents
			foundStudents.push_back(&currentStudent);
		}
	}
	
	//kta xem damh sach co rong hay khong
	if (!foundStudents.empty()) {
		//in ra danh sach sinh vien khop
		cout << "                                               List of students with ID: " << studentID << endl;
		const int columnWidth = 10;
		printHeaderColumn();
		for (const auto& students : foundStudents) {
			cout << "  |" << setw(12) << left << students->id
				<< setw(25) << left << students->name
				<< setw(8) << left << students->sex
				<< setw(15) << left << students->birthday
				<< setw(15) << left << students->address
				<< setw(25) << left << students->class_name
				<< setw(columnWidth) << left << students->mark->project1
				<< setw(columnWidth) << left << students->mark->database
				<< setw(columnWidth) << left << students->mark->oop
				<< fixed << setw(5) << left << setprecision(2) << students->mark->gpa << "|" << endl;
		}
		cout << "  |---------------------------------------------------------------------------------------------------------------------------------------|\n";
	}
	else {
		cout << "\tNo students were found whose MSSV contains " << studentID << "!" << endl;
	}
}

//ham chuyen doi chuoi ve chu thuong
string toLowerCase(const string& str) {
	string result = str;
	transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

//ham tim kiem sinh vien theo ten
void searchStudentByName(const vector<student>& listOfStudents, const string& studentName) {
	vector<const student*> foundStudents;

	//chuyen studentName ve chu thuong
	string lowerStudentName = toLowerCase(studentName);

	for (const auto& currentStudent : listOfStudents) {
		string lowerCurrentStudentName = toLowerCase(currentStudent.name);

		if (lowerCurrentStudentName.find(lowerStudentName) != string::npos) {
			foundStudents.push_back(&currentStudent);
		}
	}

	if (!foundStudents.empty()) {
		//in ra danh sach sinh vien khop
		cout << "                                               List of students with name: " << studentName << endl;
		const int columnWidth = 10;
		printHeaderColumn();
		for (const auto& students : foundStudents) {
			cout << "  |" << setw(12) << left << students->id
				<< setw(25) << left << students->name
				<< setw(8) << left << students->sex
				<< setw(15) << left << students->birthday
				<< setw(15) << left << students->address
				<< setw(25) << left << students->class_name
				<< setw(columnWidth) << left << students->mark->project1
				<< setw(columnWidth) << left << students->mark->database
				<< setw(columnWidth) << left << students->mark->oop
				<< fixed << setw(5) << left << setprecision(2) << students->mark->gpa << "|" << endl;
		}
		cout << "  |---------------------------------------------------------------------------------------------------------------------------------------|\n";
	}
	else {
		cout << "\tNo students were found whose name contains " << studentName << "!" << endl;
	}
}

//ham cat ho ten
string separateName(const string& studentName,int i) {//i=0 la ho, i=1 la ten dem, i=2 la ten chinh
	vector<string> result;//khai bao vecto de luu ket qua tach voi vi tri dau vecto là ho, vi tri cuoi la ten, con lai la ten dem
	
	istringstream iss(studentName); //doc tung tu trong chuoi 
	string word;
	
	while (iss >> word) {//doc tung tu trong chuoi va gan cho word
		result.push_back(word);//thanh cong thi them tu vao vecto result
	}

	//neu ten co nhieu hon 3 tu 
	if (result.size() >= 3) {
		if (i == 0) {
			return result[0];
		}
		if (i == 2) {
			return result.back();
		}
		if (i == 1) {
			string middle_name;
			for (size_t i = 1; i < result.size() - 1; i++) {
				middle_name += result[i] + " ";
			}
			return middle_name;
		}
	}
	if (result.size() == 2) {
		if (i == 0) {
			return result[0];
		}
		if (i == 2) {
			return result[1];
		}
	}
}

//ham so sanh tuy chinh cho viec sap xep theo ten va ho
bool compareByName(const student& a, const student& b) {
	if (separateName(a.name, 2) == separateName(b.name, 2)) {
		if (separateName(a.name, 0) == separateName(b.name, 0)) {
			return separateName(a.name, 1) < separateName(b.name, 1);
		}
		return separateName(a.name, 0) < separateName(b.name, 0);
	}
	return separateName(a.name, 2) < separateName(b.name, 2);
}

//tuy chinh sap xep gpa tang dan hoac giam dan
bool compareByGPAascending(const student& a, const student& b) {
		return a.mark->gpa < b.mark->gpa; //tang dan
}
bool compareByGPAdescending(const student& a, const student& b) {
	return a.mark->gpa > b.mark->gpa; //giam dan
}
int main() {
	int numberOfStudents;// khai bao so student nhap vao
	struct student* students; // khai bao con tro students tro vao phan tu dau tien trong danh sach student nhap vao 
	
	// tao "sonsole menu":
		char choice;
		do {
			cout << "                     " << "|-----------------------------------------------------------------------------------------|\n";
			cout << "                     " << "|                                  STUDENT MANAGEMENT                                     |\n";
			cout << "                     " << "|-----------------------------------------------------------------------------------------|\n";
			cout << "                     " << "|                            1. Show the list of available students                       |\n";
			cout << "                     " << "|                            2. Add students to the list                                  |\n";
			cout << "                     " << "|                            3. Remove students from the list                             |\n";
			cout << "                     " << "|                            4. Edit student's information                                |\n";
			cout << "                     " << "|                            5. Sort students by name                                     |\n";
			cout << "                     " << "|                            6. Sort students by GPA                                      |\n";
			cout << "                     " << "|                            7. Search students by name                                   |\n";
			cout << "                     " << "|                            8. Search students by ID                                     |\n";
			cout << "                     " << "|                            0. Exit the program                                          |\n";
			cout << "                     " << "|-----------------------------------------------------------------------------------------|\n";
			cout << endl;

			cout << "Enter your choice: ";
			fflush(stdin);//xoa bo nho dem
			//bo qua lenh enter
			choice = getchar(); //nhap lua chon tu ban phim
			while (choice == '\n') {
				choice = getchar();
			}
			cout << endl;

			vector<student> listOfStudents = readFile("C://Users//admin//OneDrive//Desktop//SINHVIEN.txt");
			string studentID;
			string studentName;

			switch (choice) {
			case '1':
				cout << "You chosse show the list of available students!\n" << endl;
				cout << "                                                          STUDENTS LIST\n" << endl;
				showListOfStudents();
				break;

			case '2':
				cout << "You choose add student!\n";
				cout << endl;
				cout << "\tNumber of sudents: ";
				cin >> numberOfStudents; // nhap vao so student
				cout << endl;
				// cap phat bo nho cho tung day so luong student
				students = new student[numberOfStudents];
				input(students, numberOfStudents);//nhap thong tin
				saveStudents(students, numberOfStudents);//ghi vào file
				break;

			case '3':
				cout << "You choose remove student!\n";
				cout << endl;

				do {
					cout << "\tEnter MSSV: ";
					cin >> studentID;
					cout << endl;
					removeStudent(listOfStudents, studentID);
					cout << endl;
					cout << "\tYou want to countinue deleting students! (Press any key)\n";
					cout << "\tYou want to exit the deleting program! (Press 'n' or 'N')\n";
					cout << endl;
					cout << "\tEnter your choice: ";
					fflush(stdin);//xoa bo nho dem
					choice = getchar(); //nhap lua chon tu ban phim
					while (choice == '\n') {
						choice = getchar();
					}
					cout << endl;
					if (choice == 'n' || choice == 'N') {
						cout << "\tYou have exited the deleting program!\n";
					}
					cout << endl;
				} while (choice != 'n' && choice != 'N');
				break;

			case '4':
				cout << "You choose edit student's information!\n";
				cout << endl;
				do {
					cout << "\tEnter MSSV: ";
					cin >> studentID;
					cout << endl;
					editStudent(listOfStudents, studentID); 
					cout << "\tYou want to continue edit student's information! (Press any key)\n";
					cout << "\tYou want to exit program! (Press 'n' or 'N')\n";
					cout << endl;
					cout << "\tEnter your choice: ";
					fflush(stdin);
					choice = getchar();
					while (choice == '\n') {
						choice = getchar();
					}
					cout << endl;
					if (choice == 'n' || choice == 'N') {
						cout << "\tYou have exited program!";
					}
					cout << endl;
				} while (choice != 'n' && choice != 'N');
				break; 

			case '5':
				cout << "You choose sort students by name!\n";
				cout << endl;
				sort(listOfStudents.begin(), listOfStudents.end(), compareByName);
				cout << "	                                      List of students sorted by name" << endl;
				cout << endl;
				showListOfStudents(listOfStudents);
				break;

			case '6':
				cout << "You choose sort students by GPA!\n";
				cout << endl;
				cout << "\tYou want to sort GPA in ascending order! (Press 't' or 'T')\n";
				cout << "\tYou want to sort GPA in descending order! (Press 'g' or 'G')\n";
				cout << "\tYou want to exit the sorting program! (Press 'n' or 'N')\n";
				cout << endl;
				do {
					cout << "\tEnter your choice: ";
					fflush(stdin);//xoa bo nho dem80
					//bo qua lenh enter
					choice = getchar(); //nhap lua chon tu ban phim
					while (choice == '\n') {
						choice = getchar();
					}
					cout << endl;
					if (choice == 't' || choice == 'T') {
						sort(listOfStudents.begin(), listOfStudents.end(), compareByGPAascending);
						cout << "                                               List of students sort by GPA in ascending order" << endl;
						cout << endl;
						showListOfStudents(listOfStudents);
						cout << endl;

					}
					else if (choice == 'g' || choice == 'G') {
						sort(listOfStudents.begin(), listOfStudents.end(), compareByGPAdescending);
						cout << "                                               List of students sort by GPA in descending order" << endl;
						cout << endl;
						showListOfStudents(listOfStudents);
						cout << endl;
					}
					else if (choice == 'n' || choice == 'N') {
						cout << "\tYou have exited the GPA sorting program!";
						cout << endl;
					}
					else {
						cout << "\tYour selection is invalid!" << endl;
					}
				} while (choice != 'n' && choice != 'N');
				break;


			case '7':
				do {
					cout << "You choose search students by name!\n";
					cout << endl;
					cout << "\tEnter Name: ";
					cin >> studentName;
					cout << endl;
					searchStudentByName(listOfStudents, studentName);
					cout << endl;
					cout << "\tYou want to continue search students by name! (Press any key)\n";
					cout << "\tYou want to exit program! (Press 'n' or 'N')\n";
					cout << endl;
					cout << "\tEnter your choice: ";
					fflush(stdin);
					choice = getchar();
					while (choice == '\n') {
						choice = getchar();
					}
					cout << endl;
					if (choice == 'n' || choice == 'N') {
						cout << "\tYou have exited program!";
					}
					cout << endl;
				} while (choice != 'n' && choice != 'N');
				break;

			case '8':
				do {
					cout << "You choose search students by ID!\n";
					cout << endl;
					cout << "\tEnter MSSV: ";
					cin >> studentID;
					cout << endl;
					searchStudentByID(listOfStudents, studentID);
					cout << endl;
					cout << "\tYou want to continue edit student's information! (Press any key)\n";
					cout << "\tYou want to exit program! (Press 'n' or 'N')\n";
					cout << endl;
					cout << "\tEnter your choice: ";
					fflush(stdin);
					choice = getchar();
					while (choice == '\n') {
						choice = getchar();
					}
					cout << endl;
					if (choice == 'n' || choice == 'N') {
						cout << "\tYou have exited program!";
					}
					cout << endl;
				} while (choice != 'n' && choice != 'N');
				break;

			default:
				cout << "You choose exit the program!\n";
				break;
			}

			cout << endl;

			cout << "Do you want to continue?\n";
			cout << "Yes, I do (Press any key)\n"; // tiep tuc thi chon y hoac Y
			cout << "No, I don't (Press 'n' or 'N')\n"; // khong tiep tuc thi chon n hoac N
			cout << "Clear the screen and continue (Press 'c' or 'C')\n";// tiep tuc va xoa man hinh
			
			cout << endl;

			cout << "Your choice: ";

			fflush(stdin); //xoa bo nho dem
			// bo qua lenh enter
			choice = getchar();
			while (choice == '\n') {
				choice = getchar();
			}

			if (choice == 'c' || choice == 'C') {
				system("cls");//xóa màn hình
			}
		} while (choice != 'n' && choice != 'N'); // chua chon thoat thi van tiep tuc cac lua chon tiep theo
}