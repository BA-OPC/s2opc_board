/*
 *  Copyright (C) 2018 Systerel and others.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/** \file
 *
 * \brief Entry point for threads tests. Tests use libcheck.
 *
 * If you want to debug the exe, you should define env var CK_FORK=no
 * http://check.sourceforge.net/doc/check_html/check_4.html#No-Fork-Mode
 */

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "check_helpers.h"

#include "sopc_log_manager.h"
#include "sopc_time.h"

#define MAX_LINE_LENGTH 100
#define LINE_PREFIX_LENGTH 26

START_TEST(test_logger_levels)
{
    SOPC_Log_Instance* otherLog = NULL;
    bool res = false;
    FILE* refLogFile = NULL;
    FILE* genLogFile = NULL;
    int ires = 0;
    char* filePathPrefix = NULL;
    char* filePath = NULL;
    char refFilePath[17];
    char refLogLine[MAX_LINE_LENGTH];
    char* refLogLineBis = NULL;
    char genLogLine[MAX_LINE_LENGTH];
    char* genLogLineBis = NULL;

    otherLog = SOPC_Log_CreateInstance("", "AnotherLogFile", "Other", 10000, 2); // Another testLog file
    ck_assert(otherLog != NULL);

    res = SOPC_Log_SetConsoleOutput(otherLog, true);
    ck_assert(res != false);

    res = SOPC_Log_SetLogLevel(otherLog, SOPC_LOG_LEVEL_ERROR);
    ck_assert(res != false);
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_ERROR, "Printing in another log %d %s", 1000, "using template");
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_WARNING, "No warning printed !");
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_INFO, "No info printed !");
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_DEBUG, "No debug printed !");

    // wait 1 ms to have different timestamps
    SOPC_Sleep(1);

    SOPC_Log_SetConsoleOutput(otherLog, false);
    res = SOPC_Log_SetLogLevel(otherLog, SOPC_LOG_LEVEL_WARNING);
    ck_assert(res != false);
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_WARNING, "Warning printed !");
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_INFO, "No info printed !");
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_DEBUG, "No debug printed !");
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_ERROR, "It is another log");

    // wait 1 ms to have different timestamps
    SOPC_Sleep(1);

    res = SOPC_Log_SetLogLevel(otherLog, SOPC_LOG_LEVEL_INFO);
    ck_assert(res != false);
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_WARNING, "Warning printed again !");
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_INFO, "Info printed !");
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_DEBUG, "No debug printed !");
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_ERROR, "Still another log !");

    // wait 1 ms to have different timestamps
    SOPC_Sleep(1);

    res = SOPC_Log_SetLogLevel(otherLog, SOPC_LOG_LEVEL_DEBUG);
    ck_assert(res != false);
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_WARNING, "Warning printed again !");
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_INFO, "Info printed 2 times !");
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_DEBUG, "Debug printed !");
    SOPC_Log_Trace(otherLog, SOPC_LOG_LEVEL_ERROR, "Error in the end");

    filePathPrefix = SOPC_Log_GetFilePathPrefix(otherLog);
    ck_assert(filePathPrefix != NULL);
    ck_assert(strlen(filePathPrefix) > 0);

    // Close the otherLog instance
    SOPC_Log_ClearInstance(&otherLog);

    // Check testLog log file content is the expected content
    free(filePath);
    filePath = malloc((strlen(filePathPrefix) + 10) * sizeof(char)); // 9 + '\0'
    ck_assert(filePath != NULL);
    ires = sprintf(filePath, "%s00001.log", filePathPrefix);
    ck_assert(ires > 0);
    strcpy(refFilePath, "logAnother.ref");
    // Open the generated log and reference log files
    refLogFile = fopen(refFilePath, "r");
    ck_assert(refLogFile != NULL);
    genLogFile = fopen(filePath, "r");
    ck_assert(genLogFile != NULL);

    printf("Comparing log files: %s / %s\n", refFilePath, filePath);

    refLogLineBis = refLogLine;
    genLogLineBis = genLogLine;
    while (NULL != refLogLineBis && NULL != genLogLineBis)
    {
        refLogLineBis = fgets(refLogLine, MAX_LINE_LENGTH, refLogFile);
        genLogLineBis = fgets(genLogLine, MAX_LINE_LENGTH, genLogFile);

        if (refLogLineBis != NULL && genLogLineBis != NULL)
        {
            // Compare logs excluding the timestamp prefix
            ires = strcmp(&refLogLine[LINE_PREFIX_LENGTH], &genLogLine[LINE_PREFIX_LENGTH]);
            printf("Comparing (result == %d):\n- %s- %s", ires, &refLogLine[LINE_PREFIX_LENGTH],
                   &genLogLine[LINE_PREFIX_LENGTH]);
            ck_assert(ires == 0);
        }
        else
        {
            ck_assert(refLogLineBis == NULL && genLogLineBis == NULL);
        }
    }

    fclose(refLogFile);
    fclose(genLogFile);

    free(filePathPrefix);
    free(filePath);
}
END_TEST

