/*
 * Copyright (C) 2017     Critical Embedded System Laboratory (LSEC)
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
 *    \class hamster::HAMSTERNode HAMSTERNode.h
 *    \brief Provides a basic structure for all nodes in the application.
 *    \details 
 *       \note This class is present only in Design Model, not existing in the
 *             conceptual model.
 * 
 *       \n
 *       This class is used as a point of inheritance for classes in conceptual
 *       model which represent any nodes in the architecture.
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 * \endif
 */

#ifndef HAMSTERNODE_H
#define HAMSTERNODE_H

#include "HAMSTEROptions.h"
#include "HAMSTERLogger.h"


namespace hamster{
    
class HAMSTERNode {
public:
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
    HAMSTERNode(){};
    virtual ~HAMSTERNode(){};

//-----------------------------------------------------------------------------
// HAMSTERNode Methods
//-----------------------------------------------------------------------------
    /*! 
     * \fn void HAMSTERNode::initialize()
     * \brief Initialization of the node.
     * \details Pure virtual method which perform the necessary steps to 
     * initialize a HAMSTERNode.
     * \attention All concrete child classes must provide an implementation 
     * for this method.
     */
    virtual void initialize(void) = 0;
    /*! 
     * \fn void HAMSTERNode::execute()
     * \brief Main loop of the node.
     * \details Pure virtual method which implements the main functionality of
     * a HAMSTERNode.
     * \attention All concrete child classes must provide an implementation 
     * for this method.
     */
    virtual void execute(void) = 0;
    /*! 
     * \fn void HAMSTERNode::nodeTermination()
     * \brief Termination of the node.
     * \details Pure virtual method which perform the necessary steps to 
     * correctly terminate a HAMSTERNode.
     * \attention All concrete child classes must provide an implementation 
     * for this method.
     */
    virtual void nodeTermination(void) = 0;
    
    /*!
     * \fn inline friend std::ostream& hamster::HAMSTERNode::operator<<(std::ostream& stream,HAMSTERNode& node)
     * \brief Operator << overload for all HAMSTER Nodes.
     * \details This method invokes method printNode, which is a private, pure
     * virtual function in HAMSTERNode class. This ensures that all HAMSTER Nodes
     * provides a function in which their important data is sent to output stream.
     */
    inline friend std::ostream& operator<<(std::ostream& stream,HAMSTERNode * node){
        return node->printNode(stream);
    }
    
    inline friend std::ostream& operator<<(std::ostream& stream,HAMSTERNode& node){
        return node.printNode(stream);
    }

private:
    /*!
     * \fn virtual std::ostream& hamster::HAMSTERNode::printNode(std::ostream& stream) const
     * \brief Outputs the information of the HAMSTERNode to the output stream.
     * \details Pure virtual method which inserts the details of a HAMSTER Node
     * in an output stream to be used in operator << overload.
     * \attention All concrete child classes must provide an implementation for
     * this method.
     */
    virtual std::ostream& printNode(std::ostream& stream) const = 0;
protected:
        bool terminate = false;
};

}

#endif /* HAMSTERNODE_H */

