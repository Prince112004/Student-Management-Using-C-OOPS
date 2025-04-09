#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Student {
public:
    string name;
    string rollno;
    string dob;
    string semester;

private:
    string password;

public:
    Student(string name, string rollno, string dob, string semester, string password) {
        this->name = name;
        this->rollno = rollno;
        this->dob = dob;
        this->semester = semester;
        this->password = password;

        if (isRollNumberExists(rollno)) {
            cout << "Roll Number already exists! Please try again with a different Roll Number." << endl;
            return;
        }

        ofstream file("student_data.csv", ios::app);
        if (!file) {
            cout << "Error while saving" << endl;
            return;
        }

        // Write header if file is empty
        ifstream checkFile("student_data.csv");
        if (checkFile.peek() == ifstream::traits_type::eof()) {
            file << "Name,DOB,Roll Number,Semester,Password,Subject,Subject/Marks/Grade,Hostel,Room No,Fees" << endl;
        }
        checkFile.close();

        // Save student details
        file << name << "," << dob << "," << rollno << "," << semester << "," << password <<",N/A,N/A,N/A,N/A,N/A"<< endl;
        file.close();
        cout << "Student Registered successfully!" << endl;
    }
    void getDetails() {
        cout << "Name: " << name << endl;
        cout << "DOB: " << dob << endl;
        cout << "Roll Number: " << rollno << endl;
        cout << "Semester: " << semester << endl;
    }

    static bool isRollNumberExists(const string& rollno) {
        ifstream file("student_data.csv");
        if (!file) {
            return false; // If file doesn't exist, no duplicates
        }

        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> data;
            string word;
            while (getline(ss, word, ',')) {
                data.push_back(word);
            }
            if (data.size() >= 3 && data[2] == rollno) {
                file.close();
                return true; // Roll number already exists
            }
        }
        file.close();
        return false;
    }

    static void profile(string rollno,string password) {
        ifstream file("student_data.csv");
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }

        string line;
        getline(file, line); // Skip header
        bool found = false;

        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> data;
            string word;

            while (getline(ss, word, ',')) {
                data.push_back(word);
            }

            if (data[2] == rollno && data[4] == password) {
                cout<<"************************************"<<endl;
                cout << "\nProfile Found:\n";
                cout << "Name: " << data[0] << endl;
                cout << "DOB: " << data[1] << endl;
                cout << "Roll Number: " << data[2] << endl;
                cout << "Semester: " << data[3] << endl;
                cout << "Hostel name : "<<data[7]<<endl;
                cout << "Room number : "<<data[8]<<endl;
                found = true;
                cout<<endl<<"************************************"<<endl;
                break;
            }
        }

        if (!found) {
            cout << "Invalid Roll Number or Password!" << endl;
        }
        file.close();
    }

    static void sethostel(string rollno,string pass) {
        string hname, rno;
        cin.ignore(); // Clear the buffer
    
        ifstream file("student_data.csv");
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }
    
        vector<vector<string>> students;
        string line;
        getline(file, line); // Read header
        students.push_back({line}); // Store header separately
    
        bool found = false;
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> data;
            string word;
    
            while (getline(ss, word, ',')) {
                data.push_back(word);
            }
    
            // Validate roll number and password
            if (data[2] == rollno && data[4] == pass) {
                cout << "Enter Hostel Name: ";
                getline(cin, hname);
                cout << "Enter Room Number: ";
                getline(cin, rno);
    
                data[7] = hname;  // Hostel name at column 6
                data[8] = rno;    // Room number at column 7
                cout << "Hostel and Room number updated successfully!\n";
    
                found = true;
            }
            students.push_back(data);
        }
        file.close();
    
        if (!found) {
            cout << "Student not found or invalid credentials. Please try again.\n";
            return;
        }
    
        // Write updated data back to CSV
        ofstream outFile("student_data.csv");
        if (!outFile) {
            cout << "Error saving updates!" << endl;
            return;
        }
    
        for (const auto &row : students) {
            for (size_t i = 0; i < row.size(); i++) {
                outFile << row[i];
                if (i != row.size() - 1) outFile << ",";
            }
            outFile << "\n";
        }
        outFile.close();
    }
    

    // Helper function to split CSV lines into vector
    static vector<string> splitCSV(const string &line) {
        stringstream ss(line);
        vector<string> data;
        string word;
        while (getline(ss, word, ',')) {
            data.push_back(word);
        }
        return data;
    }
    static void assignSubject(string rollno,string pass) {
        cin.ignore(); 
    
        ifstream file("student_data.csv");
        if (!file) {//if there is no file with specified name
            cout << "Error opening file!" << endl;
            return;
        }
    
        vector<vector<string>> students; //store all the updated data in an array
        string line;
        getline(file, line); // Read header
        students.push_back(splitCSV(line)); // Store header using a helper function
    
        bool found = false;
        while (getline(file, line)) {
            vector<string> data = splitCSV(line);
    
            // Validate roll number and password
            if (data[2] == rollno && data[4] == pass) {
                int n;
                cout << "Enter how many subjects you want to assign: ";
                cin >> n;
                cin.ignore(); // Clear buffer
    
                string subject = "";
                for (int i = 0; i < n; i++) {
                    string sub;
                    cout << "Enter Subject " << i + 1 << ": ";
                    getline(cin, sub);
                    subject += sub;
                    if (i != n - 1) subject += " | "; // Avoid trailing '|'
                }
                data[5] = subject; // Update Subject column
                found = true;
            }
            students.push_back(data);
        }
        file.close();
    
        if (!found) {
            cout << "Student not found or invalid credentials. Please try again.\n";
            return;
        }
    
        // Write updated data back to CSV
        ofstream outFile("student_data.csv");
        if (!outFile) {
            cout << "Error saving updates!" << endl;
            return;
        }
    
        for (const auto &row : students) {
            for (size_t i = 0; i < row.size(); i++) {
                outFile << row[i];
                if (i != row.size() - 1) outFile << ",";
            }
            outFile << "\n";
        }
        outFile.close();
        cout << "Subject Assigned Successfully.\n";
    }
    
    static void addGrades(string rno,string pass) {
        
        cin.ignore(); // Clear buffer
    
        ifstream file("student_data.csv");
        if (!file) {
            cout << "Error opening 'student_data.csv'. Please check if the file exists." << endl;
            return;
        }
    
        vector<vector<string>> students;
        string line;
        getline(file, line); // Read header
        students.push_back(splitCSV(line)); // Store header
    
        bool found = false;
        while (getline(file, line)) {
            vector<string> data = splitCSV(line);
    
            if (data[2] == rno && data[4] == pass) {
                string assignedSubject = data[5];
                vector<string> subjects;
                stringstream ss(assignedSubject);
                string temp;
    
                while (getline(ss, temp, '|')) {
                    subjects.push_back(temp);
                }
    
                // Add marks and grade
                string gradeString = "";
                for (int i = 0; i < subjects.size(); i++) {
                    string sub = subjects[i]; //current subject
                    string marks; //
                    cout << "Enter marks and grade for " << sub << " (format: marks/grade): ";
                    getline(cin, marks);
                    
                    // Validate marks/grade input
                    if (marks.find('/') == string::npos) {
                        cout << "Invalid input! Please use 'marks/grade' format." << endl;
                        return;
                    }
                    
                    gradeString += sub + '-' + marks;
                    if (i != subjects.size() - 1) gradeString += " | ";
                }
    
                data[6] = gradeString;
                found = true;
            }
            students.push_back(data);
        }
        file.close();
    
        if (!found) {
            cout << "Student not found or invalid credentials. Please try again.\n";
            return;
        }
    
        // Write updated data back to CSV
        ofstream outFile("student_data.csv", ios::trunc);
        if (!outFile) {
            cout << "Error saving updates!" << endl;
            return;
        }
    
        for (const auto &row : students) {
            for (size_t i = 0; i < row.size(); i++) {
                outFile << row[i];
                if (i != row.size() - 1) outFile << ",";
            }
            outFile << "\n";
        }
        outFile.close();
        cout << "Marks Added Successfully.\n";
    }
    

    static void setfees(string rno,string pass){
        string fe;
        cout<<"Enter fees of the student : ";
        cin>>fe;
        cin.ignore(); // Clear buffer
    
        ifstream file("student_data.csv");
        if (!file) {
            cout << "Error opening 'student_data.csv'. Please check if the file exists." << endl;
            return;
        }
    
        vector<vector<string>> students;
        string line;
        getline(file, line); // Read header
        students.push_back(splitCSV(line)); // Store header
    
        bool found = false;
        while (getline(file, line)) {
            vector<string> data = splitCSV(line);
    
            if (data[2] == rno && data[4] == pass) {
                data[9]=fe;
                found=true;
    
            }
            students.push_back(data);
        }
        file.close();
    
        if (!found) {
            cout << "Student not found or invalid credentials. Please try again.\n";
            return;
        }
    
        // Write updated data back to CSV
        ofstream outFile("student_data.csv", ios::trunc);
        if (!outFile) {
            cout << "Error saving updates!" << endl;
            return;
        }
    
        for (const auto &row : students) {
            for (size_t i = 0; i < row.size(); i++) {
                outFile << row[i];
                if (i != row.size() - 1) outFile << ",";
            }
            outFile << "\n";
        }
        outFile.close();
        cout << "Fess Added Successfully. Thank You !! \n";
    }


    
};

