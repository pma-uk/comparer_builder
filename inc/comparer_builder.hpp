/*
* Filename:		comparer_builder.hpp
* Project:		ComparerBuilder
* By:			Paul Ma
* Date:			August 13, 2024
* Description:  This header file defines the `comparer_builder` template class, which allows for the construction of custom comparison
*               functors based on multiple member variables or functions of a class. The builder supports ascending or descending
*               order for each member used in the comparison. The built comparer can be used to define custom sorting orders for
*               containers of objects of type T.
*/

#ifndef COMPARER_BUILDER_HPP
#define COMPARER_BUILDER_HPP

#include <functional>

// Template class for building custom comparers
template<typename T>
class comparer_builder 
{
private:
    std::vector<std::function<bool(const T&, const T&)>> comparers; // Vector to store comparer functions for objects of class type T

public:

    /*
    * Function:     comparer_builder::by
    * Purpose:      Adds a comparison function based on a member variable of the class T.
    *
    * Inputs:       U T::* pMember      Pointer to member variable or function of type U within class T.
    *               bool descending     If true, sorts in descending order; otherwise, sorts in ascending order (default is false).
    *
    * Outputs:      None
    *
    * Returns:      comparer_builder&   Reference to the current comparer_builder object to allow method chaining.
    */
    template<typename U>
    comparer_builder& by(U T::* pMember, bool descending = false)
    {
        comparers.emplace_back
        (
            [pMember, descending](const T& lhs, const T& rhs) 
            {
                // Using std::invoke should allow call or access to be uniform - reduces code redundancy and need for function overloading
                auto lhsValue = std::invoke(pMember, lhs);
                auto rhsValue = std::invoke(pMember, rhs);

                if (descending)
                {
                    return lhsValue > rhsValue;
                }
                else
                {
                    return lhsValue < rhsValue;
                }
            }
        );
        return *this;
    }


    /*
    * Function:     comparer_builder::build
    * Purpose:      Constructs a comparison functor based on the series of comparison functions added through `by` methods.
    *
    * Inputs:       None
    *
    * Outputs:      None
    *
    * Returns:      auto    A lambda function that takes two objects of type T and returns a boolean indicating if the first is less than the second.
    */
    auto build() const 
    {
        return [comparers = this->comparers](const T& lhs, const T& rhs) 
        {
            // Iterate through comparers sequentially - if comparer returns false in both directions then the specific members for the LHS and RHS are equal,
            // in which case move to next comparer (with different class member, ideally). If all comparers return false, LHS and RHS are 'fully' equal
            for (const auto& comparer : comparers) 
            {   
                if (comparer(lhs, rhs)) return true;
                if (comparer(rhs, lhs)) return false;
            }
            return false;
        };
    }
};

#endif // COMPARER_BUILDER_HPP