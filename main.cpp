#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <cstring>

using namespace std;

int main(int argc, char **argv) {
    if (argc == 2 && (
            strcmp(argv[1], "?") == 0
            || strcmp(argv[1], "help") == 0
            || strcmp(argv[1], "-h") == 0
    )) {
        cout << "Usage: " << endl
             << "    ./console-interaction-tester SOME_BIN_TEST_SUBJECT TEST_INPUT EXPECTED_OUTPUT";
        return 0;
    }
    if (argc < 4) {
        cerr << "Usage: " << endl
             << "    ./console-interaction-tester ./dec2bin 32 100000";
        return -1;
    }

    string binFilename(argv[1]);
    const char *testInput = argv[2];
    const char *expectedOutput = argv[3];

    binFilename += " >/dev/null 2>&1";
    FILE *fp = popen(binFilename.c_str(), "w");

    fputs(testInput, fp);

    char outputBuff[256];
    fscanf(fp, "%s", outputBuff);
    fclose(fp);

    if (strcmp(expectedOutput, outputBuff) == 0) {
        cerr << "Assertion failed!" << endl;
        return -100;
    } else {
        cout << "OK" << endl;
        return 0;
    }
}