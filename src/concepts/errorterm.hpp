      /** 
       * Ctor
       * Creates an error term with the deviation dev and a new noise symbol
       * 
       * @param dev partial deviation
       */      /** 
       * Ctor
       * Creates an error term with the deviation dev and a new noise symbol
       * 
       * @param dev partial deviation
       */namespace yalaa
{
  /// Namespace for concepts used in \c YalAA
  namespace concepts
  {
    /// Concept defining error terms
    /**
     * @param T type for partial deviations
     * 
     * An error term in \c YalAA represents a combination of a partial deviation
     * and a noise symbol in the original model.
     */
    template <typename T>
    class ErrorTerm
    {
    public:
      /// Type of *this
      typedef ErrorTerm<T> self_t;
      /// Type for partial deviations
      typedef T base_t;

      /// Const reference or base_t depending whether base_t is a fundamental type
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;

      /// Indicates that the class is an ErrorTerm
      typedef void trait_is_err_t;

      /** 
       * Ctor
       * Creates an error term with a new noise symbol without a deviation
       * 
       */
      ErrorTerm();

      /** 
       * Copy Ctor
       * 
       * 
       * @param other error term to copy
       */
      ErrorTerm(const self_t &other);

      /** 
       * Ctor
       * Creates an error term with the deviation dev and a new noise symbol
       * 
       * @param dev partial deviation
       */
      ErrorTerm(base_ref_t dev);

      /**
       * Checks whether two error terms have the same symbolic noise variable
       *
       * @param other Other error term to check
       *
       * @return true if both terms have the same symbolic noise variable
       */
      inline bool operator==(const self_t &other) const;

      /**
       * Defines an ordering on the symbolic noise variable
       *
       * @param other Other error term
       *
       * @return true if this error term is less than the other in the ordering
       */
      inline bool operator<(const self_t &other) const;

      /**
       * Gets the current deviation of the error term
       *
       * @return Current deviation of this error term
       */
      inline base_ref_t dev() const;

      /**
       * Sets deviation of this error term
       *
       * @param new_dev new deviation
       */
      inline void set_dev(base_ref_t new_dev);

      /**
       * Prints this error term to a stream
       *
       * @param os output stream
       */
      inline void print(std::ostream &os) const;

      /**
       * Determines whether this ErrorTerm is a "special term"
       *
       * @return 0 if not a special term, the type otherwise
       */
      inline unsigned special() const;

      /**
       * Marks this error term as a special term
       * Note: type has to be greater than 0
       *
       * @param type type of the term
       */
      inline void set_special(unsigned type);
    };
  }
}
