#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;


//int nextPrime( int n );

// SeparateChaining Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items

template <typename HashedObj>
class ChainHashTable
{
  public:
    explicit ChainHashTable( int size = 101 ) : currentSize{ 0 }, collisionC{ 0 }
      { theLists.resize( 101 ); }

    bool contains( const HashedObj & x ) const
    {
        auto & whichList = theLists[ myhash( x ) ];
        return find( begin( whichList ), end( whichList ), x ) != end( whichList );
    }

    void makeEmpty( )
    {
        for( auto & thisList : theLists )
            thisList.clear( );
    }

    bool insert( const HashedObj & x )
    {
        auto & whichList = theLists[ myhash( x ) ];
        if( find( begin( whichList ), end( whichList ), x ) != end( whichList) ){
          collisionC++;
          cout << "COL:" << collisionC << endl;
            return false;
          }
        whichList.push_back( x );

            // Rehash; see Section 5.5
        if( ++currentSize > theLists.size( ) )
            rehash( );

        return true;
    }

    bool insert( HashedObj && x )
    {
        auto & whichList = theLists[ myhash( x ) ];
        if( find( begin( whichList ), end( whichList ), x ) != end( whichList ) ) {
          collisionC++;
            return false;
        }
        whichList.push_back( std::move( x ) );

            // Rehash; see Section 5.5
        if( ++currentSize > theLists.size( ) )
            rehash( );

        return true;
    }

    bool remove( const HashedObj & x )
    {
        auto & whichList = theLists[ myhash( x ) ];
        auto itr = find( begin( whichList ), end( whichList ), x );

        if( itr == end( whichList ) )
            return false;

        whichList.erase( itr );
        --currentSize;
        return true;
    }

    int getCollisionC() {
      return collisionC;
    }

  private:
    vector<list<HashedObj>> theLists;   // The array of Lists
    int  currentSize;
    int collisionC;

    void rehash( )
    {
        vector<list<HashedObj>> oldLists = theLists;

            // Create new double-sized, empty table
        theLists.resize( nextPrime( 2 * theLists.size( ) ) );
        for( auto & thisList : theLists )
            thisList.clear( );

            // Copy table over
        currentSize = 0;
        for( auto & thisList : oldLists )
            for( auto & x : thisList )
                insert( std::move( x ) );
    }

    size_t myhash( const HashedObj & x ) const
    {
        static std::hash<HashedObj> hf;
        return hf( x ) % theLists.size( );
    }

    /**
     * Internal method to test if a positive number is prime.
     * Not an efficient algorithm.
     */
     bool isPrime( int n )
     {
       if( n == 2 || n == 3 )
       return true;

       if( n == 1 || n % 2 == 0 )
       return false;

       for( int i = 3; i * i <= n; i += 2 )
       if( n % i == 0 )
       return false;

       return true;
     }

     /**
     * Internal method to return a prime number at least as large as n.
     * Assumes n > 0.
     */
     int nextPrime( int n )
     {
       if( n % 2 == 0 )
       ++n;

       for( ; !isPrime( n ); n += 2 )
       ;

       return n;
     }

     /**
     * A hash routine for string objects.
     */
     size_t hash( const string & key )
     {
       size_t hashVal = 0;

       for( char ch : key )
       hashVal = 37 * hashVal + ch;
       cout<<"AAAAA!"<<endl;
       return hashVal;
     }

     /**
     * A hash routine for ints.
     */
     size_t hash( int key )
     {
       return key;
     }

};

#endif
