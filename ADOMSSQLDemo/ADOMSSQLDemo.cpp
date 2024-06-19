#include <iostream>
#include <comdef.h>
#include <atlbase.h>
#include <atlcom.h>
#include <atlsafe.h>
#include <string>
#include <random>
#include <chrono>
#include <ctime>
#include <windows.h>
#include <rpc.h> // for UUID generation
#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF", "EndOfFile")


std::string GenerateRandomString(int min_length, int max_length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    int string_length = rand() % (max_length - min_length + 1) + min_length;
    std::string result;
    result.reserve(string_length);

    for (int i = 0; i < string_length; ++i) {
        result += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return result;
}

std::time_t ConvertStringToTimeT(const std::string& date) {
    std::tm tm = {};
    sscanf_s(date.c_str(), "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900; // Year since 1900
    tm.tm_mon -= 1;     // Month in the range 0-11
    return std::mktime(&tm);
}

std::string GenerateRandomDate(const std::string& start_date, const std::string& end_date) {
    std::time_t start_time = ConvertStringToTimeT(start_date);
    std::time_t end_time = ConvertStringToTimeT(end_date);

    std::uniform_int_distribution<std::time_t> dist(start_time, end_time);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::time_t random_time = dist(mt);

    std::tm random_tm;
    localtime_s(&random_tm, &random_time);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &random_tm);

    return std::string(buffer);
}

void CreateTables(_ConnectionPtr pConn) {
    try {
        // Create the Department table
        _CommandPtr pCmd("ADODB.Command");
        pCmd->ActiveConnection = pConn;
        pCmd->CommandText = "CREATE TABLE Department (id UNIQUEIDENTIFIER PRIMARY KEY DEFAULT NEWSEQUENTIALID(), name NVARCHAR(50), address NVARCHAR(100))";
        pCmd->Execute(NULL, NULL, adCmdText);

        // Create the Employee table
        pCmd->CommandText = "CREATE TABLE Employee (id UNIQUEIDENTIFIER PRIMARY KEY DEFAULT NEWSEQUENTIALID(), name NVARCHAR(50), salary FLOAT, date_of_birth DATE, date_of_hiring DATE, department_id UNIQUEIDENTIFIER, FOREIGN KEY (department_id) REFERENCES Department(id))";
        pCmd->Execute(NULL, NULL, adCmdText);

        std::cout << "Tables created successfully." << std::endl;
    }
    catch (_com_error& e) {
        std::wcerr << L"Error: " << e.ErrorMessage() << std::endl;
    }
}

void BulkInsertDepartments(_ConnectionPtr pConn) {
    try {
        _RecordsetPtr pRs("ADODB.Recordset");
        pRs->Open("Department", pConn.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdTable);

        for (int i = 1; i <= 5000; ++i) {
            pRs->AddNew();
            pRs->Fields->Item["name"]->Value = GenerateRandomString(10, 50).c_str();
            pRs->Fields->Item["address"]->Value = GenerateRandomString(10, 50).c_str();
            pRs->Update();
        }
        pRs->Close();

        std::cout << "Departments inserted successfully." << std::endl;
    }
    catch (_com_error& e) {
        std::wcerr << L"Error: " << e.ErrorMessage() << std::endl;
    }
}

std::vector<std::string> GetDepartmentIDs(_ConnectionPtr pConn) {
    std::vector<std::string> department_ids;
    try {
        _RecordsetPtr pRs("ADODB.Recordset");
        pRs->Open("SELECT id FROM Department", pConn.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);

        while (!pRs->EndOfFile) {
            department_ids.push_back((char*)_bstr_t(pRs->Fields->Item["id"]->Value));
            pRs->MoveNext();
        }
        pRs->Close();
    }
    catch (_com_error& e) {
        std::wcerr << L"Error: " << e.ErrorMessage() << std::endl;
    }
    return department_ids;
}

void BulkInsertEmployees(_ConnectionPtr pConn) {
    std::vector<std::string> department_ids = GetDepartmentIDs(pConn);

    if (department_ids.empty()) {
        std::cerr << "No departments found. Cannot insert employees without departments." << std::endl;
        return;
    }

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, department_ids.size() - 1);

    int batchSize = 100000;

    try {
        for (int i = 1; i <= 5000000; i += batchSize) {
            _RecordsetPtr pRs("ADODB.Recordset");
            pRs->Open("Employee", pConn.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdTable);

            for (int j = 0; j < batchSize && (i + j) <= 5000000; ++j) {
                pRs->AddNew();
                pRs->Fields->Item["name"]->Value = GenerateRandomString(10, 50).c_str();
                pRs->Fields->Item["salary"]->Value = 50000 + static_cast<double>(rand()) / RAND_MAX * (120000 - 50000);
                pRs->Fields->Item["date_of_birth"]->Value = GenerateRandomDate("1950-01-01", "2000-01-01").c_str();
                pRs->Fields->Item["date_of_hiring"]->Value = GenerateRandomDate("1978-01-01", "2023-06-01").c_str();
                std::string dept_id = department_ids[dist(rng)];
                pRs->Fields->Item["department_id"]->Value = dept_id.c_str();
            }

            pRs->UpdateBatch(adAffectAll);
            pRs->Close();

            std::cout << "Inserted " << i + batchSize - 1 << " employees." << std::endl;
        }

        std::cout << "Employees inserted successfully." << std::endl;
    }
    catch (_com_error& e) {
        std::wcerr << L"Error: " << e.ErrorMessage() << std::endl;
        std::wcerr << L"Source: " << (const wchar_t*)e.Source() << std::endl;
        std::wcerr << L"Description: " << (const wchar_t*)e.Description() << std::endl;
    }
}

