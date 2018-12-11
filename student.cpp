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

// menu methods
void student_master();
void student_entry();
void edit_student();
void marks_entry();
void display_students();
void reports();
void students_and_marks();
void individual();
void marks_info();

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
        cout << "Do you want to cancel? [Y|n]: ";
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

    int set_name_from_user() {
        char input_buffer[8];
        // clear input_buffer
        for (int j=0; j<8; j++) input_buffer[j] = '\0';
        do {
            cout << "Enter Student Name: "; cin.getline(name, 32);
            if (strlen(name) == 31) // in case overflowed
                cin.ignore(100, '\n'); // eat chars including newline
            if (strcmp(name, "") == 0) {
                cout << "Student name cannot be blank\n";
                if (cancel_student_entry()) return 0;
            } else break;
        } while (1);
        return 1;
    }

    int set_class_from_user() {
        char input_buffer[8]; int tm_flag;
        // clear input_buffer
        for (int j=0; j<8; j++) input_buffer[j] = '\0';
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
        return 1;
    }

    int set_sec_from_user() {
        do {
            cout << "Enter Section: "; cin.getline(sec, 2);
            cin.ignore(100, '\n');
            strcpy(sec, strupr(sec)); // convert to uppercase
            if ((strcmp(sec, "") == 0) || !isalpha(sec[0])) {
                cout << "Section must be a single alphabet\n";
                if (cancel_student_entry()) return 0;
            } else break;
        } while (1);
        return 1;
    }

    int set_roll_from_user() {
        char input_buffer[8]; int tm_flag = 0;
        // clear input_buffer
        for (int j=0; j<8; j++) input_buffer[j] = '\0';
        do {
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
        return 1;
    }

    int set_data_from_user() {
        if (!set_name_from_user())  return 0;
        if (!set_class_from_user()) return 0;
        if (!set_sec_from_user())   return 0;
        if (!set_roll_from_user())  return 0;
    }

    int get_uid() { return uid; }

    void get_name(char str[]) { strcpy(str, name); }

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
        cout << "Marks in English: ";      cin >> marks[0];
        cout << "Marks in Bengali: ";      cin >> marks[1];
        cout << "Marks in Mathemathics: "; cin >> marks[2];
        cout << "Marks in Science: ";      cin >> marks[3];
        cout << "Marks in History: ";      cin >> marks[4];
        cout << "Marks in Geography: ";    cin >> marks[5];
    }

    int get_uid() { return uid; }

    void get_marks(int m[]) {
        for (int i=0; i<6; i++)
            m[i] = marks[i];
    }

    void print_details() {
        cout << "  English : "     << marks[0] << endl;
        cout << "  Bengali : "     << marks[1] << endl;
        cout << "  Mathematics : " << marks[2] << endl;
        cout << "  Science : "     << marks[3] << endl;
        cout << "  History : "     << marks[4] << endl;
        cout << "  Geography : "   << marks[5] << endl;
    }
};

int main() {
    int ch;
    char rep = 'y';

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
                student_master();
                break;
            case 2:
                marks_entry();
                break;
            case 3:
                reports();
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

void student_master() {
    int ch;
    char rep = 'y';
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
                student_entry();
                break;
            case 2:
                edit_student();
                break;
            case 3:
                display_students();
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
}

void student_entry() {
    Student goodperson, duplicate;
    char res='n';
    fstream students_fio(
        "STUDENTS.DAT",
        ios::in | ios::out
    );
    if (!students_fio) {
        cout << "Unable to open file \"STUDENTS.DAT\"\n"; getch();
        return;
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
                        return;
                    } break;
                }
            } else if (goodperson.cancel_student_entry()) {
                students_fio.close();
                return;
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
}

