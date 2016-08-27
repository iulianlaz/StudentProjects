#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lib.h"

#include<sys/time.h>

#define HOST "127.0.0.1"
#define PORT 10000



void send_file(char* filename, float w,int time_to_wait, float loss, float corrupt){
  msg t;
  
  
    
    int max_seq = (int) w + 1;
    if (max_seq == 1)
      max_seq = 2;
   
    
    /*I: Buffer for message */
    msg *frame = (msg*) malloc (max_seq*sizeof(msg));
    
    /* Number of frame to send*/
    int index = 0; 
    
    /* Next frame to confirm */
    int conf_frame = 0;
    
    char confirm_ack[10];
    int i;
    int ok = 1;
    int here = 0;
    int end = 0;
    int window = 0;
    char *find;
   
    
    
    
    memset(t.payload, '\0', 1400); 
  
    struct stat buf;
    if (stat(filename,&buf)<0){
      perror("Stat failed");
      return;
    }
    
    int fd = open(filename, O_RDONLY);

    if (fd<0){
      perror("Couldn't open file");
      return;
    }

   /* I: type = 1 -> Filename and size message  send*/
   t.type = 1;
   sprintf(t.payload,"%s\n%d\n",filename,(int)buf.st_size);
   t.len = strlen(t.payload)+1;
    
   
    /*I: Add frame number and max_seq to the end of the message */
    sprintf (t.payload, "%s%d\n%d" ,t.payload, index, max_seq);
   
     /*I: Add index in frame (buffer) */
     sprintf (frame[index].payload, "%s" ,t.payload);
  
     frame[index].len = t.len;
     frame[index].type = 1;
    
    
    /*I: Sending filename, filesize, index (frame number) and max_seq */
    printf("Trimitem: %s\n", frame[index].payload);
    send_message(&frame[index]);
    
    /* Receive ACK and window receiver size */
    msg* r = NULL; 
    while (!r) {
	    if (loss == 0) 
		r = receive_message();  
	    else
		r = receive_message_timeout(time_to_wait+100);
	    if (r) {
	      	      
	      if ( r->type == 5 ) {
		        
		    find = strchr(r->payload, '\n');
		    window = atoi(find+1);
		    printf("Win %d\n", window);
		    
		    
		     /* Change maximum window size if window < max_seq
		      * and window != 0 */
		     if (( window > 1) && (window < max_seq)) {
		     	    max_seq = window;
		     }
		     else window = 0; 
		     printf("Max_seq %d\n", max_seq);
		    
	      }
	   }
	   if (!r){
		
		perror("receive error");
		printf("Lost frame: %d\n", conf_frame);
			
		  /* Send again all the frames from conf_frame */
		 
		  
		 send_message(&frame[index]);
	   }
     }	   
	    
    memset(t.payload, '\0', 1400); 
    
    /* ---------------I: Read from file ---------------*/
    t.type = 2;  
    while (1) {  
  
      here = 0;
  
      memset(t.payload, '\0', 1400); 
      
      if (ok == 1) {
	    while (( (t.len = read(fd,&t.payload, 1380))>0) ){
	      
	      here = 1;
	      end = 0;
	      
	      /*I: Add frame number to the end of the message */
	      sprintf (t.payload, "%s%d" ,t.payload, index);
	            
	      /*I: Add index  in frame (buffer)*/
	      sprintf (frame[index].payload, "%s" ,t.payload);
	      
	      frame[index].len = t.len;
	      frame[index].type = 2;
	      
	      /*I: Sending message */      
	      
	      printf(" Se Trimite %d\n", index);
	
	      send_message(&frame[index]);
	      
	      index++;
	
	      memset(t.payload, '\0', 1400); 
	      
	      /* If index is >= max_seq, then index = 0 and stop reading,
	       * else if index ( number of frame) is equal with ACK recently
	       * confirmed then stop reading too */
	      if (index >= max_seq) {
		    index = 0; 
		    break;
	      }
	      else 
		  if (index == conf_frame)
			break;
			    
	      
	  }
	  
      
      }

      msg* r = NULL; 
      while (!r) {
	    if (loss == 0) 
		r = receive_message();  
	    else
		r = receive_message_timeout(time_to_wait+50);
	    if (r) {
		/*I: Extract frame number from ACK confirmation */
		printf("Am primit confirmare: %s %d\n", r->payload, r->len);
		
		     
		 sprintf(confirm_ack, "%s", (r->payload + 3));
		 conf_frame = atoi(confirm_ack);
		
		printf("Cadru: %d\n",  conf_frame);
		
		conf_frame++;
		
		for (i = 0; i < 10; i++)
		    confirm_ack[i] = '\0';
		
		ok = 1;
		
		if (conf_frame >= max_seq) {
		      conf_frame = 0;
		      ok = 1;
		      end = 1;	      
		}
		else	
		   if (conf_frame == index)
			return;
		   
		
		
	    }  
	    
	    /* If package confirmed ( ok == 1) and we reach the
	     * end of file ( here == 0) and (index == 0) and all packages 
	     * confirmed ( end = 1) then finish */  
	    if ((ok == 1) && (index == 0) && (here == 0) && (end == 1 ))
			return;
	   
	    if (!r){
		
		perror("receive error");
		printf("Lost frame: %d\n", conf_frame);
			
		  /* Send again all the frames from conf_frame */
		  int it;
		  it = conf_frame;  
		  do {
		     send_message(&frame[it]);
		    
		     it++;
		     if (it >= max_seq)
			      it = 0;
		  } while (it != index);
		
		ok = 0;
		
		break;

	    }
	}
	
	free(r); 
    }

    close(fd);
}


int main(int argc,char** argv){
  init(HOST,PORT);
  
  char *find;
  int speed, delay;
  float loss, corrupt;
  float w;
  int time_to_wait;
  
  
  if (argc<2){
    printf("Usage %s filename\n",argv[0]);
    return -1;
  }
  
  
  /*I: Extract speed, delay, loss and corrupt */
  find = strchr(argv[1], '=');
  speed = atoi(find+1);
  printf("%d\n", speed);
  
  
  find = strchr(argv[2], '=');
  delay = atoi(find+1);
  printf("%d\n", delay);
 
  
  find = strchr(argv[3], '=');
  loss = atof(find+1);
  printf("%f\n", loss);
  
  
  find = strchr(argv[4], '=');
  corrupt = atof(find+1);
  printf("%f\n", corrupt);
  
  /*I: Maximum window size */
  w = ((delay * speed * 1000) / (1400*8));
  printf("%f\n", w);
  
  time_to_wait = delay;
  
  send_file(argv[5], w, time_to_wait, loss, corrupt);
  return 0;
}
