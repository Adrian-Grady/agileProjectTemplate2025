#include "DBAbstraction.h"
#include <iomanip>

using namespace std;

DBAbstraction::DBAbstraction(const string& dbPath)
{
    if(!openDB(dbPath))
    {
        cerr << "Error opening database";
    }
}
DBAbstraction::~DBAbstraction()
{
    closeDB();
}
bool DBAbstraction::openDB(const string& dbPath)
{
    return sqlite3_open(dbPath.c_str(), &db) == SQLITE_OK;
}
void DBAbstraction::closeDB()
{
    if(db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}
//Add new students to the database
void DBAbstraction::addStudent(const string& firstName, const string& lastName)
{
    const char* sql = "INSERT INTO Students (first_name, last_name) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Status Failed: " << sqlite3_errmsg(db) << endl;
        return;
    }
    //put the students names to the place holder
    sqlite3_bind_text(stmt, 1, firstName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, lastName.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            cerr << "Insert failed: " << sqlite3_errmsg(db) << endl;
        }
        else
        {
            cout << "Student added successfully.\n";
        }

        sqlite3_finalize(stmt);
}
void DBAbstraction::addClass(const string& className)
{
    const char* sql = "INSERT INTO class (class_name) VALUES (?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Status Failed: " << sqlite3_errmsg(db) << endl;
        return;
    }
    //put the students names to the place holder
    sqlite3_bind_text(stmt, 1, className.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Insert failed: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Class added successfully.\n";
    }
    sqlite3_finalize(stmt);

}
void DBAbstraction::getAllStudents()
{
    const char* sql = "SELECT id, first_name, last_name FROM Students;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << "\n";
        return;
    }
    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        //extract the column values
        int id = sqlite3_column_int(stmt,0);
        string firstName = reinterpret_cast<const char*>(sqlite3_column_text(stmt,1));
        string lastName = reinterpret_cast<const
            char*>(sqlite3_column_text(stmt, 2));
        //print out the student info
        cout << "ID: " << id << ", First Name: " << firstName << ", Last Name: " << lastName << endl;
    }
    sqlite3_finalize(stmt);
}
//update the students name lines 77 - 127
void DBAbstraction::editStudentFirstName(int studentID, const string& newFirstName)
{
    const char* sql = "UPDATE Students SET first_name = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Preparation failed: " << sqlite3_errmsg(db) << endl;
        return;
    }
    // put the info in the place it is suppose to be in 
    sqlite3_bind_text(stmt, 1, newFirstName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, studentID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Update failed: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "First name updated successfully." << endl;
    }

    sqlite3_finalize(stmt);
}
void DBAbstraction::editStudentLastName(int studentID, const string& newLastName)
{
    const char* sql = "UPDATE Students SET last_name = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Preparation failed: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, newLastName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, studentID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Update failed: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Last name updated successfully." << endl;
    }

    sqlite3_finalize(stmt);
}
void DBAbstraction::editClassName(int classID, const string& newClassName)
{
    const char* sql = "UPDATE class SET class_name = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Preparation failed: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, newClassName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, classID);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Update failed: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Class name updated successfully." << endl;
    }
    sqlite3_finalize(stmt);

}
void DBAbstraction::getAllClasses()
{
    sqlite3_stmt* myStatement;
    const char* query = "SELECT * FROM class";
    int statusOfPrep = sqlite3_prepare_v2(db, query, -1, &myStatement, NULL);

    if (statusOfPrep == SQLITE_OK)
    {
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW)
        {
            const unsigned char* classID = sqlite3_column_text(myStatement, 0);
            const unsigned char* className = sqlite3_column_text(myStatement, 1);

            statusOfStep = sqlite3_step(myStatement);
        }

        sqlite3_finalize(myStatement);
    }
    else
    {
        cout << "Problem creating a prepared statement" << endl;
    }
}

void DBAbstraction::getClassSummary(int classID)
{
}