void edit_student() {
    clrscr();
    int uid, pos;
    cout << "Enter student UID: "; cin >> uid;
    fstream students_fio("STUDENTS.DAT", ios::in | ios::out);
    if (!students_fio) {
        cout << "Unable to read file \"STUDENTS.DAT\"\n"; getch();
        return;
    }
    Student s; int flag;
    pos = students_fio.tellg();
    while (students_fio.read((char*) &s, sizeof(s))) {
        if (s.get_uid() == uid)
            { flag = 1; break; }
        pos = students_fio.tellg();
    }
    if (!flag) {
        cout << "Student doesn't exist\n";
        students_fio.close(); getch(); return;
    }
    int res = 'y';
    do {
        clrscr();
        cout << " E D I T   S T U D E N T\n";
        cout << "=-=-=-=-=-=-=-=-=-=-=-=-=\n";
        cout << "Student UID : " << uid << endl;
        s.print_details(); cout << endl; int ch;
        cout << "1 >> Edit Name\n";
        cout << "2 >> Edit Class\n";
        cout << "3 >> Edit Section\n";
        cout << "4 >> Edit Roll no.\n";
        cout << "5 >> Delete Student\n";
        cout << "6 >> Cancel\n";
        cout << "Enter your choice: "; cin >> ch;
        cin.ignore(10, '\n'); // eat chars including newline
        int cancel_flag = 0, del_flag = 0, invalid_flag = 0;
        switch (ch) {
            case 1:
                if (!s.set_name_from_user()) cancel_flag = 1; break;
            case 2:
                if (!s.set_class_from_user()) cancel_flag = 1; break;
            case 3:
                if (!s.set_sec_from_user()) cancel_flag = 1; break;
            case 4:
                if (!s.set_roll_from_user()) cancel_flag = 1; break;
            case 5:
                int res;
                cout << "Are you sure? [Y|n]: "; res = getche();
                if (tolower(res) == 'y') del_flag = 1;
                else cancel_flag = 1; break;

            case 6: cancel_flag = 1; break;
            default:
                cout << "Invalid choice!\n"; invalid_flag = 1;
        }
        if (!cancel_flag && !invalid_flag && !del_flag) {
            students_fio.seekg(pos);
            students_fio.write((char*) &s, sizeof(s));
            cout << "\nUpdated!\n";
        } else if (!cancel_flag && !invalid_flag && del_flag) {
            // Delete student
            ofstream temp_fout;
            temp_fout.open("TEMP.DAT");
            if (!temp_fout) {
                cout << "Unable to open temporary file\n"; getch();
                return;
            }
            students_fio.seekg(0);
            while (students_fio.read((char*) &s, sizeof(s)))
                if (s.get_uid() != uid)
                    temp_fout.write((char*) &s, sizeof(s));
            students_fio.close();
            temp_fout.close();
            remove("STUDENTS.DAT");
            rename("TEMP.DAT", "STUDENTS.DAT");

            // Delete Marks Entry
            Marks m;
            ifstream marks_fin("MARKS.DAT");
            if (!marks_fin) {
                cout << "Unable to read file \"MARKS.DAT\"\n"; getch();
                return;
            }
            temp_fout.open("TEMP.DAT");
            if (!temp_fout) {
                cout << "Unable to open temporary file\n"; getch();
                return;
            }
            while (marks_fin.read((char*) &m, sizeof(m)))
                if (m.get_uid() != uid)
                    temp_fout.write((char*) &m, sizeof(m));
            marks_fin.close();
            temp_fout.close();
            remove("MARKS.DAT");
            rename("TEMP.DAT", "MARKS.DAT");

            cout << "\nDeletion complete!\n"; getch(); return;
        } else if (cancel_flag && !invalid_flag) {
            students_fio.close();
            return;
        }
        cout << "Would you like to continue? [Y|n]: "; res = getche();
    } while (tolower(res) == 'y');
    students_fio.close();
}

void display_students() {
    Student goodperson;
    ifstream fin("STUDENTS.DAT");

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
}

void marks_entry() {
    fstream marks_fio("MARKS.DAT", ios::in | ios::out);
    if (!marks_fio) {
        cout << "Unable to open file \"MARKS.DAT\"\n"; getch();
        return;
    }

    int pos;
    ifstream students_fin("STUDENTS.DAT");
    if (!students_fin) {
        cout << "Unable to read file \"STUDENTS.DAT\"\n"; getch();
        return;
    }
    Student s; Marks m, temp;
    int flag, rewrite_flag; char res='n';

    do {
        students_fin.clear(); students_fin.seekg(0); // Reset students_fin
        marks_fio.seekg(0);
        flag = 0; rewrite_flag = 0;

        clrscr();
        cout << "\t M A R K S   E N T R Y " << endl;
        cout << "\t=+=+=+=+=+=+=+=+=+=+=+=" << endl;
        m.set_student_uid_from_user();

        // If it is to be updated
        pos = marks_fio.tellg();
        while (marks_fio.read((char*) &temp, sizeof(temp))) {
            if (temp.get_uid() == m.get_uid())
                { rewrite_flag = 1; break; }
            pos = marks_fio.tellg();
        }

        // Student exists?
        while (students_fin.read((char*) &s, sizeof(s)))
            if (s.get_uid() == m.get_uid())
                { flag = 1; break; }

        if (!flag) {
            cout << "Entered UID doesn't match any existing student\n";
            cout << "Try going back and make an entry for the student\n";
            cout << "Did you mistype? [Y|n]: ";
        } else {
            if (!rewrite_flag) marks_fio.clear();
            marks_fio.seekg(pos);
            s.print_details();
            m.set_marks_from_user();
            marks_fio.write((char*) &m, sizeof(m));
            cout << "\nData written successfully!\n";
            cout << "Would you like to enter another? [Y|n]: ";
        }
        res = tolower(getche());
    } while (res == 'y');
    marks_fio.close();
    students_fin.close();
}

