#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include<chrono>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdlib>
#include<iostream>

#include "packet.h"

#define HOST_PORT 11211

/*void rand_str(char *dest, size_t length) {
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}
*/

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 4) {
       fprintf(stderr,"Please provide number of msgs, key and value\n");
       exit(0);
    }
    struct sockaddr_in remaddr;
    int fd, i;
    int recvlen;
    socklen_t slen =sizeof(remaddr);
    int msgs = atoi(argv[1]);
	int tries = atoi(argv[4]);
	/* create a UDP socket */
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("cannot create socket\n");
        return 0;
    }


    /* now define remaddr, the address to whom we want to send messages */
    memset((char *) &remaddr, 0, sizeof(remaddr));
    remaddr.sin_family = AF_INET;
    remaddr.sin_port = htons(HOST_PORT);
    remaddr.sin_addr.s_addr = inet_addr("192.168.2.4");

	auto start = std::chrono::high_resolution_clock::now();
	char buf[200];
	struct packet p;
	p.key = argv[2];
	p.value = argv[3];
	p.flags = "0";
	p.exp_time = "900";
	p.req_id = 40;
	//int len = set(p, buf);
	int len = get("zzzz", buf);
	uint32_t seq;
	char b[50];
    for (i=0; i < msgs; i++) {
        seq = i+1;
        //memcpy(buf, &seq, 4);
        if (sendto(fd, buf, len, 0, (struct sockaddr *)&remaddr, slen)==-1) {
            perror("sendto");
            exit(1);
        }
        //std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        for(int i=0;i<tries;i++)
            sprintf(b,"hellojdfkdjfkjdkfjkdjfkdj");

        /* now receive an acknowledgement from the server */
        // recvlen = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *)&remaddr, &slen);
        //         if (recvlen >= 0) {
        //                 buf[recvlen] = 0;    /* expect a printable string - terminate it */
        //                 printf("received message: \"%s\"\n", buf);
        //         }
    }
    auto end = std::chrono::high_resolution_clock::now();
	auto cpu_time_used = (end - start);
    //printf("\n start = %lu, end=%lu, time = %lu\n",start,end,cpu_time_used);
    std::cout << "Total time = " << cpu_time_used / std::chrono::milliseconds(1) << "ms" <<endl;

    len = get("mani", buf);
	if (sendto(fd, buf, len, 0, (struct sockaddr *)&remaddr, slen)==-1) {
        perror("sendto");
        exit(1);
    }
    close(fd);
	return 0;


}
