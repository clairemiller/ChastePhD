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

#include "GammaDistributedStochasticDurationCellCycleModel.hpp"
#include "Exception.hpp"
#include "StemCellProliferativeType.hpp"
#include "TransitCellProliferativeType.hpp"
#include "DifferentiatedCellProliferativeType.hpp"

GammaDistributedStochasticDurationCellCycleModel::GammaDistributedStochasticDurationCellCycleModel()
    : AbstractSimpleCellCycleModel(),
      mShape(DOUBLE_UNSET),
      mScale(DOUBLE_UNSET)
{
}

AbstractCellCycleModel* GammaDistributedStochasticDurationCellCycleModel::CreateCellCycleModel()
{
    // Create a new cell-cycle model
    GammaDistributedStochasticDurationCellCycleModel* p_model = new GammaDistributedStochasticDurationCellCycleModel();

    /*
     * Set each member variable of the new cell-cycle model that inherits
     * its value from the parent.
     *
     * Note 1: some of the new cell-cycle model's member variables (namely
     * mBirthTime, mCurrentCellCyclePhase, mReadyToDivide) will already have been
     * correctly initialized in its constructor.
     *
     * Note 2: one or more of the new cell-cycle model's member variables
     * may be set/overwritten as soon as InitialiseDaughterCell() is called on
     * the new cell-cycle model.
     *
     * Note 3: the member variable mDimension remains unset, since this cell-cycle
     * model does not need to know the spatial dimension, so if we were to call
     * SetDimension() on the new cell-cycle model an exception would be triggered;
     * hence we do not set this member variable.
     */
    p_model->SetBirthTime(mBirthTime);
    p_model->SetMinimumGapDuration(mMinimumGapDuration);
    p_model->SetStemCellG1Duration(mStemCellG1Duration);
    p_model->SetTransitCellG1Duration(mTransitCellG1Duration);
    p_model->SetSDuration(mSDuration);
    p_model->SetG2Duration(mG2Duration);
    p_model->SetMDuration(mMDuration);
    p_model->SetShape(mShape);
    p_model->SetScale(mScale);

    return p_model;
}

void GammaDistributedStochasticDurationCellCycleModel::SetG1Duration()
{
    if (    mpCell->GetCellProliferativeType()->IsType<StemCellProliferativeType>()
         || mpCell->GetCellProliferativeType()->IsType<TransitCellProliferativeType>() )
    {
        // Generate a gamma random number with mShape and mScale
        mG1Duration = RandomNumberGenerator::Instance()->GammaRandomDeviate(mShape, mScale);
    }
    else if (mpCell->GetCellProliferativeType()->IsType<DifferentiatedCellProliferativeType>())
    {
        mG1Duration = DBL_MAX;
    }
    else
    {
        NEVER_REACHED;
    }
}

void GammaDistributedStochasticDurationCellCycleModel::SetShape(double shape)
{
    mShape = shape;
}

void GammaDistributedStochasticDurationCellCycleModel::SetScale(double scale)
{
    mScale = scale;
}

double GammaDistributedStochasticDurationCellCycleModel::GetShape()
{
    return mShape;
}

double GammaDistributedStochasticDurationCellCycleModel::GetScale()
{
    return mScale;
}

void GammaDistributedStochasticDurationCellCycleModel::OutputCellCycleModelParameters(out_stream& rParamsFile)
{
    *rParamsFile << "\t\t\t<Shape>" << mShape << "</Shape>\n";
    *rParamsFile << "\t\t\t<Scale>" << mScale << "</Scale>\n";

    AbstractSimpleCellCycleModel::OutputCellCycleModelParameters(rParamsFile);
}

// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(GammaDistributedStochasticDurationCellCycleModel)
