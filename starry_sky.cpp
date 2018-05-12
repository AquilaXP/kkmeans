#include <fstream>
#include <random>
#include <algorithm>

template<class T>
T clamp( const T& v, const T& lo, const T& hi )
{
    return std::less<T>()( v, lo ) ? lo : (std::less<T>()( hi, v ) ? hi : v);
}

int main()
{
    std::ofstream f( "starry_sky.txt", std::ios::binary );
    if( !f )
        return 1;

    std::random_device rd;
    std::mt19937 rand_engine( rd() );
    std::normal_distribution<double> ndx{ 0, 50 };
    std::normal_distribution<double> ndy{ 0, 50 };

    for( int i = 0; i < 50; ++i )
    {
        f << clamp( ndx( rand_engine ), -100.0, 100.0 ) << ';' 
            << clamp( ndy( rand_engine ), -100.0, 100.0 ) << '\n';
    }
    const int count_group = 3;
    std::normal_distribution<double> ndx1{ 0, 15 };
    std::normal_distribution<double> ndy1{ 0, 15 };
    double center_x[count_group] = { -50, 0, 50 };
    double center_y[count_group] = { 50, -50, 50 };
    for( int i = 0; i < 50; ++i )
    {
        for( int j = 0; j < count_group; ++j )
        {
            f << clamp( ndx1( rand_engine ) + center_x[j], -100.0, 100.0 ) << ';' 
                << clamp( ndy1( rand_engine ) + center_y[j], -100.0, 100.0 ) << '\n';
        }
    }

    return 0;
}