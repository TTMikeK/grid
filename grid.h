#pragma once

template<typename T>
class Grid {
public:
    Grid() = delete;

    Grid( const int newWidth, const int newHeight ) :
        width(newWidth),
        height(newHeight),
        data(new T[newWidth * newHeight])
    {
    }

    Grid( Grid&& ) = default;

    ~Grid() {
        delete [] data;
    }


    /// When the desired usage is to wrap around
    inline int WrapIndex( const int x, const int y ) const {
        int newX = x % width;
        int newY = y % height;

        return (newY * width) + newX;
    }

    inline T& Wrap( const int x, const int y ) {
        return data[WrapIndex(x, y)];
    }
    inline T& Wrap( const int x, const int y ) const {
        return data[WrapIndex(x, y)];
    }


    /// When the desired usage is clamp or align to the edges
    inline int SaturateIndex( const int x, const int y ) const {
        int newX = x;
        if ( x < 0 ) {
            newX = 0;
        }
        else if ( x >= width ) {
            newX = width - 1;
        }

        int newY = y;
        if ( y < 0 ) {
            newY = 0;
        }
        else if ( y >= height ) {
            newY = height - 1;
        }

        return (newY * width) + newX;
    }

    inline T& Saturate( const int x, const int y ) {
        return data[SaturateIndex(x, y)];
    }
    inline T& Saturate( const int x, const int y ) const {
        return data[SaturateIndex(x, y)];
    }


    /// When the desired usage is to treat the outside as dead
    inline int DeadIndex( const int x, const int y ) const {
        int newX = x;
        if ( x < 0 ) {
            return -1;
        }
        else if ( x >= width ) {
            return -1;
        }

        int newY = y;
        if ( y < 0 ) {
            return -1;
        }
        else if ( y >= height ) {
            return -1;
        }

        return (newY * width) + newX;
    }

    inline T* Dead( const int x, const int y ) {
        int index = DeadIndex(x, y);
        return (index == -1) ? nullptr : &data[index];
    }
    inline T* Dead( const int x, const int y ) const {
        int index = DeadIndex(x, y);
        return (index == -1) ? nullptr : &data[index];
    }

private:
    int width, height;
    T* data;
};
