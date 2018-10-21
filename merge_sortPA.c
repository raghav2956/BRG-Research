#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <cilk/cilk.h>
#include <assert.h> 
#include <sys/time.h>
#include <math.h>

void merge(int main_array[], int start_1, int end_1, int start_2, int end_2 , int buffer[])       
{
	int size = ( end_2 - start_2 ) + ( end_1 - start_1);
  int x=start_1;
  int y=start_2;
   
  
  for ( int i = 0; i < size; i++ ){
		
    if ( x == end_1){
      buffer[ i ] = main_array[ y ];
      y++;
    }
    else if ( y == end_2 ){
      buffer[ i ] = main_array[ x ];
      x++;
    }
      
    else if ( main_array[ x ] < main_array[ y ]){
      buffer[ i ] = main_array[ x ];
      x++;
    }
    
    else{
			buffer[ i ] = main_array[ y ];
			y++;
    }
    
	}
}



void merge_recur_h( int arr[], int start, int end)
{

	int size =  end - start;
	if ( size == 1 ){
		return;
	}
	int midpoint = (end + start) / 2;
		
	//cilk_spawn 
  merge_recur_h( arr, start, midpoint );
	merge_recur_h( arr, midpoint, end );
	 //cilk_sync;
  
	int buffer[ size ];	
	merge( arr, start, midpoint, midpoint, end, buffer );

	
	int j = 0;
  int i = start;
	for( i; i < end; i++ ){
		arr[ i ] = buffer[ j ];
		j++;
	 } 
  }
 

void merge_sort( int arr[], size_t size )    
{
		if ( size == 0 ){
			arr = NULL;
		}
		else{
		merge_recur_h(arr, 0, size);
		
	}
}



int main ( void ){
    srand(5);
    int size = 1000000000;
    int alist[ size ];
    int i = 0;
    for ( i; i < size; i++){
      alist[ i ] = rand();
    }
    merge_sort( alist, size );   
    
    i = 0;
    for( i; i < size; i++ ){
      printf("%d\n", alist[i]);
    }
 
  return 0;

}

