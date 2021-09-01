#include <stdio.h>
#include <sys/time.h>
//double time_diff(struct timeval x , struct timeval y);

int main(){
	//struct timeval before , after;
	int N;
	int x=0,y=0;
	FILE *file;
	FILE *ofile;
	
	file = fopen("qr_code_64x64_grayscale.dat","r"); // other file names are:"qr_code_128x128_grayscale.dat" and "qr_code_512x512_grayscale.dat"
	ofile = fopen("outputc.txt","w");
	
	fscanf(file,"%d",&N);
	
	int arr[N][N];
	
	while(x < N)
	{	
		while(y < N){
		
		fscanf(file,"%d",&arr[x][y]);
		y++;}

		x++;
		y=0;
	}
	
	x = 0;
	y = 0;
	
	//gettimeofday(&before , NULL);
	
	while(x<N){
		while(y<N){
		if(arr[x][y]<=127){
			arr[x][y]=0;
		}
		else if(arr[x][y]>127){
			arr[x][y]=255;
		}
		y++;
		}
	x++;
	y=0;
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


	return 0;
}

	//double time_diff(struct timeval x , struct timeval y)
//{
   // double x_ms , y_ms , diff;
      
   // x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
   // y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
      
   // diff = (double)y_ms - (double)x_ms;
      
   // return diff;
//}