void reports() {
    int ch;
    char rep = 'y';
    do {
        clrscr();
        cout << "\t R E P O R T S " << endl;
        cout << "\t===============" << endl;
        cout << "1. All students and marks" << endl;
        cout << "2. Individual" << endl;
        cout << "3. Overall Marks Info" << endl;
        cout << "4. Back To Main Menu" << endl;
        cout << endl << "Your choice: "; cin >> ch;

        switch(ch) {
            case 1:
                students_and_marks();
                break;
            case 2:
                individual();
                break;
            case 3:
                marks_info();
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
}

void students_and_marks() {
    ifstream students_fin("STUDENTS.DAT");
	if (!students_fin) {
        cout << "Unable to read file \"STUDENTS.DAT\"\n"; getch();
        return;
    }
    ifstream marks_fin("MARKS.DAT");
	if (!marks_fin) {
        cout << "Unable to read file \"MARKS.DAT\"\n"; getch();
        return;
    }
    Student s; Marks m;

    clrscr();
    const int MARKS_LENGTH = 6;
    int t_width = COLUMN0_WIDTH + COLUMN1_WIDTH + 6*MARKS_LENGTH;
    line('=', t_width);
    cout << setiosflags(ios::left)
         << setw(COLUMN0_WIDTH) << "UID"
         << setw(COLUMN1_WIDTH) << "Name"
         << setiosflags(ios::right)
         << setw(MARKS_LENGTH) << "Eng"
         << setw(MARKS_LENGTH) << "Beng"
         << setw(MARKS_LENGTH) << "Math"
         << setw(MARKS_LENGTH) << "Sci"
         << setw(MARKS_LENGTH) << "Hist"
         << setw(MARKS_LENGTH) << "Geog"
         << endl;
    line('=', t_width);
    while (marks_fin.read((char*) &m, sizeof(m))) {
        int flag = 0;
        while (students_fin.read((char*) &s, sizeof(s))) {
            if (s.get_uid() == m.get_uid())
                { flag = 1; break; }
        }
        if (flag) {
            char n[32]; s.get_name(n);
            int mrks[6]; m.get_marks(mrks);
            cout << setiosflags(ios::left)
                 << setw(COLUMN0_WIDTH) << s.get_uid()
                 << setw(COLUMN1_WIDTH) << n
                 << setiosflags(ios::right)
                 << setw(MARKS_LENGTH) << mrks[0]
                 << setw(MARKS_LENGTH) << mrks[1]
                 << setw(MARKS_LENGTH) << mrks[2]
                 << setw(MARKS_LENGTH) << mrks[3]
                 << setw(MARKS_LENGTH) << mrks[4]
                 << setw(MARKS_LENGTH) << mrks[5]
                 << endl;
        }
    }
    line('=', t_width);
    students_fin.close();
	marks_fin.close();
    getch();
}

void individual() {
    ifstream students_fin("STUDENTS.DAT");
	if (!students_fin) {
        cout << "Unable to read file \"STUDENTS.DAT\"\n"; getch();
        return;
    }
    ifstream marks_fin("MARKS.DAT");
	if (!marks_fin) {
        cout << "Unable to read file \"MARKS.DAT\"\n"; getch();
        return;
    }
    Student s; Marks m;

    clrscr();

    int uid, m_flag, s_flag;
    cout << "Enter UID of Student: "; cin >> uid;

    while (marks_fin.read((char*) &m, sizeof(m))) {
        m_flag = 0;
        if (m.get_uid() == uid)
            { m_flag = 1; break; }
    }

    while (students_fin.read((char*) &s, sizeof(s))) {
        s_flag = 0;
        if (s.get_uid() == uid)
            { s_flag = 1; break; }
    }

    if (m_flag && s_flag) {
        cout << endl;
        s.print_details();
        cout << endl;
        m.print_details();
    } else if (s_flag)
        cout << "Marks information missing." << endl;
    else if (m_flag)
        cout << "Student information missing." << endl;
    else
        cout << "Student does not exist." << endl;
    getch();
}

void marks_info() {
    ifstream marks_fin("MARKS.DAT");
	if (!marks_fin) {
        cout << "Unable to read file \"MARKS.DAT\"\n"; getch();
        return;
    }
    Marks m;
    int sum[] = { 0, 0, 0, 0, 0, 0 };
    int max[] = { 0, 0, 0, 0, 0, 0 };
    int marks[6];
    int c = 0;
    while (marks_fin.read((char*) &m, sizeof(m))) {
        m.get_marks(marks);
        for (int i=0; i<6; i++) {
            if (max[i] < marks[i]) max[i] = marks[i];
            sum[i] += marks[i];
        }
        c++;
    }

    clrscr();
    cout << "\t M A R K S   I N F O \n";
    cout << "\t=====================\n";
    if (c > 0) {
        cout << "\nAVERAGE MARKS :\n";
        cout << "English : "     << sum[0] / c << endl;
        cout << "Bengali : "     << sum[1] / c << endl;
        cout << "Mathematics : " << sum[2] / c << endl;
        cout << "Science : "     << sum[3] / c << endl;
        cout << "History : "     << sum[4] / c << endl;
        cout << "Geography : "   << sum[5] / c << endl;

        cout << "\nHIGHEST MARKS :\n";
        cout << "English : "     << max[0] << endl;
        cout << "Bengali : "     << max[1] << endl;
        cout << "Mathematics : " << max[2] << endl;
        cout << "Science : "     << max[3] << endl;
        cout << "History : "     << max[4] << endl;
        cout << "Geography : "   << max[5] << endl;
    } else
        cout << "Not enough information!\n";
    getch();
}

void line(char ch, int l) {
    for (int i=0; i<l; i++)
        cout << ch;
    cout << endl;
}