void PopulateTablesWithRandomData(_ConnectionPtr pConn) {
    BulkInsertDepartments(pConn);
    BulkInsertEmployees(pConn);
}

void ReportEmployeesPerDepartment(_ConnectionPtr pConn) {
    try {
        _RecordsetPtr pRs("ADODB.Recordset");
        pRs->Open("SELECT department_id, COUNT(*) AS num_employees FROM Employee GROUP BY department_id", pConn.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);

        std::cout << "Number of Employees per Department:" << std::endl;
        while (!pRs->EndOfFile) {
            std::cout << "Department ID: " << (char*)_bstr_t(pRs->Fields->Item["department_id"]->Value) << ", Number of Employees: " << (long)pRs->Fields->Item["num_employees"]->Value << std::endl;
            pRs->MoveNext();
        }
        pRs->Close();
    }
    catch (_com_error& e) {
        std::wcerr << L"Error: " << e.ErrorMessage() << std::endl;
    }
}

void ReportEmployeeAgeDistribution(_ConnectionPtr pConn) {
    try {
        _RecordsetPtr pRs("ADODB.Recordset");
        pRs->Open(
            "WITH AgeDistribution AS ("
            "    SELECT "
            "        DATEPART(YEAR, GETDATE()) - DATEPART(YEAR, date_of_birth) - "
            "        CASE "
            "            WHEN DATEADD(YEAR, DATEPART(YEAR, GETDATE()) - DATEPART(YEAR, date_of_birth), date_of_birth) > GETDATE() "
            "            THEN 1 "
            "            ELSE 0 "
            "        END AS Age "
            "    FROM "
            "        Employee"
            ") "
            "SELECT "
            "    Age, "
            "    COUNT(*) AS Count "
            "FROM "
            "    AgeDistribution "
            "GROUP BY "
            "    Age "
            "ORDER BY "
            "    Age;",
            pConn.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);

        std::cout << "Employee Age Distribution:" << std::endl;
        while (!pRs->EndOfFile) {
            std::cout << "Age: " << (long)pRs->Fields->Item["Age"]->Value << ", Count: " << (long)pRs->Fields->Item["Count"]->Value << std::endl;
            pRs->MoveNext();
        }
        pRs->Close();
    }
    catch (_com_error& e) {
        std::wcerr << L"Error: " << e.ErrorMessage() << std::endl;
    }
}

void FetchAndDisplayData(_ConnectionPtr pConn) {
    try {
        // Fetch data from Department table
        _RecordsetPtr pRs("ADODB.Recordset");
        pRs->Open("SELECT * FROM Department", pConn.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);

        std::cout << "Department Table:" << std::endl;
        while (!pRs->EndOfFile) {
            std::cout << "ID: " << (char*)_bstr_t(pRs->Fields->Item["id"]->Value) << ", Name: " << (char*)_bstr_t(pRs->Fields->Item["name"]->Value) << ", Address: " << (char*)_bstr_t(pRs->Fields->Item["address"]->Value) << std::endl;
            pRs->MoveNext();
        }
        pRs->Close();

        // Fetch data from Employee table
        pRs->Open("SELECT TOP 10 * FROM Employee", pConn.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText); // Limiting to 10 for display

        std::cout << "Employee Table (first 10 rows):" << std::endl;
        while (!pRs->EndOfFile) {
            std::cout << "ID: " << (char*)_bstr_t(pRs->Fields->Item["id"]->Value) << ", Name: " << (char*)_bstr_t(pRs->Fields->Item["name"]->Value) << ", Salary: " << (double)pRs->Fields->Item["salary"]->Value << ", DOB: " << (char*)_bstr_t(pRs->Fields->Item["date_of_birth"]->Value) << ", DOH: " << (char*)_bstr_t(pRs->Fields->Item["date_of_hiring"]->Value) << ", Department ID: " << (char*)_bstr_t(pRs->Fields->Item["department_id"]->Value) << std::endl;
            pRs->MoveNext();
        }
        pRs->Close();
    }
    catch (_com_error& e) {
        std::wcerr << L"Error: " << e.ErrorMessage() << std::endl;
    }
}

void DropTables(_ConnectionPtr pConn) {
    try {
        _CommandPtr pCmd("ADODB.Command");
        pCmd->ActiveConnection = pConn;

        // Drop the Employee table
        pCmd->CommandText = "DROP TABLE IF EXISTS Employee";
        pCmd->Execute(NULL, NULL, adCmdText);

        // Drop the Department table
        pCmd->CommandText = "DROP TABLE IF EXISTS Department";
        pCmd->Execute(NULL, NULL, adCmdText);

        std::cout << "Tables dropped successfully." << std::endl;
    }
    catch (_com_error& e) {
        std::wcerr << L"Error: " << e.ErrorMessage() << std::endl;
    }
}

int main() {
    // Initialize COM
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        std::wcerr << L"Failed to initialize COM library." << std::endl;
        return -1;
    }

    try {
        // Create a connection object
        _ConnectionPtr pConn("ADODB.Connection");
        pConn->Open("Provider=SQLOLEDB; Data Source=localhost; Initial Catalog=nikosdb; User ID=sa; Password=N1k0S1967;", "", "", adConnectUnspecified);

        DropTables(pConn);
        CreateTables(pConn);
        PopulateTablesWithRandomData(pConn);
        FetchAndDisplayData(pConn);
        ReportEmployeesPerDepartment(pConn);
        ReportEmployeeAgeDistribution(pConn);
        

        // Close the connection
        pConn->Close();
    }
    catch (_com_error& e) {
        std::wcerr << L"Error: " << e.ErrorMessage() << std::endl;
    }

    // Uninitialize COM
    CoUninitialize();

    return 0;
}
