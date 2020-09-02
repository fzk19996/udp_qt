//#ifndef SPPEDTEST_COMMON_H
//#define SPPEDTEST_COMMON_H

//char *run_rx_test(int confd, int retstr);
//void run_tx_test(int confd);

//#endif //SPPEDTEST_COMMON_H

#include <QString>

char* run_rx_test(int confd, int retstr);
void run_tx_test(int confd);
int isDigitStr(QString src);
int generate_uuid();

