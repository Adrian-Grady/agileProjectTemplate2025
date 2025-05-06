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
