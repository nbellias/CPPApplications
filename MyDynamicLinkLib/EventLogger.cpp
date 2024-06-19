#include "pch.h"
#include "EventLogger.h"
#include <time.h>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

void WriteToEventLog(string message)
{
    LPCWSTR loggerName = L"MyEventLogger";
    HANDLE hEventLog = RegisterEventSource(NULL, loggerName);

    if (hEventLog)
    {
        // Get the current time
        time_t rawtime;
        struct tm timeinfo;
        
        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);
        ostringstream oss;
        oss << put_time(&timeinfo, "%Y-%m-%dT%H:%M:%S");

        string fullMessage = oss.str() + ": " + message;
        WCHAR* finalMessage = (WCHAR*)fullMessage.c_str();

        const WCHAR* strings[1] = { finalMessage };

        ReportEvent(
            hEventLog,          // Event log handle
            EVENTLOG_INFORMATION_TYPE, // Event type
            0,                  // Event category
            0x1000,             // Event identifier
            NULL,               // No user security identifier
            1,                  // Number of substitution strings
            0,                  // No data
            strings,            // Pointer to strings (message)
            NULL                // No data
        );

        DeregisterEventSource(hEventLog);
    }
}
