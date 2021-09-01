#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/time.h>

	int N,k;
	int **arr;
	int x=0,y=0;
	int k;
	pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;
	
	//double time_diff(struct timeval x , struct timeval y);

	void *myThread(void *vargp)
{ 	
	int val = *((int*)vargp);
	
    int m=0;
    int n=0;
    x = val / (k/N);
	y = 64 * (val % (k/N));
		
        	
        	while(m<8){
        		while(n<8){

        			if(arr[x][y]<=127)
        				arr[x][y]=0;
        			else if(arr[x][y]>127)
        				arr[x][y]=255;
        		y++;
        		n++;	
        		}

        	m++;
        	n=0;		
        	}
    
   
} 
	int main(){
		//struct timeval before , after;
		FILE *file;
		FILE *ofile;
		
		file = fopen("qr_code_64x64_grayscale.dat","r"); // other file names are:"qr_code_128x128_grayscale.dat" and "qr_code_512x512_grayscale.dat"
		ofile = fopen("outputb.txt","w");
		
		pthread_mutex_lock(&mymutex);
		
		fscanf(file,"%d",&N);
		
		k=(N*N)/64;
		int z=(N/8)*(N/8);
		
		pthread_mutex_unlock(&mymutex);
	
	
		
		arr = (int**)malloc(N*sizeof(int*));
		
		while(x < N)
		{
		*(arr+x) = (int*)malloc(N*sizeof(int)); 
		x++;
		}
		x = 0;
		while(x<N){
			while(y<N){
			fscanf(file,"%d",&arr[x][y]);
			y++;
			}
		x++;
		y=0;
		}
		x=0;
		y=0;
		//gettimeofday(&before , NULL);
		for(int i=0;i<z;i++){
		

		int *pass_val_ptr = (int*)malloc(sizeof(int));
		*pass_val_ptr = i;
		pthread_t thread;
		pthread_create(&thread, NULL, myThread, pass_val_ptr); 
   	    pthread_join(thread, NULL);
   	    
		}
		//gettimeofday(&after , NULL);
		//printf("Total time elapsed : %.0lf ms" , time_diff(before , after) );	
		x=0;
		y=0;

	while(x<N){
		while(y<N){
		fprintf(ofile,"%d\n",arr[x][y]);
		y++;
		}
	x++;
	y=0;
	}
	fclose(ofile);
	fclose(file);
		exit(0);
	}

	//double time_diff(struct timeval x , struct timeval y)
//{
    //double x_ms , y_ms , diff;
      
   // x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
   // y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
      
   // diff = (double)y_ms - (double)x_ms;
      
   // return diff;
//}