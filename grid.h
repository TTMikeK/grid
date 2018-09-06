#pragma once
#include <string.h>

template<typename T>
class Grid {
public:
    Grid() = delete;

    /// Must construct
    inline Grid( const int newWidth, const int newHeight ) :
        width(newWidth),
        height(newHeight),
        data(new T[newWidth * newHeight])
    {
        //printf("Create %p\n", this);
    }

    inline Grid( const Grid& src ) :
        width(src.width),
        height(src.height)
    {
        data = new T[src.width * src.height];
        memcpy(data, src.data, sizeof(T) * src.width * src.height);
        //printf("Copy %p\n", this);
    }

    inline ~Grid() {
        delete [] data;
        //printf("Die %p\n", this);
    }

    /// Dimensions
    inline int Width() const {
        return width;
    }
    inline int Height() const {
        return height;
    }
    inline int Size() const {
        return width * height;
    }

    /// Dereference as a pointer
    inline T* operator *() {
        return data;
    }
    inline T* operator *() const {
        return data;
    }

    /// Index as an array
    inline T& operator []( const int index ) {
        return data[index];
    }
    inline const T& operator []( const int index ) const {
        return data[index];
    }

    // Index as a function
    inline T& operator ()( const int x, const int y ) {
        return Saturate(x, y);
    }
    inline const T& operator ()( const int x, const int y ) const {
        return Saturate(x, y);
    }

    /// Fill the grid with a value
    inline void Fill( const T& what ) {
        for ( int idx = 0; idx < Size(); ++idx ) {
            data[idx] = what;
        }
    }


    /// When the desired usage is to wrap around
    inline int WrapIndex( const int x, const int y ) const {
        // Double mod version
//        int newX = ((x % width) + width) % width;
//        int newY = ((y % height) + height) % height;

        // Branch version (should be faster)
        int newX = x % width;
        newX = (newX < 0) ? (newX + width) : newX;
        int newY = y % height;
        newY = (newY < 0) ? (newY + height) : newY;

        return (newY * width) + newX;
    }

    inline T& Wrap( const int x, const int y ) {
        return data[WrapIndex(x, y)];
    }
    inline const T& Wrap( const int x, const int y ) const {
        return data[WrapIndex(x, y)];
    }


    /// When the desired usage is clamp or align to the edges
    inline int SaturateIndex( const int x, const int y ) const {
        int newX;
        if ( x < 0 ) {
            newX = 0;
        }
        else if ( x >= width ) {
            newX = width - 1;
        }
        else {
            newX = x;
        }

        int newY;
        if ( y < 0 ) {
            newY = 0;
        }
        else if ( y >= height ) {
            newY = height - 1;
        }
        else {
            newY = y;
        }

        return (newY * width) + newX;
    }

    inline T& Saturate( const int x, const int y ) {
        return data[SaturateIndex(x, y)];
    }
    inline const T& Saturate( const int x, const int y ) const {
        return data[SaturateIndex(x, y)];
    }


    /// When the desired usage is to treat the outside as dead
    inline int DeadIndex( const int x, const int y ) const {
        int newX;
        if ( x < 0 ) {
            return -1;
        }
        else if ( x >= width ) {
            return -1;
        }
        else {
            newX = x;
        }

        int newY;
        if ( y < 0 ) {
            return -1;
        }
        else if ( y >= height ) {
            return -1;
        }
        else {
            newY = y;
        }

        return (newY * width) + newX;
    }

    inline T* Dead( const int x, const int y ) {
        int index = DeadIndex(x, y);
        return (index < 0) ? nullptr : &data[index];
    }
    inline const T* Dead( const int x, const int y ) const {
        int index = DeadIndex(x, y);
        return (index < 0) ? nullptr : &data[index];
    }

private:
    int width, height;
    T* data;
};
