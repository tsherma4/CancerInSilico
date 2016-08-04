// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// CellModel
Rcpp::List CellModel(int initialNum, int numMCSteps, double density, double maxTranslation, double maxDeform, double maxRotate, double epsilon, double delta, int outIncrement, int randSeed, Rcpp::NumericVector growthRates, bool inheritGrowth, double nG, double timeIncrement);
RcppExport SEXP CancerInSilico_CellModel(SEXP initialNumSEXP, SEXP numMCStepsSEXP, SEXP densitySEXP, SEXP maxTranslationSEXP, SEXP maxDeformSEXP, SEXP maxRotateSEXP, SEXP epsilonSEXP, SEXP deltaSEXP, SEXP outIncrementSEXP, SEXP randSeedSEXP, SEXP growthRatesSEXP, SEXP inheritGrowthSEXP, SEXP nGSEXP, SEXP timeIncrementSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< int >::type initialNum(initialNumSEXP);
    Rcpp::traits::input_parameter< int >::type numMCSteps(numMCStepsSEXP);
    Rcpp::traits::input_parameter< double >::type density(densitySEXP);
    Rcpp::traits::input_parameter< double >::type maxTranslation(maxTranslationSEXP);
    Rcpp::traits::input_parameter< double >::type maxDeform(maxDeformSEXP);
    Rcpp::traits::input_parameter< double >::type maxRotate(maxRotateSEXP);
    Rcpp::traits::input_parameter< double >::type epsilon(epsilonSEXP);
    Rcpp::traits::input_parameter< double >::type delta(deltaSEXP);
    Rcpp::traits::input_parameter< int >::type outIncrement(outIncrementSEXP);
    Rcpp::traits::input_parameter< int >::type randSeed(randSeedSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type growthRates(growthRatesSEXP);
    Rcpp::traits::input_parameter< bool >::type inheritGrowth(inheritGrowthSEXP);
    Rcpp::traits::input_parameter< double >::type nG(nGSEXP);
    Rcpp::traits::input_parameter< double >::type timeIncrement(timeIncrementSEXP);
    __result = Rcpp::wrap(CellModel(initialNum, numMCSteps, density, maxTranslation, maxDeform, maxRotate, epsilon, delta, outIncrement, randSeed, growthRates, inheritGrowth, nG, timeIncrement));
    return __result;
END_RCPP
}
