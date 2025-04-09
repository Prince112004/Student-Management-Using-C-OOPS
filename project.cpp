
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include<unordered_map>
#include <iomanip>
#include <algorithm>    
#include <cctype>       
using namespace std;

class Admin{
    
    public:
        static void regist(string name, string rollno, string dob, string semester, string password){
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

        static bool isFacultyExists(const string& id) {
            ifstream file("faculty_data.csv");
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
                if (data.size() >= 3 && data[1] == id) {
                    file.close();
                    return true; // Roll number already exists
                }
            }
            file.close();
            return false;
        }
        
        static void profile(string rollno) {
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
    
                if (data[2] == rollno) {
                    cout << "=============================================\n";
                    cout << "|                Student Profile            |\n";
                    cout << "=============================================\n";
                    cout << left << setw(20) << "Name:" << data[0] << endl;
                    cout << left << setw(20) << "Date of Birth:" << data[1] << endl;
                    cout << left << setw(20) << "Roll Number:" << data[2] << endl;
                    cout << left << setw(20) << "Semester:" << data[3] << endl;
                    cout << left << setw(20) << "Hostel Name:" << data[7] << endl;
                    cout << left << setw(20) << "Room Number:" << data[8] << endl;
                    cout << "=============================================\n";
                    found=true;
                    break;
                }
            }
    
