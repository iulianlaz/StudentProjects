/* Lazar Iulian 325CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

#define BUFLEN 1500
#define SEC 60
#define MIN 3600
#define MAX_CLIENTS 100
#define BUFLEN_2 1024

void error(char *msg)
{
    perror(msg);
    exit(0);
}

/* Verific daca un fisier se gaseste la client */
int verifica_fisier(char *buffer) {
char pars_1[100];
char pars_2[100];
int iter = 0;
char *pc;
char aux_buffer[BUFLEN];
char *share = "sharefile";
FILE *f1;

  sprintf(aux_buffer, "%s", buffer);
  pc = strtok(aux_buffer, " \n");
		    
  while (pc != NULL) {
	if (iter >=2) break;
	
	if (iter == 0) {
	sprintf(pars_1, "%s", pc);		  
	}
	
	if (iter == 1) {
		 sprintf(pars_2, "%s", pc);
		 
			  
	}
	
	pc = strtok (NULL, " \n");
	iter++;
	}

  if (strcmp(pars_1, share) == 0) {
      f1 = fopen(pars_2, "r+");
      if ( f1 != NULL) {
	  fclose(f1);
	  return 1;
	
	
      }
      else {
	  return -3;
 
      }
  }
  return 1;
  
}

int main(int argc, char *argv[])
{
    int sockfd, n, k;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[BUFLEN];
    char buffer_with_name[BUFLEN];
    int len;
    int correct_name = 0;
    char *verify = "reject_client_dup";
    char *accept_str = "Accept";
    char *pch;
    int incr = 0;
    int found = 0;
    int rem = 0;
    int execute = -3;
    char pars_command_1[100];
    long int time;
    int check = 0;
    char *er = "Error";
    char aux_buffer[BUFLEN];
    int sockfd_to_send;
    int sockfd_to_send_share;
    int sockfd_to_send_file;
    char from_name[100];
    char from_ip[100];
    char from_port[100];
    
    char to_send_ip[100];
    char to_send_port[100];
    char file_name[100];
    char first_word[100];
    char nume_fisier[100];
    int fd;
    FILE  *fd_1;
    
    
    /* Lista cu comenzi posibile */
    char *tasks[] = { "listclients", "infoclient", "message", "sharefile", 
		    "unsharefile", "getshare", "quit", "getfile"};
    
    if (argc < 4) {
       fprintf(stderr,"Usage %s server_address server_port\n", argv[0]);
       exit(0);
    }  
    
    
    

  int sockfd_listen;
  int portno;
  struct sockaddr_in recv_mess_addr;
  sockfd_listen = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd_listen < 0) 
    error("ERROR opening socket");
     
  portno = atoi(argv[3]);

  memset((char *) &recv_mess_addr, 0, sizeof(recv_mess_addr));
  
  recv_mess_addr.sin_family = AF_INET;
  recv_mess_addr.sin_addr.s_addr = INADDR_ANY;	// foloseste adresa IP a masinii
  recv_mess_addr.sin_port = htons(atoi(argv[4]));
  
  
  if (bind(sockfd_listen, (struct sockaddr *) &recv_mess_addr,
					sizeof(struct sockaddr)) < 0) 
    error("ERROR on binding");
  listen(sockfd_listen, MAX_CLIENTS);

  //adaugam noul file descriptor (socketul pe care se asculta conexiuni) in 
  //multimea read_fds
  fd_set read_set;
  FD_SET(sockfd_listen, &read_set);
  
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[3]));
    inet_aton(argv[2], &serv_addr.sin_addr);
   
    
    if (connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");    
    
    fd_set read_fds; // permanent
    FD_ZERO(&read_set); //temporar
    FD_ZERO(&read_fds);
    
    int fdmax = sockfd;
    
    while(1){
      
	if (correct_name == 0) {
	
		
		memset(buffer, 0 , BUFLEN);
		sprintf(buffer, "name:%s:%s", argv[1], argv[4]);
		n = send(sockfd,buffer,strlen(buffer), 0);
		correct_name++;
	  
	}
	else  {
	
	FD_SET(sockfd, &read_set);
        FD_SET(STDIN_FILENO, &read_set);
	FD_SET(sockfd_listen, &read_set);
	
	if (sockfd > sockfd_listen)
	    fdmax = sockfd;
	else
	    fdmax = sockfd_listen;
	
	if (fdmax < sockfd_to_send)
	      fdmax = sockfd_to_send;
	
        select(fdmax + 1, &read_set, NULL, NULL, NULL);  
	   
        if (FD_ISSET(STDIN_FILENO, &read_set)) {
      		//citesc de la tastatura
        	memset(buffer, 0 , BUFLEN);
        	fgets(buffer, BUFLEN-1, stdin);
		
		/* Verific daca fisierul exista la client */
		check = verifica_fisier(buffer);
		
		if (check == 1) {
		    sprintf(buffer_with_name, "name:%s:%s", argv[1], buffer);
		    sprintf(buffer, "%s", buffer_with_name);
		    //printf("Trimitem mesajul: %s\n", buffer);
		    //trimit mesaj la server
		    n = send(sockfd,buffer,strlen(buffer), 0);
		    if (n < 0) 
		    error("ERROR writing to socket");
		}
		else 
		   if (check == -3) {
		   
		     printf("Error. Fisierul nu exista.\n");
		  }
		
        } else if (FD_ISSET(sockfd, &read_set)) {
            /* primit mesaj de la server */
            //printf("PRIMIT\n");
            len = recv(sockfd, buffer, BUFLEN, 0);
            if (len <= 0) {
                break;
            }
            if (strcmp (buffer, verify) == 0) {
		printf("Error: Reject. (duplicate name)\n");
		close(sockfd_listen);
		close(sockfd_to_send);
		close(sockfd);
		return;
	    }
	    else {
		if (strcmp(buffer, accept_str) == 0) {
			  puts(buffer);
			  
		}
		else {
			
			incr = 0;
			rem = 0;
			
			/* Parsare comanda ceruta */
			pch=strchr(buffer,':');
			while (pch!=NULL) {
			    if (incr == 1) break;
			    found = pch - buffer + 1;
			    sprintf (pars_command_1, "%s", 
						    strndup(buffer, found -1));
			    printf("*** Se executa comanda: %s ...\n", 
						      pars_command_1);  
			    rem = found;
			    incr++;
			}
			
			/* Buffer fara comanda */
			sprintf(buffer, "%s", buffer + rem);
			
			/* Determin comanda de la client */  
			for (k = 0; k < 8; k++)
			    if (strcmp(pars_command_1, tasks[k]) == 0)
				execute = k;
			
			
			/* Executa comanda */  
			switch (execute) {   
			    
			  /* Am primit comanda listclients */
			  case 0:
			    
			     printf("Clienti conectati la server:\n");
			    /* Afisare nume client, adresa ip, socket si port */
			    incr = 0;
			    rem = 0;
			    pch=strchr(buffer,':');
			    while (pch!=NULL) {
				
				found = pch - buffer + 1;
				
				if (incr % 4 == 0) {
					printf("Nume client: %*s \t", 12, 
					 strndup(buffer + rem, found - rem -1));
					rem = found;
				  
				}
				
				if (incr % 4 == 1) {
					printf("IP: %*s \t", 5 ,
					strndup(buffer + rem, found - rem - 1));
					rem = found;
				}
				
				if (incr % 4 == 2) {
					printf("Socket: %*s \t", 5, 
					strndup(buffer + rem, found - rem - 1));
					rem = found;
				}
				
				if (incr % 4 == 3) {
					printf("Port: %*s\n", 5, 
					strndup(buffer + rem, found - rem - 1));
					rem = found;
				}
				
				pch=strchr(buffer+found,':');
				incr++;
			    }
			    execute = -3;
			    break;
			
			    
			   /* Am primit comanda infoclient */  
			  case 1: 
			      
			      printf("Informatii suplimentare:\n");
			    
			      incr = 0;
			      rem = 0;
			      pch=strchr(buffer,':');
			      while (pch!=NULL) {
				
				  found = pch - buffer + 1;
				  
				  if (incr == 0) {
					 printf("Nume client: %s \t",  
					 strndup(buffer + rem, found - rem -1));
					rem = found;
				    
				  }
				  
				  if (incr == 1) {
				    time =  atol (strndup(buffer 
					    + rem, found - rem - 1));
				    if (time < SEC)
				      printf("Conectat de: %ld sec \t ", time);
				    else if (time < MIN) {
				      printf("Conectat de: %ld min %ld sec \t ", 
					     time / SEC, time % SEC);
					    
				    }
				    else 
					if (time > MIN) {
				printf("Conectat de: %ld h %ld min %ld sec \t ",
					time / MIN, (time % MIN) / SEC, 
					(time % MIN) % SEC);
					}
					
				    rem = found;
				  }
				  
				  if (incr == 2) {
				      printf("Port: %s \n",
				      strndup(buffer + rem, found - rem - 1));
				      rem = found;
				  }
				  
				  pch=strchr(buffer+found,':');
				  incr++;
			      }
			      
			      execute = -3;
			      break;
			      
			      
			  /* Am primit comanda message */  
			  case 2: 
			      
			      incr = 0;
			      rem = 0;
			     
			      
			      memset(from_name, 0, 100);
			      memset(from_ip, 0, 100);
			      memset(from_port, 0, 100);
			      
			      /* Parsez numele clientului care trimite mesajul,
			       * ip-ul si portul clientului care primeste 
			       * mesajul */
			      pch=strchr(buffer,':');
			      while (pch!=NULL) {
				  if (incr >= 3) break;
				  found = pch - buffer + 1;
				  
				  if (incr == 0) 
				    sprintf (from_name, "%s", 
						    strndup(buffer+ rem, found 
								- rem -1));
				  if (incr == 1)
				    sprintf (from_ip, "%s", 
						    strndup(buffer+ rem, found 
								  - rem -1));
				    
				  if (incr == 2)
				    sprintf (from_port, "%s", 
						    strndup(buffer+ rem, found 
								  - rem -1));
				  rem = found;
				 
				  pch=strchr(buffer+found,':');
				  incr++;
				  
			      }
			    
			      
			      if (strcmp(from_name, er) == 0) {
			      
				  printf("Error: ");
				  printf("%s", buffer + rem);
			      }
			      else {
			      
				  printf("Mesaj trimis.\n");
					
				  struct sockaddr_in for_send_addr;
				    
				    memset((char *) &for_send_addr, 0, 
						      sizeof(for_send_addr));
				    
				    
				     sockfd_to_send = socket(AF_INET, 
								SOCK_STREAM, 0);
				     if (sockfd_to_send < 0) 
					    error("ERROR opening socket");
			      
				  
				    
				    for_send_addr.sin_family = AF_INET;
				    inet_aton(from_ip, 
						    &(for_send_addr.sin_addr));
				    for_send_addr.sin_port = 
							 htons(atoi(from_port));
				    
				    if (connect(sockfd_to_send,
				      (struct sockaddr*) &for_send_addr,
						    sizeof(for_send_addr)) < 0) 
					  error("ERROR connecting");
				    
				    memset(aux_buffer, 0, BUFLEN);
				    sprintf(aux_buffer,"From %s: %s",from_name,
								buffer + rem);
				    memset(buffer, 0, BUFLEN);
				    sprintf(buffer, "%s", aux_buffer);
				    
				    send (sockfd_to_send, buffer, 
							    strlen(buffer), 0);
				    
			      }
			      
			      execute = -3;
			      break;
			      
			  /* Am primit comanda sharefile */    
			  case 3:

			      printf("%s\n", buffer);
				
			      execute = -3;
			      break;
			      
			 /* Am primit comanda unsharefile */    
			 case 4:

			      printf("%s\n", buffer);
				
			      execute = -3;
			      break;
			   
			 /* Am primit comanda getshare */     
			 case 5:
			   
			   
			    printf("Fisiere partajate:\n");
			    
			    /* Afisare toate fisierele pentru nume_client */
			    incr = 0;
			    rem = 0;
			    pch=strchr(buffer,':');
			    while (pch!=NULL) {
				
				found = pch - buffer + 1;
				
				printf(" %s \n", 
				    strndup(buffer + rem, found - rem -1));
				rem = found;
				  
				
				
				pch=strchr(buffer+found,':');
				incr++;
			    }
			    
			    
			    execute = -3;
			    break;
			  
			 /* Am primit comanda quit */   
			 case 6:   
			   
			   printf("Conexiunile s-au inchis.\n");
			   
			   close(sockfd);
			   close(sockfd_listen);
			   close(sockfd_to_send);
			   close(sockfd_to_send_file);
			   close(sockfd_to_send_share);
			   
			   return;
			   execute = -3;
			   break;
			   
			 /* Am primit comanda getfile */
			 case 7:  
			   
			    incr = 0;
			    rem = 0;
			     
			      memset(from_name, 0, 100);
			      memset(from_ip, 0, 100);
			      memset(from_port, 0, 100);
			      
			      memset(to_send_ip, 0, 100);
			      memset(to_send_port, 0, 100);
			      memset(file_name, 0, 100);
			      
			      /* Parsam numele clientului care cere fiserul,
			       * ip-ul si portul acestuia, precum si ip-ul si
			       * portul clientului de la care descarcam 
			       * fisierul */
			      pch=strchr(buffer,':');
			      while (pch!=NULL) {
				  if (incr >= 5) break;
				  found = pch - buffer + 1;
				  
				  if (incr == 0) 
				    sprintf (from_name, "%s", 
						    strndup(buffer+ rem, found 
								- rem -1));
				  
				  if (incr == 1) 
				    sprintf (to_send_ip, "%s", 
						    strndup(buffer+ rem, found 
								- rem -1));
				  if (incr == 2)
				    sprintf (to_send_port, "%s", 
						    strndup(buffer+ rem, found 
								  - rem -1));
				    
				  if (incr == 3)
				    sprintf (from_ip, "%s", 
						    strndup(buffer+ rem, found 
								  - rem -1));
				    
				   if (incr == 4)
				    sprintf (from_port, "%s", 
						    strndup(buffer+ rem, found 
								  - rem -1));
				  rem = found;
				 
				  pch=strchr(buffer+found,':');
				  incr++;
				  
			      }
			    
			      
			      if (strcmp(from_name, er) == 0) {
			      
				  printf("Error: ");
				  printf("%s", buffer + rem);
			      }
			      else {
				  
				  sprintf(file_name, "%s", buffer + rem);
	  
				  struct sockaddr_in for_send_addr_share;
				    
				    memset((char *) &for_send_addr_share, 0, 
						   sizeof(for_send_addr_share));
				    
				    
				     sockfd_to_send_share = socket(AF_INET, 
								SOCK_STREAM, 0);
				     if (sockfd_to_send_share< 0) 
					    error("ERROR opening socket");
			      
				  
				    
				    for_send_addr_share.sin_family = AF_INET;
				    inet_aton(from_ip, 
					      &(for_send_addr_share.sin_addr));
				    for_send_addr_share.sin_port = 
							 htons(atoi(from_port));
				    
				    if (connect(sockfd_to_send_share,
				      (struct sockaddr*) &for_send_addr_share,
					      sizeof(for_send_addr_share)) < 0) 
					  error("ERROR connecting");
				    
				    memset(aux_buffer, 0, BUFLEN);
				    sprintf(aux_buffer,"File %s:%s:%s:",
					    file_name,to_send_ip, to_send_port);
				    memset(buffer, 0, BUFLEN);
				    sprintf(buffer, "%s", aux_buffer);
				    
				    send (sockfd_to_send_share, buffer, 
							    strlen(buffer), 0);
			      printf("Fisierul a fost descarcat cu succes.\n");
				    
			      }
			   
			   execute = -3;
			   break;
			}
		  
			
		  
		  
		}
	    }
	   /* Socket de ascultare al clientilor */ 
        } else if (FD_ISSET(sockfd_listen, &read_set)) {
	    
	     int clilen, newsockfd;
	     struct sockaddr_in cli_addr;
	   clilen = sizeof(cli_addr);
	  if ((newsockfd = accept(sockfd_listen, (struct sockaddr *)
	      &cli_addr, &clilen)) == -1) {
	    error("ERROR in accept");
	  } 
	  else {
	     
	      memset(buffer, 0, BUFLEN);
	      len = recv(newsockfd, buffer, BUFLEN, 0);
	      if (len <= 0) {
                break;
	      }
	      
	      
	       memset(first_word, 0, 100);
	       
	       incr = 0;
	       rem = 0;
	       pch=strchr(buffer,' ');
	      while (pch!=NULL) {
		if (incr >= 1) break;
		found = pch - buffer + 1;
				  
		if (incr == 0) 
		sprintf (first_word, "%s", 
			strndup(buffer+ rem, found 
				- rem -1));
				  
	
		rem = found;
				 
		pch=strchr(buffer+found,' ');
		incr++;
				  
	      }
	      
	      /* Daca este mesaj, afiseaza-l */
	      if (strcmp(first_word, "From") == 0) {
	      
		      printf("%s\n", buffer);
	      }
	      else { 
		  /* Daca este fisier conecteaza-te la client si trimite 
		   * fisierul */
		  if (strcmp(first_word, "File") == 0) {
		
		    memset(aux_buffer, 0, BUFLEN);
		    sprintf(aux_buffer, "%s", buffer + rem);
		    
		    memset(buffer, 0, BUFLEN);
		    sprintf(buffer, "%s", aux_buffer);
		    
		    
		    
		    /* Parsare nume fisier, ip-ul si portul unde trimitem */
			    incr = 0;
			    rem = 0;
			     
			      memset(from_ip, 0, 100);
			      memset(from_port, 0, 100);
			      
			      memset(file_name, 0, 100);
			      
			      pch=strchr(buffer,':');
			      while (pch!=NULL) {
				  if (incr >= 3) break;
				  found = pch - buffer + 1;
				  
				  if (incr == 0) 
				    sprintf (file_name, "%s", 
						    strndup(buffer+ rem, found 
								- rem -1));
				  
				  if (incr == 1) 
				    sprintf (from_ip, "%s", 
						    strndup(buffer+ rem, found 
								- rem -1));
				  if (incr == 2)
				    sprintf (from_port, "%s", 
						    strndup(buffer+ rem, found 
								  - rem -1));
				  rem = found;
				 
				  pch=strchr(buffer+found,':');
				  incr++;
				  
			      }
			      
			      
				  /* Deschidere fisier pentru citire */
				  
				  fd=open(file_name,O_RDONLY);
				  
				  int lung;
				  
				  memset(buffer, 0, BUFLEN);
				  
				   struct sockaddr_in for_send_addr_file;
				    
				    memset((char *) &for_send_addr_file, 0, 
						    sizeof(for_send_addr_file));
				     sockfd_to_send_file = socket(AF_INET, 
								SOCK_STREAM, 0);
				     if (sockfd_to_send_file < 0) 
					    error("ERROR opening socket");
			     
				    /* Trimit mesaj la client sa deschida un
				     * fisier pentru a primi date in el */
				    for_send_addr_file.sin_family = AF_INET;
				    inet_aton(from_ip, 
						&(for_send_addr_file.sin_addr));
				    for_send_addr_file.sin_port = 
							 htons(atoi(from_port));
				    
				    if (connect(sockfd_to_send_file,
				      (struct sockaddr*) &for_send_addr_file,
						sizeof(for_send_addr_file)) < 0) 
					  error("ERROR connecting");
				  
				    
				    
				    
				    memset(aux_buffer, 0, BUFLEN);
				    sprintf(aux_buffer, "Open %s", file_name);
				    memset(buffer, 0, BUFLEN);
				    sprintf(buffer, "%s", aux_buffer);
				   
				    send (sockfd_to_send_file, buffer, 
							    strlen(buffer), 0);
				    
				    memset(buffer, 0, BUFLEN);
				  
				  
				  /* Trimit datele din fisier */
				  while((lung = read(fd,buffer,800))>0){ 
				        
				    memset((char *) &for_send_addr_file, 0, 
						    sizeof(for_send_addr_file));

				     sockfd_to_send_file = socket(AF_INET, 
								SOCK_STREAM, 0);
				     if (sockfd_to_send_file < 0) 
					    error("ERROR opening socket");
			      
				    for_send_addr_file.sin_family = AF_INET;
				    inet_aton(from_ip, 
						&(for_send_addr_file.sin_addr));
				    for_send_addr_file.sin_port = 
							 htons(atoi(from_port));
				    
				    if (connect(sockfd_to_send_file,
				      (struct sockaddr*) &for_send_addr_file,
					 sizeof(for_send_addr_file)) < 0) 
					  error("ERROR connecting");
				  
				    memset(aux_buffer, 0, BUFLEN);
				    sprintf(aux_buffer, "File_send %s", buffer);
				    memset(buffer, 0, BUFLEN);
				    sprintf(buffer, "%s", aux_buffer);
				    send (sockfd_to_send_file, buffer, 
							    strlen(buffer), 0);
				    
				    memset(buffer, 0, BUFLEN);
				  }
				  
				   
				    memset((char *) &for_send_addr_file, 0, 
						    sizeof(for_send_addr_file));
				    
				    
				     sockfd_to_send_file = socket(AF_INET, 
								SOCK_STREAM, 0);
				     if (sockfd_to_send_file < 0) 
					    error("ERROR opening socket");
			      
				  
				    /* Trimit mesaj de inchidere fisier unde
				     * s-au trimis datele */
				    for_send_addr_file.sin_family = AF_INET;
				    inet_aton(from_ip, 
						&(for_send_addr_file.sin_addr));
				    for_send_addr_file.sin_port = 
							 htons(atoi(from_port));
				    
				    if (connect(sockfd_to_send_file,
				      (struct sockaddr*) &for_send_addr_file,
						sizeof(for_send_addr_file)) < 0) 
					  error("ERROR connecting");
				  
				    memset(aux_buffer, 0, BUFLEN);
				    sprintf(aux_buffer, "Close %s", file_name);
				    memset(buffer, 0, BUFLEN);
				    sprintf(buffer, "%s", aux_buffer);
				    
				    send (sockfd_to_send_file, buffer, 
							    strlen(buffer), 0);
				    
				    memset(buffer, 0, BUFLEN);
				  
				   		    
		  }
		  else {
		  
		    /* Daca s-a primit File_send (date din fisier), atunci
		     * le vom pune intr-un fisier*/
		    if (strcmp(first_word, "File_send") == 0) {
			
			
			
			 memset(aux_buffer, 0, BUFLEN);
			sprintf(aux_buffer, "%s", buffer + rem);
		    
			memset(buffer, 0, BUFLEN);
			sprintf(buffer, "%s", aux_buffer);
	
			fputs(buffer, fd_1);

		    }
		    else {
		      /* Daca s-a primit mesaj de deschidere a unui nou fisier
		       * vom deschide un nou fisier cu numele 
		       * share_(nume_fiser_descarcat) */
		      if (strcmp(first_word, "Open") == 0) {
			  
			  memset(nume_fisier, 0, 100);
			  
			  sprintf(nume_fisier, "share_%s", buffer + rem);
			  
			  fd_1 = fopen(nume_fisier, "w");
			 
			
		      }
		    
		      else {
			/* Daca s-a primit mesaj de inchidere a fisierului
			 * vom inchide fisierul unde s-au descarcat datele */
			if (strcmp(first_word, "Close") == 0) {
			 
			  fclose(fd_1);
			}
		      }
		    }  
		  }
		  
	      }
	      close(newsockfd);
	      
	  }
	}
      }
    }
    close(fd);
  
    close(sockfd);
    close(sockfd_listen);
    close(sockfd_to_send);
    close(sockfd_to_send_file);
    close(sockfd_to_send_share);
    
    return 0;
}