void DBAbstraction::getDaySummary(const string& date)
{
}

void DBAbstraction::getStudentSummary(int studentID)
{
}

void DBAbstraction::enrollStudentInClass(int studentID, int classID)
{
}

void DBAbstraction::removeStudentFromClass(int studentID, int classID)
{
}
<<<<<<< HEAD
void DBAbstraction::recordAttendance()
{
	cout << "Which class would you like to record attendance for?" << endl;
//populate from database
auto start = std::chrono::system_clock::now();
auto legacyStart = std::chrono::system_clock::to_time_t(start);
char tmBuff[30];
ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
cout << "What day do you wish to record attendance for?" << endl << "1. Use Current Time" << endl << "2. Enter a date." << endl;
char inDateOpt = 0;
cin >> inDateOpt;
if (inDateOpt == '1')
{
    //select count(*) from className where class = currentClassName;
    /*int classSize = result of above;
    * vector<studentInfo> studentInfo;
    * select studentName, studentID from student
    * join Attendance on students.studentID, studentClassJoin.studentID
    * join class on studentClassJoin.classID, class.classID
    * where class.className = className
    * insert into studentInfo all of the results of that
    * for(studentInsertIterator = 0; studentInsertIterator < classSize; studentInsertIterator++)
    * {
    * cout << "Student: " << studentNames<studentInsertIterator> << endl << "Enter p for present, ea for excused absence, ua for unexcused absence, and l for late" << endl;
    * string profIn;
    * cin >> profIn
    * insert into Attendance(studentID) values(profIn)
    * }
    */
}
else if (inDateOpt == '2')
{
    //select class.classID from className where class = currentClassName;
    /*int classID = result of above;
    * vector<studentInfo> studentInfo;
    * select studentName, studentID from student
    * join Attendance on students.studentID, studentClassJoin.studentID
    * join class on studentClassJoin.classID, class.classID
    * where class.className = className
    * insert into studentInfo all of the results of that
    * for(studentInsertIterator = 0; studentInsertIterator < studentInfo.size(); studentInsertIterator++)
    * {
    * cout << "Student: " << studentNames<studentInsertIterator> << endl << "Enter p for present, ea for excused absence, ua for unexcused absence, and l for late" << endl;
    * string profIn;
    * cin >> profIn
   * insert into Attendance(studentID) values(profIn)
   * join Class on Attendance.classID, Class.classID
   * where Class.classID = classID
    * }
   */
}
}
void DBAbstraction::editStudentAttendance()
{
	/*vector<string> classNames
select Class.name from Class
cout << Select their class from this list: << endl << classNames << endl;
 string className;
 cin >> className;
 vector<attendanceInfo> attnInfo;
select Attendance.Date, Attendance.attendance from Attendance
 join class on Attendance.classID = Class.classID
 where Attendance.studentID = studentID and Class.Name = className
insert everything into attnInfo
cout << attnInfo << endl;
cout << "Select the date to edit << endl;
string dateToEdit;
cin >> dateToEdit;
cout << "Write the new attendance info" << endl;
string newAttn;
cin >> newAttn;
insert into Attendance(attendance) values(newAttn) where Attendance.date = dateToEdit
*/
}

=======
void DBAbstraction::recordAttendence(int studentID, int classID, const string& date, const string& present)
{
    const char* sql = "INSERT INTO Attendence (student_id, class_id, date, present) VALUES (?,?,?,?);";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to send student statement: " << sqlite3_errmsg(db) << endl;
    }
    
    sqlite3_bind_int(stmt, 1, studentID);
    sqlite3_bind_int(stmt, 2, classID);
    sqlite3_bind_text(stmt, 3, date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, present.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Failed to record attendance: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "Attendance recorded: " << present << " for student " << studentID << " on " << date << endl;
    }

    sqlite3_finalize(stmt);
}
>>>>>>> 33708c1510bb1c4eb42799db1daae695e765e409
