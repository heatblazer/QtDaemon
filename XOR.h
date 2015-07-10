#ifndef XOR_H
#define XOR_H

/* XOR must be ran on separate worker
 * to confirm execution and finish */

/* TODO - test if working with QT
 * filepaths possible to fail
 * use as debug code never cross with Qt libs */

void encrypt(const char*, const char* , char* );
int getFileSize(const char*, const char*);
void writeToTMPFileStream(char*, char);

void testWrite(); /* remove later */
#endif // XOR_H
