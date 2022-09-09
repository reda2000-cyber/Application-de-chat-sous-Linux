#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> // contains definitions of a number of data types used in system calls
#include <sys/socket.h> // includes a number of defenitions of structures needed for sockets (defines the sockaddr stucture)
#include <netinet/in.h> // contains constants and structures needed for internet domain addresses (contains the sockaddr_in stucture)


void error(const char *msg) 
 {
perror(msg); 
exit(1);
}


int main(int argc , char *argv[]){


if(argc < 2)
{
     fprintf(stderr, "Port non fourni. Programme terminé.\n");
     exit(1);
}
int sockfd , newsockfd , portno, n;
char buffer [255];
struct sockaddr_in serv_addr , cli_addr;
socklen_t clilen;
 
 
 sockfd = socket(AF_INET , SOCK_STREAM , 0); 
 if(sockfd < 0){
     error("Erreur d'ouverture de Socket.");
 }

bzero((char *)&serv_addr,sizeof (serv_addr));
portno = atoi(argv[1]); // converts the string pointed to,by the argument str to an integer (type int)


serv_addr.sin_family - AF_INET; 
serv_addr.sin_addr.s_addr = INADDR_ANY; 
serv_addr.sin_port = htons(portno);
if(bind(sockfd , (struct sockaddr *) &serv_addr , sizeof(serv_addr)) < 0)
{
   error("Échec de la liaison.");
}

listen(sockfd , 5);
clilen = sizeof(cli_addr);

newsockfd = accept(sockfd , (struct sockaddr *) &cli_addr , &clilen); 
if(newsockfd < 0) 
{
    error("Erreur lors de l'acceptation");
} 
while(1){
    bzero(buffer , 255);
    n = read(newsockfd , buffer , 255);

   if(n < 0)
   {
       error("Erreur à la lecture.");
   }

   printf("Client : %s\n", buffer); 
   bzero(buffer , 255); 
   fgets (buffer, 255, stdin);

   n = write(newsockfd , buffer , strlen(buffer));

   if(n < 0)
   {
       error("Erreur lors de l'écriture.");
   }



    int i = strncmp("bye" , buffer , 3);
    if(i == 0) 
    {
        break;
    }
    
}
   
  
close(newsockfd);
 close(sockfd);
  return 0;

} 