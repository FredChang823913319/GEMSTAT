#include "FactorIntFunc.h"

string getIntOptionStr( FactorIntType intOption )
{
	    if ( intOption == BINARY ) return "Binary";
	        if ( intOption == GAUSSIAN ) return "Gaussian";

		    return "Invalid";
}

double FactorIntFuncBinary::compFactorInt( double normalInt, double dist, bool orientation ) const
{
    assert( dist >= 0 );

    double spacingTerm = ( dist < distThr ? normalInt : 1.0 );
    double orientationTerm = orientation ? 1.0 : orientationEffect;
    return spacingTerm * orientationTerm;
}


double FactorIntFuncGaussian::compFactorInt( double normalInt, double dist, bool orientation ) const
{
    assert( dist >= 0 );

    double GaussianInt = dist < distThr ? normalInt * exp( - ( dist * dist ) / ( 2.0 * sigma * sigma ) ) : 1.0;
    return max( 1.0, GaussianInt );
}


double FactorIntFuncGeometric::compFactorInt( double normalInt, double dist, bool orientation ) const
{
    assert( dist >= 0 );

    double spacingTerm = max( 1.0, dist <= distThr ? normalInt : normalInt * pow( spacingEffect, dist - distThr ) );
    double orientationTerm = orientation ? 1.0 : orientationEffect;
    return spacingTerm * orientationTerm;
}

