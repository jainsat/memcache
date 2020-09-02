#ifndef PACKET_H
#define PACKET_H

//#include <arpa/inet.h>
#include<cstring>

struct packet {
	const char *key;
	const char *value;
	const char *flags;
	const char *exp_time;
	uint32_t req_id;
};

int get(const char *key, char *buffer) {
	int j=0;
	int key_len = strlen(key);
    memcpy(buffer, "\x00\x00\x00\x00\x00\x01\x00\x00", 8);
	j += 8;

	memcpy(buffer+j, "get ", 4);
	j += 4;

	memcpy(buffer+j, key, key_len);
	j += key_len;

	memcpy(buffer+j, "\r\n", 2);
	j+=2;

	return j;
}

int set(struct packet p, char *buffer) {
	int flag_len = strlen(p.flags);
	int exp_time_len = strlen(p.exp_time);
	int key_len = strlen(p.key);
	int val_len = strlen(p.value);
	memcpy(buffer, &p.req_id, 4);
	memcpy(buffer+4, "\x00\x01\x00\x00", 4);
	memcpy(buffer+8, "set ", 4);
	memcpy(buffer+12, p.key, key_len);
	int j = 12 + key_len;
	
	memcpy(buffer+j, " ", 1);
	j++;

	memcpy(buffer+j, p.flags, flag_len);
	j += flag_len;

	memcpy(buffer+j, " ", 1);
	j++;

	memcpy(buffer+j, p.exp_time, exp_time_len);
	j += exp_time_len;

	memcpy(buffer+j, " ", 1);
	j++;

    char bytes[10];
	sprintf(bytes, "%d", val_len);
	memcpy(buffer+j, bytes, strlen(bytes));
	j += strlen(bytes);

	memcpy(buffer+j, " noreply\r\n", 10);
	j += 10;

	memcpy(buffer+j, p.value, val_len);
	j += val_len;

	memcpy(buffer+j, "\r\n", 2);
	j += 2;
    return j;

}

/*uint64_t deserialize(char* buffer) {
	uint32_t l,r;
	memcpy(&l, buffer, 4); 
	memcpy(&r, buffer+4, 4); 

	return ((uint64_t)ntohl(l)) << 32 | ntohl(r);
}

struct packet ntohpacket(char buffer[27]) {
	struct packet p;
	p.msg = buffer[0];
	p.method = buffer[1];
	p.key = deserialize(buffer+2);
	p.id = buffer[10];
	p.term = deserialize(buffer+11);
	p.log_id = deserialize(buffer+19);
	return p;

}*/

#endif
