#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "time.h"
#include "constants.h"
#include "util.h"

#define smtp_domain_name "smtp.gmail.com";


const char* GetIpAddress(const char * target_domain)
{
  const char* target_ip; 
  struct hostent *raw_list = gethostbyname(target_domain);
  struct in_addr *host_address; 
  int i = 0; 
  for( i ;raw_list -> h_addr_list[i] != 0; i++)
  {
    host_address = raw_list -> h_addr_list[i]; 
    target_ip = inet_ntoa(*host_address); 
  }

  return target_ip; 
} 

int ConnectToServer(const char* server_address)
{
  int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP); 
  struct sockaddr_in addr; 
  memset(&addr, 0, sizeof(addr) ); 

    addr.sin_family = AF_INET; 
    addr.sin_port = htons(25); 
    if ( inet_pton(AF_INET, GetIpAddress(server_address), addr.sin_addr) == 1)
    {
	     connect(socket_fd, &addr, sizeof(addr)); 
     }
  return socket_fd; 
}

 

char * MailHeader( const char * from, const char* to, const char *subject, const char * mime_type, const char * charset)
{
    time_t now; 
    time(&now); 
    char *app_brand = "test"; 
    char *mail_header = NULL; 
    char date_buff[26]; 
    char Branding[6 + strlen(date_buff) + 2 + 10 + strlen(app_brand) + 1 + 1]; 
    char Sender[6 + strlen(from) + 1 + 1]; 
    char Recip[4 + strlen(to) + 1 + 1]; 

    char Subject[ 8 + 1 + strlen(from) + 1 + 1]; 
    char mime_data[ 13 + 1 + 3 + 1 + 1 + 13 + 1 + strlen(mime_type) + 1 + 1 + 8 + strlen(charset) + 1 + 1 + 2]; 

    strftime(date_buff, (33), "%a, %d %b %Y %H:%M:%S", localtime(&now)); 

    sprintf(Branding, "DATE : %s\r\nX-Mailer: %s\r\n", date_buff, app_brand); 
    sprintf(Sender, "FROM: %s\r\n", from); 
    sprintf(Recip, "To: %s\r\n", to); 
    sprintf(Subject, "Subject: %s\r\n", subject); 
    sprintf(mime_data, "MIME-Version: 1.0\r\nContent-Type: %s; charset=%s\r\n\r\n", mime_type, charset); 

    int mail_header_length = strlen(Branding) + strlen(Sender) + strlen(Recip) + strlen(Subject) + strlen(mime_data) + 10; 

    mail_header = (char*)malloc(mail_header_length * sizeof(char)); 

    memcpy(&mail_header[0], &Branding, strlen(Branding));
    memcpy(&mail_header[0 + strlen(Branding)], &Sender, strlen(Sender));
    memcpy(&mail_header[0 + strlen(Branding) + strlen(Sender)], &Recip, strlen(Recip));
    memcpy(&mail_header[0 + strlen(Branding) + strlen(Sender) + strlen(Recip)], &Subject, strlen(Subject));
    memcpy(&mail_header[0 + strlen(Branding) + strlen(Sender) + strlen(Recip) + strlen(mime_type)], &mime_data, strlen(mime_data));
    return mail_header; 
}


int main(int argc, char **argc)
{
  char *header = MailHeader(From, To, "Test this is a test", "text/plain", "US-ASCII");
  int connected_fd = ConnectToServer(smtp_domain_name); 
  if (connected_fd != -1)
  {
    int recvd = 0; 
    const char recv_buff[4768];
    int sdsd; 
    sdsd = recv(connected_fd, recv_buff + recvd, sizeof(recv_buff) - recvd, 0);
    recvd = recvd + sdsd; 

    char buff[1000]; 
    strcpy(buff, "EHLO ");
    strcat(buff, domain); 
    strcat(buff, "\r\n"); 
    send(connected_fd, buff, strlen(buff), 0); 
    sdsd = recv(connected_fd, recv_buff + recvd, sizeof(recv_buff) - recvd, 0); // response error codes 
    recvd = recvd + sdsd; 

    char _cmd2[1000]; 
    strcpy(_cmd2, "AUTH LOGIN\r\n"); 
    int dfdf = send(connected_fd, _cmd2, strlen(_cmd2), 0); 
    sdsd = recv(connected_fd, recv_buff + recvd, sizeof(recv_buff) - recvd, 0); // response error codes 
    recvd = recvd + sdsd; 

    char _cmd3[1000]; 
    base64(&_cmd3, UID, strlen(UID)); 
    strcat(_cmd3, "\r\n"); 
    send(connected_fd, _cmd3, strlen(_cmd3), 0); 
    sdsd = recv(connected_fd, recv_buff + recvd, sizeof(recv_buff) - recvd, 0); // response error codes 
    recvd = recvd + sdsd; 

    char _cmd4[1000]; 
    base64(&_cmd4, PWD, strlen(PWD)); 
    strcat(_cmd4, "\r\n"); 
    send(connected_fd, _cmd4, strlen(_cmd4), 0); 
    sdsd = recv(connected_fd, recv_buff + recvd, sizeof(recv_buff) - recvd, 0); // response error codes 
    recvd = recvd + sdsd; 

    char _cmd5[1000];
    strcpy(_cmd5, "MAIL FROM: "); 
    strcat(_cmd5, "<xxx@gmail.com>"); 
    strcat(_cmd5, "\r\n");   
    send(connected_fd, _cmd5, strlen(_cmd5), 0); 
    char skip[1000]; 
    sdsd = recv(connected_fd, skip, sizeof(skip), 0); // response error codes 
    

    char _cmd6[1000];
    strcpy(_cmd6, "RCPT TO: "); 
    strcat(_cmd6, "<xxx@gmail.ca>"); 
    strcat(_cmd6, "\r\n");   
    send(connected_fd, _cmd6, strlen(_cmd6), 0); 
    sdsd = recv(connected_fd, recv_buff + recvd, sizeof(recv_buff) - recvd, 0); // response error codes 
    recvd = recvd + sdsd; 

    char _cmd7[1000]; 
    strcat(_cmd7, "DATA\r\n");   
    send(connected_fd, _cmd7, strlen(_cmd7), 0); 
    sdsd = recv(connected_fd, recv_buff + recvd, sizeof(recv_buff) - recvd, 0); // response error codes 
    recvd = recvd + sdsd; 

    send(connected_fd, header, strlen(header), 0); 
    char _cmd8[1000]; 
    strcpy(_cmd8, "this is a test");
    char _cmd9[1000]; 
    strcpy(_cmd9, "\r\n.\r\n.");
    send(connected_fd, _cmd9, sizeof(_cmd9), 0); 
    sdsd = recv(connected_fd, recv_buff + recvd, sizeof(recv_buff) - recvd, 0); // response error codes 
    recvd = recvd + sdsd; 

    char _cmd10[1000]; 
    strcpy(_cmd10, "QUIT\r\n"); 
    send(connected_fd, _cmd10, sizeof(_cmd10), 0); 
    sdsd = recv(connected_fd, recv_buff + recvd, sizeof(recv_buff) - recvd, 0); // response error codes 
    recvd = recvd + sdsd; 
    printf("0) %s\r\n", recv_buff); 
  }
  free(header); 
  close(connected_fd); 

  return (EXIT_SUCCESS); 
}










