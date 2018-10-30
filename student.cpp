#include <iostream.h>
#include <iomanip.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream.h>
#include <ctype.h>
#include <stdio.h>

#define COLUMN0_WIDTH   8  // UID
#define COLUMN1_WIDTH  32  // Name
#define COLUMN2_WIDTH   6  // Class
#define COLUMN3_WIDTH  10  // Section
#define COLUMN4_WIDTH   8  // Roll No.
#define COLUMNS_WIDTH  (COLUMN0_WIDTH + COLUMN1_WIDTH + COLUMN2_WIDTH \
                        + COLUMN3_WIDTH + COLUMN4_WIDTH)

// TODO: eliminate the Feedback logic

// menu methods
void student_master(char&);
void student_entry(char&);
void marks_entry(char&);
void display_students(char&);

// utility methods
void line(char, int);

class Student {
private:
    int uid, clas, roll;
    char name[32], sec[2];

public:
    Student() {
        // assign garbage
        this->uid = 0;
        strcpy(this->name, "");
        this->clas = 0;
        strcpy(this->sec, "");
        this->roll = 0;
    }

    Student(int uid, char name[], int clas, char sec[], int roll) {
        this->uid = uid;
        strcpy(this->name, name);
        this->clas = clas;
        strcpy(this->sec, sec);
        this->roll = roll;
    }

    int cancel_student_entry() {
        cout << "Do you want to cancel adding this student? [Y|n]: ";
        if (tolower(getche()) == 'y') return 1;
        cout << endl;
        return 0;
    }

    int set_uid_from_user() {
        char input_buffer[8]; int tm_flag = 0;
        cout << "Enter Unique ID: "; cin.getline(input_buffer, 8);
        if (strlen(input_buffer) == 7) // in case overflowed
            cin.ignore(100, '\n'); // eat chars including newline
        for (int i=0; i<strlen(input_buffer); i++)
            if (!isdigit(input_buffer[i])) tm_flag = 1;
        if (!tm_flag) uid = atoi(input_buffer);
        if (tm_flag || uid < 1) {
            cout << "Student UID must be a positive integer\n";
            return 0;
        }
        return 1;
    }

    int set_data_from_user() {
        char input_buffer[8]; int tm_flag;
        do {
            cout << "Enter Student Name: "; cin.getline(name, 32);
            if (strlen(name) == 31) // in case overflowed
                cin.ignore(100, '\n'); // eat chars including newline
            if (strcmp(name, "") == 0) {
                cout << "Student name cannot be blank\n";
                if (cancel_student_entry()) return 0;
            } else break;
        } while (1);

        do {
            tm_flag = 0;
            cout << "Enter Class: "; cin.getline(input_buffer, 8);
            if (strlen(input_buffer) == 7) // in case overflowed
                cin.ignore(100, '\n'); // eat chars including newline
            for (int i=0; i<strlen(input_buffer); i++)
                if (!isdigit(input_buffer[i])) tm_flag = 1;
            if (!tm_flag) clas = atoi(input_buffer);
            if (tm_flag || clas < 1 || clas > 12) {
                cout << "Class must be a positive integer "
                    << "less than or equal to 12.\n";
                if (cancel_student_entry()) return 0;
            } else break;
        } while (1);

        do {
            cout << "Enter Section: "; cin.getline(sec, 2);
            cin.ignore(100, '\n');
            strcpy(sec, strupr(sec)); // convert to uppercase
            if ((strcmp(sec, "") == 0) || !isalpha(sec[0])) {
                cout << "Section must be a single alphabet\n";
                if (cancel_student_entry()) return 0;
            } else break;
        } while (1);

        // clear input_buffer
        for (int j=0; j<8; j++) input_buffer[j] = '\0';

        do {
            tm_flag = 0;
            cout << "Enter Roll No.: "; cin.getline(input_buffer, 8);
            if (strlen(input_buffer) == 7) // in case overflowed
                cin.ignore(100, '\n'); // eat chars including newline
            for (int i=0; i<strlen(input_buffer); i++)
                if (!isdigit(input_buffer[i])) tm_flag = 1;
            if (!tm_flag) roll = atoi(input_buffer);
            if (tm_flag || roll < 1) {
                cout << "Roll no. must be a positive integer\n";
                if (cancel_student_entry()) return 0;
            } else break;
        } while (1);
    }

