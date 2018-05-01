#ifndef CSP_TAGFACTORY_HH
#define CSP_TAGFACTORY_HH

#include <string>
#include "tag.hh"

/** \brief A factory to produce CSP tags.
 *
 */

class TagFactory {
public:
    /**
     * Produces (instantiate) a new CSP tag that's derived from base class Tag.
     * @param tag Produces a Tag according to this.
     * @throw std::invalid_argument Unkown type of Tag
     * @return A pointer to the produced CSP tag
     */
    static Tag* produce(const std::string &tag);
};

/** @example example_tagfactory.cc
 * This is an example of how to use the TagFactory class.
 */

#endif

