#include <fstream>

#include <dlib/rand.h>
#include <dlib/matrix.h>

using namespace std;
using namespace dlib;

typedef matrix<double, 2, 1> sample_type;

int main()
{
    std::ofstream f( "kkmeans_ex.txt", std::ios::binary );
    if( !f )
        return 1;

    std::vector<sample_type> samples;
    std::vector<sample_type> initial_centers;

    sample_type m;

    dlib::rand rnd;
    // we will make 50 points from each class
    const long num = 50;

    // make some samples near the origin
    double radius = 0.5;
    for( long i = 0; i < num; ++i )
    {
        double sign = 1;
        if( rnd.get_random_double() < 0.5 )
            sign = -1;
        m( 0 ) = 2 * radius*rnd.get_random_double() - radius;
        m( 1 ) = sign*sqrt( radius*radius - m( 0 )*m( 0 ) );

        // add this sample to our set of samples we will run k-means 
        samples.push_back( m );
    }

    // make some samples in a circle around the origin but far away
    radius = 10.0;
    for( long i = 0; i < num; ++i )
    {
        double sign = 1;
        if( rnd.get_random_double() < 0.5 )
            sign = -1;
        m( 0 ) = 2 * radius*rnd.get_random_double() - radius;
        m( 1 ) = sign*sqrt( radius*radius - m( 0 )*m( 0 ) );

        // add this sample to our set of samples we will run k-means 
        samples.push_back( m );
    }

    // make some samples in a circle around the point (25,25) 
    radius = 4.0;
    for( long i = 0; i < num; ++i )
    {
        double sign = 1;
        if( rnd.get_random_double() < 0.5 )
            sign = -1;
        m( 0 ) = 2 * radius*rnd.get_random_double() - radius;
        m( 1 ) = sign*sqrt( radius*radius - m( 0 )*m( 0 ) );

        // translate this point away from the origin
        m( 0 ) += 25;
        m( 1 ) += 25;

        // add this sample to our set of samples we will run k-means 
        samples.push_back( m );
    }

    for( auto& v : samples )
    {
        f << v( 0 ) << ';' << v( 1 ) << '\n';
    }

    return 0;
}