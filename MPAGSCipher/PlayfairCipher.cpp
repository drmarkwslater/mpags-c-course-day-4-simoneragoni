
// Standard library includes
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

// Out project headers
#include "PlayfairCipher.hpp"

/*PlayfairCipher::PlayfairCipher( const size_t key )
  : key_{key%alphabetSize_}
{
}*/   //not implemented for this type of cipher

//_______________________________________________________
PlayfairCipher::PlayfairCipher( const std::string& key )
  //: key_{0}
{
  // We have the key as a string, but the cipher needs a 5x5 grid, so we first need to convert it.
  // We default to having a key of 0, i.e. no encryption, if no (valid) key was provided on the command line
  if ( ! key.empty() ) {
      setKey(key);
  }
}
//_______________________________________________________
void PlayfairCipher::setKey( const std::string& key )
{
  // store the original key
  key_ = key;

  // Append the alphabet

/* - SIMONE IN:
 * - Copying the full alphabet just by adding it
 * - to the end iterator of the original vector.
 */
  std::copy( alphabet_.begin(), alphabet_.end(), back_inserter(key_) );
  // key_.push_back('A');
  // key_.push_back('B');
  // key_.push_back('C');
  // key_.push_back('D');
  // key_.push_back('E');
  // key_.push_back('F');
  // key_.push_back('G');
  // key_.push_back('H');
  // key_.push_back('I');
  // key_.push_back('J');
  // key_.push_back('K');
  // key_.push_back('L');
  // key_.push_back('M');
  // key_.push_back('N');
  // key_.push_back('O');
  // key_.push_back('P');
  // key_.push_back('Q');
  // key_.push_back('R');
  // key_.push_back('S');
  // key_.push_back('T');
  // key_.push_back('U');
  // key_.push_back('V');
  // key_.push_back('W');
  // key_.push_back('X');
  // key_.push_back('Y');
  // key_.push_back('Z');


  // Make sure the key is upper case

  /* - SIMONE IN:
   * - Changing the full string to UPPER CASE
   * - by usage of ::toupper function in conjunction
   * - to std::transform.
   * - A slightly different variant is commented just
   * - below the official version. NOT TESTED.
   */
  std::transform( key_.begin(), key_.end(), key_.begin() , ::toupper );
  // std::transform( key_.begin(), key_.end(), key_.begin() , [](char &c){ c = ::toupper(c); } );

  // Remove non-alpha characters

  /* - SIMONE IN:
   * - Erasing the non-alpha characters.
   * - This is achieved by using the classic strategy ERASE+REMOVE_IF
   * - We are postponing to the vector.end IF a certain char IS NOT ALPHABETIC.
   * - The remove function returns an iterator to the beginning of
   * - the postponed character, thus enabling the ACTUAL ERASING act.
   */
  key_.erase(std::remove_if(key_.begin(), key_.end(),
             [](char elem){return !isalpha(elem);}  ), key_.end() );

  // Change J -> I

  /* - SIMONE IN:
   * - Changing the Js full string to Is
   * - by usage of LAMBDA CHECK function in conjunction
   * - to std::transform.
   */
  std::transform(key_.begin(), key_.end(), key_.begin(),
                 [](char &c){ if ( c == 'J') return 'I'; else return c; } );

  // Remove duplicated letters

/*  - SIMONE IN:
 *  - Creating a local string.
 *  - What happens is that every time we cycle on the vector,
 *  - we cycle on the string too.
 *  - If we happen to find the same char on the string,
 *  - we get rid of it, otherwise we add it to the string
 *  - for later checks.
 * - This action HAS to happen AFTER changing all Js to Is.
 */
  std::string seen;
  key_.erase(std::remove_if(key_.begin(), key_.end(),
             [&seen](const char &value)
             {
               if( seen.find(value) != std::string::npos ) return true;
               seen += value ;
               return false;
             }), key_.end() );

  // Store the coords of each letter

/* - SIMONE IN:
 * - Created a cartesian grid of size_t with the expected XY coords.
 *
 */
 Cartesian fiveByFiveGrid[5][5];
 for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 5; j++) {
            fiveByFiveGrid[i][j] = std::make_pair(i,j);
      }
 }
  // Store the playfair cipher key map

  /* - SIMONE IN:
   * - Associated chars to respective coords and coords to chars,
   * - keeping in mind that the [x][y] corresponds to
   * - char[x*5+y] in our LOGIC because we have to consider the
   * - carry-on from the grid limitations.
   */

 std::cout << key_ << std::endl;
 for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 5; j++) {
            atlas_.insert(std::make_pair( key_.at( i*5 + j ), fiveByFiveGrid[i][j] ));
            hasbro_.insert(std::make_pair( fiveByFiveGrid[i][j], key_.at( i*5 + j ) ));
      }
 }
}