    int get_uid() { return uid; }

    void print_details() {
        cout << "  Name : " << name << endl;
        cout << "  Class : " << clas << endl;
        cout << "  Section : " << sec << endl;
        cout << "  Roll No. : " << roll << endl;
    }

    void display_student_row() {
        cout << setiosflags(ios::left)
             << setw(COLUMN0_WIDTH) << uid
             << setw(COLUMN1_WIDTH) << name
             << setw(COLUMN2_WIDTH) << clas
             << setw(COLUMN3_WIDTH) << sec
             << setiosflags(ios::right)
             << setw(COLUMN4_WIDTH) << roll;
        cout << endl;
    }
};

class Marks {
private:
    int uid;
    float marks[6];

public:
    void set_student_uid_from_user() {
        cout << "Enter student UID: ";  cin >> uid;
        return;
    }

    void set_marks_from_user() {
        cout << "Marks in English: ";   cin >> marks[0];
        cout << "Marks in Bengali: ";   cin >> marks[1];
        cout << "Marks in Maths: ";     cin >> marks[2];
        cout << "Marks in Science: ";   cin >> marks[3];
        cout << "Marks in History: ";   cin >> marks[4];
        cout << "Marks in Geography: "; cin >> marks[5];
    }

    int get_uid() {
        return uid;
    }
};

int main() {
    int ch;
    char rep = 'n';

    do {
        clrscr();
        cout << "\t M A I N   M E N U " << endl;
        cout << "\t===================" << endl;
        cout << "1. Student Master" << endl;
        cout << "2. Marks Entry" << endl;
        cout << "3. Reports" << endl;
        cout << "4. Exit" << endl;
        cout << endl << "Your choice: "; cin >> ch;

        switch(ch) {
            case 1:
                student_master(rep);
                break;
            case 2:
                marks_entry(rep);
                break;
            case 3:
                // Call to Reports menu method
                break;
            case 4: exit(0);
            default:
                cout << "Incorrect choice,\n" ;
                cout << "Would you like to try again? [Y/n]: ";
                rep = tolower(getche());
        }
    } while (rep == 'y');
    getch();

    return 0;
}

void student_master(char &rmm) {
    int ch;
    char rep = 'n';
    do {
        clrscr();
        cout << "\t S T U D E N T   M A S T E R " << endl;
        cout << "\t=============================" << endl;
        cout << "1. Enter New Student" << endl;
        cout << "2. Edit Student" << endl;
        cout << "3. View" << endl;
        cout << "4. Back To Main Menu" << endl;
        cout << endl << "Your choice: "; cin >> ch;

        switch(ch) {
            case 1:
                student_entry(rep);
                break;
            case 2:
                // Code / Method call for Details Editing
                break;
            case 3:
                display_students(rep);
                break;
            case 4:
                rep = 'n';
                break;
            default:
                cout << "Invalid choice!\n";
                cout << "Would you like to try again? [Y|n]: ";
                rep = tolower(getche());
        }
    } while (rep == 'y');
    rmm = 'y'; // Feedback to caller for repetition of Main Menu
}