            if (!found) {
                cout << "Invalid Roll Number or Password!" << endl;
            }
            file.close();
        }

        static vector<string> splitCSV(const string &line) {
            stringstream ss(line);
            vector<string> data;
            string word;
            while (getline(ss, word, ',')) {
                data.push_back(word);
            }
            return data;
        }
    
        static void sethostel(string rollno) {
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
            students.push_back(splitCSV(line)); // Store header
        
            bool found = false;
            while (getline(file, line)) {
                vector<string> data = splitCSV(line);
        
                // Validate roll number
                if (data[2] == rollno) {
                    cout << "Enter Hostel Name: ";
                    getline(cin, hname);
                    cout << "Enter Room Number: ";
                    getline(cin, rno);
        
                    // Room number validation: must be digits only
                    if (!all_of(rno.begin(), rno.end(), ::isdigit)) {
                        cout << "Invalid Room Number! Please enter a positive number only.\n";
                        return;
                    }
        
                    data[7] = hname;  // Hostel name
                    data[8] = rno;    // Room number
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
        }

        
        
        static void assignSubject(string rollno) {
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
                if (data[2] == rollno) {
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
        
        static void addGrades(string rno) {
            
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
        
                if (data[2] == rno) {
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
        
        static void setfees(string rno){
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
        
                if (data[2] == rno) {
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
        
        static void faculty(string name,string fid,string fpass,string subject,string email,string phno,string designation,string department,string qualification,string exp){
            if (isFacultyExists(fid)) {
                cout<< "================================================================================"<<endl;
                cout << "                       Faculty already exists!! Thank you                     " << endl;
                cout<< "================================================================================"<<endl;
                return;
            }
    
            ofstream file("faculty_data.csv", ios::app);
            if (!file) {
                cout << "Error while saving" << endl;
                return;
            }
    
            // Write header if file is empty
            ifstream checkFile("faculty_data.csv");
            if (checkFile.peek() == ifstream::traits_type::eof()) {
                file << "Faculty Name,Faculty ID,Faculty Password,Subject Taught,Email,Phone Number,Department,Designation,Qualification,Experience" << endl;
            }
            checkFile.close();
    
            // Save student details
            file << name << "," << fid << "," << fpass << "," << subject << "," << email <<"," << phno <<","<< department <<","<< designation <<","<< qualification <<","<< exp << endl;
            file.close();
            cout << "===================================================\n";
            cout << "|               Faculty Added !!!                 |\n";
            cout << "===================================================\n";
        }
        
        static void deleteFac(string id){
            ifstream file("faculty_data.csv");
            if (!file.is_open()) {
                cout << "Error opening faculty data file!" << endl;
                return;
            }

            vector<string> rows;
            string line;

            // Read the header
            getline(file, line);
            rows.push_back(line); // Keep the header

            bool found = false;
            
            while (getline(file, line)) {
                stringstream ss(line);
                vector<string> data;
                string word;

                while (getline(ss, word, ',')) {
                    data.push_back(word);
                }

                // Check if the Faculty ID matches
                if (data.size() > 1 && data[1] == id) {
                    found = true;
                    cout << "Faculty with ID " << id << " has been deleted successfully." << endl;
                } else {
                    rows.push_back(line); // Keep other rows
                }
            }

            file.close();

            if (!found) {
                cout << "===================================================\n";
                cout << "     Faculty with ID " << id << " not found.        " << endl;
                cout << "===================================================\n";
                
                return;
            }

            // Write updated data to the file
            ofstream outFile("faculty_data.csv");
            if (!outFile.is_open()) {
                cout << "Error opening faculty data file for writing!" << endl;
                return;
            }

            for (const auto& row : rows) {
                outFile << row << "\n";
            }

            outFile.close();
            cout << "===================================================\n";
            cout << "|                 Faculty Deleted !!               |\n";
            cout << "===================================================\n";
        }

        static void deletStud(string id){
            ifstream file("student_data.csv");
            if (!file.is_open()) {
                cout << "Error opening Student data file!" << endl;
                return;
            }

            vector<string> rows;
            string line;

            // Read the header
            getline(file, line);
            rows.push_back(line); // Keep the header

            bool found = false;
            
            while (getline(file, line)) {
                stringstream ss(line);
                vector<string> data;
                string word;

                while (getline(ss, word, ',')) {
                    data.push_back(word);
                }

                // Check if the Faculty ID matches
                if (data.size() > 1 && data[2] == id) {
                    found = true;
                    cout << "Student with ID " << id << " has been deleted successfully." << endl;
                } else {
                    rows.push_back(line); // Keep other rows
                }
            }

            file.close();

            if (!found) {
                cout << "===================================================\n";
                cout << "     Student with Roll no  " << id << " not found.        " << endl;
                cout << "===================================================\n";
                
                return;
            }

            // Write updated data to the file
            ofstream outFile("student_data.csv");
            if (!outFile.is_open()) {
                cout << "Error opening faculty data file for writing!" << endl;
                return;
            }

            for (const auto& row : rows) {
                outFile << row << "\n";
            }

            outFile.close();
            cout << "===================================================\n";
            cout << "|                 Student Deleted !!               |\n";
            cout << "===================================================\n";

        }

        static void displayFacultyProfile(string id) {
            ifstream file("faculty_data.csv");
            if (!file.is_open()) {
                cout << "Error opening faculty data file!" << endl;
                return;
            }
        
            string line;
            getline(file, line); // Skip the header
        
            bool found = false;
        
            while (getline(file, line)) {
                stringstream ss(line);
                vector<string> data;
                string word;
        
                while (getline(ss, word, ',')) {
                    data.push_back(word);
                }
        
                // Verify ID and Password
                if (data.size() >= 10 && data[1] == id) {
                    found = true;
                    
                    // Display Faculty Profile
                    cout << "====================================================\n";
                    cout << "|                  Faculty Profile                 |\n";
                    cout << "====================================================\n";
                    cout << left << setw(20) << "Faculty Name:" << data[0] << endl;
                    cout << left << setw(20) << "Faculty ID:" << data[1] << endl;
                    cout << left << setw(20) << "Subject Taught:" << data[3] << endl;
                    cout << left << setw(20) << "Email:" << data[4] << endl;
                    cout << left << setw(20) << "Phone Number:" << data[5] << endl;
                    cout << left << setw(20) << "Department:" << data[6] << endl;
                    cout << left << setw(20) << "Designation:" << data[7] << endl;
                    cout << left << setw(20) << "Qualification:" << data[8] << endl;
                    cout << left << setw(20) << "Experience:" << data[9] << endl;
                    cout << "====================================================\n";
                    break;
                }
            }
        
            if (!found) {
                cout << "Invalid Faculty ID or Password!" << endl;
            }
        
            file.close();
        }



};

class Student{


    public:

        static void viewResult(string id,string pass){
            cin.ignore();

            ifstream file("student_data.csv");
            if(!file.is_open()){
                cout<<"Error in opening file..!!"<<endl;
                return;
            }

            string line;
            getline(file, line); // Skip header

            while(getline(file,line)){
                stringstream ss(line);
                vector<string> data;
                string word;

                while(getline(ss,word,',')){
                    data.push_back(word);
                }

                if(data[2]==id && data[4]==pass ){
                    if(data[6]=="N/A"){
                        cout << "=====================================================================\n";
                        cout << "|                          Academic Results                          |\n";
                        cout << "=====================================================================\n";
                        cout<<endl;
                        cout << "             No Result have been added. Thank you !!                 \n";
                        cout<<endl;
                        cout << "---------------------------------------------------------------------\n";

                    }
                    else{

                    
                        cout << "=====================================================================\n";
                        cout << "|                          Academic Results                          |\n";
                        cout << "=====================================================================\n";
                        stringstream resultSS(data[6]); // Assuming results are stored in data[6]
                        string subjectData;
                        cout << left << setw(45) << "Subject" 
                            << setw(10) << "Score" 
                            << setw(10) << "Grade" << endl;
                        cout << "---------------------------------------------------------------------\n";

                        while (getline(resultSS, subjectData, '|')) {
                            stringstream subjectSS(subjectData);
                            string subject, score, grade;
                            getline(subjectSS, subject, '-');
                            getline(subjectSS, score, '/');
                            getline(subjectSS, grade);

                            cout << left << setw(45) << subject
                                << setw(10) << score
                                << setw(10) << grade << endl;
                        }
                        cout << "=====================================================================\n";
                        file.close();
                        return;
                    }
                }
            }
            file.close();
            


        }
        static void viewCourses(string id,string pass){
            cin.ignore();

            ifstream file("student_data.csv");
            if(!file.is_open()){
                cout<<"Error in opening file..!!"<<endl;
                return;
            }

            string line;
            getline(file, line); // Skip header

            while(getline(file,line)){
                stringstream ss(line);
                vector<string> data;
                string word;

                while(getline(ss,word,',')){
                    data.push_back(word);
                }

                if(data[2]==id && data[4]==pass ){
                    if(data[5]=="N/A"){
                        cout << "===============================================================================\n";
                        cout << "|                             Subject Assigned                                 |\n";
                        cout << "===============================================================================\n";
                        cout<<endl;
                        cout << "                   No Subject have been added. Thank you !!                     \n";
                        cout<<endl;
                        cout << "-------------------------------------------------------------------------------\n";
                    }
                    else{

                    
                        cout << "===============================================================================\n";
                        cout << "|                            Subject Assigned                                  |\n";
                        cout << "===============================================================================\n";
                        stringstream resultSS(data[5]); // Assuming results are stored in data[6]
                        string subjectData;
                        cout << left << setw(40) << "Subject" 
                            << setw(20) << "Faculty " 
                            << setw(15) << "Subject code" << endl;
                        cout << "-------------------------------------------------------------------------------\n";

                        while (getline(resultSS, subjectData, '|')) {
                            stringstream subjectSS(subjectData);
                            string subject, score, grade;
                            getline(subjectSS, subject, '-');
                            // getline(subjectSS, score, '/');
                            // getline(subjectSS, grade);

                            cout << left << setw(45) << subject <<endl;
                                // << setw(10) << score
                                // << setw(10) << grade << endl;
                        }
                        cout << "===============================================================================\n";
                        file.close();
                        return;
                    }
                }
            }
            file.close();
            

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
                    cout << "=============================================\n";
                    cout << "|                Student Profile            |\n";
                    cout << "=============================================\n";
                    cout << left << setw(20) << "Name:" << data[0] << endl;
                    cout << left << setw(20) << "Date of Birth:" << data[1] << endl;
                    cout << left << setw(20) << "Roll Number:" << data[2] << endl;
                    cout << left << setw(20) << "Semester:" << data[3] << endl;
                    cout << left << setw(20) << "Hostel Name:" << data[7] << endl;
                    cout << left << setw(20) << "Room Number:" << data[8] << endl;
                    cout << "=============================================\n";
                    found=true;
                    break;
                }
            }
    
            if (!found) {
                cout << "Invalid Roll Number or Password!" << endl;
            }
            file.close();
        }

    
    
        static void viewFees(string id, string pass) {
        
            cin.ignore();
        
            ifstream file("student_data.csv");
            if (!file.is_open()) {
                cout << "Error in opening file..!!" << endl;
                return;
            }
        
            vector<vector<string>> records; // Store all records for rewriting
            string line;
            getline(file, line); // Read header
        
            records.push_back({line}); // Store header
        
            bool found = false;
        
            while (getline(file, line)) {
                stringstream ss(line);
                vector<string> data;
                string word;
        
                while (getline(ss, word, ',')) {
                    data.push_back(word);
                }
        
                if (data.size() < 10) {
                    cout << "Invalid data format in CSV." << endl;
                    continue;
                }
        
                if (data[2] == id && data[4] == pass) {
                    found = true;
                    if (data[9] == "N/A" || data[9] == "Paid") {
                        cout << "===============================================================================\n";
                        cout << "|                                Fees Detail                                   |\n";
                        cout << "===============================================================================\n";
                        cout<<endl<<endl;
                        cout << "\n                             No Dues. Thank you !!                              \n";
                        cout<<endl<<endl;
                        cout << "\n-------------------------------------------------------------------------------\n";
                    } else {
                        cout << "===============================================================================\n";
                        cout << "|                             Fees Detail                                      |\n";
                        cout << "===============================================================================\n";
                        cout<<endl<<endl;
                        cout << setw(20) << "Fees Due:" << setw(45) << data[9] << endl;
                        cout<<endl<<endl;
                        cout << "\n-------------------------------------------------------------------------------\n";
        
                        cout << "Want to pay fees?\n1. Yes\n2. No\nChoose: ";
                        int res;
                        cin >> res;
        
                        if (res == 1) {
                            string amount=data[9];
                            data[9] = "Paid"; // Update fees status
                            cout << "===============================================================================\n";
                            cout << "|                          Fees Paid Successfully!                               |\n";
                            cout << "===============================================================================\n";
                            cout << "\n                           Payment Details\n";
                            cout << "\n-------------------------------------------------------------------------------\n";
                            cout<<endl<<endl;
                            cout << setw(20) << "Name:" << setw(25) << data[0] << endl;
                            cout << setw(20) << "Roll Number:" << setw(25) << data[2] << endl;
                            cout << setw(20) << "Amount Paid:" << setw(25) << amount << endl;
                            cout<<endl<<endl;
                            cout << "\n-------------------------------------------------------------------------------\n";
                        } else {
                            cout << "\nExiting without payment.\n";
                        }
                    }
                }
                records.push_back(data);
            }
        
            file.close();
        
            if (!found) {
                cout << "Invalid ID or Password!" << endl;
                return;
            }
        
            // Update the CSV file
            ofstream outFile("student_data.csv");
            if (!outFile.is_open()) {
                cout << "Error in opening file for writing!" << endl;
                return;
            }
        
            for (const auto& row : records) {
                for (size_t i = 0; i < row.size(); i++) {
                    outFile << row[i];
                    if (i != row.size() - 1) outFile << ",";
                }
                outFile << "\n";
            }
        
            outFile.close();
        }
};

class Faculty{

    public:
    static void addGrades(string rno) {
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

            if (data[2] == rno) {
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
                    string sub = subjects[i]; // current subject
                    string marks;
                    cout << "Enter marks and grade for " << sub << " (format: marks/grade): ";
                    getline(cin, marks);

                    // Validate marks/grade input
                    if (marks.find('/') == string::npos) {
                        cout << "Invalid input! Please use 'marks/grade' format." << endl;
                        return;
                    }

                    size_t slashPos = marks.find('/');
                    string markPart = marks.substr(0, slashPos);

                    // Check if marks are digits and non-negative
                    if (!all_of(markPart.begin(), markPart.end(), ::isdigit)) {
                        cout << "Invalid marks! Please enter a non-negative number for marks." << endl;
                        return;
                    }

                    gradeString += sub + '-' + marks;
                    if (i != subjects.size() - 1) gradeString += " | ";
                }

                data[6] = gradeString; // Assuming grade is in column index 6
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

        for (const auto& row : students) {
            for (size_t i = 0; i < row.size(); i++) {
                outFile << row[i];
                if (i != row.size() - 1) outFile << ",";
            }
            outFile << "\n";
        }

        outFile.close();
        cout << "Marks Added Successfully.\n";
    }

    // Helper function to split CSV line
    static vector<string> splitCSV(const string& line) {
        stringstream ss(line);
        vector<string> data;
        string word;
        while (getline(ss, word, ',')) {
            data.push_back(word);
        }
        return data;
    }
};

//bool verify admin
pair<bool, string> verifyAdmin(string id, string password) {
    ifstream adminFile("admin.csv");
    if (!adminFile.is_open()) {
        cout << "Error in opening the file" << endl;
        return make_pair(false, "");
    }

    string line;
    getline(adminFile, line); // Skip the header line

    while (getline(adminFile, line)) {
        stringstream ss(line);
        string name, a, pass;

        getline(ss, name, ','); // Extract name
        getline(ss, a, ',');    // Extract id
        getline(ss, pass, ','); // Extract password

        // Verify ID and password
        if (a == id && pass == password) {
            return make_pair(true, name);
        }
    }

    cout << "Incorrect ID or Password" << endl;
    return make_pair(false, "");
}

void registerStudent(){
    string name, dob, rollno, semester, password;
    cout << "=============================================\n";
    cout << "|               Register Student             |\n";
    cout << "=============================================\n";
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter DOB (DD/MM/YYYY): ";
    getline(cin, dob);
    
    // Validate roll number (positive integer only)
    while (true) {
        cout << "Enter Roll Number (positive number only): ";
        getline(cin, rollno);
        if (!rollno.empty() && all_of(rollno.begin(), rollno.end(), ::isdigit) && stoi(rollno) > 0)
            break;
        cout << "Invalid Roll Number. Please enter a positive number.\n";
    }

    // Validate semester (positive integer only)
    while (true) {
        cout << "Enter Semester (positive number only): ";
        getline(cin, semester);
        if (!semester.empty() && all_of(semester.begin(), semester.end(), ::isdigit) && stoi(semester) > 0)
            break;
        cout << "Invalid Semester. Please enter a positive number.\n";
    }

    cout << "Enter Password: ";
    getline(cin, password);

    Admin::regist(name, rollno, dob, semester, password);
}

void viewProfile(){
    string rollno, password;
    cout << "Enter Roll Number: ";
    cin >> rollno;
    Admin::profile(rollno);
}
void assignSubject(){
    cout << "=============================================\n";
    cout << "|               Assign Subject              |\n";
    cout << "=============================================\n";
    string rollno;
    cout << "Enter Roll Number: ";
    cin >> rollno;
    Admin::assignSubject(rollno);
}
void assignHostel(){
    cout << "=============================================\n";
    cout << "|               Assign Hostel               |\n";
    cout << "=============================================\n";
    string rollno;
    cout << "Enter Roll Number: ";
    cin >> rollno;
    Admin::sethostel(rollno);
}
void setFees(){
    cout << "=============================================\n";
    cout << "|                 Set Fees                  |\n";
    cout << "=============================================\n";
    string rollno;
    cout<<"Enter you roll Number: ";
    cin>>rollno;
    Admin::setfees(rollno);
}
void addfaculty(){
    string name,fid,fpass,subject,email,phno,designation,department,qualification,exp;
    cout << "===================================================\n";
    cout << "|                   Add Faculty                    |\n";
    cout << "===================================================\n";
    
    cout << "Enter Faculty Name: ";
    getline(cin >> ws, name); // 'ws' clears input buffer
    cout << "Enter Faculty ID: ";
    getline(cin, fid);
    cout << "Enter Password: ";
    getline(cin, fpass);
    cout << "Enter Subject Taught: ";
    getline(cin, subject);
    cout << "Enter Email: ";
    getline(cin, email);
    cout << "Enter Phone Number: ";
    getline(cin, phno);
    cout << "Enter Department: ";
    getline(cin, department);
    cout << "Enter Designation: ";
    getline(cin, designation);
    cout << "Enter Qualification: ";
    getline(cin, qualification);
    cout << "Enter Experience (e.g., 5 years): ";
    getline(cin, exp);
    Admin::faculty(name,fid,fpass,subject,email,phno,designation,department,qualification,exp);

}
void deleteFaculty(){
    string id;
    cout << "Enter Faculty ID to Delete: ";
    cin >> id;
    Admin::deleteFac(id);

}

void deleteStudent(){
    string rollno;
    cout<<"Enter the student Roll number which you want to remove :";
    cin>>rollno;
    Admin::deletStud(rollno);
}

void displayFac(){
    string id,pass;
    cout<<"Enter Teacher Id : ";
    cin>>id;
    Admin::displayFacultyProfile(id);
}


void adminPortal(){
    cout<<endl<<"***************************"<<endl;
    cout<<"Welcome to Admin Portal ..."<<endl;
    //verification
    string id,pass;
    cout<<"Enter Admin Id: ";
    cin>>id;
    cout<<"Enter Admin Password: ";
    cin>>pass;

    pair<bool,string> verification=verifyAdmin(id,pass);//verify admin
    if(verification.first){
        cout << "======================================================================\n";
        cout << "| ADMIN:                                                              |\n";
        cout<<  "| Welcome "<<verification.second<<" , what do you want to do   "<<endl;
        cout << "|                                                                     |\n";
        cout << "======================================================================\n";
        while(true){
            int res;
            cout << "\n1. Register\n2. View Profile\n3. Assign Subject\n4. Assign Hostel\n5. Fees\n6. Add Faculty\n7. Delete Faculty\n8. Delete Student\n9. Display Faculty Profile\n10. Exit\nChoose: ";
            cin >> res;

            if(res==1){
                //register
                registerStudent();


            } else if(res==2){
                //view profile
                viewProfile();

            } else if(res==3){
                //Assign subject
                assignSubject();

            } else if(res==4){
                //Assign Hostel
                assignHostel();

            } else if(res==5){
                //Fees
                setFees();

            } else if(res==6){
                //Faculty
                addfaculty();
            } else if(res==7){
                //Faculty
                deleteFaculty();
            }else if(res==8){
                //Faculty
                deleteStudent();
            } else if(res==9){
                displayFac();
            } else if(res==10){
                break;
            } else {
                cout<<"Invalid Choice !! Try again..."<<endl;
            }
            
        }
    }
    else{
        cout<<"Wrong Id or Password. Exiting";
        return;
    }
}




//********************STUDENT PORTAL*******************




pair<bool,string> verifyStudent(string id,string pass){
    ifstream studentfile("student_data.csv");
    if (!studentfile.is_open()) {
        cout << "Error in opening the file" << endl;
        return make_pair(false, "");
    }

    string line;
    getline(studentfile, line); // Skip the header line

    while(getline(studentfile,line)){
        stringstream ss(line);
        vector<string> data;
        string word;

        while(getline(ss,word,',')){
            data.push_back(word);
        }

        if(data[2] == id && data[4] == pass){
            return make_pair(true,data[0]);
        }
    }

    cout << "Incorrect ID or Password" << endl;
    return make_pair(false, "");

}
void studentPortal(){
    cout<<endl<<"***************************"<<endl;
    cout<<"Welcome to student Portal..."<<endl;
    
    //verification
    string id,pass;
    cout<<"Enter your Id: ";
    cin>>id;
    cout<<"Enter your Password: ";
    cin>>pass;

    pair<bool,string> response=verifyStudent(id,pass);
    if(response.first){
        //student verified
        cout<<endl<<"***************************"<<endl;
        cout<<"Welcome "<<response.second<<" , what you want to search.."<<endl;
        while(true){
            int res;
            cout<<"1. View Profile\n2. View result\n3. View Fees\n4. Courses Assigned\n5. Display Faculty Profile\n6. Exit\nChoose : ";
            cin>>res;
            
            if(res==1){
                //view profile
                Student::profile(id,pass);
                

            } else if(res==2){
                //view result
                Student::viewResult(id,pass);

            } else if(res==3){
                //view Fees
                Student::viewFees(id,pass);

            } else if(res==4){
                //view courses
                Student::viewCourses(id,pass);

            } else if(res==5){
                displayFac();
                
            } else if(res==6){
                //exit
                break;

            }else {
                cout<<"Invalid Choice !! Try again..."<<endl;
            }

        }
        
    }


}


//********************Faculty PORTAL*******************



pair<bool,string> verifyTeacher(string id,string pass){
    ifstream file("faculty_data.csv");
    if (!file.is_open()) {
        cout << "Error in opening faculty data file!" << endl;
        return {false, ""};
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

        if (data.size() < 3) {
            continue; // Ensure there are enough fields (ID, Password, Name)
        }

        if (data[1] == id && data[2] == pass) {
            file.close();
            return {true, data[0]}; // Return true with Faculty Name
        }
    }

    file.close();
    return {false, ""}; // Return false if no match is found
}
void facultyPortal(){
    cout<<endl<<"***************************"<<endl;
    // Add Marks
    cout<<"Welcome to Faculty Portal..."<<endl;
    //verification
    string id,pass;
    cout<<"Enter your Id: ";
    cin>>id;
    cout<<"Enter your Password: ";
    cin>>pass;

    pair<bool,string> verification=verifyTeacher(id,pass);

    if(verification.first){
        cout << "=============================================\n";
        cout << "|                Faculty Portal              |\n";
        cout << "=============================================\n";
        cout<<"Welcome "<<verification.second<<" , what do you want to do :"<<endl;
        while(true){
            int res;
            cout << "\n1. Add Marks/Grade\n2. View Profile Of Student\n3. View Result\n4. Display Faculty Profile\n5. Exit\n Choose: ";
            cin >> res;

            if(res==1){
                //Add marks
                string rno,pass;
                cout<<"Enter Student's Roll number: ";
                cin>>rno;
                Faculty::addGrades(rno);


            } else if(res==2){
                //view profile
                string rno,pass;
                cout<<"Enter Student's Roll number: ";
                cin>>rno;
                Admin::profile(rno);

            } else if(res==3){
                //View Result
                string rno,pass;
                cout<<"Enter Student's Roll number: ";
                cin>>rno;
                cout<<"Enter Student's  Password : ";
                cin>>pass;
                Student::viewResult(rno,pass);

            } else if(res==4){
                displayFac();
                
            } else if(res==5){
               //Exit
               break;

            } 
            else {
                cout<<"Invalid Choice !! Try again..."<<endl;
            }
            
        }
    }
    else{
        cout<<"Wrong Id or Password. Exiting";
        return;
    }


    
}






int main() {

    while(true){
        cout<<endl<<"***************************"<<endl;
        int a;
        cout<<"You are .....\n1. Admin\n2. Faculty\n3. Student\n4. Exit\nChoose: ";
        cin>>a;
        if(a==1){
            //admin portal
            adminPortal();
        }
        else if(a==2){
            //faculty Portal
            facultyPortal();
        }
        else if(a==3){
            //student portal
            studentPortal();
        }
        else if(a==4){
            //exit
            cout<<"Exiting......!!"<<endl;
            break;
        }
        else{
            cout<<"Invalid choice. Try again !!"<<endl;
        }
    }
   
}
