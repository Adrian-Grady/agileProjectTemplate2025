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



