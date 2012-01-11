//
//  Vector4.h
//  Archetype
//
//  Created by Jay Steen on 11/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "vector.h"
#include "libPrefix.h"
#include <ostream>

namespace AT
{
    namespace Maths
    {
        
        class Vector3;
        
        class Vector4 :	public Vector
        {
            
            
        public:
            
#pragma region Members
            
            // Members are public as any values are valid
            float x, y, z, w;
            
#pragma endregion
            
#pragma region Constructors
            
            DLLEXPORT Vector4();
            
            // Constructor with the three vector components as floats
            DLLEXPORT Vector4(float x, float y, float z, float w);
            
            // Constructor from a Vector3, with optional w component
            DLLEXPORT Vector4(const Vector3 & v, float w = 0.0f);
            
#pragma endregion
            
#pragma region Destructor
            
            // Destructors
            DLLEXPORT ~Vector4();
            
#pragma endregion
            
#pragma region Overloaded Operators
            
            DLLEXPORT Vector4 operator- () const;
            
            DLLEXPORT void operator*= (float scale);
            
            DLLEXPORT void operator/= (float scale);
            
            DLLEXPORT void operator+= (const Vector4& v);
            
            DLLEXPORT void operator-= (const Vector4& v);
            
#pragma endregion
            
#pragma region Member Functions
            
            /*<summary>
             Converts the vector to unit length
             </summary>*/
            DLLEXPORT virtual void Normalise();
            
            /*<summary> 
             Returns the magnitude (length) of the vector 
             </summary>*/
            DLLEXPORT virtual float Length() const;
            
            // Returns the length squared of the vector
            DLLEXPORT virtual float LengthSquared() const;
            
#pragma endregion
            
#pragma region Class Functions
            
            //DLLEXPORT virtual std::string ToString();
            
            DLLEXPORT static float Dot(const Vector4 & v1, const Vector4 & v2);
            
            DLLEXPORT static Vector4 Cross(const Vector4 & v1, const Vector4 & v2);
            
#pragma endregion
            
#pragma region Factory Methods
            
            // Returns a vector with all components initialised to zero
            DLLEXPORT static Vector4 Zero();
            
            // Returns a standard up vector (0, 1, 0)
            DLLEXPORT static Vector4 Up();
            
            // Returns a standard right vector (1, 0, 0)
            DLLEXPORT static Vector4 Right();
            
            // Returns an Right-Handed coordinate space forward vector (0, 0, -1)
            DLLEXPORT static Vector4 Forward();
            
#pragma endregion
            
        };
        
#pragma region Non-Member Operator Overloads
        
        // Overloaded * for a vector and a scalar
        DLLEXPORT Vector4 operator* (const Vector4 & v, float scale);
        
        // Overloaded / for a vector and a scalar
        DLLEXPORT Vector4 operator/ (const Vector4 & v, float scale);
        
        // Overloaded + operator for two vectors
        DLLEXPORT Vector4 operator+ (const Vector4 & a, const Vector4 & b);
        
        // Overloaded - operator (does opposite of +)
        DLLEXPORT Vector4 operator- (const Vector4 & a, const Vector4 & b);
        
        // Overloaded << operator for debug output
        DLLEXPORT std::ostream & operator<< (std::ostream & o, const Vector4 & v);
        
#pragma endregion
        
    }
}