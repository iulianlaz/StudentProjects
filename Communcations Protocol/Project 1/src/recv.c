#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(int argc,char** argv){
  msg *r,t;
  init(HOST,PORT);
  char filename[1400], filesize[1400];
  int fs;
  int window;
  char  *find;
  
  /* Extract window size from receiver */
   find = strchr(argv[1], '=');
  window = atoi(find+1);
  printf("%d\n", window);
  
  r = receive_message();
  
  if (!r){
    perror("Receive message");
    return -1;
  }

  int name = 1, crt = 0,i;

  /* Receive message until r->type == 1 */
  while (r->type != 1) {
    r = receive_message();
  }
  

  /* Create filename and size message */
  for (i=0;i<r->len;i++){
    if (crt>=1400){
      printf("Malformed message received! Bailing out");
      return -1;
    }

    if (name){
      if (r->payload[i]=='\n'){
	name = 0;
	filename[crt] = 0;
	crt = 0;
      }
      else 
	filename[crt++] = r->payload[i];
    }
    else {
      if (r->payload[i]=='\n'){
	name = 0;
	filesize[crt] = 0;
	crt = 0;
	break;
      }
      else 
	filesize[crt++] = r->payload[i];
    }
  }
  fs = atoi(filesize);
  char fn[2000];

  /* Receive filename and size + frame number + max_seq */
   int index = 0;
  int frame_expected;
  char nr_frame_expected[10];
  char str_max_seq[10];
  int max_seq;
   for (i = 0; i < 10; i++) {
      nr_frame_expected[i] = '\0';
      str_max_seq[i] = '\0';
   }
  
   memset(t.payload, '\0', 1400); 
   t.type = 3;
   
   
   /* Extract frame number and max_seq */
   int k = 0;
   int k2 = 0;
   int ok = 0;
   printf("%d %d\n", (r->len-1 + k), strlen(r->payload));
   while ((r->len-1 + k) < (strlen(r->payload))) {
     
	  if (r->payload[r->len-1 + k] == '\n') {
		ok = 1;
		k++;
		
	  }
	  else
	      if (ok == 0) {
		nr_frame_expected[k] = r->payload[r->len-1 + k];
		k++;
		
	      }
	      else {
		  if (ok == 1) {
		      str_max_seq[k2] = r->payload[ r->len-1 + k];
		      k2++;
		      k++;
		     
		  }
	      }
   }
	  
   frame_expected = atoi(nr_frame_expected);
   max_seq = atoi (str_max_seq);
   
    for (i = 0; i < 10; i++) {
      nr_frame_expected[i] = '\0';
      str_max_seq[i] = '\0';
    }
    
   printf ("Max_seq: %d\n" , max_seq);
   
   /*Sending  ACK + frame to confirm + window size from receiver*/
    t.type = 5;
    sprintf(t.payload, "ACK%d\n%d", frame_expected, window);
    t.len = strlen(t.payload);
    send_message(&t);
    memset(t.payload, '\0', 1400); 
   
    /* Change max_seq for sender */
     if (( window > 1) && (window < max_seq)) {
		     	    max_seq = window;
     } else window = 0;  
    
   
    for (i = 0; i < 10; i++)
	  nr_frame_expected[i] = '\0';
   
   sprintf(fn,"recv_%s", filename);
   printf("Receiving file %s of size %d\n",fn,fs);

  
 
   
  /*------------------ Receive message - step by step ---------------*/
  int fd = open(fn,O_WRONLY|O_CREAT,0644);
  if (fd<0) {
    perror("Failed to open file\n");
  }

  while (fs>0){
    printf("Left to read %d\n",fs);
    r = receive_message();
    if (!r){
      perror("Receive message");
      return -1;
    }    
    
    memset(t.payload, '\0', 1400);
    
    
    
    if (r->type == 2){
      
      /* ACK + frame to confirm */
      sprintf(t.payload, "ACK%s", (r->payload + r->len));
    
      sprintf(nr_frame_expected, "%s", (r->payload + r->len));
      frame_expected = atoi(nr_frame_expected);
    
      printf ("Frame: %d, Index: %d\n" , frame_expected, index); 
    
      for (i = 0; i < 10; i++)
	  nr_frame_expected[i] = '\0';
    } 
    
    else
      
      if (r->type == 1) {
	
	      /* Extract frame number and max_seq */
	   
	      while ((r->len-1 + k) < (strlen(r->payload))) {
     
		if (r->payload[r->len-1 + k] == '\n') {
		ok = 1;
		k++;
		
		}
		else
		  if (ok == 0) {
		      nr_frame_expected[k] = r->payload[r->len-1 + k];
		      k++;
		     
		    }
		    else {
			if (ok == 1) {
			    str_max_seq[k2] = r->payload[ r->len-1 + k];
			    k2++;
			    k++;
			 
		    }
		}
	      }
	  
	  frame_expected = atoi(nr_frame_expected);
	  max_seq = atoi (str_max_seq);
	  sprintf(t.payload, "ACK%d", frame_expected);
	  
	  for (i = 0; i < 10; i++) {
	    nr_frame_expected[i] = '\0';
	    str_max_seq[i] = '\0';
	  }
	
	
      }

    /* If frames are in order, write to file */
    if (index == frame_expected) {
	  write(fd, r->payload, r->len);
	  fs -= r->len;
	  index++;
    
	if (index >= max_seq)
	index = 0;
    
	free(r);

	/* Sending ACK with frame number confirmed */
	t.type = 3;
	t.len = strlen(t.payload);
	send_message(&t);
    
	memset(t.payload, '\0', 1400); 
    }
    else {
	  /* When is timeout */
    }
  }
  return 0;
}
