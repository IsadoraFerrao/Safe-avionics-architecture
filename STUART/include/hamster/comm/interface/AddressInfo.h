/*
 * Copyright (C) 2018     Critical Embedded System Laboratory (LSEC)
 * 
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * See the GNU Lesser General Public License for more details.
 * <http://www.gnu.org/licenses/>
 */

/*!
 * \if DESIGN_MODEL
 * 
 *  \anchor AddressInfo
 *  \class hamster::comm::interface::AddressInfo AddressInfo.h
 *  \brief Encapsulates adressing info for interfaces.
 *  \details This is an empty class created so that the poliformism of various
 *  types of interface is possible.
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 * 
 *  \endif
 */


#ifndef ADDRESSINFO_H
#define ADDRESSINFO_H

#include "MessageField.h"
#include "CommInterface.h"

namespace hamster{
namespace comm{
namespace interface{
    
namespace inet_socket{class INETSocketAddressInfo;}

class AddressInfo : public messaging::MessageField {

public:
    AddressInfo();
    AddressInfo(AddressInfo & info);
    virtual ~AddressInfo();
    
    static AddressInfo * buildAddressInfo(interface::COMM_INTERFACE_TECH type);
};

} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */

#endif /* ADDRESSINFO_H */

