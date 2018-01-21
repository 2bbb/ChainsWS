//
//  ofxOscSubscriberLoadImplementation.h
//
//  Created by ISHII 2bit on 2016/05/29.
//
//

#pragma once

#ifndef ofxOscSubscriberLoadImplementation_h
#define ofxOscSubscriberLoadImplementation_h

#include "ofxOscMessage.h"

#include "ofxPubSubOscSettings.h"
#include "ofxPubSubOscTypeUtils.h"
#include "ofxPubSubOscTypeTraits.h"

namespace ofx {
    namespace PubSubOsc {
#define define_set_arithmetic(type) \
        inline void load(ofxOscMessage &m, type &v, std::size_t offset = 0) { \
            if(m.getArgType(offset) == OFXOSC_TYPE_INT32) v = m.getArgAsInt32(offset); \
            else if(m.getArgType(offset) == OFXOSC_TYPE_INT64) v = m.getArgAsInt64(offset); \
            else if(m.getArgType(offset) == OFXOSC_TYPE_FLOAT) v = m.getArgAsFloat(offset); \
            else if(m.getArgType(offset) == OFXOSC_TYPE_DOUBLE) v = m.getArgAsDouble(offset); \
            else if(m.getArgType(offset) == OFXOSC_TYPE_STRING) v = ofToDouble(m.getArgAsString(offset)); \
            else if(m.getArgType(offset) == OFXOSC_TYPE_TRUE) v = true; \
            else if(m.getArgType(offset) == OFXOSC_TYPE_FALSE) v = false; \
}
        
        define_set_arithmetic(bool);
        define_set_arithmetic(char);
        define_set_arithmetic(unsigned char);
        define_set_arithmetic(short);
        define_set_arithmetic(unsigned short);
        define_set_arithmetic(int);
        define_set_arithmetic(unsigned int);
        define_set_arithmetic(long);
        define_set_arithmetic(unsigned long);
        define_set_arithmetic(long long);
        define_set_arithmetic(unsigned long long);
        
        define_set_arithmetic(float);
        define_set_arithmetic(double);
#undef define_set_arithmetic
        
        inline void load(ofxOscMessage &m, std::string &v, std::size_t offset = 0) {
            if(m.getArgType(offset) == OFXOSC_TYPE_STRING) v = m.getArgAsString(offset);
            else if(m.getArgType(offset) == OFXOSC_TYPE_FLOAT) v = ofToString(m.getArgAsFloat(offset));
            else if(m.getArgType(offset) == OFXOSC_TYPE_DOUBLE) v = ofToString(m.getArgAsDouble(offset));
            else if(m.getArgType(offset) == OFXOSC_TYPE_INT32) v = ofToString(m.getArgAsInt32(offset));
            else if(m.getArgType(offset) == OFXOSC_TYPE_INT64) v = ofToString(m.getArgAsInt64(offset));
            else v = m.getArgAsString(offset);
        }
        
        inline void load(ofxOscMessage &m, ofBuffer &v, std::size_t offset = 0) {
            v = m.getArgAsBlob(offset);
        }
        
#pragma mark ofColor_
        template <typename U>
        inline void loadColor(ofxOscMessage &m, ofColor_<U> &v, U defaultValue, std::size_t offset = 0) {
            if(m.getNumArgs() == 1) {
                load(m, v.r, offset);
                load(m, v.g, offset);
                load(m, v.b, offset);
                v.a = defaultValue;
            } else if(m.getNumArgs() == 3) {
                load(m, v.r, offset + 0);
                load(m, v.g, offset + 1);
                load(m, v.b, offset + 2);
                v.a = defaultValue;
            } else {
                load(m, v.r, offset + 0);
                load(m, v.g, offset + 1);
                load(m, v.b, offset + 2);
                load(m, v.a, offset + 3);
            }
        }
        
        inline void load(ofxOscMessage &m, ofColor &v, std::size_t offset = 0) {
            loadColor<unsigned char>(m, v, 255, offset);
        }
        inline void load(ofxOscMessage &m, ofShortColor &v, std::size_t offset = 0) {
            loadColor<unsigned short>(m, v, 65535, offset);
        }
        inline void load(ofxOscMessage &m, ofFloatColor &v, std::size_t offset = 0) {
            loadColor<float>(m, v, 1.0f, offset);
        }
        
#pragma mark oF container type
        template <std::size_t n, typename U>
        inline void loadVec(ofxOscMessage &m, U &v, std::size_t offset = 0) {
            for(int i = 0; i < min(static_cast<std::size_t>(m.getNumArgs() - offset), n); i++) {
                load(m, v[i], offset + i);
            }
        }
        
        inline void load(ofxOscMessage &m, ofVec2f &v, std::size_t offset = 0) {
            loadVec<2>(m, v, offset);
        }
        inline void load(ofxOscMessage &m, ofVec3f &v, std::size_t offset = 0) {
            loadVec<3>(m, v, offset);
        }
        inline void load(ofxOscMessage &m, ofVec4f &v, std::size_t offset = 0) {
            loadVec<4>(m, v, offset);
        }
        inline void load(ofxOscMessage &m, ofQuaternion &v, std::size_t offset = 0) {
            loadVec<4>(m, v, offset);
        }
        inline void load(ofxOscMessage &m, ofMatrix3x3 &v, std::size_t offset = 0) {
            loadVec<9>(m, v, offset);
        }
        
