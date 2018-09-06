#include <stdio.h>
#include "grid.h"

void Dump( Grid<float>& data ) {
    for ( int y = 0; y < data.Height(); ++y ) {
        for ( int x = 0; x < data.Width(); ++x ) {
            printf("%7.2f ", data(x, y));
        }
        printf("\n");
    }
}

int main( int argc, char* argv[] ) {
	Grid<float> billy(8, 6);
	billy.Fill(0.5f);
    billy.Wrap(-2, -1) = 22;
    billy.Saturate(-16, 4) = 11.11;

	Grid<float> robby(billy);

    billy(0, 0) = 10.75;
    billy[2] = 4;
    float* deadable = billy.Dead(2, 3);
    if ( deadable ) {
        *deadable = 16;
    }
    deadable = billy.Dead(2, -3);
    if ( deadable ) {
        *deadable = 116.11;
    }

    printf("billy\n");
    Dump(billy);

    printf("robby\n");
    Dump(robby);

	return 0;
}

