/*

Copyright (C) University of Oxford, 2005-2010

University of Oxford means the Chancellor, Masters and Scholars of the
University of Oxford, having an administrative office at Wellington
Square, Oxford OX1 2JD, UK.

This file is part of Chaste.

Chaste is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 2.1 of the License, or
(at your option) any later version.

Chaste is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details. The offer of Chaste under the terms of the
License is subject to the License being interpreted in accordance with
English Law and subject to any action against the University of Oxford
being under the jurisdiction of the English Courts.

You should have received a copy of the GNU Lesser General Public License
along with Chaste. If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef TESTLATTICEBASEDUPDATERULES_HPP_
#define TESTLATTICEBASEDUPDATERULES_HPP_

#include <cxxtest/TestSuite.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "CellsGenerator.hpp"
#include "DiffusionUpdateRule.hpp"
#include "AdvectionUpdateRule.hpp"
#include "LatticeBasedCellPopulation.hpp"
#include "CellsGenerator.hpp"
#include "FixedDurationGenerationBasedCellCycleModel.hpp"
#include "AbstractCellBasedTestSuite.hpp"

class TestLatticeBasedUpdateRules : public AbstractCellBasedTestSuite
{
public:

    void TestDiffusionUpdateRuleConstructor()
    {
        // Create update rule using default input argument
        DiffusionUpdateRule<2> update_rule1;

        // Check the diffusion constant has been set correctly
        TS_ASSERT_DELTA(update_rule1.GetDiffusionConstant(), 1.0000, 1e-6);

        // Create update rule using different input argument
        DiffusionUpdateRule<3> update_rule2(3.1412);

        // Check the diffusion constant has been set correctly
        TS_ASSERT_DELTA(update_rule2.GetDiffusionConstant(), 3.1412, 1e-6);
    }

    void TestDiffusionUpdateRuleGetNewLocationOfCell() throw(Exception)
    {
        // Create mesh
        TetrahedralMesh<2,2> mesh;
        mesh.ConstructRectangularMesh(2, 2, true); // 3*3 nodes

        // Create a cell
        boost::shared_ptr<AbstractCellMutationState> p_state(new WildTypeCellMutationState);
        FixedDurationGenerationBasedCellCycleModel* p_model = new FixedDurationGenerationBasedCellCycleModel();
        p_model->SetCellProliferativeType(DIFFERENTIATED);
        CellPtr p_cell(new Cell(p_state, p_model));

        // Create lattice-based cell population
        std::vector<CellPtr> cells;
        cells.push_back(p_cell);

        std::vector<unsigned> real_node_indices;
        real_node_indices.push_back(4);

        LatticeBasedCellPopulation<2> cell_population(mesh, cells, real_node_indices);

        // Create update rule
        DiffusionUpdateRule<2> update_rule(2.0);

        // Set the time step high enough that movement is guaranteed
        double dt = 1.0;

        // Test an exception is thrown when using a location index that does not correspond to a cell
        TS_ASSERT_THROWS_THIS(update_rule.GetNewLocationOfCell(0, cell_population, dt),
                              "There is no cell at the current location.");

        // Check the cell moves to the correct new location (random, but reproducible)
        unsigned new_location_index = update_rule.GetNewLocationOfCell(4, cell_population, dt);

        TS_ASSERT_EQUALS(new_location_index, 7u);
    }

    void TestArchiveDiffusionUpdateRule() throw(Exception)
    {
        OutputFileHandler handler("archive", false); // don't erase contents of folder
        std::string archive_filename = handler.GetOutputDirectoryFullPath() + "diff_update_rule.arch";

        {
            // Create update rule using different input argument
            DiffusionUpdateRule<2> update_rule(1.25);

            std::ofstream ofs(archive_filename.c_str());
            boost::archive::text_oarchive output_arch(ofs);

            // Serialize via pointer
            DiffusionUpdateRule<2>* const p_update_rule = &update_rule;

            output_arch << p_update_rule;
        }

        {
        	// Create an input archive
            std::ifstream ifs(archive_filename.c_str(), std::ios::binary);
            boost::archive::text_iarchive input_arch(ifs);

            DiffusionUpdateRule<2>* p_update_rule;

            // Restore from the archive
            input_arch >> p_update_rule;

            // Test the member data
            TS_ASSERT_DELTA(p_update_rule->GetDiffusionConstant(), 1.25, 1e-6);

            // Tidy up
            delete p_update_rule;
        }
    }

    void TestAdvectionUpdateRuleGetNewLocationOfCell() throw(Exception)
    {
        // Create mesh
        TetrahedralMesh<2,2> mesh;
        mesh.ConstructRectangularMesh(5, 5, true); // 6*6 nodes

        // Create a line of cells along the bottom of the mesh
        boost::shared_ptr<AbstractCellMutationState> p_state(new WildTypeCellMutationState);

        // Create cells
        std::vector<CellPtr> cells;
        CellsGenerator<FixedDurationGenerationBasedCellCycleModel, 2> cells_generator;
        cells_generator.GenerateBasic(cells, 6);

        std::vector<unsigned> real_node_indices;
        for (unsigned i=0; i<cells.size(); i++)
        {
            cells[i]->GetCellCycleModel()->SetCellProliferativeType(DIFFERENTIATED);
            real_node_indices.push_back(i);
        }

        // Create cell population
        LatticeBasedCellPopulation<2> cell_population(mesh, cells, real_node_indices);

        // Create advection update rule: impose a flow 'north' with (mean) speed 2
        unsigned flow_direction = 0; // north
        AdvectionUpdateRule<2> update_rule(flow_direction, 2.0);

        // Take the time step large enough for flow-induced movement to be guaranteed
        double dt = 1.0;

        // Test an exception is thrown when using a location index that does not correspond to a cell
        TS_ASSERT_THROWS_THIS(update_rule.GetNewLocationOfCell(10, cell_population, dt),
                              "There is no cell at the current location.");

        // Call GetNewLocationOfCell() on each cell
        for (unsigned i=0; i<6; i++)
        {
            unsigned new_location_index = update_rule.GetNewLocationOfCell(i, cell_population, dt);
            TS_ASSERT_EQUALS(new_location_index, i+6);
        }
    }

    void TestArchiveAdvectionUpdateRule() throw(Exception)
    {
        OutputFileHandler handler("archive", false); // don't erase contents of folder
        std::string archive_filename = handler.GetOutputDirectoryFullPath() + "adv_update_rule.arch";

        {
            // Create update rule using different input argument
            AdvectionUpdateRule<2> update_rule(3, 1.25);

            std::ofstream ofs(archive_filename.c_str());
            boost::archive::text_oarchive output_arch(ofs);

            // Serialize via pointer
            AdvectionUpdateRule<2>* const p_update_rule = &update_rule;

            output_arch << p_update_rule;
        }

        {
            // Create an input archive
            std::ifstream ifs(archive_filename.c_str(), std::ios::binary);
            boost::archive::text_iarchive input_arch(ifs);

            AdvectionUpdateRule<2>* p_update_rule;

            // Restore from the archive
            input_arch >> p_update_rule;

            // Test the member data
            TS_ASSERT_DELTA(p_update_rule->GetAdvectionSpeed(), 1.25, 1e-6);
            TS_ASSERT_EQUALS(p_update_rule->GetAdvectionDirection(), 3u);

            // Tidy up
            delete p_update_rule;
        }
    }
};

#endif /*TESTLATTICEBASEDUPDATERULES_HPP_*/