        inline void load(ofxOscMessage &m, ofMatrix4x4 &v, std::size_t offset = 0) {
            for(int j = 0; j < 4; j++) for(int i = 0; i < 4; i++) {
                load(m, v(i, j), offset + 4 * j + i);
            }
        }
        
        inline void load(ofxOscMessage &m, ofRectangle &v, std::size_t offset = 0) {
            load(m, v.x,      offset + 0);
            load(m, v.y,      offset + 1);
            load(m, v.width,  offset + 2);
            load(m, v.height, offset + 3);
        }
        
#pragma mark ofParameter<T> / ofParameterGroup
        
        template <typename U>
        inline void load(ofxOscMessage &m, ofParameter<U> &p, std::size_t offset = 0) {
            U u;
            load(m, u, offset);
            p.set(u);
        }
        
        inline void load(ofxOscMessage &m, ofAbstractParameter &p, std::size_t offset = 0) {
#define type_convert(type_) if(p.type() == typeid(ofParameter<type_>).name()) { load(m, p.cast<type_>(), offset); return; }
            type_convert(float);
            type_convert(double);
            type_convert(int);
            type_convert(unsigned int);
            type_convert(long);
            type_convert(unsigned long);
            type_convert(ofColor);
            type_convert(ofRectangle);
            type_convert(ofVec2f);
            type_convert(ofVec3f);
            type_convert(ofVec4f);
            type_convert(ofQuaternion);
            type_convert(ofMatrix3x3);
            type_convert(ofMatrix4x4);
            
            type_convert(ofFloatColor);
            type_convert(ofShortColor);
            
            type_convert(bool);
            type_convert(char);
            type_convert(unsigned char);
            type_convert(short);
            type_convert(unsigned short);
            type_convert(long long);
            type_convert(unsigned long long);
            type_convert(ofBuffer);
            ofLogWarning("ofxOscSubscriber") << "ofAbstractParameter: Unknown type \"" << p.type() << "\", bind to " << m.getAddress() << ". we ignored.";
#undef type_convert
        }
        
        inline void load(ofxOscMessage &m, ofParameterGroup &pg, std::size_t offset = 0) {
            if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
                if(pg.size() <= m.getArgAsInt32(0)) {
                    ofLogWarning("ofxOscSubscriber") << "ofAbstractParameterGroup: not contain index \"" << m.getArgAsInt32(0) << "\"";
                    return;
                }
                load(m, pg.get(m.getArgAsInt32(0)), offset + 1);
            } else if(m.getArgType(0) == OFXOSC_TYPE_INT64) {
                if(pg.size() <= m.getArgAsInt64(0)) {
                    ofLogWarning("ofxOscSubscriber") << "ofAbstractParameterGroup: not contain index \"" << m.getArgAsInt64(0) << "\"";
                    return;
                }
                load(m, pg.get(m.getArgAsInt64(0)), offset + 1);
            } else if(m.getArgType(0) == OFXOSC_TYPE_STRING) {
                if(!pg.contains(m.getArgAsString(0))) {
                    ofLogWarning("ofxOscSubscriber") << "ofAbstractParameterGroup: not contain key \"" << m.getArgAsString(0) << "\"";
                    return;
                }
                load(m, pg.get(m.getArgAsString(0)), offset + 1);
            }
        }
        
#pragma mark container
        template <typename U, std::size_t size>
        inline void load(ofxOscMessage &m, std::array<U, size> &v, std::size_t offset = 0) {
            for(int i = 0; i < min(size, (m.getNumArgs() - offset) / type_traits<U>::size); i++) {
                load(m, v[i], offset + i * type_traits<U>::size);
            }
        }
        
        template <typename U, std::size_t size>
        inline void load(ofxOscMessage &m, U (&v)[size], std::size_t offset = 0) {
            for(int i = 0; i < min(size, (m.getNumArgs() - offset) / type_traits<U>::size); i++) {
                load(m, v[i], offset + i * type_traits<U>::size);
            }
        }
        
        template <typename U, typename Alloc>
        inline void load(ofxOscMessage &m, std::vector<U, Alloc> &v, std::size_t offset = 0) {
            std::size_t num = (m.getNumArgs() - offset) / type_traits<U>::size;
            if(v.size() != num) v.resize(num);
            for(int i = 0; i < num; i++) {
                load(m, v[i], offset + i * type_traits<U>::size);
            }
        }
        
        template <typename U, typename Alloc>
        inline void load(ofxOscMessage &m, std::deque<U, Alloc> &v, std::size_t offset = 0) {
            std::size_t num = (m.getNumArgs() - offset) / type_traits<U>::size;
            if(v.size() != num) v.resize(num);
            for(int i = 0; i < num; i++) {
                load(m, v[i], offset + i * type_traits<U>::size);
            }
        }
    };
};

#endif /* ofxOscSubscriberLoadImplementation_h */
