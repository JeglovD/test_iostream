#pragma once

namespace DJ
{
// Used to initialize _Mycont when _SECURE_SCL is off
#define IGNORE_MYCONT ( ( const ContainerBase*) -2 )

// struct _Container_base
struct ContainerBase
{
};

// identifying tag for input iterators
// struct input_iterator_tag
struct InputIteratorTag {};

// identifying tag for forward iterators
// struct forward_iterator_tag
struct ForwardIteratorTag: public InputIteratorTag {};

// identifying tag for bidirectional iterators
// struct bidirectional_iterator_tag
struct BidirectionalIteratorTag: public ForwardIteratorTag {};

// identifying tag for random-access iterators
// struct random_access_iterator_tag
struct RandomAccessIteratorTag: public BidirectionalIteratorTag {};

// base of all iterators
// struct _ITERATOR_BASE
struct IteratorBase
{
   const ContainerBase* mCont;
};

// base type for container random-access iterator classes
template< typename Type, typename Difference, typename Pointer, typename Reference, typename BaseClass >
// struct _Ranit_base
struct RanitBase: public BaseClass
{
   typedef RandomAccessIteratorTag IteratorCategory;
   typedef Type ValueType;
   typedef Difference DifferenceType;
   typedef Difference DistanceType;	// retained
   typedef Pointer Pointer;
   typedef Reference Reference;
};

// typedef _Iterator_base _Iterator_base_secure;
typedef IteratorBase IteratorBaseSecure;
} // namespace DJ
