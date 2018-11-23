#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

// Standard library includes
#include <string>
#include <vector>

// Our project headers
#include "CipherMode.hpp"
#include "map.hpp"

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Caesar cipher with the given key
 */
class PlayfairCipher {
  public:
    // /**
    //  * Create a new PlayfairCipher with the given key
    //  *
    //  * \param key the key to use in the cipher
    //  */
    // explicit PlayfairCipher( const size_t key );

    /**
     * Create a new PlayfairCipher, converting the given string into the key
     *
     * \param key the string to convert into the key to be used in the cipher
     */
    explicit PlayfairCipher( const std::string& key );

    /**
     * Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher( const std::string& inputText, const CipherMode cipherMode ) const;

    /**
     * Set the kay and the Grid
     *
     * \param key the text to generate the Grid
     *
     *
     */
    void setKey( const std::string& key );


  private:
    /// The alphabet - used to determine the cipher character given the plain character and the key
    const std::vector<char> alphabet_ = {'A', 'B', 'C', 'D', 'E',
                                         'F', 'G', 'H', 'I', 'J', 'K',
                                         'L', 'M', 'N', 'O', 'P',
                                         'Q', 'R', 'S', 'T', 'U',
                                         'V', 'W', 'X', 'Y', 'Z'};

    /// The size of the alphabet
    const std::vector<char>::size_type alphabetSize_ = alphabet_.size();

    /** The cipher key, essentially a string that must later be filled
     *  with remaining characters of the alphabet to reach the 25 = 5x5
     *  limit we want.
     */
    std::string key_;

    /** The char to coords association map
     */
  // names here are a bit confusing!
    CharOnGrid  atlas_;

    /** The coords to char association map
     */
    GridOnChar  hasbro_;
};

#endif