void registerStudent() {
    string name, dob, rollno, semester, password;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter DOB (DD/MM/YYYY): ";
    getline(cin, dob);
    cout << "Enter Roll Number: ";
    getline(cin, rollno);
    cout << "Enter Semester: ";
    getline(cin, semester);
    cout << "Enter Password: ";
    getline(cin, password);

    Student stud(name, rollno, dob, semester, password);
}
void getProfile(){
    string rollno, password;
    cout << "Enter Roll Number: ";
    cin >> rollno;
    cout << "Enter Password: ";
    cin >> password;
    Student::profile(rollno,password);
}
void Subject(){
    string rollno, password;
    cout << "Enter Roll Number: ";
    cin >> rollno;
    cout << "Enter Password: ";
    cin >> password;
    Student::assignSubject(rollno,password);
}
void hostel(){
    string rollno, password;
    cout << "Enter Roll Number: ";
    cin >> rollno;
    cout << "Enter Password: ";
    cin >> password;
    Student::sethostel(rollno,password);
}
void Grades(){
    string rollno, password;
    cout << "Enter Roll Number: ";
    cin >> rollno;
    cout << "Enter Password: ";
    cin >> password;
    Student::addGrades(rollno,password);
}
void fees(){
    string rollno,pass;
    cout<<"Enter you roll Number: ";
    cin>>rollno;
    cout<<"Enter you password: ";
    cin>>pass;
    Student::setfees(rollno,pass);

}

class Admin{



};



int main() {

    while(true){
        int a;
        cout<<"You are .....\n1. Admin\n2. Faculty\n3. Student"<<endl;
        cin>>a;
        if(a==1){
            //admin portal

            //1 Register student

            //2 Add hostel

            //3 Add Fees


            //4 Add the teachers //further discussion


        }
        else if(a==2){
            //faculty Portal

            // Add Marks
        }
        else if(a==3){
            //student portal
        }
        else if(a==4){
            //exit
        }

    
        while (true) {
            cout<<"******************************";
            cout << "\n1. Register\n2. View Profile\n3. Assign Subject\n4. Hostel\n5. Fees\n6. Add Marks\n7. Exit\nChoose: ";
            int res;
            cin >> res;
            if (res == 1) {
                registerStudent();
            } else if (res == 2) {
                getProfile();
            } else if(res==3){
                Subject();
            } else if(res==4){
                hostel();
            } else if(res==5){
                fees();
            } else if(res==6){
                Grades();
            }else if (res == 7) {
                break;
            } 
            
            else {
                cout << "Invalid Choice! Try again." << endl;
            }
        }
    }
   
}