void student_entry(char &rsm) {
    Student goodperson, duplicate;
    char res='n';
    fstream students_fio(
        "C:\\CODES\\CPP\\STUDENT\\STUDENTS.DAT",
        ios::in | ios::out
    );
    if (!students_fio) {
        cout << "Unable to open file \"STUDENTS.DAT\"\n"; getch();
        rsm = 'y'; return;
    }
    int flag;
    cin.ignore(10, '\n'); // eat chars including newline

    do {
        clrscr();
        cout << "\t S T U D E N T   E N T R Y " << endl;
        cout << "\t=+=+=+=+=+=+=+=+=+=+=+=+=+=" << endl;
        do {
            students_fio.clear(); // Reset students_fio
            students_fio.seekg(0);  // prepare for searching
            flag = 0;

            if (goodperson.set_uid_from_user()) {
                while(students_fio.read((char*) &duplicate, sizeof(duplicate)))
                    if (duplicate.get_uid() == goodperson.get_uid())
                        { flag = 1; break; }
                if (flag) {
                    cout << "Student with similar UID already exists\n";
                    duplicate.print_details(); cout << endl;
                } else {
                    if (!goodperson.set_data_from_user()) {
                        students_fio.close();
                        rsm = 'y'; return;
                    } break;
                }
            } else if (goodperson.cancel_student_entry()) {
                students_fio.close();
                rsm = 'y'; return;
            }
        } while (1);

        if (!flag) {
            students_fio.clear();
            students_fio.seekg(0, ios::end); // prepare to append
            students_fio.write((char*) &goodperson, sizeof(goodperson));
            cout << "\nData written successfully!\n";
            cout << "Would you like to enter another? [Y|n]: ";
        } else
            cout << "Would you like to try again? [Y|n]: ";
        res = tolower(getche());
    } while (res == 'y');

    students_fio.close();
    rsm = 'y'; // Feedback to caller for repetition of Student Master
}

void display_students(char &rsm) {
    Student goodperson;
    ifstream fin("C:\\CODES\\CPP\\STUDENT\\STUDENTS.DAT");
    //const int COLUMNS_WIDTH = COLUMN0_WIDTH + COLUMN1_WIDTH + COLUMN2_WIDTH
    //                          + COLUMN3_WIDTH + COLUMN4_WIDTH;

    clrscr();
    cout << setiosflags(ios::left)
         << setw(COLUMN0_WIDTH) << "UID"
         << setw(COLUMN1_WIDTH) << "Name"
         << setw(COLUMN2_WIDTH) << "Class"
         << setw(COLUMN3_WIDTH) << "Section"
         << setiosflags(ios::right)
         << setw(COLUMN4_WIDTH) << "Roll No.";
    cout << endl;
    line('=', COLUMNS_WIDTH);

    while(fin.read((char*) &goodperson, sizeof(goodperson)))
        goodperson.display_student_row();

    line('=', COLUMNS_WIDTH);
    fin.close();
    getch();

    rsm = 'y'; // Feedback to caller for repetition of Student Master
}

void marks_entry(char &rmm) {
    // ofstream marks_fout("C:\\CODES\\CPP\\STUDENT\\MARKS.DAT", ios::app);
    ifstream students_fin("C:\\CODES\\CPP\\STUDENT\\STUDENTS.DAT");
    Student goodperson; Marks goodmarks;
    int flag; char res='n';

    do {
        students_fin.clear(); students_fin.seekg(0); // Reset students_fin
        flag = 0;

        clrscr();
        cout << "\t M A R K S   E N T R Y " << endl;
        cout << "\t=+=+=+=+=+=+=+=+=+=+=+=" << endl;
        goodmarks.set_student_uid_from_user();

        while (students_fin.read((char*) &goodperson, sizeof(goodperson)))
            if (goodperson.get_uid() == goodmarks.get_uid())
                { flag = 1; break; }

        if (!flag) {
            cout << "Entered UID doesn't match any existing student\n";
            cout << "Try going back and make an entry for the student\n";
            cout << "Did you mistype? [Y|n]: ";
        } else {
            goodperson.print_details();
            // goodmarks.set_marks_from_user();
            // marks_fout.write((char*) &goodmarks, sizeof(goodperson));
            cout << "\nData written successfully!\n";
            cout << "Would you like to enter another? [Y|n]: ";
        }
        res = tolower(getche());
    } while (res == 'y');
    // marks_fout.close();
    students_fin.close();
    rmm = 'y'; // Feedback to caller for repetition of Main Menu
}

void line(char ch, int l) {
    for (int i=0; i<l; i++)
        cout << ch;
    cout << endl;
}
