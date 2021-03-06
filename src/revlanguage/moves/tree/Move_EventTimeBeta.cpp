#include "ArgumentRule.h"
#include "ArgumentRules.h"
#include "MetropolisHastingsMove.h"
#include "Move_EventTimeBeta.h"
#include "EventBranchTimeBetaProposal.h"
#include "RbException.h"
#include "RealPos.h"
#include "RlBoolean.h"
#include "RlTimeTree.h"
#include "TypedDagNode.h"
#include "TypeSpec.h"


using namespace RevLanguage;

/**
 * Default constructor.
 *
 * The default constructor does nothing except allocating the object.
 */
Move_EventTimeBeta::Move_EventTimeBeta() : Move()
{
    
}


/**
 * The clone function is a convenience function to create proper copies of inherited objected.
 * E.g. a.clone() will create a clone of the correct type even if 'a' is of derived type 'b'.
 *
 * \return A new copy of the move.
 */
Move_EventTimeBeta* Move_EventTimeBeta::clone(void) const
{
    
    return new Move_EventTimeBeta(*this);
}


/**
 * Create a new internal move object.
 *
 * This function simply dynamically allocates a new internal move object that is
 * associated with the variable (DAG-node). The internal move object is created by calling its
 * constructor and passing the move-parameters (the variable and other parameters) as arguments of the
 * constructor. The move constructor takes care of the proper hook-ups.
 *
 */
void Move_EventTimeBeta::constructInternalObject( void )
{
    // we free the memory first
    delete value;
    
    // now allocate a new sliding move
    double w = static_cast<const RealPos &>( weight->getRevObject() ).getValue();
    RevBayesCore::TypedDagNode<RevBayesCore::Tree>* tmp = static_cast<const TimeTree &>( tree->getRevObject() ).getDagNode();
    RevBayesCore::StochasticNode<RevBayesCore::Tree> *n = static_cast<RevBayesCore::StochasticNode<RevBayesCore::Tree> *>( tmp );
    double d = static_cast<const RealPos &>( delta->getRevObject() ).getValue();
    double o = static_cast<const RealPos &>( offset->getRevObject() ).getValue();
    bool tu = static_cast<const RlBoolean &>( tune->getRevObject() ).getValue();
    
    RevBayesCore::Proposal *p = new RevBayesCore::EventBranchTimeBetaProposal(n,d,o);
    value = new RevBayesCore::MetropolisHastingsMove(p,w,tu);
    
}


/**
 * Get Rev type of object
 *
 * \return The class' name.
 */
const std::string& Move_EventTimeBeta::getClassType(void)
{
    
    static std::string rev_type = "Move_EventTimeBeta";
    
    return rev_type;
}


/**
 * Get class type spec describing type of an object from this class (static).
 *
 * \return TypeSpec of this class.
 */
const TypeSpec& Move_EventTimeBeta::getClassTypeSpec(void)
{
    
    static TypeSpec rev_type_spec = TypeSpec( getClassType(), new TypeSpec( Move::getClassTypeSpec() ) );
    
    return rev_type_spec;
}


/**
 * Get the Rev name for the constructor function.
 *
 * \return Rev name of constructor function.
 */
std::string Move_EventTimeBeta::getMoveName( void ) const
{
    // create a constructor function name variable that is the same for all instance of this class
    std::string c_name = "EventTimeBeta";
    
    return c_name;
}


/**
 * Get the member rules used to create the constructor of this object.
 *
 * The member rules of the scale move are:
 * (1) the variable which must be a time-tree.
 *
 * \return The member rules.
 */
const MemberRules& Move_EventTimeBeta::getParameterRules(void) const
{
    
    static MemberRules memberRules;
    static bool rules_set = false;
    
    if ( !rules_set )
    {
        memberRules.push_back( new ArgumentRule( "tree", TimeTree::getClassTypeSpec(), "The time-tree variable on which this move operates.", ArgumentRule::BY_REFERENCE, ArgumentRule::STOCHASTIC ) );
        memberRules.push_back( new ArgumentRule( "delta"  , RealPos::getClassTypeSpec()  , "The concentration parameter.", ArgumentRule::BY_VALUE    , ArgumentRule::ANY       , new RealPos( 1.0 ) ) );
        memberRules.push_back( new ArgumentRule( "offset"  , RealPos::getClassTypeSpec()  , "The offset for the proposal density.", ArgumentRule::BY_VALUE    , ArgumentRule::ANY       , new RealPos( 2.0 ) ) );
        memberRules.push_back( new ArgumentRule( "tune"   , RlBoolean::getClassTypeSpec(), "Should we tune the concentration parameter during burnin?", ArgumentRule::BY_VALUE    , ArgumentRule::ANY       , new RlBoolean( true ) ) );
        

        /* Inherit weight from Move, put it after variable */
        const MemberRules& inheritedRules = Move::getParameterRules();
        memberRules.insert( memberRules.end(), inheritedRules.begin(), inheritedRules.end() );
        
        rules_set = true;
    }
    
    return memberRules;
}


/**
 * Get type-specification on this object (non-static).
 *
 * \return The type spec of this object.
 */
const TypeSpec& Move_EventTimeBeta::getTypeSpec( void ) const
{
    
    static TypeSpec type_spec = getClassTypeSpec();
    
    return type_spec;
}


/**
 * Set a member variable.
 *
 * Sets a member variable with the given name and store the pointer to the variable.
 * The value of the variable might still change but this function needs to be called again if the pointer to
 * the variable changes. The current values will be used to create the distribution object.
 *
 * \param[in]    name     Name of the member variable.
 * \param[in]    var      Pointer to the variable.
 */
void Move_EventTimeBeta::setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var)
{
    
    if ( name == "tree" )
    {
        tree = var;
    }
    else if ( name == "delta" )
    {
        delta = var;
    }
    else if ( name == "offset" )
    {
        offset = var;
    }
    else if ( name == "tune" )
    {
        tune = var;
    }
    else
    {
        Move::setConstParameter(name, var);
    }
    
}