//_______________________________________________________
std::string PlayfairCipher::applyCipher( const std::string& inputText,
                                         const CipherMode cipherMode ) const
{

  std::string outputText = inputText;
  // Change J -> I

  /* - SIMONE IN:
   * - Changing the Js full string to Is
   * - by usage of LAMBDA CHECK function in conjunction
   * - to std::transform.
   */
  std::transform(outputText.begin(), outputText.end(), outputText.begin(),
                 [](char &c){ if ( c == 'J') return 'I'; else return c; } );


  // If repeated chars in a digraph add an X or Q if XX

/*  - SIMONE IN:
 *  - Creating a local counter (could have done without, but it felt weird).
 *  - What happens is that every time we cycle on the vector,
 *  - we check every time the counter is even (so making pairs).
 *  - If we happen to find the same char one cell ahead,
 *  - like:   ___________________
 *  -         | H | E | L  | L  |
 *  -         ___________________
 *  -
 *  - we either add 'X' or 'Q' depending on the rule, and increase the counter
 *  - so that the logic does not get affected but the inner order does.
 *  - This action HAS to happen AFTER changing all Js to Is.
 */
  size_t counter = 0;
  size_t duplica = 0;
  for ( auto iter { std::begin(outputText) }; iter !=  outputText.end() + duplica - 2; ++iter )
  {
        if( ( counter%2 == 0 ) &&  (*iter == *(iter + 1) ) )
        {
            if ( *iter == 'X' )  outputText.insert(iter + 1, 'Q');
            else                 outputText.insert(iter + 1, 'X');
            ++duplica;

        }
        ++counter;
  }

  // if the size of input is odd, add a trailing Z
 /*
  * - Simply appending 'Z' is the size is not even.
  * - It felt more natural and readable to achieve
  * - this by makings of std::push_back.
  */
  size_t outputTextSize = outputText.size();
  if ( outputTextSize%2 == 1 ) outputText.push_back('Z');

  // Loop over the input in Digraphs
  // - Find the coords in the grid for each digraph
  // - Apply the rules to these coords to get 'new' coords
  // - Find the letter associated with the new coords

if(cipherMode == CipherMode::Encrypt)
{
  for ( auto iter2 { std::begin(outputText) }; iter2 != outputText.end(); iter2 += 2 )
  {
        auto mapIter  = atlas_.find( *iter2     );
        auto mapIter2 = atlas_.find( *(iter2+1) );

        Cartesian foundYou       =  std::make_pair( std::get<0> ((*mapIter).second),
                                                    std::get<1> ((*mapIter).second ));
        Cartesian foundYou2      =  std::make_pair( std::get<0> ((*mapIter2).second),
                                                    std::get<1> ((*mapIter2).second ));
        Cartesian replacement;
        Cartesian replacement2;
        if ( std::get<0> (foundYou) == 0 )
        {
            //this "if" completes the rectangle case
            if ( std::get<0> (foundYou2) == 4 )
            {
                if ( std::get<1> (foundYou) != std::get<1> (foundYou2)  )
                {
                    replacement  =  std::make_pair( 4, std::get<1> ((*mapIter).second) );
                    auto help    = hasbro_.find(replacement);
                    *iter2       = (*help).second;
                    replacement2 =  std::make_pair( 0, std::get<1> ((*mapIter2).second) );
                    auto help2   = hasbro_.find(replacement2);
                    *(iter2 + 1) = (*help2).second;
                }
            }
        }
        //this "if" completes the case horizontal case
        if ( std::get<1> (foundYou) == std::get<1> (foundYou2) )
        {
            if ( (std::get<0> (foundYou2) == std::get<0> (foundYou) + 1)%5 )
            {
                replacement  =  std::make_pair( (std::get<0> ((*mapIter).second) + 2)%5 ,
                                                 std::get<1> ((*mapIter).second) );
                auto help    = hasbro_.find(replacement);
                *iter2       = (*help).second;
            }
        }
        //this "if" completes the case vertical case
        if ( std::get<0> (foundYou) == std::get<0> (foundYou2) )
        {
            if ( (std::get<1> (foundYou2) == std::get<1> (foundYou) + 1)%5 )
            {
                replacement  =  std::make_pair( std::get<0> ((*mapIter).second),
                                               (std::get<1> ((*mapIter).second) + 2)%5 );
                auto help    = hasbro_.find(replacement);
                *iter2       = (*help).second;
            }
        }


  }
}
else if (cipherMode == CipherMode::Decrypt)
{
  for ( auto iter2 { std::begin(outputText) }; iter2 != outputText.end(); iter2 += 2 )
  {
        auto mapIter  = atlas_.find( *iter2     );
        auto mapIter2 = atlas_.find( *(iter2+1) );

        Cartesian foundYou       =  std::make_pair( std::get<0> ((*mapIter).second),
                                                    std::get<1> ((*mapIter).second ));
        Cartesian foundYou2      =  std::make_pair( std::get<0> ((*mapIter2).second),
                                                    std::get<1> ((*mapIter2).second ));
        Cartesian replacement;
        Cartesian replacement2;
        if ( std::get<0> (foundYou) == 0 )
        {
            //this "if" completes the rectangle case
            if ( std::get<0> (foundYou2) == 4 )
            {
                if ( std::get<1> (foundYou) != std::get<1> (foundYou2)  )
                {
                    replacement  =  std::make_pair( 4, std::get<1> ((*mapIter).second) );
                    auto help    = hasbro_.find(replacement);
                    *iter2       = (*help).second;
                    replacement2 =  std::make_pair( 0, std::get<1> ((*mapIter2).second) );
                    auto help2   = hasbro_.find(replacement2);
                    *(iter2 + 1) = (*help2).second;
                }
            }
        }
        //this "if" completes the case horizontal case
        if ( std::get<1> (foundYou) == std::get<1> (foundYou2) )
        {
            if ( (std::get<0> (foundYou2) == std::get<0> (foundYou) + 1)%5 )
            {
                replacement  =  std::make_pair( (std::get<0> ((*mapIter).second) + 3)%5 , // +3 == -2 (mod 5)
                                                 std::get<1> ((*mapIter).second) );
                auto help    = hasbro_.find(replacement);
                *iter2       = (*help).second;
            }
        }
        //this "if" completes the case vertical case
        if ( std::get<0> (foundYou) == std::get<0> (foundYou2) )
        {
            if ( (std::get<1> (foundYou2) == std::get<1> (foundYou) + 1)%5 )
            {
                replacement  =  std::make_pair( std::get<0> ((*mapIter).second),
                                               (std::get<1> ((*mapIter).second) + 3)%5 );
                auto help    = hasbro_.find(replacement);
                *iter2       = (*help).second;
            }
        }


  }
}




  // return the text
  return outputText;
}
