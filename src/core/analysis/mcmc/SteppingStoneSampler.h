#ifndef SteppingStoneSampler_H
#define SteppingStoneSampler_H

#include "MarginalLikelihoodEstimator.h"

#include <string>
#include <vector>

namespace RevBayesCore {
    
    /**
     * @brief SteppingStone-Sampler class.
     *
     * The SteppingStone sampler analyzes the output of a power posterior and
     * computes the SteppingStone-Sampler marginal likelihood.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @since Version 1.0, 2012-06-17
     *
     */
    class SteppingStoneSampler : public MarginalLikelihoodEstimator {
        
    public:
        SteppingStoneSampler(const std::string &fn, const std::string &pn, const std::string &ln, const std::string &del);             //!< Constructor initializing the object.
        virtual                                            ~SteppingStoneSampler(void);                                                //!< Virtual destructor
        
        // public methods
        SteppingStoneSampler*                               clone(void) const;                                                          //!< Create a deep copy
        double                                              marginalLikelihood( void ) const;                                           //!< Compute the marginal likelihood using SteppingStone-Sampler
        
    };
    
}

#endif
