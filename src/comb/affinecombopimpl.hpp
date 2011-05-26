#ifndef __AFFINECOMBOPIMPL_HPP__
#define __AFFINECOMBOPIMPL_HPP__

namespace yalaa 
{
  namespace details
  {
    /** 
     * Adds two affine combinations
     * The result is stored inside the first combination
     * 
     * @param ac1 First combination
     * @param ac2 Second combination
     * 
     * @return Number of performed additions
     */
    template<class AC, bool CENTRAL>
    unsigned add_ac_ac(AC *ac1, const AC &ac2);

    template<class AC>
    unsigned add_ac_ac(AC* ac1, const AC &ac2);

    /** 
     * Substracts two affine combinations
     * The result is stored inside the first combination
     * 
     * @param ac1 First combination
     * @param ac2 Second combination
     * 
     * @return Number of performed substractions
     */
    template<class AC, class CENTRAL>
    unsigned sub_ac_ac(AC* ac1, const AC &ac2);

    template<class AC>
    unsigned sub_ac_ac(AC* ac1, const AC &ac2);

    /** 
     * Scales an affine combination
     * 
     * @param ac1 Affine combination to scale
     * @param sc Scaling factor central
     * @param sn Scaling factor noise
     * 
     * @return Number of operations
     */
    template<class AC>
    unsigned mul_ac_s(AC *ac, typename AC::base_ref_t sc, typename AC::base_ref_t sn);
    
    /** 
     * Adds an scalar to an affine combination
     * 
     * @param ac1 Affine combination for addition
     * @param s Scalar to add
     * 
     * @return Number of operations
     */
    template<class AC>
    unsigned add_ac_s(AC *ac, typename AC::base_ref_t s);

    /** 
     * Negates an affine combination
     * 
     * @param ac Affine combination to negate
     * 
     * @return number of operations
     */
    template<class AC>
    unsigned neg_ac(AC *ac);
  }
}


#endif /*__AFFINECOMBOP_HPP__*/
