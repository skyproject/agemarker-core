#ifndef ACL_ATOMIC_H
#define ACL_ATOMIC_H

#include <atomic>

#include "acl_global.h"

namespace ACL
{
    struct AGEMARKERCORESHARED_EXPORT AtomicUInt64
    {
        std::atomic<uint64_t> atomic;

        AtomicUInt64() : atomic ( uint64_t() ) {}

        explicit AtomicUInt64 ( uint64_t const &v ) : atomic ( v ) {}
        explicit AtomicUInt64 ( std::atomic<uint64_t> const &a ) : atomic ( a.load() ) {}

        AtomicUInt64 ( AtomicUInt64 const &other ) : atomic ( other.atomic.load() ) {}

        AtomicUInt64 &operator= ( AtomicUInt64 const &other )
        {
            atomic.store ( other.atomic.load() );
            return *this;
        }

        AtomicUInt64 operator++ ()
        {
            this->atomic++;
            return *this;
        }

        template <typename T_i>
        AtomicUInt64 operator= ( T_i const &other )
        {
            this->atomic = other;
            return *this;
        }

        bool operator< ( AtomicUInt64 const &other )
        {
            if ( atomic < other.atomic )
            {
                return true;
            }
            return false;
        }

        bool operator> ( AtomicUInt64 const &other )
        {
            if ( atomic > other.atomic )
            {
                return true;
            }
            return false;
        }

        template <typename T_i>
        bool operator< ( T_i const &other )
        {
            if ( atomic < other )
            {
                return true;
            }
            return false;
        }

        template <typename T_i>
        bool operator> ( T_i const &other )
        {
            if ( atomic > other )
            {
                return true;
            }
            return false;
        }
    };
}

#endif // ACL_ATOMIC_H
