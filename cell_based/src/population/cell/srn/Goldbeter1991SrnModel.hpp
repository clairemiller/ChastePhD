/*

Copyright (c) 2005-2016, University of Oxford.
All rights reserved.

University of Oxford means the Chancellor, Masters and Scholars of the
University of Oxford, having an administrative office at Wellington
Square, Oxford OX1 2JD, UK.

This file is part of Chaste.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
 * Neither the name of the University of Oxford nor the names of its
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef GOLDBETER1991SRNMODEL_HPP_
#define GOLDBETER1991SRNMODEL_HPP_



#include "ChasteSerialization.hpp"
#include <boost/serialization/base_object.hpp>

#include "Goldbeter1991OdeSystem.hpp"
#include "AbstractOdeSrnModel.hpp"

/**
 * A subclass of StochasticDurationGenerationBasedCellCycleModel
 * that includes a Goldbeter1991 ODE system in the SRN.
 *
 * For another example of a cell cycle model that is not *based on*
 * an ODE system, but that includes an ODE system, see
 * SingleOdeWntCellCycleModel (in Crypt).
 */
class Goldbeter1991SrnModel : public AbstractOdeSrnModel
{
private:

    /** Needed for serialization. */
    friend class boost::serialization::access;
    /**
     * Archive the cell-cycle model and member variables.
     *
     * @param archive the archive
     * @param version the current version of this class
     */
    template<class Archive>
    void serialize(Archive & archive, const unsigned int version)
    {
        archive & boost::serialization::base_object<AbstractOdeSrnModel>(*this);
    }


public:

    /**
     * Default constructor calls base class.
     *
     * @param pOdeSolver An optional pointer to a cell-cycle model ODE solver object (allows the use of different ODE solvers)
     */
    Goldbeter1991SrnModel(boost::shared_ptr<AbstractCellCycleModelOdeSolver> pOdeSolver = boost::shared_ptr<AbstractCellCycleModelOdeSolver>());


    /**
     * Overridden builder method to create new copies of
     * this srn model.
     *
     * @return Returns a copy of the current srn model.
     */
    AbstractSrnModel* CreateSrnModel();

    /**
     * Initialise the cell-cycle model at the start of a simulation.
     *
     * This overridden method sets up a new Delta-Notch ODE system.
     */
    void Initialise(); // override

    /**
     * Overridden SimulateToTime() method for custom behaviour
     */
    void SimulateToCurrentTime();

    /**
     * Outputs cell-cycle model parameters to file.
     *
     * @param rParamsFile the file stream to which the parameters are output
     */
    void OutputSrnModelParameters(out_stream& rParamsFile);

    /**
     * @return the value of the state variable C in the ODE system.
     */
    double GetC();

    /**
     * @return the value of the state variable M in the ODE system.
     */
    double GetM();

    /**
     * @return the value of the state variable X in the ODE system.
     */
    double GetX();

};

// Declare identifier for the serializer
#include "SerializationExportWrapper.hpp"
CHASTE_CLASS_EXPORT(Goldbeter1991SrnModel)
#include "CellCycleModelOdeSolverExportWrapper.hpp"
EXPORT_CELL_CYCLE_MODEL_ODE_SOLVER(Goldbeter1991SrnModel)



#endif /* GOLDBETER1991SRNMODEL_HPP_ */
