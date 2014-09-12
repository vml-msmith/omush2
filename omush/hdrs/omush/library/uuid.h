/**
 * \file uui.dh
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUHS_HDRS_OMUSH_LIBRARY_UUID
#define OMUHS_HDRS_OMUSH_LIBRARY_UUID

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
namespace omush {
  namespace library {
    typedef  boost::uuids::uuid uuid;

    inline uuid generate_uuid() {
      boost::uuids::random_generator gen;
      return gen();
    }

  }  // namespace library

} // omush

#endif //  OMUHS_HDRS_OMUSH_LIBRARY_UUID
