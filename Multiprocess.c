#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

	//double time_diff(struct timeval x , struct timeval y);
int main(){
	//struct timeval before , after;
   
    int temparr[8][8];
    int m,n;
	int N,k;

	int x=0,y=0;
	FILE *file;
	FILE *ofile;
	
	file = fopen("qr_code_64x64_grayscale.dat","r"); // other file names are:"qr_code_128x128_grayscale.dat" and "qr_code_512x512_grayscale.dat"
	
	fscanf(file,"%d",&N);
	
	int z=(N/8)*(N/8);
	
	int **arr;
	
	arr = (int**)malloc(N*sizeof(int*));
	
	while(x < N)
	{
		*(arr+x) = (int*)malloc(N*sizeof(int)); 
		x++;
	}
	x = 0;
	k=(N*N)/64;
	char filen[k][10];
	for(int i=0;i<k;i++){
		char tmp[10];
		snprintf(tmp, 10,"o%d.txt", i);
		strcpy(*(filen+i),tmp);
	}

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
	for(int i=0;i<z;i++)
    {  pid_t c=fork();
	
       switch(c){
       	case -1:
       		perror("fork error");
       		exit(1);
       	case 0:
        	m=0;
        	n=0;
			
        	x = i / (k/N);
			y = 64 * (i% (k/N));
        	
        	while(m<8){
        		while(n<8){

        			if(arr[x][y]<=127)
        				temparr[m][n]=0;
        			else if(arr[x][y]>127)
        				temparr[m][n]=255;
        		y++;
        		n++;	
        		}

        	m++;
        	n=0;		
        	}

        	m=0,n=0;
        	ofile = fopen(*(filen+i),"w");
	        while(m<8){
				while(n<8){
					fprintf(ofile,"%d\n",temparr[m][n]);
					n++;
					}
			m++;
			n=0;
			}
			fclose(ofile);
          
            exit(0); 
			

        
         
    } 
}
	
	while(wait(NULL)>0){}

	//gettimeofday(&after , NULL);
	//printf("Total time elapsed : %.0lf ms" , time_diff(before , after) );	
	ofile = fopen("outputa.txt","w");
	for(int i=0;i<k;i++){
		file = fopen(*(filen+i),"r");
		char c = fgetc(file);
		while (c != EOF) 
    	{ 
        fputc(c, ofile); 
        c = fgetc(file); 
    	}
		fclose(file);
	}
	

	x = 0;
	while(x < N)
	{
		free(*(arr+x));
		x++;
	}

	
	return 0;
}

//double time_diff(struct timeval x , struct timeval y)
//{
    //double x_ms , y_ms , diff;
      
   // x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    //y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
      
    //diff = (double)y_ms - (double)x_ms;
      
   // return diff;
//}