START_TEST(test_logger_categories_and_files)
{
    // For 1 line of testLog
    // 23 characters used for compact timestamps + 2 for brackets + 1 blank
    // 9 characters used for category + 1 blank
    // 8 characters used for Error level (including 1 space) => Not present in start stop
    // 1 character for newline
    // => 37 characters + 8 level + trace length

    // Start message => 37 + 9 trace = 46

    SOPC_Log_Instance* testLog = NULL;
    SOPC_Log_Instance* testLog2 = NULL;
    SOPC_Log_Instance* testLog3 = NULL;
    FILE* refLogFile = NULL;
    FILE* genLogFile = NULL;
    int ires = 0;
    char* filePathPrefix = NULL;
    char* filePath = NULL;
    char refFilePath[17];
    char refLogLine[MAX_LINE_LENGTH];
    char* refLogLineBis = NULL;
    char genLogLine[MAX_LINE_LENGTH];
    char* genLogLineBis = NULL;
    uint8_t idx = 0;

    testLog = SOPC_Log_CreateInstance("./not_existing_path/", "testLogFile", "Category1", 340, 3);
    ck_assert(testLog == NULL);
    testLog = SOPC_Log_CreateInstance("", "testLogFile", "Category1", 0, 3);
    ck_assert(testLog == NULL);
    testLog = SOPC_Log_CreateInstance("", "testLogFile", "Category1", 340, 0);
    ck_assert(testLog == NULL);

    testLog = SOPC_Log_CreateInstance("", "TestLogFile", "Category1",
                                      340, // 100 bytes reserved for final line (indicating next file) => 240 of trace
                                      3);  // 3 files => generate enough content to have 3 files
    ck_assert(testLog != NULL);

    testLog2 = SOPC_Log_CreateInstanceAssociation(testLog, "Category2");
    ck_assert(testLog != NULL);

    testLog3 = SOPC_Log_CreateInstanceAssociation(testLog, "Category9999"); // Truncated after 9 characters
    ck_assert(testLog != NULL);

    SOPC_Log_Trace(testLog, SOPC_LOG_LEVEL_ERROR, "This is a test "); // 1st message (60 characters for each)

    SOPC_Log_Trace(testLog2, SOPC_LOG_LEVEL_ERROR, "Always a test !"); // 2 messages

    SOPC_Log_Trace(testLog3, SOPC_LOG_LEVEL_ERROR,
                   "Again a test !!"); // 3 messages => 2nd file of first testLog creation !

    SOPC_Log_Trace(testLog2, SOPC_LOG_LEVEL_ERROR, "2nd file test !"); // 4 messages

    SOPC_Log_Trace(testLog2, SOPC_LOG_LEVEL_ERROR, "message in 2nd!"); // 5 messages

    SOPC_Log_Trace(testLog, SOPC_LOG_LEVEL_ERROR, "This is a test "); // 6 messages

    SOPC_Log_Trace(testLog, SOPC_LOG_LEVEL_ERROR,
                   "This is test 2!"); // 7 messages => 3rd file of first testLog creation

    SOPC_Log_Trace(testLog3, SOPC_LOG_LEVEL_ERROR, "This is the end"); // last message of first testLog

    // Retrieve the prefix file path of testLog files
    filePathPrefix = SOPC_Log_GetFilePathPrefix(testLog);
    ck_assert(filePathPrefix != NULL);
    ck_assert(strlen(filePathPrefix) > 0);

    // Close the testLog instances
    SOPC_Log_ClearInstance(&testLog);
    SOPC_Log_ClearInstance(&testLog2);
    SOPC_Log_ClearInstance(&testLog3);

    // Check testLog log file content is the expected content
    filePath = malloc((strlen(filePathPrefix) + 10) * sizeof(char)); // 9 + '\0'
    ck_assert(filePath != NULL);
    ires = sprintf(filePath, "%s00001.log", filePathPrefix);
    ck_assert(ires > 0);
    strcpy(refFilePath, "logTest.ref1");

    for (idx = 1; idx <= 3; idx++)
    {
        // Open the generated log and reference log files
        refFilePath[11] = 48 + idx; // 48 => '0'
        refLogFile = fopen(refFilePath, "r");
        ck_assert(refLogFile != NULL);
        filePath[strlen(filePathPrefix) + 4] = 48 + idx; // 48 => '0'
        genLogFile = fopen(filePath, "r");
        ck_assert(genLogFile != NULL);

        printf("Comparing log files: %s / %s\n", refFilePath, filePath);

        refLogLineBis = refLogLine;
        genLogLineBis = genLogLine;
        while (NULL != refLogLineBis && NULL != genLogLineBis)
        {
            refLogLineBis = fgets(refLogLine, MAX_LINE_LENGTH, refLogFile);
            genLogLineBis = fgets(genLogLine, MAX_LINE_LENGTH, genLogFile);

            if (refLogLineBis != NULL && genLogLineBis != NULL)
            {
                // Compare logs excluding the timestamp prefix
                ires = strcmp(&refLogLine[LINE_PREFIX_LENGTH], &genLogLine[LINE_PREFIX_LENGTH]);
                if (ires != 0)
                {
                    // It shall be the continue in next file line
                    ires = memcmp(&refLogLine[LINE_PREFIX_LENGTH], "LOG CONTINUE IN NEXT FILE: ", 27);
                    if (ires == 0)
                    {
                        ires = memcmp(&genLogLine[LINE_PREFIX_LENGTH], "LOG CONTINUE IN NEXT FILE: ", 27);
                    }
                }
                printf("Comparing (result == %d):\n- %s- %s", ires, &refLogLine[LINE_PREFIX_LENGTH],
                       &genLogLine[LINE_PREFIX_LENGTH]);
                ck_assert(ires == 0);
            }
            else
            {
                ck_assert(refLogLineBis == NULL && genLogLineBis == NULL);
            }
        }
        fclose(refLogFile);
        fclose(genLogFile);
    }

    free(filePathPrefix);
    free(filePath);
}
END_TEST

