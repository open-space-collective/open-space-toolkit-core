////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           Library/Core/Containers/Table/Row.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Core_Containers_Table_Row__
#define __OpenSpaceToolkit_Core_Containers_Table_Row__

#include <Library/Core/Containers/Table/Cell.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/Size.hpp>
#include <Library/Core/Types/Index.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace ctnr
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Table ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace table
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Index ;
using library::core::types::Size ;
using library::core::types::String ;
using library::core::ctnr::Array ;
using library::core::ctnr::table::Cell ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Row of table container

class Row
{

    public:

        typedef                 Array<Cell>::ConstIterator                      ConstIterator ;

                                Row                                         (   const   Array<Cell>&                aCellArray                                  ) ;

                                Row                                         (           std::initializer_list<Cell> aCellList                                   ) ;

                                Row                                         (   const   Table*                      aTablePtr                                   ) ;

                                Row                                         (   const   Table*                      aTablePtr,
                                                                                const   Array<Cell>&                aCellArray                                  ) ;

                                Row                                         (   const   Row&                        aRow                                        ) ;

        Row&                    operator =                                  (   const   Row&                        aRow                                        ) ;

        bool                    operator ==                                 (   const   Row&                        aRow                                        ) const ;

        bool                    operator !=                                 (   const   Row&                        aRow                                        ) const ;

        const Cell&             operator []                                 (   const   Index&                      aColumnIndex                                ) const ;

        const Cell&             operator []                                 (   const   String&                     aColumnName                                 ) const ;

        bool                    isEmpty                                     ( ) const ;

        Size                    getSize                                     ( ) const ;

        Row::ConstIterator      begin                                       ( ) const ;

        Row::ConstIterator      end                                         ( ) const ;

        void                    associateTable                              (   const   Table*                      aTablePtr                                   ) ;

    private:

        const Table*            tablePtr_ ;
        Array<Cell>             cells_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
