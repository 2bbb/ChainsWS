//
//  Blockchain.h
//  ChainsWSExample
//
//  Created by ISHII 2bit on 2018/01/02.
//

#ifndef Blockchain_h
#define Blockchain_h

#include "ofxJsonUtils.h"

namespace Blockchain {
    struct Block {
        std::vector<std::uint64_t> txIndexes;
        std::uint64_t totalBTCSent;
        std::uint64_t estimatedBTCSent;
        std::uint64_t size;
        
        std::uint64_t blockIndex;
        std::uint64_t prevBlockIndex;
        std::uint64_t height;
        
        std::string hash;
        std::string mrklRoot; // Root of "Merkle tree"
        
        std::uint64_t time;
        std::uint64_t bits;
        std::uint64_t nonce;
        
        void loadJson(const ofJson &json) {
            ofxJsonUtils::load(json, kv(txIndexes));
            ofxJsonUtils::load(json, kv(totalBTCSent));
            ofxJsonUtils::load(json, kv(estimatedBTCSent));
            ofxJsonUtils::load(json, kv(size));
            ofxJsonUtils::load(json, kv(blockIndex));
            ofxJsonUtils::load(json, kv(prevBlockIndex));
            ofxJsonUtils::load(json, kv(height));
            ofxJsonUtils::load(json, kv(hash));
            ofxJsonUtils::load(json, kv(mrklRoot));
            ofxJsonUtils::load(json, kv(time));
            ofxJsonUtils::load(json, kv(bits));
            ofxJsonUtils::load(json, kv(nonce));
        }
    };
};

#endif /* Blockchain_h */
