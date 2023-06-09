// **************************************************************************
// File       [mergeSort.cpp]
// Author     [Deitel How to program C++, 5ed. Ch 20, Fig. 20.06]
// Synopsis   [The implementation of the MergeSort Class]
// Modify     [2010/02/21 CM Li]
// **************************************************************************

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <cstdlib> // prototypes for functions srand and rand
using std::rand;
using std::srand;

#include <ctime> // prototype for function time
using std::time;

#include "mergeSort.h" // class MergeSort definition

// constructor fill vector with random integers
MergeSort::MergeSort( int vectorSize )
{
  size = ( vectorSize > 0 ? vectorSize : 10 ); // validate vectorSize
  srand( time( 0 ) ); // seed random number generator using current time

  // fill vector with random ints in range 10-99
  for ( int i = 0; i < size; i++ )
    data.push_back( 10 + rand() % 90 );
} // end MergeSort constructor

// split vector, sort subvectors and merge subvectors into sorted vector
void MergeSort::sort()
{
  sortSubVector( 0, size - 1 ); // recursively sort entire vector
} // end function sort

// recursive function to sort subvectors                
void MergeSort::sortSubVector( int low, int high )
{                                                 
  // test base case; size of vector equals 1
  if ( ( high - low ) >= 1 ) // if not base case
    {
      int middle1;  // calculate middle of vector
      int middle2;  // calculate next element over
      middle1 = (low + high) / 2;;
      middle2 = middle1 + 1;
      // output split step 
	  
     #ifdef _DEBUG_ON_	  
      cout << "split:   ";                                          
      displaySubVector( low, high );                                 
      cout << endl << "         ";                                  
      displaySubVector( low, middle1 );                              
      cout << endl << "         ";                                  
      displaySubVector( middle2, high );                             
      cout << endl << endl;                                         
	  #endif

      sortSubVector(low, middle1);
      sortSubVector(middle2, high);
      // merge two sorted vectors after split calls return
      merge( low, middle1, middle2, high );
   } // end if
} // end function sortSubVector

// merge two sorted subvectors into one sorted subvector
void MergeSort::merge( int left, int middle1, int middle2, int right ) 
{
  int leftIndex = left; // index into left subvector              
  int rightIndex = middle2; // index into right subvector         
  int combinedIndex = left; // index into temporary working vector
  vector< int > combined( size ); // working vector              

  // output two subvectors before merging
  #ifdef _DEBUG_ON_
  cout << "merge:   ";                  
  displaySubVector( left, middle1 );     
  cout << endl << "         ";          
  displaySubVector( middle2, right );    
  cout << endl;  
  #endif
      
  while ( leftIndex <= middle1 && rightIndex <= right )
    {
      if (data[leftIndex] <= data[rightIndex]){
        combined[combinedIndex] = data[leftIndex];
        leftIndex++;
      }
      else{
        combined[combinedIndex] = data[rightIndex];
        rightIndex++;
      }
      combinedIndex++;
    } // end while
  
  if ( leftIndex == middle2 ) // if at end of left vector          
    { 
      while (rightIndex <= right){
        combined[combinedIndex] = data[rightIndex];
        rightIndex++;                            
        combinedIndex++;     
      }               
    } // end if                                                     
  else // at end of right vector                                   
    {                                                               
      while (leftIndex <= middle1){
        combined[combinedIndex] = data[leftIndex];
        leftIndex++;                            
        combinedIndex++;  
      }
    } // end else                                                   
  //copy values back into original vector
  for (int i = left; i <= right; i++){
    data[i] = combined[i];
  }
  
  // output merged vector         
  #ifdef _DEBUG_ON_
  cout << "         ";            
  displaySubVector( left, right );
  cout << endl << endl;           
  #endif
} // end function merge

// display elements in vector
void MergeSort::displayElements() const
{
  displaySubVector( 0, size - 1 );
} // end function displayElements

// display certain values in vector
void MergeSort::displaySubVector( int low, int high ) const
{
  // output spaces for alignment
  for ( int i = 0; i < low; i++ )
    cout << "   ";
  
  // output elements left in vector
  for ( int i = low; i <= high; i++ )
    cout << " " << data[ i ];
} // end function displaySubVector