START_TEST(test_logger_circular)
{
    // For 1 line of testLog
    // 23 characters used for compact timestamps + 2 for brackets + 1 blank
    // 9 characters used for category + 1 blank
    // 8 characters used for Error level (including 1 space) => Not present in start stop
    // 1 character for newline
    // => 37 characters + 8 level + trace length

    // Start message => 37 + 9 trace = 46

    SOPC_Log_Instance* circularLog = NULL;
    bool res = false;
    FILE* refLogFile = NULL;
    FILE* genLogFile = NULL;
    int ires = 0;
    char* filePathPrefix = NULL;
    char* filePath = NULL;
    char refFilePath[17];
    char refLogLine[MAX_LINE_LENGTH];
    char* refLogLineBis = NULL;
    char genLogLine[MAX_LINE_LENGTH];
    char* genLogLineBis = NULL;
    uint8_t idx = 0;

    circularLog = SOPC_Log_CreateInstance("", "CircularLogFile", "Circular1",
                                          340, // Same as testLog
                                          2);  // TestLog - 1 => first log file overwritten

    // Start circular log
    res = SOPC_Log_SetLogLevel(circularLog, SOPC_LOG_LEVEL_INFO);
    ck_assert(res != false);
    // Simulate a start line in circular log to generate same amount of bytes
    SOPC_Log_Trace(circularLog, SOPC_LOG_LEVEL_INFO, "LOG START");

    SOPC_Log_Trace(circularLog, SOPC_LOG_LEVEL_ERROR, "This is a test "); // 1st message (60 characters for each)

    SOPC_Log_Trace(circularLog, SOPC_LOG_LEVEL_ERROR, "Always a test !"); // 2 messages

    SOPC_Log_Trace(circularLog, SOPC_LOG_LEVEL_ERROR,
                   "Again a test !!"); // 3 messages => 2nd file of first testLog creation !

    SOPC_Log_Trace(circularLog, SOPC_LOG_LEVEL_ERROR, "2nd file test !"); // 4 messages

    SOPC_Log_Trace(circularLog, SOPC_LOG_LEVEL_ERROR, "message in 2nd!"); // 5 messages

    SOPC_Log_Trace(circularLog, SOPC_LOG_LEVEL_ERROR, "This is a test "); // 6 messages

    SOPC_Log_Trace(circularLog, SOPC_LOG_LEVEL_ERROR,
                   "This is test 2!"); // 7 messages => overwrite first circularLog file

    SOPC_Log_Trace(circularLog, SOPC_LOG_LEVEL_ERROR, "This is the end"); // last message of circularLog

    // Check circularLog log file content is the expected content
    filePathPrefix = SOPC_Log_GetFilePathPrefix(circularLog);
    ck_assert(filePathPrefix != NULL);
    ck_assert(strlen(filePathPrefix) > 0);

    // Close the circular log instance
    SOPC_Log_ClearInstance(&circularLog);

    // Check testLog log file content is the expected content
    free(filePath);
    filePath = malloc((strlen(filePathPrefix) + 10) * sizeof(char)); // 9 + '\0'
    ck_assert(filePath != NULL);
    ires = sprintf(filePath, "%s00001.log", filePathPrefix);
    ck_assert(ires > 0);
    strcpy(refFilePath, "logCircular.ref1");

    for (idx = 1; idx <= 2; idx++)
    {
        // Open the generated log and reference log files
        refFilePath[15] = 48 + idx; // 48 => '0'
        refLogFile = fopen(refFilePath, "r");
        ck_assert(refLogFile != NULL);
        filePath[strlen(filePathPrefix) + 4] = 48 + idx; // 48 => '0'
        genLogFile = fopen(filePath, "r");
        ck_assert(genLogFile != NULL);

        printf("Comparing log files: %s / %s\n", refFilePath, filePath);

        refLogLineBis = refLogLine;
        genLogLineBis = genLogLine;
        while (NULL != refLogLineBis && NULL != genLogLineBis)
        {
            refLogLineBis = fgets(refLogLine, MAX_LINE_LENGTH, refLogFile);
            genLogLineBis = fgets(genLogLine, MAX_LINE_LENGTH, genLogFile);

            if (refLogLineBis != NULL && genLogLineBis != NULL)
            {
                // Compare logs excluding the timestamp prefix
                ires = strcmp(&refLogLine[LINE_PREFIX_LENGTH], &genLogLine[LINE_PREFIX_LENGTH]);
                if (ires != 0)
                {
                    // It shall be the continue in next file line
                    ires = memcmp(&refLogLine[LINE_PREFIX_LENGTH], "LOG CONTINUE IN NEXT FILE: ", 27);
                    if (ires == 0)
                    {
                        ires = memcmp(&genLogLine[LINE_PREFIX_LENGTH], "LOG CONTINUE IN NEXT FILE: ", 27);
                    }
                }
                printf("Comparing (result == %d):\n- %s- %s", ires, &refLogLine[LINE_PREFIX_LENGTH],
                       &genLogLine[LINE_PREFIX_LENGTH]);
                ck_assert(ires == 0);
            }
            else
            {
                ck_assert(refLogLineBis == NULL && genLogLineBis == NULL);
            }
        }
        fclose(refLogFile);
        fclose(genLogFile);
    }

    free(filePathPrefix);
    free(filePath);
}
END_TEST

void init(void)
{
    SOPC_Log_Initialize();
}

void clear(void)
{
    SOPC_Log_Clear();
}

Suite* tests_make_suite_logger(void)
{
    Suite* s;
    TCase* tc_logger;

    s = suite_create("Logger tests");
    tc_logger = tcase_create("Logger");
    tcase_add_unchecked_fixture(tc_logger, init, clear);
    tcase_add_test(tc_logger, test_logger_levels);
    suite_add_tcase(s, tc_logger);
    tcase_add_test(tc_logger, test_logger_categories_and_files);
    suite_add_tcase(s, tc_logger);
    tcase_add_test(tc_logger, test_logger_circular);
    suite_add_tcase(s, tc_logger);

    return s;
}
