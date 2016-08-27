/* Lazar Iulian 325CA */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 100
#define BUFLEN 1500
#define NEG -3

typedef struct data {
    int active;
    char name[100];
    char ip_addr[30];
    int socket;
    int port;
    int correct_name;
    long int time;
    char files[100][100];
    int num_files_shared;
    int port_listening;
} DATA;

void error(char *msg)
{
    perror(msg);
    exit(1);
}


/* Initializare vector clienti */
 void initializare_clienti (DATA *clients) {
  int i, j;
  for( i = 0 ; i < MAX_CLIENTS; i++) {
     
	clients[i].active = 0;
	memset(clients[i].name, 0, 100);
	memset(clients[i].ip_addr, 0, 30);		     
	clients[i].socket = -3;
	clients[i].port = -3;		
	clients[i].correct_name = 0;
	clients[i].time = 0;
	for (j = 0; j < 100; j++)
		memset(clients[i].files[j], 0, 100);
	clients[i].num_files_shared = 0;
	clients[i].port_listening = 0;
	
  }
}

int main(int argc, char *argv[])
{
  int sockfd, newsockfd, portno, clilen;
  char buffer[BUFLEN];
  char aux_buffer[BUFLEN];
  struct sockaddr_in serv_addr, cli_addr;
  int n, i, j, k, status, k_1;
  int num_clients = 0;

  fd_set read_fds;   //multimea de citire folosita in select()
  fd_set tmp_fds;	//multime folosita temporar 
  int fdmax;		//valoare maxima file descriptor din multimea read_fds
   
  int execute = -3;
  
  /*Alocare dinamica a informatiilor despre clienti */
  //DATA clients[MAX_CLIENTS];
  DATA *clients = (DATA*) malloc (sizeof(DATA)*MAX_CLIENTS);
     
  /* Lista cu comenzi posibile */
  char *tasks[] = { "listclients", "infoclient", "message", "sharefile", 
		    "unsharefile", "getshare", "quit", "getfile"};
  int correct_name = 0;
  int poz_in_vect;
  char pars_command_1[100];
  char pars_command_2[100];
  char pars_command_3[BUFLEN];
  time_t seconds_fin, dif;
  int getshare = -3;
  int file_dup = 0;
  char *command_status = "status";
  char *command_quit = "quit";
  int exist = 0;

  /* Initializare vector clienti */
  initializare_clienti(clients);
    
  if (argc < 2) {
    fprintf(stderr,"Usage : %s port\n", argv[0]);
    exit(1);
  }

  //golim multimea de descriptori de citire (read_fds) si multimea tmp_fds 
  FD_ZERO(&read_fds);
  FD_ZERO(&tmp_fds);
     
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
    error("ERROR opening socket");
     
  portno = atoi(argv[1]);

  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;	// foloseste adresa IP a masinii
  serv_addr.sin_port = htons(portno);
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) < 0) 
    error("ERROR on binding");
    
  listen(sockfd, MAX_CLIENTS);
  //adaugam noul file descriptor (socketul pe care se asculta conexiuni) in 
  //multimea read_fds
  FD_SET(sockfd, &read_fds);
  
  fdmax = sockfd;
  
  FD_SET(STDIN_FILENO, &read_fds);
  
  printf("Serverul este pornit...\n");
  // main loop
  while (1) {
    tmp_fds = read_fds; 
      if (select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1) 
	error("ERROR in select");
	
      
      
    for(i = 0; i <= fdmax; i++) {
      
      
      if (FD_ISSET(i, &tmp_fds)) {
	
	if (i == sockfd) {
	  // a venit ceva pe socketul de ascultare = o noua conexiune
	  // actiunea serverului: accept()
	  clilen = sizeof(cli_addr);
	  if ((newsockfd = accept(sockfd, (struct sockaddr *)
	      &cli_addr, &clilen)) == -1) {
	    error("ERROR in accept");
	  } 
	  else {
	      //adaug noul socket intors de accept() la multimea descriptorilor
	      //de citire
	      FD_SET(newsockfd, &read_fds);
	      if (newsockfd > fdmax) {			
		fdmax = newsockfd;
	      }
	  }
	  printf("Noua conexiune de la %s, port %d, socket_client %d\n ", 
		 inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), 
		 newsockfd);
					
	  /* Clientul s-a conectat (este activ) pe un anumit socket si port */
	 
	  clients[num_clients].active = 1;
	  sprintf(clients[num_clients].ip_addr, "%s", 
					      inet_ntoa(cli_addr.sin_addr));
	  clients[num_clients].socket = newsockfd;
	  clients[num_clients].port = ntohs(cli_addr.sin_port);	
	  
	  /* Ora conectarii */
	  time_t seconds;
	  seconds = time (NULL);
	  clients[num_clients].time = seconds; 
	  
	  num_clients++;
	  if (num_clients == MAX_CLIENTS) {
	      printf("Serverul este momentan plin!");
	  }
					
	}				
	else { 
	  if (i != STDIN_FILENO){
	    // am primit date pe unul din socketii cu care vorbesc cu clientii
	    //actiunea serverului: recv()
	    memset(buffer, 0, BUFLEN);
	    if ((n = recv(i, buffer, sizeof(buffer), 0)) <= 0) {
		if (n == 0) {
		//conexiunea s-a inchis
		printf("selectserver: socket %d hung up\n", i);
		} 
		else {
		    error("ERROR in recv");
		}
						
						
		/* Pozitia in vectorul de clienti al clientului cu socketul 
		 * egal cu cel curent */
		for (k = 0; k < num_clients; k++)
		   if (clients[k].socket == i)
		      poz_in_vect = k;
				
		/* Stergem din vector clientul care a iesit */  
	
		for (k = poz_in_vect; k < num_clients-1; k++) {  
		      
		    clients[k].active = clients[k+1].active;
		    sprintf(clients[k].name, "%s", clients[k+1].name);
		    sprintf(clients[k].ip_addr, "%s", clients[k+1].ip_addr);
		    clients[k].socket = clients[k+1].socket;
		    clients[k].port = clients[k+1].port;	
		    clients[k].correct_name =  clients[k+1].correct_name;
		    clients[k].time = clients[k+1].correct_name;
		    for (j = 0; j < 100; j++)
		      sprintf(clients[k].files[j], "%s", clients[k+1].files[j]);
		    clients[k].num_files_shared = clients[k+1].num_files_shared;
		    clients[k].port_listening = clients[k+1].port_listening;
		    
		}
		
	
		clients[num_clients - 1].active = 0;
		memset(clients[num_clients - 1].name, 0, 100);
		memset(clients[num_clients - 1].ip_addr, 0, 30);		     
		clients[num_clients - 1].socket = -3;
		clients[num_clients - 1].port = -3;		
		clients[num_clients - 1].correct_name = 0;
		clients[num_clients - 1].time = 0;
		for (j = 0; j < 100; j++)
		      memset(clients[num_clients].files[j], 0, 100);
		clients[num_clients - 1].num_files_shared = 0;
		clients[i].port_listening = 0;
		  
						
		num_clients--;
									
		close(i); 
		FD_CLR(i, &read_fds); // scoatem din multimea de citire socketul 
	    } 
					
	    else { //recv intoarce >0
				
   printf("Am primit de la clientul de pe socketul %d, mesajul: \nMesaj:\t%s\n",
								  i, buffer);
						
		char *pch;
		int found;
		int incr = 0;
		
		
		/* Caut pana la sfarsitul numele clientului */
		pch=strchr(buffer,':');
		while (pch!=NULL) {
		    if (incr >= 2) break;
		    found = pch - buffer + 1;
		    pch=strchr(buffer+found,':');
		    incr++;
		}
						 
						 
		char only_message[BUFLEN];
		char client_name[100];
		int it;
		int ok = 0;
						
						 
		memset(only_message, 0, BUFLEN);
		memset(client_name, 0, 100);
						 
		/* Parsare nume client */
		for(it = 5; it < found-1; it++)
		    client_name[it-5] = buffer[it];
		client_name[found-1] = '\0';
							
		for (k = 0; k < num_clients; k++) {
		    
		    if (clients[k].socket != i) {
			if (strcmp(clients[k].name, client_name) == 0) {
				ok = 1;
								
			}
		    }
		}
						
		/* Pozitia in vectorul de clienti al clientului cu socketul 
		 * egal cu cel curent */
		for (k = 0; k < num_clients; k++)
			if (clients[k].socket == i)
				poz_in_vect = k;
						
		/* Daca nu mai exista client cu acelasi nume */    
		if ((ok == 0) && (clients[poz_in_vect].correct_name > 0)) {
							
		    /*Parsare mesaj */
		     sprintf(only_message, "%s", buffer + found);
		    
		    
		    memset(pars_command_1, 0, 100);
		    memset(pars_command_2, 0, 100);
		    memset(aux_buffer, 0, BUFLEN);
		    
		    /* Parsez comanda pe care o primesc si mesajul daca exista
		     * (aici voi parsa primul si al doilea parametru al comenzii
		     * daca exista */
		    char *pc;
		    int iter;
		    iter = 0;
		    sprintf(aux_buffer, "%s", only_message);
		    pc = strtok(aux_buffer, " \n");
		    
		    while (pc != NULL) {
			
		        if (iter == 0) {
			    sprintf(pars_command_1, "%s", pc);
			  
			}
			if (iter == 1) {
			    sprintf(pars_command_2, "%s", pc);
			      
			}
			pc = strtok (NULL, " \n");
			iter++;
		    }
		    
		    /* Extrag al treilea parametru al comenzii daca exista 
		     * (inclusiv cu "\n" */
		    iter = 0;
		    pch=strchr(only_message,' ');
		    while (pch != NULL) {
		      if (iter >= 2) break;
		      found = pch - only_message + 1;
		      
		      pch=strchr(only_message + found,' ');
		      iter++;
		    }
		    
		    memset(pars_command_3, 0, BUFLEN);
		    
		    sprintf(pars_command_3, "%s", only_message + found);
		   
		    
		    /* Determin comanda de la client */  
		    for (k = 0; k < 8; k++)
			 if (strcmp(pars_command_1, tasks[k]) == 0)
				execute = k;
							  
		    /* Executa comanda */  
		    switch (execute) {
							
			/* ----- Comanda listclients -----*/
			case 0: 
				
			    /* Trimit clientului informatii despre toti clientii
			     * conectati la server. (nume, adresa ip, socket si
			     * port). In fata acestor informatii voi adaugam
			     * numele comenzii executate*/
			    memset(buffer, 0, BUFLEN);
			    
			    sprintf(buffer, "%s:", pars_command_1);
			    for (k = 0; k < num_clients; k++) {
				memset(aux_buffer, 0, BUFLEN);
				sprintf(aux_buffer, "%s:%s:%d:%d:", 
					  clients[k].name, clients[k].ip_addr, 
					    clients[k].socket, clients[k].port); 
				sprintf(buffer, "%s%s", buffer, aux_buffer);
				
			    }
							      
			    status = send(i,buffer,strlen(buffer) + 1, 0);
			    if (status <= 0) {
				 printf("Error: Problem here\n");
			     }
									      
			     execute = -3;
			      break;
			
			/* ----- Comanda infoclient -----*/      
			case 1:
			  
			    seconds_fin = time (NULL);
			    
			    for (k = 0; k < num_clients; k++) {
				  if ((clients[k].active == 1) && 
				      (strcmp (clients[k].name, pars_command_2)
				      == 0)) {
			    
					dif = seconds_fin - clients[k].time;
					if (dif < 0) dif = -dif;
					
					sprintf(buffer, "%s:%s:%ld:%d:",
					    pars_command_1, pars_command_2, dif, 
							  clients[k].port_listening);
			    
			    
			    
					status = send(i,
						  buffer,strlen(buffer) + 1, 0);
					if (status <= 0) {
					    printf("Error: Problem here\n");
					}
					
					
				  }
			    }
			    
			    execute = -3;
			    break;
			      
			/* ----- Comanda message -----*/      
			case 2:
			    
			    
			    /* Pozitia in vectorul de clienti al clientului 
			     * cu socketul egal cu cel curent */
			    for (k = 0; k < num_clients; k++)
				if (clients[k].socket == i)
				    poz_in_vect = k;
			    
			    /* Trimit mesajul clientului cu ip si portul de 
			     * ascultare al clientului caruia vrea sa ii trimita
			     * mesajul*/
			    exist = 0;
			    for (k = 0; k < num_clients; k++) {
			     
				  if ((clients[k].active == 1) && 
				      (strcmp (clients[k].name, pars_command_2)
				      == 0)) {
				      
				      exist = 1;
				      memset(buffer, 0, BUFLEN);
			    
				      sprintf(buffer, "%s:%s:%s:%d:%s",
						pars_command_1, 
						clients[poz_in_vect].name, 
						clients[k].ip_addr, clients[k].
								port_listening,
						pars_command_3);
				      
				      status = send(i,
						  buffer,strlen(buffer) + 1, 0);
				      if (status <= 0) {
					  printf("Error: Problem here\n");
				      }
				    
				  }
			    }
			    /* Daca numele clientului caruia vrem sa ii trimitem
			     * mesaj nu exista, atunci eroare */
			    if (exist == 0) {
			     memset(buffer, 0, BUFLEN);
			     sprintf(buffer, 
			    "%s:Error: Clientul %s nu este conectat la server\n"
					    , pars_command_1, pars_command_2);
			       status = send(i,buffer,strlen(buffer) + 1, 0);
				      if (status <= 0) {
					  printf("Error: Problem here\n");
				      }
			    }
			    execute = -3;
			    break;
			    
			/* --- Comanda sharefile */   
			case 3:
			  
			     /* Pozitia in vectorul de clienti al clientului 
			     * cu socketul egal cu cel curent */
			    for (k = 0; k < num_clients; k++)
				if (clients[k].socket == i)
				    poz_in_vect = k;
			    
			    /* Adaugare la client fisier partajat si incremetare
			     * numar fisiere partajate */
			   
			   
			    if (strcmp( pars_command_2, "") != 0) {
			      
			      file_dup = -3;
			      for(k = 0; k < clients[poz_in_vect].
				 num_files_shared; k++)
				 if (strcmp(clients[poz_in_vect].files[k], 
				    pars_command_2) == 0)
					file_dup = k;
			      
			      if (file_dup == -3) { 
				sprintf(clients[poz_in_vect].files[
					 clients[poz_in_vect].num_files_shared], 
							  "%s", pars_command_2);
				clients[poz_in_vect].num_files_shared++;
				
				
				memset(buffer, 0, BUFLEN);
				sprintf(buffer, 
				      "%s:Fisierul a fost partajat cu succes.",
							      pars_command_1);
				
				status = send(i, buffer,strlen(buffer) + 1, 0);
					  if (status <= 0) {
					      printf("Error: Problem here\n");
					  } 
			      }
			      else {
			      
				memset(buffer, 0, BUFLEN);
				sprintf(buffer,"%s:Error. Cauza: nume duplicat."
							      ,pars_command_1);
			      
				status = send(i, buffer,strlen(buffer) + 1, 0);
				if (status <= 0) {
					    printf("Error: Problem here\n");
				} 
				
			      }
			      
			     }
			     else {
			     
			        memset(buffer, 0, BUFLEN);
			      sprintf(buffer,"%s:Error. Cauza: nume inexistent."
							      ,pars_command_1);
			      
			      status = send(i, buffer,strlen(buffer) + 1, 0);
			      if (status <= 0) {
					    printf("Error: Problem here\n");
			      } 
			       
			       
			    }
			    
			    execute = -3;
			    break;
			    
			    
			/* --- Comanda unsharefile */   
			case 4:
			  
			    /* Pozitia in vectorul de clienti al clientului 
			     * cu socketul egal cu cel curent */
			    for (k = 0; k < num_clients; k++)
				if (clients[k].socket == i)
				    poz_in_vect = k;
				
			    /* Stergere fisier partajat si decrementare fisiere
			     * partajate */
			    int unshare = -3;
			    for(k = 0; k < clients[poz_in_vect].
				num_files_shared; k++)
				  if (strcmp(clients[poz_in_vect].files[k], 
				      pars_command_2) == 0)
					unshare = k;
			    if (unshare != NEG)  {
				/* Stergem fisierul din lista de fisiere
				 * partajate */
				for(k = unshare; k < clients[poz_in_vect].
				    num_files_shared - 1; k++) {
				
				    sprintf(clients[poz_in_vect].files[k], 
					 "%s", clients[poz_in_vect].files[k+1]);
				  
				}
				memset (clients[poz_in_vect].
					files[clients[poz_in_vect].
					num_files_shared - 1], 0, 100);
				/*Decrementam numarul fisierelor partajate */
				clients[poz_in_vect].num_files_shared--;
				
				memset(buffer, 0, BUFLEN);
				sprintf(buffer, "%s:Fisierul a fost sters.",
							      pars_command_1);
			      
				status = send(i, buffer,strlen(buffer) + 1, 0);
				if (status <= 0) {
					    printf("Error: Problem here\n");
				} 
			    }
			    else {
			      
				memset(buffer, 0, BUFLEN);
				sprintf(buffer, "%s:Fisierul nu exista.",
								pars_command_1);
			      
				status = send(i, buffer,strlen(buffer) + 1, 0);
				if (status <= 0) {
					    printf("Error: Problem here\n");
				} 
			      
			    }
			    
			    execute = -3;
			    break;
			    
			    
		      /* --- Comanda getshare --- */
		      case 5:
			
			getshare = -3;
			/* Pozitia in vectorul de clienti al clientului 
			 * cu numele egal cu nume_client din comanda */
			for (k = 0; k < num_clients; k++) {
				  if ((clients[k].active == 1) && 
				      (strcmp (clients[k].name, pars_command_2)
				      == 0)) {
				     getshare = k;
				  }
			}
			
			if (getshare != -3) {
			  
			  memset(buffer, 0, BUFLEN);
			  sprintf(buffer, "%s:",pars_command_1);
			  
			  for (k = 0; k < clients[getshare].num_files_shared; 
									  k++) {
				memset(aux_buffer, 0, BUFLEN);
				sprintf(aux_buffer, "%s:",clients[getshare].
								      files[k]);
				sprintf(buffer, "%s%s", buffer, aux_buffer);
			    
			  }
			  
			  status = send(i, buffer,strlen(buffer) + 1, 0);
				  if (status <= 0) {
					      printf("Error: Problem here\n");
				  } 
			      
			}
			else {
			  
			      memset(buffer, 0, BUFLEN);
			      sprintf(buffer, 
				      "%s:Error. Numele clientului necunoscut.:"
							      ,pars_command_1);
			      status = send(i, buffer,strlen(buffer) + 1, 0);
			      if (status <= 0) {
					    printf("Error: Problem here\n");
			      } 
			}
			execute = -3;
			break;
			
		      /* --- Comanda quit --- */	
		      case 6:
			
			memset(buffer, 0, BUFLEN);
			sprintf(buffer, "%s:Exit" ,pars_command_1);
			
			status = send(i, buffer,strlen(buffer) + 1, 0);
			if (status <= 0) {
					    printf("Error: Problem here\n");
			 } 
			
			execute = -3;
			break;
			
		      /* --- Comanda getfile ---*/
		      case 7:
			
			
			
			/* Pozitia in vectorul de clienti al clientului 
			     * cu socketul egal cu cel curent */
			    for (k = 0; k < num_clients; k++)
				if (clients[k].socket == i)
				    poz_in_vect = k;
			    
			    /* Trimit mesajul clientului cu ip si portul de 
			     * ascultare al clientului de la care voi lua
			     * fisierul*/
			    exist = 0;
			    int exist_file = 0;
			  
			    for (k = 0; k < num_clients; k++) {
			     
				  if (pars_command_3[strlen(pars_command_3)-1] 
				      == '\n')
				      pars_command_3[strlen(pars_command_3)-1] 
					  = '\0';
				  
				  if ((clients[k].active == 1) && 
				      (strcmp (clients[k].name, pars_command_2)
				      == 0)) {
				      
				      exist = 1;
					
				      for(k_1 = 0; k_1 < clients[k].
						      num_files_shared; k_1++){
					   if (strcmp(clients[k].files[k_1],
							pars_command_3) == 0) {
						      
						exist_file = 1;
						memset(buffer, 0, BUFLEN);
									  
					 sprintf(buffer, "%s:%s:%s:%d:%s:%d:%s",
						  pars_command_1,
						  clients[poz_in_vect].name, 
						  clients[poz_in_vect].ip_addr,
						  clients[poz_in_vect].
								port_listening, 
						  clients[k].ip_addr, 
						  clients[k].port_listening,
						  pars_command_3);
									  
						  status = send(i,
						  buffer,strlen(buffer) + 1, 0);
						  if (status <= 0) {
						      printf
						      ("Error: Problem here\n");
						  }
					      }
					}	  
				      
				  }
			    }
			    /* Daca numele clientului caruia vrem sa ii trimitem
			     * mesaj nu exista, atunci eroare */
			    if ((exist == 0) || (exist_file == 0)) {
			     memset(buffer, 0, BUFLEN);
			     sprintf(buffer, 
			    "%s:Error: Clientul %s nu este conectat la server sau fisierul nu este partajat.\n"
					    , pars_command_1, pars_command_2);
			       status = send(i,buffer,strlen(buffer) + 1, 0);
				      if (status <= 0) {
					  printf("Error: Problem here\n");
				      }
			    }
			
			
			
			
			
			execute = -3;
			break;
			
		    }
		}
		else {
		  /* Daca exista un nume de client identic, atunci reject */
		  if (ok == 1) {
		      memset(buffer, 0, BUFLEN);
		      sprintf(buffer, "reject_client_dup");
				      			      
		      status = send(i,buffer,strlen(buffer) + 1, 0);
		      if (status <= 0) {
			      printf("Problem here\n");
		      }
							
		  }
		  else {
		     
		     sprintf(clients[poz_in_vect].name, "%s", client_name);
		      char str_port[100];
		      sprintf(str_port, "%s", buffer + found);
		      clients[poz_in_vect].port_listening = atoi(str_port);

		    memset(buffer, 0, BUFLEN);
		     sprintf(buffer, "Accept");
		      /* Adaug numele clientului in vector */
		     
		      status = send(i,buffer,strlen(buffer) + 1, 0);
		      if (status <= 0) {
			printf("Problem here\n");
		      }
		      memset(buffer, 0, BUFLEN);
		      clients[poz_in_vect].correct_name++;
		  }
						  
						  
		}
						
	      }
	}
	else {
	
	  if (i == STDIN_FILENO) {
	    
	    //citesc de la tastatura
	    memset(buffer, 0 , BUFLEN);
	    fgets(buffer, BUFLEN-1, stdin);
	    
	    buffer[strlen(buffer)-1] = '\0';
	    
	    /* Daca de la tastatura s-a introdus "status" */
	    if (strcmp(buffer, command_status) == 0) {
		  printf("*** Status:\n");
		  printf("---------------------------------------------------");
		  printf("--------------------\n");
		  for (k = 0; k < num_clients; k++) {
		  
		    printf("%d. Nume client: %*s \t",k+1, 12, clients[k].name); 
		    printf("IP: %*s \t", 5, clients[k].ip_addr);
		    printf("Socket: %*d \t", 3, clients[k].socket);
		    printf("Port: %*d \n", 5, clients[k].port);
		    printf(" - Fisiere partajate:\n");
		    for(j = 0; j < clients[k].num_files_shared; j++) {
			printf("\t %d. %s \n",j+1, clients[k].files[j]);
		      
		      
		    }
		  printf("---------------------------------------------------");
		    printf("--------------------\n");
		    
		  }
	      
	      
	    }
	    else { /* Quit server */
	    
	      if (strcmp(buffer, command_quit) == 0) {
		       printf("Serverul se inchide...\n");
		       close(sockfd);
		       for(k = 0; k < num_clients; k++){
			    close(clients[k].socket);
			 
		       }
		       
		       return;
		
	      }
	      
	    }
	      
	    
	    
	    
	  }
	  
	}
       }
      }
    
    }
  }


  close(sockfd);
   
  return 0; 
}


